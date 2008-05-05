/***************************************************************************/
/*                                                                         */
/*  cpw_win32.c                                                            */
/*                                                                         */
/*    The Cpw library interface to Windows.                                */
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
/*  File Platform: win32                                                   */
/*                                                                         */
/***************************************************************************/

#include "cpw_win32.h"
#include "cpw_event.h"
#include "cpw_error.h"
#include "cpw_init.h"
#include "cpw_main.h"
#include "cpw_windowlist.h"
#include "cpw_joystick.h"

/* out of all the code in Cpw, this is where things can sometimes get ugly.
   please comment your code clearly, and in detail, so the next guy doesn't
   have to sift through a rats nest. thanks! */

/* #define DEBUGOPENGLFORMATS - define if you want the pixel formats dumped to printhandler. */

/* #define DEBUGJOYSTICKS */

/*************************************************************************/
/*                                                                       */
/*   init and exit.                                                      */
/*                                                                       */
/*************************************************************************/

/* init - whatever needs to be done for this platform. This function 
   should create a CpwLocalhostContext and store anything in it it needs. 
   CpwLocalhostContext is defined in the .h. Cpw stores it in it's state
   as a pointer but doesn't do anything with it. You can access it in 
   subsequent calls at cpw->ctx_localhost.  */

LONG WINAPI cpw_localhost_internal_WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

/* used in creating a unique class name for each Cpw state that gets initialized */

static uint_32 classregistercount = 1;

bool cpw_localhost_init( pCpw cpw )
{
    WNDCLASSEX wcex;
    CpwLocalhostContext lhc;
    HINSTANCE hInstance = GetModuleHandle(NULL);

    /* clear mem in our local localhost context */

    memset(&lhc, 0, sizeof( CpwLocalhostContext ) );

    /* register the window class for Cpw */

    memset(&wcex, 0, sizeof(WNDCLASSEX));

    sprintf( lhc.classname, "%s%d", CPW_LOCALHOST_WIN32_CLASSNAME, classregistercount );
    classregistercount++;

    wcex.cbSize           = sizeof(WNDCLASSEX);
    wcex.style            = CS_OWNDC;
    wcex.lpfnWndProc      = (WNDPROC)cpw_localhost_internal_WindowProc;
    wcex.hInstance        = hInstance;
    wcex.cbClsExtra       = 32;
    wcex.cbWndExtra       = 32;
    wcex.hIcon            = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground    = NULL;
    wcex.lpszMenuName     = NULL;
    wcex.lpszClassName    = lhc.classname;

    if( !RegisterClassEx( &wcex ) ) {
        cpw_error_set( cpw, cpw_error_initfailed );
        return false;
    }

    /* initialize values for cpw that the localhost knows about */

    cpw->cpw_screenwidth    = GetSystemMetrics(SM_CXSCREEN);
    cpw->cpw_screenheight   = GetSystemMetrics(SM_CYSCREEN);

    /* save our instance handle */

    lhc.moduleInstance = hInstance;

    /* allocate a localhost context for the state */

    cpw->ctx_localhost = (pVoid) cpwmalloc( sizeof( CpwLocalhostContext ) );

    if ( cpw->ctx_localhost == 0 ) {
        cpw_error_set( cpw, cpw_error_outofmemory );
        return false;
    }

    /* copy over the localhost state context data */

    memcpy( cpw->ctx_localhost, &lhc, sizeof( CpwLocalhostContext ) ); 

    return true;
}

/* exit localhost. all windows will be destroyed by cpw prior to 
   this call. make sure and free your CpwLocalhostContext memory
   here. */

void cpw_localhost_exit( pCpw cpw )
{
    CpwLocalhostContext* plhc = cpw->ctx_localhost;

    /* release the di COM interface if it's been created */

    #if defined(CPW_DIRECTINPUT_MOUSEACCESS) | defined(CPW_DIRECTINPUT_JOYSTICKACCESS)
    if ( plhc->pdi != 0 ) IDirectInput2_Release( plhc->pdi ); 
    #endif

    /* very important - some gl drivers don't free resources 
       until this is called */

    UnregisterClass( plhc->classname, plhc->moduleInstance );

    /* free a font filename from a fontlist if it exists */

    freeStr( &plhc->fontfile );

    /* free the localhost context memory */

    cpwfree( plhc );
    cpw->ctx_localhost = 0;
}

/*************************************************************************/
/*                                                                       */
/*   windows                                                             */
/*                                                                       */
/*************************************************************************/

/* create a window and return a CpwLocalhostWindow struct pointer for it. 
   pCpwLhwc's are defined in the .h and can contain anything. Cpw
   stores them as a void* pointers and doesn't do anything with em. */

pCpwLhwc
cpw_localhost_createwindow( pCpw cpw, uint_32 id, 
                            char* title, 
                            uint_32 x, uint_32 y, 
                            uint_32 width, uint_32 height,
                            uint_32 properties, bool expectmenu )
{
    HWND      hwnd;
    pCpwLhc   plhc;
    pCpwLhwc  plhwc;
    RECT      rect;
    DWORD     wintype;
    HMENU     hmenu;

    plhc = ( pCpwLhc ) cpw->ctx_localhost;

    wintype = 0;

    /* set window style properties */

    if ( properties & CPW_WINDOWPROP_STANDARD ) {
        wintype = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
            | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
    } else if ( properties & CPW_WINDOWPROP_POPUP ) {
        wintype = WS_POPUP;
    } else if ( properties & CPW_WINDOWPROP_NODRESSING ) {
        wintype = WS_OVERLAPPED | WS_CAPTION;
    } else {
        wintype = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
            | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
    }

    /* set window border style properties */

    if ( properties & CPW_WINDOWPROP_THICKBORDER ) {
        wintype = wintype | WS_THICKFRAME;
    } else if ( properties & CPW_WINDOWPROP_THINBORDER ) {
        wintype = wintype | WS_BORDER;
    } else if ( properties & CPW_WINDOWPROP_NOBORDER ) {
    } else {
        wintype = wintype | WS_THICKFRAME;
    }

    /* x and y are the window's position, width and height are client are sizes */

    /* we need to compute the total window width and height (used by createwindow) */

    rect.left   = 0;
    rect.top    = 0;
    rect.right  = width;
    rect.bottom = height;

    /* printf( "in: x:%d y:%d w:%d h:%d\n", rect.left, rect.top, rect.right, rect.bottom ); */

    AdjustWindowRect( &rect, wintype, expectmenu );

    rect.right = rect.right+abs(rect.left);
    rect.bottom = rect.bottom+abs(rect.top);

    rect.left   = x;
    rect.top    = y;

    /* printf( "out: x:%d y:%d w:%d h:%d\n", rect.left, rect.top, rect.right, rect.bottom ); */

    /* add empty menu */

    if ( expectmenu ) {

        MENUITEMINFO info;
        hmenu = 0;

        /* add a default empty menu */

        hmenu = CreateMenu();
        memset( &info, 0, sizeof( info ) );
        info.cbSize = sizeof( info );
        info.fMask = MIIM_ID | MIIM_STATE | MIIM_TYPE;
        info.fType = MFT_STRING;
        info.dwTypeData = " ";
        info.cch = strlen( " " );
        InsertMenuItem( hmenu, 1, TRUE, &info );

    } else {
        hmenu = 0;
    }

    hwnd = CreateWindow(
            plhc->classname,               /* pointer to registered class name */
            title,                         /* pointer to window name */
            wintype,                       /* window style */
            rect.left,                     /* horizontal position of window */
            rect.top,                      /* vertical position of window */
            rect.right,                    /* window width */
            rect.bottom,                   /* window height */
            0,                             /* handle to parent or owner window */
            hmenu,                         /* handle to menu */
            plhc->moduleInstance,          /* handle to application instance */
            0                              /* pointer to window-creation data */
    );

    if ( hwnd == 0 ) {
        cpw_error_set( cpw, cpw_error_createwindowfailed );
        return 0;
    }

    /* store the cpw context pointer with the class */

    SetClassLongPtr( hwnd, 0, (LONG_PTR) cpw );

    /* store the cpw window id with the window */

    SetWindowLongPtr( hwnd, 0, (LONG_PTR) id );

    /* create localhost window context for this window */

    plhwc = ( pCpwLhwc ) cpwmalloc( sizeof( CpwLocalhostWindow ) );

    if ( plhwc == 0 ) {
        cpw_error_set( cpw, cpw_error_outofmemory );
        return 0;
    }

    plhwc->hwnd     = hwnd;
    plhwc->hdc      = GetDC( hwnd );
    plhwc->hmenu    = hmenu;
    plhwc->winstyle = wintype;
    plhwc->updates  = true;

    /* ToDo: add sporty AnimateWindow stuff for os >= XP */

    ShowWindow( hwnd, SW_SHOW );
    SetForegroundWindow( hwnd );

    return plhwc;
}

pCpwLhwc
cpw_localhost_createfullscreenwindow( pCpw cpw, uint_32 id, char* title )
{
    HWND     hwnd;
    pCpwLhc  plhc;
    pCpwLhwc plhwc;

    plhc = ( pCpwLhc ) cpw->ctx_localhost;
        
    hwnd = CreateWindowEx(
            WS_EX_TOPMOST,                 /* Extended window style */
            plhc->classname,               /* pointer to registered class name */
            title,                         /* pointer to window name */
            WS_MAXIMIZE | WS_POPUP,        /* window style */
            0,                             /* horizontal position of window */
            0,                             /* vertical position of window */
            cpw->cpw_screenwidth,          /* window width */
            cpw->cpw_screenheight,         /* window height */
            0,                             /* handle to parent or owner window */
            0,                             /* handle to menu or child-window identifier */
            plhc->moduleInstance,          /* handle to application instance */
            0                              /* pointer to window-creation data */
    );

    if ( hwnd == 0 ) {
		{ uint_32 i = GetLastError(); 
        cpw_error_set( cpw, cpw_error_createwindowfailed );
		}
        return 0;
    }

    /* store the cpw context pointer with the class */

    SetClassLongPtr( hwnd, 0, (LONG_PTR) cpw );

    /* store the cpw window id with the window */

    SetWindowLongPtr( hwnd, 0, (LONG_PTR) id );

    /* create localhost window context for this window */

    plhwc = ( pCpwLhwc ) cpwmalloc( sizeof( CpwLocalhostWindow ) );

    if ( plhwc == 0 ) {
        cpw_error_set( cpw, cpw_error_outofmemory );
        return 0;
    }

    plhwc->hwnd = hwnd;
    plhwc->hdc = GetDC( hwnd );
    plhwc->updates  = true;

    ShowWindow( hwnd, SW_SHOW );
    SetForegroundWindow( hwnd );

    return plhwc;
}

/* convert a regular window to fullscreen mode */

bool cpw_localhost_fullscreenwindow( pCpw cpw, pCpwWin wc )
{
    pCpwLhwc lhwc = wc->plhwc;

    ShowWindow( lhwc->hwnd, SW_HIDE );

    if ( !SetWindowLong( lhwc->hwnd, GWL_STYLE, WS_POPUP ) ) {
        /* what errors could possibly happen here? */
        return false;
    }

    SetWindowPos( lhwc->hwnd, 0, wc->x, wc->y, wc->width, wc->height, 
          SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED );

    ShowWindow( lhwc->hwnd, SW_MAXIMIZE );

    SetForegroundWindow( lhwc->hwnd );
    
    return true;
}

/* convert a fullscreen window to regular one */

bool cpw_localhost_standardizewindow( pCpw cpw, pCpwWin wc )
{
    pCpwLhwc lhwc = wc->plhwc;

    if ( !SetWindowLong( lhwc->hwnd, GWL_STYLE, lhwc->winstyle ) ) {
        return false;
    }

    ShowWindow( lhwc->hwnd, SW_RESTORE );

    return true;
}

/* destroy the window specified */

bool cpw_localhost_destroywindow( pCpw cpw, pCpwWin wc )
{
    pCpwLhwc lhwc = wc->plhwc;
    DestroyWindow( lhwc->hwnd );
    return true;
}

/* set the title bar text */

bool cpw_localhost_setwindowtitle( pCpwWin wc )
{
    pCpwLhwc lhwc = wc->plhwc;
    if ( strLen( wc->title ) != 0 )
        SetWindowText( lhwc->hwnd, str( wc->title ) );
    else
        return false;
    return true;
}

/* position the window on the desktop */

bool cpw_localhost_positionwindow( pCpwWin wc )
{
    pCpwLhwc lhwc = wc->plhwc;

    /* printf( "lh_position: %dx%d\n", wc->x, wc->y ); */

    if ( SetWindowPos( lhwc->hwnd, 0, wc->x, wc->y, wc->width, wc->height, 
                       SWP_NOZORDER|SWP_NOSIZE ) )
        return true;

    return false;
}

