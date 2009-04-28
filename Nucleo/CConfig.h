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
private:
    struct SIniEntry
    {
        CString szName;
        CString szValue;
        SIniEntry* pNext;
    };
  
    struct SIniSection
    {
        CString szName;
        SIniEntry* pEntries;
        SIniSection* pNext;
    };

public:
                    CConfig         ( );
                    CConfig         ( const CConfig& copy );
                    CConfig         ( const CString& szFilename );
    virtual         ~CConfig        ( );

    CConfig&        operator=       ( const CConfig& copy );

    bool            SetFilename     ( const CString& szFilename );
    bool            GetValue        ( CString& szDest, const CString& szSection, const CString& szEntry );

    bool            IsOk            ( ) const;
    int             Errno           ( ) const;
    const CString&  Error           ( ) const;

private:
    void            Reset           ( );

private:
    int             m_iErrno;
    CString         m_szError;
    SIniSection*    m_pSections;
};