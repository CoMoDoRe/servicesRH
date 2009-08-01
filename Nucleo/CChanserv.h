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
// Archivo:     CChanserv.h
// Prop�sito:   Registro de canales
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

class CChanserv : public CService
{
public:
                    CChanserv       ( const CConfig& config );
    virtual         ~CChanserv      ( );

    void            Load            ( );
    void            Unload          ( );

    bool            CheckIdentifiedAndReg   ( CUser& s );
    unsigned long long
                    GetChannelID            ( const CString& szChannelName );

    // Comandos
protected:
    void            UnknownCommand  ( SCommandInfo& info );
private:
#define COMMAND(x) bool cmd ## x ( SCommandInfo& info )
#define SET_COMMAND(x) bool cmd ## x ( SCommandInfo& info, unsigned long long IDTarget )
    COMMAND(Help);
    COMMAND(Register);
#undef SET_COMMAND
#undef COMMAND

    // Verificaci�n de acceso a comandos
private:
    bool            verifyAll               ( SCommandInfo& info );
    bool            verifyPreoperator       ( SCommandInfo& info );
    bool            verifyOperator          ( SCommandInfo& info );
    bool            verifyCoadministrator   ( SCommandInfo& info );
    bool            verifyAdministrator     ( SCommandInfo& info );

private:
    struct
    {
        unsigned int    uiTimeRegister;
    } m_options;

    CNickserv*      m_pNickserv;
};
