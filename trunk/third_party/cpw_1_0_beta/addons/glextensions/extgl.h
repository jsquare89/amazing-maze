/* 
    Copyright (c) 2001-2002 Lev Povalahev
  
    levp@gmx.net

    http://www.uni-karlsruhe.de/~uli2/

    Parts Copyright (C) 1998-2000 ATI Technologies Inc. 
*/
                
#ifndef __EXTGL_H__
#define __EXTGL_H__

/*-----------------------------------------*/
/*-----------------------------------------*/

#if defined(_WIN32) && !defined(APIENTRY)
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#endif

#include <GL/gl.h>

#ifndef APIENTRY
#define APIENTRY
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __PROTOTYPE__
#undef __PROTOTYPE__
#endif

#define GL_VERSION_1_2                              1
#define GL_VERSION_1_3                              1
#define GL_ARB_imaging                              1

/* 1.2 and 1.3 enumerants */

#define GL_RESCALE_NORMAL                                       0x803A
#define GL_CLAMP_TO_EDGE                                        0x812F
#define GL_MAX_ELEMENTS_VERTICES                                0x80E8
#define GL_MAX_ELEMENTS_INDICES                                 0x80E9
#define GL_BGR                                                  0x80E0
#define GL_BGRA                                                 0x80E1
#define GL_UNSIGNED_BYTE_3_3_2                                  0x8032
#define GL_UNSIGNED_BYTE_2_3_3_REV                              0x8362
#define GL_UNSIGNED_SHORT_5_6_5                                 0x8363
#define GL_UNSIGNED_SHORT_5_6_5_REV                             0x8364
#define GL_UNSIGNED_SHORT_4_4_4_4                               0x8033
#define GL_UNSIGNED_SHORT_4_4_4_4_REV                           0x8365
#define GL_UNSIGNED_SHORT_5_5_5_1                               0x8034
#define GL_UNSIGNED_SHORT_1_5_5_5_REV                           0x8366
#define GL_UNSIGNED_INT_8_8_8_8                                 0x8035
#define GL_UNSIGNED_INT_8_8_8_8_REV                             0x8367
#define GL_UNSIGNED_INT_10_10_10_2                              0x8036
#define GL_UNSIGNED_INT_2_10_10_10_REV                          0x8368
#define GL_LIGHT_MODEL_COLOR_CONTROL                            0x81F8
#define GL_SINGLE_COLOR                                         0x81F9
#define GL_SEPARATE_SPECULAR_COLOR                              0x81FA
#define GL_TEXTURE_MIN_LOD                                      0x813A
#define GL_TEXTURE_MAX_LOD                                      0x813B
#define GL_TEXTURE_BASE_LEVEL                                   0x813C
#define GL_TEXTURE_MAX_LEVEL                                    0x813D
#define GL_SMOOTH_POINT_SIZE_RANGE                              0x0B12
#define GL_SMOOTH_POINT_SIZE_GRANULARITY                        0x0B13
#define GL_SMOOTH_LINE_WIDTH_RANGE                              0x0B22
#define GL_SMOOTH_LINE_WIDTH_GRANULARITY                        0x0B23
#define GL_ALIASED_POINT_SIZE_RANGE                             0x846D
#define GL_ALIASED_LINE_WIDTH_RANGE                             0x846E
#define GL_PACK_SKIP_IMAGES                                     0x806B
#define GL_PACK_IMAGE_HEIGHT                                    0x806C
#define GL_UNPACK_SKIP_IMAGES                                   0x806D
#define GL_UNPACK_IMAGE_HEIGHT                                  0x806E
#define GL_TEXTURE_3D                                           0x806F
#define GL_PROXY_TEXTURE_3D                                     0x8070
#define GL_TEXTURE_DEPTH                                        0x8071
#define GL_TEXTURE_WRAP_R                                       0x8072
#define GL_MAX_3D_TEXTURE_SIZE                                  0x8073
#define GL_TEXTURE_BINDING_3D                                   0x806A

#define GL_COLOR_TABLE                                          0x80D0
#define GL_POST_CONVOLUTION_COLOR_TABLE                         0x80D1
#define GL_POST_COLOR_MATRIX_COLOR_TABLE                        0x80D2
#define GL_PROXY_COLOR_TABLE                                    0x80D3
#define GL_PROXY_POST_CONVOLUTION_COLOR_TABLE                   0x80D4
#define GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE                  0x80D5
#define GL_COLOR_TABLE_SCALE                                    0x80D6
#define GL_COLOR_TABLE_BIAS                                     0x80D7
#define GL_COLOR_TABLE_FORMAT                                   0x80D8
#define GL_COLOR_TABLE_WIDTH                                    0x80D9
#define GL_COLOR_TABLE_RED_SIZE                                 0x80DA
#define GL_COLOR_TABLE_GREEN_SIZE                               0x80DB
#define GL_COLOR_TABLE_BLUE_SIZE                                0x80DC
#define GL_COLOR_TABLE_ALPHA_SIZE                               0x80DD
#define GL_COLOR_TABLE_LUMINANCE_SIZE                           0x80DE
#define GL_COLOR_TABLE_INTENSITY_SIZE                           0x80DF

#define GL_CONVOLUTION_1D                                       0x8010
#define GL_CONVOLUTION_2D                                       0x8011
#define GL_SEPARABLE_2D                                         0x8012
#define GL_CONVOLUTION_BORDER_MODE                              0x8013
#define GL_CONVOLUTION_FILTER_SCALE                             0x8014
#define GL_CONVOLUTION_FILTER_BIAS                              0x8015
#define GL_REDUCE                                               0x8016
#define GL_CONVOLUTION_FORMAT                                   0x8017
#define GL_CONVOLUTION_WIDTH                                    0x8018
#define GL_CONVOLUTION_HEIGHT                                   0x8019
#define GL_MAX_CONVOLUTION_WIDTH                                0x801A
#define GL_MAX_CONVOLUTION_HEIGHT                               0x801B
#define GL_POST_CONVOLUTION_RED_SCALE                           0x801C
#define GL_POST_CONVOLUTION_GREEN_SCALE                         0x801D
#define GL_POST_CONVOLUTION_BLUE_SCALE                          0x801E
#define GL_POST_CONVOLUTION_ALPHA_SCALE                         0x801F
#define GL_POST_CONVOLUTION_RED_BIAS                            0x8020
#define GL_POST_CONVOLUTION_GREEN_BIAS                          0x8021
#define GL_POST_CONVOLUTION_BLUE_BIAS                           0x8022
#define GL_POST_CONVOLUTION_ALPHA_BIAS                          0x8023
#define GL_CONSTANT_BORDER                                      0x8151
#define GL_REPLICATE_BORDER                                     0x8153
#define GL_CONVOLUTION_BORDER_COLOR                             0x8154
#define GL_COLOR_MATRIX                                         0x80B1
#define GL_COLOR_MATRIX_STACK_DEPTH                             0x80B2
#define GL_MAX_COLOR_MATRIX_STACK_DEPTH                         0x80B3
#define GL_POST_COLOR_MATRIX_RED_SCALE                          0x80B4
#define GL_POST_COLOR_MATRIX_GREEN_SCALE                        0x80B5
#define GL_POST_COLOR_MATRIX_BLUE_SCALE                         0x80B6
#define GL_POST_COLOR_MATRIX_ALPHA_SCALE                        0x80B7
#define GL_POST_COLOR_MATRIX_RED_BIAS                           0x80B8
#define GL_POST_COLOR_MATRIX_GREEN_BIAS                         0x80B9
#define GL_POST_COLOR_MATRIX_BLUE_BIAS                          0x80BA
#define GL_POST_COLOR_MATRIX_ALPHA_BIAS                         0x80BB
#define GL_HISTOGRAM                                            0x8024
#define GL_PROXY_HISTOGRAM                                      0x8025
#define GL_HISTOGRAM_WIDTH                                      0x8026
#define GL_HISTOGRAM_FORMAT                                     0x8027
#define GL_HISTOGRAM_RED_SIZE                                   0x8028
#define GL_HISTOGRAM_GREEN_SIZE                                 0x8029
#define GL_HISTOGRAM_BLUE_SIZE                                  0x802A
#define GL_HISTOGRAM_ALPHA_SIZE                                 0x802B
#define GL_HISTOGRAM_LUMINANCE_SIZE                             0x802C
#define GL_HISTOGRAM_SINK                                       0x802D
#define GL_MINMAX                                               0x802E
#define GL_MINMAX_FORMAT                                        0x802F
#define GL_MINMAX_SINK                                          0x8030
#define GL_TABLE_TOO_LARGE                                      0x8031
#define GL_BLEND_EQUATION                                       0x8009
#define GL_MIN                                                  0x8007
#define GL_MAX                                                  0x8008
#define GL_FUNC_ADD                                             0x8006
#define GL_FUNC_SUBTRACT                                        0x800A
#define GL_FUNC_REVERSE_SUBTRACT                                0x800B
#define GL_BLEND_COLOR                                          0x8005

#define GL_TEXTURE0                                             0x84C0
#define GL_TEXTURE1                                             0x84C1
#define GL_TEXTURE2                                             0x84C2
#define GL_TEXTURE3                                             0x84C3
#define GL_TEXTURE4                                             0x84C4
#define GL_TEXTURE5                                             0x84C5
#define GL_TEXTURE6                                             0x84C6
#define GL_TEXTURE7                                             0x84C7
#define GL_TEXTURE8                                             0x84C8
#define GL_TEXTURE9                                             0x84C9
#define GL_TEXTURE10                                            0x84CA
#define GL_TEXTURE11                                            0x84CB
#define GL_TEXTURE12                                            0x84CC
#define GL_TEXTURE13                                            0x84CD
#define GL_TEXTURE14                                            0x84CE
#define GL_TEXTURE15                                            0x84CF
#define GL_TEXTURE16                                            0x84D0
#define GL_TEXTURE17                                            0x84D1
#define GL_TEXTURE18                                            0x84D2
#define GL_TEXTURE19                                            0x84D3
#define GL_TEXTURE20                                            0x84D4
#define GL_TEXTURE21                                            0x84D5
#define GL_TEXTURE22                                            0x84D6
#define GL_TEXTURE23                                            0x84D7
#define GL_TEXTURE24                                            0x84D8
#define GL_TEXTURE25                                            0x84D9
#define GL_TEXTURE26                                            0x84DA
#define GL_TEXTURE27                                            0x84DB
#define GL_TEXTURE28                                            0x84DC
#define GL_TEXTURE29                                            0x84DD
#define GL_TEXTURE30                                            0x84DE
#define GL_TEXTURE31                                            0x84DF
#define GL_ACTIVE_TEXTURE                                       0x84E0
#define GL_CLIENT_ACTIVE_TEXTURE                                0x84E1
#define GL_MAX_TEXTURE_UNITS                                    0x84E2

#define GL_NORMAL_MAP                                           0x8511
#define GL_REFLECTION_MAP                                       0x8512
#define GL_TEXTURE_CUBE_MAP                                     0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP                             0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X                          0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X                          0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y                          0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y                          0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z                          0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z                          0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP                               0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE                            0x851C

#define GL_COMPRESSED_ALPHA                                     0x84E9
#define GL_COMPRESSED_LUMINANCE                                 0x84EA
#define GL_COMPRESSED_LUMINANCE_ALPHA                           0x84EB
#define GL_COMPRESSED_INTENSITY                                 0x84EC
#define GL_COMPRESSED_RGB                                       0x84ED
#define GL_COMPRESSED_RGBA                                      0x84EE
#define GL_TEXTURE_COMPRESSION_HINT                             0x84EF
#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE                        0x86A0
#define GL_TEXTURE_COMPRESSED                                   0x86A1
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS                       0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS                           0x86A3

#define GL_MULTISAMPLE                                          0x809D
#define GL_SAMPLE_ALPHA_TO_COVERAGE                             0x809E
#define GL_SAMPLE_ALPHA_TO_ONE                                  0x809F
#define GL_SAMPLE_COVERAGE                                      0x80A0
#define GL_SAMPLE_BUFFERS                                       0x80A8
#define GL_SAMPLES                                              0x80A9
#define GL_SAMPLE_COVERAGE_VALUE                                0x80AA
#define GL_SAMPLE_COVERAGE_INVERT                               0x80AB
#define GL_MULTISAMPLE_BIT                                      0x20000000

#define GL_TRANSPOSE_MODELVIEW_MATRIX                           0x84E3
#define GL_TRANSPOSE_PROJECTION_MATRIX                          0x84E4
#define GL_TRANSPOSE_TEXTURE_MATRIX                             0x84E5
#define GL_TRANSPOSE_COLOR_MATRIX                               0x84E6

#define GL_COMBINE                                              0x8570
#define GL_COMBINE_RGB                                          0x8571
#define GL_COMBINE_ALPHA                                        0x8572
#define GL_SOURCE0_RGB                                          0x8580
#define GL_SOURCE1_RGB                                          0x8581
#define GL_SOURCE2_RGB                                          0x8582
#define GL_SOURCE0_ALPHA                                        0x8588
#define GL_SOURCE1_ALPHA                                        0x8589
#define GL_SOURCE2_ALPHA                                        0x858A
#define GL_OPERAND0_RGB                                         0x8590
#define GL_OPERAND1_RGB                                         0x8591
#define GL_OPERAND2_RGB                                         0x8592
#define GL_OPERAND0_ALPHA                                       0x8598
#define GL_OPERAND1_ALPHA                                       0x8599
#define GL_OPERAND2_ALPHA                                       0x859A
#define GL_RGB_SCALE                                            0x8573
#define GL_ADD_SIGNED                                           0x8574
#define GL_INTERPOLATE                                          0x8575
#define GL_SUBTRACT                                             0x84E7
#define GL_CONSTANT                                             0x8576
#define GL_PRIMARY_COLOR                                        0x8577
#define GL_PREVIOUS                                             0x8578

#define GL_DOT3_RGB                                             0x86AE
#define GL_DOT3_RGBA                                            0x86AF

#define GL_CLAMP_TO_BORDER                                      0x812D


/* 1.2 functions */

#ifdef __PROTOTYPE__

extern void APIENTRY glDrawRangeElements( GLenum mode, GLuint start,
                    GLuint end, GLsizei count, GLenum type, const GLvoid *indices );

extern void APIENTRY glTexImage3D( GLenum target, GLint level,
                                      GLint internalFormat,
                                      GLsizei width, GLsizei height,
                                      GLsizei depth, GLint border,
                                      GLenum format, GLenum type,
                                      const GLvoid *pixels );

extern void APIENTRY glTexSubImage3D( GLenum target, GLint level,
                                         GLint xoffset, GLint yoffset,
                                         GLint zoffset, GLsizei width,
                                         GLsizei height, GLsizei depth,
                                         GLenum format,
                                         GLenum type, const GLvoid *pixels);

extern void APIENTRY glCopyTexSubImage3D( GLenum target, GLint level,
                                             GLint xoffset, GLint yoffset,
                                             GLint zoffset, GLint x,
                                             GLint y, GLsizei width,
                                             GLsizei height );


/* 1.2 imaging extension functions */

extern void APIENTRY glColorTable( GLenum target, GLenum internalformat,
                                    GLsizei width, GLenum format,
                                    GLenum type, const GLvoid *table );

extern void APIENTRY glColorSubTable( GLenum target, GLsizei start, GLsizei count,
                                       GLenum format, GLenum type,
                                       const GLvoid *data );

extern void APIENTRY glColorTableParameteriv(GLenum target, GLenum pname,
                                              const GLint *params);

extern void APIENTRY glColorTableParameterfv(GLenum target, GLenum pname,
                                              const GLfloat *params);

extern void APIENTRY glCopyColorSubTable( GLenum target, GLsizei start,
                                           GLint x, GLint y, GLsizei width );

extern void APIENTRY glCopyColorTable( GLenum target, GLenum internalformat,
                                        GLint x, GLint y, GLsizei width );

extern void APIENTRY glGetColorTable( GLenum target, GLenum format,
                                       GLenum type, GLvoid *table );

extern void APIENTRY glGetColorTableParameterfv( GLenum target, GLenum pname,
                                                  GLfloat *params );

extern void APIENTRY glGetColorTableParameteriv( GLenum target, GLenum pname,
                                                  GLint *params );

extern void APIENTRY glBlendEquation( GLenum mode );

extern void APIENTRY glBlendColor( GLclampf red, GLclampf green,
                                    GLclampf blue, GLclampf alpha );

extern void APIENTRY glHistogram( GLenum target, GLsizei width,
                                   GLenum internalformat, GLboolean sink );

extern void APIENTRY glResetHistogram( GLenum target );

extern void APIENTRY glGetHistogram( GLenum target, GLboolean reset,
                                      GLenum format, GLenum type,
                                      GLvoid *values );

extern void APIENTRY glGetHistogramParameterfv( GLenum target, GLenum pname,
                                                 GLfloat *params );

extern void APIENTRY glGetHistogramParameteriv( GLenum target, GLenum pname,
                                                 GLint *params );

extern void APIENTRY glMinmax( GLenum target, GLenum internalformat,
                                GLboolean sink );

extern void APIENTRY glResetMinmax( GLenum target );

extern void APIENTRY glGetMinmax( GLenum target, GLboolean reset,
                                   GLenum format, GLenum types,
                                   GLvoid *values );

extern void APIENTRY glGetMinmaxParameterfv( GLenum target, GLenum pname,
                                              GLfloat *params );

extern void APIENTRY glGetMinmaxParameteriv( GLenum target, GLenum pname,
                                              GLint *params );

extern void APIENTRY glConvolutionFilter1D( GLenum target,
        GLenum internalformat, GLsizei width, GLenum format, GLenum type,
        const GLvoid *image );

extern void APIENTRY glConvolutionFilter2D( GLenum target,
        GLenum internalformat, GLsizei width, GLsizei height, GLenum format,
        GLenum type, const GLvoid *image );

extern void APIENTRY glConvolutionParameterf( GLenum target, GLenum pname,
        GLfloat params );

extern void APIENTRY glConvolutionParameterfv( GLenum target, GLenum pname,
        const GLfloat *params );

extern void APIENTRY glConvolutionParameteri( GLenum target, GLenum pname,
        GLint params );

extern void APIENTRY glConvolutionParameteriv( GLenum target, GLenum pname,
        const GLint *params );

extern void APIENTRY glCopyConvolutionFilter1D( GLenum target,
        GLenum internalformat, GLint x, GLint y, GLsizei width );

extern void APIENTRY glCopyConvolutionFilter2D( GLenum target,
        GLenum internalformat, GLint x, GLint y, GLsizei width,
        GLsizei height);

extern void APIENTRY glGetConvolutionFilter( GLenum target, GLenum format,
        GLenum type, GLvoid *image );

extern void APIENTRY glGetConvolutionParameterfv( GLenum target, GLenum pname,
        GLfloat *params );

extern void APIENTRY glGetConvolutionParameteriv( GLenum target, GLenum pname,
        GLint *params );

extern void APIENTRY glSeparableFilter2D( GLenum target,
        GLenum internalformat, GLsizei width, GLsizei height, GLenum format,
        GLenum type, const GLvoid *row, const GLvoid *column );

extern void APIENTRY glGetSeparableFilter( GLenum target, GLenum format,
        GLenum type, GLvoid *row, GLvoid *column, GLvoid *span );

/* 1.3 functions */

extern void APIENTRY glActiveTexture( GLenum texture );

extern void APIENTRY glClientActiveTexture( GLenum texture );

extern void APIENTRY glCompressedTexImage1D( GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data );

extern void APIENTRY glCompressedTexImage2D( GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data );

extern void APIENTRY glCompressedTexImage3D( GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data );

extern void APIENTRY glCompressedTexSubImage1D( GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data );

extern void APIENTRY glCompressedTexSubImage2D( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data );

extern void APIENTRY glCompressedTexSubImage3D( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data );

extern void APIENTRY glGetCompressedTexImage( GLenum target, GLint lod, GLvoid *img );

extern void APIENTRY glMultiTexCoord1d( GLenum target, GLdouble s );

extern void APIENTRY glMultiTexCoord1dv( GLenum target, const GLdouble *v );

extern void APIENTRY glMultiTexCoord1f( GLenum target, GLfloat s );

extern void APIENTRY glMultiTexCoord1fv( GLenum target, const GLfloat *v );

extern void APIENTRY glMultiTexCoord1i( GLenum target, GLint s );

extern void APIENTRY glMultiTexCoord1iv( GLenum target, const GLint *v );

extern void APIENTRY glMultiTexCoord1s( GLenum target, GLshort s );

extern void APIENTRY glMultiTexCoord1sv( GLenum target, const GLshort *v );

extern void APIENTRY glMultiTexCoord2d( GLenum target, GLdouble s, GLdouble t );

extern void APIENTRY glMultiTexCoord2dv( GLenum target, const GLdouble *v );

extern void APIENTRY glMultiTexCoord2f( GLenum target, GLfloat s, GLfloat t );

extern void APIENTRY glMultiTexCoord2fv( GLenum target, const GLfloat *v );

extern void APIENTRY glMultiTexCoord2i( GLenum target, GLint s, GLint t );

extern void APIENTRY glMultiTexCoord2iv( GLenum target, const GLint *v );

extern void APIENTRY glMultiTexCoord2s( GLenum target, GLshort s, GLshort t );

extern void APIENTRY glMultiTexCoord2sv( GLenum target, const GLshort *v );

extern void APIENTRY glMultiTexCoord3d( GLenum target, GLdouble s, GLdouble t, GLdouble r );

extern void APIENTRY glMultiTexCoord3dv( GLenum target, const GLdouble *v );

extern void APIENTRY glMultiTexCoord3f( GLenum target, GLfloat s, GLfloat t, GLfloat r );

extern void APIENTRY glMultiTexCoord3fv( GLenum target, const GLfloat *v );

extern void APIENTRY glMultiTexCoord3i( GLenum target, GLint s, GLint t, GLint r );

extern void APIENTRY glMultiTexCoord3iv( GLenum target, const GLint *v );

extern void APIENTRY glMultiTexCoord3s( GLenum target, GLshort s, GLshort t, GLshort r );

extern void APIENTRY glMultiTexCoord3sv( GLenum target, const GLshort *v );

extern void APIENTRY glMultiTexCoord4d( GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q );

extern void APIENTRY glMultiTexCoord4dv( GLenum target, const GLdouble *v );

extern void APIENTRY glMultiTexCoord4f( GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q );

extern void APIENTRY glMultiTexCoord4fv( GLenum target, const GLfloat *v );

extern void APIENTRY glMultiTexCoord4i( GLenum target, GLint s, GLint t, GLint r, GLint q );

extern void APIENTRY glMultiTexCoord4iv( GLenum target, const GLint *v );

extern void APIENTRY glMultiTexCoord4s( GLenum target, GLshort s, GLshort t, GLshort r, GLshort q );

extern void APIENTRY glMultiTexCoord4sv( GLenum target, const GLshort *v );


extern void APIENTRY glLoadTransposeMatrixd( const GLdouble m[16] );

extern void APIENTRY glLoadTransposeMatrixf( const GLfloat m[16] );

extern void APIENTRY glMultTransposeMatrixd( const GLdouble m[16] );

extern void APIENTRY glMultTransposeMatrixf( const GLfloat m[16] );

extern void APIENTRY glSampleCoverage( GLclampf value, GLboolean invert );

#endif /* __PROTOTYPE__ */

/* 1.2 functions */

