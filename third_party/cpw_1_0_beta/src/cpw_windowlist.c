/***************************************************************************/
/*                                                                         */
/*  cpw_windowlist.c                                                       */
/*                                                                         */
/*    The Cpw library windowlist manager.                                  */
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

#include "cpw_windowlist.h"

/*************************************************************************/
/*                                                                       */
/*   init and exit.                                                      */
/*                                                                       */
/*************************************************************************/

bool
cpw_windowlist_init( pCpw cpw )
{
    ll_initList( &cpw->list_win );
    return true;
}

void
cpw_windowlist_exit( pCpw cpw )
{
    ll_deleteList( &cpw->list_win );
    return;
}

/*************************************************************************/
/*                                                                       */
/*   list management                                                     */
/*                                                                       */
/*************************************************************************/

/* insert a new window at top z position */

uint_32
cpw_windowlist_insert( pCpw cpw, pCpwWin window )
{
    return ll_addVoid( &cpw->list_win, (pVoid) window );    
}

/* replace a window pointer with a new one */

bool cpw_windowlist_replace( pCpw cpw, pCpwWin window, uint_32 id )
{
    return ll_setVoid( &cpw->list_win, id, (pVoid) window );
}


/* remove a window from the windowlist */

pCpwWin
cpw_windowlist_remove( pCpw cpw, uint_32 id )
{
    pCpwWin window;
    if ( !ll_getVoid( &cpw->list_win, (pVoid*)&window, id ) )
        return 0;
    ll_deleteElement( &cpw->list_win, id );
    return window;
}

/* get the window for id */

pCpwWin
cpw_windowlist_lookup( pCpw cpw, uint_32 id )
{
    pCpwWin window;
    if ( id == 0 ) id = cpw->win_foregroundid;
    if ( !ll_getVoid( &cpw->list_win, (pVoid*)&window, id ) )
        return 0;
    return window;
}

/* start an iteration of all windows */

pCpwWin
cpw_windowlist_iteratestart( pCpw cpw )
{
    ll_initIterate( &cpw->list_win );
    return (pCpwWin)le_getVoid( ll_getNext( &cpw->list_win ) );
}

/* get next window or 0 for no more */

pCpwWin
cpw_windowlist_iteratenext( pCpw cpw )
{
    return (pCpwWin)le_getVoid( ll_getNext( &cpw->list_win ) );
}

uint_32
cpw_windowlist_length( pCpw cpw )
{
    return (uint_32)ll_getLength( &cpw->list_win );
}
