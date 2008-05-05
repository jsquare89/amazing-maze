/***************************************************************************/
/*                                                                         */
/*  cpw_state.c                                                            */
/*                                                                         */
/*    The Cpw library state context & library init and exit.               */
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

#include "cpw_state.h"
#include "cpw_event.h"
#include "cpw_init.h"
#include "cpw_window.h"
#include "cpw_windowlist.h"
#include "cpw_menus.h"
#include "cpw_timers.h"
#include "cpw_joystick.h"
#include "cpw_videosettings.h"
#include "cpw_primitives.h"
#include "cpw_glextensions.h"
#include "cpw_perftracker.h"
#include "cpw_font.h"
#include CPW_LOCALHOST_H

/*************************************************************************/
/*                                                                       */
/*   init and exit.                                                      */
/*                                                                       */
/*************************************************************************/

bool
cpwInitContext( pCpw * cpw ) 
{
    if ( cpw == null ) return false;
    if ( *cpw != null ) return true;

    *cpw = (pCpw) cpwmalloc( sizeof( CpwContext ) );

    if ( *cpw == 0 ) { return false; }

    memset( *cpw, 0, sizeof( CpwContext ) );

    /* cpw core api init */

    if ( cpw_init_init( *cpw )          == 0 ) { return false; }
    if ( cpw_localhost_init( *cpw )     == 0 ) { return false; }
    if ( cpw_perftracker_init( *cpw )   == 0 ) { return false; }
    if ( cpw_font_init( *cpw )          == 0 ) { return false; }
    if ( cpw_event_init( *cpw )         == 0 ) { return false; }
    if ( cpw_window_init( *cpw )        == 0 ) { return false; }
    if ( cpw_menus_init( *cpw )         == 0 ) { return false; }
    if ( cpw_timers_init( *cpw )        == 0 ) { return false; }
    if ( cpw_videosettings_init( *cpw ) == 0 ) { return false; }
    if ( cpw_primitives_init( *cpw )    == 0 ) { return false; }
    if ( cpw_glextensions_init( *cpw )  == 0 ) { return false; }
    if ( cpw_joystick_init( *cpw )      == 0 ) { return false; }

    /* cpw extension api init */


    (*cpw)->cpw_initsuccess = true;
    return true;
}

bool 
cpwFreeContext( pCpw * cpw ) 
{
    if ( cpw == null ) return false;
    if ( *cpw == null ) return true;

    cpw_glextensions_exit( *cpw );  /* free resources */
    cpw_primitives_exit( *cpw );    /* free primitive drawing resources */
    cpw_videosettings_exit( *cpw ); /* restore pre-gamemode settings */
    cpw_timers_exit( *cpw );        /* kill timers */
    cpw_window_close( *cpw );       /* send close events to open windows */
    cpw_event_exit( *cpw );         /* flushs all window events */
    cpw_menus_exit( *cpw );         /* destroy all menus */
    cpw_window_exit( *cpw );        /* manually destroys open windows */
    cpw_font_exit( *cpw );          /* free font library */
    cpw_perftracker_exit( *cpw );   /* dump stats to print handler */
    cpw_joystick_exit( *cpw );      /* shutdown joystick interface */
    cpw_localhost_exit( *cpw );     /* shutdonw lh adapter */
    cpw_init_exit( *cpw );          /* shutdown cpw */
    
    freeStr( &(*cpw)->cpw_driverinfo ); /* free cpwGet string for driver info if it's allocated */

    cpwfree( *cpw );                /* free state memory */
    *cpw = 0;                       /* return null pointer */

    return true;
}

/* user definable state contexts */

bool cpwSetUserdata( pCpw cpw, pVoid userdata )
{
    cpw->ctx_user = userdata;
    return true;
}


pVoid cpwGetUserdata( pCpw cpw )
{
    return cpw->ctx_user;
}
