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
// Archivo:     CDatabase.h
// Prop�sito:   Base de datos.
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

class CDatabase
{
public:
    static CDatabase&       GetSingleton        ( );
    static CDatabase*       GetSingletonPtr     ( );
private:
    static CDatabase        ms_instance;

public:
                            CDatabase           ( );
                            CDatabase           ( const CString& szHost,
                                                  unsigned short usPort = 3306,
                                                  const CString& szUser = "",
                                                  const CString& szPass = "",
                                                  const CString& szDb = "" );
    virtual                 ~CDatabase          ( );

    bool                    Connect             ( const CString& szHost,
                                                  unsigned short usPort = 3306,
                                                  const CString& szUser = "",
                                                  const CString& szPass = "",
                                                  const CString& szDb = "" );
    void                    Close               ( );

    inline bool             IsOk                ( ) const { return m_bIsOk; }
    inline int              Errno               ( ) const { return m_iErrno; }
    inline const CString&   Error               ( ) const { return m_szError; }

    CDBStatement*           PrepareStatement    ( const CString& szStatement );

private:
    bool        m_bIsOk;
    MYSQL       m_handler;
    int         m_iErrno;
    CString     m_szError;

    std::vector < CDBStatement* >
                m_vecStatements;
};
