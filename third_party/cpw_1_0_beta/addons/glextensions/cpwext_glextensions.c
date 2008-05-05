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

#include "cpwext_glextensions.h"

bool   
cpwextInitOpenGLExtensions( pCpw cpw, GLExtensionSupport * info )
{
    return glInitExtensionLibrary( info );
}

void   
cpwextOpenGLExtensions( pCpw cpw )
{}
