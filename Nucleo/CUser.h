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
// Archivo:     CUser.h
// Prop�sito:   Usuarios
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

class CServer;

class CUser : public CClient
{
public:
                    CUser           ( );
                    CUser           ( CServer* pServer,
                                      unsigned long ulNumeric,
                                      const CString& szName,
                                      const CString& szDesc = "" );
    virtual         ~CUser          ( );

    void            Create          ( CServer* pServer,
                                      unsigned long ulNumeric,
                                      const CString& szName,
                                      const CString& szDesc = "" );

    void            FormatNumeric   ( char* szDest ) const;
    inline EType    GetType         ( ) const { return CClient::USER; }
};
