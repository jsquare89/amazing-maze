/***************************************************************************/
/*                                                                         */
/*  cpw_event.c                                                            */
/*                                                                         */
/*    The Cpw library event stack interface and management.                */
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

#include "cpw_event.h"
#include "cpw_error.h"
#include "cpw_windowlist.h"
#include CPW_LOCALHOST_H

/* #define DEBUGEVENTRAW 1  prints stack s/r data to stdout */
/* #define DEBUGUSEREVENTS 1  prints every event sent to the application */

/*************************************************************************/
/*                                                                       */
/*   init and exit.                                                      */
/*                                                                       */
/*************************************************************************/

bool cpw_event_init( pCpw cpw )
{
    /* allocate the stack's memory */

    cpw->stack = cpwmalloc( sizeof( CpwEventStack ) );

    if ( cpw->stack == 0 ) { 
        cpw_error_set( cpw, cpw_error_outofmemory );
        return false; 
    }

    memset( cpw->stack, 0, sizeof( CpwEventStack ) );
    return true;
}

void cpw_event_exit( pCpw cpw )
{
    cpwFilterEvent( cpw, CPW_DISPLAY_EVENT, true );
    cpwFilterEvent( cpw, CPW_RESHAPE_EVENT, true );

    /* flush pending events include window close events */

    while ( cpw_event_sendevent( cpw ) ) {}

    /* free event stack memory */

    cpwfree( cpw->stack );
}

/*************************************************************************/
/*                                                                       */
/*   global event handler setter api.                                    */
/*                                                                       */
/*************************************************************************/

bool cpwCreateCallback( pCpw cpw, CpwCreateCallback createCallback )
{
    cpw->createCallback = (pVoid)createCallback;
    return true;
}

bool cpwDisplayCallback( pCpw cpw, CpwDisplayCallback displayCallback )
{
    cpw->displayCallback = (pVoid)displayCallback;
    return true;
}

bool cpwReshapeCallback( pCpw cpw, CpwReshapeCallback reshapeCallback )
{
    cpw->reshapeCallback = (pVoid)reshapeCallback;
    return true;
}

bool cpwPositionCallback( pCpw cpw, CpwPositionCallback positionCallback )
{
    cpw->positionCallback = (pVoid)positionCallback;
    return true;
}

bool cpwKeyboardCallback( pCpw cpw, CpwKeyboardCallback keyCallback )
{
    cpw->keyCallback = (pVoid)keyCallback;
    return true;
}

bool cpwSystemKeyboardCallback( pCpw cpw, CpwSystemKeyboardCallback skeyCallback )
{
    cpw->skeyCallback = (pVoid)skeyCallback;
    return true;
}

bool cpwVisibilityCallback( pCpw cpw, CpwVisibilityCallback visibilityCallback )
{
    cpw->visibilityCallback = (pVoid)visibilityCallback;
    return true;
}

bool cpwMouseClickCallback( pCpw cpw, CpwMouseClickCallback mouseclickCallback )
{
    cpw->mouseclickCallback = (pVoid)mouseclickCallback;
    return true;
}

bool cpwMouseDragCallback( pCpw cpw, CpwMouseDragCallback mousedragCallback )
{
    cpw->mousedragCallback = (pVoid)mousedragCallback;
    return true;
}

bool cpwMouseMoveCallback( pCpw cpw, CpwMouseMoveCallback mousemoveCallback )
{
    cpw->mousemoveCallback = (pVoid)mousemoveCallback;
    return true;
}

bool cpwMouseEntryCallback( pCpw cpw, CpwMouseEntryCallback mouseentryCallback )
{
    cpw->mouseentryCallback = (pVoid)mouseentryCallback;
    return true;
}

/*************************************************************************/
/*                                                                       */
/*   window specifc event handler setter api.                            */
/*                                                                       */
/*************************************************************************/

bool cpwWindowCreateCallback( pCpw cpw, CpwCreateCallback createCallback, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    window->createCallback = (pVoid)createCallback;
    return true;
}

bool cpwWindowDisplayCallback( pCpw cpw, CpwDisplayCallback displayCallback, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    window->displayCallback = (pVoid)displayCallback;
    return true;
}

bool cpwWindowReshapeCallback( pCpw cpw, CpwReshapeCallback reshapeCallback, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    window->reshapeCallback = (pVoid)reshapeCallback;
    return true;
}

bool cpwWindowPositionCallback( pCpw cpw, CpwPositionCallback positionCallback, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    window->positionCallback = (pVoid)positionCallback;
    return true;
}

