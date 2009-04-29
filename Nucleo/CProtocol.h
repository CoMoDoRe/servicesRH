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
// Archivo:     CProtocol.h
// Prop�sito:   Protocolo de cliente
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

#define PROTOCOL_CALLBACK CCallback < bool, const SProtocolMessage& >

class CProtocol
{
private:
    typedef google::dense_hash_map < const char*, std::vector < PROTOCOL_CALLBACK* > > t_commandsMap;

private:
    static CProtocol        ms_instance;

public:
    static CProtocol&       GetSingleton        ( );
    static CProtocol*       GetSingletonPtr     ( );

private:
                            CProtocol           ( );
public:
    virtual                 ~CProtocol          ( );

    virtual bool            Initialize          ( const CSocket& socket, const CConfig& config );
    virtual int             Loop                ( );
    virtual bool            Process             ( const CString& szLine );
    virtual int             Send                ( const IMessage& ircmessage, CClient* pSource = NULL );

    void                    AddHandler          ( const IMessage& message, const PROTOCOL_CALLBACK& callback );
    inline CServer&         GetMe               ( ) { return m_me; }
    inline const CServer&   GetMe               ( ) const { return m_me; }

private:
    CSocket                 m_socket;
    CConfig                 m_config;
    CString                 m_szLine;
    CServer                 m_me;
    t_commandsMap           m_commandsMap;
    bool                    m_bGotServer;
};
