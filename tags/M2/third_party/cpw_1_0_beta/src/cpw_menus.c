/***************************************************************************/
/*                                                                         */
/*  cpw_menus.c                                                            */
/*                                                                         */
/*    Window menus.                                                        */
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

#include "cpw_menus.h"
#include "cpw_error.h"
#include "cpw_windowlist.h"
#include CPW_LOCALHOST_H

/*************************************************************************/
/*                                                                       */
/*   list management                                                     */
/*                                                                       */
/*************************************************************************/

/* insert a new menu into the list */

uint_32
cpw_menulist_insert( pCpw cpw, pCpwMenu menu )
{
    return ll_addVoid( &cpw->list_menus, (pVoid) menu );    
}

/* get the window for id */

pCpwMenu
cpw_menulist_lookup( pCpw cpw, uint_32 menuid )
{
    pCpwMenu menu;
    if ( !ll_getVoid( &cpw->list_menus, (pVoid*)&menu, menuid ) )
        return 0;
    return menu;
}

/* start an iteration of all menus */

pCpwMenu
cpw_menulist_iteratestart( pCpw cpw )
{
    ll_initIterate( &cpw->list_menus );
    return (pCpwMenu)le_getVoid( ll_getNext( &cpw->list_menus ) );
}

/* get next menu or 0 for no more */

pCpwMenu
cpw_menulist_iteratenext( pCpw cpw )
{
    return (pCpwMenu)le_getVoid( ll_getNext( &cpw->list_menus ) );
}

/*************************************************************************/
/*                                                                       */
/*   init and exit.                                                      */
/*                                                                       */
/*************************************************************************/

bool
cpw_menus_init( pCpw cpw )
{
    ll_initList( &cpw->list_menus );
    return true;
}

void
cpw_menus_exit( pCpw cpw )
{
    pCpwMenu menu;

    /* iterate across all menus every created */
    
    menu = cpw_menulist_iteratestart( cpw );

    while ( menu != 0 ) {

        uint_32 i;

        /* destory this menu's entry resources */

        for ( i = 0; i < menu->ecount; i++ ) {

            /* make sure we have an allocated entry */

            if ( menu->entries[i] != 0 ) {

                /* free the string label if it exists */
                                
                if ( menu->entries[i]->title != 0 )
                    freeStr( &menu->entries[i]->title );
                
                /* free the entry memory itself */

                cpwfree( menu->entries[i] );
            }
        }

        /* free menu resources */

        cpwfree( menu );        

        menu = cpw_menulist_iteratenext( cpw );
    }

    /* free the list */

    ll_deleteList( &cpw->list_menus );

    return;
}

/*************************************************************************/
/*                                                                       */
/*   button popup function for cpw_event.c's button click event          */
/*                                                                       */
/*************************************************************************/

/* called from cpw_event when it processes a button down event thats assigned */

void cpw_menus_popupselected( pCpw cpw, pCpwWin window, uint_32 menuid, uint_32 x, uint_32 y )
{
    pCpwMenu menu;

    menu = cpw_menulist_lookup( cpw, menuid );

    if ( menu == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidmenuid );
        return;
    }

    cpw_localhost_displaypopup( cpw, window, menu, x, y );
}

/*************************************************************************/
/*                                                                       */
/*   sending a popup event to the menu's callback                        */
/*                                                                       */
/*************************************************************************/

/* called from cpw_event when it processes a menuselected event */

void cpw_menus_popupcallback( pCpw cpw, uint_32 id, uint_32 menuid, uint_32 entryid )
{
    pCpwMenu menu;

    menu = cpw_menulist_lookup( cpw, menuid );

    if ( menu == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidmenuid );
        return;
    }

    if ( menu->callback == 0 ) return;

    menu->callback( cpw, id, menuid, entryid );
}

/*************************************************************************/
/*                                                                       */
/*   menu api                                                            */
/*                                                                       */
/*************************************************************************/

/* create / destroy / callback */

uint_32 cpwCreateMenu( pCpw cpw, CpwMenuCallback callback )
{
    pCpwMenu menu;
    
    menu = cpwmalloc( sizeof( CpwMenu ) );

    if ( menu == 0 ) {
        cpw_error_set( cpw, cpw_error_outofmemory );
        return 0;
    }
        
    memset( menu, 0, sizeof( CpwMenu ) );

    menu->id = cpw_menulist_insert( cpw, menu );
    menu->callback = callback;

    return menu->id;        
}

uint_32 cpwCreateSubMenu( pCpw cpw )
{
    pCpwMenu menu;
    
    menu = cpwmalloc( sizeof( CpwMenu ) );

    if ( menu == 0 ) {
        cpw_error_set( cpw, cpw_error_outofmemory );
        return 0;
    }
        
    memset( menu, 0, sizeof( CpwMenu ) );

    menu->id = cpw_menulist_insert( cpw, menu );
    menu->callback = 0;

    return menu->id;        
}

