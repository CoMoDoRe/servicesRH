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
// Archivo:     CServer.h
// Prop�sito:   Servidores
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

class CUser;

class CServer : public CClient
{
public:
    enum EServerFlags
    {
        SERVER_HIDDEN   = 0x00001,
        SERVER_HUB      = 0x00002,
        SERVER_SERVICE  = 0x00004
    };

public:
                            CServer         ( );
                            CServer         ( CServer* pParent,
                                              const CString& szYXX,
                                              const CString& szName,
                                              const CString& szDesc = "",
                                              const CString& szFlags = "+" );
    virtual                 ~CServer        ( );
    void                    Destroy         ( );

    void                    Create          ( CServer* pParent,
                                              const CString& szYXX,
                                              const CString& szName,
                                              const CString& szDesc = "",
                                              const CString& szFlags = "+" );

    void                    FormatNumeric   ( char* szDest ) const;
    inline EType            GetType         ( ) const { return CClient::SERVER; }

    unsigned long           GetFlags        ( ) const { return m_ulFlags; }

    CServer*                GetServer       ( const CString& szName );
    CServer*                GetServer       ( unsigned long ulNumeric );
    CUser*                  GetUser         ( const CString& szName );
    CUser*                  GetUser         ( unsigned long ulNumeric );
    CUser*                  GetUserAnywhere ( const CString& szName );
    CUser*                  GetUserAnywhere ( unsigned long ulNumeric );

    void                    AddUser         ( CUser* pUser );
    void                    RemoveUser      ( CUser* pUser );
    void                    UpdateUserName  ( CUser* pUser, const CString& szName );

    bool                    IsConnectedTo   ( const CServer* pServer ) const;

    unsigned long           GetNumUsers     ( bool bGoInDepth = true ) const;
    unsigned long           GetNumServers   ( bool bGoInDepth = true ) const;

    bool                    ForEachUser     ( const FOREACH_USER_CALLBACK& cbk, void* userdata, bool bGoInDepth = true ) const;
    bool                    ForEachServer   ( const FOREACH_SERVER_CALLBACK& cbk, void* userdata, bool bGoInDepth = false ) const;

private:
    CClientManager          m_clientManager;
    std::list < CServer* >  m_children;
    unsigned long           m_ulFlags;
};