/* reshape the window frame */

bool cpw_localhost_reshapewindow( pCpwWin wc )
{
    RECT rect;

    pCpwLhwc plhwc = wc->plhwc;

    /* printf( "lh_reshape: %dx%d\n", wc->width, wc->height ); */

    rect.left   = 0;
    rect.top    = 0;
    rect.right  = wc->width;
    rect.bottom = wc->height;

    AdjustWindowRect( &rect, plhwc->winstyle, (bool)plhwc->hmenu ); 

    rect.right  = rect.right + abs(rect.left);
    rect.bottom = rect.bottom + abs(rect.top);

    /* x and y are ignored, width and height should be the total window dimensions */

    SetWindowPos( plhwc->hwnd, 0, 0, 0, rect.right, rect.bottom, 
                       SWP_NOZORDER|SWP_NOMOVE );

    return true;
}

/* max the window width and height out */

bool cpw_localhost_maximizewindow( pCpwWin wc )
{
    pCpwLhwc lhwc = wc->plhwc;

    ShowWindow( lhwc->hwnd, SW_MAXIMIZE );

    return true;
}

/* iconify the window */

bool cpw_localhost_inconifywindow( pCpwWin wc )
{
    pCpwLhwc lhwc = wc->plhwc;

    ShowWindow( lhwc->hwnd, SW_MINIMIZE );

    return true;
}

/* restore an iconic or maximized window */

bool cpw_localhost_restorewindow( pCpwWin wc )
{
    pCpwLhwc lhwc = wc->plhwc;
    ShowWindow( lhwc->hwnd, SW_RESTORE );
    return true;
}

/* hide the window completely */

bool cpw_localhost_hidewindow( pCpwWin wc )
{
    pCpwLhwc lhwc = wc->plhwc;
    if ( !ShowWindow( lhwc->hwnd, SW_HIDE ) ) 
        return false;
    return true;
}

/* show the window completely */

bool cpw_localhost_showwindow( pCpwWin wc )
{
    pCpwLhwc lhwc = wc->plhwc;
    if ( !ShowWindow( lhwc->hwnd, SW_SHOW ) ) 
        return false;
    return true;
}

/* set a window to the foreground z-order */

bool cpw_localhost_setforeground( pCpwWin wc )
{
    pCpwLhwc lhwc = wc->plhwc;
    SetForegroundWindow( lhwc->hwnd );
    return true;
}

/* get the current x,y position and width,height of the window */

bool cpw_localhost_windowinfo( pCpwWin wc )
{
    RECT rect;
    pCpwLhwc lhwc = wc->plhwc;

    if ( GetClientRect( lhwc->hwnd, &rect ) ) {
        wc->x = rect.left;
        wc->y = rect.top;
        wc->width  = rect.right;
        wc->height = rect.bottom;
    } else return false;

    return true;
}

/* push the window below by one in the z-order */

bool cpw_localhost_pushwindow( pCpwWin wc ) 
{
    pCpwLhwc lhwc = wc->plhwc;
    if ( SetWindowPos( lhwc->hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE ) )
        return true;
    return false;
}

/* push the window to the bottom of the z-order */

bool cpw_localhost_popwindow( pCpwWin wc ) 
{
    pCpwLhwc lhwc = wc->plhwc;
    if ( SetWindowPos( lhwc->hwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE ) )
        return true;
    return false;
}

/*************************************************************************/
/*                                                                       */
/*   menus                                                               */
/*                                                                       */
/*************************************************************************/

/* build a window menu or popup and return the handle to it */

HMENU cpw_localhost_internal_createmenu( pCpw cpw, pCpwMenu menu, bool popup )
{
    HMENU hMenu;
    MENUITEMINFO info;
    int i;

    if ( popup ) 
        hMenu = CreatePopupMenu();
    else
        hMenu = CreateMenu();

    if ( hMenu == 0 ) return 0;

    for( i = 0; i < (int_32)menu->ecount; i++ ) {

        memset( &info, 0, sizeof( info ) );

        info.cbSize = sizeof( info );

        info.fMask = MIIM_ID | MIIM_STATE | MIIM_TYPE;

        /* seperator vs. string */

        if ( menu->entries[i]->f_seperator ) {

            info.fType = MFT_SEPARATOR;

        }  else {

            info.fType = MFT_STRING;
            info.dwTypeData = str( menu->entries[i]->title );
            info.cch = len( menu->entries[i]->title );

        }

        /* checked or not checked */
                
        if ( menu->entries[i]->f_checked ) {
            info.fState = MFS_CHECKED;
        } else {
            info.fState = MFS_UNCHECKED;
        }

        /* add a sub menu */
                
        if ( menu->entries[i]->f_submenu ) {
            info.fMask = MIIM_ID | MIIM_STATE | MIIM_TYPE | MIIM_SUBMENU;
            info.hSubMenu = cpw_localhost_internal_createmenu( cpw, menu->entries[i]->submenu, popup );
        }

        info.wID = menu->entries[i]->id;

        if ( !InsertMenuItem( hMenu, CPW_MENUS_MAXENTRIES - i, TRUE, &info ) ) 
            return 0;
    }

    return hMenu;
}

/* create a menu for a window's menu bar and display it */

bool cpw_localhost_assignmenutowindow( pCpw cpw, pCpwWin wc, pCpwMenu menu )
{
    HMENU hMenu;
    pCpwLhwc plhwc = wc->plhwc;

    /* create the menu */

    hMenu = cpw_localhost_internal_createmenu( cpw, menu, false );

    if ( hMenu == 0 ) return false;

    if ( plhwc->hmenu == 0 ) {

        RECT rect;

        rect.left   = 0;
        rect.top    = 0;
        rect.right  = wc->width;
        rect.bottom = wc->height;

        AdjustWindowRect( &rect, plhwc->winstyle, true ); 

        rect.right  = rect.right + abs(rect.left);
        rect.bottom = rect.bottom + abs(rect.top);

        /* x and y are ignored, width and height should be the total window dimensions */

        SetWindowPos( plhwc->hwnd, 0, 0, 0, rect.right, rect.bottom, 
                           SWP_NOZORDER|SWP_NOMOVE );

    }

    /* assign the menu to the window */

    if ( !SetMenu( plhwc->hwnd, hMenu ) ) 
        return false;

    plhwc->updates  = true;

    /* save the handle for later updates */

    plhwc->hmenu = hMenu;

    return true;
}

bool cpw_localhost_updatemenu( pCpw cpw, pCpwWin wc, pCpwMenu menu )
{
    HMENU hMenu;
    pCpwLhwc lhwc = wc->plhwc;

    /* create the menu */

    hMenu = cpw_localhost_internal_createmenu( cpw, menu, false );
    if ( hMenu == 0 ) return false;

    /* assign the menu to the window */

    if ( !SetMenu( lhwc->hwnd, hMenu ) ) 
        return false;

    /* delete the old one */

    if ( lhwc->hmenu != 0 ) 
        DestroyMenu( lhwc->hmenu );

    /* save the handle for later updates */

    lhwc->hmenu = hMenu;

    return true;
}

/* detach a menu from the menu bar */

void cpw_localhost_unassignmenu( pCpw cpw, pCpwWin wc )
{
    RECT rect;
    pCpwLhwc plhwc = wc->plhwc;

    rect.left   = 0;
    rect.top    = 0;
    rect.right  = wc->width;
    rect.bottom = wc->height;

    AdjustWindowRect( &rect, plhwc->winstyle, false ); 

    rect.right  = rect.right + abs(rect.left);
    rect.bottom = rect.bottom + abs(rect.top);

    /* x and y are ignored, width and height should be the total window dimensions */

    SetWindowPos( plhwc->hwnd, 0, 0, 0, rect.right, rect.bottom, 
                       SWP_NOZORDER|SWP_NOMOVE );

    SetMenu( plhwc->hwnd, null );

    if ( plhwc->hmenu != 0 ) 
        DestroyMenu( plhwc->hmenu );

    plhwc->hmenu = 0;
}

/* 
   display a popup menu at the specified location. 
   it is acceptable for this function to either trap 
   the thread of execution and hold it until a selection
   is made or return emmediately and use event processing 
   to track menu selection. regardless, the resulting
   item selection should be sent to the application with 
   the following event stack interface function:

   cpw_hostevent_menuselect( cpw, winid, menuid, entryid );
*/

bool cpw_localhost_displaypopup( pCpw cpw, pCpwWin wc, pCpwMenu menu, uint_32 x, uint_32 y )
{
    HMENU hMenu;
    POINT point;
    int_32 selected;
    pCpwLhwc lhwc = wc->plhwc;

    point.x = x; point.y = y;
    ClientToScreen( lhwc->hwnd, &point );

    hMenu = cpw_localhost_internal_createmenu( cpw, menu, true );

    if ( hMenu == 0 ) return false;

    selected = TrackPopupMenu( hMenu, 
        ( TPM_CENTERALIGN | TPM_TOPALIGN | TPM_RETURNCMD | TPM_NONOTIFY | TPM_RIGHTBUTTON
        #ifdef TPM_HORNEGANIMATION /* windows 5.0/98 animations */
        | TPM_HORNEGANIMATION | TPM_VERPOSANIMATION
        #endif
        ) , point.x, point.y, 0, lhwc->hwnd, null );

    /* insert th event into the event stack */

    cpw_hostevent_menuselect( cpw, wc->id, menu->id, selected );

    /* were not saving popup menu handles, they are created 'on-the-fly'
    every time they are shown. */

    return true;
}

/*************************************************************************/
/*                                                                       */
/*   Cursors                                                             */
/*                                                                       */
/*************************************************************************/

/* set the cursor type.  custom isn't supported yet. */

bool cpw_localhost_setcursor( pCpw cpw, pCpwWin wc ) 
{
    CpwCursor c = wc->cursor;
    switch( c ) {

        case CursorArrow:
            SetCursor(LoadCursor(NULL, IDC_ARROW));
        break;
        case CursorHand:
            /* IDC_HAND Windows NT 5.0 and later  */
            #ifdef IDC_HAND
            SetCursor(LoadCursor(NULL, IDC_HAND));
            #else
            SetCursor(LoadCursor(NULL, IDC_ARROW));
            #endif
        break;
        case CursorNo:
            SetCursor(LoadCursor(NULL, IDC_NO));
        break;
        case CursorQuestion:
            SetCursor(LoadCursor(NULL, IDC_HELP));
        break;
        case CursorBeam:
            SetCursor(LoadCursor(NULL, IDC_IBEAM));
        break;
        case CursorWait:
            SetCursor(LoadCursor(NULL, IDC_WAIT));
        break;
        case CursorCrosshair:
            SetCursor(LoadCursor(NULL, IDC_CROSS));
        break;
        case CursorNone:
            SetCursor(NULL);
        break;
        case CursorSizeNSEW:
            SetCursor(LoadCursor(NULL, IDC_SIZEALL));
        break;
        case CursorSizeNS:
            SetCursor(LoadCursor(NULL, IDC_SIZENS));
        break;
        case CursorSizeNeSw:
            SetCursor(LoadCursor(NULL, IDC_SIZENESW));
        break;
        case CursorSizeEW:
            SetCursor(LoadCursor(NULL, IDC_SIZEWE));
        break;
        case CursorSizeSeNw:
            SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
        break;
        case CursorCustom:
        break;
    }
    return false;
}

/* the cursor left a cpw window, restore if needed to default cursor */

bool cpw_localhost_restorecursor( pCpw cpw ) 
{
    return true;
}

bool cpw_localhost_positioncursor( pCpwWin wc, uint_32 x, uint_32 y )
{
    POINT point;
    pCpwLhwc lhwc = wc->plhwc;
    point.x = x; point.y = y;
    ClientToScreen( lhwc->hwnd, &point );
    return SetCursorPos( point.x, point.y );
}

bool cpw_localhost_centercursor( pCpwWin wc )
{
    POINT point;
    pCpwLhwc lhwc = wc->plhwc;
    point.x = (int)(((float)wc->width)*.5); point.y = (int)(((float)wc->height)*.5);
    ClientToScreen( lhwc->hwnd, &point );
    return SetCursorPos( point.x, point.y );
}

/*************************************************************************/
/*                                                                       */
/*   OpenGL                                                              */
/*                                                                       */
/*************************************************************************/

/* match the requested draw surface to one that is available on 
   this machine. used by cpw_localhost_setpixelformat below which 
   is called by Cpw. */

