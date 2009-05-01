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
// Archivo:     CMembership.h
// Prop�sito:   Membres�as de usuarios en canales
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

class CUser;
class CChannel;

class CMembership
{
public:
                            CMembership     ( );
                            CMembership     ( CChannel* pChannel, CUser* pUser, unsigned long ulFlags = 0UL );
    virtual                 ~CMembership    ( );

    inline CChannel*        GetChannel      ( ) const { return m_pChannel; }
    inline CUser*           GetUser         ( ) const { return m_pUser; }
    inline unsigned long    GetFlags        ( ) const { return m_ulFlags; }

    inline void             SetChannel      ( CChannel* pChannel ) { m_pChannel = pChannel; }
    inline void             SetUser         ( CUser* pUser ) { m_pUser = pUser; }
    inline void             SetFlags        ( unsigned long ulFlags ) { m_ulFlags = ulFlags; }

private:
    CChannel*       m_pChannel;
    CUser*          m_pUser;
    unsigned long   m_ulFlags;
};
