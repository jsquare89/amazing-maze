/***************************************************************************/
/*                                                                         */
/*  cpw_joystick.c                                                         */
/*                                                                         */
/*    Joystick polling interface.                                          */
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

#include "cpw_joystick.h"
#include "cpw_error.h"
#include "cpw_timers.h"
#include CPW_LOCALHOST_H

/*************************************************************************/
/*                                                                       */
/*   init and exit.                                                      */
/*                                                                       */
/*************************************************************************/

bool cpw_joystick_init( pCpw cpw )
{
    /* allocate the joystick context memory */

    cpw->ctx_joystick = cpwmalloc( sizeof( CpwJoystickContext ) );

    if ( cpw->ctx_joystick == 0 ) { 
        cpw_error_set( cpw, cpw_error_outofmemory );
        return false; 
    }

    memset( cpw->ctx_joystick, 0, sizeof( CpwJoystickContext ) );
    return true;
}

void cpw_joystick_exit( pCpw cpw )
{
    /* free adapter joystick resources if needed */

    cpw_localhost_freejoysticks( cpw );

    /* free context memory */

    cpwfree( cpw->ctx_joystick );
}

/*************************************************************************/
/*                                                                       */
/*   joystick api                                                        */
/*                                                                       */
/*************************************************************************/

bool  cpwInitJoysticks( pCpw cpw, CpwJoystickList * list )
{
    if ( list == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }

    if ( list->joysticks > CPW_MAX_JOYSTICKS ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }

    /* set the default ranges if they have not been set */

    if ( !list->ranges.axis ) {
        list->ranges.axismin = CPW_JOY_AXISMIN;
        list->ranges.axismax = CPW_JOY_AXISMAX;
    }

    if ( !list->ranges.rotation ) {
        list->ranges.rotmin = CPW_JOY_ROTATIONMIN;
        list->ranges.rotmax = CPW_JOY_ROTATIONMAX;
    }

    if ( !list->ranges.velocity ) {
        list->ranges.velmin = CPW_JOY_VELOCITYMIN;
        list->ranges.velmax = CPW_JOY_VELOCITYMAX;
    }

    if ( !list->ranges.accel ) {
        list->ranges.accelmin = CPW_JOY_ACCELMIN;
        list->ranges.accelmax = CPW_JOY_ACCELMAX;
    }

    return cpw_localhost_initjoysticks( cpw, list );
}

/* set an internal timer to return joystick data each delay */

bool cpwJoystickCallback( pCpw cpw, CpwJoystickCallback joyCallback, uint_32 joyid, uint_32 delay )
{
    pCpwJoystickContext ctx = ( pCpwJoystickContext ) cpw->ctx_joystick;

    if ( joyid > CPW_MAX_JOYSTICKS ) {
        cpw_error_set( cpw, cpw_error_invalidjoystickid );
        return false;
    }

    /* check to see if we are resetting this callback */

    if ( ctx->joyCallback[joyid-1] > 0 ) {
        /* ToDo: lookup timer and change delay if needed or kill if cb is null. */
        ctx->joyCallback[joyid-1] = (pVoid) joyCallback;
        return true;
    }

    /* create a new callback / internal timer with an id of 'joyid' */

    ctx->timerid[joyid-1] = cpw_timers_createinternal( cpw, CPW_TIMER_INTERNAL_JOYSTICK, true, delay, joyid );
    ctx->joyCallback[joyid-1] = (pVoid) joyCallback;

    return true;
}

/* callback from cpw_timer */

void cpw_joystick_timout( pCpw cpw, uint_32 id )
{
    CpwJoystickInfo info;
    pCpwJoystickContext ctx = ( pCpwJoystickContext ) cpw->ctx_joystick;

    /* clear info */

    memset( &info, 0, sizeof( CpwJoystickInfo ) );

    /* store the joyid in info */

    info.id = id;

    /* call poll to fill info. on error poll will set error code */

    if ( !cpwJoystickPoll( cpw, &info ) )
        return;

    /* call the callback */

    if ( ctx->joyCallback[id-1] != 0 ) 
        ctx->joyCallback[id-1]( cpw, &info );
}

/* force a joystick callback */

bool cpwJoystickPing( pCpw cpw, uint_32 joyid )
{
    if ( joyid > CPW_MAX_JOYSTICKS ) {
        cpw_error_set( cpw, cpw_error_invalidjoystickid );
        return false;
    }

    cpw_joystick_timout( cpw, joyid );

    return false;
}

/* poll the joystick for it's current state */

bool cpwJoystickPoll( pCpw cpw, CpwJoystickInfo * info )
{
    if ( info == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }

    if ( info->id > CPW_MAX_JOYSTICKS || info->id == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidjoystickid );
        return false;
    }

    return cpw_localhost_polljoystick( cpw, info );
}


