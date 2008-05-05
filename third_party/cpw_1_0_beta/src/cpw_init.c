/***************************************************************************/
/*                                                                         */
/*  cpw_init.c                                                             */
/*                                                                         */
/*    The Cpw library init interface.                                      */
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

#include "cpw_init.h"
#include "cpw_error.h"

/*************************************************************************/
/*                                                                       */
/*   init and exit.                                                      */
/*                                                                       */
/*************************************************************************/

/* default printf handler if not overridden */

void cpw_init_defaultprint( char * string ) 
{
    if ( string == 0 ) return;
    fprintf( stderr, string ); 
}

/* init the basic cpw settings */

bool cpw_init_init( pCpw cpw )
{
    cpw->cpw_displaymode    = CPW_SURFACE_RGBA | CPW_SURFACE_DOUBLE |
                              CPW_SURFACE_DEPTH | CPW_SURFACE_DEPTH8;
    cpw->cpw_screenwidth    = 300;
    cpw->cpw_screenheight   = 300;
    cpw->win_initx          = 100;
    cpw->win_inity          = 100;
    cpw->win_initwidth      = 200;
    cpw->win_initheight     = 300;
    cpw->cpw_print          = cpw_init_defaultprint;
    cpw->win_properties     = CPW_WINDOWPROP_STANDARD | CPW_WINDOWPROP_THICKBORDER;
    cpw->win_expectmenu     = false;

    return true;
}

void cpw_init_exit( pCpw cpw )
{
    /* nothing to do */
}

/*************************************************************************/
/*                                                                       */
/*   init api                                                            */
/*                                                                       */
/*************************************************************************/

bool
cpwInitWindowPosition( pCpw cpw, uint_32 x, uint_32 y ) 
{
    cpw->win_initx = x;
    cpw->win_inity = y;
    return true;
}

bool
cpwInitWindowSize( pCpw cpw, uint_32 width, uint_32 height )
{
    cpw->win_initwidth = width;
    cpw->win_initheight = height;
    return true;
}

bool
cpwInitWindowProperty( pCpw cpw, uint_32 property, uint_32 paramone, uint_32 paramtwo )
{

    /* window style settings */

    if ( property == CPW_WINDOWPROP_STANDARD ) {
        cpw->win_properties = cpw->win_properties & CPW_WINDOWPROP_STYLECLRMASK;
        cpw->win_properties = cpw->win_properties | CPW_WINDOWPROP_STANDARD;
        return true;
    } else if ( property == CPW_WINDOWPROP_POPUP ) {
        cpw->win_properties = cpw->win_properties & CPW_WINDOWPROP_STYLECLRMASK;
        cpw->win_properties = cpw->win_properties | CPW_WINDOWPROP_POPUP;
        return true;
    } else if ( property == CPW_WINDOWPROP_NODRESSING ) {
        cpw->win_properties = cpw->win_properties & CPW_WINDOWPROP_STYLECLRMASK;
        cpw->win_properties = cpw->win_properties | CPW_WINDOWPROP_NODRESSING;
        return true;
    }

    /* window border settings */

    if ( property == CPW_WINDOWPROP_THICKBORDER ) {
        cpw->win_properties = cpw->win_properties & CPW_WINDOWPROP_BORDERCLRMASK;
        cpw->win_properties = cpw->win_properties | CPW_WINDOWPROP_THICKBORDER;
        return true;
    } else if ( property == CPW_WINDOWPROP_THINBORDER ) {
        cpw->win_properties = cpw->win_properties & CPW_WINDOWPROP_BORDERCLRMASK;
        cpw->win_properties = cpw->win_properties | CPW_WINDOWPROP_THINBORDER;
        return true;
    } else if ( property == CPW_WINDOWPROP_NOBORDER ) {
        cpw->win_properties = cpw->win_properties & CPW_WINDOWPROP_BORDERCLRMASK;
        cpw->win_properties = cpw->win_properties | CPW_WINDOWPROP_NOBORDER;
        return true;
    }

    /* window expects a titlebar menu */

    if ( property == CPW_WINDOWPROP_EXPECTMENU ) {
        cpw->win_expectmenu = true;
        return true;
    }

    /* window desktop position */

    if ( property == CPW_WINDOWPROP_POSITION ) {
        cpw->win_initx = paramone;
        cpw->win_inity = paramtwo;
        return true;
    }

    /* window width and height */

    if ( property == CPW_WINDOWPROP_SIZE ) {
        cpw->win_initwidth = paramone;
        cpw->win_initheight = paramtwo;
        return true;
    }

    /* window takes desktop settings */

    if ( property == CPW_WINDOWPROP_DESKTOP ) {
        cpw->win_initx = 0;
        cpw->win_inity = 0;
        cpw->win_initwidth = cpw->cpw_screenwidth;
        cpw->win_initheight = cpw->cpw_screenheight;
        return true;
    }

    /* error - bad option */

    cpw_error_set( cpw, cpw_error_invalidparameter );
    return false;
}

