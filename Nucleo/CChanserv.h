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
// Archivo:     CChanserv.h
// Prop�sito:   Registro de canales
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

class CChanserv : public CService
{
public:
                CChanserv   ( const CConfig& config );
    virtual     ~CChanserv  ( );
private:
};
