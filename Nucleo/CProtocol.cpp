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
{
}

CProtocol::~CProtocol ( )
{
}


void CProtocol::Initialize ( const CSocket& socket, const CConfig& config )
{
    m_socket = socket;
    m_config = config;
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
    puts ( szLine );
    return true;
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
