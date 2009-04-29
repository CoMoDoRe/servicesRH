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

CServer::CServer ( const CString& szClient, const CString& szDesc )
    : CClient ( szClient, szDesc )
{
}

CServer::~CServer ( )
{
}


void CServer::FormatNumeric ( char* szDest ) const
{
    if ( ulNumeric > 63 )
        inttobase64 ( szDest, ulNumeric, 2 );
    else
        inttobase64 ( szDest, ulNumeric, 1 );
}