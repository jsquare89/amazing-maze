/***************************************************************************/
/*                                                                         */
/*  cpw_window.c                                                           */
/*                                                                         */
/*    Window management and adapter event interface.                       */
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

#include "cpw_window.h"
#include "cpw_windowlist.h"
#include "cpw_event.h"
#include "cpw_main.h"
#include "cpw_error.h"
#include CPW_LOCALHOST_H

/*************************************************************************/
/*                                                                       */
/*   init and exit.                                                      */
/*                                                                       */
/*************************************************************************/

/* init */

bool cpw_window_init( pCpw cpw )
{
    if ( cpw_windowlist_init( cpw ) == 0 ) { return false; }
    return true;
}

/* send a close message to all open windows */

void cpw_window_close( pCpw cpw )
{
    cpw_window_closeall( cpw );
}

/* exit */

void cpw_window_exit( pCpw cpw )
{
    cpw_window_destroyall( cpw );
    cpw_windowlist_exit( cpw );
}

/*************************************************************************/
/*                                                                       */
/*   internal window management.                                         */
/*                                                                       */
/*************************************************************************/

/* create a new window. returns 0 on failure */

uint_32 cpw_window_create( pCpw cpw, char* title, uint_32 x, uint_32 y, 
                            uint_32 width, uint_32 height )
{
    CpwWindowStruct * window;

    window = (CpwWindowStruct *) cpwmalloc( sizeof( CpwWindowStruct ) );

    if ( !window ) {
        cpw_error_set( cpw, cpw_error_outofmemory );
        return 0;
    }

    memset( window, 0, sizeof( CpwWindowStruct ) );

    /* init basic window properties */

    window->x            = x;
    window->y            = y;
    window->width        = width;
    window->height       = height;
    window->cursor       = CursorArrow;
    window->fullscreen   = false;
    window->bx         = window->x;
    window->by         = window->y;
    window->bwidth     = window->width;
    window->bheight    = window->height;

    window->id = cpw_windowlist_insert( cpw, window );

    /* localhost calls set the error info on failure */

    window->plhwc = cpw_localhost_createwindow( cpw, window->id, title, 
                    x, y, width, height, 
                    cpw->win_properties, cpw->win_expectmenu );

    if ( window->plhwc == 0 )
        return 0;

    /* init opengl for this window */

    if ( cpw_localhost_setpixelformat( cpw, window->plhwc ) == false )
        return 0;

    if ( cpw_localhost_createglcontext( cpw, window->plhwc ) == false )
        return 0;

    /* set to window to foreground */

    cpw_localhost_setforeground( window );
    cpw->win_foregroundid = window->id;

    /* make this windows rendering context current */

    cpw->win_currentid = 0;
    cpw_window_makecurrent( cpw, window->id );

    /* save the window's title */

    setString( &window->title, title );

    /* inject first three events a window receives into the stack */

    cpw_event_insert( cpw, window->id, CPW_CREATE_EVENT, 0, 0, 0, 0, 0 );
    cpw_event_insert( cpw, window->id, CPW_POSITION_EVENT, x, y, 0, 0, 0 );
    cpw_event_insert( cpw, window->id, CPW_RESHAPE_EVENT, width, height, 0, 0, 0 );
    cpw_event_insert( cpw, window->id, CPW_DISPLAY_EVENT, 0, 0, 0, 0, 0 );

    /* return the id */

    return window->id;
}

