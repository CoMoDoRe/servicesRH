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
// Archivo:     CUser.cpp
// Prop�sito:   Usuarios
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#include "stdafx.h"

CUser::CUser ( )
{
}

CUser::CUser ( CServer* pServer, const CString& szClient, const CString& szDesc )
    : CClient ( szClient, szDesc )
{
    m_pServer = pServer;
}

CUser::~CUser ()
{
}


void CUser::FormatNumeric ( char* szDest ) const
{
    if ( ulNumeric > 262144 )
        inttobase64 ( szDest, ulNumeric, 5 );
    else
        inttobase64 ( szDest, ulNumeric, 3 );
}
