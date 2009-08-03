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
// Archivo:     CServer.cpp
// Prop�sito:   Servidores
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#include "stdafx.h"

CServer::CServer ( )
{
}

CServer::CServer ( CServer* pParent,
                   const CString& szYXX,
                   const CString& szName,
                   const CString& szDesc,
                   const CString& szFlags )
{
    Create ( pParent, szYXX, szName, szDesc, szFlags );
}

CServer::~CServer ( )
{
    Destroy ();
}

void CServer::Destroy ( )
{
    CClient* pParent_ = CClient::GetParent ();
    if ( pParent_ )
    {
        // Es un servidor de la red, no yo
        CServer& me = CProtocol::GetSingleton ().GetMe ();
        me.m_clientManager.RemoveClient ( this );

        // Deslinkamos este servidor del padre
        CServer* pParent = static_cast < CServer* > ( pParent_ );
        pParent->m_children.remove ( this );
    }

    // Destru�mos todos los servidores hijos linkados a este servidor
    CProtocol& protocol = CProtocol::GetSingleton ();
    for ( std::list < CServer* >::iterator i = m_children.begin ();
          i != m_children.end ();
          i = m_children.begin () )
    {
        CServer* pCur = *i;
        pCur->Destroy ();
        protocol.DelayedDelete ( pCur );
    }
    m_children.clear ();

    m_clientManager.Destroy ();
    CClient::Destroy ();
}

void CServer::Create ( CServer* pParent,
                       const CString& szYXX,
                       const CString& szName,
                       const CString& szDesc,
                       const CString& szFlags )
{
    CClient::Create ( pParent, szYXX, szName, szDesc );

    if ( pParent )
    {
        CProtocol::GetSingleton ().GetMe ().m_clientManager.AddClient ( this );
        pParent->m_children.push_back ( this );
    }

    // Procesamos los flags
    const char* pszFlags = szFlags.c_str ();
    unsigned int i = 0;
    m_ulFlags = 0;
    if ( *pszFlags == '+' )
        ++i;
    for ( ; i < szFlags.length (); ++i )
    {
        switch ( pszFlags [ i ] )
        {
            case 'h':
                m_ulFlags |= SERVER_HUB;
                break;
            case 's':
                m_ulFlags |= SERVER_SERVICE;
                break;
            case 'x':
                m_ulFlags |= SERVER_HIDDEN;
                break;
        }
    }
}

void CServer::FormatNumeric ( char* szDest ) const
{
    strcpy ( szDest, CClient::GetYXX () );
}


CServer* CServer::GetServer ( const CString& szName )
{
    if ( !CompareStrings ( szName.c_str (), CClient::GetName ().c_str () ) )
        return this;
    return m_clientManager.GetServer ( szName );
}

CServer* CServer::GetServer ( unsigned long ulNumeric )
{
    if ( ulNumeric == CClient::GetNumeric () )
        return this;
    return m_clientManager.GetServer ( ulNumeric );
}

CUser* CServer::GetUser ( unsigned long ulNumeric )
{
    return m_clientManager.GetUser ( ulNumeric );
}

CUser* CServer::GetUser ( const CString& szName )
{
    return m_clientManager.GetUser ( szName );
}

CUser* CServer::GetUserAnywhere ( const CString& szName )
{
    CUser* pUser = m_clientManager.GetUser ( szName );
    if ( ! pUser )
    {
        for ( std::list < CServer* >::iterator iter = m_children.begin ();
              iter != m_children.end ();
              ++iter )
        {
            pUser = (*iter)->GetUserAnywhere ( szName );
            if ( pUser )
                break;
        }
    }

    return pUser;
}

CUser* CServer::GetUserAnywhere ( unsigned long ulNumeric )
{
    unsigned long ulServerNumeric;
    unsigned long ulUserNumeric;

    if ( ulNumeric > 262143 )
    {
        // Num�rico largo
        ulServerNumeric = ulNumeric >> 18;
        ulUserNumeric = ulNumeric & 262143;
    }
    else
    {
        // Num�rico corto
        ulServerNumeric = ulNumeric >> 12;
        ulUserNumeric = ulNumeric & 4095;
    }

    CServer* pServer;
    if ( ulServerNumeric == GetNumeric () )
        pServer = this;
    else
    {
        pServer = GetServer ( ulServerNumeric );
        if ( !pServer )
            return NULL;
    }

    return pServer->GetUser ( ulUserNumeric );
}

void CServer::AddUser ( CUser* pUser )
{
    m_clientManager.AddClient ( pUser );
}

void CServer::RemoveUser ( CUser* pUser )
{
    m_clientManager.RemoveClient ( pUser );
}

void CServer::UpdateUserName ( CUser* pUser, const CString& szName )
{
    m_clientManager.UpdateClientName ( pUser, szName );
}

bool CServer::IsConnectedTo ( const CServer* pServer ) const
{
    for ( std::list < CServer* >::const_iterator iter = m_children.begin ();
          iter != m_children.end ();
          ++iter )
    {
        if ( *iter == pServer )
            return true;
    }
    return false;
}

unsigned long CServer::GetNumUsers ( bool bGoInDepth ) const
{
    unsigned long ulUsers = m_clientManager.GetNumUsers ();

    if ( bGoInDepth )
    {
        for ( std::list < CServer* >::const_iterator i = m_children.begin ();
              i != m_children.end ();
              ++i )
        {
            ulUsers += (*i)->GetNumUsers ( true );
        }
    }

    return ulUsers;
}

unsigned long CServer::GetNumServers ( bool bGoInDepth ) const
{
    unsigned long ulNumServers = m_children.size ();

    if ( bGoInDepth )
    {
        for ( std::list < CServer* >::const_iterator i = m_children.begin ();
              i != m_children.end ();
              ++i )
        {
            ulNumServers += (*i)->GetNumServers ( true );
        }
    }

    if ( !GetParent () )
        ulNumServers++;

    return ulNumServers;
}

bool CServer::ForEachUser ( const FOREACH_USER_CALLBACK& cbk, void* userdata, bool bGoInDepth ) const
{
    if ( m_clientManager.ForEachUser ( cbk, userdata ) )
    {
        if ( bGoInDepth )
        {
            for ( std::list < CServer* >::const_iterator i = m_children.begin ();
                  i != m_children.end ();
                  ++i )
            {
                if ( !(*i)->ForEachUser ( cbk, userdata, true ) )
                    return false;
            }
        }
        return true;
    }
    else
        return false;
}

bool CServer::ForEachServer ( const FOREACH_SERVER_CALLBACK& cbk, void* userdata, bool bGoInDepth ) const
{
    SForeachInfo < CServer* > info;
    info.userdata = userdata;
    info.cur = const_cast < CServer* > ( this );

    if ( cbk ( info ) )
    {
        if ( bGoInDepth )
        {
            for ( std::list < CServer* >::const_iterator i = m_children.begin ();
                  i != m_children.end ();
                  ++i )
            {
                if ( !(*i)->ForEachServer ( cbk, userdata, true ) )
                    return false;
            }
        }
        return true;
    }
    else
        return false;
}
