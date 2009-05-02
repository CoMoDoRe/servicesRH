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

bool CNickserv::cmdHelp ( SCommandInfo& info )
{
    Msg ( info.pSource, "�A�n no hay ayuda disponible! :(" );

    return true;
}
