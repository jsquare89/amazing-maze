/***************************************************************************/
/*                                                                         */
/*  cpw_font.c                                                             */
/*                                                                         */
/*    The Cpw library interface to FreeType 2.0.                           */
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

#include "cpw_font.h"
#include "cpw_error.h"
#include CPW_LOCALHOST_H

/***************************************************************************

    Things that still need to be done here:

    - align up, down, and center isn't supported in yet
    - texture, outline, and mesh fonts aren't supported yet.

***************************************************************************/

/* converts freetype errors to Cpw ones */

void cpw_font_enterpreterror( pCpw cpw, int_32 error ) 
{
    switch( error ) {

      case FT_Err_Unknown_File_Format:
      cpw_error_set( cpw, cpw_error_invalidfont );
      break;

      default:
      cpw_error_set( cpw, cpw_error_unknown );
      break;

    }
}

/*************************************************************************/
/*                                                                       */
/*   init and exit.                                                      */
/*                                                                       */
/*************************************************************************/

bool cpw_font_init( pCpw cpw )
{
    FT_Library      library;
    CpwFontState*   pcfs;

    if ( cpw == 0 ) return false;

    cpw->ctx_font = (pVoid)cpwmalloc( sizeof(CpwFontState) );

    if ( !cpw->ctx_font ) {
        cpw_error_set( cpw, cpw_error_outofmemory );
        return false;
    }

    memset( cpw->ctx_font, 0, sizeof(CpwFontState) );

    pcfs = (CpwFontState*)cpw->ctx_font;

    if ( FT_Init_FreeType( &library ) != 0 )
        return false;

    pcfs->library = library;

    /* set default rendering options */

    pcfs->renderMode    = CPW_FONTOPT_PIXELMAP;
    pcfs->fontSize      = 16;
    pcfs->alignMode     = CPW_FONTOPT_ALIGNLEFT;
    pcfs->kerning       = false;
    pcfs->pixmap_format = GL_LUMINANCE;
    pcfs->screenWidth   = 72;
    pcfs->screenHeight  = 72;
    pcfs->spacingMulti  = 1;

    /* misc. things to do here still: 
        - freetype's printf should be routed to CpwPrintfHandler 
        - freetype's allocation routines should be routed through the cpw ones.
    */

    return true;
}

void cpw_font_exit( pCpw cpw )
{
    CpwFontState*   pcfs;

    if ( cpw == 0 ) return;
    if ( cpw->ctx_font == 0 ) return;

    pcfs = (CpwFontState*)cpw->ctx_font;

    /* free any memory we've allocated for pixelmap font rendering */

    cpw_font_pixelmap_convertfree( pcfs ); 

    /* free freetype lib */

    if ( pcfs->library != 0 )
        FT_Done_FreeType( pcfs->library );

    /* free the font context */

    cpwfree( pcfs );

    cpw->ctx_font = 0;
}

/*************************************************************************/
/*                                                                       */
/*   font lists                                                          */
/*                                                                       */
/*************************************************************************/

/* lists the fonts based on a search string */

uint_32 cpwListFonts( pCpw cpw, CpwFontList* list, pChar hints, uint_32 location ) 
{
    uint_32 count = 0;
    pStr path = null;
    pStr file = null;

    if ( list == 0 || hints == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return 0;
    }

    if ( location == CPW_FONTLOC_HOST ) {

        pStr tmp = cpw_localhost_fontpath();

        setStr( &path, tmp );
        concatString( &path, hints );
        freeStr( &tmp );
    }

    if ( location == CPW_FONTLOC_RELATIVE ) {

        setString( &path, hints );
    }

    /* no fonts to list */

    if ( cpw_localhost_iteratefiles( cpw, true, path ) == 0 )
        return 0;

    while ( ( file = cpw_localhost_iteratefiles( cpw, false, path ) ) != 0 ) {

        list->list[count] = cpwmalloc( strLen( file ) + 1 );         

        if ( !list->list[count] ) {
            cpw_error_set( cpw, cpw_error_outofmemory );
            return count;
        }

        sprintf( list->list[count], "%s\0", str( file ) );

        count++;
    }

    freeStr( &path );

    list->size = count;

    return count;
}

/* lists the local fonts based on a search string */

