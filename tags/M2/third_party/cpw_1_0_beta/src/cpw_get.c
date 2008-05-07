/***************************************************************************/
/*                                                                         */
/*  cpw_get.c                                                              */
/*                                                                         */
/*    Querying for various application constants.                          */
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

#include "cpw_get.h"
#include "cpw_windowlist.h"
#include CPW_OPENGL_H

/* 
    You can query specific window information via cpwGetWindowInfo and cpwListWindows.
    You can query video formats via cpwListVideoModes.
    You can query fonts available via cpwListLocalFonts.
    You can query joysticks and their state via the joystick api.
    You can query extension support via cpwIterateExtensions and cpwExtensionSupport.
    You can query error info via cpwGetLastError.
    You can query mouse capabilities and state via cpwMouseCapabilities and cpwMouseState.
    You can query keyboard state via cpwKeyState.

    cpwGet is available partially for GLUT compatability and for
    communicating random other bits of data, state, and constant values.

*/

int_64 cpwGet( pCpw cpw, uint_32 parameter ) 
{
    switch ( parameter ) 
    {
        /* init values */

        case CPW_INIT_WINDOW_X:
            return cpw->win_initx;

        case CPW_INIT_WINDOW_Y:
            return cpw->win_inity;

        case CPW_INIT_WINDOW_WIDTH:
            return cpw->win_initwidth;

        case CPW_INIT_WINDOW_HEIGHT:
            return cpw->win_initheight;

        case CPW_INIT_DISPLAY_MODE:
            return cpw->cpw_displaymode;

        /* localhost display values */

        case CPW_SCREEN_WIDTH:
            return cpw->cpw_screenwidth;

        case CPW_SCREEN_HEIGHT:
            return cpw->cpw_screenheight;

        case CPW_SCREEN_WIDTH_MM:
        case CPW_SCREEN_HEIGHT_MM:
            return 0;

        /* running time */

        case CPW_ELAPSED_TIME:
            return 420;

        /* foreground window information */

        case CPW_WINDOW_FOREGROUND:
            return cpw->win_foregroundid;

        case CPW_WINDOW_GLCURRENT:
            return cpw->win_currentid;

        case CPW_WINDOW_COUNT:
            return cpw_windowlist_length( cpw );

        case CPW_VERSION:
            return (int_64)CpwVersion;

        case CPW_WINDOW_X:
        {
            if ( cpw->win_foregroundid == 0 ) {
                /* no foreground window, return default */
                return cpw->win_initx;
            }

            {
                CpwWindowInfo info;
                cpwGetWindowInfo( cpw, &info, cpw->win_foregroundid );
                return info.x;

            }
        }

        case CPW_WINDOW_Y:
        {
            if ( cpw->win_foregroundid == 0 ) {
                /* no foreground window, return default */
                return cpw->win_inity;
            }

            {
                CpwWindowInfo info;
                cpwGetWindowInfo( cpw, &info, cpw->win_foregroundid );
                return info.y;

            }
        }

        case CPW_WINDOW_WIDTH:
        {
            if ( cpw->win_foregroundid == 0 ) {
                /* no foreground window, return default */
                return cpw->win_initwidth;
            }

            {
                CpwWindowInfo info;
                cpwGetWindowInfo( cpw, &info, cpw->win_foregroundid );
                return info.width;
            }
        }

        case CPW_WINDOW_HEIGHT:
        {
            if ( cpw->win_foregroundid == 0 ) {
                /* no foreground window, return default */
                return cpw->win_initwidth;
            }

            {
                CpwWindowInfo info;
                cpwGetWindowInfo( cpw, &info, cpw->win_foregroundid );
                return info.height;
            }
        }

        case CPW_MOUSE_BUTTONS:
            return CPW_MAX_BUTTONS;

        /* localhost OpenGL driver info */

        case CPW_DRIVER_VENDOR:
        {
            char* p = (char*)glGetString( GL_VENDOR );
            if ( p == 0 ) return 0;
            setString( &cpw->cpw_driverinfo, p );
            return (int_64)str( cpw->cpw_driverinfo );
        }
            
        case CPW_DRIVER_RENDERER:
        {
            char* p = (char*)glGetString( GL_RENDERER );
            if ( p == 0 ) return 0;
            setString( &cpw->cpw_driverinfo, p );
            return (int_64)str( cpw->cpw_driverinfo );
        }

        case CPW_DRIVER_VERSION:
        {
            char* p = (char*)glGetString( GL_VERSION );
            if ( p == 0 ) return 0;
            setString( &cpw->cpw_driverinfo, p );
            return (int_64)str( cpw->cpw_driverinfo );
        }

        case CPW_PLATFORM:
            return CPW_THIS_PLATFORM;

        default:
            return 0;
    }
}