bool cpwWindowKeyboardCallback( pCpw cpw, CpwKeyboardCallback keyCallback, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    window->keyCallback = (pVoid)keyCallback;
    return true;
}

bool cpwWindowSystemKeyboardCallback( pCpw cpw, CpwSystemKeyboardCallback skeyCallback, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    window->skeyCallback = (pVoid)skeyCallback;
    return true;
}

bool cpwWindowVisibilityCallback( pCpw cpw, CpwVisibilityCallback visibilityCallback, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    window->visibilityCallback = (pVoid)visibilityCallback;
    return true;
}

bool cpwWindowMouseClickCallback( pCpw cpw, CpwMouseClickCallback mouseclickCallback, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    window->mouseclickCallback = (pVoid)mouseclickCallback;
    return true;
}

bool cpwWindowMouseDragCallback( pCpw cpw, CpwMouseDragCallback mousedragCallback, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    window->mousedragCallback = (pVoid)mousedragCallback;
    return true;
}

bool cpwWindowMouseMoveCallback( pCpw cpw, CpwMouseMoveCallback mousemoveCallback, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    window->mousemoveCallback = (pVoid)mousemoveCallback;
    return true;
}

bool cpwWindowMouseEntryCallback( pCpw cpw, CpwMouseEntryCallback mouseentryCallback, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    window->mouseentryCallback = (pVoid)mouseentryCallback;
    return true;
}

/*************************************************************************/
/*                                                                       */
/*   event stack manipulation api.                                       */
/*                                                                       */
/*************************************************************************/

/* set or clear an event filter flag */

bool cpwFilterEvent( pCpw cpw, CpwWindowEvent eventType, bool flag )
{
    bool old;
    CpwEventStack * es = (CpwEventStack*)cpw->stack;

    if ( eventType < 0 || eventType > CPW_MAXEVENTVALUE ) return false;

    old = es->filter.flag[eventType];
    es->filter.flag[eventType] = flag;

    return old;
}

/* return the next event */

CpwWindowEvent cpwNextEvent( pCpw cpw )
{
    CpwEventStack * es = (CpwEventStack*)cpw->stack;

    /* look ahead by one ( user is calling from a callback ) */

    if ( es->stack[es->nxtindex+1].used != 0 )
        return es->stack[es->nxtindex+1].event;

    return CPW_NO_EVENT;
}

/* return the next event for a particular window */

CpwWindowEvent cpwNextWindowEvent( pCpw cpw, uint_32 id ) 
{
    uint_8 index;
    CpwEventStack * es = (CpwEventStack*)cpw->stack;

    /* look ahead by one ( user is calling from a callback ) */

    index = es->nxtindex+1;

    while ( es->stack[index].used != 0 ) {

        if ( es->stack[index].winid == id )
            return es->stack[index].event;

        if ( index == es->insindex ) 
            break;

        index++;
    } 

    return CPW_NO_EVENT;
}

/* reset the event stack */

bool cpwClearEvents( pCpw cpw )
{
    CpwEventStack * es = (CpwEventStack*)cpw->stack;

    memset( es, 0, sizeof( CpwEventStack ) );

    es->insindex = 0;
    es->nxtindex = 0;

    return true;
}

/* clear a single type of event from pending events */

bool cpwClearEvent( pCpw cpw, CpwWindowEvent event ) 
{
    uint_8 index;
    CpwEventStack * es = (CpwEventStack*)cpw->stack;

    index = es->nxtindex;

    while ( es->stack[index].used != 0 ) {

        if ( es->stack[index].event == event )
            es->stack[index].filt = true;

        if ( index == es->insindex ) 
            break;

        index++;
    } 

    return true;
}

/* clear all events from pending events for a window */

bool cpwClearWindowEvents( pCpw cpw, uint_32 id ) 
{
    uint_8 index;
    CpwEventStack * es = (CpwEventStack*)cpw->stack;

    index = es->nxtindex;

    while ( es->stack[index].used != 0 ) {

        if ( es->stack[index].winid == id )
            es->stack[index].filt = true;

        if ( index == es->insindex ) 
            break;

        index++;
    } 

    return true;
}

/* clear a single type of event from pending events for a window */

bool cpwClearWindowEvent( pCpw cpw, CpwWindowEvent event, uint_32 id ) 
{
    uint_8 index;
    CpwEventStack * es = (CpwEventStack*)cpw->stack;

    index = es->nxtindex;

    while ( es->stack[index].used != 0 ) {

        if ( es->stack[index].event == event && es->stack[index].winid == id )
            es->stack[index].filt = true;

        if ( index == es->insindex ) 
            break;

        index++;
    } 

    return true;
}