bool cpwDestroyMenu( pCpw cpw, uint_32 menuid )
{
    return false;
}

/* menu entry manipulation */

bool cpwAddMenuEntry( pCpw cpw, uint_32 menuid, pChar title, uint_32 entryid, bool checked )
{
    pCpwMenu menu;
    pCpwMenuEntry entry;

    menu = cpw_menulist_lookup( cpw, menuid );

    if ( menu == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidmenuid );
        return false;
    }

    /* make sure we aren't maxing out on entries */

    if ( menu->ecount > CPW_MENUS_MAXENTRIES ) {
        cpw_error_set( cpw, cpw_error_maxentriesreached );
        return false;
    }

    entry = cpwmalloc( sizeof( CpwMenuEntry ) );

    if ( entry == 0 ) {
        cpw_error_set( cpw, cpw_error_outofmemory );
        return false;
    }
        
    memset( entry, 0, sizeof( CpwMenuEntry ) );

    /* store entry info */

    entry->id = entryid;
    setString( &entry->title, title );
    entry->f_checked = checked;

    /* store entry in menu */

    menu->entries[menu->ecount] = entry;
    menu->ecount++;
                    
    return true;
}

bool cpwAddMenuSeperator( pCpw cpw, uint_32 menuid, uint_32 entryid )
{
    pCpwMenu menu;
    pCpwMenuEntry entry;

    menu = cpw_menulist_lookup( cpw, menuid );

    if ( menu == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidmenuid );
        return false;
    }

    /* make sure we aren't maxing out on entries */

    if ( menu->ecount > CPW_MENUS_MAXENTRIES ) {
        cpw_error_set( cpw, cpw_error_maxentriesreached );
        return false;
    }

    entry = cpwmalloc( sizeof( CpwMenuEntry ) );

    if ( entry == 0 ) {
        cpw_error_set( cpw, cpw_error_outofmemory );
        return false;
    }
        
    memset( entry, 0, sizeof( CpwMenuEntry ) );

    /* store entry info */

    entry->id = entryid;
    entry->f_seperator = true;

    /* store entry in menu */

    menu->entries[menu->ecount] = entry;
    menu->ecount++;
                    
    return true;
}

bool cpwAddSubMenu( pCpw cpw, uint_32 menuid, pChar title, uint_32 submenuid, uint_32 entryid )
{
    pCpwMenu menu;
    pCpwMenu submenu;
    pCpwMenuEntry entry;

    menu = cpw_menulist_lookup( cpw, menuid );

    if ( menu == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidmenuid );
        return false;
    }

    submenu = cpw_menulist_lookup( cpw, submenuid );

    if ( menu == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidmenuid );
        return false;
    }

    /* make sure we aren't maxing out on entries */

    if ( menu->ecount > CPW_MENUS_MAXENTRIES ) {
        cpw_error_set( cpw, cpw_error_maxentriesreached );
        return false;
    }

    entry = cpwmalloc( sizeof( CpwMenuEntry ) );

    if ( entry == 0 ) {
        cpw_error_set( cpw, cpw_error_outofmemory );
        return false;
    }
        
    memset( entry, 0, sizeof( CpwMenuEntry ) );

    /* store entry info */

    entry->id = entryid;
    entry->f_submenu = true;
    setString( &entry->title, title );
    entry->submenu = (pVoid) submenu;

    /* store entry in menu */

    menu->entries[menu->ecount] = entry;
    menu->ecount++;
                    
    return true;
}

bool cpwEditMenuItem( pCpw cpw, uint_32 menuid, uint_32 entryid, uint_32 newid, pChar newtitle, uint_32 newmenuid )
{
    return false;
}

bool cpwRemoveMenuItem( pCpw cpw, uint_32 menuid, uint_32 entryid )
{
    return false;
}

/* assigning menus to windows */

bool cpwAssignMenuToWindow( pCpw cpw, uint_32 menuid, uint_32 winid )
{
    pCpwMenu menu;
    pCpwWin window;

    /* lookups */

    window = cpw_windowlist_lookup( cpw, winid );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    menu = cpw_menulist_lookup( cpw, menuid );

    if ( menu == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidmenuid );
        return false;
    }

    /* assign to window */

    if ( !cpw_localhost_assignmenutowindow( cpw, window, menu ) ) {
        window->menuid = 0;
        cpw_error_set( cpw, cpw_error_unabletoassignmenu );
        return false;
    }

    window->menuid = menu->id;
    return true;
}