uint_32 cpw_window_createfullscreen( pCpw cpw )
{
    CpwWindowStruct * window;

    window = (CpwWindowStruct *) cpwmalloc( sizeof( CpwWindowStruct ) );

    if ( !window ) {
        cpw_error_set( cpw, cpw_error_outofmemory );
        return 0;
    }

    memset( window, 0, sizeof( CpwWindowStruct ) );

    /* init fullscreen window properties */

    window->x          = 0;
    window->y          = 0;
    window->width      = cpw->cpw_screenwidth;
    window->height     = cpw->cpw_screenheight;
    window->cursor     = CursorNone;
    window->fullscreen = true;
    window->bx         = window->x;
    window->by         = window->y;
    window->bwidth     = window->width;
    window->bheight    = window->height;

    window->id = cpw_windowlist_insert( cpw, window );

    /* localhost calls set the error info on failure */

    window->plhwc = cpw_localhost_createfullscreenwindow( cpw, window->id, "fullscreen" );

    if ( window->plhwc == 0 )
        return 0;

    if ( cpw_localhost_setpixelformat( cpw, window->plhwc ) == false )
        return 0;

    if ( cpw_localhost_createglcontext( cpw, window->plhwc ) == false )
        return 0;

    /* set to foreground */

    cpw_localhost_setforeground( window );
    cpw->win_foregroundid = window->id;

    cpw->win_currentid = 0;
    cpw_window_makecurrent( cpw, window->id );

    setString( &window->title, "fullscreen" );

    cpw_event_insert( cpw, window->id, CPW_CREATE_EVENT, 0, 0, 0, 0, 0 );
    cpw_event_insert( cpw, window->id, CPW_RESHAPE_EVENT, cpw->cpw_screenwidth, cpw->cpw_screenheight, 0, 0, 0 );
    cpw_event_insert( cpw, window->id, CPW_DISPLAY_EVENT, 0, 0, 0, 0, 0 );

    /* return the id */

    return window->id;
}


/* destroy a window and it's resources */

bool cpw_window_destroy( pCpw cpw, pCpwWin window )
{
    freeStr( &window->title );
    cpw_localhost_destroyglcontext( cpw, window->plhwc );
    cpw_localhost_destroywindow( cpw, window );
    cpwfree( window );
    return true;
}

/* send close message to all open windows */

bool cpw_window_closeall( pCpw cpw )
{
    pCpwWin window;

    window = cpw_windowlist_iteratestart( cpw );

    if ( window == 0 ) return true;

    while ( window != 0 ) {
        cpw_event_insert( cpw, window->id, CPW_DESTROY_EVENT, 0, 0, 0, 0, 0 );
        window = cpw_windowlist_iteratenext( cpw );
    }

    return true;
}

/* destroy all open windows and their resources */

bool cpw_window_destroyall( pCpw cpw )
{
    pCpwWin window;

    window = cpw_windowlist_iteratestart( cpw );

    if ( window == 0 ) return true;

    while ( window != 0 ) {
        cpw_window_destroy( cpw, window );
        window = cpw_windowlist_iteratenext( cpw );
    }

    /* windowlist is deleted in windowlist_exit */

    return true;
}

/* make a window's context current for rendering */

bool cpw_window_makecurrent( pCpw cpw, uint_32 id )
{
    pCpwWin window;

    #ifdef CPW_COMPILEOPT_CURRENTCONTEXTCACHING

    if ( cpw->win_currentid == id ) return true;

    #endif

    window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) return false;

    cpw->win_currentid = id;

    cpw_localhost_makecurrent( cpw, window->plhwc );

    return true;
}

/*************************************************************************/
/*                                                                       */
/*   window api                                                          */
/*                                                                       */
/*************************************************************************/

/* creation */

uint_32 
cpwCreateWindow( pCpw cpw, char * title )
{
    uint_32 id = cpw_window_create( cpw, title, cpw->win_initx, cpw->win_inity, cpw->win_initwidth, cpw->win_initheight );
    return id;    
}

/* creation */

uint_32
cpwCreateWindowEx( pCpw cpw, char * title, uint_32 x, uint_32 y, uint_32 width, uint_32 height )
{
    uint_32 id = cpw_window_create( cpw, title, x, y, width, height );
    return id;    
}

/* create a brand spankin new fullscreen window */

uint_32 cpwCreateFullscreenWindow( pCpw cpw )
{
    if ( !cpw_window_createfullscreen( cpw ) )
        return false;

    return true;
}