/* pop the next event off the stack */

bool cpwPopEvent( pCpw cpw )
{
    CpwEventStack * es = (CpwEventStack*)cpw->stack;

    /* look ahead by one ( user is calling from a callback ) */

    if ( es->stack[es->nxtindex+1].used != 0 ) {
        es->stack[es->nxtindex+1].filt = true;
        return true;
    }

    return false;
}

/* return the number of pending events */

int_32 cpwStackDepth( pCpw cpw )
{
    CpwEventStack * es = (CpwEventStack*)cpw->stack;
    if ( es->nxtindex <= es->insindex ) 
        return ( es->insindex - es->nxtindex );
    else
        return ( es->nxtindex - es->insindex );
}

/*************************************************************************/
/*                                                                       */
/*   sending events to the application                                   */
/*                                                                       */
/*************************************************************************/

/* send window event helper */

void cpw_event_create( pCpw cpw, uint_32 id, bool flag ) 
{
    #ifdef CPW_COMPILEOPT_WINDOWSPECIFICEVENTS

    pCpwWin window = cpw_windowlist_lookup( cpw, id );
    if ( window == 0 ) return;

    if ( window->createCallback ) {
        cpw_window_makecurrent( cpw, id );
        window->createCallback( cpw, id, flag );
    } else
    
    #endif /* CPW_COMPILEOPT_WINDOWSPECIFICEVENTS */

    if ( cpw->createCallback ) {
        CpwCreateCallback callback = (CpwCreateCallback)cpw->createCallback;
        cpw_window_makecurrent( cpw, id );
        callback( cpw, id, flag );
    } else 
        defaultCreateCallback( cpw, id, flag );

    #ifdef DEBUGUSEREVENTS
    if ( flag ) printf( "w create (%u)\n", id ); else printf( "w destroy (%u)\n", id );
    #endif
}

/* send display event helper */

void cpw_event_display( pCpw cpw, uint_32 id ) 
{
    #ifdef CPW_COMPILEOPT_WINDOWSPECIFICEVENTS

    pCpwWin window = cpw_windowlist_lookup( cpw, id );
    if ( window == 0 ) return;

    if ( window->displayCallback ) {
        cpw_window_makecurrent( cpw, id );
        window->displayCallback( cpw, id );
    } else
    
    #endif /* CPW_COMPILEOPT_WINDOWSPECIFICEVENTS */

    if ( cpw->displayCallback ) {
        CpwDisplayCallback callback = (CpwDisplayCallback)cpw->displayCallback;
        cpw_window_makecurrent( cpw, id );
        callback( cpw, id );
    } else 
        defaultDisplayCallback( cpw, id );

    #ifdef DEBUGUSEREVENTS
    printf( "w draw (%u: %dx%d)\n", id, window->width, window->height );
    #endif
}

/* send reshape event helper */

void cpw_event_reshape( pCpw cpw, uint_32 id, uint_32 w, uint_32 h ) 
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );
    if ( window == 0 ) return;

    window->width   = w;
    window->height  = h;

    #ifdef CPW_COMPILEOPT_WINDOWSPECIFICEVENTS

    if ( window->reshapeCallback ) {
        cpw_window_makecurrent( cpw, id );
        window->reshapeCallback( cpw, id, w, h );
    } else
    
    #endif /* CPW_COMPILEOPT_WINDOWSPECIFICEVENTS */

    if ( cpw->reshapeCallback ) {
        CpwReshapeCallback callback = (CpwReshapeCallback)cpw->reshapeCallback;
        cpw_window_makecurrent( cpw, id );
        callback( cpw, id, w, h );
    } else 
        defaultReshapeCallback( cpw, id, w, h );

    #ifdef DEBUGUSEREVENTS
    printf( "w reshape (%u: %dx%d)\n", id, w, h );
    #endif
}

/* send mouseclick event helper */

