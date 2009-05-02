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
// Archivo:     CLanguageManager.h
// Prop�sito:   Gestor de idiomas
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

class CLanguageManager
{
public:
    static CLanguageManager&    GetSingleton    ( );
    static CLanguageManager*    GetSingletonPtr ( );
private:
    static CLanguageManager     ms_instance;

private:
                    CLanguageManager    ( );
public:
    virtual         ~CLanguageManager   ( );

    void            LoadLanguages   ( );
    CLanguage*      GetLanguage         ( const CString& szLangName );

private:
    typedef google::dense_hash_map < const char*, CLanguage* > t_langMap;
    t_langMap       m_langMap;
};
