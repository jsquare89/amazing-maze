/***************************************************************************/
/*                                                                         */
/*  cpw_platform.c                                                         */
/*                                                                         */
/*    The Cpw library interface to ?????.                                  */
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
/*  File Platform: ?????                                                   */
/*                                                                         */
/***************************************************************************/

/* rename this file and the .h so it indicates your platform. then set this 
   correctly. */

#include "cpw_platform.h"
#include "cpw_event.h"
#include "cpw_error.h"
#include "cpw_init.h"
#include "cpw_main.h"
#include "cpw_windowlist.h"
#include "cpw_joystick.h"

/* out of all the code in Cpw, this is where things can sometimes get ugly.
   please comment your code clearly, and in detail, so the next guy doesn't
   have to sift through a rats nest. thanks! */

/*************************************************************************/
/*                                                                       */
/*   init and exit.                                                      */
/*                                                                       */
/*************************************************************************/

/* 
   Initialization for the localhost adapter

    Whatever needs to be done for this platform to get things ready. This 
    function should create a CpwLocalhostContext and store anything in it 
    it needs. CpwLocalhostContext should be defined in the cpw_platform.h. 
    Cpw stores it in it's state as a pointer but doesn't do anything with 
    it. You can access it in subsequent calls at cpw->ctx_localhost. 

    Some cpw state values the localhost knows about need to be initialized
    as well like screen width and height.
*/

bool
cpw_localhost_init( pCpw cpw )
{
    CpwLocalhostContext * plhc;

    /* allocate a localhost context for ths platform */

    plhc = ( CpwLocalhostContext * ) cpwmalloc( sizeof( CpwLocalhostContext ) );
    cpw->ctx_localhost = (pVoid) plhc;

    if ( cpw->ctx_localhost == 0 ) {
        cpw_error_set( cpw, cpw_error_outofmemory );
        return false;
    }

    /* clear mem in our local localhost context */

    memset( plhc, 0, sizeof( CpwLocalhostContext ) );

    /* init your localhost context with whatever you need to
       access later on. */

    /* plhc->myvariable = mydata; */

    /* initialize values for cpw that the localhost knows about */

    /* cpw->cpw_screenWidth    = ???; */
    /* cpw->cpw_screenHeight   = ???; */

    /* init anything specific to OpenGL, like loading a gl
       library or similar. Don't create gl contexts here though, 
       these are done on a per window bases later on. */

    return true;
}

/* 
   Shutdown for the localhost adapter

   Any open windows will be destroyed before this call, but maybe
   you have some stuff to shut down from above. Don't forget to free your 
   localhost context memory.
*/

void
cpw_localhost_exit( pCpw cpw )
{
    CpwLocalhostContext* plhc = cpw->ctx_localhost;

    /* free the localhost context memory */

    cpwfree( plhc );
    cpw->ctx_localhost = 0;
}

/*************************************************************************/
/*                                                                       */
/*   windows                                                             */
/*                                                                       */
/*************************************************************************/

/* 
   Create a normal window

    Create a window and return a CpwLocalhostWindow struct pointer for it. 
    pCpwLhwc's are defined in the .h and can contain anything. Cpw
    stores them as a void* pointers and doesn't do anything with em. 
    They will be passed back in when actions on a particular window is
    required.

    The values for x, and y are desktop positions. Width and Height should 
    specify the window's client area width and height.

*/

pCpwLhwc
cpw_localhost_createwindow( pCpw cpw, uint_32 id, 
                            char* title, 
                            uint_32 x, uint_32 y, 
                            uint_32 width, uint_32 height,
                            uint_32 properties, bool expectmenu )
{
    pCpwLhc  plhc;
    pCpwLhwc plhwc;

    plhc = ( pCpwLhc ) cpw->ctx_localhost;
        
    /* create localhost window context for this window */

    plhwc = ( pCpwLhwc ) cpwmalloc( sizeof( CpwLocalhostWindow ) );

    if ( plhwc == 0 ) {
        cpw_error_set( cpw, cpw_error_outofmemory );
        return 0;
    }

    /*
    set window style properties

    if ( properties & CPW_WINDOWPROP_STANDARD ) {
    } else if ( properties & CPW_WINDOWPROP_POPUP ) {
    } else if ( properties & CPW_WINDOWPROP_NODRESSING ) {
    } else {
      standard
    }

    set window border style properties

    if ( properties & CPW_WINDOWPROP_THICKBORDER ) {
    } else if ( properties & CPW_WINDOWPROP_THINBORDER ) {
    } else if ( properties & CPW_WINDOWPROP_NOBORDER ) {
    } else {
      thick 
    }
    */

    /* plhwc->mywindowinfo = something; */

    /* set the window to the forground and display it. */

    /* set the cursor to CursorArrow.*/

    return plhwc;
}

