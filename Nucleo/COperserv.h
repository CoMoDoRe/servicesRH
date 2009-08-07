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
// Archivo:     COperserv.h
// Prop�sito:   Servicio para operadores
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

class COperserv : public CService
{
public:
                    COperserv               ( const CConfig& config );
    virtual         ~COperserv              ( );

    void            Load                    ( );
    void            Unload                  ( );


    CDate           GetGlineExpiration      ( const CString& szMask, unsigned long long& ID );
    void            DropGline               ( unsigned long long ID );
    bool            GetGlineMask            ( CUser& s, const CString& szNickOrMask, CString& szFinalMask, bool& bIsMask );

    // Comandos
protected:
    void            UnknownCommand          ( SCommandInfo& info );
private:
#define COMMAND(x) bool cmd ## x ( SCommandInfo& info )
    COMMAND(Help);
    COMMAND(Kill);
    COMMAND(Gline);
    COMMAND(Raw);
    COMMAND(Load);
    COMMAND(Unload);
    COMMAND(Table);
#undef COMMAND

    // Verificaci�n de acceso a comandos
private:
    bool            verifyPreoperator       ( SCommandInfo& info );
    bool            verifyOperator          ( SCommandInfo& info );
    bool            verifyCoadministrator   ( SCommandInfo& info );
    bool            verifyAdministrator     ( SCommandInfo& info );

    // Foreach
private:
    struct SOperatorCheck
    {
        CUser*  pOperator;
        char    szMask [ 512 ];
        int     minlen;
        int     charset;
    };
    bool            foreachUserCheckOperatorMask    ( SForeachInfo < CUser* >& );

    // Eventos
private:
    bool            evtNick         ( const IMessage& msg );

    // Cron�metros
private:
    bool            timerCheckExpiredGlines     ( void* );
    CTimer*         m_pTimerGlineExpired;

private:
    CNickserv*      m_pNickserv;
};
