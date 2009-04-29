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
// Archivo:     CServer.h
// Prop�sito:   Servidores
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

class CUser;

class CServer : public CClient
{
public:
                    CServer         ( );
                    CServer         ( const CString& szClient, const CString& szDesc = "" );
                    ~CServer        ( );

    void            FormatNumeric   ( char* szDest ) const;
    inline EType    GetType         ( ) const { return CClient::SERVER; }
};