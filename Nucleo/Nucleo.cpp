/////////////////////////////////////////////////////////////
//
// Servicios de redhispana.org
// Está prohibida la reproducción y el uso parcial o total
// del código fuente de estos servicios sin previa
// autorización escrita del autor de estos servicios.
//
// Si usted viola esta licencia se emprenderán acciones legales.
//
// (C) RedHispana.Org 2009
//
// Archivo:     Nucleo.cpp
// Propósito:   Núcleo del programa. Inicialización y bucle.
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#include "stdafx.h"

int main( int argc, const char* argv[], const char* envp[] )
{
    // Inicializamos el hasher de cadenas
    init_hash ();

    // Cargamos la configuración
    CConfig config ( "services.conf" );
    if ( config.IsOk () == false )
    {
        puts ( "Error cargando la configuración" );
        CPortability::Pause ();
        return EXIT_FAILURE;
    }

    // Inicializamos la conexión a la base de datos
    CString szHost;
    CString szPort;
    CString szUser;
    CString szPass;
    CString szDB;
    if ( ! config.GetValue ( szHost, "database", "host" ) ||
         ! config.GetValue ( szPort, "database", "port" ) ||
         ! config.GetValue ( szUser, "database", "username" ) ||
         ! config.GetValue ( szPass, "database", "password" ) ||
         ! config.GetValue ( szDB,   "database", "db" ) )
    {
        puts ( "Error cargando la configuración de la base de datos" );
        CPortability::Pause ();
        return EXIT_FAILURE;
    }
    CDatabase& database = CDatabase::GetSingleton ( );
    if ( ! database.Connect ( szHost, atoi ( szPort ), szUser, szPass, szDB ) )
    {
        printf ( "Error conectando a la base de datos (%d): %s\n", database.Errno (), database.Error ().c_str () );
        CPortability::Pause ();
        return EXIT_FAILURE;
    }

    // Inicializamos la conexión
    if ( CSocket::StartupNetworking () == false )
    {
        puts ( "Error inicializando la red" );
        CPortability::Pause ();
        return EXIT_FAILURE;
    }

    // Conectamos
    if ( ! config.GetValue ( szHost, "server", "host" ) ||
         ! config.GetValue ( szPort, "server", "port" ) )
    {
        puts ( "Error cargando la información de conexión al servidor de IRC" );
        CPortability::Pause ();
        return EXIT_FAILURE;
    }

    CSocket socket;
    if ( socket.Connect ( szHost, atoi ( szPort ) ) == false )
    {
        printf ( "Error conectando al servidor (%d): %s\n", socket.Errno (), socket.Error ().c_str () );
        CPortability::Pause ();
        return EXIT_FAILURE;
    }

    // Inicializamos los idiomas
    CString szDefaultLang;
    if ( !config.GetValue ( szDefaultLang, "bots", "language" ) )
    {
        puts ( "Error al leer el idioma por defecto de la configuración" );
        CPortability::Pause ();
        return EXIT_FAILURE;
    }
    if ( ! CLanguageManager::GetSingleton ().LoadLanguages ( szDefaultLang ) )
    {
        puts ( "Error cargando los idiomas" );
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
    int iRet;
    CTimerManager& timerManager = CTimerManager::GetSingleton ();

    do
    {
        // Establecemos el timeout para los timers
        unsigned int uiTimeout;
        if ( timerManager.GetCount () > 0 )
            uiTimeout = timerManager.GetTimeForNextExec ();
        else
            uiTimeout = 0;
        protocol.GetSocket ().SetTimeout ( uiTimeout );

        // Procesamos el socket
        iRet = protocol.Loop ();

        // Ejecutamos los timers
        timerManager.Execute ();
    }
    while ( iRet >= 0 );



    // Finalizamos
    delete CProtocol::GetSingletonPtr ();
    socket.Close ();
    CSocket::CleanupNetworking ();
    CPortability::Pause ();
    return EXIT_SUCCESS;
}

