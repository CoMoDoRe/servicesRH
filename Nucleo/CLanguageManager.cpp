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
// Archivo:     CLanguageManager.cpp
// Prop�sito:   Gestor de idiomas
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#include "stdafx.h"

// Parte est�tica
CLanguageManager CLanguageManager::ms_instance;

CLanguageManager& CLanguageManager::GetSingleton ( )
{
    return ms_instance;
}

CLanguageManager* CLanguageManager::GetSingletonPtr ( )
{
    return &GetSingleton ();
}


// Parte no est�tica
CLanguageManager::CLanguageManager ( )
{
}

CLanguageManager::~CLanguageManager ( )
{
}

void CLanguageManager::LoadLanguages ( )
{
    CDirectory dir ( "../lang/" );

    for ( CDirectory::CIterator iter = dir.Begin ();
          iter != dir.End ();
          ++iter )
    {
        if ( iter.GetType () == CDirectory::ENTRY_DIRECTORY )
        {
            CString szDir = iter.GetName ();
            if ( szDir.at ( 0 ) != '.' )
            {
                CLanguage* pLanguage = new CLanguage ( szDir );
            }
        }
    }
}