/* close and destroy */

bool
cpwDestroyWindow( pCpw cpw, uint_32 id )
{
    bool res; 

    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    cpw_windowlist_remove( cpw, id );

    res = cpw_window_destroy( cpw, window ); 

    #ifdef CPW_COMPILEOPT_SHUTDOWNONFIRSTWINDOW

    /* shutdown the application on first window close */

    if ( id == 1 ) cpwBreakMainLoop( cpw );

    #endif

    return res;
}

/* set the title */

bool 
cpwSetWindowTitle( pCpw cpw, char * title, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    setString( &window->title, title );
    return cpw_localhost_setwindowtitle( window ); 
}

/* position on the desktop */

bool 
cpwPositionWindow( pCpw cpw, uint_32 x, uint_32 y, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    window->x = x;
    window->y = y;

    cpw_event_insert( cpw, window->id, CPW_POSITION_EVENT, window->x, window->y, 0, 0, 0 );
    cpw_event_insert( cpw, id, CPW_DISPLAY_EVENT, 0, 0, 0, 0, 0 );

    return cpw_localhost_positionwindow( window ); 
}

/* resize the window frame */

bool 
cpwReshapeWindow( pCpw cpw, uint_32 width, uint_32 height, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    window->width = width;
    window->height = height;

    cpw_event_insert( cpw, id, CPW_RESHAPE_EVENT, width, height, 0, 0, 0 );
    cpw_event_insert( cpw, id, CPW_DISPLAY_EVENT, 0, 0, 0, 0, 0 );

    return cpw_localhost_reshapewindow( window ); 
}

/* convert to a fullscreen window to a normal window */

bool cpwStandardWindow( pCpw cpw, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    if ( window->fullscreen == false ) return true;

    if ( !cpw_localhost_standardizewindow( cpw, window ) )
        return false;

    /* restore old dimensions */

    window->x          = window->bx;
    window->y          = window->by;
    window->width      = window->bwidth;
    window->height     = window->bheight;

    window->fullscreen = false;

    /* set to window to foreground */

    cpwSetForegroundWindow( cpw, id );

    cpw_localhost_positionwindow( window ); 
    cpw_localhost_reshapewindow( window ); 

    /* inject resize and position events */

    cpw_event_insert( cpw, window->id, CPW_RESHAPE_EVENT, window->width, window->height, 0, 0, 0 );
    cpw_event_insert( cpw, id, CPW_DISPLAY_EVENT, 0, 0, 0, 0, 0 );

    return true;

}

/* convert to an existing window to a fullscreen window */

bool cpwFullscreenWindow( pCpw cpw, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );
    
    if ( window == 0 ) return false;

    if ( window->fullscreen == true ) return true;

    /* save the old dimensions */

    window->bx         = window->x;
    window->by         = window->y;
    window->bwidth     = window->width;
    window->bheight    = window->height;

    if ( !cpw_localhost_fullscreenwindow( cpw, window ) )
        return false;

    window->fullscreen = true;

    /* set to window to foreground */

    cpwSetForegroundWindow( cpw, id );

    /* get the new dimensions */

    cpw_localhost_windowinfo( window );

    /* inject resize events */

    cpw_event_insert( cpw, id, CPW_RESHAPE_EVENT, cpw->cpw_screenwidth, cpw->cpw_screenheight, 0, 0, 0 );
    cpw_event_insert( cpw, id, CPW_DISPLAY_EVENT, 0, 0, 0, 0, 0 );

    return true;
}

/* maximize a window */

bool cpwMaximizeWindow( pCpw cpw, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    /* save the old dimensions */

    window->bx         = window->x;
    window->by         = window->y;
    window->bwidth     = window->width;
    window->bheight    = window->height;

    if ( !cpw_localhost_maximizewindow( window ) ) {
        return false;
    }

    /* get the new dimensions */

    cpw_localhost_windowinfo( window );

    cpw_event_insert( cpw, id, CPW_DISPLAY_EVENT, 0, 0, 0, 0, 0 );

    return true; 
}

