
/****************************************************/
/*  Basic Win32 Template                            */
/****************************************************/

#include <cpw.h>
#include "../../library/addons/glextensions/cpwext_glextensions.h"

/* extension support info */

static GLExtensionSupport info;

/* handy window characteristics holder */

static CpwWindowInfo windowInfo = { 0,100,100,250,300 }; /* id,posx,posy,w,h */

#pragma comment (lib, "CpwDLL.lib" ) /* dynamic dll */

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
    gluPerspective( 60, windowInfo.width / windowInfo.height, 1, 100 );
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
    /*  GL Extensions                                   */
    /****************************************************/

    while ( ( p = cpwIterateExtensions( cpw ) ) != 0 ) {
        printf( "Extension '%s' supported.\n", p );
    }

    cpwextInitOpenGLExtensions( cpw, &info );

    printf( "Extensions you can use:\n" );

    printf( "ARB_imaging: %d\n", glExtInfo.ARB_imaging );
    printf( "ARB_matrix_palette: %d\n", glExtInfo.ARB_matrix_palette );
    printf( "ARB_multisample: %d\n", glExtInfo.ARB_multisample );
    printf( "ARB_multitexture: %d\n", glExtInfo.ARB_multitexture );
    printf( "ARB_point_parameters: %d\n", glExtInfo.ARB_point_parameters );
    printf( "ARB_texture_compression: %d\n", glExtInfo.ARB_texture_compression );
    printf( "ARB_texture_env_add: %d\n", glExtInfo.ARB_texture_env_add );
    printf( "ARB_texture_env_dot3: %d\n", glExtInfo.ARB_texture_env_dot3 );
    printf( "ARB_texture_env_combine: %d\n", glExtInfo.ARB_texture_env_combine );
    printf( "ARB_texture_env_crossbar: %d\n", glExtInfo.ARB_texture_env_crossbar );
    printf( "ARB_texture_border_clamp: %d\n", glExtInfo.ARB_texture_border_clamp );
    printf( "ARB_texture_cube_map: %d\n", glExtInfo.ARB_texture_cube_map );
    printf( "ARB_transpose_matrix: %d\n", glExtInfo.ARB_transpose_matrix );
    printf( "ARB_vertex_blend: %d\n", glExtInfo.ARB_vertex_blend );
    printf( "EXT_abgr: %d\n", glExtInfo.EXT_abgr );
    printf( "EXT_compiled_vertex_array: %d\n", glExtInfo.EXT_compiled_vertex_array );
    printf( "EXT_fog_coord: %d\n", glExtInfo.EXT_fog_coord );
    printf( "EXT_multi_draw_arrays: %d\n", glExtInfo.EXT_multi_draw_arrays );
    printf( "EXT_point_parameters: %d\n", glExtInfo.EXT_point_parameters );
    printf( "EXT_secondary_color: %d\n", glExtInfo.EXT_secondary_color );
    printf( "EXT_stencil_wrap: %d\n", glExtInfo.EXT_stencil_wrap );
    printf( "EXT_texture_filter_anisotropic: %d\n", glExtInfo.EXT_texture_filter_anisotropic );
    printf( "EXT_texture_lod_bias: %d\n", glExtInfo.EXT_texture_lod_bias );
    printf( "EXT_vertex_shader: %d\n", glExtInfo.EXT_vertex_shader );
    printf( "EXT_vertex_weighting: %d\n", glExtInfo.EXT_vertex_weighting );
    printf( "ATI_element_array: %d\n", glExtInfo.ATI_element_array );
    printf( "ATI_envmap_bumpmap: %d\n", glExtInfo.ATI_envmap_bumpmap );
    printf( "ATI_fragment_shader: %d\n", glExtInfo.ATI_fragment_shader );
    printf( "ATI_pn_triangles: %d\n", glExtInfo.ATI_pn_triangles );
    printf( "ATI_texture_mirror_once: %d\n", glExtInfo.ATI_texture_mirror_once );
    printf( "ATI_vertex_array_object: %d\n", glExtInfo.ATI_vertex_array_object );
    printf( "ATI_vertex_streams: %d\n", glExtInfo.ATI_vertex_streams );
    printf( "ATIX_point_sprites: %d\n", glExtInfo.ATIX_point_sprites );
    printf( "ATIX_texture_env_route: %d\n", glExtInfo.ATIX_texture_env_route );
    printf( "HP_occlusion_test: %d\n", glExtInfo.HP_occlusion_test );
    printf( "NV_blend_square: %d\n", glExtInfo.NV_blend_square );
    printf( "NV_copy_depth_to_color: %d\n", glExtInfo.NV_copy_depth_to_color );
    printf( "NV_evaluators: %d\n", glExtInfo.NV_evaluators );
    printf( "NV_fence: %d\n", glExtInfo.NV_fence );
    printf( "NV_fog_distance: %d\n", glExtInfo.NV_fog_distance );
    printf( "NV_light_max_exponent: %d\n", glExtInfo.NV_light_max_exponent );
    printf( "NV_vertex_program: %d\n", glExtInfo.NV_vertex_program );
    printf( "NV_packed_depth_stencil: %d\n", glExtInfo.NV_packed_depth_stencil );
    printf( "NV_register_combiners: %d\n", glExtInfo.NV_register_combiners );
    printf( "NV_register_combiners2: %d\n", glExtInfo.NV_register_combiners2 );
    printf( "NV_texgen_reflection: %d\n", glExtInfo.NV_texgen_reflection );
    printf( "NV_texture_env_combine4: %d\n", glExtInfo.NV_texture_env_combine4 );
    printf( "NV_texture_rectangle: %d\n", glExtInfo.NV_texture_rectangle );
    printf( "NV_texture_shader: %d\n", glExtInfo.NV_texture_shader );
    printf( "NV_texture_shader2: %d\n", glExtInfo.NV_texture_shader2 );
    printf( "NV_vertex_array_range: %d\n", glExtInfo.NV_vertex_array_range );
    printf( "NV_vertex_array_range2: %d\n", glExtInfo.NV_vertex_array_range2 );
    printf( "SGIS_generate_mipmap: %d\n", glExtInfo.SGIS_generate_mipmap );
    printf( "SGIX_shadow: %d\n", glExtInfo.SGIX_shadow );
    printf( "SGIX_depth_texture: %d\n", glExtInfo.SGIX_depth_texture );
    printf( "OpenGL12: %d\n", glExtInfo.OpenGL12 );
    printf( "OpenGL13: %d\n", glExtInfo.OpenGL13 );

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

