/***************************************************************************/
/*                                                                         */
/*  cpw_glextensions.c                                                     */
/*                                                                         */
/*    The Cpw library interface to the localhost's GL extensions.          */
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

#include "cpw_glextensions.h"
#include "cpw_windowlist.h"
#include "cpw_error.h"
#include CPW_OPENGL_H

/*************************************************************************/
/*                                                                       */
/*   init and exit.                                                      */
/*                                                                       */
/*************************************************************************/

#define MAXEXTENSIONS 200

/* http://www.opengl.org/developers/code/features/OGLextensions/OGLextensions.html */
/* http://oss.sgi.com/projects/ogl-sample/registry/ */

bool cpw_glextensions_init( pCpw cpw )
{
    CpwExtensionList * list = cpwmalloc( sizeof( CpwExtensionList ) );

    if ( list == 0 ) {
        cpw_error_set( cpw, cpw_error_outofmemory );
        return false;
    }
    memset( list, 0, sizeof( CpwExtensionList ) );
    
    cpw->extensions = (pVoid)list;

    return true;
}

void cpw_glextensions_exit( pCpw cpw )
{
    CpwExtensionList * list = (CpwExtensionList*)cpw->extensions;
    pStr * p;

    /* free the list extension string list if it was ever created */

    if ( list->init != false ) {
        list->index = 0;
        while ( list->size > list->index ) {
            p = (pStr*)( list->list + ( sizeof( pStr ) * list->index ) );
            freeStr( p );
            list->index++;
        }
    }

    /* free the base list struct memory */

    cpwfree( list );
}

/* init a list of extension strings. called the first time
   the user asks for an extension. used below. */

bool cpw_glextensions_initlist( pCpw cpw ) 
{
    static const GLubyte * extlist = null;
    pStr token     = 0;
    uint_32 pos    = 0;
    pStr string    = 0;
    uint_32 count  = 1;
    uint_32 expand = 0;
    CpwExtensionList * list = (CpwExtensionList*)cpw->extensions;
    pStr * pp;

    if ( list->init == true ) return true;

    /* you must init gl before you can query for extensions. check to
       make sure a window has been initialized indicating gl is 'running'. */        

    if ( cpw_windowlist_length( cpw ) == 0 ) {
        cpw_error_set( cpw, cpw_error_novalidcontext );
        return false;
    }

    if ( list == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }

    list->list = 0;
    list->size = 0;
    list->index = 0;
    list->init = true;

    extlist = glGetString( GL_EXTENSIONS );

    /* real careful, sometimes drivers don't give us a good string */

    if ( extlist == null )
        return false;

    setString( &string, (char*)extlist );

    if ( strLen( string ) == 0 ) {
        freeStr( &string );
        return false;
    }

    /* save a list of pointers to copies of each extension string identifier */
    /* ( regardless of pointer size, this should work ) */
    
    while ( ( token = strToken( &string, " " ) ) != 0 ) {

        /* strToken returns a new pStr (see cpw_str.h) */

        expand = sizeof( pStr ) * count; /* 4*1=4 bytes on 32 bit cpu's */

        /* it is assumed that the local realloc can take a null pointer */

        list->list = cpwrealloc( list->list, expand );

        /* store pointer at plist + ( extension count - size of a pointer ) */

        pp = (pStr*) ( list->list + ( expand - sizeof( pStr ) ) );
        *pp = token;
        count++;

        /* safety */

        if ( count > MAXEXTENSIONS ) break;
    }

    if ( count == 0 ) { 
        cpwfree( list->list ); 
        freeStr( &string );
        return false; 
    }

    list->size = count-1;
    freeStr( &string );

    return true;
}

/*************************************************************************/
/*                                                                       */
/*   extensions api                                                      */
/*                                                                       */
/*************************************************************************/

/* pop one extension at a time back to the user out of our list of extensions */

pChar cpwIterateExtensions( pCpw cpw ) 
{
    CpwExtensionList * list = (CpwExtensionList*)cpw->extensions;
    pStr * p;

    /* if our internal list of extension isn't created, create it. */

    if ( list->init == false )
        if ( !cpw_glextensions_initlist( cpw ) ) 
            return 0;

    /* all done */

    if ( list->size == list->index ) return 0;

    /* next */

    p = (pStr*)( list->list + ( sizeof( pStr ) * list->index ) );

    /* inc our internal extension pointer */

    list->index++;

    return str((*p));
}

/* reset the list */

bool  cpwIterateExtensionsReset( pCpw cpw )
{
    CpwExtensionList * list = (CpwExtensionList*)cpw->extensions;
    list->index = 0;
    return true;
}

/* direct check for a certain extension string identifier. */

bool cpwExtensionSupport( pCpw cpw, pChar string ) 
{
    static const GLubyte * extlist = null;
    
    /* you must init gl before you can query for extensions. check to
       make sure a window has been initialized indicating gl is 'running'. */        

    if ( cpw_windowlist_length( cpw ) == 0 ) {
        cpw_error_set( cpw, cpw_error_novalidcontext );
        return false;
    }

    if ( string == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }

    extlist = glGetString( GL_EXTENSIONS );

    if ( extlist == null )
        return false;

    if ( slFind( (char*)extlist, string ) >= 0 ) return true;
    return false;
}


