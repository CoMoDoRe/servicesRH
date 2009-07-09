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
// Archivo:     CSocket.cpp
// Prop�sito:   Socket TCP
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#include "stdafx.h"


// Parte no est�tica de la clase
CSocket::CSocket ( )
: m_socket ( -1 ), m_bufferSize ( 0 ), m_iErrno ( 0 ), m_uiTimeout ( 0 )
{
}

CSocket::CSocket ( const CSocket& copy )
: m_socket ( -1 ), m_bufferSize ( 0 ), m_iErrno ( 0 ), m_uiTimeout ( 0 )
{
    m_iErrno = copy.m_iErrno;
    m_szError = copy.m_szError;
    if ( copy.m_socket != -1 )
    {
#ifdef WIN32
        m_socket = copy.m_socket;
#else
        m_socket = dup ( copy.m_socket );
#endif
    }
    else
        m_socket = -1;

    memcpy ( m_buffer, copy.m_buffer, copy.m_bufferSize );
    m_bufferSize = copy.m_bufferSize;

    m_uiTimeout = copy.m_uiTimeout;
}

CSocket::CSocket ( const CString& szHost, unsigned short usPort )
: m_socket ( -1 ), m_bufferSize ( 0 ), m_iErrno ( 0 ), m_uiTimeout ( 0 )
{
    Connect ( szHost, usPort );
}

CSocket::~CSocket ( )
{
    Close ();
}

CSocket& CSocket::operator= ( const CSocket& copy )
{
    Close ();

    m_iErrno = copy.m_iErrno;
    m_szError = copy.m_szError;
    if ( copy.m_socket != -1 )
    {
#ifdef WIN32
        m_socket = copy.m_socket;
#else
        m_socket = dup ( copy.m_socket );
#endif
    }
    else
        m_socket = -1;

    memcpy ( m_buffer, copy.m_buffer, copy.m_bufferSize );
    m_bufferSize = copy.m_bufferSize;

    return *this;
}

bool CSocket::Connect ( const CString& szHost, unsigned short usPort )
{
    // Nos aseguramos de que no hay ya una conexi�n activa
    Close ();

    // Creamos el socket
    m_socket = socket ( PF_INET, SOCK_STREAM, IPPROTO_TCP );
    if ( m_socket < 0 )
    {
        m_socket = -1;
        m_iErrno = CPortability::SocketErrno ();;
        CPortability::SocketError ( m_iErrno, m_szError );
        return false;
    }

    // Resolvemos la direcci�n
    hostent* pHost = gethostbyname ( szHost );
    if ( !pHost )
    {
#ifndef WIN32
        m_iErrno = h_errno;
#else
        m_iErrno = CPortability::SocketErrno ();
#endif
        CPortability::SocketError ( m_iErrno, m_szError );
        CPortability::SocketClose ( m_socket );
        m_socket = -1;
        return false;
    }
    if ( pHost->h_addr_list[ 0 ] == 0 )
    {
        m_szError = "No se pudo resolver la direcci�n IP";
        CPortability::SocketClose ( m_socket );
        m_socket = -1;
        return false;
    }

    // Constru�mos la estructura del servidor
    sockaddr_in peerAddr;
    peerAddr.sin_addr.s_addr = *(unsigned long *)pHost->h_addr_list[ 0 ];
    peerAddr.sin_family = AF_INET;
    peerAddr.sin_port = htons ( usPort );

    // Conectamos
    if ( connect ( m_socket, reinterpret_cast < sockaddr* > ( &peerAddr ), sizeof ( peerAddr ) ) < 0 )
    {
        m_iErrno = CPortability::SocketErrno ();
        CPortability::SocketError ( m_iErrno, m_szError );
        CPortability::SocketClose ( m_socket );
        m_socket = -1;
        return false;
    }

    // Hacemos el socket no bloqueante para poder establecer timeouts
    CPortability::SetBlockingSocket ( m_socket, false );

    return true;
}

void CSocket::Close ( )
{
    InternalClose ( false );
}

void CSocket::InternalClose ( bool bKeepErrors )
{
    if ( m_socket != -1 )
    {
        CPortability::SocketClose ( m_socket );
        m_socket = -1;
    }

    if ( !bKeepErrors )
    {
        m_iErrno = 0;
        m_szError = "";
    }
    m_bufferSize = 0;
}