bool cpwFreeFontList( pCpw cpw, CpwFontList* list ) 
{
    if ( list == 0 || list->size == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return 0;
    }

    while ( list->size > 0 ) {

        cpwfree( list->list[list->size-1] );
        list->list[list->size-1] = 0;
        list->size--;
    }

    return true;
}

/*************************************************************************/
/*                                                                       */
/*   font draw mode settings                                             */
/*                                                                       */
/*************************************************************************/

/* sets various parameters regarding the type, size, and
   characteristics of the font draw code. */

int_32 cpwFontMode( pCpw cpw, int_32 mode, int_32 val )
{
    CpwFontState * cfs;
    int_32 ret;

    cfs = (CpwFontState*)cpw->ctx_font;

    switch( mode ) {

        /* render mode */

        case CPW_FONTOPT_PIXELMAP: 
            ret = cfs->renderMode;
            cfs->renderMode = CPW_FONTOPT_PIXELMAP;
        break;

        /* alignment */

        case CPW_FONTOPT_ALIGNRIGHT:
            ret = cfs->alignMode;
            cfs->alignMode = CPW_FONTOPT_ALIGNRIGHT;
        break;
        case CPW_FONTOPT_ALIGNLEFT: 
            ret = cfs->alignMode;
            cfs->alignMode = CPW_FONTOPT_ALIGNLEFT;
        break;
        case CPW_FONTOPT_ALIGNUP: 
            ret = cfs->alignMode;
            cfs->alignMode = CPW_FONTOPT_ALIGNUP;
        break;
        case CPW_FONTOPT_ALIGNDOWN: 
            ret = cfs->alignMode;
            cfs->alignMode = CPW_FONTOPT_ALIGNDOWN;
        break;
        case CPW_FONTOPT_ALIGNCENTER:
            ret = cfs->alignMode;
            cfs->alignMode = CPW_FONTOPT_ALIGNCENTER;
        break;

        /* font size */

        case CPW_FONTOPT_SIZE:
            ret = cfs->fontSize;
            cfs->fontSize = val*64;
        break;

        case CPW_FONTOPT_SPACING:
            if ( val < 0 ) {
                cpw_error_set( cpw, cpw_error_invalidparameter );
                ret = -1;
            }
            ret = cfs->spacingMulti;
            cfs->spacingMulti = val;
        break;

        case CPW_FONTOPT_PICASIZE:
            ret = (int)((float)cfs->fontSize/(float)64);
            cfs->fontSize = val;
        break;

        /* kerning */

        case CPW_FONTOPT_KERN:
            if ( val == 0 ) {
                ret = cfs->kerning;
                cfs->kerning = false;
            } else if ( val == 1 ) {
                ret = cfs->kerning;
                cfs->kerning = true;
            } else {
                cpw_error_set( cpw, cpw_error_invalidparameter );
                ret = -1;
            }
        break;

        /* pixelmap pixel format */

        case CPW_FONTOPT_PIXELMAP_GLFORMAT:
            ret = cfs->pixmap_format;
            cfs->pixmap_format = val;
        break;

        /* buffered font debug lines */

        case CPW_FONTOPT_LAYOUTDEBUG:
            if ( val == 0 ) {
                ret = cfs->layoutdebug;
                cfs->layoutdebug = false;
            } else if ( val == 1 ) {
                ret = cfs->layoutdebug;
                cfs->layoutdebug = true;
            } else {
                cpw_error_set( cpw, cpw_error_invalidparameter );
                ret = -1;
            }

        /* invalid param */

        default:
            cpw_error_set( cpw, cpw_error_invalidparameter );
            ret = -1;
        break;
    }

    return ret;
}

/*************************************************************************/
/*                                                                       */
/*   font file loading                                                   */
/*                                                                       */
/*************************************************************************/

/* load a local or application font into FreeType 2.0 */