void cpw_event_mouseclick( pCpw cpw, uint_32 id, uint_32 state, uint_32 button,
                           uint_32 x, uint_32 y ) 
{
    /* check for popup menu attachments */

    pCpwWin window = cpw_windowlist_lookup( cpw, id );
    if ( window == 0 ) return;

    if ( window->buttonmenuid[button] > 0 ) {

        if ( state == CPW_BUTTON_UP ) return;
        
        #ifdef DEBUGUSEREVENTS
        printf( "m click popup (%u)\n", id );
        #endif

        cpw_menus_popupselected( cpw, window, window->buttonmenuid[button], x, y );

        #ifdef DEBUGUSEREVENTS
        printf( "m click popup done (%u)\n", id );
        #endif
        return;
    }

    #ifdef CPW_COMPILEOPT_WINDOWSPECIFICEVENTS

    if ( window->mouseclickCallback ) {
        window->mouseclickCallback( cpw, id, state, button, x, y );
    } else
    
    #endif /* CPW_COMPILEOPT_WINDOWSPECIFICEVENTS */

    /* otherwise, send the event to the application */

    if ( cpw->mouseclickCallback ) {
        CpwMouseClickCallback callback = (CpwMouseClickCallback)cpw->mouseclickCallback;
        callback( cpw, id, state, button, x, y );
    } else 
        defaultMouseClickCallback( cpw, id, state, button, x, y );

    #ifdef DEBUGUSEREVENTS
    printf( "m click (%u)\n", id );
    #endif
}

/* send mouse drag event helper */

void cpw_event_mousedrag( pCpw cpw, uint_32 id, uint_32 button, int_32 x, int_32 y ) 
{
    #ifdef CPW_COMPILEOPT_WINDOWSPECIFICEVENTS

    pCpwWin window = cpw_windowlist_lookup( cpw, id );
    if ( window == 0 ) return;

    if ( window->mousedragCallback ) {
        window->mousedragCallback( cpw, id, button, x, y );
    } else
    
    #endif /* CPW_COMPILEOPT_WINDOWSPECIFICEVENTS */

    if ( cpw->mousedragCallback ) {
        CpwMouseDragCallback callback = (CpwMouseDragCallback)cpw->mousedragCallback;
        callback( cpw, id, button, x, y );
    } else 
        defaultMouseDragCallback( cpw, id, button, x, y );

    #ifdef DEBUGUSEREVENTS
    printf( "m drag (%u)\n", id );
    #endif
}

/* send mouse motion event helper */

void cpw_event_mousemove( pCpw cpw, uint_32 id, uint_32 x, uint_32 y ) 
{
    #ifdef CPW_COMPILEOPT_WINDOWSPECIFICEVENTS

    pCpwWin window = cpw_windowlist_lookup( cpw, id );
    if ( window == 0 ) return;

    if ( window->mousemoveCallback ) {
        window->mousemoveCallback( cpw, id, x, y );
    } else
    
    #endif /* CPW_COMPILEOPT_WINDOWSPECIFICEVENTS */

    if ( cpw->mousemoveCallback ) {
        CpwMouseMoveCallback callback = (CpwMouseMoveCallback)cpw->mousemoveCallback;
        callback( cpw, id, x, y );
    } else 
        defaultMouseMoveCallback( cpw, id, x, y );

    #ifdef DEBUGUSEREVENTS
    /*printf( "m move (%u)\n", id );*/
    #endif
}

/* send keyboard event helper */

void cpw_event_keyboard( pCpw cpw, uint_32 id, uint_32 keycode, bool shift, uint_32 state, 
                         uint_32 x, uint_32 y ) 
{
    #ifdef CPW_COMPILEOPT_WINDOWSPECIFICEVENTS

    pCpwWin window = cpw_windowlist_lookup( cpw, id );
    if ( window == 0 ) return;

    if ( window->keyCallback ) {
        window->keyCallback( cpw, id, 
          cpw_keymouse_translatekeyconstant( keycode, shift ), state, x, y );
    } else
    
    #endif /* CPW_COMPILEOPT_WINDOWSPECIFICEVENTS */

    if ( cpw->keyCallback ) {
        CpwKeyboardCallback callback = (CpwKeyboardCallback)cpw->keyCallback;
        callback( cpw, id, 
            cpw_keymouse_translatekeyconstant( keycode, shift ), state, x, y );
    } else 
        defaultKeyboardCallback( cpw, id, keycode, state, x, y );

    #ifdef DEBUGUSEREVENTS
    printf( "key (%u)\n", id );
    #endif
}

/* send system keyboard event helper */

