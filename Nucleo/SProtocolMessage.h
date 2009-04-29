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
// Archivo:     SProtocolMessage.h
// Prop�sito:   Estructura contenedora de los datos de mensajes del protocolo
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

struct SProtocolMessage
{
    SProtocolMessage ( )
    {
        pSource = 0;
        pDest = 0;
    }

    CClient* pSource;
    CString  szCommand;
    CString  szExtraInfo;
    CClient* pDest;
    CString  szText;
};