int CSocket::ReadLine ( CString& szDest )
{
    int iSize;

    if ( !IsOk () )
        return -1;

    do
    {
        if ( m_bufferSize > 0 )
        {
            char* p = strchr ( m_buffer, '\n' );
            if ( p )
            {
                char* p2 = p;
                while ( p2 > m_buffer && ( *p2 == '\n' || *p2 == '\r' ) )
                    *p2-- = '\0';

                size_t len = static_cast < size_t > ( p2 - m_buffer + 1 );
                if ( len > 1 || ( *p2 != '\n' && *p2 != '\r' ) )
                {
                    szDest.assign ( m_buffer, len );
                }

                size_t len2 = static_cast < size_t > ( p - m_buffer );
                memcpy ( m_buffer, p + 1, m_bufferSize - len2 );
                m_bufferSize -= len2 + 1;

                return len2;
            }
        }

        // Llamamos a select para establecer un timeout
        fd_set fds;
        FD_ZERO ( &fds );
        FD_SET ( m_socket, &fds );

        struct timeval* tvTimeout = 0;
        struct timeval __tvTimeout;
        if ( m_uiTimeout > 0 )
        {
            __tvTimeout.tv_sec = m_uiTimeout / 1000;
            __tvTimeout.tv_usec = (m_uiTimeout - ( __tvTimeout.tv_sec * 1000 )) * 1000;
            tvTimeout = &__tvTimeout;
        }

        int nChanged = select ( m_socket + 1, &fds, NULL, NULL, tvTimeout );

        // Comprobamos que todo ha ido bien en el select
        if ( nChanged == -1 )
        {
            m_iErrno = errno;
            m_szError = strerror ( errno );
            InternalClose ( true );
            return -1;
        }
        else if ( nChanged == 0 )
            return 0;
        else
        {
            // Leemos datos desde el socket
            iSize = recv ( m_socket, m_buffer + m_bufferSize, BUFFER_SIZE - m_bufferSize, 0 );
            if ( iSize > 0 )
            {
                m_bufferSize += iSize;
            }
        }
    } while ( iSize > 0 );

    m_iErrno = CPortability::SocketErrno ();
    CPortability::SocketError ( m_iErrno, m_szError );
    InternalClose ( true );

    return -1;
}

int CSocket::WriteString ( const CString& szString )
{
    if ( !IsOk () )
        return -1;

    int iSize = send ( m_socket, szString, szString.length (), 0 );
    if ( iSize > 0 )
        send ( m_socket, "\r\n", sizeof(char)*2, 0 );

    if ( iSize < 1 )
    {
        m_iErrno = CPortability::SocketErrno ();
        CPortability::SocketError ( m_iErrno, m_szError );
        InternalClose ( true );
        return -1;
    }

    return iSize;
}


// Errores
bool CSocket::IsOk ( ) const
{
    return ( m_socket != -1 && !m_iErrno );
}

int CSocket::Errno ( ) const
{
    return m_iErrno;
}

const CString& CSocket::Error ( ) const
{
    return m_szError;
}



// Parte est�tica de la clase
bool CSocket::ms_bNetworkingOk = false;

bool CSocket::StartupNetworking ( )
{
    if ( ms_bNetworkingOk == true )
        return true;

#ifdef WIN32
    WORD wVersionRequested;
    WSADATA wsaData;
    int iError;

    wVersionRequested = MAKEWORD(2, 2);

    iError = WSAStartup ( wVersionRequested, &wsaData );
    if ( iError != 0 )
    {
        printf ( "WSAStartup ha fallado con el c�digo de error: %d\n", iError );
        ms_bNetworkingOk = false;
        return false;
    }

    if ( LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2 )
    {
        printf ( "No se ha encontrado una versi�n apropiada de Winsock\n" );
        WSACleanup ( );
        ms_bNetworkingOk = false;
        return false;
    }

#endif

    ms_bNetworkingOk = true;
    return true;
}

void CSocket::CleanupNetworking ( )
{
#ifdef WIN32
    if ( ms_bNetworkingOk )
    {
        WSACleanup ( );
    }
#endif
    ms_bNetworkingOk = false;
}
