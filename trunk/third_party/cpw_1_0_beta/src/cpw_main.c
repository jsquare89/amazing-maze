/***************************************************************************/
/*                                                                         */
/*  cpw_main.c                                                             */
/*                                                                         */
/*    The Cpw library main processing loop.                                */
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

#include "cpw_main.h"
#include "cpw_event.h"
#include "cpw_error.h"
#include "cpw_timers.h"
#include CPW_LOCALHOST_H

/*************************************************************************/
/*                                                                       */
/*   main loop                                                           */
/*                                                                       */
/*************************************************************************/

bool cpwMainLoop( pCpw cpw )
{
    CpwIdleCallback     idleCallback;
    CpwMainLoopCallback mlCallback;

    bool    pending;
    uint_32 ticks;

    ticks   = 0;
    pending = false;

    if ( cpw->cpw_initsuccess != true ) return false;

    cpw->mainloop_break = false;

    cpw->cpw_running = true;

    for (;;) 
    {

        /* break main loop execution */

        if ( cpw->mainloop_break == true ) break;

        /* localhost event processing */

        pending = cpw_localhost_processevents( cpw, 3 );

        /* cpw event processing */

        pending = pending | cpw_event_sendevents( cpw, 3 );

        /* cpw timer processing */

        if ( cpw->timers == true ) /* optimazation flag for non-timer apps */
            pending = pending | cpw_timers_tick( cpw );

        /* if we have no timers and no events, idle */

        if ( !pending ) {
            
            if ( !cpw->idleCallback ) {
                cpw_localhost_sleep( 1 );
            } else {
                idleCallback = (CpwIdleCallback)cpw->idleCallback;
                idleCallback( cpw );
            }
        }

        /* call the user's mainloop callback if required */

        if ( cpw->mainloopCallback ) {
            ticks++;
            if ( ticks >= cpw->mainloop_callbackticks ) {
                mlCallback = cpw->mainloopCallback;
                mlCallback( cpw, pending );
                ticks = 0;
            }
        }
    }

    cpw->cpw_running = false;

    /* return error flag if an error occured */

    if ( cpwGetLastError( cpw ) > 0 ) return false;

    /* no error */

    return true;
}

bool cpwBreakMainLoop( pCpw cpw )
{
    cpw->mainloop_break = true;
    return true;
}

bool cpwMainLoopIsRunning( pCpw cpw )
{
    return cpw->cpw_running;
}


bool cpwMainLoopUpdate( pCpw cpw, uint_32 ticks )
{
    bool    pending;

    pending = false;

    while ( ticks > 0 ) 
    {

        /* break main loop execution */

        if ( cpw->mainloop_break == true ) break;

        /* localhost event processing */

        pending = cpw_localhost_processevents( cpw, 3 );

        /* cpw event processing */

        pending = pending | cpw_event_sendevents( cpw, 3 );

        /* cpw timer processing */

        if ( cpw->timers == true ) /* optimazation flag for non-timer apps */
            pending = pending | cpw_timers_tick( cpw );

        /* if we have no timers and no events, return */

        if ( !pending )
            return false;

        ticks--;
    }

    return true;
}

/*************************************************************************/
/*                                                                       */
/*   main loop callback and idle callback seters api.                    */
/*                                                                       */
/*************************************************************************/

bool cpwMainLoopCallback( pCpw cpw, CpwMainLoopCallback mlCallback, uint_32 ticks )
{
    cpw->mainloopCallback = (pVoid)mlCallback;
    cpw->mainloop_callbackticks = ticks;
    return true;
}


bool cpwIdleCallback( pCpw cpw, CpwIdleCallback idleCallback )
{
    cpw->idleCallback = (pVoid)idleCallback;
    return true;
}
