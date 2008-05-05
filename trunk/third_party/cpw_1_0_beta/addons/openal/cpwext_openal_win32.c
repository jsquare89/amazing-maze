/***************************************************************************/
/*                                                                         */
/*  cpwext_openal_win32.c                                                  */
/*                                                                         */
/*    The Cpwext OpenAL interface for Win32.                               */
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
/*  File Platform: Win32                                                   */
/*                                                                         */
/***************************************************************************/

#include "cpwext_openal.h"

/* link in the win32 lib header for openal */

#ifdef _DEBUG
#pragma comment( lib, "openal32.lib" )
#else
#pragma comment( lib, "openal32.lib" )
#endif

bool cpwextInitOpenAL( pCpw cpw )
{
    pCpwextOpenAL ctx;

    if ( cpw == 0 ) return false;

    ctx = ( pCpwextOpenAL ) cpw->ctx_ao_openal;

    if ( ctx != 0 ) return true;

    ctx = cpwmalloc( sizeof( CpwextOpenALContext ) );

    if ( ctx == 0 ) return false;
    
    memset( ctx, 0, sizeof( CpwextOpenALContext ) );

    cpw->ctx_ao_openal = ctx;

	  /* open the appropriate localhost audio device */

    /* OpenAL will fall back to DirectSound and then WinMM depending 
       on what's available. We request DS3D & let OpenAL choose the 
       appropriate one. Regardless of what is found, OpenAL will 
       compensate so we always have everything AL has to offer in
       the application. */

 	  ctx->device = (pVoid) alcOpenDevice("DirectSound3D");

 	  /* ctx->device = (pVoid) alcOpenDevice("DirectSound"); for testing specific device */
 	  /* ctx->device = (pVoid) alcOpenDevice("winmm"); for testing specific device */

    if ( ctx->device == 0 ) return false;

	  /* create OpenAL context */

	  ctx->context = (pVoid) alcCreateContext( (ALCdevice*) ctx->device, NULL );

    if ( ctx->context == 0 ) return false;

	  /* Set active context */

	  alcMakeContextCurrent( (ALvoid*) ctx->context );

    /* OpenAL is ready to go. Now wasn't that easier than initializing 
       DirectSound manually?? And we have support for audio if even if 
       DS isn't available. neato. Open standards and OpenAL rock. */

    return true;
}

void cpwextFreeOpenAL( pCpw cpw )
{
    pCpwextOpenAL ctx;

    if ( cpw == 0 ) return;

    ctx = ( pCpwextOpenAL ) cpw->ctx_ao_openal;

    if ( ctx == 0 ) return;

    /* release context */

    if ( ctx->context != 0 )
        alcDestroyContext( (ALvoid*) ctx->context );

    /* close device */

    if ( ctx->device != 0 )
        alcCloseDevice( (ALCdevice*) ctx->device );

    cpwfree( ctx );

    cpw->ctx_ao_openal = 0;

    return;
}

