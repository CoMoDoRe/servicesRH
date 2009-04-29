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

class CServer;

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
    inline                  CClient         ( CServer* pParent,
                                              unsigned long ulNumeric,
                                              const CString& szName,
                                              const CString& szDesc = "" )
    {
        Create ( pParent, ulNumeric, szName, szDesc );
    }
    virtual                 ~CClient        ( ) { }

    inline void             Create          ( CServer* pParent,
                                              unsigned long ulNumeric,
                                              const CString& szName,
                                              const CString& szDesc = "" )
    {
        m_pParent = pParent;
        m_ulNumeric = ulNumeric;
        m_szName = szName;
        m_szDesc = szDesc;
    }

    virtual inline void     FormatNumeric   ( char* szDest ) const { *szDest = '\0'; }
    virtual inline EType    GetType         ( ) const { return UNKNOWN; }

    inline CServer*         GetParent       ( ) { return m_pParent; }
    inline const CServer*   GetParent       ( ) const { return m_pParent; }
    inline const CString&   GetName         ( ) const { return m_szName; }
    inline const CString&   GetDesc         ( ) const { return m_szDesc; }
    inline unsigned long    GetNumeric      ( ) const { return m_ulNumeric; }

private:
    CServer*        m_pParent;
    unsigned long   m_ulNumeric;
    CString         m_szName;
    CString         m_szDesc;
};