bool
cpwInitDisplayMode( pCpw cpw, uint_32 mask )
{
    cpw->cpw_displaymode = mask;
    return true;
}

bool
cpwInitPrintHandler( pCpw cpw, CpwPrintHandler print )
{
    cpw->cpw_print = print;
    return true;
}

/*************************************************************************/
/*                                                                       */
/*   init string api                                                     */
/*                                                                       */
/*************************************************************************/

bool 
cpwInitDisplayModeExact( pCpw cpw, uint_32 mode, uint_32 condition, int_32 value )
{
    return false;
}

/*

#define  CPW_NONE                             0x0000
#define  CPW_EQUAL                            0x0001
#define  CPW_NOT_EQUAL                        0x0002
#define  CPW_LESS                             0x0003
#define  CPW_MORE                             0x0004
#define  CPW_LESS_OR_EQUAL                    0x0005
#define  CPW_MORE_OR_EQUAL                    0x0006
#define  CPW_CLOSEST                          0x0007

#define    CPW_SURFACEX_ALPHA                 1
#define    CPW_SURFACEX_ACCUM                 2
#define    CPW_SURFACEX_RED                   3
#define    CPW_SURFACEX_GREEN                 4
#define    CPW_SURFACEX_BLUE                  5
#define    CPW_SURFACEX_INDEXCOLORBUFFER      6
#define    CPW_SURFACEX_CONFORMANT            7
#define    CPW_SURFACEX_DEPTH                 8
#define    CPW_SURFACEX_DOUBLE                9
#define    CPW_SURFACEX_INDEX                 10
#define    CPW_SURFACEX_NUM                   11
#define    CPW_SURFACEX_RGBA                  12
#define    CPW_SURFACEX_RGB                   13
#define    CPW_SURFACEX_LUMINANCE             14
#define    CPW_SURFACEX_STENCIL               15
#define    CPW_SURFACEX_SINGLE                16
#define    CPW_SURFACEX_STEREO                17
#define    CPW_SURFACEX_SAMPLES               18
#define    CPW_SURFACEX_SLOW                  19
#define    CPW_SURFACEX_WIN32PDF              20
#define    CPW_SURFACEX_XVISUAL               21
#define    CPW_SURFACEX_XSTATICGRAY           22
#define    CPW_SURFACEX_XGRAYSCALE            23
#define    CPW_SURFACEX_XSTATICCOLOR          24
#define    CPW_SURFACEX_XPSEUDOCOLOR          25
#define    CPW_SURFACEX_XTRUECOLOR            26
#define    CPW_SURFACEX_XDIRECTCOLOR          27

NAME
     glutInitDisplayString - sets the initial display mode via  a
     string.

SYNTAX
     void glutInitDisplayString(char *string);

ARGUMENTS
     string    Display mode description string, see below.



DESCRIPTION
     The initial display mode description  string  is  used  when
     creating  top-level  windows,  subwindows,  and  overlays to
     determine the OpenGL display mode for the to-be-created win-
     dow or overlay.

     The string is a list of zero or more capability descriptions
     separated  by  spaces and tabs.  Each capability description
     is a capability name that is optionally followed by  a  com-
     parator  and  a  numeric  value.   For example, "double" and
     "depth>=12" are both valid criteria.

     The capability descriptions are translated  into  a  set  of
     criteria  used to select the appropriate frame buffer confi-
     guration.

     The criteria are matched in strict left to  right  order  of
     precdence.  That is, the first specified criteria (leftmost)
     takes precedence over the later criteria for non-exact  cri-
     teria  (greater  than,  less than, etc. comparators).  Exact
     criteria (equal, not equal compartors) must match exactly so
     precedence is not relevant.

     The numeric value is an integer that is parsed according  to
     ANSI  C's  strtol(str, strptr, 0) behavior.  This means that
     decimal, octal (leading 0), and hexidecimal values  (leading
     0x) are accepeted.

     The valid compartors are:

     =       Equal.

     !=      Not equal.

     <       Less than  and  preferring  larger  difference  (the
             least is best).

     >       Greeater than and preferring larger differences (the
             most is best).

     <=      Less than or equal and preferring larger  difference
             (the least is best).

     >=      Greater than or equal and preferring more instead of
             less.   This  comparator  is  useful  for allocating
             resources like color precsion or depth buffer preci-
             sion  where  the  maximum precison is generally pre-
             ferred.  Contrast with the tilde (~) comprator.

     ~       Greater than or equal but preferring less instead of
             more.   This  compartor  is  useful  for  allocating
             resources such as stencil bits  or  auxillary  color
             buffers where you would rather not over allocate.

             When the compartor and numeric value are not  speci-
             fied,  each  capability name has a different default
             (one default is to require a a compartor and numeric
             value).


     The valid capability names are:

     alpha   Alpha color buffer precision in  bits.   Default  is
             ">=1".

     acca    Red, green, blue, and alpha accumulation buffer pre-
             cision  in  bits.   Default is ">=1" for red, green,
             blue, and alpha capabilities.

     acc     Red, green, and green accumulation buffer  precision
             in  bits  and zero bits of alpha accumulation buffer
             precision.  Default is ">=1"  for  red,  green,  and
             blue  capabilities,  and "~0" for the alpha capabil-
             ity.

     blue    Blue color buffer precision  in  bits.   Default  is
             ">=1".

     buffer  Number of bits in  the  color  index  color  buffer.
             Default is ">=1".

     conformant
             Boolean indicating if the frame buffer configuration
             is  conformant  or  not.  Conformance information is
             based on GLX's EXT_visual_rating extension  if  sup-
             ported.   If  the  extension  is  not supported, all
             visuals are assumed conformat.  Default is "=1".

     depth   Number of bits of  precsion  in  the  depth  buffer.
             Default is ">=12".

     double  Boolean indicating if the  color  buffer  is  double
             buffered.  Default is "=1".

     green   Green color buffer precision in  bits.   Default  is
             ">=1".

     index   Boolean if the color model is color  index  or  not.
             True is color index.  Default is ">=1".

     num     A special capability name indicating where the value
             represents the Nth frame buffer configuration match-
             ing the description  string.   When  not  specified,
             glutInitDisplayString  also  returns the first (best
             matching) configuration.  num requires  a  compartor
             and numeric value.

     red     Red color buffer  precision  in  bits.   Default  is
             ">=1".

     rgba    Number of bits of red, green, blue, and alpha in the
             RGBA color buffer.  Default is ">=1" for red, green,
             blue, and alpha capabilities, and "=1" for the  RGBA
             color model capability.

     rgb     Number of bits of red, green, and blue in  the  RGBA
             color buffer and and zero bits of alpha color buffer
             precision.  Default is ">=1" for the red, green, and
             blue  capabilities,  and  "~0" for alpha capability,
             and "=1" for the RGBA color model capability.

     stencil Number of bits in the stencil buffer.

     single  Boolean indicate the color  buffer  is  single  buf-
             fered.  Double buffer capability "=1".

     stereo  Boolean indicating  the  color  buffer  is  supports
             OpenGL-style stereo.  Default is "=1".

     samples Indicates the number of multisamples to use based on
             GLX's SGIS_multisample extension (for antialiasing).
             Default is "<=4".  This default means  that  a  GLUT
             application  can request multipsampling if available
             by simply specifying "samples".

     slow    Boolean indicating if the frame buffer configuration
             is  slow  or  not.  Slowness information is based on
             GLX's EXT_visual_rating extension if supported.   If
             the  extension  is  not  supported,  all visuals are
             assumed fast.  Note  that  slowness  is  a  relative
             designation  relative  to  other frame buffer confi-
             gurations available.  The intent of the  slow  capa-
             bility is to help programs avoid frame buffer confi-
             gurations that are slower (but perhaps higher preci-
             sion)  for  the  current machine.  Default is ">=0".
             This default means that slow  visuals  are  used  in
             preference  to  fast  visuals, but fast visuals will
             still be allowed.

     xvisual Only recongized on GLUT implementations  for  the  X
             Window  System,  this  capability name matches the X
             visual ID by number.  xvisual requires  a  compartor
             and numeric value.

     xstaticgray
             Only recongized on GLUT implementations  for  the  X
             Window  System,  boolean  indicating  if  the  frame
             buffer configuration's X  visual  is  of  type  Sta-
             ticGray.  Default is "=1".

     xgrayscale
             Only recongized on GLUT implementations  for  the  X
             Window  System,  boolean  indicating  if  the  frame
             buffer configuration's X visual is  of  type  GrayS-
             cale.  Default is "=1".

     xstaticcolor
             Only recongized on GLUT implementations  for  the  X
             Window  System,  boolean  indicating  if  the  frame
             buffer configuration's X  visual  is  of  type  Sta-
             ticColor.  Default is "=1".

     xpseudocolor
             Only recongized on GLUT implementations  for  the  X
             Window  System,  boolean  indicating  if  the  frame
             buffer  configuration's  X   visual   is   of   type
             PsuedoColor.  Default is "=1".

     xtruecolor
             Only recongized on GLUT implementations  for  the  X
             Window  System,  boolean  indicating  if  the  frame
             buffer  configuration's  X   visual   is   of   type
             TrueColor.  Default is "=1".

     xdirectcolor
             Only recongized on GLUT implementations  for  the  X
             Window  System,  boolean  indicating  if  the  frame
             buffer  configuration's  X   visual   is   of   type
             DirectColor.  Default is "=1".

     Unspecifed capability descriptions will result  in  unspeci-
     fied  criteria  being generated.  These unspecified criteria
     help  glutInitDisplayString  behave  sensibly   with   terse
     display mode description strings.



EXAMPLE
     Here is an examples using glutInitDisplayString:


       glutInitDisplayString("stencil~2 rgb double depth>=16 samples");

     The above call requests a window with an  RGBA  color  model
     (but  requesting  no  bits of alpha), a depth buffer with at
     least 16 bits of precsion but preferring more, mutlisampling
     if  available, and at least 2 bits of stencil (favoring less
     stencil to more as long as 2 bits are available).

*/
