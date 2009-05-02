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
// Archivo:     CDirectory_win32.h
// Prop�sito:   Clase que permite abrir e iterar directorios, para Win32.
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#include "stdafx.h"

/* Funciones para navegar por directorios */
CString CDirectory::GetCurrentDirectory ( )
{
    CString szRet;
    char szCurDirectory [ 2048 ];
    ::GetCurrentDirectory ( sizeof ( szCurDirectory ), szCurDirectory );
    szRet.assign ( szCurDirectory );
    return szRet;
}

void CDirectory::SetCurrentDirectory ( const CString& szDirectoryPath )
{
    ::SetCurrentDirectory ( szDirectoryPath.c_str ( ) );
}

/* Clase CDirectory */
CDirectory::CDirectory ( )
    : m_pHandle ( INVALID_HANDLE_VALUE )
{
}

CDirectory::CDirectory ( const CString& szPath )
{
    Open ( szPath );
}

CDirectory::~CDirectory ( )
{
    Close ( );
}

void CDirectory::Close ( )
{
    if ( m_pHandle != INVALID_HANDLE_VALUE )
        FindClose ( m_pHandle );
}

bool CDirectory::Open ( const CString& szPath )
{
    /* Por seguridad ... */
    Close ( );

    m_pHandle = FindFirstFile ( CString( szPath + "\\*" ).c_str(), &m_ffd );

    if ( m_pHandle == INVALID_HANDLE_VALUE )
    {
        return false;
    }

    return true;
}

bool CDirectory::IsOk ( ) const
{
    return ( m_pHandle != INVALID_HANDLE_VALUE );
}

CDirectory::CIterator CDirectory::Begin ( )
{
    return CDirectory::CIterator ( this );
}

CDirectory::CIterator CDirectory::End ( )
{
    return CDirectory::CIterator ( 0 );
}

/* Iteradores */
CString CDirectory::CIterator::GetName ( ) const
{
    return CString ( std::string ( m_ffd.cFileName ) );
}

const CDirectory::EntryType CDirectory::CIterator::GetType ( ) const
{
    if ( m_ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
    {
        return ENTRY_DIRECTORY;
    }
    else
    {
        return ENTRY_FILE;
    }
}
