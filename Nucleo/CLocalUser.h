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
// Archivo:     CLocalUser.h
// Prop�sito:   Wrapper para usuarios locales
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

class CLocalUser : public CUser
{
public:
    inline                  CLocalUser          ( ) : CUser ( ), m_bCreated ( false ) { }
    inline                  CLocalUser          ( unsigned long ulNumeric,
                                                  const CString& szName,
                                                  const CString& szIdent,
                                                  const CString& szDesc,
                                                  const CString& szHost,
                                                  unsigned long ulAddress,
                                                  const CString& szModes )
                                                  : m_bCreated ( false )
    {
        Create ( ulNumeric, szName, szIdent, szDesc, szHost, ulAddress, szModes );
    }

    virtual                 ~CLocalUser         ( ) { }

    void                    Create              ( unsigned long ulNumeric,
                                                  const CString& szName,
                                                  const CString& szIdent,
                                                  const CString& szDesc,
                                                  const CString& szHost,
                                                  unsigned long ulAddress,
                                                  const CString& szModes );

    void                    Join                ( const CString& szChannel );
    void                    Join                ( CChannel* pChannel );
    void                    Part                ( const CString& szChannel, const CString& szMessage = "" );
    void                    Part                ( CChannel* pChannel, const CString& szMessage = "" );
    void                    Quit                ( const CString& szQuitMessage = "" );

private:
    bool            m_bCreated;
};
