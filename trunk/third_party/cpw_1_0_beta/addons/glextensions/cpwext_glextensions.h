/***************************************************************************/
/*                                                                         */
/*  cpwext_glextensions.h                                                  */
/*                                                                         */
/*    Initializes common OpenGL extension interfaces and provides OpenGL   */
/*    1.3 functionality under Win32.                                       */
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

/***************************************************************************/
/*                                                                         */
/*  OpenGL Extension .c and .h Code Information:                           */
/*                                                                         */
/*    Copyright (c) 2001-2002 Lev Povalahev                                */
/*                                                                         */
/*    levp@gmx.net                                                         */
/*                                                                         */
/*    http://www.uni-karlsruhe.de/~uli2/                                   */
/*                                                                         */
/***************************************************************************/

#ifndef __cpwext_glextensions_h__
#define __cpwext_glextensions_h__

#ifdef CPW_INTERN

#include "cpw_config.h"
#include "cpw_state.h"
#include "extgl.h"

#else

#define CPWDLL_EXTERN

#include "include/cpw_config.h"
#include "include/cpw_state.h"
#include "extgl.h"

#endif

CPW_BEGIN_HEADER

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*   cpwextInitOpenGLExtensions                                          */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Inits OpenGL 1.3 functionality and common extension interfaces.    */
  /*                                                                       */
  typedef struct _ExtensionTypes  GLExtensionSupport;
  CPW_API bool   
  cpwextInitOpenGLExtensions( pCpw cpw, GLExtensionSupport * info );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*   cpwextOpenGLExtensions                                              */
  /*                                                                       */
  /* <Description>                                                         */
  /*                                                                       */
  CPW_API void   
  cpwextOpenGLExtensions( pCpw cpw );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /*   internal functions                                                  */
  /*                                                                       */
  /*************************************************************************/

#ifdef CPW_INTERN

#endif /* CPW_INTERN */

CPW_END_HEADER

#endif