uint_32 
cpw_localhost_internal_findbestglformat( pCpw cpw, pCpwLhwc lhwc,
            PIXELFORMATDESCRIPTOR * pfd, uint_32 format )
{
    uint_32 pfid = 0;

    memset( pfd, 0, sizeof( PIXELFORMATDESCRIPTOR ) );
    pfd->nSize = ( sizeof( PIXELFORMATDESCRIPTOR ) );
    pfd->nVersion = 1;

    pfd->dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

    /* color format */

    if ( ( format & CPW_SURFACE_RGBA ) || ( format & CPW_SURFACE_RGB ) )
        pfd->iPixelType = PFD_TYPE_RGBA;
    else if ( ( format & CPW_SURFACE_INDEX ) )
        pfd->iPixelType = PFD_TYPE_COLORINDEX;
    else
        pfd->iPixelType = PFD_TYPE_RGBA;

    /* depth buffer */

    if ( format & CPW_SURFACE_DEPTH ) {
        if ( format & CPW_SURFACE_DEPTH2 )
            pfd->cDepthBits = 2;
        else if ( format & CPW_SURFACE_DEPTH4 ) 
            pfd->cDepthBits = 4;
        else if ( format & CPW_SURFACE_DEPTH8 ) 
            pfd->cDepthBits = 8;
        else if ( format & CPW_SURFACE_DEPTH16 ) 
            pfd->cDepthBits = 16;
        else if ( format & CPW_SURFACE_DEPTH32 ) 
            pfd->cDepthBits = 32;
        else if ( format & CPW_SURFACE_DEPTH64 ) 
            pfd->cDepthBits = 64;
        else  
            pfd->cDepthBits = 8;
    } else {
        pfd->cDepthBits = 0;
    }

    /* color depth */

    if ( format & CPW_SURFACE_COLOR8 ) {
        pfd->cAlphaBits = 2;
        pfd->cColorBits = 8;
    } else if ( format & CPW_SURFACE_COLOR16 ) {
        pfd->cAlphaBits = 4;
        pfd->cColorBits = 16;
    } else if ( format & CPW_SURFACE_COLOR32 ) {
        pfd->cAlphaBits = 8;
        pfd->cColorBits = 32;
    } else if ( format & CPW_SURFACE_COLOR64 ) {
        pfd->cAlphaBits = 16;
        pfd->cColorBits = 64;
    } else  {
        pfd->cAlphaBits = 0;
        pfd->cColorBits = 16;
    }

    /* alpha depth */

    /* buffers */

    if ( ( format & CPW_SURFACE_SINGLE ) ) {
      pfd->dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
    } else {
      pfd->dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
    }

    /* accumulation buffer */

    if ( format & CPW_SURFACE_ACCUM ) 
        pfd->cAccumBits = 16;

    /* stencil buffer */

    if ( format & CPW_SURFACE_STENCIL ) 
        pfd->cStencilBits = 8;

    /* stereo buffer */

    if ( format & CPW_SURFACE_STEREO ) 
        pfd->iPixelType = pfd->iPixelType | PFD_STEREO;

    /* debug pixel formats */

#ifdef DEBUGOPENGLFORMATS

    {
        char buf[10000];
        int i;

        for ( i = 0; i <= 40; i++ ) {

            PIXELFORMATDESCRIPTOR data;
            bool mcd, soft, icd;

            memset( &data, 0, sizeof( data ) );
            data.nSize = ( sizeof( PIXELFORMATDESCRIPTOR ) );
            data.nVersion = 1;
    
            if ( !DescribePixelFormat( lhwc->hdc, i, sizeof( PIXELFORMATDESCRIPTOR ), &data ) )
                continue;

            if ( ( data.dwFlags & PFD_SUPPORT_OPENGL ) == 0 ) continue;

            /* generic without acceleration */

            soft=((pfd->dwFlags & PFD_GENERIC_FORMAT) && !(pfd->dwFlags & PFD_GENERIC_ACCELERATED));

            /* generic is accelerated */

            mcd=((pfd->dwFlags & PFD_GENERIC_FORMAT) && (pfd->dwFlags & PFD_GENERIC_ACCELERATED));

            /* hardware / icd accelerated driver */

            icd=(!(pfd->dwFlags & PFD_GENERIC_FORMAT) && !(pfd->dwFlags & PFD_GENERIC_ACCELERATED));

            sprintf( buf, " id:%2d accel:[%d,%d,%d] color:%2d depth:%2d alpha:%2d stencil:%2d\n", 
                i,
                soft, mcd, icd,
                data.cColorBits, 
                data.cDepthBits,
                data.cAlphaBits,
                data.cStencilBits );
        
            cpw->cpw_print( buf );
        }
    }

    /* debug print the requested format */

    {
        char buf[10000];

        sprintf( buf, "requesting for color:%d depth:%d alpha:%d stencil:%d\n", 
            pfd->cColorBits, 
            pfd->cDepthBits,
            pfd->cAlphaBits,
            pfd->cStencilBits );
        
        cpw->cpw_print( buf );
    }

#endif

    /* request the closest format we can get */

    pfid = ChoosePixelFormat( lhwc->hdc, pfd );

    /* debug print what we got */

#ifdef DEBUGOPENGLFORMATS

    {
        char buf[10000];

        if ( pfid > 0 )
            sprintf( buf, "received id:%d color:%d depth:%d alpha:%d stencil:%d\n", 
                pfid,
                pfd->cColorBits, 
                pfd->cDepthBits,
                pfd->cAlphaBits,
                pfd->cStencilBits );
        else
            sprintf( buf, "not found." );
                
        cpw->cpw_print( buf );
    }

#endif

    /* return the pixelformat id */

    return pfid;
}

/* set the drawing surface based on the user's requested
   format (cpw->cpw_glDisplayMode). see cpw_init for more 
   details on draw surface modes. */

bool
cpw_localhost_setpixelformat( pCpw cpw, pCpwLhwc lhwc )
{
    PIXELFORMATDESCRIPTOR pfd;
    uint_32 pfid = 0;

    if ( !lhwc ) return false;

    /* choose a valid pixel format */

    if ( ( pfid = cpw_localhost_internal_findbestglformat( cpw, lhwc, 
                  &pfd, cpw->cpw_displaymode ) ) == 0 ) {

        /* this should never really happen */

        cpw_error_set( cpw, cpw_error_visualformatunsupported );
        return false;
    }

    /* set the choosen pixel format */

    if (!SetPixelFormat( lhwc->hdc, pfid, &pfd ) ) {

        /* this should never really happen */

        cpw_error_set( cpw, cpw_error_visualformatinvalid );
        return false;
    }
    return true;
}

/* create a gl rendering context for this window */

bool
cpw_localhost_createglcontext( pCpw cpw, pCpwLhwc lhwc )
{
    if ( !lhwc ) return false;
    lhwc->glContext = wglCreateContext( lhwc->hdc );
    if ( lhwc->glContext == 0 ) {

        /* this should never really happen */

        cpw_error_set( cpw, cpw_error_createcontextfailed );
        return false;
    }
    return true;
}

/* destroy the window's rendering context */

bool
cpw_localhost_destroyglcontext( pCpw cpw, pCpwLhwc lhwc )
{
    if ( !lhwc ) return false;
    wglDeleteContext( lhwc->glContext );
    ReleaseDC( lhwc->hwnd, lhwc->hdc );
    return true;
}

/* make this window's rendering context current */

bool
cpw_localhost_makecurrent( pCpw cpw, pCpwLhwc lhwc )
{
    if ( !lhwc ) return false;
    if ( !wglMakeCurrent( lhwc->hdc, lhwc->glContext ) ) {

        /* this should never really happen */

        cpw_error_set( cpw, cpw_error_setcurrentcontextfailed );
        return false;
    }
    return true;
}

/* swap this windows buffers */

bool
cpw_localhost_swapbuffers( pCpwLhwc lhwc )
{
    if ( !lhwc ) return false;
    return SwapBuffers( lhwc->hdc );
}

/*************************************************************************/
/*                                                                       */
/*   Keyboard key state tracker                                          */
/*                                                                       */
/*************************************************************************/

void cpw_localhost_internal_keypress( pCpw cpw, uint_32 key, bool state ) 
{
    switch ( key ) {
        case CPW_KEY_CONTROL:
          {
          if ( GetKeyState( VK_LCONTROL ) & 0x8000 ) 
            cpw->keyboard_state[CPW_KEY_LCONTROL] = state;
          if ( GetKeyState( VK_RCONTROL ) & 0x8000 ) 
            cpw->keyboard_state[CPW_KEY_RCONTROL] = state;
          break;
          }
        case CPW_KEY_SHIFT:
          if ( GetKeyState( VK_LSHIFT ) & 0x8000 ) 
            cpw->keyboard_state[CPW_KEY_LSHIFT] = state;
          if ( GetKeyState( VK_RSHIFT ) & 0x8000 ) 
            cpw->keyboard_state[CPW_KEY_RSHIFT] = state;
          break;
        case CPW_KEY_ALT:
          if ( GetKeyState( VK_LMENU ) & 0x8000 ) 
            cpw->keyboard_state[CPW_KEY_LALT] = state;
          if ( GetKeyState( VK_RMENU ) & 0x8000 ) 
            cpw->keyboard_state[CPW_KEY_RALT] = state;
          break;
        
        break;
    }

    cpw->keyboard_state[key] = state;
}

/*************************************************************************/
/*                                                                       */
/*   window events                                                       */
/*                                                                       */
/*************************************************************************/

/* deal with the platform's event processing, called from cpwMainLoop.
   process count events and return. Events should be converted to the
   appropriate Cpw events and inserted into the Cpw event stack. return
   true if there are more events to process. count is currently 3 but
   can be changed by the user when the lib is compiled. */

bool
cpw_localhost_processevents( pCpw cpw, uint_32 count )
{
    MSG event;

    while ( count > 0 ) {

        /* do we have anything pending? */

        if ( PeekMessage ( &event, NULL, 0, 0, PM_NOREMOVE ) == 0 )
            return false;

        if ( GetMessage( &event, NULL, 0, 0 ) == 0 ) {

            /* WM_QUIT */

            cpwBreakMainLoop( cpw );
            return false;
        }

        /* send it down to the proceedure for interpretation */

        TranslateMessage(&event);
        DispatchMessage(&event);

        count--;
    }
    return true;
}

/* windows event interpretation for every window created. */

