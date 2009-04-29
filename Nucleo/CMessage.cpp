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
// Archivo:     CMessage.cpp
// Prop�sito:   Mensajes del protocolo
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#include "stdafx.h"

////////////////////////////
//          PASS          //
////////////////////////////
CMessagePASS::CMessagePASS ( const CString& szPass )
: m_szPass ( szPass )
{
}
CMessagePASS::~CMessagePASS ( ) { }

bool CMessagePASS::BuildMessage ( SProtocolMessage& message ) const
{
    message.szText = m_szPass;
    return true;
}

bool CMessagePASS::ProcessMessage ( const CString& szLine, const std::vector < CString >& vec )
{
    // Nunca vamos a necesitar procesar este mensaje
    return true;
}


////////////////////////////
//         SERVER         //
////////////////////////////
CMessageSERVER::CMessageSERVER ( const CString& szHost,
                                 unsigned int uiDepth,
                                 time_t timestamp,
                                 const CString& szProtocol,
                                 unsigned long ulNumeric,
                                 unsigned long ulMaxusers,
                                 const CString& szFlags,
                                 const CString& szDesc )
: m_szHost ( szHost ),
  m_uiDepth ( uiDepth ),
  m_timestamp ( timestamp ),
  m_szProtocol ( szProtocol ),
  m_ulNumeric ( ulNumeric ),
  m_ulMaxusers ( ulMaxusers ),
  m_szFlags ( szFlags ),
  m_szDesc ( szDesc )
{
}
CMessageSERVER::~CMessageSERVER ( ) { }

bool CMessageSERVER::BuildMessage ( SProtocolMessage& message ) const
{
    char szNumeric [ 4 ];
    char szMaxusers [ 4 ];

    if ( m_ulNumeric > 63 )
    {
        // Num�rico largo
        if ( m_ulNumeric > 4095 )
            return false;

        inttobase64 ( szNumeric, m_ulNumeric, 2 );
        if ( m_ulMaxusers > 262143 )
            return false;
        inttobase64 ( szMaxusers, m_ulMaxusers, 3 );
    }
    else
    {
        // Num�rico corto
        inttobase64 ( szNumeric, m_ulNumeric, 1 );
        if ( m_ulMaxusers > 4095 )
            return false;
        inttobase64 ( szMaxusers, m_ulMaxusers, 2 );
    }

    unsigned long ulTime = static_cast < unsigned long > ( m_timestamp );

    message.szExtraInfo.Format ( "%s %u %lu %lu %s %s%s +%s",
                                 m_szHost.c_str (), m_uiDepth,
                                 ulTime, ulTime,
                                 m_szProtocol.c_str (),
                                 szNumeric, szMaxusers,
                                 m_szFlags.c_str () );
    message.szText = m_szDesc;

    return true;
}

bool CMessageSERVER::ProcessMessage ( const CString& szLine, const std::vector < CString >& vec )
{
    if ( vec.size () < 9 )
        return false;

    if ( GetSource ()->GetType () != CClient::SERVER )
        return false;

    m_szHost = vec [ 2 ];
    m_uiDepth = atoi ( vec [ 3 ] );
    m_timestamp = atol ( vec [ 5 ] );
    m_szProtocol = vec [ 6 ];

    if ( vec [ 7 ].length () > 3 )
    {
        // Num�rico largo
        m_ulNumeric = base64toint ( vec [ 7 ].substr ( 0, 2 ).c_str () );
        m_ulMaxusers = base64toint ( vec [ 7 ].substr ( 2 ).c_str () );
    }
    else
    {
        // Num�rico corto
        m_ulNumeric = base64toint ( vec [ 7 ].substr ( 0, 1 ).c_str () );
        m_ulMaxusers = base64toint ( vec [ 7 ].substr ( 1 ).c_str () );
    }

    m_szFlags = vec [ 8 ].substr ( 1 );
    m_szDesc = vec [ 9 ];

    return true;
}




////////////////////////////
//      END_OF_BURST      //
////////////////////////////
CMessageEND_OF_BURST::~CMessageEND_OF_BURST ( ) { }
bool CMessageEND_OF_BURST::BuildMessage ( SProtocolMessage& message ) const
{
    return true;
}

bool CMessageEND_OF_BURST::ProcessMessage ( const CString& szLine, const std::vector < CString >& vec )
{
    return true;
}


////////////////////////////
//         EOB_ACK        //
////////////////////////////
CMessageEOB_ACK::~CMessageEOB_ACK ( ) { }
bool CMessageEOB_ACK::BuildMessage ( SProtocolMessage& message ) const
{
    return true;
}

bool CMessageEOB_ACK::ProcessMessage ( const CString& szLine, const std::vector < CString >& vec )
{
    return true;
}


////////////////////////////
//          PING          //
////////////////////////////
CMessagePING::CMessagePING ( time_t time, CServer* pDest )
: m_time ( time ), m_pDest ( pDest )
{
}
CMessagePING::~CMessagePING ( ) { }

bool CMessagePING::BuildMessage ( SProtocolMessage& message ) const
{
    // No lo vamos a necesitar
    return false;
}

bool CMessagePING::ProcessMessage ( const CString& szLine, const std::vector < CString >& vec )
{
    if ( vec.size () < 5 )
        return false;

    m_pDest = CProtocol::GetSingleton ().GetMe ().GetServer ( vec [ 3 ] );
    if ( ! m_pDest )
    {
        return false;
    }

    unsigned long ulTime = atol ( vec [ 4 ] );
    m_time = static_cast < time_t > ( ulTime );

    return true;
}



