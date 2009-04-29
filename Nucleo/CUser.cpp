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
// Archivo:     CUser.cpp
// Prop�sito:   Usuarios
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#include "stdafx.h"

const unsigned long CUser::ms_ulUserModes [ 256 ] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,       /* 000-009 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,       /* 010-019 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,       /* 020-029 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,       /* 030-039 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,       /* 040-049 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,       /* 050-059 */

    0, 0, 0, 0, 0, CUser::UMODE_ADMIN, CUser::UMODE_BOT, 0, CUser::UMODE_DEVELOPER, 0,      /* 060-069 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, CUser::UMODE_LOCOP,                                          /* 070-079 */
    0, 0, CUser::UMODE_ONLYREG, CUser::UMODE_SUSPENDED, 0, 0, 0, 0, CUser::UMODE_VIEWIP, 0, /* 080-089 */
    0, 0, 0, 0, 0, 0, 0, CUser::UMODE_COADMIN, CUser::UMODE_USERBOT, 0,                     /* 090-099 */
    CUser::UMODE_DEAF, 0, 0, CUser::UMODE_DEBUG, CUser::UMODE_HELPOP,                       /* 100-104 */
    CUser::UMODE_INVISIBLE, 0, CUser::UMODE_CHSERV, 0, 0,                                   /* 105-109 */
    CUser::UMODE_IDENTIFIED, CUser::UMODE_OPER, CUser::UMODE_PREOP, 0,                      /* 110-113 */
    CUser::UMODE_REGNICK, CUser::UMODE_SERVNOTICE, 0, 0, 0, CUser::UMODE_WALLOP,            /* 114-119 */
    CUser::UMODE_HIDDENHOST, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                     /* 120-129 */

    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,       /* 130-139 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,       /* 140-149 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,       /* 150-159 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,       /* 160-169 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,       /* 170-179 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,       /* 180-189 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,       /* 190-199 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,       /* 200-209 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,       /* 210-229 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,       /* 220-229 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,       /* 230-239 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,       /* 240-249 */
    0, 0, 0, 0, 0, 0                    /* 250-255 */
};

CUser::CUser ( )
{
}

CUser::CUser ( CServer* pServer,
               unsigned long ulNumeric,
               const CString& szName,
               const CString& szIdent,
               const CString& szDesc,
               const CString& szHost,
               unsigned long ulAddress )
{
    Create ( pServer, ulNumeric, szName, szIdent, szDesc, szHost, ulAddress );
}

CUser::~CUser ()
{
}

void CUser::Create ( CServer* pServer,
               unsigned long ulNumeric,
               const CString& szName,
               const CString& szIdent,
               const CString& szDesc,
               const CString& szHost,
               unsigned long ulAddress )
{
    CClient::Create ( pServer, ulNumeric, szName, szDesc );
    m_szIdent = szIdent;
    m_szHost = szHost;
    m_ulAddress = ulAddress;
}

void CUser::FormatNumeric ( char* szDest ) const
{
    const CClient* pParent = CClient::GetParent ();

    if ( pParent )
    {
        unsigned long ulServerNumeric = pParent->GetNumeric ();
        if ( ulServerNumeric > 63 )
        {
            unsigned long ulNumeric = ( ulServerNumeric << 18 ) | CClient::GetNumeric ();
            inttobase64 ( szDest, ulNumeric, 5 );
        }
        else
        {
            unsigned long ulNumeric = ( ulServerNumeric << 12 ) | CClient::GetNumeric ();
            inttobase64 ( szDest, ulNumeric, 3 );
        }

    }
    else
        *szDest = '\0';
}

void CUser::SetNick ( const CString& szNick )
{
    CClient* pParent = GetParent ();
    if ( pParent )
    {
        CServer* pServer = static_cast < CServer* > ( pParent );
        pServer->UpdateUserName ( this, szNick );
    }
    CClient::SetName ( szNick );
}

void CUser::SetModes ( const CString& szModes )
{
    enum { ADD, DEL } eDirection = ADD;

    const char* p = szModes.c_str ();
    while ( *p != '\0' )
    {
        switch ( *p )
        {
            case '+':
            {
                eDirection = ADD;
                break;
            }
            case '-':
            {
                eDirection = DEL;
                break;
            }
            default:
            {
                unsigned long ulFlag = CUser::ms_ulUserModes [ *p ];
                if ( eDirection == ADD )
                    m_ulModes |= ulFlag;
                else
                    m_ulModes &= ~ulFlag;
            }
        }

        ++p;
    }
}
