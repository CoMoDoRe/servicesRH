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

CUser::CUser ( CServer* pServer, unsigned long ulNumeric, const CString& szName, const CString& szDesc )
{
    Create ( pServer, ulNumeric, szName, szDesc );
}

CUser::~CUser ()
{
}

void CUser::Create ( CServer* pServer, unsigned long ulNumeric, const CString& szName, const CString& szDesc )
{
    CClient::Create ( pServer, ulNumeric, szName, szDesc );
}

void CUser::FormatNumeric ( char* szDest ) const
{
    const CClient* pParent = CClient::GetParent ();

    if ( pParent )
    {
        unsigned long ulServerNumeric = pParent->GetNumeric ();
        if ( ulServerNumeric > 63 )
        {
            unsigned long ulNumeric = ( ulServerNumeric << 18 ) | CClient::GetNumeric ();
            inttobase64 ( szDest, ulNumeric, 5 );
        }
        else
        {
            unsigned long ulNumeric = ( ulServerNumeric << 12 ) | CClient::GetNumeric ();
            inttobase64 ( szDest, ulNumeric, 3 );
        }

    }
    else
        *szDest = '\0';
}
