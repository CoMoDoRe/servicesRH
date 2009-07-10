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
// Archivo:     CLogger.cpp
// Prop�sito:   Logs.
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#include "stdafx.h"

void CLogger::Log ( const char* szFormat, ... )
{
    va_list vl;

    CString szOutput;
    va_start ( vl, szFormat );
    szOutput.vFormat ( szFormat, vl );
    va_end ( vl );

    puts ( szOutput );
}
