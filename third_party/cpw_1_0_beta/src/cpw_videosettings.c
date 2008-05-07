/***************************************************************************/
/*                                                                         */
/*  cpw_videosettings.c                                                    */
/*                                                                         */
/*    Setting video resolution of the desktop.                             */
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

#include "cpw_videosettings.h"
#include "cpw_window.h"
#include "cpw_error.h"
#include CPW_LOCALHOST_H

/*************************************************************************/
/*                                                                       */
/*   init and exit.                                                      */
/*                                                                       */
/*************************************************************************/

bool cpw_videosettings_init( pCpw cpw )
{
    return true;
}

void cpw_videosettings_exit( pCpw cpw )
{
    /* if we have changed the video settings, change them back */

    cpw_localhost_resetvideomode( cpw );
}

/*************************************************************************/
/*                                                                       */
/*   video modes api                                                     */
/*                                                                       */
/*************************************************************************/

/* changes the video resolution of the default display device. */

bool cpwChangeVideoMode( pCpw cpw, CpwVideoHints hints )
{
    return cpw_localhost_setvideomode( cpw, hints );
}

/* if changes have been made, reset back to defaults */

bool cpwResetVideoMode( pCpw cpw )
{
    cpw_localhost_resetvideomode( cpw );
    return true;
}

/* list all of the video modes supported by the host */

bool cpwListVideoModes( pCpw cpw, CpwVideoList * list )
{
    if ( list == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }

    memset( list, 0, sizeof( CpwVideoList ) );

    return cpw_localhost_listvideomodes( cpw, list );
}

/* free a list of video modes. ToDo: I probably should not
   be doing this here. I should just call into the 
   adapter. */

bool cpwFreeVideoList( pCpw cpw, CpwVideoList * list )
{
    uint_32 index = 0;

    if ( list == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }

    while ( index <= list->size ) {
        cpwfree( list->list[index] );
        index++;
    }

    memset( list, 0, sizeof( CpwVideoList ) );

    return true;
}

 
