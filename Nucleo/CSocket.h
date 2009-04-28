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
// Archivo:     CSocket.h
// Prop�sito:   Socket TCP
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

class CSocket
{
public:
    enum
    {
        BUFFER_SIZE = 65536
    };

public:
    static bool     StartupNetworking   ( );
    static void     CleanupNetworking   ( );
private:
    static bool     m_bNetworkingOk;

public:
                    CSocket             ( );
                    CSocket             ( const CSocket& copy );
                    CSocket             ( const CString& szHost, unsigned short usPort );
    virtual         ~CSocket            ( );

    bool            Connect             ( const CString& szHost, unsigned short usPort );
    void            Close               ( );

    int             ReadLine            ( CString& szDest );
    int             WriteString         ( const CString& szString );

    bool            IsOk                ( ) const;
    int             Errno               ( ) const;
    const CString&  Error               ( ) const;

private:
    void            InternalClose       ( bool bKeepErrors );

    sock_t          m_socket;
    char            m_buffer [ BUFFER_SIZE ];
    size_t          m_bufferSize;
    int             m_iErrno;
    CString         m_szError;
};