bool cpwUnassignMenu( pCpw cpw, uint_32 winid )
{
    pCpwWin window;

    /* lookups */

    window = cpw_windowlist_lookup( cpw, winid );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    /* unassign */

    if ( window->menuid == 0 ) {
        cpw_error_set( cpw, cpw_error_menunotassigned );
        return false;
    }

    cpw_localhost_unassignmenu( cpw, window );

    window->menuid = 0;
    return true;
}


/* attaching menus to buttons per window */

bool cpwAttachMenuToButton( pCpw cpw, uint_32 menuid, uint_32 button, uint_32 winid )
{
    pCpwWin window;
    pCpwMenu menu;

    /* lookups */

    window = cpw_windowlist_lookup( cpw, winid );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    menu = cpw_menulist_lookup( cpw, menuid );

    if ( menu == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidmenuid );
        return false;
    }

    /* attach */

    window->buttonmenuid[button] = menuid;

    return true;
}

bool cpwDetachMenu( pCpw cpw, uint_32 button, uint_32 winid )
{
    pCpwWin window;

    /* lookups */

    window = cpw_windowlist_lookup( cpw, winid );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    /* unattach */

    window->buttonmenuid[button] = 0;

    return true;
}

/* find a menuentry by entryid */
 
pCpwMenuEntry cpw_menus_findentry( pCpw cpw, pCpwMenu menu, uint_32 entryid )
{
    uint_32 i; 
    pCpwMenuEntry entry;

    for ( i = 0; i < menu->ecount; i++ ) {

        /* printf( "looking for:%u at %u in menu %x.\n", entryid, menu->entries[i]->id, menu ); */

        if ( menu->entries[i]->id == entryid )
            return menu->entries[i];

        if ( menu->entries[i]->f_submenu ) {

            /* step down into sub menu using the call stack for state */

            if ( ( entry = cpw_menus_findentry( cpw, menu->entries[i]->submenu, entryid ) ) > 0 )
                return entry;

            /* it wasn't in that sub menu, or it's sub menus.. continue.. */
        }
    }

    /* not found in this menu */

    return 0;
}

/* item check marks */

bool cpwCheckMenuEntry( pCpw cpw, uint_32 menuid, uint_32 entryid )
{
    pCpwMenu menu;
    pCpwMenuEntry entry;

    /* lookups */

    menu = cpw_menulist_lookup( cpw, menuid );

    if ( menu == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidmenuid );
        return false;
    }

    /* search for entry id */

    entry = cpw_menus_findentry( cpw, menu, entryid );

    if ( entry > 0 ) {

        pCpwWin window;

        entry->f_checked = true;

        /* menus can have a 1 to many relationship with windows. 
           for popups, changing a check value is no big deal since
           popups are created on the fly based on the menu's 
           current info. for titlebar menus however, they may need
           to be updated. were going to iterate across the windowlist
           and send a menu updates to windows to compensate. */

        window = cpw_windowlist_iteratestart( cpw );

        if ( window == 0 ) {
            cpw_error_set( cpw, cpw_error_invalidwindowid );
            return false;
        }

        while ( window != 0 ) {

            /* update window menu */

            if ( window->menuid != 0 ) 
                cpw_localhost_updatemenu( cpw, window, menu );

            window = cpw_windowlist_iteratenext( cpw );
        }
        
        return true;
    }

    cpw_error_set( cpw, cpw_error_invalidentryid );
    return false;
}

bool cpwUncheckMenuEntry( pCpw cpw, uint_32 menuid, uint_32 entryid )
{
    pCpwMenu menu;
    pCpwMenuEntry entry;

    /* lookups */

    menu = cpw_menulist_lookup( cpw, menuid );

    if ( menu == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidmenuid );
        return false;
    }

    /* search for entry id */

    entry = cpw_menus_findentry( cpw, menu, entryid );

    if ( entry > 0 ) {

        pCpwWin window;

        entry->f_checked = false;

        window = cpw_windowlist_iteratestart( cpw );

        if ( window == 0 ) {
            cpw_error_set( cpw, cpw_error_invalidwindowid );
            return false;
        }

        while ( window != 0 ) {

            /* update window menu */

            if ( window->menuid != 0 ) 
                cpw_localhost_updatemenu( cpw, window, menu );

            window = cpw_windowlist_iteratenext( cpw );
        }
        
        return true;
    }

    cpw_error_set( cpw, cpw_error_invalidentryid );
    return false;
}

bool cpwMenuEntryChecked( pCpw cpw, uint_32 menuid, uint_32 entryid )
{
    pCpwMenu menu;
    pCpwMenuEntry entry;

    /* lookups */

    menu = cpw_menulist_lookup( cpw, menuid );

    if ( menu == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidmenuid );
        return false;
    }

    /* search for entry id */

    entry = cpw_menus_findentry( cpw, menu, entryid );

    if ( entry > 0 ) {
        return entry->f_checked;
    }

    cpw_error_set( cpw, cpw_error_invalidentryid );
    return false;
}