CpwFontFace 
cpwLoadFont( pCpw cpw, char* fontname, uint_32 location, char* fontpath, char* cachelist )
{
    CpwFontState *  cfs;
    FT_Library      library;
    FT_Face         face;

    pStr            fontName;
    pStr            fontPath;
    pStr            cacheList;
    int_32          error;

    cfs     = (CpwFontState*)cpw->ctx_font;
    library = (FT_Library)cfs->library;

    fontName  = null;
    fontPath  = null;
    cacheList = null;

    /* fontname */

    if ( fontname == null ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return 0;
    }
    setString( &fontName, fontname );

    /* location */

    if ( location != CPW_FONTLOC_HOST && location != CPW_FONTLOC_RELATIVE ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return 0;
    } 

    if ( location == CPW_FONTLOC_HOST ) {
        
        pStr tmp = cpw_localhost_fontpath();

        concatStr( &fontPath, tmp );
        concatStr( &fontPath, fontName );
        freeStr( &tmp );

    }

    if ( location == CPW_FONTLOC_RELATIVE ) {

        /* opt: fontpath */

        if ( fontpath == 0 ) {
            cpw_error_set( cpw, cpw_error_invalidparameter );
            return 0;
        }

        setString( &fontPath, fontpath );

        concatString( &fontPath, CPW_LOCALHOST_DIRDIV );
        concatStr( &fontPath, fontName );

    }

    error = FT_New_Face( library, str( fontPath ), 0, &face );

    freeStr( &fontPath );
    freeStr( &fontName );

    if ( error != 0 ) {
        cpw_font_enterpreterror( cpw, error );
        return 0;
    }

    /* no caching yet - ft has a built-in cacher i'd like to use. */
    // cpw_font_cacheface( pface, cachelist );

	return (CpwFontFace) face;
}

/* unload a local or application font from memory */

bool
cpwUnloadFont( pCpw cpw, CpwFontFace font )
{
    CpwFontState *  cfs;
    FT_Library      library;
    FT_FaceRec*     face;

    cfs     = (CpwFontState*)cpw->ctx_font;
    library = (FT_Library)cfs->library;
    face    = (FT_FaceRec*)font;

    if ( face == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    } 

    FT_Done_Face( face );

    return true;
}


/*************************************************************************/
/*                                                                       */
/*   pen position advance per alignment and kerning                      */
/*                                                                       */
/*************************************************************************/

/* used in rendering. advances the pen values based on a character's
   size without applying kerning. */

void cpw_font_penadvance( FT_Face face, uint_32 align, 
                          int_32 * pos_x, int_32 * pos_y )
{
    switch( align ) {

        case CPW_FONTOPT_ALIGNCENTER:   /* align text center */
        case CPW_FONTOPT_ALIGNRIGHT:    /* align text right */
        case CPW_FONTOPT_ALIGNLEFT:     /* align text left */
        *pos_x = (face->glyph->advance.x >> 6);
        *pos_y = (face->glyph->advance.y >> 6);
        break;

        case CPW_FONTOPT_ALIGNUP:       /* align text up */
        break;

        case CPW_FONTOPT_ALIGNDOWN:     /* align text down */
        break;
    }
}

/* used in rendering w/kerning. advances the pen values based on the 
   last character drawn and th e one about to be drawn. */

void cpw_font_kernadvance( FT_Face face, uint_32 align,
                          uint_32 previous, uint_32 next, 
                          int_32 * pos_x, int_32 * pos_y )
{
    if ( previous && next )
    {
        FT_Vector  delta;

        FT_Get_Kerning( face, previous, next, 0, &delta );
          
        switch( align ) {

            case CPW_FONTOPT_ALIGNCENTER:   /* align text center */
            case CPW_FONTOPT_ALIGNRIGHT:    /* align text right */
            case CPW_FONTOPT_ALIGNLEFT:     /* align text left */
            *pos_x = (delta.x >> 6);
            *pos_y = (delta.y >> 6);
            break;

            case CPW_FONTOPT_ALIGNUP:       /* align text up */
            break;

            case CPW_FONTOPT_ALIGNDOWN:     /* align text down */
            break;
        }
    }
}

void cpw_font_alignright( char* string, FT_Face face )
{
}

void cpw_font_aligncenter( char* string, FT_Face face )
{
}

/*************************************************************************/
/*                                                                       */
/*   calculate a font string's bounding box dimensions                   */
/*                                                                       */
/*************************************************************************/