/* 
   Create a fullscreen window

    Create a window and return a CpwLocalhostWindow struct pointer for it. 
    The window should be fullscreen and suitable for a fullscreen game.
    If possible the cursor should be turned off initially.

*/

pCpwLhwc
cpw_localhost_createfullscreenwindow( pCpw cpw, uint_32 id, char* title )
{
    pCpwLhc  plhc;
    pCpwLhwc plhwc;

    plhc = ( pCpwLhc ) cpw->ctx_localhost;
        
    /* create localhost window context for this window */

    plhwc = ( pCpwLhwc ) cpwmalloc( sizeof( CpwLocalhostWindow ) );

    if ( plhwc == 0 ) {
        cpw_error_set( cpw, cpw_error_outofmemory );
        return 0;
    }

    /* plhwc->mywindowinfo = something; */

    /* set the window to the forground and display it. */

    /* set cursor to CursorNone */

    return plhwc;
}

/* convert a regular window to fullscreen mode */

bool cpw_localhost_fullscreenwindow( pCpw cpw, pCpwWin wc )
{
    pCpwLhwc lhwc = wc->plhwc;
    return true;
}

/* convert a fullscreen window to regular one */

bool cpw_localhost_standardizewindow( pCpw cpw, pCpwWin wc )
{
    pCpwLhwc lhwc = wc->plhwc;

    return true;
}

/* destroy the window specified and all of it's resources */

bool cpw_localhost_destroywindow( pCpw cpw, pCpwWin wc )
{
    pCpwLhwc lhwc = wc->plhwc;
    return true;
}

/* set the title bar text of the window specified */

bool cpw_localhost_setwindowtitle( pCpwWin wc )
{
    pCpwLhwc lhwc = wc->plhwc;
    return true;
}

/* position the window on the desktop. wc->x and wc->y are 
   desktop coordinates. */

bool cpw_localhost_positionwindow( pCpwWin wc )
{
    pCpwLhwc lhwc = wc->plhwc;
    return true;
}

/* reshape the window frame. wc->width and height are
   client area values. */

bool cpw_localhost_reshapewindow( pCpwWin wc )
{
    pCpwLhwc lhwc = wc->plhwc;
    return true;
}

/* max the window width and height out to the desktop, 
   but keep any window dressing. make sure and set the
   x, y, width, and height to the new values. */

bool cpw_localhost_maximizewindow( pCpwWin wc )
{
    pCpwLhwc lhwc = wc->plhwc;

    return true;
}

/* iconify the window */

bool cpw_localhost_inconifywindow( pCpwWin wc )
{
    pCpwLhwc lhwc = wc->plhwc;
    return true;
}

/* restore an iconic or maximized window */

bool cpw_localhost_restorewindow( pCpwWin wc )
{
    pCpwLhwc lhwc = wc->plhwc;
    return true;
}

/* hide the window completely */

bool cpw_localhost_hidewindow( pCpwWin wc )
{
    pCpwLhwc lhwc = wc->plhwc;
    return true;
}

/* show the window completely */

bool cpw_localhost_showwindow( pCpwWin wc )
{
    pCpwLhwc lhwc = wc->plhwc;
    return true;
}

/* set a window to the foreground z-order */

bool cpw_localhost_setforeground( pCpwWin wc )
{
    pCpwLhwc lhwc = wc->plhwc;
    return true;
}

/* get the current x,y position and width,height of the window 
   and store it in the Cpw window context. */

bool cpw_localhost_windowinfo( pCpwWin wc )
{
    pCpwLhwc lhwc = wc->plhwc;
    /*
    wc->x      = window's desktop x;
    wc->y      = window's desktop y;
    wc->width  = window's client h;
    wc->height = window's client w;
    */
    return true;
}