typedef void (APIENTRY * PFNGLBLENDCOLORPROC) (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
typedef void (APIENTRY * PFNGLBLENDEQUATIONPROC) (GLenum mode);
typedef void (APIENTRY * PFNGLDRAWRANGEELEMENTSPROC) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices);
typedef void (APIENTRY * PFNGLCOLORTABLEPROC) (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *table);
typedef void (APIENTRY * PFNGLCOLORTABLEPARAMETERFVPROC) (GLenum target, GLenum pname, const GLfloat *params);
typedef void (APIENTRY * PFNGLCOLORTABLEPARAMETERIVPROC) (GLenum target, GLenum pname, const GLint *params);
typedef void (APIENTRY * PFNGLCOPYCOLORTABLEPROC) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
typedef void (APIENTRY * PFNGLGETCOLORTABLEPROC) (GLenum target, GLenum format, GLenum type, GLvoid *table);
typedef void (APIENTRY * PFNGLGETCOLORTABLEPARAMETERFVPROC) (GLenum target, GLenum pname, GLfloat *params);
typedef void (APIENTRY * PFNGLGETCOLORTABLEPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRY * PFNGLCOLORSUBTABLEPROC) (GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid *data);
typedef void (APIENTRY * PFNGLCOPYCOLORSUBTABLEPROC) (GLenum target, GLsizei start, GLint x, GLint y, GLsizei width);
typedef void (APIENTRY * PFNGLCONVOLUTIONFILTER1DPROC) (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *image);
typedef void (APIENTRY * PFNGLCONVOLUTIONFILTER2DPROC) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *image);
typedef void (APIENTRY * PFNGLCONVOLUTIONPARAMETERFPROC) (GLenum target, GLenum pname, GLfloat params);
typedef void (APIENTRY * PFNGLCONVOLUTIONPARAMETERFVPROC) (GLenum target, GLenum pname, const GLfloat *params);
typedef void (APIENTRY * PFNGLCONVOLUTIONPARAMETERIPROC) (GLenum target, GLenum pname, GLint params);
typedef void (APIENTRY * PFNGLCONVOLUTIONPARAMETERIVPROC) (GLenum target, GLenum pname, const GLint *params);
typedef void (APIENTRY * PFNGLCOPYCONVOLUTIONFILTER1DPROC) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width);
typedef void (APIENTRY * PFNGLCOPYCONVOLUTIONFILTER2DPROC) (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRY * PFNGLGETCONVOLUTIONFILTERPROC) (GLenum target, GLenum format, GLenum type, GLvoid *image);
typedef void (APIENTRY * PFNGLGETCONVOLUTIONPARAMETERFVPROC) (GLenum target, GLenum pname, GLfloat *params);
typedef void (APIENTRY * PFNGLGETCONVOLUTIONPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRY * PFNGLGETSEPARABLEFILTERPROC) (GLenum target, GLenum format, GLenum type, GLvoid *row, GLvoid *column, GLvoid *span);
typedef void (APIENTRY * PFNGLSEPARABLEFILTER2DPROC) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *row, const GLvoid *column);
typedef void (APIENTRY * PFNGLGETHISTOGRAMPROC) (GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid *values);
typedef void (APIENTRY * PFNGLGETHISTOGRAMPARAMETERFVPROC) (GLenum target, GLenum pname, GLfloat *params);
typedef void (APIENTRY * PFNGLGETHISTOGRAMPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRY * PFNGLGETMINMAXPROC) (GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid *values);
typedef void (APIENTRY * PFNGLGETMINMAXPARAMETERFVPROC) (GLenum target, GLenum pname, GLfloat *params);
typedef void (APIENTRY * PFNGLGETMINMAXPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRY * PFNGLHISTOGRAMPROC) (GLenum target, GLsizei width, GLenum internalformat, GLboolean sink);
typedef void (APIENTRY * PFNGLMINMAXPROC) (GLenum target, GLenum internalformat, GLboolean sink);
typedef void (APIENTRY * PFNGLRESETHISTOGRAMPROC) (GLenum target);
typedef void (APIENTRY * PFNGLRESETMINMAXPROC) (GLenum target);
typedef void (APIENTRY * PFNGLTEXIMAGE3DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (APIENTRY * PFNGLTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels);
typedef void (APIENTRY * PFNGLCOPYTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);

/* 1.3 functions */

typedef void (APIENTRY * PFNGLACTIVETEXTUREPROC) (GLenum texture);
typedef void (APIENTRY * PFNGLCLIENTACTIVETEXTUREPROC) (GLenum texture);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1DPROC) (GLenum target, GLdouble s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1DVPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1FPROC) (GLenum target, GLfloat s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1FVPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1IPROC) (GLenum target, GLint s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1IVPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1SPROC) (GLenum target, GLshort s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1SVPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2DPROC) (GLenum target, GLdouble s, GLdouble t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2DVPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2FPROC) (GLenum target, GLfloat s, GLfloat t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2FVPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2IPROC) (GLenum target, GLint s, GLint t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2IVPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2SPROC) (GLenum target, GLshort s, GLshort t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2SVPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3DPROC) (GLenum target, GLdouble s, GLdouble t, GLdouble r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3DVPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3FPROC) (GLenum target, GLfloat s, GLfloat t, GLfloat r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3FVPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3IPROC) (GLenum target, GLint s, GLint t, GLint r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3IVPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3SPROC) (GLenum target, GLshort s, GLshort t, GLshort r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3SVPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4DPROC) (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4DVPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4FPROC) (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4FVPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4IPROC) (GLenum target, GLint s, GLint t, GLint r, GLint q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4IVPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4SPROC) (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4SVPROC) (GLenum target, const GLshort *v);

typedef void (APIENTRY * PFNGLLOADTRANSPOSEMATRIXFPROC) (const GLfloat *m);
typedef void (APIENTRY * PFNGLLOADTRANSPOSEMATRIXDPROC) (const GLdouble *m);
typedef void (APIENTRY * PFNGLMULTTRANSPOSEMATRIXFPROC) (const GLfloat *m);
typedef void (APIENTRY * PFNGLMULTTRANSPOSEMATRIXDPROC) (const GLdouble *m);

typedef void (APIENTRY * PFNGLCOMPRESSEDTEXIMAGE3DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * PFNGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * PFNGLCOMPRESSEDTEXIMAGE1DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * PFNGLGETCOMPRESSEDTEXIMAGEPROC) (GLenum target, GLint level, GLvoid *img);

typedef void (APIENTRY * PFNGLSAMPLECOVERAGEPROC) (GLclampf value, GLboolean invert);
typedef void (APIENTRY * PFNGLSAMPLEPASSPROC) (GLenum pass);

/*-------------------------------------------------------------------*/
/*------------EXTENSIONS---------------------------------------------*/
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
/*------------ARB_MULTITEXTURE---------------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_ARB_multitexture
#define GL_ARB_multitexture 1
#define GL_TEXTURE0_ARB                                         0x84C0
#define GL_TEXTURE1_ARB                                         0x84C1
#define GL_TEXTURE2_ARB                                         0x84C2
#define GL_TEXTURE3_ARB                                         0x84C3
#define GL_TEXTURE4_ARB                                         0x84C4
#define GL_TEXTURE5_ARB                                         0x84C5
#define GL_TEXTURE6_ARB                                         0x84C6
#define GL_TEXTURE7_ARB                                         0x84C7
#define GL_TEXTURE8_ARB                                         0x84C8
#define GL_TEXTURE9_ARB                                         0x84C9
#define GL_TEXTURE10_ARB                                        0x84CA
#define GL_TEXTURE11_ARB                                        0x84CB
#define GL_TEXTURE12_ARB                                        0x84CC
#define GL_TEXTURE13_ARB                                        0x84CD
#define GL_TEXTURE14_ARB                                        0x84CE
#define GL_TEXTURE15_ARB                                        0x84CF
#define GL_TEXTURE16_ARB                                        0x84D0
#define GL_TEXTURE17_ARB                                        0x84D1
#define GL_TEXTURE18_ARB                                        0x84D2
#define GL_TEXTURE19_ARB                                        0x84D3
#define GL_TEXTURE20_ARB                                        0x84D4
#define GL_TEXTURE21_ARB                                        0x84D5
#define GL_TEXTURE22_ARB                                        0x84D6
#define GL_TEXTURE23_ARB                                        0x84D7
#define GL_TEXTURE24_ARB                                        0x84D8
#define GL_TEXTURE25_ARB                                        0x84D9
#define GL_TEXTURE26_ARB                                        0x84DA
#define GL_TEXTURE27_ARB                                        0x84DB
#define GL_TEXTURE28_ARB                                        0x84DC
#define GL_TEXTURE29_ARB                                        0x84DD
#define GL_TEXTURE30_ARB                                        0x84DE
#define GL_TEXTURE31_ARB                                        0x84DF
#define GL_ACTIVE_TEXTURE_ARB                                   0x84E0
#define GL_CLIENT_ACTIVE_TEXTURE_ARB                            0x84E1
#define GL_MAX_TEXTURE_UNITS_ARB                                0x84E2

#ifdef __PROTOTYPE__

extern void APIENTRY glActiveTextureARB (GLenum texture);
extern void APIENTRY glClientActiveTextureARB(GLenum texture);
extern void APIENTRY glMultiTexCoord1dARB (GLenum target, GLdouble s);
extern void APIENTRY glMultiTexCoord1dvARB (GLenum target, const GLdouble *v);
extern void APIENTRY glMultiTexCoord1fARB (GLenum target, GLfloat s);
extern void APIENTRY glMultiTexCoord1fvARB (GLenum target, const GLfloat *v);
extern void APIENTRY glMultiTexCoord1iARB (GLenum target, GLint s);
extern void APIENTRY glMultiTexCoord1ivARB (GLenum target, const GLint *v);
extern void APIENTRY glMultiTexCoord1sARB (GLenum target, GLshort s);
extern void APIENTRY glMultiTexCoord1svARB (GLenum target, const GLshort *v);
extern void APIENTRY glMultiTexCoord2dARB (GLenum target, GLdouble s, GLdouble t);
extern void APIENTRY glMultiTexCoord2dvARB (GLenum target, const GLdouble *v);
extern void APIENTRY glMultiTexCoord2fARB (GLenum target, GLfloat s, GLfloat t);
extern void APIENTRY glMultiTexCoord2fvARB (GLenum target, const GLfloat *v);
extern void APIENTRY glMultiTexCoord2iARB (GLenum target, GLint s, GLint t);
extern void APIENTRY glMultiTexCoord2ivARB (GLenum target, const GLint *v);
extern void APIENTRY glMultiTexCoord2sARB (GLenum target, GLshort s, GLshort t);
extern void APIENTRY glMultiTexCoord2svARB (GLenum target, const GLshort *v);
extern void APIENTRY glMultiTexCoord3dARB (GLenum target, GLdouble s, GLdouble t, GLdouble r);
extern void APIENTRY glMultiTexCoord3dvARB (GLenum target, const GLdouble *v);
extern void APIENTRY glMultiTexCoord3fARB (GLenum target, GLfloat s, GLfloat t, GLfloat r);
extern void APIENTRY glMultiTexCoord3fvARB (GLenum target, const GLfloat *v);
extern void APIENTRY glMultiTexCoord3iARB (GLenum target, GLint s, GLint t, GLint r);
extern void APIENTRY glMultiTexCoord3ivARB (GLenum target, const GLint *v);
extern void APIENTRY glMultiTexCoord3sARB (GLenum target, GLshort s, GLshort t, GLshort r);
extern void APIENTRY glMultiTexCoord3svARB (GLenum target, const GLshort *v);
extern void APIENTRY glMultiTexCoord4dARB (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
extern void APIENTRY glMultiTexCoord4dvARB (GLenum target, const GLdouble *v);
extern void APIENTRY glMultiTexCoord4fARB (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
extern void APIENTRY glMultiTexCoord4fvARB (GLenum target, const GLfloat *v);
extern void APIENTRY glMultiTexCoord4iARB (GLenum target, GLint s, GLint t, GLint r, GLint q);
extern void APIENTRY glMultiTexCoord4ivARB (GLenum target, const GLint *v);
extern void APIENTRY glMultiTexCoord4sARB (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
extern void APIENTRY glMultiTexCoord4svARB (GLenum target, const GLshort *v);

#endif /* __PROTOTYPE__ */

typedef void (APIENTRY * PFNGLACTIVETEXTUREARBPROC) (GLenum texture);
typedef void (APIENTRY * PFNGLCLIENTACTIVETEXTUREARBPROC) (GLenum texture);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1DARBPROC) (GLenum target, GLdouble s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1DVARBPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1FARBPROC) (GLenum target, GLfloat s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1FVARBPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1IARBPROC) (GLenum target, GLint s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1IVARBPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1SARBPROC) (GLenum target, GLshort s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1SVARBPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2DARBPROC) (GLenum target, GLdouble s, GLdouble t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2DVARBPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2FARBPROC) (GLenum target, GLfloat s, GLfloat t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2FVARBPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2IARBPROC) (GLenum target, GLint s, GLint t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2IVARBPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2SARBPROC) (GLenum target, GLshort s, GLshort t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2SVARBPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3DARBPROC) (GLenum target, GLdouble s, GLdouble t, GLdouble r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3DVARBPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3FARBPROC) (GLenum target, GLfloat s, GLfloat t, GLfloat r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3FVARBPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3IARBPROC) (GLenum target, GLint s, GLint t, GLint r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3IVARBPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3SARBPROC) (GLenum target, GLshort s, GLshort t, GLshort r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3SVARBPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4DARBPROC) (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4DVARBPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4FARBPROC) (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4FVARBPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4IARBPROC) (GLenum target, GLint s, GLint t, GLint r, GLint q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4IVARBPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4SARBPROC) (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4SVARBPROC) (GLenum target, const GLshort *v);

#endif /* GL_ARB_multitexture */

/*-------------------------------------------------------------------*/
/*------------ARB_TRANSPOSE_MATRIX-----------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_ARB_transpose_matrix
#define GL_ARB_transpose_matrix 1
#define GL_TRANSPOSE_MODELVIEW_MATRIX_ARB                       0x84E3
#define GL_TRANSPOSE_PROJECTION_MATRIX_ARB                      0x84E4
#define GL_TRANSPOSE_TEXTURE_MATRIX_ARB                         0x84E5
#define GL_TRANSPOSE_COLOR_MATRIX_ARB                           0x84E6

#ifdef __PROTOTYPE__

extern void APIENTRY glLoadTransposeMatrixfARB (const GLfloat *m);
extern void APIENTRY glLoadTransposeMatrixdARB (const GLdouble *m);
extern void APIENTRY glMultTransposeMatrixfARB (const GLfloat *m);
extern void APIENTRY glMultTransposeMatrixdARB (const GLdouble *m);

#endif /* __PROTOTYPE__ */                                

typedef void (APIENTRY * PFNGLLOADTRANSPOSEMATRIXFARBPROC) (const GLfloat *m);
typedef void (APIENTRY * PFNGLLOADTRANSPOSEMATRIXDARBPROC) (const GLdouble *m);
typedef void (APIENTRY * PFNGLMULTTRANSPOSEMATRIXFARBPROC) (const GLfloat *m);
typedef void (APIENTRY * PFNGLMULTTRANSPOSEMATRIXDARBPROC) (const GLdouble *m);

#endif /* GL_ARB_transpose_matrix */

/*-------------------------------------------------------------------*/
/*------------ARB_TEXTURE_COMPRESSION--------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_ARB_texture_compression
#define GL_ARB_texture_compression 1

#define GL_COMPRESSED_ALPHA_ARB                                 0x84E9
#define GL_COMPRESSED_LUMINANCE_ARB                             0x84EA
#define GL_COMPRESSED_LUMINANCE_ALPHA_ARB                       0x84EB
#define GL_COMPRESSED_INTENSITY_ARB                             0x84EC
#define GL_COMPRESSED_RGB_ARB                                   0x84ED
#define GL_COMPRESSED_RGBA_ARB                                  0x84EE
#define GL_TEXTURE_COMPRESSION_HINT_ARB                         0x84EF
#define GL_TEXTURE_IMAGE_SIZE_ARB                               0x86A0
#define GL_TEXTURE_COMPRESSED_ARB                               0x86A1
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB                   0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS_ARB                       0x86A3

#ifdef __PROTOTYPE__

extern void APIENTRY glCompressedTexImage3DARB  (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data);
extern void APIENTRY glCompressedTexImage2DARB (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data);
extern void APIENTRY glCompressedTexImage1DARB (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data);
extern void APIENTRY glCompressedTexSubImage3DARB (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data);
extern void APIENTRY glCompressedTexSubImage2DARB (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data);
extern void APIENTRY glCompressedTexSubImage1DARB (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data);
extern void APIENTRY glGetCompressedTexImageARB (GLenum target, GLint level, GLvoid *img);

#endif /* __PROTOTYPE__ */

typedef void (APIENTRY * PFNGLCOMPRESSEDTEXIMAGE3DARBPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * PFNGLCOMPRESSEDTEXIMAGE2DARBPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * PFNGLCOMPRESSEDTEXIMAGE1DARBPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * PFNGLCOMPRESSEDTEXSUBIMAGE3DARBPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * PFNGLCOMPRESSEDTEXSUBIMAGE1DARBPROC) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRY * PFNGLGETCOMPRESSEDTEXIMAGEARBPROC) (GLenum target, GLint level, GLvoid *img);

#endif /* GL_ARB_texture_compression */

/*-------------------------------------------------------------------*/
/*------------ARB_CUBE_MAP-------------------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_ARB_texture_cube_map
#define GL_ARB_texture_cube_map 1

#define GL_NORMAL_MAP_ARB                                       0x8511
#define GL_REFLECTION_MAP_ARB                                   0x8512
#define GL_TEXTURE_CUBE_MAP_ARB                                 0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP_ARB                         0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB                      0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB                      0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB                      0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB                      0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB                      0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB                      0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP_ARB                           0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE_ARB                        0x851C

#endif /* GL_ARB_texture_cube_map */

/*-------------------------------------------------------------------*/
/*------------SGIX_SHADOW--------------------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_SGIX_shadow
#define GL_SGIX_shadow 1

#define GL_TEXTURE_COMPARE_SGIX                                 0x819A
#define GL_TEXTURE_COMPARE_OPERATOR_SGIX                        0x819B
#define GL_TEXTURE_LEQUAL_R_SGIX                                0x819C
#define GL_TEXTURE_GEQUAL_R_SGIX                                0x819D

#endif /* GL_SGIX_shadow */

/*-------------------------------------------------------------------*/
/*------------SGIX_DEPTH_TEXTURE-------------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_SGIX_depth_texture
#define GL_SGIX_depth_texture 1

#define GL_DEPTH_COMPONENT16_SGIX                               0x81A5
#define GL_DEPTH_COMPONENT24_SGIX                               0x81A6
#define GL_DEPTH_COMPONENT32_SGIX                               0x81A7

#endif /* GL_SGIX_depth_texture */

/*-------------------------------------------------------------------*/
/*------------EXT_COMPILED_VERTEX_ARRAY------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_EXT_compiled_vertex_array
#define GL_EXT_compiled_vertex_array 1

#define GL_ARRAY_ELEMENT_LOCK_FIRST_EXT                         0x81A8
#define GL_ARRAY_ELEMENT_LOCK_COUNT_EXT                         0x81A9

#ifdef __PROTOTYPE__

extern void APIENTRY glLockArraysEXT(GLint first, GLsizei count);
extern void APIENTRY glUnlockArraysEXT();

#endif /* __PROTOTYPE__ */

typedef void (APIENTRY * PFNGLLOCKARRAYSEXTPROC) (GLint first, GLsizei count);
typedef void (APIENTRY * PFNGLUNLOCKARRAYSEXTPROC) (void);

#endif /* GL_EXT_compiled_vertex_array */

/*-------------------------------------------------------------------*/
/*------------ARB_TEXTURE_ENV_COMBINE--------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_ARB_texture_env_combine
#define GL_ARB_texture_env_combine 1

#define GL_COMBINE_ARB                                          0x8570
#define GL_COMBINE_RGB_ARB                                      0x8571
#define GL_COMBINE_ALPHA_ARB                                    0x8572
#define GL_RGB_SCALE_ARB                                        0x8573
#define GL_ADD_SIGNED_ARB                                       0x8574
#define GL_INTERPOLATE_ARB                                      0x8575
#define GL_CONSTANT_ARB                                         0x8576
#define GL_PRIMARY_COLOR_ARB                                    0x8577
#define GL_PREVIOUS_ARB                                         0x8578
#define GL_SOURCE0_RGB_ARB                                      0x8580
#define GL_SOURCE1_RGB_ARB                                      0x8581
#define GL_SOURCE2_RGB_ARB                                      0x8582
#define GL_SOURCE0_ALPHA_ARB                                    0x8588
#define GL_SOURCE1_ALPHA_ARB                                    0x8589
#define GL_SOURCE2_ALPHA_ARB                                    0x858A
#define GL_OPERAND0_RGB_ARB                                     0x8590
#define GL_OPERAND1_RGB_ARB                                     0x8591
#define GL_OPERAND2_RGB_ARB                                     0x8592
#define GL_OPERAND0_ALPHA_ARB                                   0x8598
#define GL_OPERAND1_ALPHA_ARB                                   0x8599
#define GL_OPERAND2_ALPHA_ARB                                   0x859A

#endif /* GL_ARB_texture_env_combine */

/*-------------------------------------------------------------------*/
/*------------ARB_TEXTURE_ENV_DOT3-----------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_ARB_texture_env_dot3
#define GL_ARB_texture_env_dot3 1

#define GL_DOT3_RGB_ARB                                         0x86AE
#define GL_DOT3_RGBA_ARB                                        0x86AF

#endif /* GL_ARB_texture_env_dot3 */

/*-------------------------------------------------------------------*/
/*------------ARB_TEXTURE_BORDER_CLAMP-------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_ARB_texture_border_clamp
#define GL_ARB_texture_border_clamp 1

#define GL_CLAMP_TO_BORDER_ARB                                  0x812D

#endif /* GL_ARB_texture_border_clamp */

/*-------------------------------------------------------------------*/
/*------------ARB_TEXTURE_ENV_ADD------------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_ARB_texture_env_add
#define GL_ARB_texture_env_add 1


#endif /* GL_ARB_texture_env_add */

/*-------------------------------------------------------------------*/
/*------------EXT_SECONDARY_COLOR------------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_EXT_secondary_color
#define GL_EXT_secondary_color 1

#define GL_COLOR_SUM_EXT                                        0x8458
#define GL_CURRENT_SECONDARY_COLOR_EXT                          0x8459
#define GL_SECONDARY_COLOR_ARRAY_SIZE_EXT                       0x845A
#define GL_SECONDARY_COLOR_ARRAY_TYPE_EXT                       0x845B
#define GL_SECONDARY_COLOR_ARRAY_STRIDE_EXT                     0x845C
#define GL_SECONDARY_COLOR_ARRAY_POINTER_EXT                    0x845D
#define GL_SECONDARY_COLOR_ARRAY_EXT                            0x845E

#ifdef __PROTOTYPE__

extern void APIENTRY glSecondaryColor3bEXT (GLbyte red, GLbyte green, GLbyte blue);
extern void APIENTRY glSecondaryColor3bvEXT (const GLbyte *v);
extern void APIENTRY glSecondaryColor3dEXT (GLdouble red, GLdouble green, GLdouble blue);
extern void APIENTRY glSecondaryColor3dvEXT (const GLdouble *v);
extern void APIENTRY glSecondaryColor3fEXT (GLfloat red, GLfloat green, GLfloat blue);
extern void APIENTRY glSecondaryColor3fvEXT (const GLfloat *v);
extern void APIENTRY glSecondaryColor3iEXT (GLint red, GLint green, GLint blue);
extern void APIENTRY glSecondaryColor3ivEXT (const GLint *v);
extern void APIENTRY glSecondaryColor3sEXT (GLshort red, GLshort green, GLshort blue);
extern void APIENTRY glSecondaryColor3svEXT (const GLshort *v);
extern void APIENTRY glSecondaryColor3ubEXT (GLubyte red, GLubyte green, GLubyte blue);
extern void APIENTRY glSecondaryColor3ubvEXT (const GLubyte *v);
extern void APIENTRY glSecondaryColor3uiEXT (GLuint red, GLuint green, GLuint blue);
extern void APIENTRY glSecondaryColor3uivEXT (const GLuint *v);
extern void APIENTRY glSecondaryColor3usEXT (GLushort red, GLushort green, GLushort blue);
extern void APIENTRY glSecondaryColor3usvEXT (const GLushort *v);
extern void APIENTRY glSecondaryColorPointerEXT (GLint size, GLenum type, GLsizei stride, GLvoid *pointer);

#endif /* __PROTOTYPE__ */

typedef void (APIENTRY * PFNGLSECONDARYCOLOR3BEXTPROC) (GLbyte red, GLbyte green, GLbyte blue);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3BVEXTPROC) (const GLbyte *v);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3DEXTPROC) (GLdouble red, GLdouble green, GLdouble blue);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3DVEXTPROC) (const GLdouble *v);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3FEXTPROC) (GLfloat red, GLfloat green, GLfloat blue);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3FVEXTPROC) (const GLfloat *v);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3IEXTPROC) (GLint red, GLint green, GLint blue);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3IVEXTPROC) (const GLint *v);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3SEXTPROC) (GLshort red, GLshort green, GLshort blue);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3SVEXTPROC) (const GLshort *v);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3UBEXTPROC) (GLubyte red, GLubyte green, GLubyte blue);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3UBVEXTPROC) (const GLubyte *v);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3UIEXTPROC) (GLuint red, GLuint green, GLuint blue);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3UIVEXTPROC) (const GLuint *v);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3USEXTPROC) (GLushort red, GLushort green, GLushort blue);
typedef void (APIENTRY * PFNGLSECONDARYCOLOR3USVEXTPROC) (const GLushort *v);
typedef void (APIENTRY * PFNGLSECONDARYCOLORPOINTEREXTPROC) (GLint size, GLenum type, GLsizei stride, GLvoid *pointer);


#endif /* GL_EXT_secondary_color */

