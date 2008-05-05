/***************************************************************************/
/*                                                                         */
/*  cpw_linkedlist.c                                                       */
/*                                                                         */
/*    Cpw's linked list. General purpose linked list routines.             */
/*                                                                         */
/*  Copyright 2001-2002 by                                                 */
/*  Jim Mathies,                                                           */
/*                                                                         */
/*  This file is part of the Cpw project, and may only be used,            */
/*  modified, and distributed under the terms of the Cpw project           */
/*  license.  By continuing to use, modify, or distribute this file        */
/*  you indicate that you have read the license and understand and         */
/*  accept it fully.                                                       */
/*                                                                         */
/*  File Platform: cross                                                   */
/*                                                                         */
/***************************************************************************/

#include "cpw_linkedlist.h"

/* init of list data structure */

void 
ll_initList( LinkedListData * lld )
{
    lld->idcount = 1;
    lld->baseElement = null;
}

/* deletes a list's contents. returns the number of objects collected */

uint_32
ll_deleteList( LinkedListData * lld )
{
    uint_32 killcount = 0;

    if ( lld == null ) return 0;
    
    if ( lld->baseElement == null ) return 0;

    killcount = 0;

    /* clean up the list elements */
    le_cleanUp( lld->baseElement, &killcount );

    /* free our base element */
    le_freeElement( &lld->baseElement );

    lld->idcount = 1;
    lld->baseElement = null;

    return killcount++;
}

/* create and init a list */

LinkedListData * 
ll_createList( void )
{
    LinkedListData * p;
    p = (LinkedListData*) cpwmalloc( sizeof( LinkedListData ) );
    if ( p == null ) return null;
    ll_initList( p );
    return p;
}

/* delete and free a list pointer */

void 
ll_freeList( LinkedListData ** lld )
{
    if ( lld == null ) return;
    if ( *lld == null ) return;

    ll_deleteList( *lld );
    cpwfree( *lld );
    *lld = null;
}

/* returns id of element or 0 on error */

uint_32 
ll_addStr( LinkedListData * lld, pStr string )
{
    LinkedElement * le = le_initStr( string, lld->idcount );
    if ( le == null ) return 0;

    if ( lld->baseElement == null ) {
        lld->baseElement = le;
    } else {
        le_linkUp( lld->baseElement, le );
    }

    lld->idcount++;
    return lld->idcount-1;
}

/* returns id of element or 0 on error */

uint_32 
ll_addString( LinkedListData * lld, char* string )
{
    LinkedElement * le = le_initString( string, lld->idcount );
    if ( le == null ) return 0;

    if ( lld->baseElement == null ) {
        lld->baseElement = le;
    } else {
        le_linkUp( lld->baseElement, le );
    }

    lld->idcount++;
    return lld->idcount-1;
}

/* returns id of element or 0 on error */

uint_32 
ll_addFloat64( LinkedListData * lld, float_64 number )
{
    LinkedElement * le = le_initFloat64( number, lld->idcount );
    if ( le == null ) return 0;

    if ( lld->baseElement == null ) {
        lld->baseElement = le;
    } else {
        le_linkUp( lld->baseElement, le );
    }

    lld->idcount++;
    return lld->idcount-1;
}

/* returns id of element or 0 on error */

uint_32 
ll_addInt32( LinkedListData * lld, int_32 number )
{
    LinkedElement * le = le_initInt32( number, lld->idcount );
    if ( le == null ) return 0;

    if ( lld->baseElement == null ) {
        lld->baseElement = le;
    } else {
        le_linkUp( lld->baseElement, le );
    }

    lld->idcount++;
    return lld->idcount-1;
}

/* returns id of element or 0 on error */

uint_32 
ll_addVoid( LinkedListData * lld, void * p )
{
    LinkedElement * le = le_initVoid( p, lld->idcount );
    if ( le == null ) return 0;

    if ( lld->baseElement == null ) {
        lld->baseElement = le;
    } else {
        le_linkUp( lld->baseElement, le );
    }

    lld->idcount++;
    return lld->idcount-1;
}

/* returns pStr or null if not found */

bool
ll_getString( LinkedListData * lld, pStr* string, uint_32 id )
{
    LinkedElement * le;

    if ( lld->baseElement == null ) return false;
    le = le_seek( lld->baseElement, id );
    setStr( string, le_getString( le ) );
    return true;
}

/* returns void* pointer or null if not found */

bool
ll_getVoid( LinkedListData * lld, void** pdata, uint_32 id )
{
    LinkedElement * le;

    if ( lld->baseElement == null ) return false;
    le = le_seek( lld->baseElement, id );
    *pdata = le_getVoid( le );
    return true;
}

/* returns bool indicating success or failure, fills string with value if found */

