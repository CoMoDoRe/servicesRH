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
// Archivo:     CMemoserv.h
// Prop�sito:   Mensajer�a entre usuarios
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

class CMemoserv : public CService
{
public:
                CMemoserv   ( const CConfig& config );
    virtual     ~CMemoserv  ( );
private:
};