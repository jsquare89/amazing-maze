/***************************************************************************/
/*                                                                         */
/*  cpw_linkedelement.c                                                    */
/*                                                                         */
/*    LinkedElement, used by LinkedList.                                   */
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

#include "cpw_linkedelement.h"

/* default construction */

LinkedElement*
le_createElement( void )
{
    LinkedElement * le;
    le = (LinkedElement*) cpwmalloc( sizeof( LinkedElement ) );
    memset( le, 0, sizeof( LinkedElement ) ); 
    return le;
}

/* init a pStr element */

LinkedElement*
le_initStr( pStr string, uint_32 id )
{
    LinkedElement * le = le_createElement();
    if ( le == null ) return 0;

    le->childtomyright  = null;
    le->id              = id;
    le->etype           = Element_pStr;
    le->e.e_pstr        = strCpy( string );

    return le;
}

/* init a string element */

LinkedElement*
le_initString( char* string, uint_32 id )
{
    LinkedElement * le = le_createElement();
    if ( le == null ) return 0;

    le->childtomyright  = null;
    le->id              = id;
    le->etype           = Element_pStr;
    le->e.e_pstr = cpyString( string );

    return le;
}

/* init a 64 bit float element */

LinkedElement*
le_initFloat64( float_64 number, uint_32 id )
{
    LinkedElement * le = le_createElement();
    if ( le == null ) return 0;

  	le->childtomyright  = null;
    le->id              = id;
    le->etype           = Element_Float64;
    le->e.e_float_32    = number;

    return le;
}

/* init a 32 bit int element */

LinkedElement*
le_initInt32( int_32 number, uint_32 id )
{
    LinkedElement * le = le_createElement();
    if ( le == null ) return 0;

    le->childtomyright  = null;
    le->id              = id;
    le->etype           = Element_Int32;
    le->e.e_float_32    = number;

    return le;
}

/* init a void* pointer element */

LinkedElement*
le_initVoid( void * userp, uint_32 id )
{
    LinkedElement * le = le_createElement();
    if ( le == null ) return 0;

    le->childtomyright  = null;
    le->id              = id;
    le->etype           = Element_Void;
    le->e.e_pvoid       = userp;

    return le;
}

/* default destruction */

void
le_freeElement( LinkedElement** le )
{
    /* destroy any resources */
    if ( le == null ) return;
    if ( *le == null ) return;

    switch ( (*le)->etype ) {
        
        case Element_pStr:
            if ( (*le)->e.e_pstr ) freeStr( &((*le)->e.e_pstr) );
        break;
    
        case Element_Float64:
            (*le)->e.e_float_32 = 0;
        break;

        case Element_Int32:
            (*le)->e.e_int_32 = 0;
        break;

        case Element_Void:
            (*le)->e.e_pvoid = 0;
        break;
    }
    cpwfree( *le );
    *le = null;
}

/* getters */

LinkedElementType 
le_getType( LinkedElement* le )
{
    if ( !le ) return Element_Empty;
    return le->etype;
}

pStr
le_getString( LinkedElement* le )
{
    if ( !le ) return 0;
    return le->e.e_pstr;
}

void*
le_getVoid( LinkedElement* le )
{
    if ( !le ) return 0;
    return le->e.e_pvoid;
}

float_64
le_getFloat64( LinkedElement* le )
{
    if ( !le ) return 0;
    return le->e.e_float_32;
}

int_32
le_getInt32( LinkedElement* le )
{
    if ( !le ) return 0;
    return le->e.e_int_32;
}

uint_32  
le_getId( LinkedElement* le ) 
{ 
    if ( !le ) return 0;
    return le->id; 
}

/* setters */

void 
le_setId( LinkedElement* le, uint_32 id )
{ 
    if ( !le ) return;
    le->id = id; 
}

void
le_setVoid( LinkedElement* le, void* p )
{
    if ( !le ) return;
    le->e.e_pvoid = p;
}

/* purge the list of elements */

void
le_cleanUp( LinkedElement* le, uint_32 * pkillcount ) 
{
    (*pkillcount)++;

    /* do i have kids? */

    if ( le->childtomyright ) {

        le_cleanUp( (LinkedElement*)le->childtomyright, pkillcount );
        le_freeElement( (LinkedElement**)&le->childtomyright );
        le->childtomyright = null;

    }
    return;
}

/* add an element */

void 
le_linkUp(  LinkedElement* le, LinkedElement* sibling ) 
{
	if ( le->childtomyright ) {

    /* hand it down to our first kid */
		le_linkUp( (LinkedElement*)le->childtomyright, sibling );

	} else {

		/* link up! */
		le->childtomyright = (void*)sibling;

	}
}

/* remove an element */

LinkedElement*
le_unLink( LinkedElement* me, LinkedElement * myParent, uint_32 id ) 
{
    if ( me->id == id ) {

        /* i'm it */

        if ( myParent )
            myParent->childtomyright = me->childtomyright;  /* may be null that's ok */

        #ifdef listdebug
        printf( "unlink: %d %d\n", me->id, me );
        #endif

        return me;
    }

    /* we were not the victim of this seek and destroy, hand it to 
    our sibling or error not found if we are the last element. */

    if ( me->childtomyright != null ) {
        /* hand it down the list */
        return le_unLink( (LinkedElement*)me->childtomyright, me, id );
    }

    /* not found */

    #ifdef listdebug
    printf( "unlink: not found\n" );
    #endif

    return  null;
}

/* find an element */

LinkedElement* 
le_seek( LinkedElement* le, uint_32 id ) 
{
    if ( le->id == id )
        /* i'm it */
        return le;

    /* pass it down */

    if ( le->childtomyright )
        /* hand it down to our first kid */
        return le_seek( (LinkedElement*)le->childtomyright, id );

    return null;
}

/* count elements */

void 
le_countUp( LinkedElement* le, uint_32 * pcount ) 
{
    (*pcount)++;

    /* count the kids */

    if ( le->childtomyright )
        le_countUp( (LinkedElement*)le->childtomyright, pcount );

    return;
}

/* iterate all elements - init */

void 
le_initIterate( LinkedElement* le ) 
{
    le->iterate = false;

    if ( le->childtomyright )
        le_initIterate( (LinkedElement*)le->childtomyright );

    return;
}

/* iterate all elements - next */

LinkedElement*
le_getNext( LinkedElement* le ) 
{
    if ( le->iterate == false ) {
        le->iterate = true;
        return le;
    }

    if ( le->childtomyright != null )
        return le_getNext( (LinkedElement*)le->childtomyright );
    else
        return null;
}

/* get the last element */

LinkedElement*
le_lastOne( LinkedElement* le ) 
{
    if ( le == null ) return null;

    if ( le->childtomyright != null )
        return le_lastOne( (LinkedElement*)le->childtomyright );

    return le;
}
