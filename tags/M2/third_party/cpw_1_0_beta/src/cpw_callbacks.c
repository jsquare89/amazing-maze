/***************************************************************************/
/*                                                                         */
/*  cpw_callbacks.c                                                        */
/*                                                                         */
/*    Default global event callbacks called by Cpw.                        */
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

#include "cpw_callbacks.h"
#include "cpw_window.h"

void defaultCreateCallback( pCpw cpw, uint_32 id, bool flag )
{
    if ( flag == false ) cpwDestroyWindow( cpw, id );
}

void defaultDisplayCallback( pCpw cpw, uint_32 id )
{
}

void defaultReshapeCallback( pCpw cpw, uint_32 id, uint_32 w, uint_32 h )
{
}

void defaultVisibilityCallback( pCpw cpw, uint_32 id, uint_32 state )
{
}

void defaultPositionCallback( pCpw cpw, uint_32 id, uint_32 x, uint_32 y )
{
}

void defaultMouseClickCallback( pCpw cpw, uint_32 id, uint_32 state, uint_32 button, uint_32 x, uint_32 y )
{
}

void defaultMouseDragCallback( pCpw cpw, uint_32 id, uint_32 button, int_32 x, int_32 y )
{
}

void defaultMouseMoveCallback( pCpw cpw, uint_32 id, uint_32 x, uint_32 y )
{
}

void defaultMouseEntryCallback( pCpw cpw, uint_32 id, uint_32 state )
{
}

void defaultKeyboardCallback( pCpw cpw, uint_32 id, uint_32 key, uint_32 state, uint_32 x, uint_32 y )
{
}

void defaultSystemKeyboardCallback( pCpw cpw, uint_32 id, uint_32 key, uint_32 state, uint_32 x, uint_32 y )
{
}


