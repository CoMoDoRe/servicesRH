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
// Archivo:     CDBStatement.h
// Prop�sito:   Estamentos precompilados de la base de datos.
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

class CDBStatement
{
    friend class CDatabase;

public:
    enum
    {
        FETCH_OK,
        FETCH_ERROR,
        FETCH_NO_DATA,
        FETCH_DATA_TRUNCATED,
        FETCH_UNKNOWN
    };

private:
                            CDBStatement    ( MYSQL* pHandle );
    virtual                 ~CDBStatement   ( );

    bool                    Prepare         ( const CString& szQuery );

public:
    bool                    Execute         ( const char* szParamTypes = "", ... );
    int                     Fetch           ( unsigned long* ulLengths, bool* bNulls, const char* szParamTypes, ... );
    bool                    FreeResult      ( );

    unsigned long long      InsertID        ( );

    inline bool             IsOk            ( ) const { return m_pStatement != NULL && Errno () == 0; }
    inline int              Errno           ( ) const { return m_iErrno; }
    inline const CString&   Error           ( ) const { return m_szError; }

private:
    MYSQL_STMT*             m_pStatement;
    MYSQL*                  m_pHandler;

    int                     m_iErrno;
    CString                 m_szError;
};
