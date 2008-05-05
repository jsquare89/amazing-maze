/***************************************************************************/
/*                                                                         */
/*  cpw_perftracker.c                                                      */
/*                                                                         */
/*    Debug performance tracking                                           */
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

#include "cpw_perftracker.h"
#include "cpw_error.h"
#include CPW_LOCALHOST_H

/*************************************************************************/
/*                                                                       */
/*   init and exit.                                                      */
/*                                                                       */
/*************************************************************************/

bool cpw_perftracker_init( pCpw cpw )
{
    ll_initList( &cpw->list_perf );
    return true;
}

void cpw_perftracker_exit( pCpw cpw )
{
    pCpwMark pmark;

    /* on exit we dump stats if there are marks set */

    ll_initIterate( &cpw->list_perf );

    pmark = (pCpwMark)le_getVoid( ll_getNext( &cpw->list_perf ) );

    /* no marks */

    if ( pmark == 0 ) {
        ll_deleteList( &cpw->list_perf );
        return;
    }

    ll_deleteList( &cpw->list_perf );

    return;
}

/*************************************************************************/
/*                                                                       */
/*   performance marks api                                               */
/*                                                                       */
/*************************************************************************/

/* add a new performance mark we will be using */

uint_32 cpwAddMark( pCpw cpw, pChar name, bool average )
{
    pCpwMark pmark;
    pmark = cpwmalloc( sizeof( PerformanceMark ) );

    if ( pmark == 0 ) {
        cpw_error_set( cpw, cpw_error_outofmemory );
        return false;
    }
    memset( pmark, 0, sizeof( PerformanceMark ) );

    setString( &pmark->name, name );
    pmark->average = average;

    return ll_addVoid( &cpw->list_perf, (pVoid) pmark );    
}

/* enter a performance marker's tracking point */

bool cpwEnterMark( pCpw cpw, uint_32 id ) 
{
    pCpwMark pmark;
    if ( !ll_getVoid( &cpw->list_perf, (pVoid*)&pmark, id ) )
        return false;

    pmark->entered = cpw_localhost_hpcount();

    return true;
}

/* leave a performance mark's tracking point */

bool cpwExitMark( pCpw cpw, uint_32 id ) 
{
    pCpwMark pmark;
    if ( !ll_getVoid( &cpw->list_perf, (pVoid*)&pmark, id ) )
        return false;

    if ( pmark->average == false )
        pmark->ticks = pmark->ticks + ( cpw_localhost_hpcount() - pmark->entered );
    else
        pmark->ticks = ( pmark->ticks + ( cpw_localhost_hpcount() - pmark->entered ) ) * .5;

    pmark->entered = 0;

    return true;
}

/* dump the current stats to the print handler */

void cpwDumpMarks( pCpw cpw ) 
{
    pCpwMark pmark;
    char buf[1000];

    ll_initIterate( &cpw->list_perf );

    pmark = (pCpwMark)le_getVoid( ll_getNext( &cpw->list_perf ) );

    if ( pmark == 0 ) {
        return;
    }

    cpw->cpw_print( "\n" );
    cpw->cpw_print( "Performance Marks:\n" );
    cpw->cpw_print( "---------------------------------------------\n" );

    while ( pmark != 0 ) {

        if ( pmark->average == false )
            sprintf( buf, "%15s %10.7f\n", str( pmark->name ), 
                   ( pmark->ticks / cpw_localhost_hpfreq() ) ); 
        else
            sprintf( buf, "%15s %10.7f av.\n", str( pmark->name ), 
                   ( pmark->ticks / cpw_localhost_hpfreq() ) ); 

        cpw->cpw_print( buf );

        if ( pmark->entered != 0 ) cpw->cpw_print( "^unclosed\n" );

        pmark = (pCpwMark)le_getVoid( ll_getNext( &cpw->list_perf ) );
    }

    /* prompt on the console */

    getchar();

    return;
}

/*************************************************************************/
/*                                                                       */
/*   simple frame counter api                                            */
/*                                                                       */
/*************************************************************************/

void cpwFpsInit( pCpw cpw )
{
    cpw->fps_hpcount = cpw_localhost_hpcount();
    cpw->fps_hpfreq  = cpw_localhost_hpfreq();
    cpw->fps_ticks = 0;
}

void cpwFpsDraw( pCpw cpw, bool print )
{
    float_64 count = cpw_localhost_hpcount();

    cpw->fps_ticks++;

    if ( count >= ( cpw->fps_hpcount + cpw->fps_hpfreq ) ) {

        cpw->fps_fps     = cpw->fps_ticks;
        cpw->fps_ticks   = 0;
        cpw->fps_hpcount = count;

        if ( print ) {
            char buf[100];
            sprintf( buf, "fps: %i\n", cpw->fps_fps );
            cpw->cpw_print( buf );
        }
    }
}

uint_32 cpwFpsGet( pCpw cpw )
{
    return cpw->fps_fps;
}
