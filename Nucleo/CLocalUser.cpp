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
// Archivo:     CLocalUser.cpp
// Prop�sito:   Wrapper para usuarios locales
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#include "stdafx.h"

void CLocalUser::Create ( unsigned long ulNumeric,
                          const CString& szName,
                          const CString& szIdent,
                          const CString& szDesc,
                          const CString& szHost,
                          unsigned long ulAddress,
                          const CString& szModes )
{
    CProtocol& protocol = CProtocol::GetSingleton ();
    CServer& me = protocol.GetMe ();
    CUser::Create ( &me, ulNumeric, szName, szIdent, szDesc, szHost, ulAddress );
    me.AddUser ( this );

    protocol.Send ( CMessageNICK ( GetName (),
                                   time ( 0 ),
                                   &me,
                                   1,
                                   GetIdent (),
                                   GetHost (),
                                   "",
                                   GetAddress (),
                                   GetNumeric (),
                                   GetDesc ()
                                 ), &me );
    protocol.Send ( CMessageMODE ( this, 0, szModes ), this );
}
