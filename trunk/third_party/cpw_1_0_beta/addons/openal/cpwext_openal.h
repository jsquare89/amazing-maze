/***************************************************************************/
/*                                                                         */
/*  cpwext_openal.h                                                        */
/*                                                                         */
/*    Initializes the OpenAL library and has some nice helper functions    */
/*    for using the WAV file loading routines in alc.                      */
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
/*  To use this extension:                                                 */
/*                                                                         */
/*      1) Download the Cpw library source.                                */
/*                                                                         */
/*      2) Open the Cpw project your using and add                         */
/*         the cpwext_openal* files to it.                                 */
/*                                                                         */
/*      3) Depending on your platform, you may have to compile OpenAL.     */
/*         (www.openal.org) If your using Win32, you can optionally        */
/*         download and install the Creative Labs OpenAL developer sdk     */
/*         which comes with pre-compiled binaries and headers.             */
/*         (developer.creative.com)                                        */
/*                                                                         */
/*      4) Add an include search path to the openal headers you            */
/*         installed or downloaded in step 3.                              */
/*                                                                         */
/*      5) compile Cpw with OpenAL.                                        */
/*                                                                         */
/***************************************************************************/

#ifndef __cpwext_openal_h__
#define __cpwext_openal_h__

#ifdef CPW_INTERN

#include "cpw_config.h"
#include "cpw_state.h"

#else

#include "include/cpw_config.h"
#include "include/cpw_state.h"

#endif

CPW_BEGIN_HEADER

#include <al/al.h>
#include <al/alc.h>
#include <al/alu.h>
#include <al/alut.h>

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*   CpwextOpenALContext                                                 */
  /*                                                                       */
  /* <Description>                                                         */
  /*                                                                       */
  struct _CpwextOpenALContext 
  {
	  pVoid device;
	  pVoid context;
  };
  typedef struct _CpwextOpenALContext  CpwextOpenALContext;
  typedef struct _CpwextOpenALContext* pCpwextOpenAL;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*   cpwextInitOpenAL                                                    */
  /*                                                                       */
  /* <Description>                                                         */
  /*                                                                       */
  CPW_API bool   
  cpwextInitOpenAL( pCpw cpw ); 
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*   cpwextFreeOpenAL                                                    */
  /*                                                                       */
  /* <Description>                                                         */
  /*                                                                       */
  CPW_API void   
  cpwextFreeOpenAL( pCpw cpw ); 
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