bool
ll_popString( LinkedListData * lld, pStr * string )
{
    LinkedElement * le;
    pStr tmp;

    if ( lld->baseElement == null ) return false;

    le = le_lastOne( lld->baseElement );
    if ( le == null ) return false;

    tmp = le_getString( le );
    if ( tmp == null ) return false;

    setStr( string, tmp );

    le = le_unLink( lld->baseElement, null, le_getId( le ) );
    if ( le == lld->baseElement ) lld->baseElement = null;

    le_freeElement( &le );

    lld->idcount = 1;

    return true;
}

bool
ll_popFloat64( LinkedListData * lld, float_64 * number )
{
    LinkedElement * le;

    if ( lld->baseElement == null ) return false;

    le = le_lastOne( lld->baseElement );
    if ( le == null ) return false;

    *number = le_getFloat64( le );

    le = le_unLink( lld->baseElement, null, le_getId( le ) );
    if ( le == lld->baseElement ) lld->baseElement = null;

    le_freeElement( &le );
    
    lld->idcount = 1;

    return true;
}

bool
ll_popInt32( LinkedListData * lld, int_32 * number )
{
    LinkedElement * le;

    if ( lld->baseElement == null ) return false;

    le = le_lastOne( lld->baseElement );
    if ( le == null ) return false;

    *number = le_getInt32( le );

    le = le_unLink( lld->baseElement, null, le_getId( le ) );
    if ( le == lld->baseElement ) lld->baseElement = null;

    le_freeElement( &le );

    lld->idcount = 1;

    return true;
}

bool
ll_setVoid( LinkedListData * lld, uint_32 id, void* p )
{
    LinkedElement * le;

    if ( lld->baseElement == null ) return false;

    if ( !( le = le_seek( lld->baseElement, id ) ) )
        return false;

    le_setVoid( le, p );

    return true;
}

bool
ll_deleteElement( LinkedListData * lld, uint_32 id )
{
    LinkedElement * le = null;

    if ( lld->baseElement == null ) return false;

    le = le_unLink( lld->baseElement, null, id );

    if ( le == lld->baseElement ) lld->baseElement = null;

    if ( le != null ) {
        le_freeElement( &le );
        return true;
    }

    return false;
}

int_32 
ll_getLength( LinkedListData * lld )
{
    uint_32 count = 0;

    if ( lld->baseElement == null ) return 0;

    le_countUp( lld->baseElement, &count );
    
    return count;
}

bool 
ll_initIterate( LinkedListData * lld )
{
    if ( lld->baseElement == null ) return false;

    le_initIterate( lld->baseElement );
   
    return true;
}

LinkedElement *
ll_getNext( LinkedListData * lld )
{
    if ( lld->baseElement == null ) return 0;

    return le_getNext( lld->baseElement );
}

LinkedElement *
ll_getElement( LinkedListData * lld, uint_32 id )
{
    if ( lld->baseElement == null ) return 0;

    return le_seek( lld->baseElement, id );
}

uint_32 
ll_linkUp( LinkedListData * lld, LinkedElement* le )
{
    if ( le == null ) return 0;

    le_setId( le, lld->idcount );

    lld->idcount++;

    if ( lld->baseElement == null )
        lld->baseElement = le;
    else
        le_linkUp( lld->baseElement, le );

    return lld->idcount;
}

/* unlink an element. does not delete the element. */

bool
ll_unLink( LinkedListData * lld, uint_32 id ) 
{
    LinkedElement * le;

    le = null;

    if ( lld->baseElement != null )
        le = le_unLink( lld->baseElement, null, id );

    /* not found */
    if ( le == null ) 
        return false;

    if ( le == lld->baseElement ) lld->baseElement = null;

    lld->idcount = 1;

	return  true;
}

/* flip the list over into a new list. lld must have been created 
   with ll_createList(). It is iterated, deleted, freed here and then replaced. */

bool
ll_flipList( LinkedListData ** lld ) 
{
    LinkedElement * le;
    LinkedListData * plist;

    if ( lld == null ) return false;
    if ( *lld == null ) return false;

    if ( ll_getLength( *lld ) <= 0 ) return false;

    plist = ll_createList();
    ll_initList( plist );

    /* flip into new stack */

    while ( le = le_lastOne( (*lld)->baseElement )  ) {
        switch ( le->etype ) {
            case Element_pStr:
                ll_addStr( plist, le->e.e_pstr );
            break;
    
            case Element_Float64:
                ll_addFloat64( plist, le->e.e_float_32 );
            break;

            case Element_Int32:
                ll_addInt32( plist, le->e.e_int_32 );
            break;

            case Element_Void:
                ll_addVoid( plist, le->e.e_pvoid );
            break;
        }
        ll_unLink( *lld, le_getId( le ) );
        le_freeElement( &le );
    }

    ll_freeList( lld );
    *lld = plist;
    return true;
}