/* push the window down one in the z-order */

bool cpw_localhost_pushwindow( pCpwWin wc ) 
{
    pCpwLhwc lhwc = wc->plhwc;
    return false;
}

/* push the window to the bottom of the z-order */

bool cpw_localhost_popwindow( pCpwWin wc ) 
{
    pCpwLhwc lhwc = wc->plhwc;
    return false;
}

/*************************************************************************/
/*                                                                       */
/*   menus                                                               */
/*                                                                       */
/*************************************************************************/

/* create a menu for a window's menu bar and display it */

bool cpw_localhost_assignmenutowindow( pCpw cpw, pCpwWin wc, pCpwMenu menu )
{
    pCpwLhwc lhwc = wc->plhwc;

    /* create the menu */

    /* assign the menu to the window */

    return true;
}

/* update a menu due to changes made by the user */

bool cpw_localhost_updatemenu( pCpw cpw, pCpwWin wc, pCpwMenu menu )
{
    pCpwLhwc lhwc = wc->plhwc;

    return true;
}

/* detach a menu from the menu bar */

void cpw_localhost_unassignmenu( pCpw cpw, pCpwWin wc )
{
    pCpwLhwc lhwc = wc->plhwc;
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
    pCpwLhwc lhwc = wc->plhwc;

    return true;
}

/*************************************************************************/
/*                                                                       */
/*   Cursors                                                             */
/*                                                                       */
/*************************************************************************/

/* set the cursor type for this window. this is called when the cursor
   enters the window. (custom cursors aren't supported yet.) */

bool cpw_localhost_setcursor( pCpw cpw, pCpwWin wc ) 
{
    CpwCursor c = wc->cursor;
    switch( c ) {

        case CursorArrow:       /* standard arrow */
        break;
        case CursorHand:        /* a grab hand or similar */
        break;
        case CursorNo:          /* action denied */
        break;
        case CursorQuestion:    /* help or question */
        break;
        case CursorBeam:        /* <---> */
        break;
        case CursorWait:        /* hourglass */
        break;
        case CursorCrosshair:   /* crosshair */
        break;
        case CursorNone:        /* no cursor visible */
        break;
        case CursorSizeNSEW:    /* NorthSouth <-> EastWest arrow */
        break;
        case CursorSizeNS:      /* North <-> South arrow */
        break;
        case CursorSizeNeSw:    /* NorthEast <-> SouthWest arrow */
        break;
        case CursorSizeEW:      /* East <-> West arrow */
        break;
        case CursorSizeSeNw:    /* SouthEast <-> NorthWest arrow */
        break;
        case CursorCustom:      /* not supported yet */
        break;
    }
    return false;
}

/* the cursor left a cpw window, restore it to the system's default
   cursor if you need too. */

bool cpw_localhost_restorecursor( pCpw cpw ) 
{
    return true;
}

/* position the cursor at x,y in the client area of the window specified */

bool cpw_localhost_positioncursor( pCpwWin wc, uint_32 x, uint_32 y )
{
    pCpwLhwc lhwc = wc->plhwc;
    return true;
}

/* position the cursor at the center of the client area of the window specified */

bool cpw_localhost_centercursor( pCpwWin wc )
{
    pCpwLhwc lhwc = wc->plhwc;
    return true;
}

/*************************************************************************/
/*                                                                       */
/*   OpenGL                                                              */
/*                                                                       */
/*************************************************************************/

/* set the pixelformat */

bool
cpw_localhost_setpixelformat( pCpw cpw, pCpwLhwc lhwc )
{
    return true;
}

/* after setting the draw surface format, you usually have to 
   create a gl rendering context for the window. this function
   is called directly after cpw_localhost_setpixelformat. */

bool
cpw_localhost_createglcontext( pCpw cpw, pCpwLhwc lhwc )
{
    if ( !lhwc ) return false;
    /* lhwc->glContext = glCreateContext( lhwc->hdc ); 
    if ( lhwc->glContext == 0 ) {
        cpw_error_set( cpw, cpw_error_createcontextfailed ); /* this should never really happen 
        return false;
    } */
    return true;
}

/* destroy the window's gl rendering context */

