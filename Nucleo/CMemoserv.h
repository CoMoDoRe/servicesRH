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
// Archivo:     CMemoserv.h
// Prop�sito:   Mensajer�a entre usuarios
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

class CMemoserv : public CService
{
private:
    struct SGlobalIDs
    {
        unsigned long long      ID;
        unsigned long long      MessageID;
        std::vector < CUser* >  vecConnectedUsers;
    };

public:
                    CMemoserv               ( const CConfig& config );
    virtual         ~CMemoserv              ( );

    void            Load                    ( );
    void            Unload                  ( );

private:
    bool            CheckIdentifiedAndReg   ( CUser& s );
    unsigned long long
                    GetBestIDForMessage     ( unsigned long long ID, bool bIgnoreBoxSize = false );

    // Comandos
protected:
    void            UnknownCommand          ( SCommandInfo& info );
private:
#define COMMAND(x) bool cmd ## x ( SCommandInfo& info )
    COMMAND(Help);
    COMMAND(Send);
    COMMAND(List);
    COMMAND(Read);
    COMMAND(Del);
    COMMAND(Global);
#undef COMMAND

    // Verificaci�n de acceso a comandos
private:
    bool            verifyAll               ( SCommandInfo& info );
    bool            verifyCoadministrator   ( SCommandInfo& info );

    // Eventos
private:
    bool            evtIdentify             ( const IMessage& msg );

private:
    struct
    {
        CString         szHashingKey;
        unsigned int    uiMaxInboxSize;
        unsigned int    uiTimeSend;
    } m_options;

    CNickserv*      m_pNickserv;
};