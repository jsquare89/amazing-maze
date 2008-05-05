/***************************************************************************/
/*                                                                         */
/*  cpw_bitmaps.c                                                          */
/*                                                                         */
/*    Cpw interface to BMP file loading and saving.                        */
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

#include "cpw_bitmaps.h"
#include "cpw_error.h"

#define BITMAP_ID 0x4D42

/* reads an rgb bitmap image */

bool cpw_bitmap_load( pCpw cpw, char * filename, CpwImage * image )
{
    FILE *              fp;
    BITMAPINFOHEADER    bitmapInfoHeader;
    BITMAPFILEHEADER	  bitmapFileHeader;
    uint_32             index;
    uint_32             len;
    uint_32             datasize;
    unsigned char       byte;
    unsigned char       red;
    unsigned char       grn;
    unsigned char       blu;
    uint_16             word;
    pChar               tempBuf;

    if ( image == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }

    fp = fopen( filename, "rb" );

    if ( fp == 0 ) {
        cpw_error_set( cpw, cpw_error_failedtoload );
        return false;
    }

    len = fread( &bitmapFileHeader, sizeof( BITMAPFILEHEADER ), 1, fp );

    if ( len != 1 ) {
        cpw_error_set( cpw, cpw_error_invalidformat );
        fclose( fp );
        return false;
    }

    if ( bitmapFileHeader.bfType != BITMAP_ID ) {
        cpw_error_set( cpw, cpw_error_invalidformat );
        fclose( fp );
        return false;
    }

    len = fread( &bitmapInfoHeader, sizeof( BITMAPINFOHEADER ), 1, fp );

    if ( len != 1 ) {
        cpw_error_set( cpw, cpw_error_invalidformat );
        fclose( fp );
        return false;
    }

    switch ( bitmapInfoHeader.biBitCount ) {

        /* currently no support for 0 (jpeg), 1 (mono), 4 (indexed), or 8 (indexed) bits */

        case 0:
        case 1:
        case 4:
        case 8:
          cpw_error_set( cpw, cpw_error_invalidformat );
          fclose( fp );
          return false;
        break;

        case 16:
          datasize = bitmapInfoHeader.biWidth * bitmapInfoHeader.biHeight * 2;
          image->depth = 3;
          break;
        case 24:
          datasize = bitmapInfoHeader.biWidth * bitmapInfoHeader.biHeight * 3;
          image->depth = 3;
          break;
        case 32:
          datasize = bitmapInfoHeader.biWidth * bitmapInfoHeader.biHeight * 4;
          image->depth = 3;
          break;
        break;

        default:
          cpw_error_set( cpw, cpw_error_invalidformat );
          fclose( fp );
          return false;
        break;

    }

    if ( bitmapInfoHeader.biCompression == BI_RGB || 
         bitmapInfoHeader.biCompression == BI_BITFIELDS ) {
    } else {
        /* currently no support for compressed bitmaps */

        cpw_error_set( cpw, cpw_error_invalidformat );
        fclose( fp );
        return false;
    }

    /* jump forward to the data */

    fseek( fp, bitmapFileHeader.bfOffBits, SEEK_SET );

    image->data = (pChar) cpwmalloc( datasize );

    if ( !image->data ) {
        cpw_error_set( cpw, cpw_error_outofmemory );
        fclose( fp );
        return false;
    }

    len = fread( image->data, 1, datasize, fp );

    if ( len != datasize ) {
        cpw_error_set( cpw, cpw_error_invalidformat );
        cpwfree( image->data );
        fclose( fp );
        return false;
    }

    fclose( fp );

    /* Convert data to RGB, 8 bits per color. (BMP's are BGR not RGB) */

    switch( bitmapInfoHeader.biBitCount ) {

        case 16:
          
          /* red, green, and blue are represented with 5 bits for each color  */

          tempBuf = cpwmalloc( bitmapInfoHeader.biWidth * bitmapInfoHeader.biHeight * 3 );

          if ( !tempBuf ) {
              cpw_error_set( cpw, cpw_error_outofmemory );
              cpwfree( image->data );
              fclose( fp );
              return false;
          }

          for ( index = 0; index < datasize; index += 3 ) {
	          word = (uint_16)*( image->data + index );
            /* 0x7C00  red   (0111 1100 0000 0000) */
            red = (word | 0x7C00) >> 10;
            /* 0x03E0  green (0000 0011 1110 0000) */
            grn = (word | 0x03E0) >> 5;
            /* 0x001F  blue  (0000 0000 0001 1111) */
            blu = (word | 0x001F);
	          tempBuf[index+0] = red;
	          tempBuf[index+1] = grn;
	          tempBuf[index+2] = blu;
          }

          cpwfree( image->data );
          image->data = tempBuf;

        break;

        case 24:

          /* red, green, and blue are represented with 8 bits for each color */
          /* bitmap data is BGR so we convert to RGB */
          
          for ( index = 0; index < datasize; index += 3 ) {
              byte = image->data[index]; /* byte = blue */
              image->data[index] = image->data[index + 2]; /* swap red */
              image->data[index + 2] = byte; /* blue over */
          }

        break;
        
        case 32:

          /* red, green, and blue are represented with 12 bits for each color  */

        break;


    }

    image->depth = 3;
    image->width = bitmapInfoHeader.biWidth;
    image->height = bitmapInfoHeader.biHeight;

    return true;
}