bool cpwGetFontBBox( pCpw cpw, CpwFontFace font, char* string, CpwFontBBox * bbox )
{
    CpwFontState *  cfs;
    FT_Library      library;
    FT_Face         face;
    int_32          width, height;
    int_32          glyph_index;
    int_32          last_index;
    int_32          index;
    int_32          downShift;
    char            c;
    bool            use_kerning;

    cfs     = (CpwFontState*)cpw->ctx_font;
    library = (FT_Library)cfs->library;
    face    = (FT_Face)font;

    last_index = 0; /* ft null character */
    index      = 0;

    /* invalid params */

    if ( face == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }

    if ( string == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }

    if ( bbox == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }

    /* ft character size */

    FT_Set_Char_Size( face,                  /* handle to face object           */
                      0,                     /* char_width in 1/64th of points  */
                      cfs->fontSize,         /* char_height in 1/64th of points */
                      cfs->screenWidth,      /* horizontal device resolution    */
                      cfs->screenHeight );   /* vertical device resolution      */


    /* does the face have kerning info? if not, theres no point in kerning */

    use_kerning = cfs->kerning & FT_HAS_KERNING(face);

    /* iterate each character */

    bbox->width   = 0;
    bbox->height  = 0;
    bbox->offsetx = 0;
    bbox->offsety = 0;

    while ( ( c = *(string+index) ) != 0 ) {

        index++;

        /* set the character were interested in */

        glyph_index = FT_Get_Char_Index( face, c );

        FT_Load_Glyph( face, glyph_index, FT_LOAD_NO_BITMAP );

        downShift = face->glyph->metrics.height / 64 - face->glyph->metrics.horiBearingY / 64;
        height = face->glyph->metrics.height / 64;
        width = ( face->glyph->advance.x / 64 ) * cfs->spacingMulti;

        bbox->width  = bbox->width + width;

        if ( bbox->height < height ) 
            bbox->height = height;

        if ( bbox->offsety < downShift ) 
            bbox->offsety = downShift;

        /*
        printf( "---%c----------------------------------------\n", c );

        printf( "face : height=%d descender=%d ascender=%d\n", 
                  face->height / 64, 
                  face->descender / 64, 
                  face->ascender / 64 );

        printf( "face bbox : xmin=%d xmax=%d ymin=%d ymax=%d\n", 
                  face->bbox.xMin / 64, face->bbox.xMax / 64, 
                  face->bbox.yMin / 64, face->bbox.yMax / 64 );

        printf( "glyph advance : x=%d y=%d\n", 
                  face->glyph->advance.x / 64, 
                  face->glyph->advance.y / 64 );

        printf( "glyph metrics : w=%d h=%d hbx=%d hby=%d vbx=%d vby=%d ha=%d va=%d\n", 
                  face->glyph->metrics.width / 64,        face->glyph->metrics.height / 64 );
                  face->glyph->metrics.horiBearingX / 64, face->glyph->metrics.horiBearingY / 64,
                  face->glyph->metrics.vertBearingX / 64, face->glyph->metrics.vertBearingY / 64, 
                  face->glyph->metrics.horiAdvance / 64,  face->glyph->metrics.vertAdvance / 64 );

        printf( "horizontal offsets: bx=%d by=%d w-bx=%d h-by=%d\n", 
                  face->glyph->metrics.horiBearingX / 64, face->glyph->metrics.horiBearingY / 64, 
                  face->glyph->metrics.width / 64 - face->glyph->metrics.horiBearingX / 64,
                  downShift );
        */
    }

    /*
    printf( "texture dimensions : w=%d h=%d maxdown=%d\n", 
            bbox->width, bbox->height, bbox->offsety );
    */

    return true;
}

/*************************************************************************/
/*                                                                       */
/*   freetype grayscale buffer to gl format buffer conversion            */
/*                                                                       */
/*************************************************************************/

/* convert a font character drawn in 256 gray scale to a RGB or RGBA image. */