/*-------------------------------------------------------------------*/
/*------------EXT_FOG_COORD------------------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_EXT_fog_coord
#define GL_EXT_fog_coord 1

#define GL_FOG_COORDINATE_SOURCE_EXT                            0x8450
#define GL_FOG_COORDINATE_EXT                                   0x8451
#define GL_FRAGMENT_DEPTH_EXT                                   0x8452
#define GL_CURRENT_FOG_COORDINATE_EXT                           0x8453
#define GL_FOG_COORDINATE_ARRAY_TYPE_EXT                        0x8454
#define GL_FOG_COORDINATE_ARRAY_STRIDE_EXT                      0x8455
#define GL_FOG_COORDINATE_ARRAY_POINTER_EXT                     0x8456
#define GL_FOG_COORDINATE_ARRAY_EXT                             0x8457

#ifdef __PROTOTYPE__

extern void APIENTRY glFogCoordfEXT (GLfloat coord);
extern void APIENTRY glFogCoordfvEXT (const GLfloat *coord);
extern void APIENTRY glFogCoorddEXT (GLdouble coord);
extern void APIENTRY glFogCoorddvEXT (const GLdouble *coord);
extern void APIENTRY glFogCoordPointerEXT (GLenum type, GLsizei stride, const GLvoid *pointer);

#endif /* __PROTOTYPE__ */

typedef void (APIENTRY * PFNGLFOGCOORDFEXTPROC) (GLfloat coord);
typedef void (APIENTRY * PFNGLFOGCOORDFVEXTPROC) (const GLfloat *coord);
typedef void (APIENTRY * PFNGLFOGCOORDDEXTPROC) (GLdouble coord);
typedef void (APIENTRY * PFNGLFOGCOORDDVEXTPROC) (const GLdouble *coord);
typedef void (APIENTRY * PFNGLFOGCOORDPOINTEREXTPROC) (GLenum type, GLsizei stride, const GLvoid *pointer);

#endif /* GL_EXT_fog_coord */

/*-------------------------------------------------------------------*/
/*------------NV_VERTEX_ARRAY_RANGE----------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_NV_vertex_array_range
#define GL_NV_vertex_array_range 1

#define GL_VERTEX_ARRAY_RANGE_NV                                0x851D
#define GL_VERTEX_ARRAY_RANGE_LENGTH_NV                         0x851E
#define GL_VERTEX_ARRAY_RANGE_VALID_NV                          0x851F
#define GL_MAX_VERTEX_ARRAY_RANGE_ELEMENT_NV                    0x8520
#define GL_VERTEX_ARRAY_RANGE_POINTER_NV                        0x8521

#ifdef __PROTOTYPE__

extern void APIENTRY glFlushVertexArrayRangeNV (void);
extern void APIENTRY glVertexArrayRangeNV (GLsizei size, const GLvoid *pointer);

#endif /* __PROTOTYPE__ */

typedef void (APIENTRY * PFNGLFLUSHVERTEXARRAYRANGENVPROC) (void);
typedef void (APIENTRY * PFNGLVERTEXARRAYRANGENVPROC) (GLsizei size, const GLvoid *pointer);

#endif /* GL_NV_vertex_array_range */

/*-------------------------------------------------------------------*/
/*------------NV_VERTEX_ARRAY_RANGE2---------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_NV_vertex_array_range2
#define GL_NV_vertex_array_range2 1

#define GL_VERTEX_ARRAY_RANGE_WITHOUT_FLUSH_NV                  0x8533

#endif /* GL_NV_vertex_array_range2 */

/*-------------------------------------------------------------------*/
/*------------EXT_POINT_PARAMETERS-----------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_EXT_point_parameters
#define GL_EXT_point_parameters 1

#define GL_POINT_SIZE_MIN_EXT                                   0x8126
#define GL_POINT_SIZE_MAX_EXT                                   0x8127
#define GL_POINT_FADE_THRESHOLD_SIZE_EXT                        0x8128
#define GL_DISTANCE_ATTENUATION_EXT                             0x8129

#ifdef __PROTOTYPE__

extern void APIENTRY glPointParameterfEXT (GLenum pname, GLfloat param);
extern void APIENTRY glPointParameterfvEXT (GLenum pname, const GLfloat *params);

#endif /* __PROTOTYPE__ */

typedef void (APIENTRY * PFNGLPOINTPARAMETERFEXTPROC) (GLenum pname, GLfloat param);
typedef void (APIENTRY * PFNGLPOINTPARAMETERFVEXTPROC) (GLenum pname, const GLfloat *params);

#endif /* GL_EXT_point_parameters */

/*-------------------------------------------------------------------*/
/*------------NV_REGISTER_COMBINERS----------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_NV_register_combiners
#define GL_NV_register_combiners 1

#define GL_REGISTER_COMBINERS_NV                                0x8522
#define GL_COMBINER0_NV                                         0x8550
#define GL_COMBINER1_NV                                         0x8551
#define GL_COMBINER2_NV                                         0x8552
#define GL_COMBINER3_NV                                         0x8553
#define GL_COMBINER4_NV                                         0x8554
#define GL_COMBINER5_NV                                         0x8555
#define GL_COMBINER6_NV                                         0x8556
#define GL_COMBINER7_NV                                         0x8557
#define GL_VARIABLE_A_NV                                        0x8523
#define GL_VARIABLE_B_NV                                        0x8524
#define GL_VARIABLE_C_NV                                        0x8525
#define GL_VARIABLE_D_NV                                        0x8526
#define GL_VARIABLE_E_NV                                        0x8527
#define GL_VARIABLE_F_NV                                        0x8528
#define GL_VARIABLE_G_NV                                        0x8529
#define GL_CONSTANT_COLOR0_NV                                   0x852A
#define GL_CONSTANT_COLOR1_NV                                   0x852B
#define GL_PRIMARY_COLOR_NV                                     0x852C
#define GL_SECONDARY_COLOR_NV                                   0x852D
#define GL_SPARE0_NV                                            0x852E
#define GL_SPARE1_NV                                            0x852F
#define GL_UNSIGNED_IDENTITY_NV                                 0x8536
#define GL_UNSIGNED_INVERT_NV                                   0x8537
#define GL_EXPAND_NORMAL_NV                                     0x8538
#define GL_EXPAND_NEGATE_NV                                     0x8539
#define GL_HALF_BIAS_NORMAL_NV                                  0x853A
#define GL_HALF_BIAS_NEGATE_NV                                  0x853B
#define GL_SIGNED_IDENTITY_NV                                   0x853C
#define GL_SIGNED_NEGATE_NV                                     0x853D
#define GL_E_TIMES_F_NV                                         0x8531
#define GL_SPARE0_PLUS_SECONDARY_COLOR_NV                       0x8532
#define GL_SCALE_BY_TWO_NV                                      0x853E
#define GL_SCALE_BY_FOUR_NV                                     0x853F
#define GL_SCALE_BY_ONE_HALF_NV                                 0x8540
#define GL_BIAS_BY_NEGATIVE_ONE_HALF_NV                         0x8541
#define GL_DISCARD_NV                                           0x8530
#define GL_COMBINER_INPUT_NV                                    0x8542
#define GL_COMBINER_MAPPING_NV                                  0x8543
#define GL_COMBINER_COMPONENT_USAGE_NV                          0x8544
#define GL_COMBINER_AB_DOT_PRODUCT_NV                           0x8545
#define GL_COMBINER_CD_DOT_PRODUCT_NV                           0x8546
#define GL_COMBINER_MUX_SUM_NV                                  0x8547
#define GL_COMBINER_SCALE_NV                                    0x8548
#define GL_COMBINER_BIAS_NV                                     0x8549
#define GL_COMBINER_AB_OUTPUT_NV                                0x854A
#define GL_COMBINER_CD_OUTPUT_NV                                0x854B
#define GL_COMBINER_SUM_OUTPUT_NV                               0x854C
#define GL_NUM_GENERAL_COMBINERS_NV                             0x854E
#define GL_COLOR_SUM_CLAMP_NV                                   0x854F
#define GL_MAX_GENERAL_COMBINERS_NV                             0x854D

#ifdef __PROTOTYPE__

extern void APIENTRY glCombinerParameterfvNV (GLenum pname, const GLfloat *params);
extern void APIENTRY glCombinerParameterfNV (GLenum pname, GLfloat param);
extern void APIENTRY glCombinerParameterivNV (GLenum pname, const GLint *params);
extern void APIENTRY glCombinerParameteriNV (GLenum pname, GLint param);
extern void APIENTRY glCombinerInputNV (GLenum stage, GLenum portion, GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage);
extern void APIENTRY glCombinerOutputNV (GLenum stage, GLenum portion, GLenum abOutput, GLenum cdOutput, GLenum sumOutput, GLenum scale, GLenum bias, GLboolean abDotProduct, GLboolean cdDotProduct, GLboolean muxSum);
extern void APIENTRY glFinalCombinerInputNV (GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage);
extern void APIENTRY glGetCombinerInputParameterfvNV (GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLfloat *params);
extern void APIENTRY glGetCombinerInputParameterivNV (GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLint *params);
extern void APIENTRY glGetCombinerOutputParameterfvNV (GLenum stage, GLenum portion, GLenum pname, GLfloat *params);
extern void APIENTRY glGetCombinerOutputParameterivNV (GLenum stage, GLenum portion, GLenum pname, GLint *params);
extern void APIENTRY glGetFinalCombinerInputParameterfvNV (GLenum variable, GLenum pname, GLfloat *params);
extern void APIENTRY glGetFinalCombinerInputParameterivNV (GLenum variable, GLenum pname, GLint *params);

#endif /* __PROTOTYPE__ */

typedef void (APIENTRY * PFNGLCOMBINERPARAMETERFVNVPROC) (GLenum pname, const GLfloat *params);
typedef void (APIENTRY * PFNGLCOMBINERPARAMETERFNVPROC) (GLenum pname, GLfloat param);
typedef void (APIENTRY * PFNGLCOMBINERPARAMETERIVNVPROC) (GLenum pname, const GLint *params);
typedef void (APIENTRY * PFNGLCOMBINERPARAMETERINVPROC) (GLenum pname, GLint param);
typedef void (APIENTRY * PFNGLCOMBINERINPUTNVPROC) (GLenum stage, GLenum portion, GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage);
typedef void (APIENTRY * PFNGLCOMBINEROUTPUTNVPROC) (GLenum stage, GLenum portion, GLenum abOutput, GLenum cdOutput, GLenum sumOutput, GLenum scale, GLenum bias, GLboolean abDotProduct, GLboolean cdDotProduct, GLboolean muxSum);
typedef void (APIENTRY * PFNGLFINALCOMBINERINPUTNVPROC) (GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage);
typedef void (APIENTRY * PFNGLGETCOMBINERINPUTPARAMETERFVNVPROC) (GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLfloat *params);
typedef void (APIENTRY * PFNGLGETCOMBINERINPUTPARAMETERIVNVPROC) (GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLint *params);
typedef void (APIENTRY * PFNGLGETCOMBINEROUTPUTPARAMETERFVNVPROC) (GLenum stage, GLenum portion, GLenum pname, GLfloat *params);
typedef void (APIENTRY * PFNGLGETCOMBINEROUTPUTPARAMETERIVNVPROC) (GLenum stage, GLenum portion, GLenum pname, GLint *params);
typedef void (APIENTRY * PFNGLGETFINALCOMBINERINPUTPARAMETERFVNVPROC) (GLenum variable, GLenum pname, GLfloat *params);
typedef void (APIENTRY * PFNGLGETFINALCOMBINERINPUTPARAMETERIVNVPROC) (GLenum variable, GLenum pname, GLint *params);


#endif /* GL_NV_register_combiners */

/*-------------------------------------------------------------------*/
/*------------ARB_MULTISAMPLE----------------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_ARB_multisample
#define GL_ARB_multisample 1

#define GL_MULTISAMPLE_ARB                                      0x809D
#define GL_SAMPLE_ALPHA_TO_COVERAGE_ARB                         0x809E
#define GL_SAMPLE_ALPHA_TO_ONE_ARB                              0x809F
#define GL_SAMPLE_COVERAGE_ARB                                  0x80A0
#define GL_SAMPLE_BUFFERS_ARB                                   0x80A8
#define GL_SAMPLES_ARB                                          0x80A9
#define GL_SAMPLE_COVERAGE_VALUE_ARB                            0x80AA
#define GL_SAMPLE_COVERAGE_INVERT_ARB                           0x80AB
#define GL_MULTISAMPLE_BIT_ARB                                  0x20000000

#ifdef __PROTOTYPE__

extern void APIENTRY glSampleCoverageARB (GLclampf value, GLboolean invert);

#endif /* __PROTOTYPE__ */

typedef void (APIENTRY * PFNGLSAMPLECOVERAGEARBPROC) (GLclampf value, GLboolean invert);

#endif /* GL_ARB_multisample */

/*-------------------------------------------------------------------*/
/*------------NV_TEXTURE_SHADER--------------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_NV_texture_shader
#define GL_NV_texture_shader 1

#define GL_TEXTURE_SHADER_NV                                    0x86DE
#define GL_RGBA_UNSIGNED_DOT_PRODUCT_MAPPING_NV                 0x86D9
#define GL_SHADER_OPERATION_NV                                  0x86DF
#define GL_CULL_MODES_NV                                        0x86E0
#define GL_OFFSET_TEXTURE_MATRIX_NV                             0x86E1
#define GL_OFFSET_TEXTURE_SCALE_NV                              0x86E2
#define GL_OFFSET_TEXTURE_BIAS_NV                               0x86E3
#define GL_PREVIOUS_TEXTURE_INPUT_NV                            0x86E4
#define GL_CONST_EYE_NV                                         0x86E5
#define GL_SHADER_CONSISTENT_NV                                 0x86DD
#define GL_PASS_THROUGH_NV                                      0x86E6
#define GL_CULL_FRAGMENT_NV                                     0x86E7
#define GL_OFFSET_TEXTURE_2D_NV                                 0x86E8
#define GL_OFFSET_TEXTURE_RECTANGLE_NV                          0x864C
#define GL_OFFSET_TEXTURE_RECTANGLE_SCALE_NV                    0x864D
#define GL_DEPENDENT_AR_TEXTURE_2D_NV                           0x86E9
#define GL_DEPENDENT_GB_TEXTURE_2D_NV                           0x86EA
#define GL_DOT_PRODUCT_NV                                       0x86EC
#define GL_DOT_PRODUCT_DEPTH_REPLACE_NV                         0x86ED
#define GL_DOT_PRODUCT_TEXTURE_2D_NV                            0x86EE
#define GL_DOT_PRODUCT_TEXTURE_RECTANGLE_NV                     0x864E
#define GL_DOT_PRODUCT_TEXTURE_CUBE_MAP_NV                      0x86F0
#define GL_DOT_PRODUCT_DIFFUSE_CUBE_MAP_NV                      0x86F1
#define GL_DOT_PRODUCT_REFLECT_CUBE_MAP_NV                      0x86F2
#define GL_DOT_PRODUCT_CONST_EYE_REFLECT_CUBE_MAP_NV            0x86F3
#define GL_HILO_NV                                              0x86F4
#define GL_DSDT_NV                                              0x86F5
#define GL_DSDT_MAG_NV                                          0x86F6
#define GL_DSDT_MAG_VIB_NV                                      0x86F7
#define GL_UNSIGNED_INT_S8_S8_8_8_NV                            0x86DA
#define GL_UNSIGNED_INT_8_8_S8_S8_REV_NV                        0x86DB
#define GL_SIGNED_RGBA_NV                                       0x86FB
#define GL_SIGNED_RGBA8_NV                                      0x86FC
#define GL_SIGNED_RGB_NV                                        0x86FE
#define GL_SIGNED_RGB8_NV                                       0x86FF
#define GL_SIGNED_LUMINANCE_NV                                  0x8701
#define GL_SIGNED_LUMINANCE8_NV                                 0x8702
#define GL_SIGNED_LUMINANCE_ALPHA_NV                            0x8703
#define GL_SIGNED_LUMINANCE8_ALPHA8_NV                          0x8704
#define GL_SIGNED_ALPHA_NV                                      0x8705
#define GL_SIGNED_ALPHA8_NV                                     0x8706
#define GL_SIGNED_INTENSITY_NV                                  0x8707
#define GL_SIGNED_INTENSITY8_NV                                 0x8708
#define GL_SIGNED_RGB_UNSIGNED_ALPHA_NV                         0x870C
#define GL_SIGNED_RGB8_UNSIGNED_ALPHA8_NV                       0x870D
#define GL_HILO16_NV                                            0x86F8
#define GL_SIGNED_HILO_NV                                       0x86F9
#define GL_SIGNED_HILO16_NV                                     0x86FA
#define GL_DSDT8_NV                                             0x8709
#define GL_DSDT8_MAG8_NV                                        0x870A
#define GL_DSDT_MAG_INTENSITY_NV                                0x86DC
#define GL_DSDT8_MAG8_INTENSITY8_NV                             0x870B
#define GL_HI_SCALE_NV                                          0x870E
#define GL_LO_SCALE_NV                                          0x870F
#define GL_DS_SCALE_NV                                          0x8710
#define GL_DT_SCALE_NV                                          0x8711
#define GL_MAGNITUDE_SCALE_NV                                   0x8712
#define GL_VIBRANCE_SCALE_NV                                    0x8713
#define GL_HI_BIAS_NV                                           0x8714
#define GL_LO_BIAS_NV                                           0x8715
#define GL_DS_BIAS_NV                                           0x8716
#define GL_DT_BIAS_NV                                           0x8717
#define GL_MAGNITUDE_BIAS_NV                                    0x8718
#define GL_VIBRANCE_BIAS_NV                                     0x8719
#define GL_TEXTURE_BORDER_VALUES_NV                             0x871A
#define GL_TEXTURE_HI_SIZE_NV                                   0x871B
#define GL_TEXTURE_LO_SIZE_NV                                   0x871C
#define GL_TEXTURE_DS_SIZE_NV                                   0x871D
#define GL_TEXTURE_DT_SIZE_NV                                   0x871E
#define GL_TEXTURE_MAG_SIZE_NV                                  0x871F

#endif /* GL_NV_texture_shader */

/*-------------------------------------------------------------------*/
/*------------GL_NV_TEXTURE_RECTANGLE--------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_NV_texture_rectangle
#define GL_NV_texture_rectangle 1

#define GL_TEXTURE_RECTANGLE_NV                                 0x84F5
#define GL_TEXTURE_BINDING_RECTANGLE_NV                         0x84F6
#define GL_PROXY_TEXTURE_RECTANGLE_NV                           0x84F7
#define GL_MAX_RECTANGLE_TEXTURE_SIZE_NV                        0x84F8

#endif /* GL_NV_texture_recrangle */

/*-------------------------------------------------------------------*/
/*------------NV_TEXTURE_ENV_COMBINE4--------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_NV_texture_env_combine4
#define GL_NV_texture_env_combine4 1

#define GL_COMBINE4_NV                                          0x8503
#define GL_SOURCE3_RGB_NV                                       0x8583
#define GL_SOURCE3_ALPHA_NV                                     0x858B
#define GL_OPERAND3_RGB_NV                                      0x8593
#define GL_OPERAND3_ALPHA_NV                                    0x859B

#endif /* GL_NV_texture_env_combine */

/*-------------------------------------------------------------------*/
/*------------NV_FOG_DISTANCE----------------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_NV_fog_distance
#define GL_NV_fog_distance 1

#define GL_FOG_DISTANCE_MODE_NV                                 0x855A
#define GL_EYE_RADIAL_NV                                        0x855B
#define GL_EYE_PLANE_ABSOLUTE_NV                                0x855C

#endif /* GL_NV_fog_distance */

/*-------------------------------------------------------------------*/
/*------------EXT_TEXTURE_FILTER_ANISOTROPIC-------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_EXT_texture_filter_anisotropic
#define GL_EXT_texture_filter_anisotropic 1

#define GL_TEXTURE_MAX_ANISOTROPY_EXT                           0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT                       0x84FF

#endif /* GL_EXT_texture_filter_anisotropic */

/*-------------------------------------------------------------------*/
/*------------SGIS_GENERATE_MIPMAP-----------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_SGIS_generate_mipmap
#define GL_SGIS_generate_mipmap 1

#define GL_GENERATE_MIPMAP_SGIS                                 0x8191
#define GL_GENERATE_MIPMAP_HINT_SGIS                            0x8192

#endif /* GL_SGIS_generate_mipmap */

/*-------------------------------------------------------------------*/
/*------------NV_TEXGEN_REFLECTION-----------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_NV_texgen_reflection
#define GL_NV_texgen_reflection 1

#define GL_NORMAL_MAP_NV                                        0x8511
#define GL_REFLECTION_MAP_NV                                    0x8512

#endif /* GL_NV_texgen_reflection */

/*-------------------------------------------------------------------*/
/*------------EXT_VERTEX_WEIGHTING-----------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_EXT_vertex_weighting
#define GL_EXT_vertex_weighting 1

#define GL_MODELVIEW0_STACK_DEPTH_EXT                           0x0BA3  /* alias to GL_MODELVIEW_STACK_DEPTH */
#define GL_MODELVIEW1_STACK_DEPTH_EXT                           0x8502
#define GL_MODELVIEW0_MATRIX_EXT                                0x0BA6  /* alias to GL_MODELVIEW_MATRIX */
#define GL_MODELVIEW1_MATRIX_EXT                                0x8506
#define GL_VERTEX_WEIGHTING_EXT                                 0x8509
#define GL_MODELVIEW0_EXT                                       0x1700  /* alias to GL_MODELVIEW */
#define GL_MODELVIEW1_EXT                                       0x850A
#define GL_CURRENT_VERTEX_WEIGHT_EXT                            0x850B
#define GL_VERTEX_WEIGHT_ARRAY_EXT                              0x850C
#define GL_VERTEX_WEIGHT_ARRAY_SIZE_EXT                         0x850D
#define GL_VERTEX_WEIGHT_ARRAY_TYPE_EXT                         0x850E
#define GL_VERTEX_WEIGHT_ARRAY_STRIDE_EXT                       0x850F
#define GL_VERTEX_WEIGHT_ARRAY_POINTER_EXT                      0x8510

#ifdef __PROTOTYPE__

extern void APIENTRY glVertexWeightfEXT (GLfloat weight);
extern void APIENTRY glVertexWeightfvEXT (const GLfloat *weight);
extern void APIENTRY glVertexWeightPointerEXT (GLsizei size, GLenum type, GLsizei stride, const GLvoid *pointer);

#endif /* __PROTOTYPE__ */

typedef void (APIENTRY * PFNGLVERTEXWEIGHTFEXTPROC) (GLfloat weight);
typedef void (APIENTRY * PFNGLVERTEXWEIGHTFVEXTPROC) (const GLfloat *weight);
typedef void (APIENTRY * PFNGLVERTEXWEIGHTPOINTEREXTPROC) (GLsizei size, GLenum type, GLsizei stride, const GLvoid *pointer);

#endif /* GL_EXT_vertex_weighting */

