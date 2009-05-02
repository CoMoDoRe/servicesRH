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
// Archivo:     CDirectory.h
// Prop�sito:   Clase que permite abrir e iterar directorios, multiplataforma (Win32 y POSIX).
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

#pragma once

class CDirectory;

#ifdef WIN32
	#include "CDirectory_win32.h"
#else
	#include "CDirectory_posix.h"
#endif
