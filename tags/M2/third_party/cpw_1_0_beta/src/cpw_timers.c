/***************************************************************************/
/*                                                                         */
/*  cpw_timers.c                                                           */
/*                                                                         */
/*    The Cpw library Timer interface.                                     */
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

#include "cpw_timers.h"
#include "cpw_error.h"
#include "cpw_linkedlist.h"
#include "cpw_joystick.h"
#include CPW_LOCALHOST_H

/*************************************************************************/
/*                                                                       */
/*   init and exit.                                                      */
/*                                                                       */
/*************************************************************************/

bool cpw_timers_init( pCpw cpw )
{
    ll_initList( &cpw->list_timers );
    cpw->timers = false;
    return true;
}

void cpw_timers_exit( pCpw cpw )
{
    pCpwTimer timer;

    timer = cpw_timers_iteratestart( cpw );

    if ( timer == 0 ) return;
        
    while ( timer != 0 ) {
        cpwfree( timer );
        timer = cpw_timers_iteratenext( cpw );
    }

    ll_deleteList( &cpw->list_timers );
    return;
}

/*************************************************************************/
/*                                                                       */
/*   create & destroy for a timer api                                    */
/*                                                                       */
/*************************************************************************/

bool cpwTimerCallback( pCpw cpw, uint_32 milli, uint_32 id, bool redo, 
    CpwTimerCallback timerCallback )
{
    float_64 seconds;

    /* allocate a new timer struct */

    pCpwTimer timer = cpwmalloc( sizeof( CpwTimer ) );   

    if ( timer == 0 ) {
        cpw_error_set( cpw, cpw_error_outofmemory );
        return false;
    }
    memset( timer, 0, sizeof( CpwTimer ) );

    /* offset in seconds for this timer */

    seconds = (float_64)milli / (float_64)1000.0;

    /* add it to our linked list */

    timer->listid = ll_addVoid( &cpw->list_timers, (void *) timer );

    cpw->timers = true;

    /* setup */

    timer->internal      = false;
    timer->timerid       = id;
    timer->redo          = redo;
    timer->timerCallback = timerCallback;
    timer->hpdiff        = seconds * cpw_localhost_hpfreq();
    timer->hpcount       = cpw_localhost_hpcount(); /* running */
    
    return true;
}

bool  cpwKillTimer( pCpw cpw, uint_32 id )
{
    pCpwTimer timer;

    timer = cpw_timers_iteratestart( cpw );

    if ( timer == 0 ) return false;
        
    while ( timer != 0 ) {
        if ( timer->timerid == id )
            return ll_deleteElement( &cpw->list_timers, timer->listid );
        timer = cpw_timers_iteratenext( cpw );
    }
    return true;
}

/*************************************************************************/
/*                                                                       */
/*   managing timers                                                     */
/*                                                                       */
/*************************************************************************/

/* start an iteration of all timers */

pCpwTimer
cpw_timers_iteratestart( pCpw cpw )
{
    if ( !ll_initIterate( &cpw->list_timers ) ) return 0;
    return (pCpwTimer)le_getVoid( ll_getNext( &cpw->list_timers ) );
}

/* get next timer or 0 for no more */

pCpwTimer
cpw_timers_iteratenext( pCpw cpw )
{
    return (pCpwTimer)le_getVoid( ll_getNext( &cpw->list_timers ) );
}

/* check for a timeout and send the message */

bool
cpw_timers_check( pCpw cpw, pCpwTimer timer, bool * pending )
{
    /* returns false if a timer was deleted from the list */

    float_64 count = cpw_localhost_hpcount();

    if ( ( count - timer->hpcount ) >= timer->hpdiff ) {

        *pending = true;

        /* timeout */

        if ( !timer->internal ) {

            /* external application defined timer */

            timer->timerCallback( cpw, timer->timerid );

        } else {

            /* internal Cpw defined timer */

            cpw_timers_internaltimeout( cpw, timer );
        }

        if ( timer->redo == false ) {
            ll_deleteElement( &cpw->list_timers, timer->listid );
            cpwfree( timer );
            return false;
        }            
        
        timer->hpcount = count;
    } else {
        
        /* nothing to do */

        *pending = false;

    }

    return true;
}

/* check all timers for timeouts */

bool
cpw_timers_tick( pCpw cpw )
{
    pCpwTimer timer;
    bool pending = false;

    /* return false if there are no pending timers */

    if ( ( timer = cpw_timers_iteratestart( cpw ) ) == 0 ) {
        cpw->timers = false;
        return false;
    }

    while ( timer != 0 ) {
        if ( !cpw_timers_check( cpw, timer, &pending ) ) break;
        timer = cpw_timers_iteratenext( cpw );
    }

    return pending;
}

/*************************************************************************/
/*                                                                       */
/*   internal timers                                                     */
/*                                                                       */
/*************************************************************************/

bool cpw_timers_createinternal( pCpw cpw, uint_32 type, bool redo, uint_32 delay, uint_32 id )
{
    float_64 seconds;

    /* allocate a new timer struct */

    pCpwTimer timer = cpwmalloc( sizeof( CpwTimer ) );   

    if ( timer == 0 ) {
        cpw_error_set( cpw, cpw_error_outofmemory );
        return false;
    }
    memset( timer, 0, sizeof( CpwTimer ) );

    /* offset in seconds for this timer */

    seconds = (float_64)delay / (float_64)1000.0;

    /* add it to our linked list */

    timer->listid = ll_addVoid( &cpw->list_timers, (void *) timer );

    cpw->timers = true;

    /* setup */

    timer->internal      = true;
    timer->int_type      = type;
    timer->timerid       = id;
    timer->redo          = redo;
    timer->hpdiff        = seconds * cpw_localhost_hpfreq();
    timer->hpcount       = cpw_localhost_hpcount(); /* running */
    
    return true;
}

void cpw_timers_internaltimeout( pCpw cpw, pCpwTimer timer )
{
    switch( timer->int_type ) {

        case CPW_TIMER_INTERNAL_JOYSTICK:
            cpw_joystick_timout( cpw, timer->timerid );
        break;

    }
    return;
}
