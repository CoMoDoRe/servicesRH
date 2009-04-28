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
// Archivo:     CClientManager.cpp
// Prop�sito:   Gestor de clientes.
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#include "stdafx.h"

// Parte no est�tica
CClientManager::CClientManager ( )
{
    m_mapClientsByName.set_deleted_key ( (const char *)0xDEADBEEF );
    m_mapClientsByNumeric.set_deleted_key ( 0xDEADBEEF );
    m_mapClientsByName.set_empty_key ( (const char *)NULL );
    m_mapClientsByNumeric.set_empty_key ( 0xDEADBEFF );
}

CClientManager::~CClientManager ( )
{
}

void CClientManager::AddClient ( CClient* client )
{
    m_mapClientsByName.insert ( t_mapClientsByName::value_type ( client->szName.c_str (), client ) );
    m_mapClientsByNumeric.insert ( t_mapClientsByNumeric::value_type ( client->ulNumeric, client ) );
}

void CClientManager::RemoveClient ( CClient* client )
{
    t_mapClientsByName::iterator iter1 = m_mapClientsByName.find ( client->szName.c_str () );
    if ( iter1 != m_mapClientsByName.end () )
    {
        m_mapClientsByName.erase ( iter1 );
    }

    t_mapClientsByNumeric::iterator iter2 = m_mapClientsByNumeric.find ( client->ulNumeric );
    if ( iter2 != m_mapClientsByNumeric.end () )
    {
        m_mapClientsByNumeric.erase ( iter2 );
    }
}

CClient* CClientManager::GetClient ( const CString& szName )
{
    t_mapClientsByName::iterator iter = m_mapClientsByName.find ( szName.c_str () );
    if ( iter != m_mapClientsByName.end () )
    {
        return (*iter).second;
    }

    return NULL;
}

CClient* CClientManager::GetClient ( unsigned long ulNumeric )
{
    t_mapClientsByNumeric::iterator iter = m_mapClientsByNumeric.find ( ulNumeric );
    if ( iter != m_mapClientsByNumeric.end () )
    {
        return (*iter).second;
    }

    return NULL;
}



// Parte est�tica
CClientManager CClientManager::ms_instance;

CClientManager& CClientManager::GetSingleton ( )
{
    return ms_instance;
}

CClientManager* CClientManager::GetSingletonPtr ( )
{
    return &GetSingleton ();
}
