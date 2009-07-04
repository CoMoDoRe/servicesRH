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
// Archivo:     CTimerManager.h
// Prop�sito:   Gestor de cron�metros.
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

class CTimer;

class CTimerManager
{
    friend class CTimer;

    // Parte no est�tica
public:
                                    CTimerManager           ( );
                                    ~CTimerManager          ( );

    CTimer*                         CreateTimer             ( const TIMER_CALLBACK& callback,
                                                              unsigned int uiTimesToExecute,
                                                              unsigned int uiMiliseconds,
                                                              void* pUserData = 0 );

    unsigned int                    GetCount                ( ) const { return m_listTimers.size (); }
    unsigned int                    GetTimeForNextExec      ( CTimer* pTimer = 0 ) const;

    void                            Execute                 ( );
    bool                            IsActive                ( CTimer* pTimer ) const;
    void                            Stop                    ( CTimer* pTimer );
    unsigned int                    GetTimesToExecute       ( CTimer* pTimer ) const;

private:
    std::list < CTimer* >::const_iterator
                                    FindTimer               ( CTimer* pTimer ) const;
    std::list < CTimer* >::iterator
                                    FindTimer               ( CTimer* pTimer );
    void                            InsertIntoListSorted    ( CTimer* pTimer );

private:
    bool                            m_bExecutingTimers;
    std::list < CTimer* >           m_listTimers;


    // Parte est�tica
public:
    static CTimerManager&           GetSingleton            ( );
    static CTimerManager*           GetSingletonPtr         ( );

private:
    static CTimerManager*           ms_instance;
};
