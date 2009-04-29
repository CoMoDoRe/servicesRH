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
// Archivo:     CClientManager.h
// Prop�sito:   Gestor de clientes.
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

class CUser;
class CServer;

class CClientManager
{
public:
                                CClientManager      ( );
    virtual                     ~CClientManager     ( );

    void                        AddClient           ( CServer* pServer );
    void                        AddClient           ( CUser* pUser );
    void                        RemoveClient        ( CServer* pServer );
    void                        RemoveClient        ( CUser* pUser );

    CServer*                    GetServer           ( unsigned long ulNumeric );
    CServer*                    GetServer           ( const CString& szName );

    CUser*                      GetUser             ( unsigned long ulNumeric );
    CUser*                      GetUser             ( const CString& szName );

private:
    typedef google::dense_hash_map < const char*, CServer*, SStringHasher > t_mapServersByName;
    typedef google::dense_hash_map < unsigned long, CServer* > t_mapServersByNumeric;
    typedef google::dense_hash_map < const char*, CUser*, SStringHasher > t_mapUsersByName;
    typedef google::dense_hash_map < unsigned long, CUser* > t_mapUsersByNumeric;

    t_mapServersByName          m_mapServersByName;
    t_mapServersByNumeric       m_mapServersByNumeric;
    t_mapUsersByName            m_mapUsersByName;
    t_mapUsersByNumeric         m_mapUsersByNumeric;
};