void cpw_event_systemkeyboard( pCpw cpw, uint_32 id, uint_32 key, uint_32 state, 
                         uint_32 x, uint_32 y ) 
{
    #ifdef CPW_COMPILEOPT_WINDOWSPECIFICEVENTS

    pCpwWin window = cpw_windowlist_lookup( cpw, id );
    if ( window == 0 ) return;

    if ( window->skeyCallback ) {
        window->skeyCallback( cpw, id, key, state, x, y );
    } else
    
    #endif /* CPW_COMPILEOPT_WINDOWSPECIFICEVENTS */

    if ( cpw->skeyCallback ) {
        CpwSystemKeyboardCallback callback = (CpwSystemKeyboardCallback)cpw->skeyCallback;
        callback( cpw, id, key, state, x, y );
    } else 
        defaultSystemKeyboardCallback( cpw, id, key, state, x, y );

    #ifdef DEBUGUSEREVENTS
    printf( "skey (%u)\n", id );
    #endif
}

/* send window positioning event helper */

void cpw_event_position( pCpw cpw, uint_32 id, uint_32 x, uint_32 y ) 
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );
    if ( window == 0 ) return;

    window->x   = x;
    window->y   = y;

    #ifdef CPW_COMPILEOPT_WINDOWSPECIFICEVENTS

    if ( window->positionCallback ) {
        window->positionCallback( cpw, id, x, y );
    } else
    
    #endif /* CPW_COMPILEOPT_WINDOWSPECIFICEVENTS */

    if ( cpw->positionCallback ) {
        CpwPositionCallback callback = (CpwPositionCallback)cpw->positionCallback;
        callback( cpw, id, x, y );
    } else 
        defaultPositionCallback( cpw, id, x, y );

    #ifdef DEBUGUSEREVENTS
    printf( "w position (%u:%dx%d)\n", id, x, y );
    #endif
}

/* send visibility changes event helper */

void cpw_event_visibility( pCpw cpw, uint_32 id, uint_32 state ) 
{
    #ifdef CPW_COMPILEOPT_WINDOWSPECIFICEVENTS

    pCpwWin window = cpw_windowlist_lookup( cpw, id );
    if ( window == 0 ) return;

    if ( window->visibilityCallback ) {
        window->visibilityCallback( cpw, id, state );
    } else
    
    #endif /* CPW_COMPILEOPT_WINDOWSPECIFICEVENTS */

    if ( cpw->visibilityCallback ) {
        CpwVisibilityCallback callback = (CpwVisibilityCallback)cpw->visibilityCallback;
        callback( cpw, id, state );
    } else 
        defaultVisibilityCallback( cpw, id, state );

    #ifdef DEBUGUSEREVENTS
    switch( state ) {
        case CPW_HIDE:
        printf( "w hide (%u) \n", id ); break;
        case CPW_SHOW:
        printf( "w show (%u) \n", id ); break;
        case CPW_GAINEDFOCUS:
        printf( "w gain (%u) \n", id ); break;
        case CPW_LOSTFOCUS:
        printf( "w lost (%u) \n", id ); break;
        case CPW_ICONIC:
        printf( "w iconic (%u) \n", id ); break;
        case CPW_RESTORED:
        printf( "w restore (%u) \n", id ); break;
    }
    #endif
}

/* send mouse entry event helper */

void cpw_event_mouseentry( pCpw cpw, uint_32 id, uint_32 state ) 
{
    #ifdef CPW_COMPILEOPT_WINDOWSPECIFICEVENTS

    pCpwWin window = cpw_windowlist_lookup( cpw, id );
    if ( window == 0 ) return;

    if ( window->mouseentryCallback ) {
        window->mouseentryCallback( cpw, id, state );
    } else
    
    #endif /* CPW_COMPILEOPT_WINDOWSPECIFICEVENTS */

    if ( cpw->mouseentryCallback ) {
        CpwMouseEntryCallback callback = (CpwMouseEntryCallback)cpw->mouseentryCallback;
        callback( cpw, id, state );
    } else 
        defaultMouseEntryCallback( cpw, id, state );

    #ifdef DEBUGUSEREVENTS
    if ( state == CPW_MOUSE_ENTER ) printf( "m enter (%u)\n", id ); 
    else printf( "m leave (%u)\n", id );
    #endif
}

/* menu selected event helper */

void cpw_event_menuselect( pCpw cpw, uint_32 id, uint_32 menuid, uint_32 entryid )
{
    cpw_menus_popupcallback( cpw, id, menuid, entryid );
}

/*************************************************************************/
/*                                                                       */
/*   processing events on the stack                                      */
/*                                                                       */
/*************************************************************************/

/* process the top event on the stack */