/* iconify the window to the task bar */

bool 
cpwIconifyWindow( pCpw cpw, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    /* save the old dimensions */

    window->bx         = window->x;
    window->by         = window->y;
    window->bwidth     = window->width;
    window->bheight    = window->height;

    return cpw_localhost_inconifywindow( window ); 
}

/* restore an iconic or maximized window */

bool 
cpwRestoreWindow( pCpw cpw, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    cpw_localhost_restorewindow( window );

    /* restore old dimensions */

    window->x          = window->bx;
    window->y          = window->by;
    window->width      = window->bwidth;
    window->height     = window->bheight;

    //cpw_localhost_positionwindow( window ); 
    //cpw_localhost_reshapewindow( window ); 

    cpw_event_insert( cpw, window->id, CPW_POSITION_EVENT, window->x, window->y, 0, 0, 0 );
    cpw_event_insert( cpw, window->id, CPW_RESHAPE_EVENT, window->width, window->height, 0, 0, 0 );
    cpw_event_insert( cpw, id, CPW_DISPLAY_EVENT, 0, 0, 0, 0, 0 );

    return true;
}

/* get the foreground window id */

uint_32
cpwGetWindow( pCpw cpw )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, cpw->win_foregroundid );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return 0;
    }

    return window->id;
}

/* set the window's rendering context current */

bool 
cpwSetWindow( pCpw cpw, uint_32 id )
{
    return cpw_window_makecurrent( cpw, id );
}

/* move the window to the foreground */

bool 
cpwSetForegroundWindow( pCpw cpw, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    if ( cpw_localhost_setforeground( window ) ) {
        cpw->win_foregroundid = window->id;
        return true;
    }

    cpw_event_insert( cpw, id, CPW_DISPLAY_EVENT, 0, 0, 0, 0, 0 );

    return false;
}

/* pop the window below this one up to the foreground */

bool
cpwPopWindow( pCpw cpw )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, cpw->win_foregroundid );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    return cpw_localhost_popwindow( window );
}

/* push the window below by one in the z-order */

bool 
cpwPushWindow( pCpw cpw )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, cpw->win_foregroundid );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    return cpw_localhost_pushwindow( window );
}

/* hide a window completely from view */

bool 
cpwHideWindow( pCpw cpw, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    return cpw_localhost_hidewindow( window ); 
}

/* restore a hidden window */

bool 
cpwShowWindow( pCpw cpw, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    return cpw_localhost_showwindow( window ); 
}

/* post a paint message to all windows */

bool 
cpwPostRedisplay( pCpw cpw )
{
    pCpwWin window;

    window = cpw_windowlist_iteratestart( cpw );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    while ( window != 0 ) {
        cpw_event_insert( cpw, window->id, CPW_DISPLAY_EVENT, 0, 0, 0, 0, 0 );
        window = cpw_windowlist_iteratenext( cpw );
    }

    return true;
}

/* post a paint message to a particular window */

bool 
cpwPostWindowRedisplay( pCpw cpw, uint_32 id )
{
    /*  Depending on whether or not you care about accurate event order. 
        Sending the display event directly increases performance slightly
        but the event will not be in it's 'proper order' with respect to 
        other events. Be careful with this mode, sometimes you will get a draw
        event before the initial reshape event. */

    /* 'correct ordering' */
    return cpw_event_insert( cpw, id, CPW_DISPLAY_EVENT, 0, 0, 0, 0, 0 );

    /* 'direct mode' */
    /* return cpw_event_insertnext( cpw, id, CPW_DISPLAY_EVENT, 0, 0, 0, 0 ); */
}

/* swap all double buffered windows */