bool
cpw_localhost_destroyglcontext( pCpw cpw, pCpwLhwc lhwc )
{
    if ( !lhwc ) return false;
    /* glDeleteContext( lhwc->glContext ); */
    return true;
}

/* make this window's gl rendering context current */

bool
cpw_localhost_makecurrent( pCpw cpw, pCpwLhwc lhwc )
{
    if ( !lhwc ) return false;
    /*if ( !glMakeCurrent( lhwc->hdc, lhwc->glContext ) ) {
        cpw_error_set( cpw, cpw_error_setcurrentcontextfailed ); /* this should never really happen
        return false;
    }*/
    return true;
}

/* swap a window's gl buffers */

bool
cpw_localhost_swapbuffers( pCpwLhwc lhwc )
{
    bool ret = false;
    if ( !lhwc ) return false;
    /*ret = SwapBuffers( lhwc->hdc );*/
    return ret;
}

/*************************************************************************/
/*                                                                       */
/*   Keyboard key state tracker                                          */
/*                                                                       */
/*************************************************************************/

/* store a key's state in the internal keystate buffer */

/* in event process below, ascii / unicode key values should be converted
   to cpw key constants. when a key is pressed, the event should be passed 
   into cpw and this routine should also be called to set the key's state
   in the cpw key state buffer.

   cpw->keyboard_state is a 256 byte array that tracks key states. 
   See cpw_keymouse.h / .c for a list of all the key constants. cpw_win32.c
   is a good example of how this processing takes place. */

void cpw_localhost_internal_keypress( pCpw cpw, uint_32 key, bool state ) 
{
    cpw->keyboard_state[key] = state;
}

/*************************************************************************/
/*                                                                       */
/*   window events                                                       */
/*                                                                       */
/*************************************************************************/