/*-------------------------------------------------------------------*/
/*------------NV_VERTEX_PROGRAM--------------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_NV_vertex_program
#define GL_NV_vertex_program 1

#define GL_VERTEX_PROGRAM_NV                                    0x8620
#define GL_VERTEX_PROGRAM_POINT_SIZE_NV                         0x8642
#define GL_VERTEX_PROGRAM_TWO_SIDE_NV                           0x8643
#define GL_VERTEX_STATE_PROGRAM_NV                              0x8621
#define GL_ATTRIB_ARRAY_SIZE_NV                                 0x8623
#define GL_ATTRIB_ARRAY_STRIDE_NV                               0x8624
#define GL_ATTRIB_ARRAY_TYPE_NV                                 0x8625
#define GL_CURRENT_ATTRIB_NV                                    0x8626
#define GL_PROGRAM_PARAMETER_NV                                 0x8644
#define GL_ATTRIB_ARRAY_POINTER_NV                              0x8645
#define GL_PROGRAM_TARGET_NV                                    0x8646
#define GL_PROGRAM_LENGTH_NV                                    0x8627
#define GL_PROGRAM_RESIDENT_NV                                  0x8647
#define GL_PROGRAM_STRING_NV                                    0x8628
#define GL_TRACK_MATRIX_NV                                      0x8648
#define GL_TRACK_MATRIX_TRANSFORM_NV                            0x8649
#define GL_MAX_TRACK_MATRIX_STACK_DEPTH_NV                      0x862E
#define GL_MAX_TRACK_MATRICES_NV                                0x862F
#define GL_CURRENT_MATRIX_STACK_DEPTH_NV                        0x8640
#define GL_CURRENT_MATRIX_NV                                    0x8641
#define GL_VERTEX_PROGRAM_BINDING_NV                            0x864A
#define GL_PROGRAM_ERROR_POSITION_NV                            0x864B
#define GL_MODELVIEW_PROJECTION_NV                              0x8629
#define GL_MATRIX0_NV                                           0x8630
#define GL_MATRIX1_NV                                           0x8631
#define GL_MATRIX2_NV                                           0x8632
#define GL_MATRIX3_NV                                           0x8633
#define GL_MATRIX4_NV                                           0x8634
#define GL_MATRIX5_NV                                           0x8635
#define GL_MATRIX6_NV                                           0x8636
#define GL_MATRIX7_NV                                           0x8637
#define GL_IDENTITY_NV                                          0x862A
#define GL_INVERSE_NV                                           0x862B
#define GL_TRANSPOSE_NV                                         0x862C
#define GL_INVERSE_TRANSPOSE_NV                                 0x862D
#define GL_VERTEX_ATTRIB_ARRAY0_NV                              0x8650
#define GL_VERTEX_ATTRIB_ARRAY1_NV                              0x8651
#define GL_VERTEX_ATTRIB_ARRAY2_NV                              0x8652
#define GL_VERTEX_ATTRIB_ARRAY3_NV                              0x8653
#define GL_VERTEX_ATTRIB_ARRAY4_NV                              0x8654
#define GL_VERTEX_ATTRIB_ARRAY5_NV                              0x8655
#define GL_VERTEX_ATTRIB_ARRAY6_NV                              0x8656
#define GL_VERTEX_ATTRIB_ARRAY7_NV                              0x8657
#define GL_VERTEX_ATTRIB_ARRAY8_NV                              0x8658
#define GL_VERTEX_ATTRIB_ARRAY9_NV                              0x8659
#define GL_VERTEX_ATTRIB_ARRAY10_NV                             0x865A
#define GL_VERTEX_ATTRIB_ARRAY11_NV                             0x865B
#define GL_VERTEX_ATTRIB_ARRAY12_NV                             0x865C
#define GL_VERTEX_ATTRIB_ARRAY13_NV                             0x865D
#define GL_VERTEX_ATTRIB_ARRAY14_NV                             0x865E
#define GL_VERTEX_ATTRIB_ARRAY15_NV                             0x865F
#define GL_MAP1_VERTEX_ATTRIB0_4_NV                             0x8660
#define GL_MAP1_VERTEX_ATTRIB1_4_NV                             0x8661
#define GL_MAP1_VERTEX_ATTRIB2_4_NV                             0x8662
#define GL_MAP1_VERTEX_ATTRIB3_4_NV                             0x8663
#define GL_MAP1_VERTEX_ATTRIB4_4_NV                             0x8664
#define GL_MAP1_VERTEX_ATTRIB5_4_NV                             0x8665
#define GL_MAP1_VERTEX_ATTRIB6_4_NV                             0x8666
#define GL_MAP1_VERTEX_ATTRIB7_4_NV                             0x8667
#define GL_MAP1_VERTEX_ATTRIB8_4_NV                             0x8668
#define GL_MAP1_VERTEX_ATTRIB9_4_NV                             0x8669
#define GL_MAP1_VERTEX_ATTRIB10_4_NV                            0x866A
#define GL_MAP1_VERTEX_ATTRIB11_4_NV                            0x866B
#define GL_MAP1_VERTEX_ATTRIB12_4_NV                            0x866C
#define GL_MAP1_VERTEX_ATTRIB13_4_NV                            0x866D
#define GL_MAP1_VERTEX_ATTRIB14_4_NV                            0x866E
#define GL_MAP1_VERTEX_ATTRIB15_4_NV                            0x866F
#define GL_MAP2_VERTEX_ATTRIB0_4_NV                             0x8670
#define GL_MAP2_VERTEX_ATTRIB1_4_NV                             0x8671
#define GL_MAP2_VERTEX_ATTRIB2_4_NV                             0x8672
#define GL_MAP2_VERTEX_ATTRIB3_4_NV                             0x8673
#define GL_MAP2_VERTEX_ATTRIB4_4_NV                             0x8674
#define GL_MAP2_VERTEX_ATTRIB5_4_NV                             0x8675
#define GL_MAP2_VERTEX_ATTRIB6_4_NV                             0x8676
#define GL_MAP2_VERTEX_ATTRIB7_4_NV                             0x8677
#define GL_MAP2_VERTEX_ATTRIB8_4_NV                             0x8678
#define GL_MAP2_VERTEX_ATTRIB9_4_NV                             0x8679
#define GL_MAP2_VERTEX_ATTRIB10_4_NV                            0x867A
#define GL_MAP2_VERTEX_ATTRIB11_4_NV                            0x867B
#define GL_MAP2_VERTEX_ATTRIB12_4_NV                            0x867C
#define GL_MAP2_VERTEX_ATTRIB13_4_NV                            0x867D
#define GL_MAP2_VERTEX_ATTRIB14_4_NV                            0x867E
#define GL_MAP2_VERTEX_ATTRIB15_4_NV                            0x867F

#ifdef __PROTOTYPE__

extern void APIENTRY glBindProgramNV(GLenum target, GLuint id);
extern void APIENTRY glDeleteProgramsNV(GLsizei n, const GLuint *ids);
extern void APIENTRY glExecuteProgramNV(GLenum target, GLuint id, const GLfloat *params);
extern void APIENTRY glGenProgramsNV(GLsizei n, GLuint *ids);
extern GLboolean APIENTRY glAreProgramsResidentNV(GLsizei n, const GLuint *ids, GLboolean *residences);
extern void APIENTRY glRequestResidentProgramsNV(GLsizei n, GLuint *ids);
extern void APIENTRY glGetProgramParameterfvNV(GLenum target, GLuint index, GLenum pname, GLfloat *params);
extern void APIENTRY glGetProgramParameterdvNV(GLenum target, GLuint index, GLenum pname, GLdouble *params);
extern void APIENTRY glGetProgramivNV(GLuint id, GLenum pname, GLint *params);
extern void APIENTRY glGetProgramStringNV(GLuint id, GLenum pname, GLubyte *program);
extern void APIENTRY glGetTrackMatrixivNV(GLenum target, GLuint address, GLenum pname, GLint *params);
extern void APIENTRY glGetVertexAttribdvNV(GLuint index, GLenum pname, GLdouble *params);
extern void APIENTRY glGetVertexAttribfvNV(GLuint index, GLenum pname, GLfloat *params);
extern void APIENTRY glGetVertexAttribivNV(GLuint index, GLenum pname, GLint *params);
extern void APIENTRY glGetVertexAttribPointervNV(GLuint index, GLenum pname, GLvoid **pointer);
extern GLboolean APIENTRY glIsProgramNV(GLuint id);
extern void APIENTRY glLoadProgramNV(GLenum target, GLuint id, GLsizei len, const GLubyte *program);
extern void APIENTRY glProgramParameter4fNV(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
extern void APIENTRY glProgramParameter4dNV(GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
extern void APIENTRY glProgramParameter4dvNV(GLenum target, GLuint index, const GLdouble *params);
extern void APIENTRY glProgramParameter4fvNV(GLenum target, GLuint index, const GLfloat *params);
extern void APIENTRY glProgramParameters4dvNV(GLenum target, GLuint index, GLuint num, const GLdouble *params);
extern void APIENTRY glProgramParameters4fvNV(GLenum target, GLuint index, GLuint num, const GLfloat *params);
extern void APIENTRY glTrackMatrixNV(GLenum target, GLuint address, GLenum matrix, GLenum transform);
extern void APIENTRY glVertexAttribPointerNV(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
extern void APIENTRY glVertexAttrib1sNV(GLuint index, GLshort x);
extern void APIENTRY glVertexAttrib1fNV(GLuint index, GLfloat x);
extern void APIENTRY glVertexAttrib1dNV(GLuint index, GLdouble x);
extern void APIENTRY glVertexAttrib2sNV(GLuint index, GLshort x, GLshort y);
extern void APIENTRY glVertexAttrib2fNV(GLuint index, GLfloat x, GLfloat y);
extern void APIENTRY glVertexAttrib2dNV(GLuint index, GLdouble x, GLdouble y);
extern void APIENTRY glVertexAttrib3sNV(GLuint index, GLshort x, GLshort y, GLshort z);
extern void APIENTRY glVertexAttrib3fNV(GLuint index, GLfloat x, GLfloat y, GLfloat z);
extern void APIENTRY glVertexAttrib3dNV(GLuint index, GLdouble x, GLdouble y, GLdouble z);
extern void APIENTRY glVertexAttrib4sNV(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
extern void APIENTRY glVertexAttrib4fNV(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
extern void APIENTRY glVertexAttrib4dNV(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
extern void APIENTRY glVertexAttrib4ubNV(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
extern void APIENTRY glVertexAttrib1svNV(GLuint index, const GLshort *v);
extern void APIENTRY glVertexAttrib1fvNV(GLuint index, const GLfloat *v);
extern void APIENTRY glVertexAttrib1dvNV(GLuint index, const GLdouble *v);
extern void APIENTRY glVertexAttrib2svNV(GLuint index, const GLshort *v);
extern void APIENTRY glVertexAttrib2fvNV(GLuint index, const GLfloat *v);
extern void APIENTRY glVertexAttrib2dvNV(GLuint index, const GLdouble *v);
extern void APIENTRY glVertexAttrib3svNV(GLuint index, const GLshort *v);
extern void APIENTRY glVertexAttrib3fvNV(GLuint index, const GLfloat *v);
extern void APIENTRY glVertexAttrib3dvNV(GLuint index, const GLdouble *v);
extern void APIENTRY glVertexAttrib4svNV(GLuint index, const GLshort *v);
extern void APIENTRY glVertexAttrib4fvNV(GLuint index, const GLfloat *v);
extern void APIENTRY glVertexAttrib4dvNV(GLuint index, const GLdouble *v);
extern void APIENTRY glVertexAttrib4ubvNV(GLuint index, const GLubyte *v);
extern void APIENTRY glVertexAttribs1svNV(GLuint index, GLsizei n, const GLshort *v);
extern void APIENTRY glVertexAttribs1fvNV(GLuint index, GLsizei n, const GLfloat *v);
extern void APIENTRY glVertexAttribs1dvNV(GLuint index, GLsizei n, const GLdouble *v);
extern void APIENTRY glVertexAttribs2svNV(GLuint index, GLsizei n, const GLshort *v);
extern void APIENTRY glVertexAttribs2fvNV(GLuint index, GLsizei n, const GLfloat *v);
extern void APIENTRY glVertexAttribs2dvNV(GLuint index, GLsizei n, const GLdouble *v);
extern void APIENTRY glVertexAttribs3svNV(GLuint index, GLsizei n, const GLshort *v);
extern void APIENTRY glVertexAttribs3fvNV(GLuint index, GLsizei n, const GLfloat *v);
extern void APIENTRY glVertexAttribs3dvNV(GLuint index, GLsizei n, const GLdouble *v);
extern void APIENTRY glVertexAttribs4svNV(GLuint index, GLsizei n, const GLshort *v);
extern void APIENTRY glVertexAttribs4fvNV(GLuint index, GLsizei n, const GLfloat *v);
extern void APIENTRY glVertexAttribs4dvNV(GLuint index, GLsizei n, const GLdouble *v);
extern void APIENTRY glVertexAttribs4ubvNV(GLuint index, GLsizei n, const GLubyte *v);

#endif /* __PROTOTYPE__ */