bool cpw_font_pixelmap_convert( CpwFontState* cfs, CpwFontBuffer* image, int_32 format, 
                                uint_32 width, uint_32 height, char* data ) 
{
    uint_32 byteSize;
    
    switch ( format ) {
        case GL_RGBA:
            byteSize = 4;
            break;
        case GL_RGB:
            byteSize = 3;
            break;
        default:
            image->w         = width;
            image->h         = height;
            image->data      = data;
            image->glformat  = format;
        return true;
    }

    /* incoming data from freetype is a 256 gray scale bitmap image. if the user
       has requested something with color, convert the image data, otherwise return 
       ft's buffer data.

        GL_COLOR_INDEX                          - no conversion
        GL_STENCIL_INDEX                        - no conversion
        GL_DEPTH_COMPONENT                      - no conversion
        GL_RGBA, GL_RGB                         - convert
        GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA     - no conversion
        GL_LUMINANCE                            - no conversion
        GL_LUMINANCE_ALPHA                      - no conversion
    */

    {
        float color[4];
        //float glbgcolor[4];
        //uint_8 bgcolor[4];

        uint_32 position = 0;
        uint_32 index    = 0;
        uint_32 bufsize  = (width*byteSize)*height;
        char * buffer;

        /* we cache a buffer in the font state for conversion. the first time
           we draw a char it is created. ever subsequent conversion we simply
           make sure it's large enough. when cpw exits, we free it. */

        if ( bufsize > cfs->pixelbuffersize )
            cfs->pixelbuffer = (char*)cpwrealloc( cfs->pixelbuffer, bufsize );

        if ( cfs->pixelbuffer == 0 )
            return false;

        cfs->pixelbuffersize = bufsize;
        buffer = cfs->pixelbuffer;

        glGetFloatv( GL_CURRENT_COLOR, color ); /* 0.0 -> 1.0 color values */

        /*
        glGetFloatv( GL_COLOR_CLEAR_VALUE, glbgcolor ); /* 0.0 -> 1.0 color values 
        bgcolor[0] = (uint_8) ( glbgcolor[0] * 255 );
        bgcolor[1] = (uint_8) ( glbgcolor[1] * 255 );
        bgcolor[2] = (uint_8) ( glbgcolor[2] * 255 );
        bgcolor[3] = (uint_8) ( glbgcolor[3] * 255 );
        */

        /* convert to rgba from grayscale */
            
        if ( format == GL_RGBA )
          for( index = 0; index < width*height; index++ ) 
          {
            *(buffer + position + 0) = (char) ( ( (uint_8) *( data + index ) ) * color[0] );
            *(buffer + position + 1) = (char) ( ( (uint_8) *( data + index ) ) * color[1] );
            *(buffer + position + 2) = (char) ( ( (uint_8) *( data + index ) ) * color[2] );
            *(buffer + position + 3) = (char) ( ( (uint_8) *( data + index ) ) * color[3] );
            /*
            if ( *(buffer + position + 0) < bgcolor[0] ) 
            *(buffer + position + 0) = (char) bgcolor[0];

            if ( *(buffer + position + 1) < bgcolor[1] ) 
            *(buffer + position + 1) = (char) bgcolor[1];

            if ( *(buffer + position + 2) < bgcolor[2] ) 
            *(buffer + position + 2) = (char) bgcolor[2];

            if ( *(buffer + position + 3) < bgcolor[3] ) 
            *(buffer + position + 3) = (char) bgcolor[3];
            */
            position = position + byteSize;
          }

        /* convert to rgb from grayscale */

        else if ( format == GL_RGB )
          for( index = 0; index < width*height; index++ ) 
          {
            *(buffer + position + 0) = (char) ( ( (uint_8) *( data + index ) ) * color[0] );
            *(buffer + position + 1) = (char) ( ( (uint_8) *( data + index ) ) * color[1] );
            *(buffer + position + 2) = (char) ( ( (uint_8) *( data + index ) ) * color[2] );
            position = position + byteSize;
          }

        /* everything else keeps grayscale */

        image->w         = width;
        image->h         = height;
        image->data      = buffer;
        image->glformat  = format;
    }

    return true;
}

/* free any conversion buffer memory we have allocated */

void cpw_font_pixelmap_convertfree( CpwFontState * cfs )
{
    if ( cfs->pixelbuffersize > 0 ) cpwfree( cfs->pixelbuffer );
}


/*************************************************************************/
/*                                                                       */
/*   draw a pixelmap font string in gl                                   */
/*                                                                       */
/*************************************************************************/

