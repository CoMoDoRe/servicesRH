/////////////////////////////////////////////////////////////
//
// Servicios de redhispana.org
// Est� prohibida la reproducci�n y el uso parcial o total
// del c�digo fuente de estos servicios sin previa
// autorizaci�n escrita del autor de estos servicios.
//
// Si usted viola esta licencia se emprender�n acciones legales.
//
// (C) RedHispana.Org 2009
//
// Archivo:     CProtocol.cpp
// Prop�sito:   Protocolo de cliente
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#include "stdafx.h"

// Parte no est�tica
CProtocol::CProtocol ( )
: m_bGotServer ( false )
{
    m_commandsMap.set_deleted_key ( (const char *)0xFABADA00 );
    m_commandsMap.set_empty_key ( (const char *)0x00000000 );

    AddHandler ( "PING", PROTOCOL_CALLBACK ( &CProtocol::CmdPing, this ) );
}

CProtocol::~CProtocol ( )
{
}


bool CProtocol::Initialize ( const CSocket& socket, const CConfig& config )
{
    m_socket = socket;
    m_config = config;

    // Inicializamos la autenticaci�n
    CString szHost;
    if ( ! m_config.GetValue ( szHost, "bots", "host" ) )
        return false;
    CString szNumeric;
    if ( ! m_config.GetValue ( szNumeric, "bots", "numerico" ) )
        return false;
    CString szPass;
    if ( ! m_config.GetValue ( szPass, "servidor", "clave" ) )
        return false;
    CString szDesc;
    if ( ! m_config.GetValue ( szDesc, "bots", "descripcion" ) )
        return false;

    m_me.szName = szHost;
    m_me.ulNumeric = atol ( szNumeric );

    Send ( CClient(), "PASS", "", CClient(), szPass );

    unsigned long ulNow = static_cast < unsigned long > ( time ( 0 ) );
    char szFormattedNumeric [ 8 ];
    m_me.FormatNumeric ( szFormattedNumeric );
    CString szServerInfo ( "%s 1 %lu %lu P10 %s]]", szHost.c_str (), ulNow, ulNow, szFormattedNumeric );

    Send ( CClient(), "SERVER", szServerInfo, CClient(), szDesc );

    return true;
}

int CProtocol::Loop ( )
{
    if ( m_socket.IsOk () == false )
        return -1;

    int iSize = m_socket.ReadLine ( m_szLine );
    if ( iSize > 0 )
    {
        Process ( m_szLine );
    }
    return iSize;
}

bool CProtocol::Process ( const CString& szLine )
{
    bool bGotText = false;
    std::vector < CString > vec;

    // Separamos los tokens del comando
    int iPos = szLine.find ( ':' );
    if ( iPos != CString::npos )
    {
        bGotText = true;
        szLine.Split ( vec, ' ', iPos );
    }
    else
        szLine.Split ( vec, ' ' );


    if ( !m_bGotServer )
    {
        // El primer mensaje esperado es el de la informaci�n del servidor al que nos conectamos
        if ( bGotText && szLine.compare ( 0, 6, "SERVER" ) == 0 )
        {
            m_bGotServer = true;

            CServer *pServer = new CServer ( vec [ 1 ], std::string ( vec [ 8 ], 1 ) );

            // Calculamos el num�rico
            char szNumeric [ 8 ];
            strcpy ( szNumeric, vec [ 6 ] );
            if ( strlen ( szNumeric ) == 3 )
                szNumeric [ 1 ] = '\0';
            else
                szNumeric [ 2 ] = '\0';
            pServer->ulNumeric = base64toint ( szNumeric );

            CClientManager::GetSingleton ().AddClient ( pServer );

            return true;
        }

        return false;
    }

    unsigned long ulNumeric = base64toint ( vec [ 0 ] );
    CClient* pClient = CClientManager::GetSingleton ().GetClient ( ulNumeric );
    if ( pClient == 0 )
        return false;

    return true;
}

int CProtocol::Send ( const CClient& source, const CString& szCommand, const CString& szExtraInfo, const CClient& dest, const CString& szText )
{
    char szNumeric [ 8 ];

    if ( m_socket.IsOk () == false )
        return -1;

    // Constru�mos el mensaje
    CString szMessage;
    switch ( source.GetType () )
    {
        case CClient::SERVER:
        {
            source.FormatNumeric ( szNumeric );
            szMessage.Format ( "%s ", szNumeric );
            break;
        }
        case CClient::UNKNOWN:
        {
            break;
        }
    }

    szMessage.append ( szCommand );
    if ( szExtraInfo.length () > 0 )
    {
        szMessage.append ( " " );
        szMessage.append ( szExtraInfo );
    }

    switch ( dest.GetType () )
    {
        case CClient::SERVER:
        {
            dest.FormatNumeric ( szNumeric );
            szMessage.append ( " " );
            szMessage.append ( szNumeric );
            break;
        }
        case CClient::UNKNOWN:
        {
            break;
        }
    }

    if ( szText.length () > 0 )
    {
        szMessage.append ( " :" );
        szMessage.append ( szText );
    }

    return m_socket.WriteString ( szMessage );
}

void CProtocol::AddHandler ( const CString& szCommand, const PROTOCOL_CALLBACK& callback )
{
    std::vector < PROTOCOL_CALLBACK* >* pVector;

    t_commandsMap::iterator find = m_commandsMap.find ( szCommand.c_str () );
    if ( find == m_commandsMap.end () )
    {
        std::pair < t_commandsMap::iterator, bool > pair = m_commandsMap.insert (
                                                            t_commandsMap::value_type (
                                                                szCommand.c_str (),
                                                                std::vector < PROTOCOL_CALLBACK* > ( 64 )
                                                            )
                                                           );
        find = pair.first;
    }

    pVector = &((*find).second);

    PROTOCOL_CALLBACK* pCallback = new PROTOCOL_CALLBACK ( callback );
    pVector->push_back ( pCallback );
}

// Parte est�tica
CProtocol CProtocol::ms_instance;

CProtocol& CProtocol::GetSingleton ( )
{
    return ms_instance;
}

CProtocol* CProtocol::GetSingletonPtr ( )
{
    return &GetSingleton ();
}


// Comandos
bool CProtocol::CmdPing ( const CProtocol::SProtocolMessage& message )
{
    return true;
}