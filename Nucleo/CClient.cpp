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
    // Almacenamos la fecha del �ltimo comando
    m_lastCommandSent.Create ();

    CProtocol::GetSingleton ().Send ( message, this );
}

unsigned long CClient::GetIdleTime ( ) const
{
    CDate now;
    now -= m_lastCommandSent;

    return static_cast < unsigned long > ( now.GetTimestamp () );
}