////////////////////////////
//          PONG          //
////////////////////////////
CMessagePONG::CMessagePONG ( time_t time, CServer* pDest )
: m_time ( time ), m_pDest ( pDest )
{
}
CMessagePONG::~CMessagePONG ( ) { }

bool CMessagePONG::BuildMessage ( SProtocolMessage& message ) const
{
    if ( m_pDest )
    {
        char szNumeric [ 4 ];
        unsigned long ulTime = static_cast < unsigned long > ( m_time );

        m_pDest->FormatNumeric ( szNumeric );
        message.szExtraInfo.Format ( "%s !%lu %lu 0 %lu", szNumeric, ulTime, ulTime, ulTime );
        return true;
    }
    return false;
}

bool CMessagePONG::ProcessMessage ( const CString& szLine, const std::vector < CString >& vec )
{
    // No lo vamos a necesitar
    return true;
}

////////////////////////////
//          NICK          //
////////////////////////////
CMessageNICK::CMessageNICK ( const CString& szNick,
                             time_t timestamp,
                             CServer* pServer,
                             unsigned int uiDepth,
                             const CString& szIdent,
                             const CString& szHost,
                             const CString& szModes,
                             unsigned long ulAddress,
                             unsigned long ulNumeric,
                             const CString& szDesc )
: m_szNick ( szNick ),
  m_timestamp ( timestamp ),
  m_pServer ( pServer ),
  m_uiDepth ( uiDepth ),
  m_szIdent ( szIdent ),
  m_szHost ( szHost ),
  m_szModes ( szModes ),
  m_ulAddress ( ulAddress ),
  m_ulNumeric ( ulNumeric ),
  m_szDesc ( szDesc )
{
}
CMessageNICK::~CMessageNICK ( ) { }

bool CMessageNICK::BuildMessage ( SProtocolMessage& message ) const
{
    // TODO
    return true;
}

bool CMessageNICK::ProcessMessage ( const CString& szLine, const std::vector < CString >& vec )
{
    if ( vec.size () < 4 )
        return false;

    if ( vec.size () < 11 )
    {
        // Cambio de nick
        m_pServer = 0;
        m_szNick = vec [ 2 ];
        m_timestamp = static_cast < time_t > ( atoi ( vec [ 3 ] ) );

        m_pServer = 0;
        m_uiDepth = 0;
        m_szIdent = "";
        m_szHost = "";
        m_szModes = "";
        m_ulAddress = 0;
        m_ulNumeric = 0;
        m_szDesc = "";
    }
    else
    {
        CClient* pSource = GetSource ();
        if ( !pSource || pSource->GetType () != CClient::SERVER )
            return false;

        // Nuevo nick desde un servidor
        m_pServer = static_cast < CServer* > ( pSource );
        m_szNick = vec [ 2 ];
        m_uiDepth = atoi ( vec [ 3 ] );
        m_timestamp = static_cast < time_t > ( atol ( vec [ 4 ] ) );
        m_szIdent = vec [ 5 ];
        m_szHost = vec [ 6 ];
        m_szModes = vec [ 7 ];
        m_ulAddress = base64toint ( vec [ 8 ] );
        
        if ( vec [ 9 ].length () > 3 )
        {
            // Num�rico largo
            m_ulNumeric = base64toint ( vec [ 9 ].substr ( 2 ).c_str () );
        }
        else
        {
            // Num�rico corto
            m_ulNumeric = base64toint ( vec [ 9 ].substr ( 1 ).c_str () );
        }

        m_szDesc = vec [ 10 ];
    }

    
    return true;
}


////////////////////////////
//          QUIT          //
////////////////////////////
CMessageQUIT::CMessageQUIT ( const CString& szMessage )
: m_szMessage ( szMessage )
{
}
CMessageQUIT::~CMessageQUIT ( ) { }

bool CMessageQUIT::BuildMessage ( SProtocolMessage& message ) const
{
    // TODO
    return true;
}

bool CMessageQUIT::ProcessMessage ( const CString& szLine, const std::vector < CString >& vec )
{
    if ( vec.size () < 3 )
        return false;

    m_szMessage = vec [ 2 ];
    return true;
}


////////////////////////////
//          MODE          //
////////////////////////////
CMessageMODE::CMessageMODE ( CUser* pUser, const CString& szModes )
: m_pUser ( pUser ), m_szModes ( szModes )
{
}
CMessageMODE::~CMessageMODE ( ) { }

bool CMessageMODE::BuildMessage ( SProtocolMessage& message ) const
{
    // TODO
    return true;
}

bool CMessageMODE::ProcessMessage ( const CString& szLine, const std::vector < CString >& vec )
{
    if ( vec.size () < 4 )
        return false;

    if ( *( vec [ 2 ].c_str () ) == '#' )
    {
        // Cambio de modo de canales
        m_pUser = 0;
    }
    else
    {
        // Cambio de modo de usuarios
        m_pUser = CProtocol::GetSingleton ().GetMe ().GetUserAnywhere ( vec [ 2 ] );
        if ( ! m_pUser )
            return false;

        m_szModes = vec [ 3 ];
    }

    return true;
}
