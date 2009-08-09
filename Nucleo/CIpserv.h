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
// Archivo:     CIpserv.h
// Prop�sito:   Servicio de clones
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

class CIpserv : public CService
{
public:
                    CIpserv                 ( const CConfig& config );
    virtual         ~CIpserv                ( );

    void            Load                    ( );
    void            Unload                  ( );

    CString         GetAccountIP            ( const CString& szName );

    // Comandos
protected:
    void            UnknownCommand          ( SCommandInfo& info );
private:
#define COMMAND(x) bool cmd ## x ( SCommandInfo& info )
    COMMAND(Help);
    COMMAND(Setip);
    COMMAND(Accounts);
    COMMAND(Register);
    COMMAND(Set);
    COMMAND(Drop);
    COMMAND(List);
    COMMAND(Default);
#undef COMMAND

    // Verificaci�n de acceso a comandos
private:
    bool            verifyCoadminOrRegistered   ( SCommandInfo& info );
    bool            verifyCoadmin               ( SCommandInfo& info );

private:
    CNickserv*      m_pNickserv;
};