/* 
    Window Event Processing

    Windows must generate events. These events need to be handed into the 
    user's application in a platform independant way. Cpw supports a number 
    of window events which your adapter needs to inject into the to Cpw
    event stack. 

    Events you should hand in are the following:

      CPW_MOUSECLICK_EVENT        - a mouse click in a window
      CPW_MOUSEMOTION_EVENT       - mouse motion when a button is not held down
      CPW_MOUSEDRAG_EVENT         - mouse drag event when a button is held down
      CPW_MOUSEENTRY_EVENT        - mouse entering or leaving a window
      CPW_KEYBOARD_EVENT          - ascii key press
      CPW_SYSKEYBOARD_EVENT       - system key press
      CPW_DESTROY_EVENT           - the user closed the window
      CPW_POSITION_EVENT          - the user moved the window on the desktop
      CPW_DISPLAY_EVENT           - the window requires repainting
      CPW_VISIBILITY_EVENT        - hide->show, show->hide, min->max, max->min
      CPW_RESHAPE_EVENT           - the window is being resized

    Events Cpw sends automatically without requiring you to do anything:

      CPW_CREATE_EVENT            - sent on successful return of createwindow

    Cpw is single threaded. Due to this, events can't be injected into the stack
    when the stack is being accessed. As such, events must be processed by the 
    localhost only when Cpw says it's ok. 

    cpw_localhost_processevents is called when Cpw wants the localhost to 
    process 'count' number of events. It should return true if there 
    are more events to process. count is currently 3 but can be changed 
    by the user when the lib is compiled. 

    Mouse messages usually include an x,y. the origin is in the upper left
    hand corner of the client window, not including any window dressing.

    To inject a message into the stack use the following calls:

    ----------------------------------------------------------------------------
    void cpw_hostevent_setfocus( pCpw cpw, uint_32 id ); 
    void cpw_hostevent_lostfocus( pCpw cpw, uint_32 id ); 
    void cpw_hostevent_cursorenter( pCpw cpw, uint_32 id );
    void cpw_hostevent_cursorleft( pCpw cpw, uint_32 id );
    void cpw_hostevent_draw( pCpw cpw, uint_32 id );
    void cpw_hostevent_reshape( pCpw cpw, uint_32 id, uint_32 width, uint_32 height );
    void cpw_hostevent_destroy( pCpw cpw, uint_32 id );
    void cpw_hostevent_position( pCpw cpw, uint_32 id, uint_32 x, uint_32 y );
    void cpw_hostevent_visibility( pCpw cpw, uint_32 id, uint_32 state );
    void cpw_hostevent_mouseclick( pCpw cpw, uint_32 id, uint_32 state, uint_32 button, uint_32 x, uint_32 y );
    void cpw_hostevent_mousedrag( pCpw cpw, uint_32 id, uint_32 button, int_32 x, int_32 y );
    void cpw_hostevent_mousemove( pCpw cpw, uint_32 id, uint_32 x, uint_32 y );
    void cpw_hostevent_keyboard( pCpw cpw, uint_32 id, uint_32 key, bool shift, uint_32 state, uint_32 x, uint_32 y );
    void cpw_hostevent_systemkeyboard( pCpw cpw, uint_32 id, uint_32 key, uint_32 state, uint_32 x, uint_32 y );
    void cpw_hostevent_menuselect( pCpw cpw, uint_32 id, uint_32 menuid, uint_32 entryid );
    ----------------------------------------------------------------------------

    for info on various constants see cpw_event.h. 

    For performance, developers can filter events from their application.
    You can check to see if a particular event is filter with the following 
    call:     

    bool cpw_event_filtered( cpw, CPW_MOUSEMOTION_EVENT )

    Notes on keyboard processing:

    Cpw key events are stored in the event stack using cpw key constants
    and a boolean value indicating the shift status. cpw key constants are 
    listed in cpw_keymouse.h. cpw_win32.c is a good example of how this processing
    takes place. Cpw key constants do not differentiate between uppercase
    and lowercase, the shift flag is used internally to translate between 
    upper/lower case keys. 
    
      Cpw System keys:

      switch (wParam)  (VK_XX are win32 constants - switch to your key constants)
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
      }

      if ( keyisgoingdown ) {
          
          cpw_localhost_internal_keypress( cpw, key, true );
          cpw_hostevent_systemkeyboard( cpw, winid, key, CPW_KEYMOD_DOWN, point.x, point.y );

      } else if ( keyisgoingup ) {

          cpw_localhost_internal_keypress( cpw, key, false );
          cpw_hostevent_systemkeyboard( cpw, winid, key, CPW_KEYMOD_UP, point.x, point.y );
      
      }


      Ascii keys:

      switch ( keyboardkey ) 
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
      }          

      if ( keyisgoingdown ) {

          cpw_localhost_internal_keypress( cpw, key, true );
          cpw_hostevent_keyboard( cpw, winid, key, theshiftstate, CPW_KEYMOD_DOWN, point.x, point.y );

      } else if ( keyisgoingup ) {

          cpw_localhost_internal_keypress( cpw, key, false );
          cpw_hostevent_keyboard( cpw, winid, key, theshiftshift, CPW_KEYMOD_UP, point.x, point.y );

      }

    Notes on mouse and keyboard x,y values:

    Mouse move, click, and drag events, and keyboard keypresses are accompanied 
    by a x, y mouse coordinate. These values should be window client coords, with 
    a origin in the upper left of the window.

    Notes on window reshape:

    Width and height should be client width and heights. Window dressing shoudl not
    be included. 

    Notes on window position:

    X and y should be the entire window's x and y desktop positions, including
    any dressing.    

*/

bool
cpw_localhost_processevents( pCpw cpw, uint_32 count )
{
    while ( count > 0 ) {

        /* process event */

        /* if no more events, return false */

        /* if os requests shutdown of app - call */
        /* cpwBreakLoop( cpw ); */

        count--;
    }
    /* if there are more events to process */
    return true;
}


/*************************************************************************/
/*                                                                       */
/*   Video Resolution of the screen                                      */
/*                                                                       */
/*************************************************************************/

/* returns a list of CpwVideoHint's holding all the possible display
   settings. see cpw_gamemode.h for more info. */