bool cpw_event_sendevent( pCpw cpw )
{
    CpwEventStack * es = (CpwEventStack*)cpw->stack;

    eventpurged:

    /* if next event is valid event */

    if ( es->stack[es->nxtindex].used != 0 ) 
    {
        
        /* if next event has been manually purged */

        if ( es->stack[es->nxtindex].filt == 1 ) {

            es->stack[es->nxtindex].used  = false;
            es->stack[es->nxtindex].filt  = false;
            es->stack[es->nxtindex].event = CPW_NO_EVENT;

            #ifdef DEBUGEVENTRAW
            printf( "p%1d:%d/%d\n", es->stack[es->nxtindex].event, es->insindex, es->nxtindex );
            #endif

            es->nxtindex++;

            goto eventpurged;
        }

        switch( es->stack[es->nxtindex].event ) 
        {
            case CPW_NO_EVENT:
            break;

            case CPW_MOUSECLICK_EVENT:
                cpw_event_mouseclick( cpw, es->stack[es->nxtindex].winid, 
                                           es->stack[es->nxtindex].p1, 
                                           es->stack[es->nxtindex].p2, 
                                           es->stack[es->nxtindex].p3, 
                                           es->stack[es->nxtindex].p4 );
            break;

            case CPW_MOUSEMOTION_EVENT:
                cpw_event_mousemove( cpw, es->stack[es->nxtindex].winid, 
                                          es->stack[es->nxtindex].p1, 
                                          es->stack[es->nxtindex].p2 );
            break;

            case CPW_MOUSEDRAG_EVENT:
                cpw_event_mousedrag( cpw, es->stack[es->nxtindex].winid, 
                                          es->stack[es->nxtindex].p1, 
                                          es->stack[es->nxtindex].p2, 
                                          es->stack[es->nxtindex].p3 );
            break;

            case CPW_MOUSEENTRY_EVENT:
                cpw_event_mouseentry( cpw, es->stack[es->nxtindex].winid, 
                                           es->stack[es->nxtindex].p1 );
            break;

            case CPW_KEYBOARD_EVENT:
                cpw_event_keyboard( cpw, es->stack[es->nxtindex].winid, 
                                         es->stack[es->nxtindex].p1, 
                                         es->stack[es->nxtindex].p2, 
                                         es->stack[es->nxtindex].p3, 
                                         es->stack[es->nxtindex].p4,
                                         es->stack[es->nxtindex].p5 );
            break;

            case CPW_SYSKEYBOARD_EVENT:
                cpw_event_systemkeyboard( cpw, es->stack[es->nxtindex].winid, 
                                               es->stack[es->nxtindex].p1, 
                                               es->stack[es->nxtindex].p2, 
                                               es->stack[es->nxtindex].p3, 
                                               es->stack[es->nxtindex].p4 );
            break;

            case CPW_CREATE_EVENT:
                cpw_event_create( cpw, es->stack[es->nxtindex].winid, true );
            break;

            case CPW_DESTROY_EVENT:
                cpw_event_create( cpw, es->stack[es->nxtindex].winid, false );
            break;

            case CPW_POSITION_EVENT:
                if ( es->stack[es->nxtindex+1].event == CPW_POSITION_EVENT ) break;
                cpw_event_position( cpw, es->stack[es->nxtindex].winid, 
                                         es->stack[es->nxtindex].p1, 
                                         es->stack[es->nxtindex].p2 );
            break;

            case CPW_VISIBILITY_EVENT:
                cpw_event_visibility( cpw, es->stack[es->nxtindex].winid, 
                                           es->stack[es->nxtindex].p1 );
            break;

            case CPW_DISPLAY_EVENT:
                cpw_event_display( cpw, es->stack[es->nxtindex].winid );
            break;

            case CPW_RESHAPE_EVENT:
                if ( es->stack[es->nxtindex+1].event == CPW_RESHAPE_EVENT ) break;
                cpw_event_reshape( cpw, es->stack[es->nxtindex].winid, 
                                        es->stack[es->nxtindex].p1, 
                                        es->stack[es->nxtindex].p2 );

            case CPW_MENUSELECT_EVENT:
                cpw_event_menuselect( cpw, es->stack[es->nxtindex].winid,
                                           es->stack[es->nxtindex].p1, 
                                           es->stack[es->nxtindex].p2 );
            break;
        }
        es->stack[es->nxtindex].used  = false;
        es->stack[es->nxtindex].filt  = false;
        es->stack[es->nxtindex].event = CPW_NO_EVENT;

        #ifdef DEBUGEVENTRAW
        printf( "s%1d:%d/%d\n", es->stack[es->nxtindex].event, es->insindex, es->nxtindex );
        #endif

        es->nxtindex++;
    }

    /* pending events? */

    if ( es->stack[es->nxtindex].used != 0 ) return true;
    return false;
}

