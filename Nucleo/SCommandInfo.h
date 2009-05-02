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
// Archivo:     SCommandInfo.h
// Prop�sito:   Informaci�n acerca de un comando enviado a un servicio
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//


#pragma once

struct SCommandInfo
{
    CUser*                  pSource;
    std::vector < CString > vecParams;
private:
    CString                 szEmptyParam;
    unsigned int            uiCurParam;
public:

    inline SCommandInfo ( )
    {
        uiCurParam = 0;
        szEmptyParam = "";
    }

    inline CString& GetNextParam ( )
    {
        while ( uiCurParam < vecParams.size () && vecParams [ uiCurParam ].length () == 0 )
            ++uiCurParam;

        if ( uiCurParam >= vecParams.size () )
            return szEmptyParam;

        ++uiCurParam;
        return vecParams [ uiCurParam - 1 ];
    }

    inline CString& GetRemainingText ( CString& szDest )
    {
        CString& szCur = GetNextParam ();
        if ( szCur.length () == 0 )
        {
            szDest = "";
        }
        else
        {
            szDest = szCur;
            while ( uiCurParam < vecParams.size () )
            {
                szDest.append ( " " );
                szDest.append ( vecParams [ uiCurParam ] );
                ++uiCurParam;
            }
        }

        return szDest;
    }
};
