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
// Archivo:     CClient.h
// Prop�sito:   Contenedor de clientes.
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

class CClient
{
public:
    enum EType
    {
        SERVER,
        USER,
        UNKNOWN
    };

public:
    inline                  CClient         ( ) {}
    inline                  CClient         ( const CString& szClient, const CString& _szDesc = "" )
    {
        int iIdent = szClient.find ( '!' );
        if ( iIdent == CString::npos )
        {
            szName = szClient;
        }
        else
        {
            szName = szClient.substr ( 0, iIdent - 1 );
            int iHost = szClient.find ( '@', iIdent + 1 );
            if ( iHost != CString::npos )
            {
                szIdent = szClient.substr ( iIdent + 1, iHost - 1 );
                szHost = szClient.substr ( iHost + 1 );
            }
        }

        szDesc = _szDesc;
    }
    virtual                 ~CClient        ( ) { }

    virtual inline void     FormatNumeric   ( char* szDest ) const { *szDest = '\0'; }
    virtual inline EType    GetType         ( ) const { return UNKNOWN; }

public:
    unsigned long   ulNumeric;
    CString         szName;
    CString         szIdent;
    CString         szHost;
    CString         szDesc;
};