LONG WINAPI cpw_localhost_internal_WindowProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    pCpw    cpw;
    pCpwLhc lhc;
    int_32  x, y;
    uint_32 winid;
    int_32  button = -1;

    /* retrieve our cpw context from window/class storage */

    cpw   = (pCpw) GetClassLongPtr( hwnd, 0 );  

    /* filter out events during initial createwindow call */

    if ( cpw == 0 ) 
        return DefWindowProc(hwnd, msg, wParam, lParam); 

    /* retrieve winid and localhost context */

    lhc   = ( pCpwLhc ) cpw->ctx_localhost;
    winid = (uint_32) GetWindowLongPtr( hwnd, 0 );  

    switch( msg ) {

        /****************************************************/
        /*  Filter out some common messages we want windows */
        /*  to deal with.                                   */
        /****************************************************/

        case WM_NCHITTEST:
        case WM_WINDOWPOSCHANGED:
        break;

        /****************************************************/
        /*  Window control                                  */
        /****************************************************/

        case WM_CLOSE:

            cpw_hostevent_destroy( cpw, winid );

        return 0;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;

            BeginPaint( hwnd, &ps ); 
            EndPaint( hwnd, &ps );

            cpw_hostevent_draw( cpw, winid );

        }
        return 0;

        /* move window */

        case WM_MOVE:
        {
            RECT rect;

            /* convert from client area to to total window position */
            
            GetWindowRect( hwnd, &rect );
            
            /* printf( "wm_move a:%dx%d\n", rect.left, rect.top ); */

            cpw_hostevent_position( cpw, winid, rect.left, rect.top );
        }
        return 0;

        /****************************************************/
        /*  Menubar selections                              */
        /****************************************************/

        case WM_COMMAND:
        {            
            DWORD wNotifyCode = HIWORD(wParam); // notification code 
            DWORD wID = LOWORD(wParam);         // item, control, or accelerator identifier 

            if ( wNotifyCode == 0 ) {

                pCpwWin window = cpw_windowlist_lookup( cpw, winid );

                if ( window == 0 ) break;

                cpw_hostevent_menuselect( cpw, winid, window->menuid, wID );
            }

            break;
        }
            
        /****************************************************/
        /*  Visibility                                      */
        /****************************************************/

        case WM_SHOWWINDOW:
            switch( wParam ) {
                case 0:
                cpw_hostevent_visibility( cpw, winid, CPW_HIDE );
                break;
                case 1:
                cpw_hostevent_visibility( cpw, winid, CPW_SHOW );
                break;
            }
        return 0;

        case WM_SIZING:
        {
            return 0;
        }

        case WM_SIZE:
        {
            int width, height;

            width = LOWORD( lParam );
            height = HIWORD( lParam );

            /* printf( "wm_size:%dx%d\n", width, height ); */

            GdiFlush();

            switch ( wParam ) {
                case SIZE_MINIMIZED:
                cpw_hostevent_visibility( cpw, winid, CPW_ICONIC );
                break;
                case SIZE_MAXIMIZED:
                cpw_hostevent_reshape( cpw, winid, width, height );
                break;
                case SIZE_RESTORED:
                cpw_hostevent_reshape( cpw, winid, width, height );
                break;
                case SIZE_MAXSHOW:
                break;
            }
        }
        return 0;

        /****************************************************/
        /*  Window focus changes                            */
        /****************************************************/

        /* 
            we want cpw cursor entered/leaving to occur only if 
            the window is in the foreground. Due to Win32's odd 
            WM_SETCURSOR event, we do some tracking in the localhost 
            state of the foreground window id and the window which 
            contains the cursor so we can send proper events.

            gainfocus should always occur before cursorentered. 
            cursorleaving should always occur before focuslost. 
            cursorenter/leave can occur independantly of focus 
            though. (the window is foreground and the cursor is 
            moved in and out of it's client area..) hence the use 
            of wm_setcursor below this.

        */

        case WM_SETFOCUS:

            /* foreground (focus to) window */

            lhc->foregroundWindow = winid;
            cpw_hostevent_setfocus( cpw, winid );

            /* if needed send the cursor entered event */

            if ( lhc->cursorWindow != winid && lhc->foregroundWindow == winid ) {

                lhc->cursorWindow = winid;
                cpw_hostevent_cursorenter( cpw, winid );

            }

        return 0;

        case WM_KILLFOCUS:

            /* if needed send the cursor leave event */

            if ( lhc->cursorWindow == winid ) {

                lhc->cursorWindow = 0;
                cpw_hostevent_cursorleft( cpw, winid );

            }

            /* lost focus */

            lhc->foregroundWindow = 0;
            cpw_hostevent_lostfocus( cpw, winid );

        return 0;

        /****************************************************/
        /*  Cursor changes                                  */
        /****************************************************/

        case WM_SETCURSOR:
        {
            /* Win32 client area setcursor messages dump into the 
               window anytime the cursor moves. we only want to 
               send one enter/leave combo and this is the only 
               default windows event we have. */

            /* is this setcursor event outside the client area? (leaving) */

            if( LOWORD( lParam ) != HTCLIENT ) {

                /* if we havent done it already on a focus change, 
                   send a leave cursor event */

                if ( lhc->cursorWindow == winid ) {

                    lhc->cursorWindow = 0;
                    cpw_hostevent_cursorleft( cpw, winid );

                }

                break;
            }

            /* have we sent a enter cursor event yet? */

            if ( lhc->cursorWindow != winid && lhc->foregroundWindow == winid ) {

                /* no, send one */

                lhc->cursorWindow = winid;
                cpw_hostevent_cursorenter( cpw, winid );

            }

            return 1;
        }

        /****************************************************/
        /*  Mouse wheel support                             */
        /****************************************************/

        /* for some odd reason WM_MOUSEWHEEL is not defined on my
           box's .h's. I have a wheel and the messages come 
           here. So instead of using the WM constant I hardcoded 
           the value. */

        case 0x020A:
        {
            int_32 steps = ((short) HIWORD(wParam))/120;

            /* Mouse Wheel is being rolled forward */

            if( steps > 0 ) 
                lhc->mouse_relz = lhc->mouse_relz + 1;

            /* Mouse Wheel is being rolled backward */

            if( steps < 0 ) 
                lhc->mouse_relz = lhc->mouse_relz - 1;

            cpw_hostevent_mouseclick( cpw, winid, CPW_BUTTON_ROLL, CPW_BUTTON_MIDDLE, steps, 0 );

            break; 
        }

        /* Sometimes we don't get a leave cursor event due to a quick 
           exit of the cursor from the window. (windows never sends a 
           setcursor event for nc areas so we don't know it left.) We 
           could add some TrackCursor code to compensate if it becomes 
           an issue. */

        /****************************************************/
        /*  Mouse movement and clicks processing            */
        /****************************************************/

        case WM_LBUTTONDOWN:

            button = CPW_BUTTON_LEFT;

            lhc->mouse_buttons[0] = true;

        case WM_MBUTTONDOWN:

            if (button < 0)
            button = CPW_BUTTON_MIDDLE;

            lhc->mouse_buttons[1] = true;

        case WM_RBUTTONDOWN:

            if (button < 0)
            button = CPW_BUTTON_RIGHT;

            lhc->mouse_buttons[2] = true;

            SetCapture( hwnd ); /* on mouse drags we want mouse events ouside the window */

            x = LOWORD( lParam );
            y = HIWORD( lParam );

            if(x & 1 << 15) x -= (1 << 16);
            if(y & 1 << 15) y -= (1 << 16);

            cpw_hostevent_mouseclick( cpw, winid, CPW_BUTTON_DOWN, button, x, y );

        return 0;

        case WM_LBUTTONUP:

            button = CPW_BUTTON_LEFT;

            lhc->mouse_buttons[0] = false;

        case WM_MBUTTONUP:

            if (button < 0)
            button = CPW_BUTTON_MIDDLE;

            lhc->mouse_buttons[1] = false;

        case WM_RBUTTONUP:

            if (button < 0)
            button = CPW_BUTTON_RIGHT;

            lhc->mouse_buttons[2] = false;

            ReleaseCapture(); /* release the mouse capture. */

            x = LOWORD( lParam );
            y = HIWORD( lParam );

            if(x & 1 << 15) x -= (1 << 16);
            if(y & 1 << 15) y -= (1 << 16);

            cpw_hostevent_mouseclick( cpw, winid, CPW_BUTTON_UP, button, x, y );

            return 0;

        /* motion callbacks */

        case WM_MOUSEMOVE:

            /* quick check to see if we currently filter these */

            if ( cpw_event_filtered( cpw, CPW_MOUSEMOTION_EVENT ) &&
                 cpw_event_filtered( cpw, CPW_MOUSEDRAG_EVENT ) ) return 0;

            x = LOWORD( lParam );
            y = HIWORD( lParam );

            /* normalize */

            if(x & 1 << 15) x -= (1 << 16);
            if(y & 1 << 15) y -= (1 << 16);

            /* store mouse relative position info */

            lhc->mouse_relx = lhc->mouse_relx + ( lhc->mouse_x - x );
            lhc->mouse_rely = lhc->mouse_rely + ( lhc->mouse_y - y );
            lhc->mouse_x = x;
            lhc->mouse_y = y;

            if ( wParam & ( MK_LBUTTON | MK_MBUTTON | MK_RBUTTON ) ) {

                /* drag event */

                switch( wParam ) {                
                    case MK_LBUTTON:
                    button = CPW_BUTTON_LEFT;
                    break;
                    case MK_MBUTTON:
                    button = CPW_BUTTON_MIDDLE;
                    break;
                    case MK_RBUTTON:
                    button = CPW_BUTTON_RIGHT;
                    break;
                }

                /* send only if the window is in the foreground */

                if ( lhc->foregroundWindow == winid )
                    cpw_hostevent_mousedrag( cpw, winid, button, x, y );

            } else if ( ( wParam & ( MK_LBUTTON | MK_MBUTTON | MK_RBUTTON ) ) == 0 ) {

                /* mouse motion event */

                /* send only if the window is in the foreground */

                if ( lhc->foregroundWindow == winid )
                    cpw_hostevent_mousemove( cpw, winid, x, y );

            }
            return 0;

        /****************************************************/
        /*  Palatte changes for index color rendering       */
        /****************************************************/

        case WM_PALETTECHANGED:
        case WM_QUERYNEWPALETTE:
            /*
            window = __glutGetWindow(hwnd);
            if (window && window->colormap) {
              UnrealizeObject(window->colormap->cmap);
              SelectPalette(window->hdc, window->colormap->cmap, FALSE);
              RealizePalette(window->hdc);
              return TRUE;
            }
            */
        return 0;

        /****************************************************/
        /*  Keyboard processing                             */
        /****************************************************/

        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP:
            if ( msg == WM_SYSKEYDOWN ) msg = WM_KEYDOWN; else msg = WM_SYSKEYUP;
        case WM_KEYDOWN:
        case WM_KEYUP:
        {
            POINT  point;
            bool   shift = false;
            int_32 key;

            /* filter out special keys from regular ones */

            switch (wParam) 
            {
                case VK_F1:         key = CPW_KEY_F1;          break;
                case VK_F2:         key = CPW_KEY_F2;          break;
                case VK_F3:         key = CPW_KEY_F3;          break;
                case VK_F4:         key = CPW_KEY_F4;          break;
                case VK_F5:         key = CPW_KEY_F5;          break;
                case VK_F6:         key = CPW_KEY_F6;          break;
                case VK_F7:         key = CPW_KEY_F7;          break;
                case VK_F8:         key = CPW_KEY_F8;          break;
                case VK_F9:         key = CPW_KEY_F9;          break;
                case VK_F10:        key = CPW_KEY_F10;         break;
                case VK_F11:        key = CPW_KEY_F11;         break;
                case VK_F12:        key = CPW_KEY_F12;         break;
                case VK_LEFT:       key = CPW_KEY_LEFT;        break;
                case VK_UP:         key = CPW_KEY_UP;          break;
                case VK_RIGHT:      key = CPW_KEY_RIGHT;       break;
                case VK_DOWN:       key = CPW_KEY_DOWN;        break;
                case VK_PRIOR:      key = CPW_KEY_PAGEUP;      break;
                case VK_NEXT:       key = CPW_KEY_PAGEDOWN;    break;
                case VK_HOME:       key = CPW_KEY_HOME;        break;
                case VK_END:        key = CPW_KEY_END;         break;
                case VK_INSERT:     key = CPW_KEY_INSERT;      break;
                case VK_DELETE:     key = CPW_KEY_DELETE;      break;
                case VK_CAPITAL:    key = CPW_KEY_CAPSLOCK;    break;
                case VK_SHIFT:      key = CPW_KEY_SHIFT;       break;
                case VK_CONTROL:    key = CPW_KEY_CONTROL;     break;
                case VK_MENU:       key = CPW_KEY_ALT;         break;
                case VK_PAUSE:      key = CPW_KEY_PAUSE;       break;
                case VK_ESCAPE:     key = CPW_KEY_ESCAPE;      break;
                case VK_TAB:        key = CPW_KEY_TAB;         break;
                case VK_MULTIPLY:   key = CPW_KEY_MULTIPLY;    break;
                case VK_ADD:        key = CPW_KEY_ADD;         break;
                case VK_SEPARATOR:  key = CPW_KEY_SEPERATOR;   break;
                case VK_SUBTRACT:   key = CPW_KEY_SUBTRACT;    break;
                case VK_DECIMAL:    key = CPW_KEY_DECIMAL;     break;
                case VK_DIVIDE:     key = CPW_KEY_DIVIDE;      break;
                case VK_NUMLOCK:    key = CPW_KEY_NUMLOCK;     break;
                case VK_PRINT:      key = CPW_KEY_PRINT;       break;
                case VK_SNAPSHOT:   key = CPW_KEY_PRINT;       break; 
                case VK_SCROLL:     key = CPW_KEY_SCROLLLOCK;  break;
                case 8:             key = CPW_KEY_BACKSPACE;   break;
                case 13:            key = CPW_KEY_ENTER;       break;

                /* regular key */
                default:            key = -1;
            }

            /* system key press event */

            if ( key != -1 ) {

                GetCursorPos( &point );
                ScreenToClient( hwnd, &point );

                if ( msg == WM_KEYDOWN ) {
                    
                    cpw_localhost_internal_keypress( cpw, key, true );
                    cpw_hostevent_systemkeyboard( cpw, winid, key, CPW_KEYMOD_DOWN, point.x, point.y );

                } else if ( msg == WM_KEYUP )  {

                    cpw_localhost_internal_keypress( cpw, key, false );
                    cpw_hostevent_systemkeyboard( cpw, winid, key, CPW_KEYMOD_UP, point.x, point.y );
                
                }

                return 0;
            }

            switch (wParam) 
            {
                case VK_NUMPAD0: key = CPW_KEY_0;     break;
                case VK_NUMPAD1: key = CPW_KEY_1;     break;
                case VK_NUMPAD2: key = CPW_KEY_2;     break;
                case VK_NUMPAD3: key = CPW_KEY_3;     break;
                case VK_NUMPAD4: key = CPW_KEY_4;     break;
                case VK_NUMPAD5: key = CPW_KEY_5;     break;
                case VK_NUMPAD6: key = CPW_KEY_6;     break;
                case VK_NUMPAD7: key = CPW_KEY_7;     break;
                case VK_NUMPAD8: key = CPW_KEY_8;     break;
                case VK_NUMPAD9: key = CPW_KEY_9;     break;
                default:         key = -1;
            }          

            if ( key != -1 ) goto sendit;

            if ( ( GetKeyState(VK_SHIFT) & 0x8000 ) && key == -1 ) {
                /* shift down */
                shift = true;
            }

            key = MapVirtualKey( wParam, 2 );

            if ( key != 0 ) wParam = key; 

            switch( wParam ) 
            {
                case '0':        key = CPW_KEY_0;              break;
                case '1':        key = CPW_KEY_1;              break;
                case '2':        key = CPW_KEY_2;              break;
                case '3':        key = CPW_KEY_3;              break;
                case '4':        key = CPW_KEY_4;              break;
                case '5':        key = CPW_KEY_5;              break;
                case '6':        key = CPW_KEY_6;              break;
                case '7':        key = CPW_KEY_7;              break;
                case '8':        key = CPW_KEY_8;              break;
                case '9':        key = CPW_KEY_9;              break;
                case '-':        key = CPW_KEY_MINUS;          break;
                case '=':        key = CPW_KEY_EQUALS;         break;
                case '[':        key = CPW_KEY_LBRACKET;       break;
                case ']':        key = CPW_KEY_RBRACKET;       break;
                case ';':        key = CPW_KEY_SEMICOLON;      break;
                case '`':        key = CPW_KEY_APOSTROPHE;     break;
                case '\'':       key = CPW_KEY_QUOTE;          break;
                case ',':        key = CPW_KEY_COMMA;          break;
                case '.':        key = CPW_KEY_PERIOD;         break;
                case '/':        key = CPW_KEY_SLASH;          break;
                case '\\':       key = CPW_KEY_BACKSLASH;      break;
                case ' ':        key = CPW_KEY_SPACE;          break;
                default:         key = -1;
            }

            if ( key != -1 ) goto sendit;

            if ( ( GetKeyState(VK_CAPITAL) & 0x0001 ) && key == -1 ) {
                /* capslock on */
                shift = true;
            }

            switch (wParam) 
            {
                case 'A':        key = CPW_KEY_A;              break;
                case 'B':        key = CPW_KEY_B;              break;
                case 'C':        key = CPW_KEY_C;              break;
                case 'D':        key = CPW_KEY_D;              break;
                case 'E':        key = CPW_KEY_E;              break;
                case 'F':        key = CPW_KEY_F;              break;
                case 'G':        key = CPW_KEY_G;              break;
                case 'H':        key = CPW_KEY_H;              break;
                case 'I':        key = CPW_KEY_I;              break;
                case 'J':        key = CPW_KEY_J;              break;
                case 'K':        key = CPW_KEY_K;              break;
                case 'L':        key = CPW_KEY_L;              break;
                case 'M':        key = CPW_KEY_M;              break;
                case 'N':        key = CPW_KEY_N;              break;
                case 'O':        key = CPW_KEY_O;              break;
                case 'P':        key = CPW_KEY_P;              break;
                case 'Q':        key = CPW_KEY_Q;              break;
                case 'R':        key = CPW_KEY_R;              break;
                case 'S':        key = CPW_KEY_S;              break;
                case 'T':        key = CPW_KEY_T;              break;
                case 'U':        key = CPW_KEY_U;              break;
                case 'V':        key = CPW_KEY_V;              break;
                case 'W':        key = CPW_KEY_W;              break;
                case 'X':        key = CPW_KEY_X;              break;
                case 'Y':        key = CPW_KEY_Y;              break;
                case 'Z':        key = CPW_KEY_Z;              break;
                default: printf( "error in key processing (%i)\n", wParam ); return 0;
            }          

            /* send the key event */

            sendit:

            GetCursorPos( &point );
            ScreenToClient( hwnd, &point );

            if ( msg == WM_KEYDOWN ) {

                cpw_localhost_internal_keypress( cpw, key, true );
                cpw_hostevent_keyboard( cpw, winid, key, shift, CPW_KEYMOD_DOWN, point.x, point.y );

            } else if ( msg == WM_KEYUP ) {

                cpw_localhost_internal_keypress( cpw, key, false );
                cpw_hostevent_keyboard( cpw, winid, key, shift, CPW_KEYMOD_UP, point.x, point.y );
            
            }

            return 0;
        }

        case WM_DISPLAYCHANGE:
            cpw->cpw_screenwidth    = GetSystemMetrics(SM_CXSCREEN);
            cpw->cpw_screenheight   = GetSystemMetrics(SM_CYSCREEN);
        break;
            
        case WM_SYSCOLORCHANGE: 
            InvalidateRect( hwnd, 0, true ); 
        break; 
    }

    return DefWindowProc(hwnd, msg, wParam, lParam); 
}

