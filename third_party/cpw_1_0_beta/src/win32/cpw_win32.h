/***************************************************************************/
/*                                                                         */
/*  cpw_win32.h                                                            */
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

#ifndef __cpw_win32_h__
#define __cpw_win32_h__

#include "cpw_config.h"
#include "cpw_state.h"
#include "cpw_window.h"
#include "cpw_menus.h"
#include "cpw_videosettings.h"
#include "cpw_joystick.h"
#include "cpw_keymouse.h"
#include CPW_OPENGL_H

CPW_BEGIN_HEADER

#ifdef CPW_INTERN

  /*************************************************************************/
  /*                                                                       */
  /* <Define>                                                              */
  /*    CPW_LOCALHOST_WIN32_CLASSNAME                                      */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Win32 specifc define for windows class name.                       */
  /*                                                                       */
  #define CPW_LOCALHOST_WIN32_CLASSNAME   "CPWWindow"
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /*   DirectInput joystick access                                         */
  /*                                                                       */
  /*************************************************************************/

  #pragma comment ( lib, "winmm.lib" ) /* always link to windows multimedia library */

  #ifdef CPW_DIRECTINPUT_JOYSTICKACCESS

  #define DI_INCLUDED

  /* include and link to directinput or directinput8 */

  #include <dinput.h>
  
  #pragma comment ( lib, "dxguid.lib" ) /* guiid definitions */
  #if DIRECTINPUT_VERSION == 0x0800 
  #pragma comment ( lib, "dinput8.lib" )
  #else
  #pragma comment ( lib, "dinput.lib" )
  #endif

  /* used as storage for di's enumerate joystick devices routine */

  struct _CpwDirectInputEnumStorage
  {

      pCpw                  cpw;
      CpwJoystickList*      list;

      #if   DIRECTINPUT_VERSION == 0x0300 
      #error joystick access not supported with DirectInput 3.0
      #elif DIRECTINPUT_VERSION == 0x0500 
      LPDIRECTINPUT2        pdi;
      LPDIRECTINPUTDEVICE2  pdev;
      #elif DIRECTINPUT_VERSION == 0x0700 
      LPDIRECTINPUT2        pdi;
      LPDIRECTINPUTDEVICE2  pdev;
      #elif DIRECTINPUT_VERSION == 0x0800 
      LPDIRECTINPUT8        pdi;
      LPDIRECTINPUTDEVICE8  pdev;
      #endif
      uint_32               id;

  }; 
  typedef struct _CpwDirectInputEnumStorage CpwDirectInputEnumStorage;

  #endif /* CPW_DIRECTINPUT_JOYSTICKACCESS */

  /* localhost joystick context */

  struct _CpwLocalhostJoystick
  {
      #ifdef CPW_DIRECTINPUT_JOYSTICKACCESS

        #if   DIRECTINPUT_VERSION == 0x0300 
        #error joystick access not supported with DirectInput 3.0
        #elif DIRECTINPUT_VERSION == 0x0500 
        LPDIRECTINPUTDEVICE2 pdev;
        #elif DIRECTINPUT_VERSION == 0x0700 
        LPDIRECTINPUTDEVICE2 pdev;
        #elif DIRECTINPUT_VERSION == 0x0800 
        LPDIRECTINPUTDEVICE8 pdev;
        #endif

      #endif /* CPW_DIRECTINPUT_JOYSTICKACCESS */

      JOYINFOEX               joyinfo; /* winbase joystick state */
      JOYCAPS                 joycaps; /* winbase joystick ranges */

      CpwJoystickRanges       ranges;  /* copy of user's normalization values */
      CpwJoystickCapabilities cpwcaps; /* copy of cpw joystick capabilities */
  };
  typedef struct _CpwLocalhostJoystick CpwLocalhostJoystick;

  /*************************************************************************/
  /*                                                                       */
  /*   DirectInput vs. WinBase keyboard access                             */
  /*                                                                       */
  /*************************************************************************/

  #ifdef CPW_DIRECTINPUT_KEYBOARDACCESS

  /* include and link to directinput if were not already */

  #ifndef DI_INCLUDED

  #define DI_INCLUDED

  #include <dinput.h>

  #pragma comment ( lib, "dxguid.lib" ) /* guiid definitions */
  #if DIRECTINPUT_VERSION == 0x0800 
  #pragma comment ( lib, "dinput8.lib" )
  #else
  #pragma comment ( lib, "dinput.lib" )
  #endif

  #endif /* NOT DI_INCLUDED */

  #endif /* CPW_DIRECTINPUT_KEYBOARDACCESS */

  /*************************************************************************/
  /*                                                                       */
  /*   DirectInput mouse access                                            */
  /*                                                                       */
  /*************************************************************************/

  #ifdef CPW_DIRECTINPUT_MOUSEACCESS

  /* include and link to directinput if were not already */

  #ifndef DI_INCLUDED

  #define DI_INCLUDED

  #include <dinput.h>

  #pragma comment ( lib, "dxguid.lib" ) /* guiid definitions */
  #if DIRECTINPUT_VERSION == 0x0800 
  #pragma comment ( lib, "dinput8.lib" )
  #else
  #pragma comment ( lib, "dinput.lib" )
  #endif

  #endif /* NOT DI_INCLUDED */

  #endif /* CPW_DIRECTINPUT_MOUSEACCESS */

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    CpwLocalhostContext                                                */
  /*                                                                       */
  /* <Description>                                                         */
  /*    The localhost's context. Stored in Cpw. The localhost context      */
  /*    contains platform specific state information.                      */
  /*                                                                       */
  struct _CpwLocalhostContext 
  {
    HINSTANCE             moduleInstance;
    char                  classname[50];
    uint_32               foregroundWindow;
    uint_32               cursorWindow;
    
    /* relative mouse position tracking */

    int_32                mouse_x;
    int_32                mouse_y;
    int_32                mouse_z;
    int_32                mouse_relx;
    int_32                mouse_rely;
    int_32                mouse_relz;
    bool                  mouse_buttons[CPW_MAX_BUTTONS];

    /* windows system font file listings */

    HANDLE                fontSearch;
    pStr                  fontfile;

    /* direct input COM interface pointer (if required) */

    #if defined(CPW_DIRECTINPUT_MOUSEACCESS) | defined(CPW_DIRECTINPUT_JOYSTICKACCESS)

      #if   DIRECTINPUT_VERSION == 0x0300 
      LPDIRECTINPUT         pdi;
      #elif DIRECTINPUT_VERSION == 0x0500 
      LPDIRECTINPUT2        pdi;
      #elif DIRECTINPUT_VERSION == 0x0700 
      LPDIRECTINPUT2        pdi;
      #elif DIRECTINPUT_VERSION == 0x0800 
      LPDIRECTINPUT8        pdi;
      #endif

    #endif

    /* joystick device info storage */

    CpwLocalhostJoystick  lhjoys[CPW_MAX_JOYSTICKS]; 
    bool                  dijoysticks;       /* using di for joy access? */
    bool                  dimouse;           /* using di for mouse access? */

    /* direct input mouse device pointer */

    #if defined(CPW_DIRECTINPUT_MOUSEACCESS)

      bool                  dimouseacquired;

      #if   DIRECTINPUT_VERSION == 0x0300 
      LPDIRECTINPUTDEVICE   pdevmouse; 
      #elif DIRECTINPUT_VERSION == 0x0500 
      LPDIRECTINPUTDEVICE2   pdevmouse; 
      #elif DIRECTINPUT_VERSION == 0x0700 
      LPDIRECTINPUTDEVICE2   pdevmouse; 
      #elif DIRECTINPUT_VERSION == 0x0800 
      LPDIRECTINPUTDEVICE8   pdevmouse; 
      #endif

    #endif /* CPW_DIRECTINPUT_MOUSEACCESS */

  };
  typedef struct _CpwLocalhostContext  CpwLocalhostContext;
  typedef struct _CpwLocalhostContext* pCpwLhc;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    CpwLocalhostWindow                                                 */
  /*                                                                       */
  /* <Description>                                                         */
  /*    The localhost window context. Stored in each Cpw window context.   */
  /*    Contains platform specific window state information.               */
  /*                                                                       */
  struct _CpwLocalhostWindow 
  {
    HGLRC         glContext;
    HWND          hwnd;
    HDC           hdc;
    HMENU         hmenu;
    DWORD         winstyle;
    bool          updates;
  };
  typedef struct _CpwLocalhostWindow  CpwLocalhostWindow;
  typedef struct _CpwLocalhostWindow* pCpwLhwc;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Const Array>                                                         */
  /*    WinBaseButtonConstants                                             */
  /*                                                                       */
  /* <Description>                                                         */
  /*    An array of the winbase joystick button constants used in checking */
  /*    button state information.                                          */
  /*                                                                       */
  static DWORD 
  WinBaseButtonConstants[32] = {
    JOY_BUTTON1,  JOY_BUTTON2,  JOY_BUTTON3,  JOY_BUTTON4,  JOY_BUTTON5,
    JOY_BUTTON6,  JOY_BUTTON7,  JOY_BUTTON8,  JOY_BUTTON9,  JOY_BUTTON10,
    JOY_BUTTON11, JOY_BUTTON12, JOY_BUTTON13, JOY_BUTTON14, JOY_BUTTON15,
    JOY_BUTTON16, JOY_BUTTON17, JOY_BUTTON18, JOY_BUTTON19, JOY_BUTTON20,
    JOY_BUTTON21, JOY_BUTTON22, JOY_BUTTON23, JOY_BUTTON24, JOY_BUTTON25,
    JOY_BUTTON26, JOY_BUTTON27, JOY_BUTTON28, JOY_BUTTON29, JOY_BUTTON30,
    JOY_BUTTON31, JOY_BUTTON32
  };
  /*                                                                       */
  /*************************************************************************/
    
  /*************************************************************************/
  /*                                                                       */
  /*   Localhost adapter API                                               */
  /*                                                                       */
  /*************************************************************************/

  /* init and exit */

  bool cpw_localhost_init( pCpw cpw );
  void cpw_localhost_exit( pCpw cpw );

  /* find and return the localhost's directory to it's fonts. 
     return an empty string if such a thing doesn't exist. */

  pStr cpw_localhost_fontpath( void );
  pStr cpw_localhost_iteratefiles( pCpw cpw, bool reset, pStr path );

  /* creating a top level window */

  pCpwLhwc
  cpw_localhost_createwindow( pCpw cpw, uint_32 id, 
                              char* title, 
                              uint_32 x, uint_32 y, 
                              uint_32 width, uint_32 height,
                              uint_32 properties, bool expectmenu );

  /* creating a fullscreen window */

  pCpwLhwc
  cpw_localhost_createfullscreenwindow( pCpw cpw, uint_32 id, char* title );

  /* convert a regular window to fullscreen mode */

  bool cpw_localhost_fullscreenwindow( pCpw cpw, pCpwWin wc );

  /* convert a fullscreen window to regular one */

  bool cpw_localhost_standardizewindow( pCpw cpw, pCpwWin wc );

  /* destroy a window and it's resources */

  bool cpw_localhost_destroywindow( pCpw cpw, pCpwWin wc );

  /* assigning a menu to a window */

  bool cpw_localhost_assignmenutowindow( pCpw cpw, pCpwWin wc, pCpwMenu menu );
  void cpw_localhost_unassignmenu( pCpw cpw, pCpwWin wc );
  bool cpw_localhost_updatemenu( pCpw cpw, pCpwWin window, pCpwMenu menu );

  /* display a popup menu */

  bool cpw_localhost_displaypopup( pCpw cpw, pCpwWin wc, pCpwMenu menu, uint_32 x, uint_32 y );

  /* set the draw surface format for this window */

  bool cpw_localhost_setpixelformat( pCpw cpw, pCpwLhwc lhwc );

  /* create the opengl rendering context for this window */

  bool cpw_localhost_createglcontext( pCpw cpw, pCpwLhwc lhwc );

  /* destroy the gl rendering context for this window */

  bool cpw_localhost_destroyglcontext( pCpw cpw, pCpwLhwc lhwc );

  /* make the gl rendering context for this window current */

  bool cpw_localhost_makecurrent( pCpw cpw, pCpwLhwc lhwc );

  /* swap the gl buffers for this window */

  bool cpw_localhost_swapbuffers( pCpwLhwc lhwc );

  /* sleep for milliseconds */

  void cpw_localhost_sleep( uint_32 milli );

  /* process count localhost window events */

  bool cpw_localhost_processevents( pCpw cpw, uint_32 count );

  /* high frequency counter access */

  float_64 cpw_localhost_hpfreq( void );
  float_64 cpw_localhost_hpcount( void );

  /* misc. window actions */

  bool cpw_localhost_setwindowtitle( pCpwWin wc );

  bool cpw_localhost_setforeground( pCpwWin wc );
  bool cpw_localhost_positionwindow( pCpwWin wc );
  bool cpw_localhost_reshapewindow( pCpwWin wc );
  bool cpw_localhost_windowinfo( pCpwWin wc );

  bool cpw_localhost_inconifywindow( pCpwWin wc );
  bool cpw_localhost_maximizewindow( pCpwWin wc );
  bool cpw_localhost_restorewindow( pCpwWin wc );

  bool cpw_localhost_hidewindow( pCpwWin wc );
  bool cpw_localhost_showwindow( pCpwWin wc );

  bool cpw_localhost_pushwindow( pCpwWin wc );
  bool cpw_localhost_popwindow( pCpwWin wc );

  /* cursor settings */

  bool cpw_localhost_setcursor( pCpw cpw, pCpwWin wc );
  bool cpw_localhost_restorecursor( pCpw cpw );
  bool cpw_localhost_positioncursor( pCpwWin wc, uint_32 x, uint_32 y );
  bool cpw_localhost_centercursor( pCpwWin wc );

  /* video resolution settings */

  bool cpw_localhost_setvideomode( pCpw cpw, CpwVideoHints hints );
  bool cpw_localhost_listvideomodes( pCpw cpw, CpwVideoList * list );
  void cpw_localhost_resetvideomode( pCpw cpw );

  /* joystick interface */

  bool cpw_localhost_initjoysticks( pCpw cpw, CpwJoystickList * list );
  bool cpw_localhost_polljoystick( pCpw cpw, CpwJoystickInfo * info );
  void cpw_localhost_freejoysticks( pCpw cpw );

  /* mouse info */

  uint_32 cpw_localhost_mousecaps( pCpw cpw, CpwMouseCapabilities * mcaps );
  bool    cpw_localhost_mousestate( pCpw cpw, CpwMouseInfo * info );

#endif /* CPW_INTERN */

CPW_END_HEADER

#endif
