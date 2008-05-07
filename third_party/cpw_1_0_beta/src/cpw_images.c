/***************************************************************************/
/*                                                                         */
/*  cpw_images.c                                                           */
/*                                                                         */
/*    Support for loading and saving a few image formats commonly used     */
/*    in game programming. Also supports a few image manipulation          */
/*    routines. Simple, no-nonsence, and built to stay that way.           */
/*                                                                         */
/*    Currently supports: TGA, BMP                                         */
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

#include "cpw_images.h"
#include "cpw_error.h"
#include "cpw_libtarga.h"
#include "cpw_bitmaps.h"
#include "cpw_window.h"
#include <math.h>
#include CPW_GLU_H

/*************************************************************************/
/*                                                                       */
/*   image api                                                           */
/*                                                                       */
/*************************************************************************/

/* load an image into an image buffer and texture fit it if requested */

bool cpwLoadImage( pCpw cpw, CpwImage * image, 
                CpwImageType type, pChar filename, bool texturefit )
{
    if ( image == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }
  
    memset( image, 0, sizeof( CpwImage ) );

    if ( type == CPW_IMAGEFORMAT_BMP ) {

        /* bmp files */

        if ( cpw_bitmap_load( cpw, filename, image ) == false ) {
            /* error set by load routine */
            return false;
        }

    } else if ( type == CPW_IMAGEFORMAT_TGA ) {

        /* tga files */
                
	      TargaInfo tga;

        memset( &tga, 0, sizeof( TargaInfo ) );

        image->data = tga_load( &tga, filename );

        if ( tga.error == true ) {
            cpw_error_set( cpw, cpw_error_failedtoload );
            return false;
        }

        image->width     = tga.width;
        image->height    = tga.height;
        image->depth     = tga.format;

    } else {
        cpw_error_set( cpw, cpw_error_invalidformat );
        return false;
    }

    if ( texturefit )
        cpwTextureFit( cpw, image );

	  return true;
}

/* free the resources associated with an image buffer */

bool cpwFreeImage( pCpw cpw, CpwImage * image )
{
    if ( image == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }

    cpwfree( image->data );    

    memset( image, 0, sizeof( CpwImage ) );

    return true;
}

/* fit an image to a width and height suitable for gl texturing */

bool cpwTextureFit( pCpw cpw, CpwImage * image )
{
    uint_32 width;
    uint_32 height;

    if ( image == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }

    width  = image->width;
    height = image->height;

    if ( cpw_images_bestfit( &width, &height ) )
        cpwResizeImage( cpw, image, width, height );

    return true;
}

/* take a screenshot of the current rendering context's frame buffer */

bool cpwScreenShot( pCpw cpw, CpwImage * image )
{
    CpwWindowInfo info;
    uint_32 size;

    if ( image == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }

    memset( image, 0, sizeof( CpwImage ) );

    if ( !cpwGetWindowInfo( cpw, &info, 0 ) ) { /* 0 winid returns current foreground info */
        cpw_error_set( cpw, cpw_error_novalidcontext );
        return false;
    }

    size = info.width * info.height * 3; /* RGB pixel width = 3 */

    if ( size == 0 ) return true;

    glPushClientAttrib( GL_CLIENT_PIXEL_STORE_BIT );
    glPushAttrib( GL_PIXEL_MODE_BIT );

    glPixelStorei( GL_UNPACK_LSB_FIRST, GL_FALSE );
    glPixelStorei( GL_PACK_ROW_LENGTH, info.width );
    glPixelStorei( GL_PACK_SKIP_ROWS, 0 );
    glPixelStorei( GL_PACK_SKIP_PIXELS, 0 );
    glPixelStorei( GL_PACK_ALIGNMENT, 1 );
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

    image->data = cpwmalloc( size );

    if ( image->data == 0 ) {
        cpw_error_set( cpw, cpw_error_outofmemory );
        return false;
    }

    memset( image->data, 0, size );

    glReadPixels( 0, 0, info.width, info.height, GL_RGB, GL_UNSIGNED_BYTE, image->data );

    image->width = info.width;
    image->height = info.height;
    image->depth = 3;

    glPopClientAttrib();
    glPopAttrib();

    return true;
}

/* save an image buffer to a file */

bool cpwSaveImage( pCpw cpw, CpwImage * image, pChar filename )
{
    if ( filename == 0 || image == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }

    /* save as rle tga */

    if ( !tga_write_rle( filename, image->width, image->height, image->data, TGA_TRUECOLOR_24 ) )
      return false;

    /*

    this works too but the file size is much bigger.

    if ( !tga_write_raw( filename, image->width, image->height, image->data, TGA_TRUECOLOR_24 ) )
      return false;

    */

    return true;
}

/* simple easy to use interface to gluScaleImage */

bool cpwResizeImage( pCpw cpw, CpwImage * image, uint_32 new_width, uint_32 new_height )
{
    pChar newdata;
    GLenum format;

    switch( image->depth ) {
        case 1: format = GL_LUMINANCE; break;
        case 3: format = GL_RGB; break;
        case 4: format = GL_RGBA; break;
        default: 
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }

    newdata = cpwmalloc( new_width * new_height * image->depth ); /* op */
    memset( newdata, 0, new_width * new_height * image->depth );

    gluScaleImage( format, image->width, image->height, GL_UNSIGNED_BYTE, image->data,
        new_width, new_height, GL_UNSIGNED_BYTE, newdata );

    cpwfree( image->data );

    image->width  = new_width;
    image->height = new_height;
    image->data   = newdata;

    return true;
}

/* fit a texture's width and height to GL texture requirements */

bool cpw_images_bestfit( uint_32 * width, uint_32 * height ) 
{
    float xratio = (float)*width / 64;
    float yratio = (float)*height / 64;

    if ( xratio == (int)xratio && yratio == (int)yratio ) return false;

    if ( ( xratio - (int)floor( xratio ) ) > .5 ) {
        *width = (int)( 64 * ceil( xratio ));
    } else {
        *width = (int)( 64 * floor( xratio ));
    }

    if ( ( yratio - (int)floor( yratio ) ) > .5 ) {
        *height = (int)( 64 * ceil( yratio ));
    } else {
        *height = (int)( 64 * floor( xratio ));
    }

    if ( *height == 0 ) *height = 64;
    if ( *width == 0 ) *width = 64;

    return true;
}