/*************************************************************************/
/*                                                                       */
/*   Video Resolution of the screen                                      */
/*                                                                       */
/*************************************************************************/

/* internal: find a video format that matches the hints values as close
   as possible. */

bool cpw_localhost_internal_findbestvideoformat( pCpw cpw, CpwVideoHints hints, 
                                       DEVMODE * deviceMode, bool debug )
{
    uint_32 index = 0;

    while ( EnumDisplaySettings( NULL, index, deviceMode ) != 0 ) {

        index++;

        /* skip bad formats */

        if ( deviceMode->dmPelsWidth < 320  || 
           ( deviceMode->dmDisplayFrequency < 60 && 
             deviceMode->dmDisplayFrequency != 0 ) )

            continue;

        /* go for a direct match */

        if ( deviceMode->dmPelsWidth == hints.width && 
             deviceMode->dmPelsHeight == hints.height && 
             deviceMode->dmBitsPerPel == hints.depth ) 
        {
            if ( debug )
                printf( "%dx%d, %d bits*\n", deviceMode->dmPelsWidth,
                                             deviceMode->dmPelsHeight,
                                             deviceMode->dmBitsPerPel );
            return true;
        }

        if ( debug )
            printf( "%dx%d, %d bits\n", deviceMode->dmPelsWidth,
                                        deviceMode->dmPelsHeight,
                                        deviceMode->dmBitsPerPel );

    }

    index = 0;

    /* try again, this time matching the closest one */

    while ( EnumDisplaySettings( NULL, index, deviceMode ) != 0 ) {

        index++;

        /* skip bad formats */

        if ( deviceMode->dmPelsWidth < 320  || 
           ( deviceMode->dmDisplayFrequency < 60 && deviceMode->dmDisplayFrequency != 0 ) )
            continue;

        /* look for a close hit */

        if ( hints.width - 60 < (uint_16)deviceMode->dmPelsWidth && 
             hints.width + 60 > (uint_16)deviceMode->dmPelsWidth )

            if ( hints.height - 60 < (uint_16)deviceMode->dmPelsHeight && 
                 hints.height + 60 > (uint_16)deviceMode->dmPelsHeight )

                if ( deviceMode->dmBitsPerPel > 4 )
        {
            if ( debug )
                printf( "%dx%d, %d bits*\n", deviceMode->dmPelsWidth,
                                             deviceMode->dmPelsHeight,
                                             deviceMode->dmBitsPerPel );
            return true;
        }
    }
    
    /* give up */

    return false;
} 

bool cpw_localhost_listvideomodes( pCpw cpw, CpwVideoList * list )
{
    DEVMODE deviceMode;
    CpwVideoHints * hint;
    CpwVideoHints * current;
    CpwVideoHints last;
    uint_32 index = 0;
    uint_32 count = 0;

    memset( &last, 0, sizeof( CpwVideoHints ) ); 

    /* the first entry is alwasy the current setting */

    if ( !EnumDisplaySettings( NULL, ENUM_CURRENT_SETTINGS, &deviceMode ) ) {
        cpw_error_set( cpw, cpw_error_failedtogetvideo );
        return false;
    }

    current = cpwmalloc( sizeof( CpwVideoHints ) );        

    if ( current == 0 ) {
        cpw_error_set( cpw, cpw_error_outofmemory );
        list->size = 0;
        return false;
    }

    list->list[count] = current;

    current->width  = (uint_16)deviceMode.dmPelsWidth;
    current->height = (uint_16)deviceMode.dmPelsHeight;
    current->depth  = (uint_16)deviceMode.dmBitsPerPel;
    current->active = true;

    count++;

    /* get the rest of the entries ( a copy of the current one is ok ) */

    while ( EnumDisplaySettings( NULL, index, &deviceMode ) != 0 ) {

        index++;

        /* skip bad formats */

        if ( deviceMode.dmPelsWidth < 320  || 
           ( deviceMode.dmDisplayFrequency < 60 && deviceMode.dmDisplayFrequency != 0 ) )
            continue;

        /* skip the current setting */

        if ( current->width  == (uint_16)deviceMode.dmPelsWidth  &&
             current->height == (uint_16)deviceMode.dmPelsHeight &&
             current->depth  == (uint_16)deviceMode.dmBitsPerPel ) 
             continue;

        /* skip same width and height but different freq. we will let
           the system choose it's own frequency when we go to set. */

        if ( last.width  == (uint_16)deviceMode.dmPelsWidth  &&
             last.height == (uint_16)deviceMode.dmPelsHeight &&
             last.depth  == (uint_16)deviceMode.dmBitsPerPel ) 
             continue;

        last.width  = (uint_16)deviceMode.dmPelsWidth;
        last.height = (uint_16)deviceMode.dmPelsHeight;
        last.depth  = (uint_16)deviceMode.dmBitsPerPel;

        /* create a hint list entry */
                     
        hint = cpwmalloc( sizeof( CpwVideoHints ) );        

        if ( hint == 0 ) {
            cpw_error_set( cpw, cpw_error_outofmemory );
            list->size = count;
            return false;
        }

        list->list[count] = hint;

        hint->width  = (uint_16)deviceMode.dmPelsWidth;
        hint->height = (uint_16)deviceMode.dmPelsHeight;
        hint->depth  = (uint_16)deviceMode.dmBitsPerPel;
        hint->active = false;

        if ( count == MAX_VLIST ) break;

        count++;
    }

    list->size = count-1;
    return true;
}

/* set the main screen's video format using the hints values. */

bool cpw_localhost_setvideomode( pCpw cpw, CpwVideoHints hints ) 
{
    DEVMODE deviceMode;

    if ( !cpw_localhost_internal_findbestvideoformat( cpw, hints, &deviceMode, false ) ) {
        cpw_error_set( cpw, cpw_error_failedtosetvideo );
        return false;
    }

    if ( ChangeDisplaySettings( &deviceMode, CDS_FULLSCREEN ) == DISP_CHANGE_SUCCESSFUL ) {

        cpw->cpw_screenwidth    = GetSystemMetrics(SM_CXSCREEN);
        cpw->cpw_screenheight   = GetSystemMetrics(SM_CYSCREEN);

        return true;
    }

    cpw_error_set( cpw, cpw_error_failedtosetvideo );
    return false;
}

/* if at any point in time we changed the video settings, change them back
   on close. */

void cpw_localhost_resetvideomode( pCpw cpw ) 
{
    ChangeDisplaySettings(NULL, 0);
}

/*************************************************************************/
/*                                                                       */
/*   high frequency timer                                                */
/*                                                                       */
/*************************************************************************/

/* 
   returns the tick value of the high frequency counter 
   for this host. the tick value is the value respresenting 
   1 second for this high frequency counter. e.g.

   start = hpcount() 
   -- one second --
   end = hpcount()
   result of hpfreq() should = ( end - start )
   
   implement this in the best way you can. PC's have a built in 
   high frequency counter software can access. Other platforms
   may have to simulate such a thing. 

   Cpw will reaquire the hpcount() on every timer timeout
   but will only grab the hpfreq once when the timer is created
   so make sure hpcount() is fast.
*/

float_64
cpw_localhost_hpfreq( void )
{
    LARGE_INTEGER lpPerformanceCount;

    QueryPerformanceFrequency( &lpPerformanceCount );

    return (float_64)lpPerformanceCount.QuadPart;
}

float_64
cpw_localhost_hpcount( void )
{
    LARGE_INTEGER lpPerformanceCount;

    QueryPerformanceCounter( &lpPerformanceCount );

    return (float_64)lpPerformanceCount.QuadPart;
}

/*************************************************************************/
/*                                                                       */
/*   local fonts                                                         */
/*                                                                       */
/*************************************************************************/

/* find and return the localhost's directory to it's fonts. 
   return an empty string if such a thing doesn't exist. */

pStr 
cpw_localhost_fontpath( void )
{
    pStr path;
    char buf[4096];

    path = null;

    GetWindowsDirectory( buf, 4096 );
    setString( &path, buf );
    concatString( &path, "\\fonts\\" );

    return path;
}