typedef void (APIENTRY * PFNGLBINDPROGRAMNVPROC) (GLenum target, GLuint id);
typedef void (APIENTRY * PFNGLDELETEPROGRAMSNVPROC) (GLsizei n, const GLuint *ids);
typedef void (APIENTRY * PFNGLEXECUTEPROGRAMNVPROC) (GLenum target, GLuint id, const GLfloat *params);
typedef void (APIENTRY * PFNGLGENPROGRAMSNVPROC) (GLsizei n, GLuint *ids);
typedef GLboolean (APIENTRY * PFNGLAREPROGRAMSRESIDENTNVPROC) (GLsizei n, const GLuint *ids, GLboolean *residences);
typedef void (APIENTRY * PFNGLREQUESTRESIDENTPROGRAMSNVPROC) (GLsizei n, GLuint *ids);
typedef void (APIENTRY * PFNGLGETPROGRAMPARAMETERFVNVPROC) (GLenum target, GLuint index, GLenum pname, GLfloat *params);
typedef void (APIENTRY * PFNGLGETPROGRAMPARAMETERDVNVPROC) (GLenum target, GLuint index, GLenum pname, GLdouble *params);
typedef void (APIENTRY * PFNGLGETPROGRAMIVNVPROC) (GLuint id, GLenum pname, GLint *params);
typedef void (APIENTRY * PFNGLGETPROGRAMSTRINGNVPROC) (GLuint id, GLenum pname, GLubyte *program);
typedef void (APIENTRY * PFNGLGETTRACKMATRIXIVNVPROC) (GLenum target, GLuint address, GLenum pname, GLint *params);
typedef void (APIENTRY * PFNGLGETVERTEXATTRIBDVNVPROC) (GLuint index, GLenum pname, GLdouble *params);
typedef void (APIENTRY * PFNGLGETVERTEXATTRINFVNVPROC) (GLuint index, GLenum pname, GLfloat *params);
typedef void (APIENTRY * PFNGLGETVERTEXATTRIBIVNVPROC) (GLuint index, GLenum pname, GLint *params);
typedef void (APIENTRY * PFNGLGETVERTEXATTRIBPOINTERVNVPROC) (GLuint index, GLenum pname, GLvoid **pointer);
typedef GLboolean (APIENTRY * PFNGLISPROGRAMNVPROC) (GLuint id);
typedef void (APIENTRY * PFNGLLOADPROGRAMNVPROC) (GLenum target, GLuint id, GLsizei len, const GLubyte *program);
typedef void (APIENTRY * PFNGLPROGRAMPARAMETER4FNVPROC) (GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (APIENTRY * PFNGLPROGRAMPARAMETER4DNVPROC) (GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRY * PFNGLPROGRAMPARAMETER4DVNVPROC) (GLenum target, GLuint index, const GLdouble *params);
typedef void (APIENTRY * PFNGLPROGRAMPARAMETER4FVNVPROC) (GLenum target, GLuint index, const GLfloat *params);
typedef void (APIENTRY * PFNGLPROGRAMPARAMETERS4DVNVPROC) (GLenum target, GLuint index, GLuint num, const GLdouble *params);
typedef void (APIENTRY * PFNGLPROGRAMPARAMETERS4FVNVPROC) (GLenum target, GLuint index, GLuint num, const GLfloat *params);
typedef void (APIENTRY * PFNGLTRACKMATRIXNVPROC) (GLenum target, GLuint address, GLenum matrix, GLenum transform);
typedef void (APIENTRY * PFNGLVERTEXATTRIBPPOINTERNVPROC) (GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
typedef void (APIENTRY * PFNGLVERTEXATTRIB1SNVPROC) (GLuint index, GLshort x);
typedef void (APIENTRY * PFNGLVERTEXATTRIB1FNVPROC) (GLuint index, GLfloat x);
typedef void (APIENTRY * PFNGLVERTEXATTRIB1DNVPROC) (GLuint index, GLdouble x);
typedef void (APIENTRY * PFNGLVERTEXATTRIB2SNVPROC) (GLuint index, GLshort x, GLshort y);
typedef void (APIENTRY * PFNGLVERTEXATTRIB2FNVPROC) (GLuint index, GLfloat x, GLfloat y);
typedef void (APIENTRY * PFNGLVERTEXATTRIB2DNVPROC) (GLuint index, GLdouble x, GLdouble y);
typedef void (APIENTRY * PFNGLVERTEXATTRIB3SNVPROC) (GLuint index, GLshort x, GLshort y, GLshort z);
typedef void (APIENTRY * PFNGLVERTEXATTRIB3FNVPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z);
typedef void (APIENTRY * PFNGLVERTEXATTRIB3DNVPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRY * PFNGLVERTEXATTRIB4SNVPROC) (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (APIENTRY * PFNGLVERTEXATTRIB4FNVPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (APIENTRY * PFNGLVERTEXATTRIB4DNVPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRY * PFNGLVERTEXATTRIB4UBNVPROC) (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
typedef void (APIENTRY * PFNGLVERTEXATTRIB1SVNVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRY * PFNGLVERTEXATTRIB1FVNVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRY * PFNGLVERTEXATTRIB1DVNVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRY * PFNGLVERTEXATTRIB2SVNVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRY * PFNGLVERTEXATTRIB2FVNVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRY * PFNGLVERTEXATTRIB2DVNVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRY * PFNGLVERTEXATTRIB3SVNVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRY * PFNGLVERTEXATTRIB3FVNVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRY * PFNGLVERTEXATTRIB3DVNVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRY * PFNGLVERTEXATTRIB4SVNVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRY * PFNGLVERTEXATTRIB4FVNVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRY * PFNGLVERTEXATTRIB4DVNVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRY * PFNGLVERTEXATTRIB4UBVNVPROC) (GLuint index, const GLubyte *v);
typedef void (APIENTRY * PFNGLVERTEXATTRIBS1SVNVPROC) (GLuint index, GLsizei n, const GLshort *v);
typedef void (APIENTRY * PFNGLVERTEXATTRIBS1FVNVPROC) (GLuint index, GLsizei n, const GLfloat *v);
typedef void (APIENTRY * PFNGLVERTEXATTRIBS1DVNVPROC) (GLuint index, GLsizei n, const GLdouble *v);
typedef void (APIENTRY * PFNGLVERTEXATTRIBS2SVNVPROC) (GLuint index, GLsizei n, const GLshort *v);
typedef void (APIENTRY * PFNGLVERTEXATTRIBS2FVNVPROC) (GLuint index, GLsizei n, const GLfloat *v);
typedef void (APIENTRY * PFNGLVERTEXATTRIBS2DVNVPROC) (GLuint index, GLsizei n, const GLdouble *v);
typedef void (APIENTRY * PFNGLVERTEXATTRIBS3SVNVPROC) (GLuint index, GLsizei n, const GLshort *v);
typedef void (APIENTRY * PFNGLVERTEXATTRIBS3FVNVPROC) (GLuint index, GLsizei n, const GLfloat *v);
typedef void (APIENTRY * PFNGLVERTEXATTRIBS3DVNVPROC) (GLuint index, GLsizei n, const GLdouble *v);
typedef void (APIENTRY * PFNGLVERTEXATTRIBS4SVNVPROC) (GLuint index, GLsizei n, const GLshort *v);
typedef void (APIENTRY * PFNGLVERTEXATTRIBS4FVNVPROC) (GLuint index, GLsizei n, const GLfloat *v);
typedef void (APIENTRY * PFNGLVERTEXATTRIBS4DVNVPROC) (GLuint index, GLsizei n, const GLdouble *v);
typedef void (APIENTRY * PFNGLVERTEXATTRIBS4UBVNVPROC) (GLuint index, GLsizei n, const GLubyte *v);

#endif /* GL_NV_vertex_program */

/*-------------------------------------------------------------------*/
/*------------NV_FENCE-----------------------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_NV_fence
#define GL_NV_fance 1

#define GL_ALL_COMPLETED_NV                                     0x84F2
#define GL_FENCE_STATUS_NV                                      0x84F3
#define GL_FENCE_CONDITION_NV                                   0x84F4

#ifdef __PROTOTYPE__

extern void APIENTRY glGenFencesNV(GLsizei n, GLuint *fences);
extern void APIENTRY glDeleteFencesNV(GLsizei n, const GLuint *fences);
extern void APIENTRY glSetFenceNV(GLuint fence, GLenum condition);
extern GLboolean APIENTRY glTestFenceNV(GLuint fence);
extern void APIENTRY glFinishFenceNV(GLuint fence);
extern GLboolean APIENTRY glIsFenceNV(GLuint fence);
extern void APIENTRY glGetFenceivNV(GLuint fence, GLenum pname, GLint *params);

#endif /* __PROTOTYPE__ */

typedef void (APIENTRY * PFNGLGENFENCESNVPROC) (GLsizei n, GLuint *fences);
typedef void (APIENTRY * PFNGLDELETEFENCESNVPROC) (GLsizei n, const GLuint *fences);
typedef void (APIENTRY * PFNGLSETFENCENVPROC) (GLuint fence, GLenum condition);
typedef GLboolean (APIENTRY * PFNGLTESTFENCENVPROC) (GLuint fence);
typedef void (APIENTRY * PFNGLFINISHFENCENVPROC) (GLuint fence);
typedef GLboolean (APIENTRY * PFNGLISFENCENVPROC) (GLuint fence);
typedef void (APIENTRY * PFNGLGETFENCEIVNVPROC) (GLuint fence, GLenum pname, GLint *params);

#endif /* GL_NV_fence */

/*-------------------------------------------------------------------*/
/*------------NV_TEXTURE_SHADER2-------------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_NV_texture_shader2
#define GL_NV_texture_shader2

#define GL_DOT_PRODUCT_TEXTURE_3D_NV                            0x86EF
#define GL_HILO_NV                                              0x86F4
#define GL_DSDT_NV                                              0x86F5
#define GL_DSDT_MAG_NV                                          0x86F6
#define GL_DSDT_MAG_VIB_NV                                      0x86F7
#define GL_UNSIGNED_INT_S8_S8_8_8_NV                            0x86DA
#define GL_UNSIGNED_INT_8_8_S8_S8_REV_NV                        0x86DB
#define GL_SIGNED_RGBA_NV                                       0x86FB
#define GL_SIGNED_RGBA8_NV                                      0x86FC
#define GL_SIGNED_RGB_NV                                        0x86FE
#define GL_SIGNED_RGB8_NV                                       0x86FF
#define GL_SIGNED_LUMINANCE_NV                                  0x8701
#define GL_SIGNED_LUMINANCE8_NV                                 0x8702
#define GL_SIGNED_LUMINANCE_ALPHA_NV                            0x8703
#define GL_SIGNED_LUMINANCE8_ALPHA8_NV                          0x8704
#define GL_SIGNED_ALPHA_NV                                      0x8705
#define GL_SIGNED_ALPHA8_NV                                     0x8706
#define GL_SIGNED_INTENSITY_NV                                  0x8707
#define GL_SIGNED_INTENSITY8_NV                                 0x8708
#define GL_SIGNED_RGB_UNSIGNED_ALPHA_NV                         0x870C
#define GL_SIGNED_RGB8_UNSIGNED_ALPHA8_NV                       0x870D
#define GL_HILO16_NV                                            0x86F8
#define GL_SIGNED_HILO_NV                                       0x86F9
#define GL_SIGNED_HILO16_NV                                     0x86FA
#define GL_DSDT8_NV                                             0x8709
#define GL_DSDT8_MAG8_NV                                        0x870A
#define GL_DSDT_MAG_INTENSITY_NV                                0x86DC
#define GL_DSDT8_MAG8_INTENSITY8_NV                             0x870B 

#endif /* GL_NV_texture_shader2 */

/*-------------------------------------------------------------------*/
/*------------NV_BLEND_SQUARE----------------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_NV_blend_square
#define GL_NV_blend_square 1

#endif /* GL_NV_blend_square */

/*-------------------------------------------------------------------*/
/*------------NV_LIGHT_MAX_EXPONENT----------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_NV_light_max_exponent
#define GL_NV_light_max_exponent 1

#define GL_MAX_SHININESS_NV                                     0x8504
#define GL_MAX_SPOT_EXPONENT_NV                                 0x8505

#endif /* GL_NV_light_max_exponent */

/*-------------------------------------------------------------------*/
/*------------NV_PACKED_DEPTH_STENCIL--------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_NV_packed_depth_stencil
#define GL_NV_packed_depth_stencil 1

#define GL_DEPTH_STENCIL_NV                                     0x84F9
#define GL_UNSIGNED_INT_24_8_NV                                 0x84FA

#endif /* GL_NV_packed_depth_stencil */

/*-------------------------------------------------------------------*/
/*------------NV_REGISTER_COMBINERS2---------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_NV_register_combiners2
#define GL_NV_register_combiners2

#define GL_PER_STAGE_CONSTANTS_NV                               0x8535

#ifdef __PROTOTYPE__

extern void APIENTRY glCombinerStageParameterfvNV(GLenum stage, GLenum pname, const GLfloat *params);
extern void APIENTRY glGetCombinerStageParameterfvNV(GLenum stage, GLenum pname, GLfloat *params);

#endif /* __PROTOTYPE__ */

typedef void (APIENTRY * PFNGLCOMBINERSTAGEPARAMETERFVNVPROC) (GLenum stage, GLenum pname, const GLfloat *params);
typedef void (APIENTRY * PFNGLGETCOMBINERSTAGEPARAMETERFVNVPROC) (GLenum stage, GLenum pname, GLfloat *params);

#endif /* GL_NV_register_combiners2 */

/*-------------------------------------------------------------------*/
/*------------EXT_ABGR-----------------------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_EXT_abgr
#define GL_EXT_abgr 1

#define GL_ABGR_EXT                                             0x8000

#endif /* GL_EXT_abgr */

/*-------------------------------------------------------------------*/
/*------------EXT_STENCIL_WRAP---------------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_EXT_stencil_wrap
#define GL_EXT_stencil_wrap 1

#define GL_INCR_WRAP_EXT             0x8507
#define GL_DECR_WRAP_EXT             0x8508

#endif /* GL_EXT_stencil_wrap */

/*-------------------------------------------------------------------*/
/*------------EXT_TEXTURE_LOD_BIAS-----------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_EXT_texture_lod_bias
#define GL_EXT_texture_lod_bias 1

#define GL_TEXTURE_FILTER_CONTROL_EXT                           0x8500
#define GL_TEXTURE_LOD_BIAS_EXT                                 0x8501
#define GL_MAX_TEXTURE_LOD_BIAS_EXT                             0x84FD

#endif /* GL_EXT_texture_lod_bias */

/*-------------------------------------------------------------------*/
/*------------NV_EVALUATORS------------------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_NV_evaluators
#define GL_NV_evaluators 1

#define GL_EVAL_2D_NV                                           0x86C0
#define GL_EVAL_TRIANGULAR_2D_NV                                0x86C1
#define GL_MAP_TESSELLATION_NV                                  0x86C2
#define GL_MAP_ATTRIB_U_ORDER_NV                                0x86C3
#define GL_MAP_ATTRIB_V_ORDER_NV                                0x86C4
#define GL_EVAL_FRACTIONAL_TESSELLATION_NV                      0x86C5
#define GL_EVAL_VERTEX_ATTRIB0_NV                               0x86C6
#define GL_EVAL_VERTEX_ATTRIB1_NV                               0x86C7
#define GL_EVAL_VERTEX_ATTRIB2_NV                               0x86C8
#define GL_EVAL_VERTEX_ATTRIB3_NV                               0x86C9
#define GL_EVAL_VERTEX_ATTRIB4_NV                               0x86CA
#define GL_EVAL_VERTEX_ATTRIB5_NV                               0x86CB
#define GL_EVAL_VERTEX_ATTRIB6_NV                               0x86CC
#define GL_EVAL_VERTEX_ATTRIB7_NV                               0x86CD
#define GL_EVAL_VERTEX_ATTRIB8_NV                               0x86CE
#define GL_EVAL_VERTEX_ATTRIB9_NV                               0x86CF
#define GL_EVAL_VERTEX_ATTRIB10_NV                              0x86D0
#define GL_EVAL_VERTEX_ATTRIB11_NV                              0x86D1
#define GL_EVAL_VERTEX_ATTRIB12_NV                              0x86D2
#define GL_EVAL_VERTEX_ATTRIB13_NV                              0x86D3
#define GL_EVAL_VERTEX_ATTRIB14_NV                              0x86D4
#define GL_EVAL_VERTEX_ATTRIB15_NV                              0x86D5
#define GL_MAX_MAP_TESSELLATION_NV                              0x86D6
#define GL_MAX_RATIONAL_EVAL_ORDER_NV                           0x86D7

#ifdef __PROTOTYPE__

extern void APIENTRY glMapControlPointsNV(GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLint uorder, GLint vorder, GLboolean packed, const GLvoid *points);
extern void APIENTRY glMapParameterivNV(GLenum target, GLenum pname, const GLint *params);
extern void APIENTRY glMapParameterfvNV(GLenum target, GLenum pname, const GLfloat *params);
extern void APIENTRY glGetMapControlPointsNV(GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLboolean packed, GLvoid *points);
extern void APIENTRY glGetMapParameterivNV(GLenum target, GLenum pname, GLint *params);
extern void APIENTRY glGetMapParameterfvNV(GLenum target, GLenum pname, GLfloat *params);
extern void APIENTRY glGetMapAttribParameterivNV(GLenum target, GLuint index, GLenum pname, GLint *params);
extern void APIENTRY glGetMapAttribParameterfvNV(GLenum target, GLuint index, GLenum pname, GLfloat *params);
extern void APIENTRY glEvalMapsNV(GLenum target, GLenum mode);

#endif /* __PROTOTYPE__ */

typedef void (APIENTRY * PFNGLMAPCONTROLPOINTSNVPROC) (GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLint uorder, GLint vorder, GLboolean packed, const GLvoid *points);
typedef void (APIENTRY * PFNGLMAPPARAMETERIVNVPROC) (GLenum target, GLenum pname, const GLint *params);
typedef void (APIENTRY * PFNGLMAPPARAMETERFVNVPROC) (GLenum target, GLenum pname, const GLfloat *params);
typedef void (APIENTRY * PFNGLGETMAPCONTROLPOINTSNVPROC) (GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLboolean packed, GLvoid *points);
typedef void (APIENTRY * PFNGLGETMAPPARAMETERIVNVPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRY * PFNGLGETMAPPARAMETERFVNVPROC) (GLenum target, GLenum pname, GLfloat *params);
typedef void (APIENTRY * PFNGLGETMAPATTRIBPARAMETERIVNVPROC) (GLenum target, GLuint index, GLenum pname, GLint *params);
typedef void (APIENTRY * PFNGLGETMAPATTRIBPARAMETERFVNVPROC) (GLenum target, GLuint index, GLenum pname, GLfloat *params);
typedef void (APIENTRY * PFNGLEVALMAPSNVPROC) (GLenum target, GLenum mode);

#endif /* GL_NV_evaluators */

/*-------------------------------------------------------------------*/
/*------------NV_COPY_DEPTH_TO_COLOR---------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_NV_copy_depth_to_color
#define GL_NV_copy_depth_to_color 1

#define GL_DEPTH_STENCIL_TO_RGBA_NV                             0x886E
#define GL_DEPTH_STENCIL_TO_BGRA_NV                             0x886F

#endif /* GL_NV_copy_depth_to_color */

/*-------------------------------------------------------------------*/
/*------------ATI_PN_TRIANGLES---------------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_ATI_pn_triangles
#define GL_ATI_pn_triangles 1

#define GL_PN_TRIANGLES_ATI                                     0x87F0
#define GL_MAX_PN_TRIANGLES_TESSELATION_LEVEL_ATI               0x87F1
#define GL_PN_TRIANGLES_POINT_MODE_ATI                          0x87F2
#define GL_PN_TRIANGLES_NORMAL_MODE_ATI                         0x87F3
#define GL_PN_TRIANGLES_TESSELATION_LEVEL_ATI                   0x87F4
#define GL_PN_TRIANGLES_POINT_MODE_LINEAR_ATI                   0x87F5
#define GL_PN_TRIANGLES_POINT_MODE_CUBIC_ATI                    0x87F6
#define GL_PN_TRIANGLES_NORMAL_MODE_LINEAR_ATI                  0x87F7
#define GL_PN_TRIANGLES_NORMAL_MODE_QUADRATIC_ATI               0x87F8

#ifdef __PROTOTYPE__

extern void APIENTRY glPNTrianglesiATI(GLenum pname, GLint param);
extern void APIENTRY glPNTrianglesfATI(GLenum pname, GLfloat param);

#endif /* __PROTOTYPE__ */

typedef void (APIENTRY * PFNGLPNTRIANGLESIATIPROC) (GLenum pname, GLint param);
typedef void (APIENTRY * PFNGLPNTRIANGLESFATIPROC) (GLenum pname, GLfloat param);

#endif /* GL_ATI_pn_triangles */

/*-------------------------------------------------------------------*/
/*------------ARB_POINT_PARAMETERS-----------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_ARB_point_parameters
#define GL_ARB_point_parameters 1

#define GL_POINT_SIZE_MIN_ARB                                   0x8126
#define GL_POINT_SIZE_MAX_ARB                                   0x8127
#define GL_POINT_FADE_THRESHOLD_SIZE_ARB                        0x8128
#define GL_POINT_DISTANCE_ATTENUATION_ARB                       0x8129


#ifdef __PROTOTYPE__

extern void APIENTRY glPointParameterfARB(GLenum pname, GLfloat param);
extern void APIENTRY glPointParameterfvARB(GLenum pname, GLfloat *params);

#endif /* __PROTOTYPE __ */

typedef void (APIENTRY * PFNGLPOINTPARAMETERFARBPROC) (GLenum pname, GLfloat param);
typedef void (APIENTRY * PFNGLPOINTPARAMETERFVARBPROC) (GLenum pname, GLfloat *params);

#endif /* GL_ARB_point_parameters */

/*-------------------------------------------------------------------*/
/*------------ARB_TEXTURE_ENV_CROSSBAR-------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_ARB_texture_env_crossbar
#define GL_ARB_texture_env_crossbar 1

#endif

/*-------------------------------------------------------------------*/
/*------------ARB_VERTEX_BLEND---------------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_ARB_vertex_blend
#define GL_ARB_vertex_blend 1

#define GL_MAX_VERTEX_UNITS_ARB                                 0x86A4
#define GL_ACTIVE_VERTEX_UNITS_ARB                              0x86A5
#define GL_WEIGHT_SUM_UNITY_ARB                                 0x86A6      
#define GL_VERTEX_BLEND_ARB                                     0x86A7
#define GL_CURRENT_WEIGHT_ARB                                   0x86A8
#define GL_WEIGHT_ARRAY_TYPE_ARB                                0x86A9
#define GL_WEIGHT_ARRAY_STRIDE_ARB                              0x86AA
#define GL_WEIGHT_ARRAY_SIZE_ARB                                0x86AB
#define GL_WEIGHT_ARRAY_POINTER_ARB                             0x86AC
#define GL_WEIGHT_ARRAY_ARB                                     0x86AD
#define GL_MODELVIEW0_ARB                                       0x1700
#define GL_MODELVIEW1_ARB                                       0x850a
#define GL_MODELVIEW2_ARB                                       0x8722
#define GL_MODELVIEW3_ARB                                       0x8723
#define GL_MODELVIEW4_ARB                                       0x8724
#define GL_MODELVIEW5_ARB                                       0x8725
#define GL_MODELVIEW6_ARB                                       0x8726
#define GL_MODELVIEW7_ARB                                       0x8727
#define GL_MODELVIEW8_ARB                                       0x8728
#define GL_MODELVIEW9_ARB                                       0x8729
#define GL_MODELVIEW10_ARB                                      0x872A
#define GL_MODELVIEW11_ARB                                      0x872B
#define GL_MODELVIEW12_ARB                                      0x872C
#define GL_MODELVIEW13_ARB                                      0x872D
#define GL_MODELVIEW14_ARB                                      0x872E
#define GL_MODELVIEW15_ARB                                      0x872F
#define GL_MODELVIEW16_ARB                                      0x8730
#define GL_MODELVIEW17_ARB                                      0x8731
#define GL_MODELVIEW18_ARB                                      0x8732
#define GL_MODELVIEW19_ARB                                      0x8733
#define GL_MODELVIEW20_ARB                                      0x8734
#define GL_MODELVIEW21_ARB                                      0x8735
#define GL_MODELVIEW22_ARB                                      0x8736
#define GL_MODELVIEW23_ARB                                      0x8737
#define GL_MODELVIEW24_ARB                                      0x8738
#define GL_MODELVIEW25_ARB                                      0x8739
#define GL_MODELVIEW26_ARB                                      0x873A
#define GL_MODELVIEW27_ARB                                      0x873B
#define GL_MODELVIEW28_ARB                                      0x873C
#define GL_MODELVIEW29_ARB                                      0x873D
#define GL_MODELVIEW30_ARB                                      0x873E
#define GL_MODELVIEW31_ARB                                      0x873F


#ifdef __PROTOTYPE__

extern void APIENTRY glWeightbvARB(GLint size, GLbyte *weights);
extern void APIENTRY glWeightsvARB(GLint size, GLshort *weights);
extern void APIENTRY glWeightivARB(GLint size, GLint *weights);
extern void APIENTRY glWeightfvARB(GLint size, GLfloat *weights);
extern void APIENTRY glWeightdvARB(GLint size, GLdouble *weights);
extern void APIENTRY glWeightubvARB(GLint size, GLubyte *weights);
extern void APIENTRY glWeightusvARB(GLint size, GLushort *weights);
extern void APIENTRY glWeightuivARB(GLint size, GLuint *weights);
extern void APIENTRY glWeightPointerARB(GLint size, GLenum type, GLsizei stride, GLvoid *pointer);
extern void APIENTRY glVertexBlendARB(GLint count);

#endif /* __PROTOTYPE__ */

typedef void (APIENTRY * PFNGLWEIGHTBVARBPROC) (GLint size, GLbyte *weights);
typedef void (APIENTRY * PFNGLWEIGHTSVARBPROC) (GLint size, GLshort *weights);
typedef void (APIENTRY * PFNGLWEIGHTIVARBPROC) (GLint size, GLint *weights);
typedef void (APIENTRY * PFNGLWEIGHTFVARBPROC) (GLint size, GLfloat *weights);
typedef void (APIENTRY * PFNGLWEIGHTDVARBPROC) (GLint size, GLdouble *weights);
typedef void (APIENTRY * PFNGLWEIGHTUBVARBPROC) (GLint size, GLubyte *weights);
typedef void (APIENTRY * PFNGLWEIGHTUSVARBPROC) (GLint size, GLushort *weights);
typedef void (APIENTRY * PFNGLWEIGHTUIVARBPROC) (GLint size, GLuint *weights);
typedef void (APIENTRY * PFNGLWEIGHTPOINTERARBPROC) (GLint size, GLenum type, GLsizei stride, GLvoid *pointer);
typedef void (APIENTRY * PFNGLVERTEXBLENDARBPROC) (GLint count);

#endif /* GL_ARB_vertex_blend */

/*-------------------------------------------------------------------*/
/*------------EXT_MULTI_DRAW_ARRAYS----------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_EXT_multi_draw_arrays
#define GL_EXT_multi_draw_arrays 1

#ifdef __PROTOTYPE__

extern void APIENTRY glMultiDrawArraysEXT(GLenum mode, GLint *first, GLsizei *count, GLsizei primcount);
extern void APIENTRY glMultiDrawElementsEXT(GLenum mode, GLsizei *count, GLenum type, const GLvoid **indices, GLsizei primcount);

#endif /* __PROTOTYPE__ */

typedef void (APIENTRY * PFNGLMULTIDRAWARRAYSEXTPROC) (GLenum mode, GLint *first, GLsizei *count, GLsizei primcount);
typedef void (APIENTRY * PFNGLMULTIDRAWELEMENTSEXTPROC) (GLenum mode, GLsizei *count, GLenum type, const GLvoid **indices, GLsizei primcount);

#endif /* GL_EXT_multi_draw_arrays */

/*-------------------------------------------------------------------*/
/*------------ARB_MATRIX_PALETTE-------------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_ARB_matrix_palette
#define GL_ARB_matrix_palette 1

#define GL_MATRIX_PALETTE_ARB                                   0x8840
#define GL_MAX_MATRIX_PALETTE_STACK_DEPTH_ARB                   0x8841
#define GL_MAX_PALETTE_MATRICES_ARB                             0x8842
#define GL_CURRENT_PALETTE_MATRIX_ARB                           0x8843
#define GL_MATRIX_INDEX_ARRAY_ARB                               0x8844
#define GL_CURRENT_MATRIX_INDEX_ARB                             0x8845
#define GL_MATRIX_INDEX_ARRAY_SIZE_ARB                          0x8846
#define GL_MATRIX_INDEX_ARRAY_TYPE_ARB                          0x8847
#define GL_MATRIX_INDEX_ARRAY_STRIDE_ARB                        0x8848
#define GL_MATRIX_INDEX_ARRAY_POINTER_ARB                       0x8849

#ifdef __PROTOTYPE__

extern void APIENTRY glCurrecnPaletteMatrixARB(GLint index);
extern void APIENTRY glMatrixIndexubvARB(GLint size, GLubyte *indices);
extern void APIENTRY glMatrixIndexusvARB(GLint size, GLushort *indices);
extern void APIENTRY glMatrixIndexuivARB(GLint size, GLuint *indices);
extern void APIENTRY glMatrixIndexPointerARB(GLint size, GLenum type, GLsizei stride, GLvoid *pointer);

#endif /* __PROTOTYPE__ */

typedef void (APIENTRY * PFNGLCURRENTPALETTEMATRIXARBPROC) (GLint index);
typedef void (APIENTRY * PFNGLMATRIXINDEXUBVARBPROC) (GLint size, GLubyte *indices);
typedef void (APIENTRY * PFNGLMATRIXINDEXUSVARBPROC) (GLint size, GLushort *indices);
typedef void (APIENTRY * PFNGLMATRIXINDEXUIVARBPROC) (GLint size, GLuint *indices);
typedef void (APIENTRY * PFNGLMATRIXINDEXPOINTERARBPROC) (GLint size, GLenum type, GLsizei stride, GLvoid *pointer);

#endif /* GL_ARB_matrix_palette */

/*-------------------------------------------------------------------*/
/*------------EXT_VERTEX_SHADER--------------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_EXT_vertex_shader
#define GL_EXT_vertex_shader 1

#define GL_VERTEX_SHADER_EXT                                    0x8780
#define GL_VERTEX_SHADER_BINDING_EXT                            0x8781
#define GL_OP_INDEX_EXT                                         0x8782
#define GL_OP_NEGATE_EXT                                        0x8783
#define GL_OP_DOT3_EXT                                          0x8784
#define GL_OP_DOT4_EXT                                          0x8785
#define GL_OP_MUL_EXT                                           0x8786
#define GL_OP_ADD_EXT                                           0x8787
#define GL_OP_MADD_EXT                                          0x8788
#define GL_OP_FRAC_EXT                                          0x8789
#define GL_OP_MAX_EXT                                           0x878A
#define GL_OP_MIN_EXT                                           0x878B
#define GL_OP_SET_GE_EXT                                        0x878C
#define GL_OP_SET_LT_EXT                                        0x878D
#define GL_OP_CLAMP_EXT                                         0x878E
#define GL_OP_FLOOR_EXT                                         0x878F
#define GL_OP_ROUND_EXT                                         0x8790
#define GL_OP_EXP_BASE_2_EXT                                    0x8791
#define GL_OP_LOG_BASE_2_EXT                                    0x8792
#define GL_OP_POWER_EXT                                         0x8793
#define GL_OP_RECIP_EXT                                         0x8794
#define GL_OP_RECIP_SQRT_EXT                                    0x8795
#define GL_OP_SUB_EXT                                           0x8796
#define GL_OP_CROSS_PRODUCT_EXT                                 0x8797
#define GL_OP_MULTIPLY_MATRIX_EXT                               0x8798
#define GL_OP_MOV_EXT                                           0x8799
#define GL_OUTPUT_VERTEX_EXT                                    0x879A
#define GL_OUTPUT_COLOR0_EXT                                    0x879B
#define GL_OUTPUT_COLOR1_EXT                                    0x879C
#define GL_OUTPUT_TEXTURE_COORD0_EXT                            0x879D
#define GL_OUTPUT_TEXTURE_COORD1_EXT                            0x879E
#define GL_OUTPUT_TEXTURE_COORD2_EXT                            0x879F
#define GL_OUTPUT_TEXTURE_COORD3_EXT                            0x87A0
#define GL_OUTPUT_TEXTURE_COORD4_EXT                            0x87A1
#define GL_OUTPUT_TEXTURE_COORD5_EXT                            0x87A2
#define GL_OUTPUT_TEXTURE_COORD6_EXT                            0x87A3
#define GL_OUTPUT_TEXTURE_COORD7_EXT                            0x87A4
#define GL_OUTPUT_TEXTURE_COORD8_EXT                            0x87A5
#define GL_OUTPUT_TEXTURE_COORD9_EXT                            0x87A6
#define GL_OUTPUT_TEXTURE_COORD10_EXT                           0x87A7
#define GL_OUTPUT_TEXTURE_COORD11_EXT                           0x87A8
#define GL_OUTPUT_TEXTURE_COORD12_EXT                           0x87A9
#define GL_OUTPUT_TEXTURE_COORD13_EXT                           0x87AA
#define GL_OUTPUT_TEXTURE_COORD14_EXT                           0x87AB
#define GL_OUTPUT_TEXTURE_COORD15_EXT                           0x87AC
#define GL_OUTPUT_TEXTURE_COORD16_EXT                           0x87AD
#define GL_OUTPUT_TEXTURE_COORD17_EXT                           0x87AE
#define GL_OUTPUT_TEXTURE_COORD18_EXT                           0x87AF
#define GL_OUTPUT_TEXTURE_COORD19_EXT                           0x87B0
#define GL_OUTPUT_TEXTURE_COORD20_EXT                           0x87B1
#define GL_OUTPUT_TEXTURE_COORD21_EXT                           0x87B2
#define GL_OUTPUT_TEXTURE_COORD22_EXT                           0x87B3
#define GL_OUTPUT_TEXTURE_COORD23_EXT                           0x87B4
#define GL_OUTPUT_TEXTURE_COORD24_EXT                           0x87B5
#define GL_OUTPUT_TEXTURE_COORD25_EXT                           0x87B6
#define GL_OUTPUT_TEXTURE_COORD26_EXT                           0x87B7
#define GL_OUTPUT_TEXTURE_COORD27_EXT                           0x87B8
#define GL_OUTPUT_TEXTURE_COORD28_EXT                           0x87B9
#define GL_OUTPUT_TEXTURE_COORD29_EXT                           0x87BA
#define GL_OUTPUT_TEXTURE_COORD30_EXT                           0x87BB
#define GL_OUTPUT_TEXTURE_COORD31_EXT                           0x87BC
#define GL_OUTPUT_FOG_EXT                                       0x87BD
#define GL_SCALAR_EXT                                           0x87BE
#define GL_VECTOR_EXT                                           0x87BF
#define GL_MATRIX_EXT                                           0x87C0
#define GL_VARIANT_EXT                                          0x87C1
#define GL_INVARIANT_EXT                                        0x87C2
#define GL_LOCAL_CONSTANT_EXT                                   0x87C3
#define GL_LOCAL_EXT                                            0x87C4
#define GL_MAX_VERTEX_SHADER_INSTRUCTIONS_EXT                   0x87C5
#define GL_MAX_VERTEX_SHADER_VARIANTS_EXT                       0x87C6
#define GL_MAX_VERTEX_SHADER_INVARIANTS_EXT                     0x87C7
#define GL_MAX_VERTEX_SHADER_LOCAL_CONSTANTS_EXT                0x87C8
#define GL_MAX_VERTEX_SHADER_LOCALS_EXT                         0x87C9
#define GL_MAX_OPTIMIZED_VERTEX_SHADER_INSTRUCTIONS_EXT         0x87CA
#define GL_MAX_OPTIMIZED_VERTEX_SHADER_VARIANTS_EXT             0x87CB
#define GL_MAX_OPTIMIZED_VERTEX_SHADER_INVARIANTS_EXT           0x87CC
#define GL_MAX_OPTIMIZED_VERTEX_SHADER_LOCAL_CONSTANTS_EXT      0x87CD
#define GL_MAX_OPTIMIZED_VERTEX_SHADER_LOCALS_EXT               0x87CE
#define GL_VERTEX_SHADER_INSTRUCTIONS_EXT                       0x87CF
#define GL_VERTEX_SHADER_VARIANTS_EXT                           0x87D0
#define GL_VERTEX_SHADER_INVARIANTS_EXT                         0x87D1
#define GL_VERTEX_SHADER_LOCAL_CONSTANTS_EXT                    0x87D2
#define GL_VERTEX_SHADER_LOCALS_EXT                             0x87D3
#define GL_VERTEX_SHADER_OPTIMIZED_EXT                          0x87D4
#define GL_X_EXT                                                0x87D5
#define GL_Y_EXT                                                0x87D6
#define GL_Z_EXT                                                0x87D7
#define GL_W_EXT                                                0x87D8
#define GL_NEGATIVE_X_EXT                                       0x87D9
#define GL_NEGATIVE_Y_EXT                                       0x87DA
#define GL_NEGATIVE_Z_EXT                                       0x87DB
#define GL_NEGATIVE_W_EXT                                       0x87DC
#define GL_ZERO_EXT                                             0x87DD
#define GL_ONE_EXT                                              0x87DE
#define GL_NEGATIVE_ONE_EXT                                     0x87DF
#define GL_NORMALIZED_RANGE_EXT                                 0x87E0
#define GL_FULL_RANGE_EXT                                       0x87E1
#define GL_CURRENT_VERTEX_EXT                                   0x87E2
#define GL_MVP_MATRIX_EXT                                       0x87E3
#define GL_VARIANT_VALUE_EXT                                    0x87E4
#define GL_VARIANT_DATATYPE_EXT                                 0x87E5
#define GL_VARIANT_ARRAY_STRIDE_EXT                             0x87E6
#define GL_VARIANT_ARRAY_TYPE_EXT                               0x87E7
#define GL_VARIANT_ARRAY_EXT                                    0x87E8
#define GL_VARIANT_ARRAY_POINTER_EXT                            0x87E9
#define GL_INVARIANT_VALUE_EXT                                  0x87EA
#define GL_INVARIANT_DATATYPE_EXT                               0x87EB
#define GL_LOCAL_CONSTANT_VALUE_EXT                             0x87EC
#define GL_LOCAL_CONSTANT_DATATYPE_EXT                          0x87ED

#ifdef __PROTOTYPE__

extern void APIENTRY glBeginVertexShaderEXT();
extern void APIENTRY glEndVertexShaderEXT();
extern void APIENTRY glBindVertexShaderEXT(GLuint id);
extern GLuint APIENTRY glGenVertexShadersEXT(GLuint range);
extern void APIENTRY glDeleteVertexShaderEXT(GLuint id);
extern void APIENTRY glShaderOp1EXT(GLenum op, GLuint res, GLuint arg1);
extern void APIENTRY glShaderOp2EXT(GLenum op, GLuint res, GLuint arg1, GLuint arg2);
extern void APIENTRY glShaderOp3EXT(GLenum op, GLuint res, GLuint arg1, GLuint arg2, GLuint arg3);
extern void APIENTRY glSwizzleEXT(GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW);
extern void APIENTRY glWriteMaskEXT(GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW);
extern void APIENTRY glInsertComponentEXT(GLuint res, GLuint src, GLuint num);
extern void APIENTRY glExtractComponentEXT(GLuint res, GLuint src, GLuint num);
extern GLuint APIENTRY glGenSymbolsEXT(GLenum dataType, GLenum storageType, GLenum range, GLuint components);
extern void APIENTRY glSetInvariantEXT(GLuint id, GLenum type, GLvoid *addr);
extern void APIENTRY glSetLocalConstantEXT(GLuint id, GLenum type, GLvoid *addr);
extern void APIENTRY glVariantbvEXT(GLuint id, GLbyte *addr);
extern void APIENTRY glVariantsvEXT(GLuint id, GLshort *addr);
extern void APIENTRY glVariantivEXT(GLuint id, GLint *addr);
extern void APIENTRY glVariantfvEXT(GLuint id, GLfloat *addr);
extern void APIENTRY glVariantdvEXT(GLuint id, GLdouble *addr);
extern void APIENTRY glVariantubvEXT(GLuint id, GLubyte *addr);
extern void APIENTRY glVariantusvEXT(GLuint id, GLushort *addr);
extern void APIENTRY glVariantuivEXT(GLuint id, GLuint *addr);
extern void APIENTRY glVariantPointerEXT(GLuint id, GLenum type, GLuint stride, GLvoid *addr);
extern void APIENTRY glEnableVariantClientStateEXT(GLuint id);
extern void APIENTRY glDisableVariantClientStateEXT(GLuint id);
extern GLuint APIENTRY glBindLightParameterEXT(GLenum light, GLenum value);
extern GLuint APIENTRY glBindMaterialParameterEXT(GLenum face, GLenum value);
extern GLuint APIENTRY glBindTexGenParameterEXT(GLenum unit, GLenum coord, GLenum value);
extern GLuint APIENTRY glBindTextureUnitParameterEXT(GLenum unit, GLenum value);
extern GLuint APIENTRY glBindParameterEXT(GLenum value);
extern GLboolean APIENTRY glIsVariantEnabledEXT(GLuint id, GLenum cap);
extern void APIENTRY glGetVariantBooleanvEXT(GLuint id, GLenum value, GLboolean *data);
extern void APIENTRY glGetVariantIntegervEXT(GLuint id, GLenum value, GLint *data);
extern void APIENTRY glGetVariantFloatVEXT(GLuint id, GLenum value, GLfloat *data);
extern void APIENTRY glGetVariantPointervEXT(GLuint id, GLenum value, GLvoid **data);
extern void APIENTRY glGetInvariantBooleanvEXT(GLuint id, GLenum value, GLboolean *data);
extern void APIENTRY glGetInvariantIntegervEXT(GLuint id, GLenum value, GLint *data);
extern void APIENTRY glGetInvariantFloatvEXT(GLuint id, GLenum value, GLfloat *data);
extern void APIENTRY glGetLocalConstantBooleanvEXT(GLuint id, GLenum value, GLboolean *data);
extern void APIENTRY glGetLocalConstantIntegervEXT(GLuint id, GLenum value, GLint *data);
extern void APIENTRY glGetLocalConstantFloatvEXT(GLuint id, GLenum value, GLfloat *data);

#endif /* __PROTOTYPE__ */

typedef void (APIENTRY * PFNGLBEGINVERTEXSHADEREXTPROC) (void);
typedef void (APIENTRY * PFNGLENDVERTEXSHADEREXTPROC) (void);
typedef void (APIENTRY * PFNGLBINDVERTEXSHADEREXTPROC) (GLuint id);
typedef GLuint (APIENTRY * PFNGLGENVERTEXSHADERSEXTPROC) (GLuint range);
typedef void (APIENTRY * PFNGLDELETEVERTEXSHADEREXTPROC) (GLuint id);
typedef void (APIENTRY * PFNGLSHADEROP1EXTPROC) (GLenum op, GLuint res, GLuint arg1);
typedef void (APIENTRY * PFNGLSHADEROP2EXTPROC) (GLenum op, GLuint res, GLuint arg1, GLuint arg2);
typedef void (APIENTRY * PFNGLSHADEROP3EXTPROC) (GLenum op, GLuint res, GLuint arg1, GLuint arg2, GLuint arg3);
typedef void (APIENTRY * PFNGLSWIZZLEEXTPROC) (GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW);
typedef void (APIENTRY * PFNGLWRITEMASKEXTPROC) (GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW);
typedef void (APIENTRY * PFNGLINSERTCOMPONENTEXTPROC) (GLuint res, GLuint src, GLuint num);
typedef void (APIENTRY * PFNGLEXTRACTCOMPONENTEXTPROC) (GLuint res, GLuint src, GLuint num);
typedef GLuint (APIENTRY * PFNGLGENSYMBOLSEXTPROC) (GLenum dataType, GLenum storageType, GLenum range, GLuint components);
typedef void (APIENTRY * PFNGLSETINVARIANTEXTPROC) (GLuint id, GLenum type, GLvoid *addr);
typedef void (APIENTRY * PFNGLSETLOCALCONSTANTEXTPROC) (GLuint id, GLenum type, GLvoid *addr);
typedef void (APIENTRY * PFNGLVARIANTBVEXTPROC) (GLuint id, GLbyte *addr);
typedef void (APIENTRY * PFNGLVARIANTSVEXTPROC) (GLuint id, GLshort *addr);
typedef void (APIENTRY * PFNGLVARIANTIVEXTPROC) (GLuint id, GLint *addr);
typedef void (APIENTRY * PFNGLVARIANTFVEXTPROC) (GLuint id, GLfloat *addr);
typedef void (APIENTRY * PFNGLVARIANTDVEXTPROC) (GLuint id, GLdouble *addr);
typedef void (APIENTRY * PFNGLVARIANTUBVEXTPROC) (GLuint id, GLubyte *addr);
typedef void (APIENTRY * PFNGLVARIANTUSVEXTPROC) (GLuint id, GLushort *addr);
typedef void (APIENTRY * PFNGLVARIANTUIVEXTPROC) (GLuint id, GLuint *addr);
typedef void (APIENTRY * PFNGLVARIANTPOINTEREXTPROC) (GLuint id, GLenum type, GLuint stride, GLvoid *addr);
typedef void (APIENTRY * PFNGLENABLEVARIANTCLIENTSTATEEXTPROC) (GLuint id);
typedef void (APIENTRY * PFNGLDISABLEVARIANTCLIENTSTATEEXTPROC) (GLuint id);
typedef GLuint (APIENTRY * PFNGLBINDLIGHTPARAMETEREXTPROC) (GLenum light, GLenum value);
typedef GLuint (APIENTRY * PFNGLBINDMATERIALPARAMETEREXTPROC) (GLenum face, GLenum value);
typedef GLuint (APIENTRY * PFNGLBINDTEXGENPARAMETEREXTPROC) (GLenum unit, GLenum coord, GLenum value);
typedef GLuint (APIENTRY * PFNGLBINDTEXTUREUNITPARAMETEREXTPROC) (GLenum unit, GLenum value);
typedef GLuint (APIENTRY * PFNGLBINDPARAMETEREXTPROC) (GLenum value);
typedef GLboolean (APIENTRY * PFNGLISVARIANTENABLEDEXTPROC) (GLuint id, GLenum cap);
typedef void (APIENTRY * PFNGLGETVARIANTBOOLEANVEXTPROC) (GLuint id, GLenum value, GLboolean *data);
typedef void (APIENTRY * PFNGLGETVARIANTINTEGERVEXTPROC) (GLuint id, GLenum value, GLint *data);
typedef void (APIENTRY * PFNGLGETVARIANTFLOATVEXTPROC) (GLuint id, GLenum value, GLfloat *data);
typedef void (APIENTRY * PFNGLGETVARIANTPOINTERVEXTPROC) (GLuint id, GLenum value, GLvoid **data);
typedef void (APIENTRY * PFNGLGETINVARIANTBOOLEANVEXTPROC) (GLuint id, GLenum value, GLboolean *data);
typedef void (APIENTRY * PFNGLGETINVARIANTINTEGERVEXTPROC) (GLuint id, GLenum value, GLint *data);
typedef void (APIENTRY * PFNGLGETINVARIANTFLOATVEXTPROC) (GLuint id, GLenum value, GLfloat *data);
typedef void (APIENTRY * PFNGLGETLOCALCONSTANTBOOLEANVEXTPROC) (GLuint id, GLenum value, GLboolean *data);
typedef void (APIENTRY * PFNGLGETLOCALCONSTANTINTEGERVEXTPROC) (GLuint id, GLenum value, GLint *data);
typedef void (APIENTRY * PFNGLGETLOCALCONSTANTFLOATVEXTPROC) (GLuint id, GLenum value, GLfloat *data);

#endif /* GL_EXT_vertex_shader */

/*-------------------------------------------------------------------*/
/*------------ATI_ENVMAP_BUMPMAP-------------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_ATI_envmap_bumpmap
#define GL_ATI_envmap_bumpmap 1

#define GL_BUMP_ROT_MATRIX_ATI                                  0x8775
#define GL_BUMP_ROT_MATRIX_SIZE_ATI                             0x8776
#define GL_BUMP_NUM_TEX_UNITS_ATI                               0x8777
#define GL_BUMP_TEX_UNITS_ATI                                   0x8778
#define GL_DUDV_ATI                                             0x8779
#define GL_DU8DV8_ATI                                           0x877A
#define GL_BUMP_ENVMAP_ATI                                      0x877B
#define GL_BUMP_TARGET_ATI                                      0x877C

#ifdef __PROTOTYPE__

extern void APIENTRY glTexBumpParameterivATI(GLenum pname, GLint *param);
extern void APIENTRY glTexBumpParameterfvATI(GLenum pname, GLfloat *param);
extern void APIENTRY glGetTexBumpParameterivATI(GLenum pname, GLint *param);
extern void APIENTRY glGetTexBumpParameterfvATI(GLenum pname, GLfloat *param);

#endif /* __PROTOTYPE__ */

typedef void (APIENTRY * PFNGLTEXBUMPPARAMETERIVATIPROC) (GLenum pname, GLint *param);
typedef void (APIENTRY * PFNGLTEXBUMPPARAMETERFVATIPROC) (GLenum pname, GLfloat *param);
typedef void (APIENTRY * PFNGLGETTEXBUMPPARAMETERIVATIPROC) (GLenum pname, GLint *param);
typedef void (APIENTRY * PFNGLGETTEXBUMPPARAMETERFVATIPROC) (GLenum pname, GLfloat *param);


#endif /* GL_ATI_envmap_bumpmap */

/*-------------------------------------------------------------------*/
/*------------ATI_FRAGMENT_SHADER------------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_ATI_fragment_shader
#define GL_ATI_fragment_shader 1

#define GL_FRAGMENT_SHADER_ATI                                  0x8920
#define GL_REG_0_ATI                                            0x8921
#define GL_REG_1_ATI                                            0x8922
#define GL_REG_2_ATI                                            0x8923
#define GL_REG_3_ATI                                            0x8924
#define GL_REG_4_ATI                                            0x8925
#define GL_REG_5_ATI                                            0x8926
#define GL_REG_6_ATI                                            0x8927
#define GL_REG_7_ATI                                            0x8928
#define GL_REG_8_ATI                                            0x8929
#define GL_REG_9_ATI                                            0x892A
#define GL_REG_10_ATI                                           0x892B
#define GL_REG_11_ATI                                           0x892C
#define GL_REG_12_ATI                                           0x892D
#define GL_REG_13_ATI                                           0x892E
#define GL_REG_14_ATI                                           0x892F
#define GL_REG_15_ATI                                           0x8930
#define GL_REG_16_ATI                                           0x8931
#define GL_REG_17_ATI                                           0x8932
#define GL_REG_18_ATI                                           0x8933
#define GL_REG_19_ATI                                           0x8934
#define GL_REG_20_ATI                                           0x8935
#define GL_REG_21_ATI                                           0x8936
#define GL_REG_22_ATI                                           0x8937
#define GL_REG_23_ATI                                           0x8938
#define GL_REG_24_ATI                                           0x8939
#define GL_REG_25_ATI                                           0x893A
#define GL_REG_26_ATI                                           0x893B
#define GL_REG_27_ATI                                           0x893C
#define GL_REG_28_ATI                                           0x893D
#define GL_REG_29_ATI                                           0x893E
#define GL_REG_30_ATI                                           0x893F
#define GL_REG_31_ATI                                           0x8940
#define GL_CON_0_ATI                                            0x8941
#define GL_CON_1_ATI                                            0x8942
#define GL_CON_2_ATI                                            0x8943
#define GL_CON_3_ATI                                            0x8944
#define GL_CON_4_ATI                                            0x8945
#define GL_CON_5_ATI                                            0x8946
#define GL_CON_6_ATI                                            0x8947
#define GL_CON_7_ATI                                            0x8948
#define GL_CON_8_ATI                                            0x8949
#define GL_CON_9_ATI                                            0x894A
#define GL_CON_10_ATI                                           0x894B
#define GL_CON_11_ATI                                           0x894C
#define GL_CON_12_ATI                                           0x894D
#define GL_CON_13_ATI                                           0x894E
#define GL_CON_14_ATI                                           0x894F
#define GL_CON_15_ATI                                           0x8950
#define GL_CON_16_ATI                                           0x8951
#define GL_CON_17_ATI                                           0x8952
#define GL_CON_18_ATI                                           0x8953
#define GL_CON_19_ATI                                           0x8954
#define GL_CON_20_ATI                                           0x8955
#define GL_CON_21_ATI                                           0x8956
#define GL_CON_22_ATI                                           0x8957
#define GL_CON_23_ATI                                           0x8958
#define GL_CON_24_ATI                                           0x8959
#define GL_CON_25_ATI                                           0x895A
#define GL_CON_26_ATI                                           0x895B
#define GL_CON_27_ATI                                           0x895C
#define GL_CON_28_ATI                                           0x895D
#define GL_CON_29_ATI                                           0x895E
#define GL_CON_30_ATI                                           0x895F
#define GL_CON_31_ATI                                           0x8960
#define GL_MOV_ATI                                              0x8961
#define GL_ADD_ATI                                              0x8963
#define GL_MUL_ATI                                              0x8964
#define GL_SUB_ATI                                              0x8965
#define GL_DOT3_ATI                                             0x8966
#define GL_DOT4_ATI                                             0x8967
#define GL_MAD_ATI                                              0x8968
#define GL_LERP_ATI                                             0x8969
#define GL_CND_ATI                                              0x896A
#define GL_CND0_ATI                                             0x896B
#define GL_DOT2_ADD_ATI                                         0x896C
#define GL_SECONDARY_INTERPOLATOR_ATI                           0x896D
#define GL_NUM_FRAGMENT_REGISTERS_ATI                           0x896E
#define GL_NUM_FRAGMENT_CONSTANTS_ATI                           0x896F
#define GL_NUM_PASSES_ATI                                       0x8970
#define GL_NUM_INSTRUCTIONS_PER_PASS_ATI                        0x8971
#define GL_NUM_INSTRUCTIONS_TOTAL_ATI                           0x8972
#define GL_NUM_INPUT_INTERPOLATOR_COMPONENTS_ATI                0x8973
#define GL_NUM_LOOPBACK_COMPONENTS_ATI                          0x8974
#define GL_COLOR_ALPHA_PAIRING_ATI                              0x8975
#define GL_SWIZZLE_STR_ATI                                      0x8976
#define GL_SWIZZLE_STQ_ATI                                      0x8977
#define GL_SWIZZLE_STR_DR_ATI                                   0x8978
#define GL_SWIZZLE_STQ_DQ_ATI                                   0x8979
#define GL_SWIZZLE_STRQ_ATI                                     0x897A
#define GL_SWIZZLE_STRQ_DQ_ATI                                  0x897B
#define GL_RED_BIT_ATI                                          0x00000001
#define GL_GREEN_BIT_ATI                                        0x00000002
#define GL_BLUE_BIT_ATI                                         0x00000004
#define GL_2X_BIT_ATI                                           0x00000001
#define GL_4X_BIT_ATI                                           0x00000002
#define GL_8X_BIT_ATI                                           0x00000004
#define GL_HALF_BIT_ATI                                         0x00000008
#define GL_QUARTER_BIT_ATI                                      0x00000010
#define GL_EIGHTH_BIT_ATI                                       0x00000020
#define GL_SATURATE_BIT_ATI                                     0x00000040
#define GL_COMP_BIT_ATI                                         0x00000002
#define GL_NEGATE_BIT_ATI                                       0x00000004
#define GL_BIAS_BIT_ATI                                         0x00000008

#ifdef __PROTOTYPE__

extern GLuint APIENTRY glGenFragmentShadersATI(GLuint range);
extern void APIENTRY glBindFragmentShaderATI(GLuint id);
extern void APIENTRY glDeleteFragmentShaderATI(GLuint id);
extern void APIENTRY glBeginFragmentShaderATI(GLvoid);
extern void APIENTRY glEndFragmentShaderATI(GLvoid);
extern void APIENTRY glPassTexCoordATI(GLuint dst, GLuint coord, GLenum swizzle);
extern void APIENTRY glSampleMapATI(GLuint dst, GLuint interp, GLenum swizzle);
extern void APIENTRY glColorFragmentOp1ATI(GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod);
extern void APIENTRY glColorFragmentOp2ATI(GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod);
extern void APIENTRY glColorFragmentOp3ATI(GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod);
extern void APIENTRY glAlphaFragmentOp1ATI(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod);
extern void APIENTRY glAlphaFragmentOp2ATI(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod);
extern void APIENTRY glAlphaFragmentOp3ATI(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod);
extern void APIENTRY glSetFragmentShaderConstantATI(GLuint dst, const GLfloat *value);

#endif /* __PROTOTYPE__ */

typedef GLuint (APIENTRY * PFNGLGENFRAGMENTSHADERSATIPROC)(GLuint range);
typedef void (APIENTRY * PFNGLBINDFRAGMENTSHADERATIPROC)(GLuint id);
typedef void (APIENTRY * PFNGLDELETEFRAGMENTSHADERATIPROC)(GLuint id);
typedef void (APIENTRY * PFNGLBEGINFRAGMENTSHADERATIPROC)(GLvoid);
typedef void (APIENTRY * PFNGLENDFRAGMENTSHADERATIPROC)(GLvoid);
typedef void (APIENTRY * PFNGLPASSTEXCOORDATIPROC)(GLuint dst, GLuint coord, GLenum swizzle);
typedef void (APIENTRY * PFNGLSAMPLEMAPATIPROC)(GLuint dst, GLuint interp, GLenum swizzle);
typedef void (APIENTRY * PFNGLCOLORFRAGMENTOP1ATIPROC)(GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod);
typedef void (APIENTRY * PFNGLCOLORFRAGMENTOP2ATIPROC)(GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod);
typedef void (APIENTRY * PFNGLCOLORFRAGMENTOP3ATIPROC)(GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod);
typedef void (APIENTRY * PFNGLALPHAFRAGMENTOP1ATIPROC)(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod);
typedef void (APIENTRY * PFNGLALPHAFRAGMENTOP2ATIPROC)(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod);
typedef void (APIENTRY * PFNGLALPHAFRAGMENTOP3ATIPROC)(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod);
typedef void (APIENTRY * PFNGLSETFRAGMENTSHADERCONSTANTATIPROC)(GLuint dst, const GLfloat *value);

#endif /* GL_ATI_fragment_shader */

/*-------------------------------------------------------------------*/
/*------------ATI_TEXTURE_MIRROR_ONCE--------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_ATI_texture_mirror_once
#define GL_ATI_texture_mirror_once 1

#define GL_MIRROR_CLAMP_ATI                                     0x8742
#define GL_MIRROR_CLAMP_TO_EDGE_ATI                             0x8743

#endif

/*-------------------------------------------------------------------*/
/*------------ATI_ELEMENT_ARRAY--------------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_ATI_element_array
#define GL_ATI_element_array 1

#define GL_ELEMENT_ARRAY_ATI                                    0x8768
#define GL_ELEMENT_ARRAY_TYPE_ATI                               0x8769
#define GL_ELEMENT_ARRAY_POINTER_ATI                            0x876A

#ifdef __PROTOTYPE__

extern void APIENTRY glElementPointerATI(GLenum type, const GLvoid *pointer);
extern void APIENTRY glDrawElementArrayATI(GLenum mode, GLsizei count);
extern void APIENTRY glDrawRangeElementArrayATI(GLenum mode, GLuint start, GLuint end, GLsizei count);

#endif /* __PROTOTYPE__ */

typedef void (APIENTRY * PFNGLELEMENTPOINTERATIPROC)(GLenum type, const GLvoid *pointer);
typedef void (APIENTRY * PFNGLDRAWELEMENTARRAYATIPROC)(GLenum mode, GLsizei count);
typedef void (APIENTRY * PFNGLDRAWRANGEELEMENTARRAYATIPROC)(GLenum mode, GLuint start, GLuint end, GLsizei count);

#endif /* GL_ATI_element_array */

/*-------------------------------------------------------------------*/
/*------------ATI_VERTEX_STREAMS-------------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_ATI_vertex_streams 
#define GL_ATI_vertex_streams 1

#define GL_MAX_VERTEX_STREAMS_ATI                               0x876B  
#define GL_VERTEX_SOURCE_ATI                                    0x876C
#define GL_VERTEX_STREAM0_ATI                                   0x876D
#define GL_VERTEX_STREAM1_ATI                                   0x876E
#define GL_VERTEX_STREAM2_ATI                                   0x876F
#define GL_VERTEX_STREAM3_ATI                                   0x8770
#define GL_VERTEX_STREAM4_ATI                                   0x8771
#define GL_VERTEX_STREAM5_ATI                                   0x8772
#define GL_VERTEX_STREAM6_ATI                                   0x8773
#define GL_VERTEX_STREAM7_ATI                                   0x8774

#ifdef __PROTOTYPE__

extern void APIENTRY glClientActiveVertexStreamATI(GLenum stream);
extern void APIENTRY glVertexBlendEnviATI(GLenum pname, GLint param);
extern void APIENTRY glVertexBlendEnvfATI(GLenum pname, GLfloat param);
extern void APIENTRY glVertexStream2sATI(GLenum stream, GLshort x, GLshort y);
extern void APIENTRY glVertexStream2svATI(GLenum stream, const GLshort *v);
extern void APIENTRY glVertexStream2iATI(GLenum stream, GLint x, GLint y);
extern void APIENTRY glVertexStream2ivATI(GLenum stream, const GLint *v);
extern void APIENTRY glVertexStream2fATI(GLenum stream, GLfloat x, GLfloat y);
extern void APIENTRY glVertexStream2fvATI(GLenum stream, const GLfloat *v);
extern void APIENTRY glVertexStream2dATI(GLenum stream, GLdouble x, GLdouble y);
extern void APIENTRY glVertexStream2dvATI(GLenum stream, const GLdouble *v);
extern void APIENTRY glVertexStream3sATI(GLenum stream, GLshort x, GLshort y, GLshort z);
extern void APIENTRY glVertexStream3svATI(GLenum stream, const GLshort *v);
extern void APIENTRY glVertexStream3iATI(GLenum stream, GLint x, GLint y, GLint z);
extern void APIENTRY glVertexStream3ivATI(GLenum stream, const GLint *v);
extern void APIENTRY glVertexStream3fATI(GLenum stream, GLfloat x, GLfloat y, GLfloat z);
extern void APIENTRY glVertexStream3fvATI(GLenum stream, const GLfloat *v);
extern void APIENTRY glVertexStream3dATI(GLenum stream, GLdouble x, GLdouble y, GLdouble z);
extern void APIENTRY glVertexStream3dvATI(GLenum stream, const GLdouble *v);
extern void APIENTRY glVertexStream4sATI(GLenum stream, GLshort x, GLshort y, GLshort z, GLshort w);
extern void APIENTRY glVertexStream4svATI(GLenum stream, const GLshort *v);
extern void APIENTRY glVertexStream4iATI(GLenum stream, GLint x, GLint y, GLint z, GLint w);
extern void APIENTRY glVertexStream4ivATI(GLenum stream, const GLint *v);
extern void APIENTRY glVertexStream4fATI(GLenum stream, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
extern void APIENTRY glVertexStream4fvATI(GLenum stream, const GLfloat *v);
extern void APIENTRY glVertexStream4dATI(GLenum stream, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
extern void APIENTRY glVertexStream4dvATI(GLenum stream, const GLdouble *v);
extern void APIENTRY glNormalStream3bATI(GLenum stream, GLbyte x, GLbyte y, GLbyte z);
extern void APIENTRY glNormalStream3bvATI(GLenum stream, const GLbyte *v);
extern void APIENTRY glNormalStream3sATI(GLenum stream, GLshort x, GLshort y, GLshort z);
extern void APIENTRY glNormalStream3svATI(GLenum stream, const GLshort *v);
extern void APIENTRY glNormalStream3iATI(GLenum stream, GLint x, GLint y, GLint z);
extern void APIENTRY glNormalStream3ivATI(GLenum stream, const GLint *v);
extern void APIENTRY glNormalStream3fATI(GLenum stream, GLfloat x, GLfloat y, GLfloat z);
extern void APIENTRY glNormalStream3fvATI(GLenum stream, const GLfloat *v);
extern void APIENTRY glNormalStream3dATI(GLenum stream, GLdouble x, GLdouble y, GLdouble z);
extern void APIENTRY glNormalStream3dvATI(GLenum stream, const GLdouble *v);

#endif /* __PROTOTYPE__ */

typedef void (APIENTRY * PFNGLCLIENTACTIVEVERTEXSTREAMATIPROC) (GLenum stream);
typedef void (APIENTRY * PFNGLVERTEXBLENDENVIATIPROC) (GLenum pname, GLint param);
typedef void (APIENTRY * PFNGLVERTEXBLENDENVFATIPROC) (GLenum pname, GLfloat param);
typedef void (APIENTRY * PFNGLVERTEXSTREAM2SATIPROC) (GLenum stream, GLshort x, GLshort y);
typedef void (APIENTRY * PFNGLVERTEXSTREAM2SVATIPROC) (GLenum stream, const GLshort *v);
typedef void (APIENTRY * PFNGLVERTEXSTREAM2IATIPROC) (GLenum stream, GLint x, GLint y);
typedef void (APIENTRY * PFNGLVERTEXSTREAM2IVATIPROC) (GLenum stream, const GLint *v);
typedef void (APIENTRY * PFNGLVERTEXSTREAM2FATIPROC) (GLenum stream, GLfloat x, GLfloat y);
typedef void (APIENTRY * PFNGLVERTEXSTREAM2FVATIPROC) (GLenum stream, const GLfloat *v);
typedef void (APIENTRY * PFNGLVERTEXSTREAM2DATIPROC) (GLenum stream, GLdouble x, GLdouble y);
typedef void (APIENTRY * PFNGLVERTEXSTREAM2DVATIPROC) (GLenum stream, const GLdouble *v);
typedef void (APIENTRY * PFNGLVERTEXSTREAM3SATIPROC) (GLenum stream, GLshort x, GLshort y, GLshort z);
typedef void (APIENTRY * PFNGLVERTEXSTREAM3SVATIPROC) (GLenum stream, const GLshort *v);
typedef void (APIENTRY * PFNGLVERTEXSTREAM3IATIPROC) (GLenum stream, GLint x, GLint y, GLint z);
typedef void (APIENTRY * PFNGLVERTEXSTREAM3IVATIPROC) (GLenum stream, const GLint *v);
typedef void (APIENTRY * PFNGLVERTEXSTREAM3FATIPROC) (GLenum stream, GLfloat x, GLfloat y, GLfloat z);
typedef void (APIENTRY * PFNGLVERTEXSTREAM3FVATIPROC) (GLenum stream, const GLfloat *v);
typedef void (APIENTRY * PFNGLVERTEXSTREAM3DATIPROC) (GLenum stream, GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRY * PFNGLVERTEXSTREAM3DVATIPROC) (GLenum stream, const GLdouble *v);
typedef void (APIENTRY * PFNGLVERTEXSTREAM4SATIPROC) (GLenum stream, GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (APIENTRY * PFNGLVERTEXSTREAM4SVATIPROC) (GLenum stream, const GLshort *v);
typedef void (APIENTRY * PFNGLVERTEXSTREAM4IATIPROC) (GLenum stream, GLint x, GLint y, GLint z, GLint w);
typedef void (APIENTRY * PFNGLVERTEXSTREAM4IVATIPROC) (GLenum stream, const GLint *v);
typedef void (APIENTRY * PFNGLVERTEXSTREAM4FATIPROC) (GLenum stream, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (APIENTRY * PFNGLVERTEXSTREAM4FVATIPROC) (GLenum stream, const GLfloat *v);
typedef void (APIENTRY * PFNGLVERTEXSTREAM4DATIPROC) (GLenum stream, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRY * PFNGLVERTEXSTREAM4DVATIPROC) (GLenum stream, const GLdouble *v);
typedef void (APIENTRY * PFNGLNORMALSTREAM3BATIPROC) (GLenum stream, GLbyte x, GLbyte y, GLbyte z);
typedef void (APIENTRY * PFNGLNORMALSTREAM3BVATIPROC) (GLenum stream, const GLbyte *v);
typedef void (APIENTRY * PFNGLNORMALSTREAM3SATIPROC) (GLenum stream, GLshort x, GLshort y, GLshort z);
typedef void (APIENTRY * PFNGLNORMALSTREAM3SVATIPROC) (GLenum stream, const GLshort *v);
typedef void (APIENTRY * PFNGLNORMALSTREAM3IATIPROC) (GLenum stream, GLint x, GLint y, GLint z);
typedef void (APIENTRY * PFNGLNORMALSTREAM3IVATIPROC) (GLenum stream, const GLint *v);
typedef void (APIENTRY * PFNGLNORMALSTREAM3FATIPROC) (GLenum stream, GLfloat x, GLfloat y, GLfloat z);
typedef void (APIENTRY * PFNGLNORMALSTREAM3FVATIPROC) (GLenum stream, const GLfloat *v);
typedef void (APIENTRY * PFNGLNORMALSTREAM3DATIPROC) (GLenum stream, GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRY * PFNGLNORMALSTREAM3DVATIPROC) (GLenum stream, const GLdouble *v);

#endif /* GL_ATI_vertex_streams */

/*-------------------------------------------------------------------*/
/*------------ATI_VERTEX_ARRAY_OBJECT--------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_ATI_vertex_array_object
#define GL_ATI_vertex_array_object 1

#define GL_STATIC_ATI                                           0x8760
#define GL_DYNAMIC_ATI                                          0x8761
#define GL_PRESERVE_ATI                                         0x8762
#define GL_DISCARD_ATI                                          0x8763
#define GL_OBJECT_BUFFER_SIZE_ATI                               0x8764
#define GL_OBJECT_BUFFER_USAGE_ATI                              0x8765
#define GL_ARRAY_OBJECT_BUFFER_ATI                              0x8766
#define GL_ARRAY_OBJECT_OFFSET_ATI                              0x8767

#ifdef __PROTOTYPE__

extern GLuint APIENTRY glNewObjectBufferATI(GLsizei size, const GLvoid *pointer, GLenum usage);
extern GLboolean APIENTRY glIsObjectBufferATI(GLuint buffer);
extern void APIENTRY glIpdateObjectBufferATI(GLuint buffer, GLuint offset, GLsizei size, const GLvoid *pointer, GLenum preserve);
extern void APIENTRY glGetObjectBufferfvATI(GLuint buffer, GLenum pname, GLfloat *params);
extern void APIENTRY glGetObjectBufferivATI(GLuint buffer, GLenum pname, GLint *params);
extern void APIENTRY glFreeObjectBufferATI(GLuint buffer);
extern void APIENTRY glArrayObjectATI(GLenum array, GLint size, GLenum type, GLsizei stride, GLuint buffer, GLuint offset);
extern void APIENTRY glGetArrayObjectfvATI(GLenum array, GLenum pname, GLfloat *params);
extern void APIENTRY glGetArrayObjectivATI(GLenum array, GLenum pname, GLint *params);
extern void APIENTRY glVariantArrayObjectATI(GLuint id, GLenum type, GLsizei stride, GLuint buffer, GLuint offset);
extern void APIENTRY glGetVariantArrayObjectfvATI(GLuint id, GLenum pname, GLfloat *params);
extern void APIENTRY glGetVariantArrayObjectivATI(GLuint id, GLenum pname, GLint *params);

#endif /* __PROTOTYPE__ */

typedef GLuint (APIENTRY * PFNGLNEWOBJECTBUFFERATIPROC)(GLsizei size, const GLvoid *pointer, GLenum usage);
typedef GLboolean (APIENTRY * PFNGLISOBJECTBUFFERATIPROC)(GLuint buffer);
typedef void (APIENTRY * PFNGLUPDATEOBJECTBUFFERATIPROC)(GLuint buffer, GLuint offset, GLsizei size, const GLvoid *pointer, GLenum preserve);
typedef void (APIENTRY * PFNGLGETOBJECTBUFFERFVATIPROC)(GLuint buffer, GLenum pname, GLfloat *params);
typedef void (APIENTRY * PFNGLGETOBJECTBUFFERIVATIPROC)(GLuint buffer, GLenum pname, GLint *params);
typedef void (APIENTRY * PFNGLFREEOBJECTBUFFERATIPROC)(GLuint buffer);
typedef void (APIENTRY * PFNGLARRAYOBJECTATIPROC)(GLenum array, GLint size, GLenum type, GLsizei stride, GLuint buffer, GLuint offset);
typedef void (APIENTRY * PFNGLGETARRAYOBJECTFVATIPROC)(GLenum array, GLenum pname, GLfloat *params);
typedef void (APIENTRY * PFNGLGETARRAYOBJECTIVATIPROC)(GLenum array, GLenum pname, GLint *params);
typedef void (APIENTRY * PFNGLVARIANTARRAYOBJECTATIPROC)(GLuint id, GLenum type, GLsizei stride, GLuint buffer, GLuint offset);
typedef void (APIENTRY * PFNGLGETVARIANTARRAYOBJECTFVATIPROC)(GLuint id, GLenum pname, GLfloat *params);
typedef void (APIENTRY * PFNGLGETVARIANTARRAYOBJECTIVATIPROC)(GLuint id, GLenum pname, GLint *params);

#endif /* GL_ATI_vertex_array_object */

/*-------------------------------------------------------------------*/
/*------------HP_OCCLUSION_TEST--------------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_HP_occlusion_test
#define GL_HP_occlusion_test 1

#define GL_OCCLUSION_TEST_HP                                    0x8165;
#define GL_OCCLUSION_TEST_RESULT_HP                             0x8166;

#endif /* GL_HP_occlusion_test */

/*-------------------------------------------------------------------*/
/*------------ATIX_POINT_SPRITES-------------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_ATIX_point_sprites
#define GL_ATIX_point_sprites 1

#define GL_TEXTURE_POINT_MODE_ATIX                              0x60b0
#define	GL_TEXTURE_POINT_ONE_COORD_ATIX                         0x60b1
#define	GL_TEXTURE_POINT_SPRITE_ATIX                            0x60b2
#define GL_POINT_SPRITE_CULL_MODE_ATIX                          0x60b3
#define GL_POINT_SPRITE_CULL_CENTER_ATIX                        0x60b4
#define GL_POINT_SPRITE_CULL_CLIP_ATIX                          0x60b5

#endif /* GL_ATIX_point_sprites */

/*-------------------------------------------------------------------*/
/*------------ATIX_TEXTURE_ENV_ROUTE---------------------------------*/
/*-------------------------------------------------------------------*/

#ifndef GL_ATIX_texture_env_route
#define GL_ATIX_texture_env_route 1

#define GL_SECONDARY_COLOR_ATIX                                 0x8747
#define GL_TEXTURE_OUTPUT_RGB_ATIX                              0x8748
#define GL_TEXTURE_OUTPUT_ALPHA_ATIX                            0x8749

#endif /* GL_ATIX_texture_env_route */

/*-------------------------------------------------------------------*/
/*------------END EXTENSIONS-----------------------------------------*/
/*-------------------------------------------------------------------*/

/* helper stuff */

/* I use int here because C does not know bool */

struct _ExtensionTypes
{
    int ARB_imaging;
    int ARB_matrix_palette;
    int ARB_multisample;
    int ARB_multitexture;
    int ARB_point_parameters;
    int ARB_texture_compression;
    int ARB_texture_env_add;
    int ARB_texture_env_dot3;
    int ARB_texture_env_combine;
    int ARB_texture_env_crossbar;
    int ARB_texture_border_clamp;
    int ARB_texture_cube_map;
    int ARB_transpose_matrix;
    int ARB_vertex_blend;
    int EXT_abgr;
    int EXT_compiled_vertex_array;
    int EXT_fog_coord;
    int EXT_multi_draw_arrays;
    int EXT_point_parameters;
    int EXT_secondary_color;
    int EXT_stencil_wrap;
    int EXT_texture_filter_anisotropic;
    int EXT_texture_lod_bias;
    int EXT_vertex_shader;
    int EXT_vertex_weighting;
    int ATI_element_array;
    int ATI_envmap_bumpmap;
    int ATI_fragment_shader;
    int ATI_pn_triangles;
    int ATI_texture_mirror_once;
    int ATI_vertex_array_object;
    int ATI_vertex_streams;
    int ATIX_point_sprites;
    int ATIX_texture_env_route;
    int HP_occlusion_test;
    int NV_blend_square;
    int NV_copy_depth_to_color;
    int NV_evaluators;
    int NV_fence;
    int NV_fog_distance;
    int NV_light_max_exponent;
    int NV_vertex_program;
    int NV_packed_depth_stencil;
    int NV_register_combiners;
    int NV_register_combiners2;
    int NV_texgen_reflection;
    int NV_texture_env_combine4;
    int NV_texture_rectangle;
    int NV_texture_shader;
    int NV_texture_shader2;
    int NV_vertex_array_range;
    int NV_vertex_array_range2;
    int SGIS_generate_mipmap;
    int SGIX_shadow;
    int SGIX_depth_texture;
    int OpenGL12;
    int OpenGL13;
};
typedef struct _ExtensionTypes  ExtensionTypes;

/* extern struct ExtensionTypes SupportedExtensions; */

/* initializes everything, call this right after the rc is created. the function returns 0 if successful */


/* helper functions */

/* initializes everything, call this right after the rc is created. the function returns 0 if successful */

int glInitExtensionLibrary( ExtensionTypes * info );
/*int glInitialize();*/

/* helpers end */

/*-------------------------------------------------------------------*/
/*------------FUNCTIONS_VARIABLES------------------------------------*/
/*-------------------------------------------------------------------*/


#ifndef __PROTOTYPE__

/* opengl 1.2 */

#ifdef _WIN32

extern PFNGLBLENDCOLORPROC glBlendColor;
extern PFNGLBLENDEQUATIONPROC glBlendEquation;
extern PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElements;
extern PFNGLCOLORTABLEPROC glColorTable;
extern PFNGLCOLORTABLEPARAMETERFVPROC glColorTableParameterfv;
extern PFNGLCOLORTABLEPARAMETERIVPROC glColorTableParameteriv;
extern PFNGLCOPYCOLORTABLEPROC glCopyColorTable;
extern PFNGLGETCOLORTABLEPROC glGetColorTable;
extern PFNGLGETCOLORTABLEPARAMETERFVPROC glGetColorTableParameterfv;
extern PFNGLGETCOLORTABLEPARAMETERIVPROC glGetColorTableParameteriv;
extern PFNGLCOLORSUBTABLEPROC glColorSubTable;
extern PFNGLCOPYCOLORSUBTABLEPROC glCopyColorSubTable;
extern PFNGLCONVOLUTIONFILTER1DPROC glConvolutionFilter1D;
extern PFNGLCONVOLUTIONFILTER2DPROC glConvolutionFilter2D;
extern PFNGLCONVOLUTIONPARAMETERFPROC glConvolutionParameterf;
extern PFNGLCONVOLUTIONPARAMETERFVPROC glConvolutionParameterfv;
extern PFNGLCONVOLUTIONPARAMETERIPROC glConvolutionParameteri;
extern PFNGLCONVOLUTIONPARAMETERIVPROC glConvolutionParameteriv;
extern PFNGLCOPYCONVOLUTIONFILTER1DPROC glCopyConvolutionFilter1D;
extern PFNGLCOPYCONVOLUTIONFILTER2DPROC glCopyConvolutionFilter2D;
extern PFNGLGETCONVOLUTIONFILTERPROC glGetConvolutionFilter;
extern PFNGLGETCONVOLUTIONPARAMETERFVPROC glGetConvolutionParameterfv;
extern PFNGLGETCONVOLUTIONPARAMETERIVPROC glGetConvolutionParameteriv;
extern PFNGLGETSEPARABLEFILTERPROC glGetSeparableFilter;
extern PFNGLSEPARABLEFILTER2DPROC glSeparableFilter2D;
extern PFNGLGETHISTOGRAMPROC glGetHistogram;
extern PFNGLGETHISTOGRAMPARAMETERFVPROC glGetHistogramParameterfv;
extern PFNGLGETHISTOGRAMPARAMETERIVPROC glGetHistogramParameteriv;
extern PFNGLGETMINMAXPROC glGetMinmax;
extern PFNGLGETMINMAXPARAMETERFVPROC glGetMinmaxParameterfv;
extern PFNGLGETMINMAXPARAMETERIVPROC glGetMinmaxParameteriv;
extern PFNGLHISTOGRAMPROC glHistogram;
extern PFNGLMINMAXPROC glMinmax;
extern PFNGLRESETHISTOGRAMPROC glResetHistogram;
extern PFNGLRESETMINMAXPROC glResetMinmax;
extern PFNGLTEXIMAGE3DPROC glTexImage3D;
extern PFNGLTEXSUBIMAGE3DPROC glTexSubImage3D;
extern PFNGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3D;

/* opengl 1.3 */

extern PFNGLACTIVETEXTUREPROC glActiveTexture;
extern PFNGLCLIENTACTIVETEXTUREPROC glClientActiveTexture;
extern PFNGLMULTITEXCOORD1DPROC glMultiTexCoord1d;
extern PFNGLMULTITEXCOORD1DVPROC glMultiTexCoord1dv;
extern PFNGLMULTITEXCOORD1FPROC glMultiTexCoord1f;
extern PFNGLMULTITEXCOORD1FVPROC glMultiTexCoord1fv;
extern PFNGLMULTITEXCOORD1IPROC glMultiTexCoord1i;
extern PFNGLMULTITEXCOORD1IVPROC glMultiTexCoord1iv;
extern PFNGLMULTITEXCOORD1SPROC glMultiTexCoord1s;
extern PFNGLMULTITEXCOORD1SVPROC glMultiTexCoord1sv;

extern PFNGLMULTITEXCOORD2DPROC glMultiTexCoord2d;
extern PFNGLMULTITEXCOORD2DVPROC glMultiTexCoord2dv;
extern PFNGLMULTITEXCOORD2FPROC glMultiTexCoord2f;
extern PFNGLMULTITEXCOORD2FVPROC glMultiTexCoord2fv;
extern PFNGLMULTITEXCOORD2IPROC glMultiTexCoord2i;
extern PFNGLMULTITEXCOORD2IVPROC glMultiTexCoord2iv;
extern PFNGLMULTITEXCOORD2SPROC glMultiTexCoord2s;
extern PFNGLMULTITEXCOORD2SVPROC glMultiTexCoord2sv;

extern PFNGLMULTITEXCOORD3DPROC glMultiTexCoord3d;
extern PFNGLMULTITEXCOORD3DVPROC glMultiTexCoord3dv;
extern PFNGLMULTITEXCOORD3FPROC glMultiTexCoord3f;
extern PFNGLMULTITEXCOORD3FVPROC glMultiTexCoord3fv;
extern PFNGLMULTITEXCOORD3IPROC glMultiTexCoord3i;
extern PFNGLMULTITEXCOORD3IVPROC glMultiTexCoord3iv;
extern PFNGLMULTITEXCOORD3SPROC glMultiTexCoord3s;
extern PFNGLMULTITEXCOORD3SVPROC glMultiTexCoord3sv;

extern PFNGLMULTITEXCOORD4DPROC glMultiTexCoord4d;
extern PFNGLMULTITEXCOORD4DVPROC glMultiTexCoord4dv;
extern PFNGLMULTITEXCOORD4FPROC glMultiTexCoord4f;
extern PFNGLMULTITEXCOORD4FVPROC glMultiTexCoord4fv;
extern PFNGLMULTITEXCOORD4IPROC glMultiTexCoord4i;
extern PFNGLMULTITEXCOORD4IVPROC glMultiTexCoord4iv;
extern PFNGLMULTITEXCOORD4SPROC glMultiTexCoord4s;
extern PFNGLMULTITEXCOORD4SVPROC glMultiTexCoord4sv;


extern PFNGLLOADTRANSPOSEMATRIXFPROC glLoadTransposeMatrixf;
extern PFNGLLOADTRANSPOSEMATRIXDPROC glLoadTransposeMatrixd;
extern PFNGLMULTTRANSPOSEMATRIXFPROC glMultTransposeMatrixf;
extern PFNGLMULTTRANSPOSEMATRIXDPROC glMultTransposeMatrixd;

extern PFNGLCOMPRESSEDTEXIMAGE3DPROC glCompressedTexImage3D;
extern PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D;
extern PFNGLCOMPRESSEDTEXIMAGE1DPROC glCompressedTexImage1D;

extern PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glCompressedTexSubImage3D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glCompressedTexSubImage1D;

extern PFNGLGETCOMPRESSEDTEXIMAGEPROC glGetCompressedTexImage;

extern PFNGLSAMPLECOVERAGEPROC glSampleCoverage;

/* ARB_multitexture */

extern PFNGLACTIVETEXTUREPROC glActiveTextureARB;
extern PFNGLCLIENTACTIVETEXTUREPROC glClientActiveTextureARB;
extern PFNGLMULTITEXCOORD1DPROC glMultiTexCoord1dARB;
extern PFNGLMULTITEXCOORD1DVPROC glMultiTexCoord1dvARB;
extern PFNGLMULTITEXCOORD1FPROC glMultiTexCoord1fARB;
extern PFNGLMULTITEXCOORD1FVPROC glMultiTexCoord1fvARB;
extern PFNGLMULTITEXCOORD1IPROC glMultiTexCoord1iARB;
extern PFNGLMULTITEXCOORD1IVPROC glMultiTexCoord1ivARB;
extern PFNGLMULTITEXCOORD1SPROC glMultiTexCoord1sARB;
extern PFNGLMULTITEXCOORD1SVPROC glMultiTexCoord1svARB;

extern PFNGLMULTITEXCOORD2DPROC glMultiTexCoord2dARB;
extern PFNGLMULTITEXCOORD2DVPROC glMultiTexCoord2dvARB;
extern PFNGLMULTITEXCOORD2FPROC glMultiTexCoord2fARB;
extern PFNGLMULTITEXCOORD2FVPROC glMultiTexCoord2fvARB;
extern PFNGLMULTITEXCOORD2IPROC glMultiTexCoord2iARB;
extern PFNGLMULTITEXCOORD2IVPROC glMultiTexCoord2ivARB;
extern PFNGLMULTITEXCOORD2SPROC glMultiTexCoord2sARB;
extern PFNGLMULTITEXCOORD2SVPROC glMultiTexCoord2svARB;

extern PFNGLMULTITEXCOORD3DPROC glMultiTexCoord3dARB;
extern PFNGLMULTITEXCOORD3DVPROC glMultiTexCoord3dvARB;
extern PFNGLMULTITEXCOORD3FPROC glMultiTexCoord3fARB;
extern PFNGLMULTITEXCOORD3FVPROC glMultiTexCoord3fvARB;
extern PFNGLMULTITEXCOORD3IPROC glMultiTexCoord3iARB;
extern PFNGLMULTITEXCOORD3IVPROC glMultiTexCoord3ivARB;
extern PFNGLMULTITEXCOORD3SPROC glMultiTexCoord3sARB;
extern PFNGLMULTITEXCOORD3SVPROC glMultiTexCoord3svARB;

extern PFNGLMULTITEXCOORD4DPROC glMultiTexCoord4dARB;
extern PFNGLMULTITEXCOORD4DVPROC glMultiTexCoord4dvARB;
extern PFNGLMULTITEXCOORD4FPROC glMultiTexCoord4fARB;
extern PFNGLMULTITEXCOORD4FVPROC glMultiTexCoord4fvARB;
extern PFNGLMULTITEXCOORD4IPROC glMultiTexCoord4iARB;
extern PFNGLMULTITEXCOORD4IVPROC glMultiTexCoord4ivARB;
extern PFNGLMULTITEXCOORD4SPROC glMultiTexCoord4sARB;
extern PFNGLMULTITEXCOORD4SVPROC glMultiTexCoord4svARB;

#endif /* _WIN32 */

/* ETX_compiled_vertex_array */

extern PFNGLLOCKARRAYSEXTPROC glLockArraysEXT;
extern PFNGLUNLOCKARRAYSEXTPROC glUnlockArraysEXT;

/* EXT_secondary_color */

extern PFNGLSECONDARYCOLOR3BEXTPROC glSecondaryColor3bEXT;
extern PFNGLSECONDARYCOLOR3BVEXTPROC glSecondaryColor3bvEXT;
extern PFNGLSECONDARYCOLOR3DEXTPROC glSecondaryColor3dEXT;
extern PFNGLSECONDARYCOLOR3DVEXTPROC glSecondaryColor3dvEXT;
extern PFNGLSECONDARYCOLOR3FEXTPROC glSecondaryColor3fEXT;
extern PFNGLSECONDARYCOLOR3FVEXTPROC glSecondaryColor3fvEXT;
extern PFNGLSECONDARYCOLOR3IEXTPROC glSecondaryColor3iEXT;
extern PFNGLSECONDARYCOLOR3IVEXTPROC glSecondaryColor3ivEXT;
extern PFNGLSECONDARYCOLOR3SEXTPROC glSecondaryColor3sEXT;
extern PFNGLSECONDARYCOLOR3SVEXTPROC glSecondaryColor3svEXT;
extern PFNGLSECONDARYCOLOR3UBEXTPROC glSecondaryColor3ubEXT;
extern PFNGLSECONDARYCOLOR3UBVEXTPROC glSecondaryColor3ubvEXT;
extern PFNGLSECONDARYCOLOR3UIEXTPROC glSecondaryColor3uiEXT;
extern PFNGLSECONDARYCOLOR3UIVEXTPROC glSecondaryColor3uivEXT;
extern PFNGLSECONDARYCOLOR3USEXTPROC glSecondaryColor3usEXT;
extern PFNGLSECONDARYCOLOR3USVEXTPROC glSecondaryColor3usvEXT;
extern PFNGLSECONDARYCOLORPOINTEREXTPROC glSecondaryColorPointerEXT;

/* EXT_fog_color */

extern PFNGLFOGCOORDFEXTPROC glFogCoordfEXT;
extern PFNGLFOGCOORDFVEXTPROC glFogCoordfvEXT;
extern PFNGLFOGCOORDDEXTPROC glFogCoorddEXT;
extern PFNGLFOGCOORDDVEXTPROC glFogCoorddvEXT;
extern PFNGLFOGCOORDPOINTEREXTPROC glFogCoordPointerEXT;

/* NV_vertex_array_range */

extern PFNGLFLUSHVERTEXARRAYRANGENVPROC glFlushVertexArrayRangeNV;
extern PFNGLVERTEXARRAYRANGENVPROC glVertexArrayRangeNV;

/* EXT_point_parameters */

extern PFNGLPOINTPARAMETERFEXTPROC glPointParameterfEXT;
extern PFNGLPOINTPARAMETERFVEXTPROC glPointParameterfvEXT;

/* NV_register_combiners */

extern PFNGLCOMBINERPARAMETERFVNVPROC glCombinerParameterfvNV;
extern PFNGLCOMBINERPARAMETERFNVPROC  glCombinerParameterfNV;
extern PFNGLCOMBINERPARAMETERIVNVPROC glCombinerParameterivNV;
extern PFNGLCOMBINERPARAMETERINVPROC glCombinerParameteriNV;
extern PFNGLCOMBINERINPUTNVPROC glCombinerInputNV;
extern PFNGLCOMBINEROUTPUTNVPROC glCombinerOutputNV;
extern PFNGLFINALCOMBINERINPUTNVPROC glFinalCombinerInputNV;
extern PFNGLGETCOMBINERINPUTPARAMETERFVNVPROC glGetCombinerInputParameterfvNV;
extern PFNGLGETCOMBINERINPUTPARAMETERIVNVPROC glGetCombinerInputParameterivNV;
extern PFNGLGETCOMBINEROUTPUTPARAMETERFVNVPROC glGetCombinerOutputParameterfvNV;
extern PFNGLGETCOMBINEROUTPUTPARAMETERIVNVPROC glGetCombinerOutputParameterivNV;
extern PFNGLGETFINALCOMBINERINPUTPARAMETERFVNVPROC glGetFinalCombinerInputParameterfvNV;
extern PFNGLGETFINALCOMBINERINPUTPARAMETERIVNVPROC glGetFinalCombinerInputParameterivNV;

/* EXT_vertex_weighting */

extern PFNGLVERTEXWEIGHTFEXTPROC glVertexWeightfEXT;
extern PFNGLVERTEXWEIGHTFVEXTPROC glVertexWeightfvEXT;
extern PFNGLVERTEXWEIGHTPOINTEREXTPROC glVertexWeightPointerEXT;

/* NV_vertex_program */

extern PFNGLBINDPROGRAMNVPROC glBindProgramNV;
extern PFNGLDELETEPROGRAMSNVPROC glDeleteProgramsNV;
extern PFNGLEXECUTEPROGRAMNVPROC glExecuteProgramNV;
extern PFNGLGENPROGRAMSNVPROC glGenProgramsNV;
extern PFNGLAREPROGRAMSRESIDENTNVPROC glAreProgramsResidentNV;
extern PFNGLREQUESTRESIDENTPROGRAMSNVPROC glRequestResidentProgramsNV;
extern PFNGLGETPROGRAMPARAMETERFVNVPROC glGetProgramParameterfvNV;
extern PFNGLGETPROGRAMPARAMETERDVNVPROC glGetProgramParameterdvNV;
extern PFNGLGETPROGRAMIVNVPROC glGetProgramivNV;
extern PFNGLGETPROGRAMSTRINGNVPROC glGetProgramStringNV;
extern PFNGLGETTRACKMATRIXIVNVPROC glGetTrackMatrixivNV;
extern PFNGLGETVERTEXATTRIBDVNVPROC glGetVertexAttribdvNV;
extern PFNGLGETVERTEXATTRINFVNVPROC glGetVertexAttribfvNV;
extern PFNGLGETVERTEXATTRIBIVNVPROC glGetVertexAttribivNV;
extern PFNGLGETVERTEXATTRIBPOINTERVNVPROC glGetVertexAttribPointervNV;
extern PFNGLISPROGRAMNVPROC glIsProgramNV;
extern PFNGLLOADPROGRAMNVPROC glLoadProgramNV;
extern PFNGLPROGRAMPARAMETER4FNVPROC glProgramParameter4fNV;
extern PFNGLPROGRAMPARAMETER4DNVPROC glProgramParameter4dNV;
extern PFNGLPROGRAMPARAMETER4DVNVPROC glProgramParameter4dvNV;
extern PFNGLPROGRAMPARAMETER4FVNVPROC glProgramParameter4fvNV;
extern PFNGLPROGRAMPARAMETERS4DVNVPROC glProgramParameters4dvNV;
extern PFNGLPROGRAMPARAMETERS4FVNVPROC glProgramParameters4fvNV;
extern PFNGLTRACKMATRIXNVPROC glTrackMatrixNV;
extern PFNGLVERTEXATTRIBPPOINTERNVPROC glVertexAttribPointerNV;
extern PFNGLVERTEXATTRIB1SNVPROC glVertexAttrib1sNV;
extern PFNGLVERTEXATTRIB1FNVPROC glVertexAttrib1fNV;
extern PFNGLVERTEXATTRIB1DNVPROC glVertexAttrib1dNV;
extern PFNGLVERTEXATTRIB2SNVPROC glVertexAttrib2sNV;
extern PFNGLVERTEXATTRIB2FNVPROC glVertexAttrib2fNV;
extern PFNGLVERTEXATTRIB2DNVPROC glVertexAttrib2dNV;
extern PFNGLVERTEXATTRIB3SNVPROC glVertexAttrib3sNV;
extern PFNGLVERTEXATTRIB3FNVPROC glVertexAttrib3fNV;
extern PFNGLVERTEXATTRIB3DNVPROC glVertexAttrib3dNV;
extern PFNGLVERTEXATTRIB4SNVPROC glVertexAttrib4sNV;
extern PFNGLVERTEXATTRIB4FNVPROC glVertexAttrib4fNV;
extern PFNGLVERTEXATTRIB4DNVPROC glVertexAttrib4dNV;
extern PFNGLVERTEXATTRIB4UBNVPROC glVertexAttrib4ubNV;
extern PFNGLVERTEXATTRIB1SVNVPROC glVertexAttrib1svNV;
extern PFNGLVERTEXATTRIB1FVNVPROC glVertexAttrib1fvNV;
extern PFNGLVERTEXATTRIB1DVNVPROC glVertexAttrib1dvNV;
extern PFNGLVERTEXATTRIB2SVNVPROC glVertexAttrib2svNV;
extern PFNGLVERTEXATTRIB2FVNVPROC glVertexAttrib2fvNV;
extern PFNGLVERTEXATTRIB2DVNVPROC glVertexAttrib2dvNV;
extern PFNGLVERTEXATTRIB3SVNVPROC glVertexAttrib3svNV;
extern PFNGLVERTEXATTRIB3FVNVPROC glVertexAttrib3fvNV;
extern PFNGLVERTEXATTRIB3DVNVPROC glVertexAttrib3dvNV;
extern PFNGLVERTEXATTRIB4SVNVPROC glVertexAttrib4svNV;
extern PFNGLVERTEXATTRIB4FVNVPROC glVertexAttrib4fvNV;
extern PFNGLVERTEXATTRIB4DVNVPROC glVertexAttrib4dvNV;
extern PFNGLVERTEXATTRIB4UBVNVPROC glVertexAttrib4ubvNV;
extern PFNGLVERTEXATTRIBS1SVNVPROC glVertexAttribs1svNV;
extern PFNGLVERTEXATTRIBS1FVNVPROC glVertexAttribs1fvNV;
extern PFNGLVERTEXATTRIBS1DVNVPROC glVertexAttribs1dvNV;
extern PFNGLVERTEXATTRIBS2SVNVPROC glVertexAttribs2svNV;
extern PFNGLVERTEXATTRIBS2FVNVPROC glVertexAttribs2fvNV;
extern PFNGLVERTEXATTRIBS2DVNVPROC glVertexAttribs2dvNV;
extern PFNGLVERTEXATTRIBS3SVNVPROC glVertexAttribs3svNV;
extern PFNGLVERTEXATTRIBS3FVNVPROC glVertexAttribs3fvNV;
extern PFNGLVERTEXATTRIBS3DVNVPROC glVertexAttribs3dvNV;
extern PFNGLVERTEXATTRIBS4SVNVPROC glVertexAttribs4svNV;
extern PFNGLVERTEXATTRIBS4FVNVPROC glVertexAttribs4fvNV;
extern PFNGLVERTEXATTRIBS4DVNVPROC glVertexAttribs4dvNV;
extern PFNGLVERTEXATTRIBS4UBVNVPROC glVertexAttribs4ubvNV;

/* NV_fence */

extern PFNGLGENFENCESNVPROC glGenFencesNV;
extern PFNGLDELETEFENCESNVPROC glDeleteFencesNV;
extern PFNGLSETFENCENVPROC glSetFenceNV;
extern PFNGLTESTFENCENVPROC glTestFenceNV;
extern PFNGLFINISHFENCENVPROC glFinishFenceNV;
extern PFNGLISFENCENVPROC glIsFenceNV;
extern PFNGLGETFENCEIVNVPROC glGetFenceivNV;

/* NV_register_combiners2 */

extern PFNGLCOMBINERSTAGEPARAMETERFVNVPROC glCombinerStageParameterfvNV;
extern PFNGLGETCOMBINERSTAGEPARAMETERFVNVPROC glGetCombinerStageParameterfvNV;

/* NV_evaluators */

extern PFNGLMAPCONTROLPOINTSNVPROC glMapControlPointsNV;
extern PFNGLMAPPARAMETERIVNVPROC glMapParameterivNV;
extern PFNGLMAPPARAMETERFVNVPROC glMapParameterfvNV;
extern PFNGLGETMAPCONTROLPOINTSNVPROC glGetMapControlPointsNV;
extern PFNGLGETMAPPARAMETERIVNVPROC glGetMapParameterivNV;
extern PFNGLGETMAPPARAMETERFVNVPROC glGetMapParameterfvNV;
extern PFNGLGETMAPATTRIBPARAMETERIVNVPROC glGetMapAttribParameterivNV;
extern PFNGLGETMAPATTRIBPARAMETERFVNVPROC glGetMapAttribParameterfvNV;
extern PFNGLEVALMAPSNVPROC glEvalMapsNV;

/* ATI_pn_triangles */

extern PFNGLPNTRIANGLESIATIPROC glPNTrianglesiATI;
extern PFNGLPNTRIANGLESFATIPROC glPNTrianglesfATI;

/* ARB_point_parameters */

extern PFNGLPOINTPARAMETERFARBPROC glPointParameterfARB;
extern PFNGLPOINTPARAMETERFVARBPROC glPointParameterfvARB;

/* ARB_vertex_blend */

extern PFNGLWEIGHTBVARBPROC glWeightbvARB;
extern PFNGLWEIGHTSVARBPROC glWeightsvARB;
extern PFNGLWEIGHTIVARBPROC glWeightivARB;
extern PFNGLWEIGHTFVARBPROC glWeightfvARB;
extern PFNGLWEIGHTDVARBPROC glWeightdvARB;
extern PFNGLWEIGHTUBVARBPROC glWeightubvARB;
extern PFNGLWEIGHTUSVARBPROC glWeightusvARB;
extern PFNGLWEIGHTUIVARBPROC glWeightuivARB;
extern PFNGLWEIGHTPOINTERARBPROC glWeightPointerARB;
extern PFNGLVERTEXBLENDARBPROC glVertexBlendARB;

/* ETX_multi_draw_arrays */

extern PFNGLMULTIDRAWARRAYSEXTPROC glMultiDrawArraysEXT;
extern PFNGLMULTIDRAWELEMENTSEXTPROC glMultiDrawElementsEXT;

/* ARB_matrix_palette */

extern PFNGLCURRENTPALETTEMATRIXARBPROC glCurrentPaletteMatrixARB;
extern PFNGLMATRIXINDEXUBVARBPROC glMatrixIndexubvARB;
extern PFNGLMATRIXINDEXUSVARBPROC glMatrixIndexusvARB;
extern PFNGLMATRIXINDEXUIVARBPROC glMatrixIndexuivARB;
extern PFNGLMATRIXINDEXPOINTERARBPROC glMatrixIndexPointerARB;

/* EXT_vertex_shader */

extern PFNGLBEGINVERTEXSHADEREXTPROC glBeginVertexShaderEXT;
extern PFNGLENDVERTEXSHADEREXTPROC glEndVertexShaderEXT;
extern PFNGLBINDVERTEXSHADEREXTPROC glBindVertexShaderEXT;
extern PFNGLGENVERTEXSHADERSEXTPROC glGenVertexShadersEXT;
extern PFNGLDELETEVERTEXSHADEREXTPROC glDeleteVertexShaderEXT;
extern PFNGLSHADEROP1EXTPROC glShaderOp1EXT;
extern PFNGLSHADEROP2EXTPROC glShaderOp2EXT;
extern PFNGLSHADEROP3EXTPROC glShaderOp3EXT;
extern PFNGLSWIZZLEEXTPROC glSwizzleEXT;
extern PFNGLWRITEMASKEXTPROC glWriteMaskEXT;
extern PFNGLINSERTCOMPONENTEXTPROC glInsertComponentEXT;
extern PFNGLEXTRACTCOMPONENTEXTPROC glExtractComponentEXT;
extern PFNGLGENSYMBOLSEXTPROC glGenSymbolsEXT;
extern PFNGLSETINVARIANTEXTPROC glSetInvarianceEXT;
extern PFNGLSETLOCALCONSTANTEXTPROC glSetLocalConstantEXT;
extern PFNGLVARIANTBVEXTPROC glVariantbvEXT;
extern PFNGLVARIANTSVEXTPROC glVariantsvEXT;
extern PFNGLVARIANTIVEXTPROC glVariantivEXT;
extern PFNGLVARIANTFVEXTPROC glVariantfvEXT;
extern PFNGLVARIANTDVEXTPROC glVariantdvEXT;
extern PFNGLVARIANTUBVEXTPROC glVariantubvEXT;
extern PFNGLVARIANTUSVEXTPROC glVariantusvEXT;
extern PFNGLVARIANTUIVEXTPROC glVariantuivEXT;
extern PFNGLVARIANTPOINTEREXTPROC glVariantPointerEXT;
extern PFNGLENABLEVARIANTCLIENTSTATEEXTPROC glEnableVariantClientStateEXT;
extern PFNGLDISABLEVARIANTCLIENTSTATEEXTPROC glDisableVariantClientStateEXT;
extern PFNGLBINDLIGHTPARAMETEREXTPROC glBindLightParameterEXT;
extern PFNGLBINDMATERIALPARAMETEREXTPROC glBindMaterialParameterEXT;
extern PFNGLBINDTEXGENPARAMETEREXTPROC glBindTexGenParameterEXT;
extern PFNGLBINDTEXTUREUNITPARAMETEREXTPROC glBindTextureUnitParameterEXT;
extern PFNGLBINDPARAMETEREXTPROC glBindParameterEXT;
extern PFNGLISVARIANTENABLEDEXTPROC glIsVariantEnabledEXT;
extern PFNGLGETVARIANTBOOLEANVEXTPROC glGetVariantBooleanvEXT;
extern PFNGLGETVARIANTINTEGERVEXTPROC glGetVariantIntegervEXT;
extern PFNGLGETVARIANTFLOATVEXTPROC glGetVariantFloatvEXT;
extern PFNGLGETVARIANTPOINTERVEXTPROC glGetVariantPointervEXT;
extern PFNGLGETINVARIANTBOOLEANVEXTPROC glGetInvariantBooleanvEXT;
extern PFNGLGETINVARIANTINTEGERVEXTPROC glGetInvariantIntegervEXT;
extern PFNGLGETINVARIANTFLOATVEXTPROC glGetInvariantFloatvEXT;
extern PFNGLGETLOCALCONSTANTBOOLEANVEXTPROC glGetLocalConstantBooleanvEXT;
extern PFNGLGETLOCALCONSTANTINTEGERVEXTPROC glGetLocalConstantIntegervEXT;
extern PFNGLGETLOCALCONSTANTFLOATVEXTPROC glGetLocalConstantFloatvEXT;

/* ATI_envmap_bumpmap */

extern PFNGLTEXBUMPPARAMETERIVATIPROC glTexBumpParameterivATI;
extern PFNGLTEXBUMPPARAMETERFVATIPROC glTexBumpParameterfvATI;
extern PFNGLGETTEXBUMPPARAMETERIVATIPROC glGetTexBumpParameterivATI;
extern PFNGLGETTEXBUMPPARAMETERFVATIPROC glGetTexBumpParameterfvATI;

/* ATI_fragment_shader */

extern PFNGLGENFRAGMENTSHADERSATIPROC glGenFragmentShadersATI;
extern PFNGLBINDFRAGMENTSHADERATIPROC glBindFragmentShaderATI;
extern PFNGLDELETEFRAGMENTSHADERATIPROC glDeleteFragmentShaderATI;
extern PFNGLBEGINFRAGMENTSHADERATIPROC glBeginFragmentShaderATI;
extern PFNGLENDFRAGMENTSHADERATIPROC glEndFragmentShaderATI;
extern PFNGLPASSTEXCOORDATIPROC glPassTexCoordATI;
extern PFNGLSAMPLEMAPATIPROC glSampleMapATI;
extern PFNGLCOLORFRAGMENTOP1ATIPROC glColorFragmentOp1ATI;
extern PFNGLCOLORFRAGMENTOP2ATIPROC glColorFragmentOp2ATI;
extern PFNGLCOLORFRAGMENTOP3ATIPROC glColorFragmentOp3ATI;
extern PFNGLALPHAFRAGMENTOP1ATIPROC glAlphaFragmentOp1ATI;
extern PFNGLALPHAFRAGMENTOP2ATIPROC glAlphaFragmentOp2ATI;
extern PFNGLALPHAFRAGMENTOP3ATIPROC glAlphaFragmentOp3ATI;
extern PFNGLSETFRAGMENTSHADERCONSTANTATIPROC glSetFragmentShaderConstantATI;

/* ATI_element_array */

extern PFNGLELEMENTPOINTERATIPROC glElementPointerATI;
extern PFNGLDRAWELEMENTARRAYATIPROC glDrawElementArrayATI;
extern PFNGLDRAWRANGEELEMENTARRAYATIPROC glDrawRangeElementArrayATI;

/* ATI_vertex_streams */

extern PFNGLCLIENTACTIVEVERTEXSTREAMATIPROC glClientActiveVertexStreamATI;
extern PFNGLVERTEXBLENDENVIATIPROC glVertexBlendEnviATI;
extern PFNGLVERTEXBLENDENVFATIPROC glVertexBlendEnvfATI;
extern PFNGLVERTEXSTREAM2SATIPROC glVertexStream2sATI;
extern PFNGLVERTEXSTREAM2SVATIPROC glVertexStream2svATI;
extern PFNGLVERTEXSTREAM2IATIPROC glVertexStream2iATI;
extern PFNGLVERTEXSTREAM2IVATIPROC glVertexStream2ivATI;
extern PFNGLVERTEXSTREAM2FATIPROC glVertexStream2fATI;
extern PFNGLVERTEXSTREAM2FVATIPROC glVertexStream2fvATI;
extern PFNGLVERTEXSTREAM2DATIPROC glVertexStream2dATI;
extern PFNGLVERTEXSTREAM2DVATIPROC glVertexStream2dvATI;
extern PFNGLVERTEXSTREAM3SATIPROC glVertexStream3sATI;
extern PFNGLVERTEXSTREAM3SVATIPROC glVertexStream3svATI;
extern PFNGLVERTEXSTREAM3IATIPROC glVertexStream3iATI;
extern PFNGLVERTEXSTREAM3IVATIPROC glVertexStream3ivATI;
extern PFNGLVERTEXSTREAM3FATIPROC glVertexStream3fATI;
extern PFNGLVERTEXSTREAM3FVATIPROC glVertexStream3fvATI;
extern PFNGLVERTEXSTREAM3DATIPROC glVertexStream3dATI;
extern PFNGLVERTEXSTREAM3DVATIPROC glVertexStream3dvATI;
extern PFNGLVERTEXSTREAM4SATIPROC glVertexStream4sATI;
extern PFNGLVERTEXSTREAM4SVATIPROC glVertexStream4svATI;
extern PFNGLVERTEXSTREAM4IATIPROC glVertexStream4iATI;
extern PFNGLVERTEXSTREAM4IVATIPROC glVertexStream4ivATI;
extern PFNGLVERTEXSTREAM4FATIPROC glVertexStream4fATI;
extern PFNGLVERTEXSTREAM4FVATIPROC glVertexStream4fvATI;
extern PFNGLVERTEXSTREAM4DATIPROC glVertexStream4dATI;
extern PFNGLVERTEXSTREAM4DVATIPROC glVertexStream4dvATI;
extern PFNGLNORMALSTREAM3BATIPROC glNormalStream3bATI;
extern PFNGLNORMALSTREAM3BVATIPROC glNormalStream3bvATI;
extern PFNGLNORMALSTREAM3SATIPROC glNormalStream3sATI;
extern PFNGLNORMALSTREAM3SVATIPROC glNormalStream3svATI;
extern PFNGLNORMALSTREAM3IATIPROC glNormalStream3iATI;
extern PFNGLNORMALSTREAM3IVATIPROC glNormalStream3ivATI;
extern PFNGLNORMALSTREAM3FATIPROC glNormalStream3fATI;
extern PFNGLNORMALSTREAM3FVATIPROC glNormalStream3fvATI;
extern PFNGLNORMALSTREAM3DATIPROC glNormalStream3dATI;
extern PFNGLNORMALSTREAM3DVATIPROC glNormalStream3dvATI;

/* ATI_vertex_array_object */

extern PFNGLNEWOBJECTBUFFERATIPROC glNewObjectBufferATI;
extern PFNGLISOBJECTBUFFERATIPROC glIsObjectBufferATI;
extern PFNGLUPDATEOBJECTBUFFERATIPROC glUpdateObjectBufferATI;
extern PFNGLGETOBJECTBUFFERFVATIPROC glGetObjectBufferfvATI;
extern PFNGLGETOBJECTBUFFERIVATIPROC glGetObjectBufferivATI;
extern PFNGLFREEOBJECTBUFFERATIPROC glFreeObjectBufferATI;
extern PFNGLARRAYOBJECTATIPROC glArrayObjectATI;
extern PFNGLGETARRAYOBJECTFVATIPROC glGetArrayObjectfvATI;
extern PFNGLGETARRAYOBJECTIVATIPROC glGetArrayObjectivATI;
extern PFNGLVARIANTARRAYOBJECTATIPROC glVariantArrayObjectATI;
extern PFNGLGETVARIANTARRAYOBJECTFVATIPROC glGetVariantArrayObjectfvATI;
extern PFNGLGETVARIANTARRAYOBJECTIVATIPROC glGetVariantArrayObjectivATI;

#endif /* __PROTOTYPE__ */

#ifdef __cplusplus
}
#endif

#endif /* __EXTGL_H__ */