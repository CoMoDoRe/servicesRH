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
// Archivo:     CNickserv.cpp
// Prop�sito:   Registro de nicks.
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#include "stdafx.h"

CNickserv::CNickserv ( const CConfig& config )
: CService ( "nickserv", config )
{
    RegisterCommand ( "help", COMMAND_CALLBACK ( &CNickserv::cmdHelp, this ) );
}

CNickserv::~CNickserv ( )
{
}

// Comandos
void CNickserv::UnknownCommand ( SCommandInfo& info )
{
    info.ResetParamCounter ();
    LangMsg ( info.pSource, "UNKNOWN_COMMAND", info.GetNextParam ().c_str () );
}

bool CNickserv::cmdHelp ( SCommandInfo& info )
{
    LangMsg ( info.pSource, "HELP" );

    return true;
}