/* list the files in a directory one at a time. this is for font 
   listings. the path will either be the path from above, or it 
   will be a directory relative to the applications working dir. 
   the first time this is called, reset will be true and path will
   be valid. if reset is false, path will be a null string and you
   should return the next in the list, or null if there are no
   more files to list.  */

pStr 
cpw_localhost_iteratefiles( pCpw cpw, bool reset, pStr path )
{
    pStr file;
    pCpwLhc  plhc;
    WIN32_FIND_DATA w32fd;

    plhc = ( pCpwLhc ) cpw->ctx_localhost;
    file = plhc->fontfile;

    if ( reset == true ) {

        if ( plhc->fontSearch != 0 ) {
            FindClose( plhc->fontSearch );
            plhc->fontSearch = 0;
        }

        plhc->fontSearch = FindFirstFile( str( path ), &w32fd );

        if ( plhc->fontSearch == INVALID_HANDLE_VALUE ) {
            plhc->fontSearch = 0;
            return 0;
        }
        return (pStr)1;
    }

    getanotherfont:

    if ( !FindNextFile( plhc->fontSearch, &w32fd ) ) {
        FindClose( plhc->fontSearch );
        plhc->fontSearch = 0;
        freeStr( &plhc->fontfile );
        return null;
    }

    if ( w32fd.cFileName[0] == '.' || w32fd.cFileName[1] == '.' )
	      goto getanotherfont;

    if ( w32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
	      goto getanotherfont;
        
    setString( &file, w32fd.cFileName );

    return file;
}

/*************************************************************************/
/*                                                                       */
/*   thread sleep                                                        */
/*                                                                       */
/*************************************************************************/

/* sleep - called by cpwMainLoop when there is nothing to do. */

void
cpw_localhost_sleep( uint_32 milli )
{
    Sleep( milli );
}

/*************************************************************************/
/*                                                                       */
/*   direct mouse access                                                 */
/*                                                                       */
/*************************************************************************/

#ifdef CPW_DIRECTINPUT_MOUSEACCESS

bool cpw_localhost_internal_dimousegetdata( pCpw cpw, CpwMouseInfo * info )
{
    pCpwLhc       plhc;   /* localhost context */
    int_32        i;

    #if   DIRECTINPUT_VERSION == 0x0300 
    DIMOUSESTATE dims;
    #elif DIRECTINPUT_VERSION == 0x0500 
    DIMOUSESTATE dims;
    #elif DIRECTINPUT_VERSION == 0x0700 
    DIMOUSESTATE2 dims;
    #elif DIRECTINPUT_VERSION == 0x0800 
    DIMOUSESTATE2 dims;
    #endif

    plhc = (pCpwLhc)cpw->ctx_localhost;

    if ( plhc->pdevmouse == 0 ) return false;

    /* acquire the mouse if possible */

    if ( plhc->dimouseacquired == false )
        if ( IDirectInputDevice2_Acquire( plhc->pdevmouse ) != DI_OK ) {
            /* printf("acquire fail.\n" ); lost focus */
            return false;
        }

    plhc->dimouseacquired = true;
            
    /* get the mouse state */

    memset( &dims, 0, sizeof( dims ) );

    #if   DIRECTINPUT_VERSION == 0x0300 
    if ( IDirectInputDevice2_GetDeviceState( plhc->pdevmouse, sizeof( DIMOUSESTATE ), &dims ) != DI_OK ) {
    #elif DIRECTINPUT_VERSION == 0x0500 
    if ( IDirectInputDevice2_GetDeviceState( plhc->pdevmouse, sizeof( DIMOUSESTATE ), &dims ) != DI_OK ) {
    #elif DIRECTINPUT_VERSION == 0x0700 
    if ( IDirectInputDevice2_GetDeviceState( plhc->pdevmouse, sizeof( DIMOUSESTATE2 ), &dims ) != DI_OK ) {
    #elif DIRECTINPUT_VERSION == 0x0800 
    if ( IDirectInputDevice2_GetDeviceState( plhc->pdevmouse, sizeof( DIMOUSESTATE2 ), &dims ) != DI_OK ) {
    #endif
        plhc->dimouseacquired = false;    
        return true;
    }

    info->x = dims.lX;
    info->y = dims.lY;
    info->z = dims.lZ;

    for( i = 0; i < CPW_MAX_BUTTONS; i++ )
        info->buttons[i] = (dims.rgbButtons[i] & 0x80) ? true : false;
    
    /* printf("mx:%d, my:%d\n", dims.lX, dims.lY ); */

    return true;
}

bool cpw_localhost_internal_dimouseinit( pCpw cpw )
{
    pCpwLhc             plhc;   /* localhost context */
    pCpwWin             pwin;   /* cpw window context */
    pCpwLhwc            plhwc;  /* localhost window context */

    plhc = (pCpwLhc)cpw->ctx_localhost;

    /* note: directinput mouse support di version >= directx 3.0 */

    /* create a directinput interface object if we haven't
       already created it. */

    if ( plhc->pdi != 0 ) goto acquiremouse;

    #if   DIRECTINPUT_VERSION == 0x0300 

    if( DirectInputCreate( GetModuleHandle(0), DIRECTINPUT_VERSION, 
                           (LPDIRECTINPUT*)&plhc->pdi, null ) != DI_OK ) 

    #elif DIRECTINPUT_VERSION == 0x0500 

    if( DirectInputCreate( GetModuleHandle(0), DIRECTINPUT_VERSION, 
                           (LPDIRECTINPUT*)&plhc->pdi, null ) != DI_OK ) 

    #elif DIRECTINPUT_VERSION == 0x0700 

    if( DirectInputCreate( GetModuleHandle(0), DIRECTINPUT_VERSION, 
                           (LPDIRECTINPUT*)&plhc->pdi, null ) != DI_OK ) 

    #elif DIRECTINPUT_VERSION == 0x0800 

    if( DirectInput8Create( GetModuleHandle(0), DIRECTINPUT_VERSION, 
                            &IID_IDirectInput8, &plhc->pdi, null ) != DI_OK ) 

    #endif

    { 
        /* we failed to create a di COM interface. fall
           back on winbase. */

        return false;
    }

    acquiremouse:

    /* create the di mouse device */

    if( IDirectInput2_CreateDevice( plhc->pdi, &GUID_SysMouse, 
                   (LPDIRECTINPUTDEVICE*)&plhc->pdevmouse, NULL ) != DI_OK ) 
    {
        /* odd, we failed to create a mouse device. fall
           back on winbase mouse access. */

        plhc->pdevmouse = 0;

        return false;
    }


    if( IDirectInputDevice2_SetDataFormat( plhc->pdevmouse, &c_dfDIMouse ) != DI_OK )
    {
        /* odd, we failed to set the mouse data format. fallback
           on winbase mouse access. */

        IDirectInputDevice2_Release( plhc->pdevmouse ); 

        return false;
    }

    /* get the foreground window handle for use in coop level settings */

    pwin   = cpw_windowlist_lookup( cpw, 0 );

    if ( pwin == 0 ) {

        cpw_error_set( cpw, cpw_error_invalidwindowid );

        IDirectInputDevice2_Release( plhc->pdevmouse ); 

        return false;
    }

    plhwc = (pCpwLhwc) pwin->plhwc;

    if( IDirectInputDevice2_SetCooperativeLevel( plhc->pdevmouse, plhwc->hwnd, 
                      DISCL_EXCLUSIVE | DISCL_FOREGROUND ) != DI_OK ) 
    { 
        /* odd, we failed to set the coop level. fallback
           on winbase mouse access. */

        IDirectInputDevice2_Release( plhc->pdevmouse ); 

        return false;
    } 

    plhc->dimouse = true;

    return true; 
}

#endif /* CPW_DIRECTINPUT_MOUSEACCESS */

/*************************************************************************/
/*                                                                       */
/*   Mouse information                                                   */
/*                                                                       */
/*************************************************************************/

uint_32 cpw_localhost_mousecaps( pCpw cpw, CpwMouseCapabilities * mcaps )
{
    uint_32 button = 0;
    uint_32 numbuttons = GetSystemMetrics( SM_CMOUSEBUTTONS );

    mcaps->buttons = numbuttons;

    if ( numbuttons > 0 )
        mcaps->xy = true;

    #ifdef SM_MOUSEWHEELPRESENT

    if ( GetSystemMetrics( SM_MOUSEWHEELPRESENT ) ) 
        mcaps->z = true;
        mcaps->buttons++;

    #endif

    return button;
}

bool cpw_localhost_mousestate( pCpw cpw, CpwMouseInfo * info )
{
    pCpwLhc plhc;

    plhc = cpw->ctx_localhost;

#ifdef CPW_DIRECTINPUT_MOUSEACCESS

    /* use di if it's working */

    if ( plhc->dimouse ) {

        cpw_localhost_internal_dimousegetdata( cpw, info );
        return true;

    } else {

        if ( cpw_localhost_internal_dimouseinit( cpw ) ) {
            cpw_localhost_internal_dimousegetdata( cpw, info );
            return true;
        }
    }

#endif /* CPW_DIRECTINPUT_MOUSEACCESS */

    info->x = plhc->mouse_relx;
    info->y = plhc->mouse_rely;
    info->z = plhc->mouse_relz;

    memcpy( info->buttons, plhc->mouse_buttons, sizeof( info->buttons ) );

    memset( plhc->mouse_buttons, 0, sizeof( plhc->mouse_buttons ) );

    plhc->mouse_relx = 0;
    plhc->mouse_rely = 0;
    plhc->mouse_relz = 0;

    return true;
}

/*************************************************************************/
/*                                                                       */
/*   direct keyboard access                                              */
/*                                                                       */
/*************************************************************************/

#ifdef CPW_DIRECTINPUT_KEYBOARDACCESS
#endif /* CPW_DIRECTINPUT_KEYBOARDACCESS */

/*************************************************************************/
/*                                                                       */
/*   joystick access                                                     */
/*                                                                       */
/*************************************************************************/

#ifdef CPW_DIRECTINPUT_JOYSTICKACCESS

/* di: callback for iterating each element of a joystick */

bool CALLBACK 
cpw_localhost_internal_di_iterateelements( const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pvRef )
{
    #if DIRECTINPUT_VERSION == 0x0500 
    LPDIRECTINPUT2        pdi;
    LPDIRECTINPUTDEVICE2  pdev;
    #elif DIRECTINPUT_VERSION == 0x0700 
    LPDIRECTINPUT2        pdi;
    LPDIRECTINPUTDEVICE2  pdev;
    #elif DIRECTINPUT_VERSION == 0x0800 
    LPDIRECTINPUT8        pdi;
    LPDIRECTINPUTDEVICE8  pdev;
    #endif

    CpwDirectInputEnumStorage * cpwdi;
    CpwJoystickList * list;
    uint_32 index;

    cpwdi = ( CpwDirectInputEnumStorage * ) pvRef;
    list  = ( CpwJoystickList * ) cpwdi->list; 
    index = cpwdi->id - 1;
    pdi   = cpwdi->pdi;
    pdev  = cpwdi->pdev;

    /* 
        Note: very very few (if any) standard joysticks support
        acceleration, velocity, and force values yet. But they will.. 
        
        Also, the Microsoft ForceFeedback 2 has a bug in it's 1.0 
        driver which reports acceleration value support, which it 
        doesn't. Be careful what you use, and test test test! 
    */

    if ( pdidoi->dwFlags & DIDOI_ASPECTVELOCITY ) {
        list->caps->vel[index] = true;
    }

    if ( pdidoi->dwFlags & DIDOI_ASPECTACCEL ) {
        list->caps->accel[index] = true;
    }

    if ( pdidoi->dwFlags & DIDOI_ASPECTFORCE ) {
        list->caps->force[index] = true;
    }
    
    #ifdef DEBUGJOYSTICKS
    {

      char buf[10000];

      if( pdidoi->dwType & DIDFT_AXIS ) {
          sprintf( buf, "%s:", pdidoi->tszName );
          cpw->cpw_print( buf );
      }

      if( pdidoi->dwType & DIDFT_BUTTON ) {
          sprintf( buf, "%s:", pdidoi->tszName );
          cpw->cpw_print( buf );
      }

      if ( pdidoi->dwType & DIDFT_POV ) {
          sprintf( buf, "%s:", pdidoi->tszName );
          cpw->cpw_print( buf );
      }

      if ( pdidoi->dwFlags & DIDOI_ASPECTVELOCITY ) {
          cpw->cpw_print( "velocity," );
      }

      if ( pdidoi->dwFlags & DIDOI_ASPECTACCEL ) {
          cpw->cpw_print( "accel," );
      }

      if ( pdidoi->dwFlags & DIDOI_ASPECTFORCE ) {
          cpw->cpw_print( "force," );
      }

      if ( pdidoi->dwFlags & DIDOI_ASPECTPOSITION ) {
          cpw->cpw_print( "position," );
      }

      if ( pdidoi->dwFlags & DIDOI_FFACTUATOR ) {
          cpw->cpw_print( "ffactuator," );
      }

      if ( pdidoi->dwFlags & DIDOI_FFEFFECTTRIGGER ) {
          cpw->cpw_print( "fftrigger," );
      }

      if ( pdidoi->dwFlags & DIDOI_POLLED ) {
          cpw->cpw_print( "polled" );
      }

      printf( "\n" );

    #endif

    return DIENUM_CONTINUE;
}

/* di: callback for iterating all joysticks */

bool CALLBACK
cpw_localhost_internal_di_iteratejoysticks( LPCDIDEVICEINSTANCE pdinst, LPVOID pvRef ) 
{ 
    #if DIRECTINPUT_VERSION == 0x0500 
    LPDIRECTINPUT2        pdi;
    LPDIRECTINPUTDEVICE2  pdev;
    #elif DIRECTINPUT_VERSION == 0x0700 
    LPDIRECTINPUT2        pdi;
    LPDIRECTINPUTDEVICE2  pdev;
    #elif DIRECTINPUT_VERSION == 0x0800 
    LPDIRECTINPUT8        pdi;
    LPDIRECTINPUTDEVICE8  pdev;
    #endif

    DIDEVCAPS             joyCaps; 
    LPCDIDATAFORMAT       format;
    DIPROPRANGE           propRange; 
    /* HRESULT hr; */

    /* our main data carrier into this callback */

    CpwDirectInputEnumStorage * cpwdi;

    uint_32           i;
    uint_32           index;  
    pCpw              cpw;    /* cpw context */
    pCpwLhc           plhc;   /* localhost context */
    CpwJoystickList*  list;   /* the list */
    pCpwWin  win;             /* cpw window context */
    pCpwLhwc lhwc;            /* localhost window context */

    /* grab everything were going to need from our storage structure */

    cpwdi = ( CpwDirectInputEnumStorage * ) pvRef;
    cpw   = cpwdi->cpw;
    plhc  = cpw->ctx_localhost;
    list  = ( CpwJoystickList * ) cpwdi->list; 
    index = cpwdi->id - 1;
    pdi   = cpwdi->pdi;

    /* get the first window handle for use in coop level settings */

    win   = cpw_windowlist_lookup( cpwdi->cpw, 0 );

    if ( win == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidwindowid );
        return DIENUM_STOP;
    }

    lhwc = (pCpwLhwc) win->plhwc;

    /* di : create a 'device handle' in pdev */

    #if DIRECTINPUT_VERSION == 0x0800 

    if( IDirectInput8_CreateDevice( pdi, &pdinst->guidInstance, 
                                    &pdev, NULL ) != DI_OK ) 

    #else

    if( IDirectInput2_CreateDevice( pdi, &pdinst->guidInstance, 
                                    (LPDIRECTINPUTDEVICE*)&pdev, NULL ) != DI_OK ) 

    #endif

        return DIENUM_CONTINUE; 

    /* save the pdev for enum objects callback below */

    cpwdi->pdev = pdev;

    /* di : get the devices capabilities */

    joyCaps.dwSize = sizeof( DIDEVCAPS ); 

    #if DIRECTINPUT_VERSION == 0x0800 

    if ( IDirectInputDevice8_GetCapabilities( pdev, &joyCaps ) != DI_OK ) {
        IDirectInputDevice8_Release( pdev ); 

    #else

    if ( IDirectInputDevice2_GetCapabilities( pdev, &joyCaps ) != DI_OK ) {
        IDirectInputDevice2_Release( pdev ); 

    #endif

        return DIENUM_CONTINUE; 
    }

    /* we found a device that's plugged in, fill the info structure on it */

    /* supports forcefeedback */

    if ( joyCaps.dwFlags & DIDC_FORCEFEEDBACK ) 
        list->caps[index].forcefeedback = true;

    /* axes supported flags */

    for ( i = 0; i < joyCaps.dwAxes; i++ ) {
        list->caps[index].axis[i] = true;
        if ( i == CPW_JOY_AXES ) break;
    }

    /* povs supported flags */

    for ( i = 0; i < joyCaps.dwPOVs; i++ ) {
        list->caps[index].pov[i] = true;
        if ( i == CPW_JOY_POVS ) break;
    }

    /* the number of buttons supported */

    list->caps[index].numbuttons  = joyCaps.dwButtons;

    /* di : set the device's 'data format' to 'joystick extended format'. 
       used when retrieving the state of the device. */

    format = &c_dfDIJoystick2;
    if( IDirectInputDevice2_SetDataFormat( pdev, format ) != DI_OK ) 
    { 
        /* couldn't get extended info, try for basic info */

        format = &c_dfDIJoystick;
        if( IDirectInputDevice2_SetDataFormat( pdev, format ) != DI_OK ) 
        { 
            IDirectInputDevice2_Release( pdev ); 
            return DIENUM_CONTINUE; 
        } 
    } 

    /* di : set the type of access we want to the device */

    if( IDirectInputDevice2_SetCooperativeLevel( pdev, lhwc->hwnd, 
                      DISCL_NONEXCLUSIVE | DISCL_BACKGROUND ) != DI_OK ) 
    { 
        IDirectInputDevice2_Release( pdev ); 
        return DIENUM_CONTINUE; 
    } 

    /*
      Useful for debugging sets and gets:

        switch ( hr ) {
            case DI_OK:
              hr = 0;
            break;
            case DI_PROPNOEFFECT:
              hr = 0;
            break;
            case DIERR_INVALIDPARAM:
              hr = 0;
            break;
            case DIERR_NOTINITIALIZED:  
              hr = 0;
            break;
            case DIERR_OBJECTNOTFOUND:  
              hr = 0;
            break;
            case DIERR_UNSUPPORTED: 
              hr = 0;
            break;
        }
    */

    /* di : set x axis range to ranges values */ 

    propRange.diph.dwSize       = sizeof(propRange); 
    propRange.diph.dwHeaderSize = sizeof(propRange.diph); 
    propRange.diph.dwObj        = DIJOFS_X; 
    propRange.diph.dwHow        = DIPH_BYOFFSET; 
    propRange.lMin              = list->ranges.axismin; 
    propRange.lMax              = list->ranges.axismax; 

    IDirectInputDevice2_SetProperty( pdev, DIPROP_RANGE, &propRange.diph );

    /* di : set y axis range to ranges values */ 

    propRange.diph.dwObj        = DIJOFS_Y; 

    IDirectInputDevice2_SetProperty(pdev, DIPROP_RANGE, &propRange.diph);

    /* di : set z axis range to ranges values */ 

    propRange.diph.dwObj        = DIJOFS_Z; 

    IDirectInputDevice2_SetProperty( pdev, DIPROP_RANGE, &propRange.diph );

    /* di : set slider 1 axis range to ranges values */ 

    propRange.diph.dwObj        = DIJOFS_SLIDER(1); 

    IDirectInputDevice2_SetProperty( pdev, DIPROP_RANGE, &propRange.diph );

    /* di : set slider 2 axis range to ranges values */ 

    propRange.diph.dwObj        = DIJOFS_SLIDER(2); 

    IDirectInputDevice2_SetProperty( pdev, DIPROP_RANGE, &propRange.diph );

    /* di : set rotation range to ranges values */ 

    propRange.diph.dwSize       = sizeof(propRange); 
    propRange.diph.dwHeaderSize = sizeof(propRange.diph); 
    propRange.diph.dwObj        = DIJOFS_RX; 
    propRange.diph.dwHow        = DIPH_BYOFFSET; 
    propRange.lMin              = list->ranges.rotmin; 
    propRange.lMax              = list->ranges.rotmax; 

    /* di : set rotation range for x axis */ 

    if ( IDirectInputDevice2_SetProperty( pdev, DIPROP_RANGE, &propRange.diph ) == DI_OK )
        list->caps[index].rot[0] = true;

    /* di : set rotation range for y axis */ 

    propRange.diph.dwObj        = DIJOFS_RY; 

    if ( IDirectInputDevice2_SetProperty( pdev, DIPROP_RANGE, &propRange.diph ) == DI_OK )
        list->caps[index].rot[1] = true;

    /* di : set rotation range for x axis */ 

    propRange.diph.dwObj        = DIJOFS_RZ; 

    if ( IDirectInputDevice2_SetProperty( pdev, DIPROP_RANGE, &propRange.diph ) == DI_OK )
        list->caps[index].rot[2] = true;

    /* enumerate extended capabilities */

    IDirectInputDevice2_EnumObjects( pdev, cpw_localhost_internal_di_iterateelements, (pVoid)cpwdi, DIDFT_ALL );

    /* di: aquire access to the device */

    IDirectInputDevice2_Acquire( pdev );

    /* save the device in our localhost joystick context */

    plhc->lhjoys[index].pdev = pdev;

    /* save the device id in the list */

    list->caps[index].id = cpwdi->id;

    /* save user's ranges in our localhost joystick context for normalization in poll */

    memcpy( &plhc->lhjoys[index].ranges, &list->ranges, sizeof( CpwJoystickRanges ) );

    /* save the cpw caps in our localhost joystick context */

    memcpy( &plhc->lhjoys[index].cpwcaps, &list->caps[index], sizeof( CpwJoystickCapabilities ) );

    /* inc the id */

    cpwdi->id++;

    /* only get the number of joysticks the user wants */

    if ( cpwdi->id > list->joysticks ) return DIENUM_STOP; 

    return DIENUM_CONTINUE; 
} 

/* di: poll the joystick state */

bool cpw_localhost_internal_di_polljoystick( pCpw cpw, CpwJoystickInfo * info ) 
{ 
    DIJOYSTATE2 joyState2;

    #if   DIRECTINPUT_VERSION == 0x0300 
    return false;
    #elif DIRECTINPUT_VERSION == 0x0500 
    LPDIRECTINPUTDEVICE2  pdev;
    #elif DIRECTINPUT_VERSION == 0x0700 
    LPDIRECTINPUTDEVICE2  pdev;
    #elif DIRECTINPUT_VERSION == 0x0800 
    LPDIRECTINPUTDEVICE8  pdev;
    #endif

    pCpwLhc plhc;
    uint_32 i;

    /* retrieve the localhost joy context based on the id passed in in info */

    plhc = cpw->ctx_localhost;
    pdev = plhc->lhjoys[info->id-1].pdev; 

    if ( pdev == null ) return false;

    /* Ping the joystick to update it's state info.
       On some joysticks this always fails because the
       device is not a polled device. */

    #if DIRECTINPUT_VERSION == 0x0500 
    IDirectInputDevice2_Poll( pdev );
    #elif DIRECTINPUT_VERSION == 0x0700 
    IDirectInputDevice2_Poll( pdev );
    #elif DIRECTINPUT_VERSION == 0x0800 
    IDirectInputDevice8_Poll( pdev );
    #endif

    if ( IDirectInputDevice2_GetDeviceState( pdev, sizeof( DIJOYSTATE2 ), &joyState2 ) != DI_OK )
      if ( IDirectInputDevice2_Acquire( pdev ) != DI_OK )
          return false;

    /* current axes values */

    info->axis[0] = joyState2.lX;
    info->axis[1] = joyState2.lY;
    info->axis[2] = joyState2.lZ;
    info->axis[3] = joyState2.rglSlider[0];
    info->axis[4] = joyState2.rglSlider[1];

    /* current axes rotation values */

    info->rot[0] = joyState2.lRx;
    info->rot[1] = joyState2.lRy;
    info->rot[2] = joyState2.lRz;

    /* pov hat states */

    info->pov[0] = joyState2.rgdwPOV[0];
    info->pov[1] = joyState2.rgdwPOV[1];
    info->pov[2] = joyState2.rgdwPOV[2];
    info->pov[4] = joyState2.rgdwPOV[3];

    /* printf( "pov:%-4d\n", info->pov[0] ); */

    /* button states */

    for ( i = 0; i < plhc->lhjoys[info->id-1].cpwcaps.numbuttons; i++ ) 
        info->buttons[i] = ( ( joyState2.rgbButtons[i] & 0x80 ) == 0 ? false : true );

    return true;

    /* extended values */

    info->vel[0] = joyState2.lVX;
    info->vel[1] = joyState2.lVY;
    info->vel[2] = joyState2.lVZ;
    info->vel[3] = joyState2.rglVSlider[0];
    info->vel[4] = joyState2.rglVSlider[1];

    info->accel[0] = joyState2.lAX;
    info->accel[1] = joyState2.lAY;
    info->accel[2] = joyState2.lAZ;
    info->accel[3] = joyState2.rglASlider[0];
    info->accel[4] = joyState2.rglASlider[1];

    /* printf( "vel:%-4d accel:%-4d\n", info->vel[0], info->accel[0] ); */

    return true;
} 

/* di : init joysticks */

bool cpw_localhost_internal_di_initjoysticks( pCpw cpw, CpwJoystickList * list ) 
{
    CpwDirectInputEnumStorage cpwdi;
    pCpwLhc                   plhc;

    cpwdi.cpw  = cpw;
    cpwdi.list = list;
    cpwdi.id   = 1;

    /* localhost context with our di COM interface pointer holder */

    plhc = (pCpwLhc) cpw->ctx_localhost;

    /* if we've already created a di COM interface, jump forward */

    if ( plhc->pdi != 0 ) goto enumeratejoys;

    /* create a directinput interface object. */

    #if   DIRECTINPUT_VERSION == 0x0300 
        return false;
    #elif DIRECTINPUT_VERSION == 0x0500 

        if( DirectInputCreate( GetModuleHandle(0), DIRECTINPUT_VERSION, 
                               (LPDIRECTINPUT*)&plhc->pdi, null ) == DI_OK ) 

    #elif DIRECTINPUT_VERSION == 0x0700 

        if( DirectInputCreate( GetModuleHandle(0), DIRECTINPUT_VERSION, 
                               (LPDIRECTINPUT*)&plhc->pdi, null ) == DI_OK ) 

    #elif DIRECTINPUT_VERSION == 0x0800 

        if( DirectInput8Create( GetModuleHandle(0), DIRECTINPUT_VERSION, 
                                &IID_IDirectInput8, &plhc->pdi, null ) == DI_OK ) 

    #endif
    { 
        enumeratejoys:

        cpwdi.pdi = plhc->pdi;

        /* enumerate joysticks attached to the sytem */

        #if   DIRECTINPUT_VERSION == 0x0300 
        return false;
        #elif DIRECTINPUT_VERSION == 0x0500 | DIRECTINPUT_VERSION == 0x0700 

        IDirectInput2_EnumDevices( plhc->pdi, DIDEVTYPE_JOYSTICK, 
           cpw_localhost_internal_di_iteratejoysticks, &cpwdi, DIEDFL_ATTACHEDONLY ); 

        #elif DIRECTINPUT_VERSION == 0x0800 

        IDirectInput8_EnumDevices( plhc->pdi, DI8DEVCLASS_GAMECTRL, 
           cpw_localhost_internal_di_iteratejoysticks, &cpwdi, DIEDFL_ATTACHEDONLY ); 

        #endif

        list->joysticks = cpwdi.id-1;

        return true; 

    }

    /* di didn't load, fall through to winbase joy access. probably
       it's not installed, or the version is lower than required. */

    return false;
}

/* di : free joystick references */

void cpw_localhost_internal_di_freejoysticks( pCpw cpw ) 
{
    pCpwLhc plhc;

    #if DIRECTINPUT_VERSION == 0x0500 
    LPDIRECTINPUTDEVICE2 pdev; 
    #elif DIRECTINPUT_VERSION == 0x0700 
    LPDIRECTINPUTDEVICE2 pdev; 
    #elif DIRECTINPUT_VERSION == 0x0800 
    LPDIRECTINPUTDEVICE8 pdev; 
    #endif

    plhc = (pCpwLhc)cpw->ctx_localhost;
    pdev = plhc->lhjoys[0].pdev; 

    /* free device 1 */

    if ( pdev != null ) {
        IDirectInputDevice2_Unacquire( pdev );
        IDirectInputDevice2_Release( pdev ); 
    }

    pdev = plhc->lhjoys[1].pdev; 

    /* free device 2 */

    if ( pdev != null ) {
        IDirectInputDevice2_Unacquire( pdev );
        IDirectInputDevice2_Release( pdev ); 
    }

    return;       
}

#endif /* CPW_DIRECTINPUT_JOYSTICKACCESS */

/* winbase : init joysticks */

bool cpw_localhost_internal_winbase_initjoysticks( pCpw cpw, CpwJoystickList * list ) 
{
    pCpwLhc plhc;
    JOYCAPS joyCaps;
    uint_32 index;

    plhc = cpw->ctx_localhost;

    /* 1 or 2 joysticks */

    if ( !joyGetNumDevs() ) {

        /* no joysticks available */

        list->joysticks = 0;
        return false;
    }

    index = 0;

    while ( index < list->joysticks ) {    

        /* configure the caps data for this joystick */

        if ( index == 0 ) {
            if ( joyGetDevCaps( JOYSTICKID1, &joyCaps, sizeof( joyCaps ) ) != JOYERR_NOERROR ) {
                list->joysticks = 0;
                return false;
            }
        } else {
            if ( joyGetDevCaps( JOYSTICKID2, &joyCaps, sizeof( joyCaps ) ) != JOYERR_NOERROR ) {
                list->joysticks = 1;
                return true;
            }
        }

        /* supports forcefeedback */

        list->caps[0].forcefeedback = false;

        /* axes supported flags */

        list->caps[0].axis[0] = true;
        list->caps[0].axis[1] = true;

        if ( joyCaps.wCaps & JOYCAPS_HASZ )
          list->caps[0].axis[2] = true;

        if ( joyCaps.wCaps & JOYCAPS_HASU )
          list->caps[0].axis[3] = true;

        if ( joyCaps.wCaps & JOYCAPS_HASV )
          list->caps[0].axis[4] = true;

        /* povs supported flags */

        if ( joyCaps.wCaps & JOYCAPS_HASPOV ) {

            list->caps[0].pov[0] = true;

            if ( joyCaps.wCaps & JOYCAPS_POVCTS )
              list->caps[0].variablepov = true;

        }

        /* the number of buttons supported */

        list->caps[0].numbuttons  = joyCaps.wNumButtons;

        /* no velocity, acceleration, or angular values with winbase access */

        /* save user's ranges in our localhost joystick context for normalization in poll */

        memcpy( &plhc->lhjoys[0].ranges, &list->ranges, sizeof( CpwJoystickRanges ) );

        /* save the device's ranges in our localhost joystick context */

        memcpy( &plhc->lhjoys[0].joycaps, &joyCaps, sizeof( JOYCAPS ) );

        /* save the cpw caps in our localhost joystick context */

        memcpy( &plhc->lhjoys[0].cpwcaps, &list->caps[0], sizeof( CpwJoystickCapabilities ) );
   
        /* save the device id in the list */

        list->caps[index].id = index+1;

        index++;

    }

    return true;
}

/* winbase : poll joystick's state */

bool cpw_localhost_internal_winbase_polljoystick( pCpw cpw, CpwJoystickInfo * info ) 
{
    JOYINFOEX           joyState;
    LPJOYCAPS           pjoyCaps;
    CpwJoystickRanges*  pranges;
    CpwJoystickCapabilities* pcpwcaps;
    pCpwLhc             plhc;
    HRESULT             hr;
    uint_32             i;

    plhc = cpw->ctx_localhost;

    /* cpw caps pointer */

    pcpwcaps = &plhc->lhjoys[0].cpwcaps;

    joyState.dwFlags = JOY_RETURNALL;
    joyState.dwSize  = sizeof( joyState );

    /* return variable or discrete pov values? */

    if ( pcpwcaps->variablepov ) 
        joyState.dwFlags = joyState.dwFlags | JOYCAPS_POVCTS;

    hr = JOYERR_UNPLUGGED;

    if ( info->id == 1 ) {
        hr = joyGetPosEx( JOYSTICKID1, &joyState );
        pjoyCaps = &plhc->lhjoys[0].joycaps;
        pranges  = &plhc->lhjoys[0].ranges;
    } else {
        hr = joyGetPosEx( JOYSTICKID2, &joyState );
        pjoyCaps = &plhc->lhjoys[1].joycaps;
        pranges  = &plhc->lhjoys[1].ranges;
    }

    if ( hr != JOYERR_NOERROR ) return false;

    /*
      typedef struct joyinfoex_tag { 
          DWORD dwSize; 
          DWORD dwFlags; 
          DWORD dwXpos; 
          DWORD dwYpos; 
          DWORD dwZpos; 
          DWORD dwRpos; 
          DWORD dwUpos; 
          DWORD dwVpos; 
          DWORD dwButtons; 
          DWORD dwButtonNumber; 
          DWORD dwPOV; 
      } JOYINFOEX; 
    */

    /* axis positions */

    /* assuming 0 -> x values. if they are negative, we have a problem and need to rework */
    
    info->axis[0] = (int)( ( (float)joyState.dwXpos / (float)pjoyCaps->wXmax ) * (float)pranges->axismax );
    info->axis[1] = (int)( ( (float)joyState.dwYpos / (float)pjoyCaps->wYmax ) * (float)pranges->axismax );
    info->axis[2] = (int)( ( (float)joyState.dwZpos / (float)pjoyCaps->wZmax ) * (float)pranges->axismax );
    info->axis[3] = (int)( ( (float)joyState.dwUpos / (float)pjoyCaps->wUmax ) * (float)pranges->axismax );
    info->axis[4] = (int)( ( (float)joyState.dwVpos / (float)pjoyCaps->wVmax ) * (float)pranges->axismax );

    /* z-axis rotation */

    info->rot[2] = (int)( ( (float)joyState.dwRpos / (float)pjoyCaps->wRmax ) * (float)pranges->rotmax );

    /* the pov hat */

    if ( pjoyCaps->wCaps & JOYCAPS_HASPOV ) {
        if ( pjoyCaps->wCaps & JOYCAPS_POVCTS ) {
            /* 0 through 35900 or -1 */
            info->pov[0] = joyState.dwPOV;
        } else {
            /* discrete value */
            switch( joyState.dwPOV ) {
                case JOY_POVBACKWARD:
                    info->pov[0] = CPW_POV_DOWN;
                break;
                case JOY_POVCENTERED:
                    info->pov[0] = CPW_POV_CENTERED;
                break;
                case JOY_POVFORWARD:
                    info->pov[0] = CPW_POV_UP;
                break;
                case JOY_POVLEFT:
                    info->pov[0] = CPW_POV_LEFT;
                break;
                case JOY_POVRIGHT:
                    info->pov[0] = CPW_POV_RIGHT;
                break;
                default:
                    /* info->pov[0] = CPW_POV_CENTERED; */
                break;
            }
        }
    }

    /* buttons */

    if ( pjoyCaps->wNumButtons > CPW_JOY_BUTTONS ) pjoyCaps->wNumButtons = CPW_JOY_BUTTONS;

    for ( i = 0; i < pjoyCaps->wNumButtons; i++ ) {
        if ( joyState.dwButtons & WinBaseButtonConstants[i] ) {
            info->buttons[i] = true;
        } else {
            info->buttons[i] = false;
        }
    }
    
    return true;
}

/* list available joysticks and init access to the number requested */

bool cpw_localhost_initjoysticks( pCpw cpw, CpwJoystickList * list ) 
{
    pCpwLhc lhc;

    lhc   = ( pCpwLhc ) cpw->ctx_localhost;

    #ifdef CPW_DIRECTINPUT_JOYSTICKACCESS

    if ( cpw_localhost_internal_di_initjoysticks( cpw, list ) ) {
        lhc->dijoysticks = true;
        return true;
    }

    /* fall through to winbase access on di init failure */

    #endif /* CPW_DIRECTINPUT_JOYSTICKACCESS */

    return cpw_localhost_internal_winbase_initjoysticks( cpw, list );
}

/* shutdown joystick interface if required. */

void cpw_localhost_freejoysticks( pCpw cpw ) 
{
    pCpwLhc plhc;

    plhc   = ( pCpwLhc ) cpw->ctx_localhost;

    #ifdef CPW_DIRECTINPUT_JOYSTICKACCESS

    if ( plhc->dijoysticks == true ) {
        cpw_localhost_internal_di_freejoysticks( cpw );
        return;
    }

    #endif /* CPW_DIRECTINPUT_JOYSTICKACCESS */

    /* nothing to do when using winbase */

    return;
}

/* poll the state of the joystick specified */

bool cpw_localhost_polljoystick( pCpw cpw, CpwJoystickInfo * info )
{
    pCpwLhc lhc;

    lhc   = ( pCpwLhc ) cpw->ctx_localhost;

    #ifdef CPW_DIRECTINPUT_JOYSTICKACCESS
    
    if ( lhc->dijoysticks )  /* using di? */
      if ( cpw_localhost_internal_di_polljoystick( cpw, info ) )
          return true;

    #endif /* CPW_DIRECTINPUT_JOYSTICKACCESS */

    return cpw_localhost_internal_winbase_polljoystick( cpw, info );
}