bool 
cpwSwapBuffers( pCpw cpw )
{
    pCpwWin window;
    bool res = true;

    window = cpw_windowlist_iteratestart( cpw );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    while ( window != 0 ) {
        res = res & cpw_localhost_swapbuffers( window->plhwc );
        window = cpw_windowlist_iteratenext( cpw );
    }

    return res;
}

/* swap a particular double buffered window */

bool 
cpwSwapWindowBuffers( pCpw cpw, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    return cpw_localhost_swapbuffers( window->plhwc );
}

/* set a store the cursor to be used when the mouse is over the window */

bool 
cpwSetCursor( pCpw cpw, CpwCursor cursor, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    if ( cpw->win_foregroundid != (uint_32)id ) return false;
    if ( window->cursorpresent == false ) return false;
    window->cursor = cursor;
    cpw_localhost_setcursor( cpw, window );
    return false;
}

/* center the cursor in the center of the windows client area. */
/* the window must be the foreground window */

bool 
cpwCenterCursor( pCpw cpw, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    if ( cpw->win_foregroundid != (uint_32)id ) return false;
    if ( window->cursorpresent == false ) return false;
    cpw_localhost_windowinfo( window );
    return cpw_localhost_centercursor( window );
}

/* position the cursor in the windows client area. */
/* the window must be the foreground window */

bool 
cpwPositionCursor( pCpw cpw, uint_32 x, uint_32 y, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    if ( cpw->win_foregroundid != (uint_32)id ) return false;
    if ( window->cursorpresent == false ) return false;
    cpw_localhost_windowinfo( window );
    return cpw_localhost_positioncursor( window, x, y );
}

/* generate a CpwWindowList containing information about all windows */

bool cpwListWindows( pCpw cpw, CpwWindowList * list )
{
    pCpwWin window;
    uint_32 count = 0;

    if ( list == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }

    memset( list, 0, sizeof( CpwWindowList ) );

    window = cpw_windowlist_iteratestart( cpw );

    if ( window == 0 ) {
        list->size = 0;
        return true;
    }

    while ( window != 0 ) {
        cpw_localhost_windowinfo( window );
        list->list[count].id     = (uint_16)window->id;
        list->list[count].x      = (uint_16)window->x;
        list->list[count].y      = (uint_16)window->y;
        list->list[count].width  = (uint_16)window->width;
        list->list[count].height = (uint_16)window->height;
        list->list[count].fullscreen = window->fullscreen;
        
        if ( window->id == cpw->win_foregroundid ) 
            list->list[count].foreground = true;
        else 
            list->list[count].foreground = false;

        window = cpw_windowlist_iteratenext( cpw );
        count++;
        if ( count == CPW_MAX_WINLIST ) break;
    }

    list->size = count;
    return true;
}

/* generate a CpwWindowInfo containing information about a particular window */

bool cpwGetWindowInfo( pCpw cpw, CpwWindowInfo * info, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );
    if ( window == 0 ) return false;

    if ( info == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }

    cpw_localhost_windowinfo( window );

    info->id     = (uint_16)window->id;
    info->x      = (uint_16)window->x;
    info->y      = (uint_16)window->y;
    info->width  = (uint_16)window->width;
    info->height = (uint_16)window->height;
    info->fullscreen = window->fullscreen;

    if ( window->id == cpw->win_foregroundid ) 
        info->foreground = true;
    else 
        info->foreground = false;
    return true;
}

/*************************************************************************/
/*                                                                       */
/*   user window context                                                 */
/*                                                                       */
/*************************************************************************/

/* The user context can contain anything. It is stored as a void* pointer
   in the window context. */

/* set the context for a particular window */

bool  cpwSetWindowUserdata( pCpw cpw, pVoid userdata, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    window->userdata = userdata;
    return true;
}

/* retrieve the context for a particular window */

pVoid cpwGetWindowUserdata( pCpw cpw, uint_32 id )
{
    pCpwWin window = cpw_windowlist_lookup( cpw, id );

    if ( window == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return false;
    }

    return window->userdata;
}
