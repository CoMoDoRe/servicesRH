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
// Archivo:     CDelayedDeletionElement.h
// Prop�sito:   Clase para identificar los elementos que se borran al final de un pulso
// Autores:     Alberto Alonso <rydencillo@gmail.com>
//

class CDelayedDeletionElement
{
    friend class CProtocol;

public:
                CDelayedDeletionElement     ( ) : m_bIsBeingDeleted ( false ) {}
    virtual     ~CDelayedDeletionElement    ( ) { }

    bool        IsBeingDeleted              ( ) const { return m_bIsBeingDeleted; }

private:
    void        SetBeingDeleted             ( bool bState ) { m_bIsBeingDeleted = bState; }

private:
    bool        m_bIsBeingDeleted;
};