bool
cpwDrawFont( pCpw cpw, CpwFontFace font, char* string, bool drawflag )
{
    CpwFontState *  cfs;
    FT_Library      library;
    FT_Face         face;
    int_32          pos_x, pos_y;
    int_32          glyph_index;
    int_32          last_index;
    int_32          index;
    char            c;
    bool            use_kerning;

    cfs     = (CpwFontState*)cpw->ctx_font;
    library = (FT_Library)cfs->library;
    face    = (FT_Face)font;

    last_index = 0; /* ft null character */
    index      = 0;

    /* invalid params */

    if ( face == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }

    if ( string == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }

    /* ft character size */

    FT_Set_Char_Size( face,                  /* handle to face object           */
                      0,                     /* char_width in 1/64th of points  */
                      cfs->fontSize,         /* char_height in 1/64th of points */
                      cfs->screenWidth,      /* horizontal device resolution    */
                      cfs->screenHeight );   /* vertical device resolution      */

    /* does the face have kerning info? if not, theres no point in kerning */

    use_kerning = cfs->kerning & FT_HAS_KERNING(face);

    /* draw it or just calculate the bounding box? */

    if ( drawflag == 1 ) {

        /* save current gl state and setup gl for ft font bitmap format */

        glPushClientAttrib( GL_CLIENT_PIXEL_STORE_BIT );
        glPushAttrib( GL_PIXEL_MODE_BIT );

        glPixelStorei( GL_UNPACK_LSB_FIRST, GL_FALSE );
        glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

    }
    
    /* pre-draw alignment processing if needed */

    /* for align right, we have to adjust our drawing position by the width
       of the string, which takes some extra processing. */

    if ( cfs->alignMode == CPW_FONTOPT_ALIGNRIGHT )  
        cpw_font_alignright( string, face );

    /* for align center, we have to adjust our drawing position by half the width
       of the string, which takes some extra processing. */

    else if ( cfs->alignMode == CPW_FONTOPT_ALIGNCENTER )  
        cpw_font_aligncenter( string, face );
        
    /* draw each charcter */

    while ( ( c = *(string+index) ) != 0 ) {

        index++;

        /* set the character were interested in */

        glyph_index = FT_Get_Char_Index( face, c );

        /* load and draw or just load the info */

        if ( drawflag == 1 ) 
            FT_Load_Glyph( face, glyph_index, FT_LOAD_RENDER  );
        else
            FT_Load_Glyph( face, glyph_index, FT_LOAD_NO_BITMAP  );

        /* reject anything that isn't a bitmap font */

        if ( face->glyph->format != ft_glyph_format_bitmap ) 
            continue;

        /* draw */

        if ( drawflag == 1 ) {

            CpwFontBuffer image;

            /* if the pixel data needs to be expanded based on the preference set, do so.
               RGB or RGBA require a conversion, everything else just returns the ft 
               buffer. */

            if ( !cpw_font_pixelmap_convert( cfs, &image, cfs->pixmap_format,
                                             face->glyph->bitmap.width, 
                                             face->glyph->bitmap.rows,
                                             face->glyph->bitmap.buffer ) ) {
                cpw_error_set( cpw, cpw_error_outofmemory );
                return false;
            }
                        
            pos_y = face->glyph->bitmap_top;
            pos_x = face->glyph->bitmap_left;

            /* freetype bitmaps are upside down to gl, flip them over */

            glPixelZoom(1, -1); 

            glBitmap( 0, 0, 0.0, 0.0, (float)pos_x, (float)pos_y, (const GLubyte *)0);

            glDrawPixels( image.w, image.h, image.glformat, GL_UNSIGNED_BYTE, image.data );

            glBitmap( 0, 0, 0.0, 0.0, -1*(float)pos_x, -1*(float)pos_y, (const GLubyte *)0);

            /* flip back over */

            glPixelZoom(1, -1); 

            /* advance spacing value with kerning or without kerning */

            switch( use_kerning ) {
                case 0:
                    cpw_font_penadvance( face, cfs->alignMode, &pos_x, &pos_y );
                break;
                case 1:
                    cpw_font_kernadvance( face, cfs->alignMode, glyph_index, last_index, 
                                          &pos_x, &pos_y );
                    last_index = glyph_index; /* save last glyph index */
                break;
            }
        }

        glBitmap( 0, 0, 0.0, 0.0, (float)pos_x, (float)pos_y, (const GLubyte *)0);
    }

    if ( drawflag == 1 ) {
        glPopClientAttrib();
        glPopAttrib();
    }

    return true;
}

/*************************************************************************/
/*                                                                       */
/*   draw a font string to a bitmap                                      */
/*                                                                       */
/*************************************************************************/

