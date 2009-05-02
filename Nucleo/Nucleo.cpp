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
    // Inicializamos el hasher de cadenas
    init_hash ();

    // Cargamos la configuraci�n
    CConfig config ( "servicios.conf" );
    if ( config.IsOk () == false )
    {
        puts ( "Error cargando la configuraci�n" );
        CPortability::Pause ();
        return EXIT_FAILURE;
    }

    // Inicializamos la conexi�n
    if ( CSocket::StartupNetworking () == false )
    {
        puts ( "Error inicializando la red" );
        CPortability::Pause ();
        return EXIT_FAILURE;
    }

    // Conectamos
    CString szHost;
    CString szPort;
    config.GetValue ( szHost, "servidor", "host" );
    config.GetValue ( szPort, "servidor", "puerto" );

    CSocket socket;
    if ( socket.Connect ( szHost, atoi ( szPort ) ) == false )
    {
        printf ( "Error conectando al servidor (%d): %s\n", socket.Errno (), socket.Error ().c_str () );
        CPortability::Pause ();
        return EXIT_FAILURE;
    }

    // Inicializamos el protocolo
    CProtocol& protocol = CProtocol::GetSingleton ( );
    if ( ! protocol.Initialize ( socket, config ) )
    {
        puts ( "Error inicializando el protocolo" );
        CPortability::Pause ();
        return EXIT_FAILURE;
    }

    // Bucle
    while ( protocol.Loop () > 0 );

    // Finalizamos
    delete CProtocol::GetSingletonPtr ();
    socket.Close ();
    CSocket::CleanupNetworking ();
    CPortability::Pause ();
    return EXIT_SUCCESS;
}

