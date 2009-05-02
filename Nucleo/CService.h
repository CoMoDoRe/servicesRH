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
// Archivo:     CService.h
// Prop�sito:   Clase base para los servicios.
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

class CService : public CUser
{
public:
    static void     RegisterServices        ( const CConfig& config );
private:
    static std::vector < unsigned long >      ms_ulFreeNumerics;
    static std::list < CService* >            ms_listServices;

public:
                    CService    ( const CString& szServiceName, const CConfig& config );
    virtual         ~CService   ( );

    bool            IsOk        ( ) const { return m_bIsOk; }
    const CString&  GetError    ( ) const { return m_szError; }

private:
    bool            m_bIsOk;
    CString         m_szError;
};
