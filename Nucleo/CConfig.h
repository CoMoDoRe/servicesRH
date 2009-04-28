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
// Archivo:     CConfig.h
// Prop�sito:   Configuraci�n.
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

class CConfig
{
public:
                CConfig ( );
                CConfig ( const CConfig& copy );
                CConfig ( const CString& szFilename );
    virtual     ~CConfig ( );
};