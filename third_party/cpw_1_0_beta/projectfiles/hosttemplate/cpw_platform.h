/***************************************************************************/
/*                                                                         */
/*  cpw_platform.h                                                         */
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

#ifndef __cpw_myplatform_h__
#define __cpw_myplatform_h__

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
  /* <Struct>                                                              */
  /*    CpwLocalhostContext                                                */
  /*                                                                       */
  /* <Description>                                                         */
  /*    The localhost's context. Stored in Cpw. The localhost context      */
  /*    contains platform specific state information.                      */
  /*                                                                       */
  struct _CpwLocalhostContext 
  {
    int i;
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
    int i;
  };
  typedef struct _CpwLocalhostWindow  CpwLocalhostWindow;
  typedef struct _CpwLocalhostWindow* pCpwLhwc;
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
