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
// Archivo:     CChannelManager.h
// Prop�sito:   Gestor de canales
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

class CChannelManager
{
public:
    static CChannelManager&     GetSingleton    ( );
    static CChannelManager*     GetSingletonPtr ( );
private:
    static CChannelManager      ms_instance;

private:
                            CChannelManager     ( );
public:
    virtual                 ~CChannelManager    ( );

    void                    AddChannel          ( CChannel* pChannel );
    void                    RemoveChannel       ( CChannel* pChannel );

    CChannel*               GetChannel          ( const CString& szName );

private:
    typedef google::dense_hash_map < const char*, CChannel*, SStringHasher, SStringEquals > t_mapChannels;

    t_mapChannels           m_mapChannels;
};
