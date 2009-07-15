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
// Archivo:     CMembership.cpp
// Prop�sito:   Membres�as de usuarios en canales
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#include "stdafx.h"


CMembership::CMembership ( )
: m_pChannel ( 0 ), m_pUser ( 0 ), m_ulFlags ( 0 )
{
}

CMembership::CMembership ( CChannel* pChannel, CUser* pUser, unsigned long ulFlags )
: m_pChannel ( pChannel ), m_pUser ( pUser ), m_ulFlags ( ulFlags )
{
}

CMembership::~CMembership ( ) { }


bool CMembership::IsOwner ( ) const
{
    return !!(m_ulFlags & CChannel::CFLAG_OWNER);
}
bool CMembership::IsOp ( ) const
{
    return !!(m_ulFlags & CChannel::CFLAG_OP);
}
bool CMembership::IsHalfop ( ) const
{
    return !!(m_ulFlags & CChannel::CFLAG_HALFOP);
}
bool CMembership::IsVoice ( ) const
{
    return !!(m_ulFlags & CChannel::CFLAG_VOICE);
}

CString CMembership::GetFlagsString ( ) const
{
    CString szFlags = "";
    if ( IsVoice () )
        szFlags.append ( "+" );
    if ( IsHalfop () )
        szFlags.append ( "%" );
    if ( IsOp () )
        szFlags.append ( "@" );
    if ( IsOwner () )
        szFlags.append ( "." );
    return szFlags;
}