bool cpw_localhost_listvideomodes( pCpw cpw, CpwVideoList * list )
{
    CpwVideoHints * hint;
    CpwVideoHints * current;
    uint_32 index = 0;
    uint_32 count = 0;

    /* the first entry is always holds the current video setting */

    /* get settings */

    current = cpwmalloc( sizeof( CpwVideoHints ) );        

    if ( current == 0 ) {
        cpw_error_set( cpw, cpw_error_outofmemory );
        list->size = 0;
        return false;
    }

    list->list[count] = current;

    /*
    current->width  = screenwidth;
    current->height = screenheight;
    current->depth  = colordepth;
    current->active = true;*/

    count++;

    /* get the rest of the entries */

    
    while ( 1==1/*enumerate settings*/ ) {

        index++;

        /* create a hint list entry */
                     
        hint = cpwmalloc( sizeof( CpwVideoHints ) );        

        if ( hint == 0 ) {
            cpw_error_set( cpw, cpw_error_outofmemory );
            list->size = count;
            return false;
        }

        list->list[count] = hint;

        /*
        current->width  = screenwidth;
        current->height = screenheight;
        current->depth  = colordepth;
        hint->active = false;*/

        if ( count == MAX_VLIST ) break;

        count++;
    }

    list->size = count-1;
    return true;
}

/* set the main screen's video format using a hints values. */

bool cpw_localhost_setvideomode( pCpw cpw, CpwVideoHints hints ) 
{
    /* 
    change the display, return false if it fails and an error.

    cpw_error_set( cpw, cpw_error_failedtosetvideo );
    return false; */

    /* update some settings in the cpw state */
    
    /*
    cpw->cpw_screenWidth    = width;
    cpw->cpw_screenHeight   = height;*/

    return true;
}

/* if at any point in time we changed the video settings, change them back
   on exit. */

void cpw_localhost_resetvideomode( pCpw cpw ) 
{
}

/*************************************************************************/
/*                                                                       */
/*   high frequency timer                                                */
/*                                                                       */
/*************************************************************************/

/* 
    Cpw relies on a high frequency counter for it's timer operations.
    Hopefully your host has one, if not, you'll have to simulate it with
    the standard time functions.

    cpw_localhost_hpfreq( void )

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

    the resolution of hpfreq() must be at least 1000.0 to get
    millisecond timers to work.

*/

float_64 cpw_localhost_hpfreq( void )
{
    return 1.0;
}

float_64 cpw_localhost_hpcount( void )
{
    return 1.0;
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

    /* GetWindowsDirectory( buf, 4096 ); */
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
    pStr file = null;

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
/*   Mouse information                                                   */
/*                                                                       */
/*************************************************************************/

uint_32 cpw_localhost_mousecaps( pCpw cpw, CpwMouseCapabilities * mcaps )
{
    uint_32 numbuttons = 3;

    mcaps->buttons = numbuttons;

    if ( numbuttons > 0 )
        mcaps->xy = true;

    /* 3rd axis? (wheel or similar) */
    mcaps->z = true;

    return numbuttons;
}

/* fill the mouse state struct. mouse x, y, and z values must be 
   relative to the last call to this routine. (note that for mouse 
   events, the values passed into cpw should be client window coords.
   see the win32.c for an example on how absolute values can be converted to
   relative values for this routine. ) */

bool cpw_localhost_mousestate( pCpw cpw, CpwMouseInfo * info )
{
    pCpwLhc plhc;

    plhc = cpw->ctx_localhost;

    /*
    info->x = plhc->mouse_relx;
    info->y = plhc->mouse_rely;
    info->z = plhc->mouse_relz;

    memcpy( info->buttons, plhc->mouse_buttons, sizeof( info->buttons ) );

    memset( plhc->mouse_buttons, 0, sizeof( plhc->mouse_buttons ) );

    plhc->mouse_relx = 0;
    plhc->mouse_rely = 0;
    plhc->mouse_relz = 0;
    */

    return true;
}

/*************************************************************************/
/*                                                                       */
/*   joystick access                                                     */
/*                                                                       */
/*************************************************************************/

/* list available joysticks and init access to the number requested */

bool cpw_localhost_initjoysticks( pCpw cpw, CpwJoystickList * list ) 
{
    pCpwLhc lhc;

    lhc   = ( pCpwLhc ) cpw->ctx_localhost;

    return true;
}

/* shutdown joystick interface if required. */

void cpw_localhost_freejoysticks( pCpw cpw ) 
{
    pCpwLhc plhc;

    plhc   = ( pCpwLhc ) cpw->ctx_localhost;

    return;
}

/* poll the state of the joystick specified */

bool cpw_localhost_polljoystick( pCpw cpw, CpwJoystickInfo * info )
{
    pCpwLhc lhc;

    lhc   = ( pCpwLhc ) cpw->ctx_localhost;

    return false;
}


