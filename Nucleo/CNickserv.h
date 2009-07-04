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
// Archivo:     CNickserv.h
// Prop�sito:   Registro de nicks.
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

class CNickserv : public CService
{
public:
                    CNickserv       ( const CConfig& config );
    virtual         ~CNickserv      ( );

    unsigned long long
                    GetAccountID    ( const CString& szName );


    // Comandos
protected:
    void            UnknownCommand  ( SCommandInfo& info );
private:
#define COMMAND(x) bool cmd ## x ( SCommandInfo& info )
    COMMAND ( Help );
    COMMAND ( Register );
    COMMAND ( Identify );
#undef COMMAND


    // Verificaci�n de acceso a comandos
private:
    bool            verifyAll       ( SCommandInfo& info );
    bool            verifyOperator  ( SCommandInfo& info );


    // Eventos
private:
    bool            evtQuit         ( const IMessage& msg );
    bool            evtNick         ( const IMessage& msg );
    bool            evtMode         ( const IMessage& msg );
};