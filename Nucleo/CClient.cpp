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
// Archivo:     CClient.cpp
// Prop�sito:   Contenedor de clientes.
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#include "stdafx.h"

void CClient::Send ( const IMessage& message )
{
    CProtocol::GetSingleton ().Send ( message, this );
}
