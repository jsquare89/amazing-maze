/****************************************************/
/*  Basic Win32 Template                            */
/****************************************************/

/* 
  Cpw link options:

  #define CPW_EXTERN        - link to the static lib
  #define CPWDLL_EXTERN     - link to the release dll's stub
  #define CPWDLLDBG_EXTERN  - link to the debug dll's stub
  #define CPWEXTDLL_EXTERN  - link to the release dll with cpw addons 
*/

#define CPWDLL_EXTERN

#include <cpw.h>

/* handy window characteristics holder */

static CpwWindowInfo windowInfo = { 0,100,100,250,300 }; /* id,posx,posy,w,h */


/****************************************************/
/*  OpenGL 2D Matrix Setup                          */
/****************************************************/

void set2DMatrix( void ) 
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0, windowInfo.width, 0, windowInfo.height );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

/****************************************************/
/*  OpenGL 3D Matrix Setup                          */
/****************************************************/

void set3DMatrix( void ) 
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 60, (float)windowInfo.width / (float)windowInfo.height, 1, 100 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

/****************************************************/
/*  Draw Window One                                 */
/****************************************************/

void drawWindowOne( pCpw cpw ) 
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    set2DMatrix();

    /* draw something in the window with OpenGL */
}

/****************************************************/
/*  Window Draw Event callback                      */
/****************************************************/

void draw( pCpw cpw, uint_32 winid )
{
    drawWindowOne( cpw );
    cpwSwapWindowBuffers( cpw, winid );
}

/****************************************************/
/*  Window Create / Destroy Event callback          */
/****************************************************/

void window( pCpw cpw, uint_32 winid, bool flag )
{
    /* creation event */

    if ( flag == true ) {

        glShadeModel( GL_SMOOTH );
        glDepthFunc( GL_LEQUAL );
        glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
        glEnable( GL_LINE_SMOOTH );
        glEnable( GL_POLYGON_SMOOTH );
        glClearColor( 0.0, 0.0, 0.0, 1.0 );
        return;
    }

    /* window close event */

    if ( flag == false ) {
        cpwDestroyWindow( cpw, winid );
        return;
    }
}

/****************************************************/
/*  Window Resize Event callback                    */
/****************************************************/

void reshape( pCpw cpw, uint_32 winid, uint_32 width, uint_32 height )
{
    if ( height == 0 ) { height = 1; }
    if ( width == 0 )  { width = 1; }

    windowInfo.width = width;
    windowInfo.height = height;

    set2DMatrix();

    glViewport( 0, 0, width, height );
}


/****************************************************/
/*  Main                                            */
/****************************************************/

#ifdef _WINDOWS
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
#elif _CONSOLE
int main(int argc, char* argv[])
#endif
{
    pCpw cpw = null;

    /****************************************************/
    /*  Init                                            */
    /****************************************************/

    cpwInitContext( &cpw );

    /****************************************************/
    /*  Creaing Windows                                 */
    /****************************************************/
    
    windowInfo.id = 
    cpwCreateWindowEx( cpw, "Basic Template", windowInfo.x, windowInfo.y, 
                             windowInfo.width, windowInfo.height );

    /****************************************************/
    /*  Event Callbacks                                 */
    /****************************************************/

    cpwCreateCallback( cpw, window );
    cpwDisplayCallback( cpw, draw );
    cpwReshapeCallback( cpw, reshape );

    /****************************************************/
    /*  MainLoop                                        */
    /****************************************************/

    cpwMainLoop( cpw );

    /****************************************************/
    /*  Exit and Free                                   */
    /****************************************************/

    cpwFreeContext( &cpw );

    return 0;
}