/* process the top num events on the stack, return false if there are no pending events */

bool cpw_event_sendevents( pCpw cpw, uint_32 count )
{
    while ( count > 0 ) {
        if ( !cpw_event_sendevent( cpw ) ) return false;
        count--;
    }
    return true;
}

/*************************************************************************/
/*                                                                       */
/*   event stack.                                                        */
/*                                                                       */
/*************************************************************************/

/*
    stack[0] = event <-------
    stack[1] = event         | 
    stack[2] = event         |
    stack[3] = event         |
    stack[4] = event         |
    ..                       |
    stack[255] = event   ----
*/

/* quick filter event check for any event insert code */

bool cpw_event_filtered( pCpw cpw, CpwWindowEvent event ) 
{
    CpwEventStack * es = (CpwEventStack*)cpw->stack;
    return es->filter.flag[event];
}

/* insert standard event - returns false if event is filtered */

bool cpw_event_insert( pCpw cpw, uint_32 id, CpwWindowEvent event, 
                       uint_32 p1, uint_32 p2, uint_32 p3, uint_32 p4, uint_32 p5 )
{
    CpwEventStack * es = (CpwEventStack*)cpw->stack;

    if ( es->filter.flag[event] ) return false;

    if ( es->stack[es->insindex].used == 0 ) {

        es->stack[es->insindex].used   = true;
        es->stack[es->insindex].winid  = id;
        es->stack[es->insindex].event  = event;
        es->stack[es->insindex].p1     = p1;
        es->stack[es->insindex].p2     = p2;
        es->stack[es->insindex].p3     = p3;
        es->stack[es->insindex].p4     = p4;
        es->stack[es->insindex].p5     = p5;
        es->insindex++;

        #ifdef DEBUGEVENTRAW
        printf( "r%1d:%d/%d\n", es->stack[es->nxtindex].event, es->insindex, es->nxtindex );
        #endif
    }

    return true;
}

/* insert high priority event */

bool cpw_event_insertnext( pCpw cpw, uint_32 id, CpwWindowEvent event,
                       uint_32 p1, uint_32 p2, uint_32 p3, uint_32 p4, uint_32 p5 )
{
    switch( event ) 
    {
        case CPW_NO_EVENT:
        break;

        case CPW_MOUSECLICK_EVENT:
            cpw_event_mouseclick( cpw, id, p1, p2, p3, p4 );
        break;

        case CPW_MOUSEMOTION_EVENT:
            cpw_event_mousemove( cpw, id, p1, p2 );
        break;

        case CPW_MOUSEDRAG_EVENT:
            cpw_event_mousedrag( cpw, id, p1, p2, p3 );
        break;

        case CPW_MOUSEENTRY_EVENT:
            cpw_event_mouseentry( cpw, id, p1 ); 
        break;

        case CPW_KEYBOARD_EVENT:
            cpw_event_keyboard( cpw, id, p1, p2, p3, p4, p5 );
        break;

        case CPW_SYSKEYBOARD_EVENT:
            cpw_event_systemkeyboard( cpw, id, p1, p2, p3, p4 );
        break;

        case CPW_CREATE_EVENT:
            cpw_event_create( cpw, id, true );
        break;

        case CPW_DESTROY_EVENT:
            cpw_event_create( cpw, id, false );
        break;

        case CPW_POSITION_EVENT:
            cpw_event_position( cpw, id, p1, p2 );
        break;

        case CPW_VISIBILITY_EVENT:
            cpw_event_visibility( cpw, id, p1 ); 
        break;

        case CPW_DISPLAY_EVENT:
            cpw_event_display( cpw, id );
        break;

        case CPW_RESHAPE_EVENT:
            cpw_event_reshape( cpw, id, p1, p2 ); 
        break;
    }
    return true;
}

/*************************************************************************/
/*                                                                       */
/*   localhost window events interface                                   */
/*                                                                       */
/*************************************************************************/

/* the localhost adapter calls this api to inject events into the event stack */

void cpw_hostevent_setfocus( pCpw cpw, uint_32 id ) /* win32 */
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );
    if ( window == 0 ) return;

    cpw->win_foregroundid = id;

    cpw->win_currentid = 0;
    cpw_localhost_makecurrent( cpw, window->plhwc );

    cpw_event_insert( cpw, id, CPW_VISIBILITY_EVENT, CPW_GAINEDFOCUS, 0, 0, 0, 0 );
    return;
}

