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
// Archivo:     Nucleo.cpp
// Prop�sito:   N�cleo del programa. Inicializaci�n y bucle.
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#include "stdafx.h"

int main( int argc, const char* argv[], const char* envp[] )
{
    CConfig config ( "servicios.conf" );
    if ( config.IsOk () == false )
    {
        puts ( "Error cargando la configuraci�n" );
        Pause ();
        return EXIT_FAILURE;
    }

    Pause ();
    return EXIT_SUCCESS;
}