bool cpwDrawBufferedFont( pCpw cpw, CpwFontFace font, char* string, CpwFontBuffer * cpwbuffer )
{
    CpwFontState *  cfs;
    FT_Library      library;
    FT_Face         face;
    int_32          glyph_index;
    int_32          last_index;
    char            c;
    char *          buffer;
    bool            use_kerning;

    CpwFontBBox     bbox;
    CpwFontBuffer   image;

    uint_32         bufsize;
    uint_32         xoffset;
    uint_32         strindex;
    uint_32         bufindex;
    uint_32         pixelSize;
    int_32          charDownShift;
    uint_32         dsty;
    uint_32         dstx;

    uint_32 y, x, position;

    cfs     = (CpwFontState*)cpw->ctx_font;
    library = (FT_Library)cfs->library;
    face    = (FT_Face)font;

    last_index = 0; /* ft null character */
    strindex   = 0;

    /* invalid params */

    if ( face == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }

    if ( string == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }

    if ( cpwbuffer == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }

    memset( &bbox, 0, sizeof( CpwFontBBox ) );

    /* ft character size */

    FT_Set_Char_Size( face,                  /* handle to face object           */
                      0,                     /* char_width in 1/64th of points  */
                      cfs->fontSize,         /* char_height in 1/64th of points */
                      cfs->screenWidth,      /* horizontal device resolution    */
                      cfs->screenHeight );   /* vertical device resolution      */


    /* does the face have kerning info? if not, theres no point in kerning */

    use_kerning = cfs->kerning & FT_HAS_KERNING(face);

    /* pre-draw bbox calculations */

    if ( !cpwGetFontBBox( cpw, font, string, &bbox ) ) return false;

    /* create the appropriate buffer */

    switch ( cfs->pixmap_format ) {
        case GL_RGBA:
            pixelSize = 4;
            bufsize  = ( bbox.width * pixelSize ) * ( bbox.height + bbox.offsety );
            break;
        case GL_RGB:
            pixelSize = 3;
            bufsize  = ( bbox.width * pixelSize ) * ( bbox.height + bbox.offsety );
            break;
        default:
            pixelSize = 1;
            bufsize  = ( bbox.width ) * ( bbox.height + bbox.offsety );
    }

    buffer = cpwmalloc( bufsize );

    if ( buffer == 0 ) {
        cpw_error_set( cpw, cpw_error_outofmemory );
        return false;
    }

    memset( buffer, 0, bufsize );

    xoffset  = 0;
    strindex = 0;
    bufindex = 0;

    /* draw each character into the buffer */

    while ( ( c = *( string + strindex ) ) != 0 ) {

        strindex++;

        /* set the character were interested in */

        glyph_index = FT_Get_Char_Index( face, c );

        /* load and draw or just load the info */

        //FT_Load_Glyph( face, glyph_index, FT_LOAD_MONOCHROME  );
        FT_Load_Glyph( face, glyph_index, FT_LOAD_RENDER  );

        /* reject anything that isn't a bitmap font */

        if ( face->glyph->format != ft_glyph_format_bitmap ) 
            continue;

        /* if the pixel data needs to be expanded based on the preference set, do so.
           RGB or RGBA require a conversion, everything else just returns the ft 
           buffer. */

        if ( !cpw_font_pixelmap_convert( cfs, &image, cfs->pixmap_format,
                                         face->glyph->bitmap.width, 
                                         face->glyph->bitmap.rows,
                                         face->glyph->bitmap.buffer ) ) 
        {
            cpw_error_set( cpw, cpw_error_outofmemory );
            return false;
        }

        /* 

            The buffer we are rendering to (destination):
            --------------------------------------------
            |A B C D E . . .                           |
            --------------------------------------------

            which is represented in memory as a very long string of bytes.

            destinationWidth

            ---------------
            |   ||   ||   |  
            | 1 || 2 || 3 |  destinationHeight
            |   ||   ||   |
            --------------- . . . 

             Gray, RGB, RGBA - pixelSize
        
            Writing to the destination buffer:
            
            position = ( ( destinationWidth * y ) + 'width of past chars drawn' +
                         'current glyph xpos' ) * pixelSize

            position = ( ( destinationWidth * y ) + xoffset + x ) * pixelSize

            
            Getting the src buffer data:

            byte_n = image.data + n + ( ( x + ( y * image.w ) ) * pixelSize ); 

            ^^^^^^                              
            n = 1, 2, 3, 4 depending on the pixel format (pixelSize)

            Now, we have to read data from the bottom row of the freetype bitmap 
            up, and write into the gl buffer from the top down, since ft's y 
            orientation is reversed from gl's. ( the ft bitmap is flipped upside 
            down from gl's perspective, so we flip it over when we write it into
            the destination buffer )

            byte_n = image.data + n + ( ( x + ( ( image.h - y - 1 ) * image.w ) ) * pixelSize ); 

                                                 ^^^^^^^^^^^^^^^^
                                                    flip over 

            Now we have to offset things so chars have correct vertical alignment.
            otherwise we end up with all characters resting at the base of the 
            texture. 

            The origin of our texture is bottom left, but we don't want characters
            sitting on this base line. We want them pushed up a bit based on what 
            character they are. Freetype gives us this offset in vertBearingY and
            we calculated the max offset for the whole string in the get bbox call 
            above. (We created a texture large enough to hold all characters.)

            downShift = ( face->glyph->metrics.height / 64 ) - ( face->glyph->metrics.horiBearingY / 64 );
            dsty = ( image.h - y - 1 );
            dsty = dsty + ( bbox.offsety - downShift );

            We also need to offset x so the position of the character is centered in it's
            rectangle. Which is given to us in abs(face->glyph->metrics.horiBearingX / 64) ).

            See http://www.freetype.org/freetype2/docs/tutorial/step2.html for an in depth
            look at the information we have for each character's layout position.

            STH@STimg src="metrics.png"STH@GT

        */

        dsty = 0;
        dstx = 0;

        /* the downshift is the value by which the individual character is offset in y for
        correct positioning along the baseline */

        charDownShift = ( face->glyph->metrics.height / 64 ) - ( face->glyph->metrics.horiBearingY / 64 );

        for( y = 0; y < image.h; y++ )  /* rows */
        for( x = 0; x < image.w; x++ ) /* colums */
        {
            /* start drawing at the lowest row of the buffer */

            dsty = ( image.h - y - 1 );

            /* slide up the total offset for the string minus this character's offset */

            dsty = dsty + ( bbox.offsety - charDownShift );

            position = ( ( bbox.width * dsty ) + ( xoffset + (face->glyph->metrics.horiBearingX / 64) ) + x ) * pixelSize;

            *( buffer + position ) = *( image.data + ( ( x + ( y * image.w ) ) * pixelSize ) ); 

            if ( pixelSize > 1 ) {
            *( buffer + position + 1 ) = *( image.data + 1 + ( ( x + ( y * image.w ) ) * pixelSize ) ); 
            *( buffer + position + 2 ) = *( image.data + 2 + ( ( x + ( y * image.w ) ) * pixelSize ) ); 
            if ( pixelSize == 4 )
            *( buffer + position + 3 ) = *( image.data + 3 + ( ( x + ( y * image.w ) ) * pixelSize ) ); 
            }

            /* draw a debug rectangle on the edges of the character's rectangle */

            if ( cfs->layoutdebug )
              if ( y == 0 || x == 0 || y+1 == image.h || x+1 == image.w )
                  *( buffer + position ) = (char)*( buffer + position ) | 0x5f;
        }

        xoffset = xoffset + ( ( face->glyph->advance.x >> 6 ) * cfs->spacingMulti );

        /* kerning not supported yet */

    }

    cpwbuffer->data = buffer;
    cpwbuffer->w = bbox.width;
    cpwbuffer->h = bbox.height;
    cpwbuffer->glformat = cfs->pixmap_format;

    /* draw a debug rectangle on the edges of the texture */

    if ( cfs->layoutdebug ) {
        for( y = 0; y < cpwbuffer->h; y++ )  /* rows */
        for( x = 0; x < cpwbuffer->w; x++ ) /* colums */
        {
            position = ( ( cpwbuffer->w * y ) + x ) * pixelSize;

            if ( y == 0 || x == 0 || y+1 == cpwbuffer->h || x+1 == cpwbuffer->w ) {
                *( buffer + position ) = (char)*( buffer + position ) | 0x7f;
            }
        }
    }

    return true;
}
                       
bool cpwFreeBufferedFont( pCpw cpw, CpwFontBuffer * buffer )
{
    if ( buffer == 0 ) {
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }
    cpwfree( buffer->data );
    memset( buffer, 0, sizeof( CpwFontBuffer ) );
    return true;
}