void cpw_hostevent_lostfocus( pCpw cpw, uint_32 id ) 
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );
    if ( window == 0 ) return;
    if ( cpw->win_foregroundid == id ) 
        cpw->win_foregroundid = 0;

    if ( window->fullscreen == true )
        cpw_localhost_inconifywindow( window );         

    cpw_event_insert( cpw, id, CPW_VISIBILITY_EVENT, CPW_LOSTFOCUS, 0, 0, 0, 0 );
    return;
}

void cpw_hostevent_cursorenter( pCpw cpw, uint_32 id ) 
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );
    if ( window == 0 ) return;
    if ( window->cursorpresent == true ) return;
    window->cursorpresent = true;
    cpw_localhost_setcursor( cpw, window );
    cpw_event_insert( cpw, id, CPW_MOUSEENTRY_EVENT, CPW_MOUSE_ENTER, 0, 0, 0, 0 );
    return;
}

void cpw_hostevent_cursorleft( pCpw cpw, uint_32 id ) 
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );
    if ( window == 0 ) return;
    if ( window->cursorpresent == false ) return;
    window->cursorpresent = false;
    cpw_localhost_restorecursor( cpw );
    cpw_event_insert( cpw, id, CPW_MOUSEENTRY_EVENT, CPW_MOUSE_LEAVE, 0, 0, 0, 0 );
    return;
}

void cpw_hostevent_draw( pCpw cpw, uint_32 id ) 
{
    /* post draw events directly to the window */

    cpw_event_insertnext( cpw, id, CPW_DISPLAY_EVENT, 0, 0, 0, 0, 0 );
}

void cpw_hostevent_reshape( pCpw cpw, uint_32 id, uint_32 width, uint_32 height ) 
{
    /* note: if we use the indirect events (event stack inserts) instead
       of the direct reshape/redraw usage we get the 'GLUT reshape issue'
       on win32. I need to do some work on the win32 adapter to fix this...
       and then i'll make the default method indirect. */

    cpw_event_insertnext( cpw, id, CPW_RESHAPE_EVENT, width, height, 0, 0, 0 );
    cpw_event_insertnext( cpw, id, CPW_DISPLAY_EVENT, 0, 0, 0, 0, 0 );
}

void cpw_hostevent_destroy( pCpw cpw, uint_32 id )
{
    cpw_event_insert( cpw, id, CPW_DESTROY_EVENT, 0, 0, 0, 0, 0 );
}

void cpw_hostevent_position( pCpw cpw, uint_32 id, uint_32 x, uint_32 y )
{
    cpw_event_insert( cpw, id, CPW_POSITION_EVENT, x, y, 0, 0, 0 );
}

void cpw_hostevent_visibility( pCpw cpw, uint_32 id, uint_32 state )
{
    cpw_event_insert( cpw, id, CPW_VISIBILITY_EVENT, state, 0, 0, 0, 0 );
}

void cpw_hostevent_mouseclick( pCpw cpw, uint_32 id, uint_32 state, uint_32 button, uint_32 x, uint_32 y )
{
    cpw_event_insert( cpw, id, CPW_MOUSECLICK_EVENT, state, button, x, y, 0 );
}

void cpw_hostevent_mousedrag( pCpw cpw, uint_32 id, uint_32 button, int_32 x, int_32 y )
{
    cpw_event_insert( cpw, id, CPW_MOUSEDRAG_EVENT, button, x, y, 0, 0 );
}

void cpw_hostevent_mousemove( pCpw cpw, uint_32 id, uint_32 x, uint_32 y )
{
    cpw_event_insert( cpw, id, CPW_MOUSEMOTION_EVENT, x, y, 0, 0, 0 );
}

void cpw_hostevent_keyboard( pCpw cpw, uint_32 id, uint_32 key, bool shift, uint_32 state, uint_32 x, uint_32 y )
{
    cpw_event_insert( cpw, id, CPW_KEYBOARD_EVENT, key, shift, state, x, y );
}

void cpw_hostevent_systemkeyboard( pCpw cpw, uint_32 id, uint_32 key, uint_32 state, uint_32 x, uint_32 y )
{
    cpw_event_insert( cpw, id, CPW_SYSKEYBOARD_EVENT, key, state, x, y, 0 );
}

void cpw_hostevent_menuselect( pCpw cpw, uint_32 id, uint_32 menuid, uint_32 entryid )
{
    cpw_event_insert( cpw, id, CPW_MENUSELECT_EVENT, menuid, entryid, 0, 0, 0 );
}

