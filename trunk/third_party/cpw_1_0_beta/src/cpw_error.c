/***************************************************************************/
/*                                                                         */
/*  cpw_error.c                                                            */
/*                                                                         */
/*    Querying for and setting last error values.                          */
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

#include "cpw_error.h"

int_32 cpwGetLastError( pCpw cpw ) 
{
    return cpw->err_code;
}

void cpwSetLastError( pCpw cpw, int_32 errorcode ) 
{
    cpw->err_code = errorcode;
}

void cpw_error_set( pCpw cpw, int_32 errorcode ) 
{
    cpw->err_code = errorcode;
}
















































































































































































/********************************************************
******** The GLUT Altar *********************************
*********************************************************

 "Capture work mask for work that needs to be done to this
  window, then clear the window's work mask (excepting the
  dummy work bit, see below).  Then, process the captured
  work mask.  This allows callbacks in the processing the
  captured work mask to set the window's work mask for
  subsequent processing."

 BeginPaint(hwnd, &ps); Must have this for some dumb Win32 reason. 
 EndPaint(hwnd, &ps);

*********************************************************/