/* Copyright (c) 2001-2002 Lev Povalahev

   levp@gmx.net
  
   http://www.uni-karlsruhe.de/~uli2/

*/                         

/* following extensions are supported:

ARB_imaging
ARB_matrix_palette
ARB_multisample
ARB_multitexture
ARB_point_parameters
ARB_texture_compression
ARB_texture_env_add
ARB_texture_env_dot3
ARB_texture_env_combine
ARB_texture_env_crossbar
ARB_texture_border_clamp
ARB_texture_cube_map
ARB_transpose_matrix
ARB_vertex_blend
EXT_abgr
EXT_compiled_vertex_array
EXT_fog_coord
EXT_multi_draw_arrays
EXT_point_parameters
EXT_secondary_color
EXT_stencil_wrap
EXT_texture_filter_anisotropic
EXT_texture_lod_bias
EXT_vertex_shader
EXT_vertex_weighting
ATI_element_array
ATI_envmap_bumpmap
ATI_fragment_shader
ATI_pn_triangles
ATI_texture_mirror_once
ATI_vertex_array_object;
ATI_vertex_streams
ATIX_point_sprites
ATIX_texture_env_route
HP_occlusion_test
NV_blend_square
NV_copy_depth_to_color
NV_evaluators
NV_fence
NV_fog_distance
NV_light_max_exponent
NV_vertex_program
NV_packed_depth_stencil
NV_register_combiners
NV_register_combiners2
NV_texgen_reflection
NV_texture_env_combine4
NV_texture_rectangle
NV_texture_shader
NV_texture_shader2
NV_vertex_array_range
NV_vertex_array_range2
SGIS_generate_mipmap
SGIX_shadow
SGIX_depth_texture

*/  
     
       
#include "extgl.h"
#include <stdio.h>

/* functions variables */

#ifndef __PROTOTYPE__

#ifdef _WIN32

/* opengl 1.2 */
PFNGLBLENDCOLORPROC glBlendColor = NULL;
PFNGLBLENDEQUATIONPROC glBlendEquation = NULL;
PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElements = NULL;
PFNGLCOLORTABLEPROC glColorTable = NULL;
PFNGLCOLORTABLEPARAMETERFVPROC glColorTableParameterfv = NULL;
PFNGLCOLORTABLEPARAMETERIVPROC glColorTableParameteriv = NULL;
PFNGLCOPYCOLORTABLEPROC glCopyColorTable = NULL;
PFNGLGETCOLORTABLEPROC glGetColorTable = NULL;
PFNGLGETCOLORTABLEPARAMETERFVPROC glGetColorTableParameterfv = NULL;
PFNGLGETCOLORTABLEPARAMETERIVPROC glGetColorTableParameteriv = NULL;
PFNGLCOLORSUBTABLEPROC glColorSubTable = NULL;
PFNGLCOPYCOLORSUBTABLEPROC glCopyColorSubTable = NULL;
PFNGLCONVOLUTIONFILTER1DPROC glConvolutionFilter1D = NULL;
PFNGLCONVOLUTIONFILTER2DPROC glConvolutionFilter2D = NULL;
PFNGLCONVOLUTIONPARAMETERFPROC glConvolutionParameterf = NULL;
PFNGLCONVOLUTIONPARAMETERFVPROC glConvolutionParameterfv = NULL;
PFNGLCONVOLUTIONPARAMETERIPROC glConvolutionParameteri = NULL;
PFNGLCONVOLUTIONPARAMETERIVPROC glConvolutionParameteriv = NULL;
PFNGLCOPYCONVOLUTIONFILTER1DPROC glCopyConvolutionFilter1D = NULL;
PFNGLCOPYCONVOLUTIONFILTER2DPROC glCopyConvolutionFilter2D = NULL;
PFNGLGETCONVOLUTIONFILTERPROC glGetConvolutionFilter = NULL;
PFNGLGETCONVOLUTIONPARAMETERFVPROC glGetConvolutionParameterfv = NULL;
PFNGLGETCONVOLUTIONPARAMETERIVPROC glGetConvolutionParameteriv = NULL;
PFNGLGETSEPARABLEFILTERPROC glGetSeparableFilter = NULL;
PFNGLSEPARABLEFILTER2DPROC glSeparableFilter2D = NULL;
PFNGLGETHISTOGRAMPROC glGetHistogram = NULL;
PFNGLGETHISTOGRAMPARAMETERFVPROC glGetHistogramParameterfv = NULL;
PFNGLGETHISTOGRAMPARAMETERIVPROC glGetHistogramParameteriv = NULL;
PFNGLGETMINMAXPROC glGetMinmax = NULL;
PFNGLGETMINMAXPARAMETERFVPROC glGetMinmaxParameterfv = NULL;
PFNGLGETMINMAXPARAMETERIVPROC glGetMinmaxParameteriv = NULL;
PFNGLHISTOGRAMPROC glHistogram = NULL;
PFNGLMINMAXPROC glMinmax = NULL;
PFNGLRESETHISTOGRAMPROC glResetHistogram = NULL;
PFNGLRESETMINMAXPROC glResetMinmax = NULL;
PFNGLTEXIMAGE3DPROC glTexImage3D = NULL;
PFNGLTEXSUBIMAGE3DPROC glTexSubImage3D = NULL;
PFNGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3D = NULL;

/* opengl 1.3 */

PFNGLACTIVETEXTUREPROC glActiveTexture = NULL;
PFNGLCLIENTACTIVETEXTUREPROC glClientActiveTexture = NULL;
PFNGLMULTITEXCOORD1DPROC glMultiTexCoord1d = NULL;
PFNGLMULTITEXCOORD1DVPROC glMultiTexCoord1dv = NULL;
PFNGLMULTITEXCOORD1FPROC glMultiTexCoord1f = NULL;
PFNGLMULTITEXCOORD1FVPROC glMultiTexCoord1fv = NULL;
PFNGLMULTITEXCOORD1IPROC glMultiTexCoord1i = NULL;
PFNGLMULTITEXCOORD1IVPROC glMultiTexCoord1iv = NULL;
PFNGLMULTITEXCOORD1SPROC glMultiTexCoord1s = NULL;
PFNGLMULTITEXCOORD1SVPROC glMultiTexCoord1sv = NULL;

PFNGLMULTITEXCOORD2DPROC glMultiTexCoord2d = NULL;
PFNGLMULTITEXCOORD2DVPROC glMultiTexCoord2dv = NULL;
PFNGLMULTITEXCOORD2FPROC glMultiTexCoord2f = NULL;
PFNGLMULTITEXCOORD2FVPROC glMultiTexCoord2fv = NULL;
PFNGLMULTITEXCOORD2IPROC glMultiTexCoord2i = NULL;
PFNGLMULTITEXCOORD2IVPROC glMultiTexCoord2iv = NULL;
PFNGLMULTITEXCOORD2SPROC glMultiTexCoord2s = NULL;
PFNGLMULTITEXCOORD2SVPROC glMultiTexCoord2sv = NULL;

PFNGLMULTITEXCOORD3DPROC glMultiTexCoord3d = NULL;
PFNGLMULTITEXCOORD3DVPROC glMultiTexCoord3dv = NULL;
PFNGLMULTITEXCOORD3FPROC glMultiTexCoord3f = NULL;
PFNGLMULTITEXCOORD3FVPROC glMultiTexCoord3fv = NULL;
PFNGLMULTITEXCOORD3IPROC glMultiTexCoord3i = NULL;
PFNGLMULTITEXCOORD3IVPROC glMultiTexCoord3iv = NULL;
PFNGLMULTITEXCOORD3SPROC glMultiTexCoord3s = NULL;
PFNGLMULTITEXCOORD3SVPROC glMultiTexCoord3sv = NULL;

PFNGLMULTITEXCOORD4DPROC glMultiTexCoord4d = NULL;
PFNGLMULTITEXCOORD4DVPROC glMultiTexCoord4dv = NULL;
PFNGLMULTITEXCOORD4FPROC glMultiTexCoord4f = NULL;
PFNGLMULTITEXCOORD4FVPROC glMultiTexCoord4fv = NULL;
PFNGLMULTITEXCOORD4IPROC glMultiTexCoord4i = NULL;
PFNGLMULTITEXCOORD4IVPROC glMultiTexCoord4iv = NULL;
PFNGLMULTITEXCOORD4SPROC glMultiTexCoord4s = NULL;
PFNGLMULTITEXCOORD4SVPROC glMultiTexCoord4sv = NULL;


PFNGLLOADTRANSPOSEMATRIXFPROC glLoadTransposeMatrixf = NULL;
PFNGLLOADTRANSPOSEMATRIXDPROC glLoadTransposeMatrixd = NULL;
PFNGLMULTTRANSPOSEMATRIXFPROC glMultTransposeMatrixf = NULL;
PFNGLMULTTRANSPOSEMATRIXDPROC glMultTransposeMatrixd = NULL;

PFNGLCOMPRESSEDTEXIMAGE3DPROC glCompressedTexImage3D = NULL;
PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D = NULL;
PFNGLCOMPRESSEDTEXIMAGE1DPROC glCompressedTexImage1D = NULL;

PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glCompressedTexSubImage3D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glCompressedTexSubImage1D = NULL;

PFNGLGETCOMPRESSEDTEXIMAGEPROC glGetCompressedTexImage = NULL;

PFNGLSAMPLECOVERAGEPROC glSampleCoverage = NULL;

/* ARB_multitexture */

PFNGLACTIVETEXTUREPROC glActiveTextureARB = NULL;
PFNGLCLIENTACTIVETEXTUREPROC glClientActiveTextureARB = NULL;
PFNGLMULTITEXCOORD1DPROC glMultiTexCoord1dARB = NULL;
PFNGLMULTITEXCOORD1DVPROC glMultiTexCoord1dvARB = NULL;
PFNGLMULTITEXCOORD1FPROC glMultiTexCoord1fARB = NULL;
PFNGLMULTITEXCOORD1FVPROC glMultiTexCoord1fvARB = NULL;
PFNGLMULTITEXCOORD1IPROC glMultiTexCoord1iARB = NULL;
PFNGLMULTITEXCOORD1IVPROC glMultiTexCoord1ivARB = NULL;
PFNGLMULTITEXCOORD1SPROC glMultiTexCoord1sARB = NULL;
PFNGLMULTITEXCOORD1SVPROC glMultiTexCoord1svARB = NULL;

PFNGLMULTITEXCOORD2DPROC glMultiTexCoord2dARB = NULL;
PFNGLMULTITEXCOORD2DVPROC glMultiTexCoord2dvARB = NULL;
PFNGLMULTITEXCOORD2FPROC glMultiTexCoord2fARB = NULL;
PFNGLMULTITEXCOORD2FVPROC glMultiTexCoord2fvARB = NULL;
PFNGLMULTITEXCOORD2IPROC glMultiTexCoord2iARB = NULL;
PFNGLMULTITEXCOORD2IVPROC glMultiTexCoord2ivARB = NULL;
PFNGLMULTITEXCOORD2SPROC glMultiTexCoord2sARB = NULL;
PFNGLMULTITEXCOORD2SVPROC glMultiTexCoord2svARB = NULL;

PFNGLMULTITEXCOORD3DPROC glMultiTexCoord3dARB = NULL;
PFNGLMULTITEXCOORD3DVPROC glMultiTexCoord3dvARB = NULL;
PFNGLMULTITEXCOORD3FPROC glMultiTexCoord3fARB = NULL;
PFNGLMULTITEXCOORD3FVPROC glMultiTexCoord3fvARB = NULL;
PFNGLMULTITEXCOORD3IPROC glMultiTexCoord3iARB = NULL;
PFNGLMULTITEXCOORD3IVPROC glMultiTexCoord3ivARB = NULL;
PFNGLMULTITEXCOORD3SPROC glMultiTexCoord3sARB = NULL;
PFNGLMULTITEXCOORD3SVPROC glMultiTexCoord3svARB = NULL;

PFNGLMULTITEXCOORD4DPROC glMultiTexCoord4dARB = NULL;
PFNGLMULTITEXCOORD4DVPROC glMultiTexCoord4dvARB = NULL;
PFNGLMULTITEXCOORD4FPROC glMultiTexCoord4fARB = NULL;
PFNGLMULTITEXCOORD4FVPROC glMultiTexCoord4fvARB = NULL;
PFNGLMULTITEXCOORD4IPROC glMultiTexCoord4iARB = NULL;
PFNGLMULTITEXCOORD4IVPROC glMultiTexCoord4ivARB = NULL;
PFNGLMULTITEXCOORD4SPROC glMultiTexCoord4sARB = NULL;
PFNGLMULTITEXCOORD4SVPROC glMultiTexCoord4svARB = NULL;

#endif /* _WIN32 */

/* ETX_compiled_vertex_array */

PFNGLLOCKARRAYSEXTPROC glLockArraysEXT = NULL;
PFNGLUNLOCKARRAYSEXTPROC glUnlockArraysEXT = NULL;

/* EXT_secondary_color */

PFNGLSECONDARYCOLOR3BEXTPROC glSecondaryColor3bEXT = NULL;
PFNGLSECONDARYCOLOR3BVEXTPROC glSecondaryColor3bvEXT = NULL;
PFNGLSECONDARYCOLOR3DEXTPROC glSecondaryColor3dEXT = NULL;
PFNGLSECONDARYCOLOR3DVEXTPROC glSecondaryColor3dvEXT = NULL;
PFNGLSECONDARYCOLOR3FEXTPROC glSecondaryColor3fEXT = NULL;
PFNGLSECONDARYCOLOR3FVEXTPROC glSecondaryColor3fvEXT = NULL;
PFNGLSECONDARYCOLOR3IEXTPROC glSecondaryColor3iEXT = NULL;
PFNGLSECONDARYCOLOR3IVEXTPROC glSecondaryColor3ivEXT = NULL;
PFNGLSECONDARYCOLOR3SEXTPROC glSecondaryColor3sEXT = NULL;
PFNGLSECONDARYCOLOR3SVEXTPROC glSecondaryColor3svEXT = NULL;
PFNGLSECONDARYCOLOR3UBEXTPROC glSecondaryColor3ubEXT = NULL;
PFNGLSECONDARYCOLOR3UBVEXTPROC glSecondaryColor3ubvEXT = NULL;
PFNGLSECONDARYCOLOR3UIEXTPROC glSecondaryColor3uiEXT = NULL;
PFNGLSECONDARYCOLOR3UIVEXTPROC glSecondaryColor3uivEXT = NULL;
PFNGLSECONDARYCOLOR3USEXTPROC glSecondaryColor3usEXT = NULL;
PFNGLSECONDARYCOLOR3USVEXTPROC glSecondaryColor3usvEXT = NULL;
PFNGLSECONDARYCOLORPOINTEREXTPROC glSecondaryColorPointerEXT = NULL;

/* EXT_fog_color */

PFNGLFOGCOORDFEXTPROC glFogCoordfEXT = NULL;
PFNGLFOGCOORDFVEXTPROC glFogCoordfvEXT = NULL;
PFNGLFOGCOORDDEXTPROC glFogCoorddEXT = NULL;
PFNGLFOGCOORDDVEXTPROC glFogCoorddvEXT = NULL;
PFNGLFOGCOORDPOINTEREXTPROC glFogCoordPointerEXT = NULL;

/* NV_vertex_array_range */

PFNGLFLUSHVERTEXARRAYRANGENVPROC glFlushVertexArrayRangeNV = NULL;
PFNGLVERTEXARRAYRANGENVPROC glVertexArrayRangeNV = NULL;

/* EXT_point_parameters */

PFNGLPOINTPARAMETERFEXTPROC glPointParameterfEXT = NULL;
PFNGLPOINTPARAMETERFVEXTPROC glPointParameterfvEXT = NULL;

/* NV_register_combiners */

PFNGLCOMBINERPARAMETERFVNVPROC glCombinerParameterfvNV = NULL;
PFNGLCOMBINERPARAMETERFNVPROC  glCombinerParameterfNV = NULL;
PFNGLCOMBINERPARAMETERIVNVPROC glCombinerParameterivNV = NULL;
PFNGLCOMBINERPARAMETERINVPROC glCombinerParameteriNV = NULL;
PFNGLCOMBINERINPUTNVPROC glCombinerInputNV = NULL;
PFNGLCOMBINEROUTPUTNVPROC glCombinerOutputNV = NULL;
PFNGLFINALCOMBINERINPUTNVPROC glFinalCombinerInputNV = NULL;
PFNGLGETCOMBINERINPUTPARAMETERFVNVPROC glGetCombinerInputParameterfvNV = NULL;
PFNGLGETCOMBINERINPUTPARAMETERIVNVPROC glGetCombinerInputParameterivNV = NULL;
PFNGLGETCOMBINEROUTPUTPARAMETERFVNVPROC glGetCombinerOutputParameterfvNV = NULL;
PFNGLGETCOMBINEROUTPUTPARAMETERIVNVPROC glGetCombinerOutputParameterivNV = NULL;
PFNGLGETFINALCOMBINERINPUTPARAMETERFVNVPROC glGetFinalCombinerInputParameterfvNV = NULL;
PFNGLGETFINALCOMBINERINPUTPARAMETERIVNVPROC glGetFinalCombinerInputParameterivNV = NULL;

/* EXT_vertex_weighting */

PFNGLVERTEXWEIGHTFEXTPROC glVertexWeightfEXT = NULL;
PFNGLVERTEXWEIGHTFVEXTPROC glVertexWeightfvEXT = NULL;
PFNGLVERTEXWEIGHTPOINTEREXTPROC glVertexWeightPointerEXT = NULL;

/* NV_vertex_program */

PFNGLBINDPROGRAMNVPROC glBindProgramNV = NULL;
PFNGLDELETEPROGRAMSNVPROC glDeleteProgramsNV = NULL;
PFNGLEXECUTEPROGRAMNVPROC glExecuteProgramNV = NULL;
PFNGLGENPROGRAMSNVPROC glGenProgramsNV = NULL;
PFNGLAREPROGRAMSRESIDENTNVPROC glAreProgramsResidentNV = NULL;
PFNGLREQUESTRESIDENTPROGRAMSNVPROC glRequestResidentProgramsNV = NULL;
PFNGLGETPROGRAMPARAMETERFVNVPROC glGetProgramParameterfvNV = NULL;
PFNGLGETPROGRAMPARAMETERDVNVPROC glGetProgramParameterdvNV = NULL;
PFNGLGETPROGRAMIVNVPROC glGetProgramivNV = NULL;
PFNGLGETPROGRAMSTRINGNVPROC glGetProgramStringNV = NULL;
PFNGLGETTRACKMATRIXIVNVPROC glGetTrackMatrixivNV = NULL;
PFNGLGETVERTEXATTRIBDVNVPROC glGetVertexAttribdvNV = NULL;
PFNGLGETVERTEXATTRINFVNVPROC glGetVertexAttribfvNV = NULL;
PFNGLGETVERTEXATTRIBIVNVPROC glGetVertexAttribivNV = NULL;
PFNGLGETVERTEXATTRIBPOINTERVNVPROC glGetVertexAttribPointervNV = NULL;
PFNGLISPROGRAMNVPROC glIsProgramNV = NULL;
PFNGLLOADPROGRAMNVPROC glLoadProgramNV = NULL;
PFNGLPROGRAMPARAMETER4FNVPROC glProgramParameter4fNV = NULL;
PFNGLPROGRAMPARAMETER4DNVPROC glProgramParameter4dNV = NULL;
PFNGLPROGRAMPARAMETER4DVNVPROC glProgramParameter4dvNV = NULL;
PFNGLPROGRAMPARAMETER4FVNVPROC glProgramParameter4fvNV = NULL;
PFNGLPROGRAMPARAMETERS4DVNVPROC glProgramParameters4dvNV = NULL;
PFNGLPROGRAMPARAMETERS4FVNVPROC glProgramParameters4fvNV = NULL;
PFNGLTRACKMATRIXNVPROC glTrackMatrixNV = NULL;
PFNGLVERTEXATTRIBPPOINTERNVPROC glVertexAttribPointerNV = NULL;
PFNGLVERTEXATTRIB1SNVPROC glVertexAttrib1sNV = NULL;
PFNGLVERTEXATTRIB1FNVPROC glVertexAttrib1fNV = NULL;
PFNGLVERTEXATTRIB1DNVPROC glVertexAttrib1dNV = NULL;
PFNGLVERTEXATTRIB2SNVPROC glVertexAttrib2sNV = NULL;
PFNGLVERTEXATTRIB2FNVPROC glVertexAttrib2fNV = NULL;
PFNGLVERTEXATTRIB2DNVPROC glVertexAttrib2dNV = NULL;
PFNGLVERTEXATTRIB3SNVPROC glVertexAttrib3sNV = NULL;
PFNGLVERTEXATTRIB3FNVPROC glVertexAttrib3fNV = NULL;
PFNGLVERTEXATTRIB3DNVPROC glVertexAttrib3dNV = NULL;
PFNGLVERTEXATTRIB4SNVPROC glVertexAttrib4sNV = NULL;
PFNGLVERTEXATTRIB4FNVPROC glVertexAttrib4fNV = NULL;
PFNGLVERTEXATTRIB4DNVPROC glVertexAttrib4dNV = NULL;
PFNGLVERTEXATTRIB4UBNVPROC glVertexAttrib4ubNV = NULL;
PFNGLVERTEXATTRIB1SVNVPROC glVertexAttrib1svNV = NULL;
PFNGLVERTEXATTRIB1FVNVPROC glVertexAttrib1fvNV = NULL;
PFNGLVERTEXATTRIB1DVNVPROC glVertexAttrib1dvNV = NULL;
PFNGLVERTEXATTRIB2SVNVPROC glVertexAttrib2svNV = NULL;
PFNGLVERTEXATTRIB2FVNVPROC glVertexAttrib2fvNV = NULL;
PFNGLVERTEXATTRIB2DVNVPROC glVertexAttrib2dvNV = NULL;
PFNGLVERTEXATTRIB3SVNVPROC glVertexAttrib3svNV = NULL;
PFNGLVERTEXATTRIB3FVNVPROC glVertexAttrib3fvNV = NULL;
PFNGLVERTEXATTRIB3DVNVPROC glVertexAttrib3dvNV = NULL;
PFNGLVERTEXATTRIB4SVNVPROC glVertexAttrib4svNV = NULL;
PFNGLVERTEXATTRIB4FVNVPROC glVertexAttrib4fvNV = NULL;
PFNGLVERTEXATTRIB4DVNVPROC glVertexAttrib4dvNV = NULL;
PFNGLVERTEXATTRIB4UBVNVPROC glVertexAttrib4ubvNV = NULL;
PFNGLVERTEXATTRIBS1SVNVPROC glVertexAttribs1svNV = NULL;
PFNGLVERTEXATTRIBS1FVNVPROC glVertexAttribs1fvNV = NULL;
PFNGLVERTEXATTRIBS1DVNVPROC glVertexAttribs1dvNV = NULL;
PFNGLVERTEXATTRIBS2SVNVPROC glVertexAttribs2svNV = NULL;
PFNGLVERTEXATTRIBS2FVNVPROC glVertexAttribs2fvNV = NULL;
PFNGLVERTEXATTRIBS2DVNVPROC glVertexAttribs2dvNV = NULL;
PFNGLVERTEXATTRIBS3SVNVPROC glVertexAttribs3svNV = NULL;
PFNGLVERTEXATTRIBS3FVNVPROC glVertexAttribs3fvNV = NULL;
PFNGLVERTEXATTRIBS3DVNVPROC glVertexAttribs3dvNV = NULL;
PFNGLVERTEXATTRIBS4SVNVPROC glVertexAttribs4svNV = NULL;
PFNGLVERTEXATTRIBS4FVNVPROC glVertexAttribs4fvNV = NULL;
PFNGLVERTEXATTRIBS4DVNVPROC glVertexAttribs4dvNV = NULL;
PFNGLVERTEXATTRIBS4UBVNVPROC glVertexAttribs4ubvNV = NULL;

/* NV_fence */

PFNGLGENFENCESNVPROC glGenFencesNV = NULL;
PFNGLDELETEFENCESNVPROC glDeleteFencesNV = NULL;
PFNGLSETFENCENVPROC glSetFenceNV = NULL;
PFNGLTESTFENCENVPROC glTestFenceNV = NULL;
PFNGLFINISHFENCENVPROC glFinishFenceNV = NULL;
PFNGLISFENCENVPROC glIsFenceNV = NULL;
PFNGLGETFENCEIVNVPROC glGetFenceivNV = NULL;

/* NV_register_combiners2 */

PFNGLCOMBINERSTAGEPARAMETERFVNVPROC glCombinerStageParameterfvNV = NULL;
PFNGLGETCOMBINERSTAGEPARAMETERFVNVPROC glGetCombinerStageParameterfvNV = NULL;

/* NV_evaluators */

PFNGLMAPCONTROLPOINTSNVPROC glMapControlPointsNV = NULL;
PFNGLMAPPARAMETERIVNVPROC glMapParameterivNV = NULL;
PFNGLMAPPARAMETERFVNVPROC glMapParameterfvNV = NULL;
PFNGLGETMAPCONTROLPOINTSNVPROC glGetMapControlPointsNV = NULL;
PFNGLGETMAPPARAMETERIVNVPROC glGetMapParameterivNV = NULL;
PFNGLGETMAPPARAMETERFVNVPROC glGetMapParameterfvNV = NULL;
PFNGLGETMAPATTRIBPARAMETERIVNVPROC glGetMapAttribParameterivNV = NULL;
PFNGLGETMAPATTRIBPARAMETERFVNVPROC glGetMapAttribParameterfvNV = NULL;
PFNGLEVALMAPSNVPROC glEvalMapsNV = NULL;

/* ATI_pn_triangles */

PFNGLPNTRIANGLESIATIPROC glPNTrianglesiATI = NULL;
PFNGLPNTRIANGLESFATIPROC glPNTrianglesfATI = NULL;

/* ARB_point_parameters */

PFNGLPOINTPARAMETERFARBPROC glPointParameterfARB = NULL;
PFNGLPOINTPARAMETERFVARBPROC glPointParameterfvARB = NULL;

/* ARB_vertex_blend */

PFNGLWEIGHTBVARBPROC glWeightbvARB = NULL;
PFNGLWEIGHTSVARBPROC glWeightsvARB = NULL;
PFNGLWEIGHTIVARBPROC glWeightivARB = NULL;
PFNGLWEIGHTFVARBPROC glWeightfvARB = NULL;
PFNGLWEIGHTDVARBPROC glWeightdvARB = NULL;
PFNGLWEIGHTUBVARBPROC glWeightubvARB = NULL;
PFNGLWEIGHTUSVARBPROC glWeightusvARB = NULL;
PFNGLWEIGHTUIVARBPROC glWeightuivARB = NULL;
PFNGLWEIGHTPOINTERARBPROC glWeightPointerARB = NULL;
PFNGLVERTEXBLENDARBPROC glVertexBlendARB = NULL;

/* EXT_multi_draw_arrays */

PFNGLMULTIDRAWARRAYSEXTPROC glMultiDrawArraysEXT = NULL;
PFNGLMULTIDRAWELEMENTSEXTPROC glMultiDrawElementsEXT = NULL;

/* ARB_matrix_palette */

PFNGLCURRENTPALETTEMATRIXARBPROC glCurrentPaletteMatrixARB = NULL;
PFNGLMATRIXINDEXUBVARBPROC glMatrixIndexubvARB = NULL;
PFNGLMATRIXINDEXUSVARBPROC glMatrixIndexusvARB = NULL;
PFNGLMATRIXINDEXUIVARBPROC glMatrixIndexuivARB = NULL;
PFNGLMATRIXINDEXPOINTERARBPROC glMatrixIndexPointerARB = NULL;

/* EXT_vertex_shader */

PFNGLBEGINVERTEXSHADEREXTPROC glBeginVertexShaderEXT = NULL;
PFNGLENDVERTEXSHADEREXTPROC glEndVertexShaderEXT = NULL;
PFNGLBINDVERTEXSHADEREXTPROC glBindVertexShaderEXT = NULL;
PFNGLGENVERTEXSHADERSEXTPROC glGenVertexShadersEXT = NULL;
PFNGLDELETEVERTEXSHADEREXTPROC glDeleteVertexShaderEXT = NULL;
PFNGLSHADEROP1EXTPROC glShaderOp1EXT = NULL;
PFNGLSHADEROP2EXTPROC glShaderOp2EXT = NULL;
PFNGLSHADEROP3EXTPROC glShaderOp3EXT = NULL;
PFNGLSWIZZLEEXTPROC glSwizzleEXT = NULL;
PFNGLWRITEMASKEXTPROC glWriteMaskEXT = NULL;
PFNGLINSERTCOMPONENTEXTPROC glInsertComponentEXT = NULL;
PFNGLEXTRACTCOMPONENTEXTPROC glExtractComponentEXT = NULL;
PFNGLGENSYMBOLSEXTPROC glGenSymbolsEXT = NULL;
PFNGLSETINVARIANTEXTPROC glSetInvarianceEXT = NULL;
PFNGLSETLOCALCONSTANTEXTPROC glSetLocalConstantEXT = NULL;
PFNGLVARIANTBVEXTPROC glVariantbvEXT = NULL;
PFNGLVARIANTSVEXTPROC glVariantsvEXT = NULL;
PFNGLVARIANTIVEXTPROC glVariantivEXT = NULL;
PFNGLVARIANTFVEXTPROC glVariantfvEXT = NULL;
PFNGLVARIANTDVEXTPROC glVariantdvEXT = NULL;
PFNGLVARIANTUBVEXTPROC glVariantubvEXT = NULL;
PFNGLVARIANTUSVEXTPROC glVariantusvEXT = NULL;
PFNGLVARIANTUIVEXTPROC glVariantuivEXT = NULL;
PFNGLVARIANTPOINTEREXTPROC glVariantPointerEXT = NULL;
PFNGLENABLEVARIANTCLIENTSTATEEXTPROC glEnableVariantClientStateEXT = NULL;
PFNGLDISABLEVARIANTCLIENTSTATEEXTPROC glDisableVariantClientStateEXT = NULL;
PFNGLBINDLIGHTPARAMETEREXTPROC glBindLightParameterEXT = NULL;
PFNGLBINDMATERIALPARAMETEREXTPROC glBindMaterialParameterEXT = NULL;
PFNGLBINDTEXGENPARAMETEREXTPROC glBindTexGenParameterEXT = NULL;
PFNGLBINDTEXTUREUNITPARAMETEREXTPROC glBindTextureUnitParameterEXT = NULL;
PFNGLBINDPARAMETEREXTPROC glBindParameterEXT = NULL;
PFNGLISVARIANTENABLEDEXTPROC glIsVariantEnabledEXT = NULL;
PFNGLGETVARIANTBOOLEANVEXTPROC glGetVariantBooleanvEXT = NULL;
PFNGLGETVARIANTINTEGERVEXTPROC glGetVariantIntegervEXT = NULL;
PFNGLGETVARIANTFLOATVEXTPROC glGetVariantFloatvEXT = NULL;
PFNGLGETVARIANTPOINTERVEXTPROC glGetVariantPointervEXT = NULL;
PFNGLGETINVARIANTBOOLEANVEXTPROC glGetInvariantBooleanvEXT = NULL;
PFNGLGETINVARIANTINTEGERVEXTPROC glGetInvariantIntegervEXT = NULL;
PFNGLGETINVARIANTFLOATVEXTPROC glGetInvariantFloatvEXT = NULL;
PFNGLGETLOCALCONSTANTBOOLEANVEXTPROC glGetLocalConstantBooleanvEXT = NULL;
PFNGLGETLOCALCONSTANTINTEGERVEXTPROC glGetLocalConstantIntegervEXT = NULL;
PFNGLGETLOCALCONSTANTFLOATVEXTPROC glGetLocalConstantFloatvEXT = NULL;

/* ATI_envmap_bumpmap */

PFNGLTEXBUMPPARAMETERIVATIPROC glTexBumpParameterivATI = NULL;
PFNGLTEXBUMPPARAMETERFVATIPROC glTexBumpParameterfvATI = NULL;
PFNGLGETTEXBUMPPARAMETERIVATIPROC glGetTexBumpParameterivATI = NULL;
PFNGLGETTEXBUMPPARAMETERFVATIPROC glGetTexBumpParameterfvATI = NULL;

/* ATI_fragment_shader */

PFNGLGENFRAGMENTSHADERSATIPROC glGenFragmentShadersATI = NULL;
PFNGLBINDFRAGMENTSHADERATIPROC glBindFragmentShaderATI = NULL;
PFNGLDELETEFRAGMENTSHADERATIPROC glDeleteFragmentShaderATI = NULL;
PFNGLBEGINFRAGMENTSHADERATIPROC glBeginFragmentShaderATI = NULL;
PFNGLENDFRAGMENTSHADERATIPROC glEndFragmentShaderATI = NULL;
PFNGLPASSTEXCOORDATIPROC glPassTexCoordATI = NULL;
PFNGLSAMPLEMAPATIPROC glSampleMapATI = NULL;
PFNGLCOLORFRAGMENTOP1ATIPROC glColorFragmentOp1ATI = NULL;
PFNGLCOLORFRAGMENTOP2ATIPROC glColorFragmentOp2ATI = NULL;
PFNGLCOLORFRAGMENTOP3ATIPROC glColorFragmentOp3ATI = NULL;
PFNGLALPHAFRAGMENTOP1ATIPROC glAlphaFragmentOp1ATI = NULL;
PFNGLALPHAFRAGMENTOP2ATIPROC glAlphaFragmentOp2ATI = NULL;
PFNGLALPHAFRAGMENTOP3ATIPROC glAlphaFragmentOp3ATI = NULL;
PFNGLSETFRAGMENTSHADERCONSTANTATIPROC glSetFragmentShaderConstantATI = NULL;

/* ATI_element_array */

PFNGLELEMENTPOINTERATIPROC glElementPointerATI = NULL;
PFNGLDRAWELEMENTARRAYATIPROC glDrawElementArrayATI = NULL;
PFNGLDRAWRANGEELEMENTARRAYATIPROC glDrawRangeElementArrayATI = NULL;

/* ATI_vertex_streams */

PFNGLCLIENTACTIVEVERTEXSTREAMATIPROC glClientActiveVertexStreamATI = NULL;
PFNGLVERTEXBLENDENVIATIPROC glVertexBlendEnviATI = NULL;
PFNGLVERTEXBLENDENVFATIPROC glVertexBlendEnvfATI = NULL;
PFNGLVERTEXSTREAM2SATIPROC glVertexStream2sATI = NULL;
PFNGLVERTEXSTREAM2SVATIPROC glVertexStream2svATI = NULL;
PFNGLVERTEXSTREAM2IATIPROC glVertexStream2iATI = NULL;
PFNGLVERTEXSTREAM2IVATIPROC glVertexStream2ivATI = NULL;
PFNGLVERTEXSTREAM2FATIPROC glVertexStream2fATI = NULL;
PFNGLVERTEXSTREAM2FVATIPROC glVertexStream2fvATI = NULL;
PFNGLVERTEXSTREAM2DATIPROC glVertexStream2dATI = NULL;
PFNGLVERTEXSTREAM2DVATIPROC glVertexStream2dvATI = NULL;
PFNGLVERTEXSTREAM3SATIPROC glVertexStream3sATI = NULL;
PFNGLVERTEXSTREAM3SVATIPROC glVertexStream3svATI = NULL;
PFNGLVERTEXSTREAM3IATIPROC glVertexStream3iATI = NULL;
PFNGLVERTEXSTREAM3IVATIPROC glVertexStream3ivATI = NULL;
PFNGLVERTEXSTREAM3FATIPROC glVertexStream3fATI = NULL;
PFNGLVERTEXSTREAM3FVATIPROC glVertexStream3fvATI = NULL;
PFNGLVERTEXSTREAM3DATIPROC glVertexStream3dATI = NULL;
PFNGLVERTEXSTREAM3DVATIPROC glVertexStream3dvATI = NULL;
PFNGLVERTEXSTREAM4SATIPROC glVertexStream4sATI = NULL;
PFNGLVERTEXSTREAM4SVATIPROC glVertexStream4svATI = NULL;
PFNGLVERTEXSTREAM4IATIPROC glVertexStream4iATI = NULL;
PFNGLVERTEXSTREAM4IVATIPROC glVertexStream4ivATI = NULL;
PFNGLVERTEXSTREAM4FATIPROC glVertexStream4fATI = NULL;
PFNGLVERTEXSTREAM4FVATIPROC glVertexStream4fvATI = NULL;
PFNGLVERTEXSTREAM4DATIPROC glVertexStream4dATI = NULL;
PFNGLVERTEXSTREAM4DVATIPROC glVertexStream4dvATI = NULL;
PFNGLNORMALSTREAM3BATIPROC glNormalStream3bATI = NULL;
PFNGLNORMALSTREAM3BVATIPROC glNormalStream3bvATI = NULL;
PFNGLNORMALSTREAM3SATIPROC glNormalStream3sATI = NULL;
PFNGLNORMALSTREAM3SVATIPROC glNormalStream3svATI = NULL;
PFNGLNORMALSTREAM3IATIPROC glNormalStream3iATI = NULL;
PFNGLNORMALSTREAM3IVATIPROC glNormalStream3ivATI = NULL;
PFNGLNORMALSTREAM3FATIPROC glNormalStream3fATI = NULL;
PFNGLNORMALSTREAM3FVATIPROC glNormalStream3fvATI = NULL;
PFNGLNORMALSTREAM3DATIPROC glNormalStream3dATI = NULL;
PFNGLNORMALSTREAM3DVATIPROC glNormalStream3dvATI = NULL;

/* ATI_vertex_array_object */

PFNGLNEWOBJECTBUFFERATIPROC glNewObjectBufferATI = NULL;
PFNGLISOBJECTBUFFERATIPROC glIsObjectBufferATI = NULL;
PFNGLUPDATEOBJECTBUFFERATIPROC glUpdateObjectBufferATI = NULL;
PFNGLGETOBJECTBUFFERFVATIPROC glGetObjectBufferfvATI = NULL;
PFNGLGETOBJECTBUFFERIVATIPROC glGetObjectBufferivATI = NULL;
PFNGLFREEOBJECTBUFFERATIPROC glFreeObjectBufferATI = NULL;
PFNGLARRAYOBJECTATIPROC glArrayObjectATI = NULL;
PFNGLGETARRAYOBJECTFVATIPROC glGetArrayObjectfvATI = NULL;
PFNGLGETARRAYOBJECTIVATIPROC glGetArrayObjectivATI = NULL;
PFNGLVARIANTARRAYOBJECTATIPROC glVariantArrayObjectATI = NULL;
PFNGLGETVARIANTARRAYOBJECTFVATIPROC glGetVariantArrayObjectfvATI = NULL;
PFNGLGETVARIANTARRAYOBJECTIVATIPROC glGetVariantArrayObjectivATI = NULL;

#endif /* __PROTOTYPE__ */

/* misc  */

/* static int error = 0; */

/* struct ExtensionTypes SupportedExtensions; */

/* getProcAddress */

void *lglGetProcAddress(char *name)
{
#ifdef _WIN32
    void *t = wglGetProcAddress(name);
    //char err[1000];
    if (t == NULL)
    {
//        sprintf(err, "wglGetProcAddress on %s failed", name);
        //error = 1;//        MessageBox(0, err, "Error", MB_OK | MB_ICONHAND);
    }
    return t;
#else
    void *t = glXGetProcAddressARB((byte*)name);
    if (t == NULL)
    {
        error = 1:
    }
    return t;
#endif
}

/** returns true if the extention is available */
int QueryExtension(const char *name)
{
    const GLubyte *extensions = NULL;
    const GLubyte *start;
    GLubyte *where, *terminator;

    /* Extension names should not have spaces. */
    where = (GLubyte *) strchr(name, ' ');
    if (where || *name == '\0')
        return 0;
    extensions = glGetString(GL_EXTENSIONS);
    /* It takes a bit of care to be fool-proof about parsing the
         OpenGL extensions string. Don't be fooled by sub-strings,
        etc. */
    start = extensions;
    for (;;) 
    {
        where = (GLubyte *) strstr((const char *) start, name);
        if (!where)
            break;
        terminator = where + strlen(name);
        if (where == start || *(where - 1) == ' ')
            if (*terminator == ' ' || *terminator == '\0')
                return 1;
        start = terminator;
    }
    return 0;
    
/*    char *s = (char*)glGetString(GL_EXTENSIONS);
    char *temp = strstr(s, name);
    return temp!=NULL;*/
}
 
#ifndef __PROTOTYPE__
 
void InitATIVertexArrayObject( ExtensionTypes * SupportedExtensions )
{
    if (!SupportedExtensions->ATI_vertex_array_object)
        return;
    glNewObjectBufferATI = (PFNGLNEWOBJECTBUFFERATIPROC) lglGetProcAddress("glNewObjectBufferATI");
    glIsObjectBufferATI = (PFNGLISOBJECTBUFFERATIPROC) lglGetProcAddress("glIsObjectBufferATI");
    glUpdateObjectBufferATI = (PFNGLUPDATEOBJECTBUFFERATIPROC) lglGetProcAddress("glUpdateObjectBufferATI");
    glGetObjectBufferfvATI = (PFNGLGETOBJECTBUFFERFVATIPROC) lglGetProcAddress("glGetObjectBufferfvATI");
    glGetObjectBufferivATI = (PFNGLGETOBJECTBUFFERIVATIPROC) lglGetProcAddress("glGetObjectBufferivATI");
    glFreeObjectBufferATI = (PFNGLFREEOBJECTBUFFERATIPROC) lglGetProcAddress("glFreeObjectBufferATI");
    glArrayObjectATI = (PFNGLARRAYOBJECTATIPROC) lglGetProcAddress("glArrayObjectATI");
    glGetArrayObjectfvATI = (PFNGLGETARRAYOBJECTFVATIPROC) lglGetProcAddress("glGetArrayObjectfvATI");
    glGetArrayObjectivATI = (PFNGLGETARRAYOBJECTIVATIPROC) lglGetProcAddress("glGetArrayObjectivATI");
    glVariantArrayObjectATI = (PFNGLVARIANTARRAYOBJECTATIPROC) lglGetProcAddress("glVariantArrayObjectATI");
    glGetVariantArrayObjectfvATI = (PFNGLGETVARIANTARRAYOBJECTFVATIPROC) lglGetProcAddress("glGetVariantArrayObjectfvATI");
    glGetVariantArrayObjectivATI = (PFNGLGETVARIANTARRAYOBJECTIVATIPROC) lglGetProcAddress("glGetVariantArrayObjectivATI");
}

void InitATIVertexStreams( ExtensionTypes * SupportedExtensions )
{
    if (!SupportedExtensions->ATI_vertex_streams)
        return;
    glClientActiveVertexStreamATI = (PFNGLCLIENTACTIVEVERTEXSTREAMATIPROC) lglGetProcAddress("glClientActiveVertexStreamATI");
    glVertexBlendEnviATI = (PFNGLVERTEXBLENDENVIATIPROC) lglGetProcAddress("glVertexBlendEnviATI");
    glVertexBlendEnvfATI = (PFNGLVERTEXBLENDENVFATIPROC) lglGetProcAddress("glVertexBlendEnvfATI");
    glVertexStream2sATI = (PFNGLVERTEXSTREAM2SATIPROC) lglGetProcAddress("glVertexStream2sATI");
    glVertexStream2svATI = (PFNGLVERTEXSTREAM2SVATIPROC) lglGetProcAddress("glVertexStream2svATI");
    glVertexStream2iATI = (PFNGLVERTEXSTREAM2IATIPROC) lglGetProcAddress("glVertexStream2iATI");
    glVertexStream2ivATI = (PFNGLVERTEXSTREAM2IVATIPROC) lglGetProcAddress("glVertexStream2ivATI");
    glVertexStream2fATI = (PFNGLVERTEXSTREAM2FATIPROC) lglGetProcAddress("glVertexStream2fATI");
    glVertexStream2fvATI = (PFNGLVERTEXSTREAM2FVATIPROC) lglGetProcAddress("glVertexStream2fvATI");
    glVertexStream2dATI = (PFNGLVERTEXSTREAM2DATIPROC) lglGetProcAddress("glVertexStream2dATI");
    glVertexStream2dvATI = (PFNGLVERTEXSTREAM2DVATIPROC) lglGetProcAddress("glVertexStream2dvATI");
    glVertexStream3sATI = (PFNGLVERTEXSTREAM3SATIPROC) lglGetProcAddress("glVertexStream3sATI");
    glVertexStream3svATI = (PFNGLVERTEXSTREAM3SVATIPROC) lglGetProcAddress("glVertexStream3svATI");
    glVertexStream3iATI = (PFNGLVERTEXSTREAM3IATIPROC) lglGetProcAddress("glVertexStream3iATI");
    glVertexStream3ivATI = (PFNGLVERTEXSTREAM3IVATIPROC) lglGetProcAddress("glVertexStream3ivATI");
    glVertexStream3fATI = (PFNGLVERTEXSTREAM3FATIPROC) lglGetProcAddress("glVertexStream3fATI");
    glVertexStream3fvATI = (PFNGLVERTEXSTREAM3FVATIPROC) lglGetProcAddress("glVertexStream3fvATI");
    glVertexStream3dATI = (PFNGLVERTEXSTREAM3DATIPROC) lglGetProcAddress("glVertexStream3dATI");
    glVertexStream3dvATI = (PFNGLVERTEXSTREAM3DVATIPROC) lglGetProcAddress("glVertexStream3dvATI");
    glVertexStream4sATI = (PFNGLVERTEXSTREAM4SATIPROC) lglGetProcAddress("glVertexStream4sATI");
    glVertexStream4svATI = (PFNGLVERTEXSTREAM4SVATIPROC) lglGetProcAddress("glVertexStream4svATI");
    glVertexStream4iATI = (PFNGLVERTEXSTREAM4IATIPROC) lglGetProcAddress("glVertexStream4iATI");
    glVertexStream4ivATI = (PFNGLVERTEXSTREAM4IVATIPROC) lglGetProcAddress("glVertexStream4ivATI");
    glVertexStream4fATI = (PFNGLVERTEXSTREAM4FATIPROC) lglGetProcAddress("glVertexStream4fATI");
    glVertexStream4fvATI = (PFNGLVERTEXSTREAM4FVATIPROC) lglGetProcAddress("glVertexStream4fvATI");
    glVertexStream4dATI = (PFNGLVERTEXSTREAM4DATIPROC) lglGetProcAddress("glVertexStream4dATI");
    glVertexStream4dvATI = (PFNGLVERTEXSTREAM4DVATIPROC) lglGetProcAddress("glVertexStream4dvATI");
    glNormalStream3bATI = (PFNGLNORMALSTREAM3BATIPROC) lglGetProcAddress("glNormalStream3bATI");
    glNormalStream3bvATI = (PFNGLNORMALSTREAM3BVATIPROC) lglGetProcAddress("glNormalStream3bvATI");
    glNormalStream3sATI = (PFNGLNORMALSTREAM3SATIPROC) lglGetProcAddress("glNormalStream3sATI");
    glNormalStream3svATI = (PFNGLNORMALSTREAM3SVATIPROC) lglGetProcAddress("glNormalStream3svATI");
    glNormalStream3iATI = (PFNGLNORMALSTREAM3IATIPROC) lglGetProcAddress("glNormalStream3iATI");
    glNormalStream3ivATI = (PFNGLNORMALSTREAM3IVATIPROC) lglGetProcAddress("glNormalStream3ivATI");
    glNormalStream3fATI = (PFNGLNORMALSTREAM3FATIPROC) lglGetProcAddress("glNormalStream3fATI");
    glNormalStream3fvATI = (PFNGLNORMALSTREAM3FVATIPROC) lglGetProcAddress("glNormalStream3fvATI");
    glNormalStream3dATI = (PFNGLNORMALSTREAM3DATIPROC) lglGetProcAddress("glNormalStream3dATI");
    glNormalStream3dvATI = (PFNGLNORMALSTREAM3DVATIPROC) lglGetProcAddress("glNormalStream3dvATI");
}

void InitATIElementArray( ExtensionTypes * SupportedExtensions )
{
    if (!SupportedExtensions->ATI_element_array)
        return;
    glElementPointerATI = (PFNGLELEMENTPOINTERATIPROC) lglGetProcAddress("glElementPointerATI");
    glDrawElementArrayATI = (PFNGLDRAWELEMENTARRAYATIPROC) lglGetProcAddress("glDrawElementArrayATI");
    glDrawRangeElementArrayATI = (PFNGLDRAWRANGEELEMENTARRAYATIPROC) lglGetProcAddress("glDrawRangeElementArrayATI");
}

void InitATIFragmentShader( ExtensionTypes * SupportedExtensions )
{
    if (!SupportedExtensions->ATI_fragment_shader)
        return;
    glGenFragmentShadersATI = (PFNGLGENFRAGMENTSHADERSATIPROC) lglGetProcAddress("glGenFragmentShadersATI");
    glBindFragmentShaderATI = (PFNGLBINDFRAGMENTSHADERATIPROC) lglGetProcAddress("glBindFragmentShaderATI");
    glDeleteFragmentShaderATI = (PFNGLDELETEFRAGMENTSHADERATIPROC) lglGetProcAddress("glDeleteFragmentShaderATI");
    glBeginFragmentShaderATI = (PFNGLBEGINFRAGMENTSHADERATIPROC) lglGetProcAddress("glBeginFragmentShaderATI");
    glEndFragmentShaderATI = (PFNGLENDFRAGMENTSHADERATIPROC) lglGetProcAddress("glEndFragmentShaderATI");
    glPassTexCoordATI = (PFNGLPASSTEXCOORDATIPROC) lglGetProcAddress("glPassTexCoordATI");
    glSampleMapATI = (PFNGLSAMPLEMAPATIPROC) lglGetProcAddress("glSampleMapATI");
    glColorFragmentOp1ATI = (PFNGLCOLORFRAGMENTOP1ATIPROC) lglGetProcAddress("glColorFragmentOp1ATI");
    glColorFragmentOp2ATI = (PFNGLCOLORFRAGMENTOP2ATIPROC) lglGetProcAddress("glColorFragmentOp2ATI");
    glColorFragmentOp3ATI = (PFNGLCOLORFRAGMENTOP3ATIPROC) lglGetProcAddress("glColorFragmentOp3ATI");
    glAlphaFragmentOp1ATI = (PFNGLALPHAFRAGMENTOP1ATIPROC) lglGetProcAddress("glAlphaFragmentOp1ATI");
    glAlphaFragmentOp2ATI = (PFNGLALPHAFRAGMENTOP2ATIPROC) lglGetProcAddress("glAlphaFragmentOp2ATI");
    glAlphaFragmentOp3ATI = (PFNGLALPHAFRAGMENTOP3ATIPROC) lglGetProcAddress("glAlphaFragmentOp3ATI");
    glSetFragmentShaderConstantATI = (PFNGLSETFRAGMENTSHADERCONSTANTATIPROC) lglGetProcAddress("glSetFragmentShaderConstantATI");
}

void InitATIEnvmapBumpmap( ExtensionTypes * SupportedExtensions )
{
    if (!SupportedExtensions->ATI_envmap_bumpmap)
        return;
    glTexBumpParameterivATI = (PFNGLTEXBUMPPARAMETERIVATIPROC) lglGetProcAddress("glTexBumpParameterivATI");
    glTexBumpParameterfvATI = (PFNGLTEXBUMPPARAMETERFVATIPROC) lglGetProcAddress("glTexBumpParameterfvATI");
    glGetTexBumpParameterivATI = (PFNGLGETTEXBUMPPARAMETERIVATIPROC) lglGetProcAddress("glGetTexBumpParameterivATI");
    glGetTexBumpParameterfvATI = (PFNGLGETTEXBUMPPARAMETERFVATIPROC) lglGetProcAddress("glGetTexBumpParameterfvATI");
}

void InitEXTVertexShader( ExtensionTypes * SupportedExtensions )
{
    if (!SupportedExtensions->EXT_vertex_shader)
        return;
    glBeginVertexShaderEXT = (PFNGLBEGINVERTEXSHADEREXTPROC) lglGetProcAddress("glBeginVertexShaderEXT");
    glEndVertexShaderEXT = (PFNGLENDVERTEXSHADEREXTPROC) lglGetProcAddress("glEndVertexShaderEXT");
    glBindVertexShaderEXT = (PFNGLBINDVERTEXSHADEREXTPROC) lglGetProcAddress("glBindVertexShaderEXT");
    glGenVertexShadersEXT = (PFNGLGENVERTEXSHADERSEXTPROC) lglGetProcAddress("glGenVertexShadersEXT");
    glDeleteVertexShaderEXT = (PFNGLDELETEVERTEXSHADEREXTPROC) lglGetProcAddress("glDeleteVertexShaderEXT");
    glShaderOp1EXT = (PFNGLSHADEROP1EXTPROC) lglGetProcAddress("glShaderOp1EXT");
    glShaderOp2EXT = (PFNGLSHADEROP2EXTPROC) lglGetProcAddress("glShaderOp2EXT");
    glShaderOp3EXT = (PFNGLSHADEROP3EXTPROC) lglGetProcAddress("glShaderOp3EXT");
    glSwizzleEXT = (PFNGLSWIZZLEEXTPROC) lglGetProcAddress("glSwizzleEXT");
    glWriteMaskEXT = (PFNGLWRITEMASKEXTPROC) lglGetProcAddress("glWriteMaskEXT");
    glInsertComponentEXT = (PFNGLINSERTCOMPONENTEXTPROC) lglGetProcAddress("glInsertComponentEXT");
    glExtractComponentEXT = (PFNGLEXTRACTCOMPONENTEXTPROC) lglGetProcAddress("glExtractComponentEXT");
    glGenSymbolsEXT = (PFNGLGENSYMBOLSEXTPROC) lglGetProcAddress("glGenSymbolsEXT");
    glSetInvarianceEXT = (PFNGLSETINVARIANTEXTPROC) lglGetProcAddress("glSetInvarianceEXT");
    glSetLocalConstantEXT = (PFNGLSETLOCALCONSTANTEXTPROC) lglGetProcAddress("glSetLocalConstantEXT");
    glVariantbvEXT = (PFNGLVARIANTBVEXTPROC) lglGetProcAddress("glVariantbvEXT");
    glVariantsvEXT = (PFNGLVARIANTSVEXTPROC) lglGetProcAddress("glVariantsvEXT");
    glVariantivEXT = (PFNGLVARIANTIVEXTPROC) lglGetProcAddress("glVariantivEXT");
    glVariantfvEXT = (PFNGLVARIANTFVEXTPROC) lglGetProcAddress("glVariantfvEXT");
    glVariantdvEXT = (PFNGLVARIANTDVEXTPROC) lglGetProcAddress("glVariantdvEXT");
    glVariantubvEXT = (PFNGLVARIANTUBVEXTPROC) lglGetProcAddress("glVariantubvEXT");
    glVariantusvEXT = (PFNGLVARIANTUSVEXTPROC) lglGetProcAddress("glVariantusvEXT");
    glVariantuivEXT = (PFNGLVARIANTUIVEXTPROC) lglGetProcAddress("glVariantuivEXT");
    glVariantPointerEXT = (PFNGLVARIANTPOINTEREXTPROC) lglGetProcAddress("glVariantPointerEXT");
    glEnableVariantClientStateEXT = (PFNGLENABLEVARIANTCLIENTSTATEEXTPROC) lglGetProcAddress("glEnableVariantClientStateEXT");
    glDisableVariantClientStateEXT = (PFNGLDISABLEVARIANTCLIENTSTATEEXTPROC) lglGetProcAddress("glDisableVariantClientStateEXT");
    glBindLightParameterEXT = (PFNGLBINDLIGHTPARAMETEREXTPROC) lglGetProcAddress("glBindLightParameterEXT");
    glBindMaterialParameterEXT = (PFNGLBINDMATERIALPARAMETEREXTPROC) lglGetProcAddress("glBindMaterialParameterEXT");
    glBindTexGenParameterEXT = (PFNGLBINDTEXGENPARAMETEREXTPROC) lglGetProcAddress("glBindTexGenParameterEXT");
    glBindTextureUnitParameterEXT = (PFNGLBINDTEXTUREUNITPARAMETEREXTPROC) lglGetProcAddress("glBindTextureUnitParameterEXT");
    glBindParameterEXT = (PFNGLBINDPARAMETEREXTPROC) lglGetProcAddress("glBindParameterEXT");
    glIsVariantEnabledEXT = (PFNGLISVARIANTENABLEDEXTPROC) lglGetProcAddress("glIsVariantEnabledEXT");
    glGetVariantBooleanvEXT = (PFNGLGETVARIANTBOOLEANVEXTPROC) lglGetProcAddress("glGetVariantBooleanvEXT");
    glGetVariantIntegervEXT = (PFNGLGETVARIANTINTEGERVEXTPROC) lglGetProcAddress("glGetVariantIntegervEXT");
    glGetVariantFloatvEXT = (PFNGLGETVARIANTFLOATVEXTPROC) lglGetProcAddress("glGetVariantFloatvEXT");
    glGetVariantPointervEXT = (PFNGLGETVARIANTPOINTERVEXTPROC) lglGetProcAddress("glGetVariantPointervEXT");
    glGetInvariantBooleanvEXT = (PFNGLGETINVARIANTBOOLEANVEXTPROC) lglGetProcAddress("glGetInvariantBooleanvEXT");
    glGetInvariantIntegervEXT = (PFNGLGETINVARIANTINTEGERVEXTPROC) lglGetProcAddress("glGetInvariantIntegervEXT");
    glGetInvariantFloatvEXT = (PFNGLGETINVARIANTFLOATVEXTPROC) lglGetProcAddress("glGetInvariantFloatvEXT");
    glGetLocalConstantBooleanvEXT = (PFNGLGETLOCALCONSTANTBOOLEANVEXTPROC) lglGetProcAddress("glGetLocalConstantBooleanvEXT");
    glGetLocalConstantIntegervEXT = (PFNGLGETLOCALCONSTANTINTEGERVEXTPROC) lglGetProcAddress("glGetLocalConstantIntegervEXT");
    glGetLocalConstantFloatvEXT = (PFNGLGETLOCALCONSTANTFLOATVEXTPROC) lglGetProcAddress("glGetLocalConstantFloatvEXT");
}

void InitARBMatrixPalette( ExtensionTypes * SupportedExtensions )
{
    if (!SupportedExtensions->ARB_matrix_palette)
        return;
    glCurrentPaletteMatrixARB = (PFNGLCURRENTPALETTEMATRIXARBPROC) lglGetProcAddress("glCurrentPaletteMatrixARB");
    glMatrixIndexubvARB = (PFNGLMATRIXINDEXUBVARBPROC) lglGetProcAddress("glMatrixIndexubvARB");
    glMatrixIndexusvARB = (PFNGLMATRIXINDEXUSVARBPROC) lglGetProcAddress("glMatrixIndexusvARB");
    glMatrixIndexuivARB = (PFNGLMATRIXINDEXUIVARBPROC) lglGetProcAddress("glMatrixIndexuivARB");
    glMatrixIndexPointerARB = (PFNGLMATRIXINDEXPOINTERARBPROC) lglGetProcAddress("glMatrixIndexPointerARB");
}

void InitEXTMultiDrawArrays( ExtensionTypes * SupportedExtensions )
{
    if (!SupportedExtensions->EXT_multi_draw_arrays)
        return;
    glMultiDrawArraysEXT = (PFNGLMULTIDRAWARRAYSEXTPROC) lglGetProcAddress("glMultiDrawArraysEXT");
    glMultiDrawElementsEXT = (PFNGLMULTIDRAWELEMENTSEXTPROC) lglGetProcAddress("glMultiDrawElementsEXT");
}

void InitARBVertexBlend( ExtensionTypes * SupportedExtensions )
{
    if (!SupportedExtensions->ARB_vertex_blend)
        return;
    glWeightbvARB = (PFNGLWEIGHTBVARBPROC) lglGetProcAddress("glWeightbvARB");
    glWeightsvARB = (PFNGLWEIGHTSVARBPROC) lglGetProcAddress("glWeightsvARB");
    glWeightivARB = (PFNGLWEIGHTIVARBPROC) lglGetProcAddress("glWeightivARB");
    glWeightfvARB = (PFNGLWEIGHTFVARBPROC) lglGetProcAddress("glWeightfvARB");
    glWeightdvARB = (PFNGLWEIGHTDVARBPROC) lglGetProcAddress("glWeightdvARB");
    glWeightubvARB = (PFNGLWEIGHTUBVARBPROC) lglGetProcAddress("glWeightubvARB");
    glWeightusvARB = (PFNGLWEIGHTUSVARBPROC) lglGetProcAddress("glWeightusvARB");
    glWeightuivARB = (PFNGLWEIGHTUIVARBPROC) lglGetProcAddress("glWeightuivARB");
    glWeightPointerARB = (PFNGLWEIGHTPOINTERARBPROC) lglGetProcAddress("glWeightPointerARB");
    glVertexBlendARB = (PFNGLVERTEXBLENDARBPROC) lglGetProcAddress("glVertexBlendARB");
}

void InitARBPointParameters( ExtensionTypes * SupportedExtensions )
{
    if (!SupportedExtensions->ARB_point_parameters)
        return;
    glPointParameterfARB = (PFNGLPOINTPARAMETERFARBPROC) lglGetProcAddress("glPointParameterfARB");
    glPointParameterfvARB = (PFNGLPOINTPARAMETERFVARBPROC) lglGetProcAddress("glPointParameterfvARB");
}

void InitATIPNTriangles( ExtensionTypes * SupportedExtensions )
{
    if (!SupportedExtensions->ATI_pn_triangles)
        return;
    glPNTrianglesiATI = (PFNGLPNTRIANGLESIATIPROC) lglGetProcAddress("glPNTrianglesiATI");
    glPNTrianglesfATI = (PFNGLPNTRIANGLESFATIPROC) lglGetProcAddress("glPNTrianglesfATI");
}

void InitNVEvaluators( ExtensionTypes * SupportedExtensions )
{
    if (!SupportedExtensions->NV_evaluators)
        return;
    glMapControlPointsNV = (PFNGLMAPCONTROLPOINTSNVPROC) lglGetProcAddress("glMapControlPointsNV");
    glMapParameterivNV = (PFNGLMAPPARAMETERIVNVPROC) lglGetProcAddress("glMapParameterivNV");
    glMapParameterfvNV = (PFNGLMAPPARAMETERFVNVPROC) lglGetProcAddress("glMapParameterfvNV");
    glGetMapControlPointsNV = (PFNGLGETMAPCONTROLPOINTSNVPROC) lglGetProcAddress("glGetMapControlPointsNV");
    glGetMapParameterivNV = (PFNGLGETMAPPARAMETERIVNVPROC) lglGetProcAddress("glGetMapParameterivNV");
    glGetMapParameterfvNV = (PFNGLGETMAPPARAMETERFVNVPROC) lglGetProcAddress("glGetMapParameterfvNV");
    glGetMapAttribParameterivNV = (PFNGLGETMAPATTRIBPARAMETERIVNVPROC) lglGetProcAddress("glGetMapAttribParameterivNV");
    glGetMapAttribParameterfvNV = (PFNGLGETMAPATTRIBPARAMETERFVNVPROC) lglGetProcAddress("glGetMapAttribParameterfvNV");
    glEvalMapsNV = (PFNGLEVALMAPSNVPROC) lglGetProcAddress("glEvalMapsNV");
}

void InitNVRegisterCombiners2( ExtensionTypes * SupportedExtensions )
{
    if (!SupportedExtensions->NV_register_combiners2)
        return;
    glCombinerStageParameterfvNV = (PFNGLCOMBINERSTAGEPARAMETERFVNVPROC) lglGetProcAddress("glCombinerStageParameterfvNV");
    glGetCombinerStageParameterfvNV = (PFNGLGETCOMBINERSTAGEPARAMETERFVNVPROC) lglGetProcAddress("glGetCombinerStageParameterfvNV");
}

void InitNVFence( ExtensionTypes * SupportedExtensions )
{
    if (!SupportedExtensions->NV_fence)
        return;
    glGenFencesNV = (PFNGLGENFENCESNVPROC) lglGetProcAddress("glGenFencesNV");
    glDeleteFencesNV = (PFNGLDELETEFENCESNVPROC) lglGetProcAddress("glDeleteFencesNV");
    glSetFenceNV = (PFNGLSETFENCENVPROC) lglGetProcAddress("glSetFenceNV");
    glTestFenceNV = (PFNGLTESTFENCENVPROC) lglGetProcAddress("glTestFenceNV");
    glFinishFenceNV = (PFNGLFINISHFENCENVPROC) lglGetProcAddress("glFinishFenceNV");
    glIsFenceNV = (PFNGLISFENCENVPROC) lglGetProcAddress("glIsFenceNV");
    glGetFenceivNV = (PFNGLGETFENCEIVNVPROC) lglGetProcAddress("glGetFenceivNV");
}

void InitNVVertexProgram( ExtensionTypes * SupportedExtensions )
{
    if (!SupportedExtensions->NV_vertex_program)
        return;
    glBindProgramNV = (PFNGLBINDPROGRAMNVPROC) lglGetProcAddress("glBindProgramNV");
    glDeleteProgramsNV = (PFNGLDELETEPROGRAMSNVPROC) lglGetProcAddress("glDeleteProgramsNV");
    glExecuteProgramNV = (PFNGLEXECUTEPROGRAMNVPROC) lglGetProcAddress("glExecuteProgramNV");
    glGenProgramsNV = (PFNGLGENPROGRAMSNVPROC) lglGetProcAddress("glGenProgramsNV");
    glAreProgramsResidentNV = (PFNGLAREPROGRAMSRESIDENTNVPROC) lglGetProcAddress("glAreProgramsResidentNV");
    glRequestResidentProgramsNV = (PFNGLREQUESTRESIDENTPROGRAMSNVPROC) lglGetProcAddress("glRequestResidentProgramsNV");
    glGetProgramParameterfvNV = (PFNGLGETPROGRAMPARAMETERFVNVPROC) lglGetProcAddress("glGetProgramParameterfvNV");
    glGetProgramParameterdvNV = (PFNGLGETPROGRAMPARAMETERDVNVPROC) lglGetProcAddress("glGetProgramParameterdvNV");
    glGetProgramivNV = (PFNGLGETPROGRAMIVNVPROC) lglGetProcAddress("glGetProgramivNV");
    glGetProgramStringNV = (PFNGLGETPROGRAMSTRINGNVPROC) lglGetProcAddress("glGetProgramStringNV");
    glGetTrackMatrixivNV = (PFNGLGETTRACKMATRIXIVNVPROC) lglGetProcAddress("glGetTrackMatrixivNV");
    glGetVertexAttribdvNV = (PFNGLGETVERTEXATTRIBDVNVPROC) lglGetProcAddress("glGetVertexAttribdvNV");
    glGetVertexAttribfvNV = (PFNGLGETVERTEXATTRINFVNVPROC) lglGetProcAddress("glGetVertexAttribfvNV");
    glGetVertexAttribivNV = (PFNGLGETVERTEXATTRIBIVNVPROC) lglGetProcAddress("glGetVertexAttribivNV");
    glGetVertexAttribPointervNV = (PFNGLGETVERTEXATTRIBPOINTERVNVPROC) lglGetProcAddress("glGetVertexAttribPointervNV");
    glIsProgramNV = (PFNGLISPROGRAMNVPROC) lglGetProcAddress("glIsProgramNV");
    glLoadProgramNV = (PFNGLLOADPROGRAMNVPROC) lglGetProcAddress("glLoadProgramNV");
    glProgramParameter4fNV = (PFNGLPROGRAMPARAMETER4FNVPROC) lglGetProcAddress("glProgramParameter4fNV");
    glProgramParameter4dNV = (PFNGLPROGRAMPARAMETER4DNVPROC) lglGetProcAddress("glProgramParameter4dNV");
    glProgramParameter4dvNV = (PFNGLPROGRAMPARAMETER4DVNVPROC) lglGetProcAddress("glProgramParameter4dvNV");
    glProgramParameter4fvNV = (PFNGLPROGRAMPARAMETER4FVNVPROC) lglGetProcAddress("glProgramParameter4fvNV");
    glProgramParameters4dvNV = (PFNGLPROGRAMPARAMETERS4DVNVPROC) lglGetProcAddress("glProgramParameters4dvNV");
    glProgramParameters4fvNV = (PFNGLPROGRAMPARAMETERS4FVNVPROC) lglGetProcAddress("glProgramParameters4fvNV");
    glTrackMatrixNV = (PFNGLTRACKMATRIXNVPROC) lglGetProcAddress("glTrackMatrixNV");
    glVertexAttribPointerNV = (PFNGLVERTEXATTRIBPPOINTERNVPROC) lglGetProcAddress("glVertexAttribPointerNV");
    glVertexAttrib1sNV = (PFNGLVERTEXATTRIB1SNVPROC) lglGetProcAddress("glVertexAttrib1sNV");
    glVertexAttrib1fNV = (PFNGLVERTEXATTRIB1FNVPROC) lglGetProcAddress("glVertexAttrib1fNV");
    glVertexAttrib1dNV = (PFNGLVERTEXATTRIB1DNVPROC) lglGetProcAddress("glVertexAttrib1dNV");
    glVertexAttrib2sNV = (PFNGLVERTEXATTRIB2SNVPROC) lglGetProcAddress("glVertexAttrib2sNV");
    glVertexAttrib2fNV = (PFNGLVERTEXATTRIB2FNVPROC) lglGetProcAddress("glVertexAttrib2fNV");
    glVertexAttrib2dNV = (PFNGLVERTEXATTRIB2DNVPROC) lglGetProcAddress("glVertexAttrib2dNV");
    glVertexAttrib3sNV = (PFNGLVERTEXATTRIB3SNVPROC) lglGetProcAddress("glVertexAttrib3sNV");
    glVertexAttrib3fNV = (PFNGLVERTEXATTRIB3FNVPROC) lglGetProcAddress("glVertexAttrib3fNV");
    glVertexAttrib3dNV = (PFNGLVERTEXATTRIB3DNVPROC) lglGetProcAddress("glVertexAttrib3dNV");
    glVertexAttrib4sNV = (PFNGLVERTEXATTRIB4SNVPROC) lglGetProcAddress("glVertexAttrib4sNV");
    glVertexAttrib4fNV = (PFNGLVERTEXATTRIB4FNVPROC) lglGetProcAddress("glVertexAttrib4fNV");
    glVertexAttrib4dNV = (PFNGLVERTEXATTRIB4DNVPROC) lglGetProcAddress("glVertexAttrib4dNV");
    glVertexAttrib4ubNV = (PFNGLVERTEXATTRIB4UBNVPROC) lglGetProcAddress("glVertexAttrib4ubNV");
    glVertexAttrib1svNV = (PFNGLVERTEXATTRIB1SVNVPROC) lglGetProcAddress("glVertexAttrib1svNV");
    glVertexAttrib1fvNV = (PFNGLVERTEXATTRIB1FVNVPROC) lglGetProcAddress("glVertexAttrib1fvNV");
    glVertexAttrib1dvNV = (PFNGLVERTEXATTRIB1DVNVPROC) lglGetProcAddress("glVertexAttrib1dvNV");
    glVertexAttrib2svNV = (PFNGLVERTEXATTRIB2SVNVPROC) lglGetProcAddress("glVertexAttrib2svNV");
    glVertexAttrib2fvNV = (PFNGLVERTEXATTRIB2FVNVPROC) lglGetProcAddress("glVertexAttrib2fvNV");
    glVertexAttrib2dvNV = (PFNGLVERTEXATTRIB2DVNVPROC) lglGetProcAddress("glVertexAttrib2dvNV");
    glVertexAttrib3svNV = (PFNGLVERTEXATTRIB3SVNVPROC) lglGetProcAddress("glVertexAttrib3svNV");
    glVertexAttrib3fvNV = (PFNGLVERTEXATTRIB3FVNVPROC) lglGetProcAddress("glVertexAttrib3fvNV");
    glVertexAttrib3dvNV = (PFNGLVERTEXATTRIB3DVNVPROC) lglGetProcAddress("glVertexAttrib3dvNV");
    glVertexAttrib4svNV = (PFNGLVERTEXATTRIB4SVNVPROC) lglGetProcAddress("glVertexAttrib4svNV");
    glVertexAttrib4fvNV = (PFNGLVERTEXATTRIB4FVNVPROC) lglGetProcAddress("glVertexAttrib4fvNV");
    glVertexAttrib4dvNV = (PFNGLVERTEXATTRIB4DVNVPROC) lglGetProcAddress("glVertexAttrib4dvNV");
    glVertexAttrib4ubvNV = (PFNGLVERTEXATTRIB4UBVNVPROC) lglGetProcAddress("glVertexAttrib4ubvNV");
    glVertexAttribs1svNV = (PFNGLVERTEXATTRIBS1SVNVPROC) lglGetProcAddress("glVertexAttribs1svNV");
    glVertexAttribs1fvNV = (PFNGLVERTEXATTRIBS1FVNVPROC) lglGetProcAddress("glVertexAttribs1fvNV");
    glVertexAttribs1dvNV = (PFNGLVERTEXATTRIBS1DVNVPROC) lglGetProcAddress("glVertexAttribs1dvNV");
    glVertexAttribs2svNV = (PFNGLVERTEXATTRIBS2SVNVPROC) lglGetProcAddress("glVertexAttribs2svNV");
    glVertexAttribs2fvNV = (PFNGLVERTEXATTRIBS2FVNVPROC) lglGetProcAddress("glVertexAttribs2fvNV");
    glVertexAttribs2dvNV = (PFNGLVERTEXATTRIBS2DVNVPROC) lglGetProcAddress("glVertexAttribs2dvNV");
    glVertexAttribs3svNV = (PFNGLVERTEXATTRIBS3SVNVPROC) lglGetProcAddress("glVertexAttribs3svNV");
    glVertexAttribs3fvNV = (PFNGLVERTEXATTRIBS3FVNVPROC) lglGetProcAddress("glVertexAttribs3fvNV");
    glVertexAttribs3dvNV = (PFNGLVERTEXATTRIBS3DVNVPROC) lglGetProcAddress("glVertexAttribs3dvNV");
    glVertexAttribs4svNV = (PFNGLVERTEXATTRIBS4SVNVPROC) lglGetProcAddress("glVertexAttribs4svNV");
    glVertexAttribs4fvNV = (PFNGLVERTEXATTRIBS4FVNVPROC) lglGetProcAddress("glVertexAttribs4fvNV");
    glVertexAttribs4dvNV = (PFNGLVERTEXATTRIBS4DVNVPROC) lglGetProcAddress("glVertexAttribs4dvNV");
    glVertexAttribs4ubvNV = (PFNGLVERTEXATTRIBS4UBVNVPROC) lglGetProcAddress("glVertexAttribs4ubvNV");
}

void InitEXTVertexWeighting( ExtensionTypes * SupportedExtensions )
{
    if (!SupportedExtensions->EXT_vertex_weighting)
        return;
    glVertexWeightfEXT = (PFNGLVERTEXWEIGHTFEXTPROC) lglGetProcAddress("glVertexWeightfEXT");
    glVertexWeightfvEXT = (PFNGLVERTEXWEIGHTFVEXTPROC) lglGetProcAddress("glVertexWeightfvEXT");
    glVertexWeightPointerEXT = (PFNGLVERTEXWEIGHTPOINTEREXTPROC) lglGetProcAddress("glVertexWeightPointerEXT");
}

void InitARBMultisample( ExtensionTypes * SupportedExtensions )
{
    if (!SupportedExtensions->ARB_multisample)
        return;
    glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC) lglGetProcAddress("glSampleCoverageARB");
}

void InitNVRegisterCombiners( ExtensionTypes * SupportedExtensions )
{
    if (!SupportedExtensions->NV_register_combiners)
        return;
    glCombinerParameterfvNV = (PFNGLCOMBINERPARAMETERFVNVPROC) lglGetProcAddress("glCombinerParameterfvNV");
    glCombinerParameterfNV = (PFNGLCOMBINERPARAMETERFNVPROC) lglGetProcAddress("glCombinerParameterfNV");
    glCombinerParameterivNV = (PFNGLCOMBINERPARAMETERIVNVPROC) lglGetProcAddress("glCombinerParameterivNV");
    glCombinerParameteriNV = (PFNGLCOMBINERPARAMETERINVPROC) lglGetProcAddress("glCombinerParameteriNV");
    glCombinerInputNV = (PFNGLCOMBINERINPUTNVPROC) lglGetProcAddress("glCombinerInputNV");
    glCombinerOutputNV = (PFNGLCOMBINEROUTPUTNVPROC) lglGetProcAddress("glCombinerOutputNV");
    glFinalCombinerInputNV = (PFNGLFINALCOMBINERINPUTNVPROC) lglGetProcAddress("glFinalCombinerInputNV");
    glGetCombinerInputParameterfvNV = (PFNGLGETCOMBINERINPUTPARAMETERFVNVPROC) lglGetProcAddress("glGetCombinerInputParameterfvNV");
    glGetCombinerInputParameterivNV = (PFNGLGETCOMBINERINPUTPARAMETERIVNVPROC) lglGetProcAddress("glGetCombinerInputParameterivNV");
    glGetCombinerOutputParameterfvNV = (PFNGLGETCOMBINEROUTPUTPARAMETERFVNVPROC) lglGetProcAddress("glGetCombinerOutputParameterfvNV");
    glGetCombinerOutputParameterivNV = (PFNGLGETCOMBINEROUTPUTPARAMETERIVNVPROC) lglGetProcAddress("glGetCombinerOutputParameterivNV");
    glGetFinalCombinerInputParameterfvNV = (PFNGLGETFINALCOMBINERINPUTPARAMETERFVNVPROC) lglGetProcAddress("glGetFinalCombinerInputParameterfvNV");
    glGetFinalCombinerInputParameterivNV = (PFNGLGETFINALCOMBINERINPUTPARAMETERIVNVPROC) lglGetProcAddress("glGetFinalCombinerInputParameterivNV");
}

void InitEXTPointParameters( ExtensionTypes * SupportedExtensions )
{
    if (!SupportedExtensions->EXT_point_parameters)
        return;
    glPointParameterfEXT = (PFNGLPOINTPARAMETERFEXTPROC) lglGetProcAddress("glPointParameterfEXT");
    glPointParameterfvEXT = (PFNGLPOINTPARAMETERFVEXTPROC) lglGetProcAddress("glPointParameterfvEXT");
}

void InitNVVertexArrayRange( ExtensionTypes * SupportedExtensions )
{
    if (!SupportedExtensions->NV_vertex_array_range)
        return;
    glFlushVertexArrayRangeNV = (PFNGLFLUSHVERTEXARRAYRANGENVPROC) lglGetProcAddress("glFlushVertexArrayRangeNV");
    glVertexArrayRangeNV = (PFNGLVERTEXARRAYRANGENVPROC) lglGetProcAddress("glVertexArrayRangeNV");
}
 
void InitEXTFogCoord( ExtensionTypes * SupportedExtensions )
{
    if (!SupportedExtensions->EXT_fog_coord)
        return;
    glFogCoordfEXT = (PFNGLFOGCOORDFEXTPROC) lglGetProcAddress("glFogCoordfEXT");
    glFogCoordfvEXT = (PFNGLFOGCOORDFVEXTPROC) lglGetProcAddress("glFogCoordfvEXT");
    glFogCoorddEXT = (PFNGLFOGCOORDDEXTPROC) lglGetProcAddress("glFogCoorddEXT");
    glFogCoorddvEXT = (PFNGLFOGCOORDDVEXTPROC) lglGetProcAddress("glFogCoorddvEXT");
    glFogCoordPointerEXT = (PFNGLFOGCOORDPOINTEREXTPROC) lglGetProcAddress("glFogCoordPointerEXT");
}

void InitEXTSecondaryColor( ExtensionTypes * SupportedExtensions )
{
    if (!SupportedExtensions->EXT_secondary_color)
        return;
    glSecondaryColor3bEXT = (PFNGLSECONDARYCOLOR3BEXTPROC) lglGetProcAddress("glSecondaryColor3bEXT");
    glSecondaryColor3bvEXT = (PFNGLSECONDARYCOLOR3BVEXTPROC) lglGetProcAddress("glSecondaryColor3bvEXT");
    glSecondaryColor3dEXT = (PFNGLSECONDARYCOLOR3DEXTPROC) lglGetProcAddress("glSecondaryColor3dEXT");
    glSecondaryColor3dvEXT = (PFNGLSECONDARYCOLOR3DVEXTPROC) lglGetProcAddress("glSecondaryColor3dvEXT");
    glSecondaryColor3fEXT = (PFNGLSECONDARYCOLOR3FEXTPROC) lglGetProcAddress("glSecondaryColor3fEXT");
    glSecondaryColor3fvEXT = (PFNGLSECONDARYCOLOR3FVEXTPROC) lglGetProcAddress("glSecondaryColor3fvEXT");
    glSecondaryColor3iEXT = (PFNGLSECONDARYCOLOR3IEXTPROC) lglGetProcAddress("glSecondaryColor3iEXT");
    glSecondaryColor3ivEXT = (PFNGLSECONDARYCOLOR3IVEXTPROC) lglGetProcAddress("glSecondaryColor3ivEXT");
    glSecondaryColor3sEXT = (PFNGLSECONDARYCOLOR3SEXTPROC) lglGetProcAddress("glSecondaryColor3sEXT");
    glSecondaryColor3svEXT = (PFNGLSECONDARYCOLOR3SVEXTPROC) lglGetProcAddress("glSecondaryColor3svEXT");
    glSecondaryColor3ubEXT = (PFNGLSECONDARYCOLOR3UBEXTPROC) lglGetProcAddress("glSecondaryColor3ubEXT");
    glSecondaryColor3ubvEXT = (PFNGLSECONDARYCOLOR3UBVEXTPROC) lglGetProcAddress("glSecondaryColor3ubvEXT");
    glSecondaryColor3uiEXT = (PFNGLSECONDARYCOLOR3UIEXTPROC) lglGetProcAddress("glSecondaryColor3uiEXT");
    glSecondaryColor3uivEXT = (PFNGLSECONDARYCOLOR3UIVEXTPROC) lglGetProcAddress("glSecondaryColor3uivEXT");
    glSecondaryColor3usEXT = (PFNGLSECONDARYCOLOR3USEXTPROC) lglGetProcAddress("glSecondaryColor3usEXT");
    glSecondaryColor3usvEXT = (PFNGLSECONDARYCOLOR3USVEXTPROC) lglGetProcAddress("glSecondaryColor3usvEXT");
    glSecondaryColorPointerEXT = (PFNGLSECONDARYCOLORPOINTEREXTPROC) lglGetProcAddress("glSecondaryColorPointerEXT");
}

void InitEXTCompiledVertexArray( ExtensionTypes * SupportedExtensions )
{
    if (!SupportedExtensions->EXT_compiled_vertex_array)
        return;
    glLockArraysEXT = (PFNGLLOCKARRAYSEXTPROC) lglGetProcAddress("glLockArraysEXT");
    glUnlockArraysEXT = (PFNGLUNLOCKARRAYSEXTPROC) lglGetProcAddress("glUnlockArraysEXT");
}

void InitARBTransposeMatrix( ExtensionTypes * SupportedExtensions )
{
    if (!SupportedExtensions->ARB_transpose_matrix)
        return;
    glLoadTransposeMatrixf = (PFNGLLOADTRANSPOSEMATRIXFPROC) lglGetProcAddress("glLoadTransposeMatrixfARB");
    glLoadTransposeMatrixd = (PFNGLLOADTRANSPOSEMATRIXDPROC) lglGetProcAddress("glLoadTransposeMatrixdARB");
    glMultTransposeMatrixf = (PFNGLMULTTRANSPOSEMATRIXFPROC) lglGetProcAddress("glMultTransposeMatrixfARB");
    glMultTransposeMatrixd = (PFNGLMULTTRANSPOSEMATRIXDPROC) lglGetProcAddress("glMultTransposeMatrixdARB");
}

void InitARBMultitexture( ExtensionTypes * SupportedExtensions )
{
    if (!SupportedExtensions->ARB_multitexture)
        return;
#ifdef _WIN32
    glActiveTextureARB = (PFNGLACTIVETEXTUREPROC) lglGetProcAddress("glActiveTextureARB");
    glClientActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREPROC) lglGetProcAddress("glClientActiveTextureARB");

    glMultiTexCoord1dARB = (PFNGLMULTITEXCOORD1DPROC) lglGetProcAddress("glMultiTexCoord1dARB");
    glMultiTexCoord1dvARB = (PFNGLMULTITEXCOORD1DVPROC) lglGetProcAddress("glMultiTexCoord1dvARB");
    glMultiTexCoord1fARB = (PFNGLMULTITEXCOORD1FPROC) lglGetProcAddress("glMultiTexCoord1fARB");
    glMultiTexCoord1fvARB = (PFNGLMULTITEXCOORD1FVPROC) lglGetProcAddress("glMultiTexCoord1fvARB");
    glMultiTexCoord1iARB = (PFNGLMULTITEXCOORD1IPROC) lglGetProcAddress("glMultiTexCoord1iARB");
    glMultiTexCoord1ivARB = (PFNGLMULTITEXCOORD1IVPROC) lglGetProcAddress("glMultiTexCoord1ivARB");
    glMultiTexCoord1sARB = (PFNGLMULTITEXCOORD1SPROC) lglGetProcAddress("glMultiTexCoord1sARB");
    glMultiTexCoord1svARB = (PFNGLMULTITEXCOORD1SVPROC) lglGetProcAddress("glMultiTexCoord1svARB");

    glMultiTexCoord2dARB = (PFNGLMULTITEXCOORD2DPROC) lglGetProcAddress("glMultiTexCoord2dARB");
    glMultiTexCoord2dvARB = (PFNGLMULTITEXCOORD2DVPROC) lglGetProcAddress("glMultiTexCoord2dvARB");
    glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FPROC) lglGetProcAddress("glMultiTexCoord2fARB");
    glMultiTexCoord2fvARB = (PFNGLMULTITEXCOORD2FVPROC) lglGetProcAddress("glMultiTexCoord2fvARB");
    glMultiTexCoord2iARB = (PFNGLMULTITEXCOORD2IPROC) lglGetProcAddress("glMultiTexCoord2iARB");
    glMultiTexCoord2ivARB = (PFNGLMULTITEXCOORD2IVPROC) lglGetProcAddress("glMultiTexCoord2ivARB");
    glMultiTexCoord2sARB = (PFNGLMULTITEXCOORD2SPROC) lglGetProcAddress("glMultiTexCoord2sARB");
    glMultiTexCoord2svARB = (PFNGLMULTITEXCOORD2SVPROC) lglGetProcAddress("glMultiTexCoord2svARB");

    glMultiTexCoord3dARB = (PFNGLMULTITEXCOORD3DPROC) lglGetProcAddress("glMultiTexCoord3dARB");
    glMultiTexCoord3dvARB = (PFNGLMULTITEXCOORD3DVPROC) lglGetProcAddress("glMultiTexCoord3dvARB");
    glMultiTexCoord3fARB = (PFNGLMULTITEXCOORD3FPROC) lglGetProcAddress("glMultiTexCoord3fARB");
    glMultiTexCoord3fvARB = (PFNGLMULTITEXCOORD3FVPROC) lglGetProcAddress("glMultiTexCoord3fvARB");
    glMultiTexCoord3iARB = (PFNGLMULTITEXCOORD3IPROC) lglGetProcAddress("glMultiTexCoord3iARB");
    glMultiTexCoord3ivARB = (PFNGLMULTITEXCOORD3IVPROC) lglGetProcAddress("glMultiTexCoord3ivARB");
    glMultiTexCoord3sARB = (PFNGLMULTITEXCOORD3SPROC) lglGetProcAddress("glMultiTexCoord3sARB");
    glMultiTexCoord3svARB = (PFNGLMULTITEXCOORD3SVPROC) lglGetProcAddress("glMultiTexCoord3svARB");

    glMultiTexCoord4dARB = (PFNGLMULTITEXCOORD4DPROC) lglGetProcAddress("glMultiTexCoord4dARB");
    glMultiTexCoord4dvARB = (PFNGLMULTITEXCOORD4DVPROC) lglGetProcAddress("glMultiTexCoord4dvARB");
    glMultiTexCoord4fARB = (PFNGLMULTITEXCOORD4FPROC) lglGetProcAddress("glMultiTexCoord4fARB");
    glMultiTexCoord4fvARB = (PFNGLMULTITEXCOORD4FVPROC) lglGetProcAddress("glMultiTexCoord4fvARB");
    glMultiTexCoord4iARB = (PFNGLMULTITEXCOORD4IPROC) lglGetProcAddress("glMultiTexCoord4iARB");
    glMultiTexCoord4ivARB = (PFNGLMULTITEXCOORD4IVPROC) lglGetProcAddress("glMultiTexCoord4ivARB");
    glMultiTexCoord4sARB = (PFNGLMULTITEXCOORD4SPROC) lglGetProcAddress("glMultiTexCoord4sARB");
    glMultiTexCoord4svARB = (PFNGLMULTITEXCOORD4SVPROC) lglGetProcAddress("glMultiTexCoord4svARB");
#endif 
}

void InitOpenGL1_2()
{
    char *s = (char*) glGetString(GL_VERSION);
    s = strstr(s, "1.");
    if (s == NULL) return;
    if (s[2] < '2') return;
#ifdef _WIN32
    glTexImage3D = (PFNGLTEXIMAGE3DPROC) lglGetProcAddress("glTexImage3D");
    glTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC) lglGetProcAddress("glTexSubImage3D");
    glCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC) lglGetProcAddress("glCopyTexSubImage3D");
    glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC) lglGetProcAddress("glDrawRangeElements");
#endif
}

void InitARBImaging( ExtensionTypes * SupportedExtensions )
{
    if (!SupportedExtensions->ARB_imaging)
        return;
    glBlendColor = (PFNGLBLENDCOLORPROC) lglGetProcAddress("glBlendColor");
    glBlendEquation = (PFNGLBLENDEQUATIONPROC) lglGetProcAddress("glBlendEquation");
    glColorTable = (PFNGLCOLORTABLEPROC) lglGetProcAddress("glColorTable");
    glColorTableParameterfv = (PFNGLCOLORTABLEPARAMETERFVPROC) lglGetProcAddress("glColorTableParameterfv");
    glColorTableParameteriv = (PFNGLCOLORTABLEPARAMETERIVPROC) lglGetProcAddress("glColorTableParameteriv");
    glCopyColorTable = (PFNGLCOPYCOLORTABLEPROC) lglGetProcAddress("glCopyColorTable");
    glGetColorTable = (PFNGLGETCOLORTABLEPROC) lglGetProcAddress("glGetColorTable");
    glGetColorTableParameterfv = (PFNGLGETCOLORTABLEPARAMETERFVPROC) lglGetProcAddress("glGetColorTableParameterfv");
    glGetColorTableParameteriv = (PFNGLGETCOLORTABLEPARAMETERIVPROC) lglGetProcAddress("glGetColorTableParameteriv");
    glColorSubTable = (PFNGLCOLORSUBTABLEPROC) lglGetProcAddress("glColorSubTable");
    glCopyColorSubTable = (PFNGLCOPYCOLORSUBTABLEPROC) lglGetProcAddress("glCopyColorSubTable");
    glConvolutionFilter1D = (PFNGLCONVOLUTIONFILTER1DPROC) lglGetProcAddress("glConvolutionFilter1D");
    glConvolutionFilter2D = (PFNGLCONVOLUTIONFILTER2DPROC) lglGetProcAddress("glConvolutionFilter2D");
    glConvolutionParameterf = (PFNGLCONVOLUTIONPARAMETERFPROC) lglGetProcAddress("glConvolutionParameterf");
    glConvolutionParameterfv = (PFNGLCONVOLUTIONPARAMETERFVPROC) lglGetProcAddress("glConvolutionParameterfv");
    glConvolutionParameteri = (PFNGLCONVOLUTIONPARAMETERIPROC) lglGetProcAddress("glConvolutionParameteri");
    glConvolutionParameteriv = (PFNGLCONVOLUTIONPARAMETERIVPROC) lglGetProcAddress("glConvolutionParameteriv");
    glCopyConvolutionFilter1D = (PFNGLCOPYCONVOLUTIONFILTER1DPROC) lglGetProcAddress("glCopyConvolutionFilter1D");
    glCopyConvolutionFilter2D = (PFNGLCOPYCONVOLUTIONFILTER2DPROC) lglGetProcAddress("glCopyConvolutionFilter2D");
    glGetConvolutionFilter = (PFNGLGETCONVOLUTIONFILTERPROC) lglGetProcAddress("glGetConvolutionFilter");
    glGetConvolutionParameterfv = (PFNGLGETCONVOLUTIONPARAMETERFVPROC) lglGetProcAddress("glGetConvolutionParameterfv");
    glGetConvolutionParameteriv = (PFNGLGETCONVOLUTIONPARAMETERIVPROC) lglGetProcAddress("glGetConvolutionParameteriv");
    glGetSeparableFilter = (PFNGLGETSEPARABLEFILTERPROC) lglGetProcAddress("glGetSeparableFilter");
    glSeparableFilter2D = (PFNGLSEPARABLEFILTER2DPROC) lglGetProcAddress("glSeparableFilter2D");
    glGetHistogram = (PFNGLGETHISTOGRAMPROC) lglGetProcAddress("glGetHistogram");
    glGetHistogramParameterfv = (PFNGLGETHISTOGRAMPARAMETERFVPROC) lglGetProcAddress("glGetHistogramParameterfv");
    glGetHistogramParameteriv = (PFNGLGETHISTOGRAMPARAMETERIVPROC) lglGetProcAddress("glGetHistogramParameteriv");
    glGetMinmax = (PFNGLGETMINMAXPROC) lglGetProcAddress("glGetMinmax");
    glGetMinmaxParameterfv = (PFNGLGETMINMAXPARAMETERFVPROC) lglGetProcAddress("glGetMinmaxParameterfv");
    glGetMinmaxParameteriv = (PFNGLGETMINMAXPARAMETERIVPROC) lglGetProcAddress("glGetMinmaxParameteriv");
    glHistogram = (PFNGLHISTOGRAMPROC) lglGetProcAddress("glHistogram");
    glMinmax = (PFNGLMINMAXPROC) lglGetProcAddress("glMinmax");
    glResetHistogram = (PFNGLRESETHISTOGRAMPROC) lglGetProcAddress("glResetHistogram");
    glResetMinmax = (PFNGLRESETMINMAXPROC) lglGetProcAddress("glResetMinmax");
}

void InitOpenGL1_3()
{
    char *s = (char*) glGetString(GL_VERSION);
    s = strstr(s, "1.");
    if (s == NULL) return;
    if (s[2] < '3') return;
#ifdef _WIN32    
    glActiveTexture = (PFNGLACTIVETEXTUREPROC) lglGetProcAddress("glActiveTexture");
    glClientActiveTexture = (PFNGLCLIENTACTIVETEXTUREPROC) lglGetProcAddress("glClientActiveTexture");

    glMultiTexCoord1d = (PFNGLMULTITEXCOORD1DPROC) lglGetProcAddress("glMultiTexCoord1d");
    glMultiTexCoord1dv = (PFNGLMULTITEXCOORD1DVPROC) lglGetProcAddress("glMultiTexCoord1dv");
    glMultiTexCoord1f = (PFNGLMULTITEXCOORD1FPROC) lglGetProcAddress("glMultiTexCoord1f");
    glMultiTexCoord1fv = (PFNGLMULTITEXCOORD1FVPROC) lglGetProcAddress("glMultiTexCoord1fv");
    glMultiTexCoord1i = (PFNGLMULTITEXCOORD1IPROC) lglGetProcAddress("glMultiTexCoord1i");
    glMultiTexCoord1iv = (PFNGLMULTITEXCOORD1IVPROC) lglGetProcAddress("glMultiTexCoord1iv");
    glMultiTexCoord1s = (PFNGLMULTITEXCOORD1SPROC) lglGetProcAddress("glMultiTexCoord1s");
    glMultiTexCoord1sv = (PFNGLMULTITEXCOORD1SVPROC) lglGetProcAddress("glMultiTexCoord1sv");

    glMultiTexCoord2d = (PFNGLMULTITEXCOORD2DPROC) lglGetProcAddress("glMultiTexCoord2d");
    glMultiTexCoord2dv = (PFNGLMULTITEXCOORD2DVPROC) lglGetProcAddress("glMultiTexCoord2dv");
    glMultiTexCoord2f = (PFNGLMULTITEXCOORD2FPROC) lglGetProcAddress("glMultiTexCoord2f");
    glMultiTexCoord2fv = (PFNGLMULTITEXCOORD2FVPROC) lglGetProcAddress("glMultiTexCoord2fv");
    glMultiTexCoord2i = (PFNGLMULTITEXCOORD2IPROC) lglGetProcAddress("glMultiTexCoord2i");
    glMultiTexCoord2iv = (PFNGLMULTITEXCOORD2IVPROC) lglGetProcAddress("glMultiTexCoord2iv");
    glMultiTexCoord2s = (PFNGLMULTITEXCOORD2SPROC) lglGetProcAddress("glMultiTexCoord2s");
    glMultiTexCoord2sv = (PFNGLMULTITEXCOORD2SVPROC) lglGetProcAddress("glMultiTexCoord2sv");

    glMultiTexCoord3d = (PFNGLMULTITEXCOORD3DPROC) lglGetProcAddress("glMultiTexCoord3d");
    glMultiTexCoord3dv = (PFNGLMULTITEXCOORD3DVPROC) lglGetProcAddress("glMultiTexCoord3dv");
    glMultiTexCoord3f = (PFNGLMULTITEXCOORD3FPROC) lglGetProcAddress("glMultiTexCoord3f");
    glMultiTexCoord3fv = (PFNGLMULTITEXCOORD3FVPROC) lglGetProcAddress("glMultiTexCoord3fv");
    glMultiTexCoord3i = (PFNGLMULTITEXCOORD3IPROC) lglGetProcAddress("glMultiTexCoord3i");
    glMultiTexCoord3iv = (PFNGLMULTITEXCOORD3IVPROC) lglGetProcAddress("glMultiTexCoord3iv");
    glMultiTexCoord3s = (PFNGLMULTITEXCOORD3SPROC) lglGetProcAddress("glMultiTexCoord3s");
    glMultiTexCoord3sv = (PFNGLMULTITEXCOORD3SVPROC) lglGetProcAddress("glMultiTexCoord3sv");

    glMultiTexCoord4d = (PFNGLMULTITEXCOORD4DPROC) lglGetProcAddress("glMultiTexCoord4d");
    glMultiTexCoord4dv = (PFNGLMULTITEXCOORD4DVPROC) lglGetProcAddress("glMultiTexCoord4dv");
    glMultiTexCoord4f = (PFNGLMULTITEXCOORD4FPROC) lglGetProcAddress("glMultiTexCoord4f");
    glMultiTexCoord4fv = (PFNGLMULTITEXCOORD4FVPROC) lglGetProcAddress("glMultiTexCoord4fv");
    glMultiTexCoord4i = (PFNGLMULTITEXCOORD4IPROC) lglGetProcAddress("glMultiTexCoord4i");
    glMultiTexCoord4iv = (PFNGLMULTITEXCOORD4IVPROC) lglGetProcAddress("glMultiTexCoord4iv");
    glMultiTexCoord4s = (PFNGLMULTITEXCOORD4SPROC) lglGetProcAddress("glMultiTexCoord4s");
    glMultiTexCoord4sv = (PFNGLMULTITEXCOORD4SVPROC) lglGetProcAddress("glMultiTexCoord4sv");

    glLoadTransposeMatrixf = (PFNGLLOADTRANSPOSEMATRIXFPROC) lglGetProcAddress("glLoadTransposeMatrixf");
    glLoadTransposeMatrixd = (PFNGLLOADTRANSPOSEMATRIXDPROC) lglGetProcAddress("glLoadTransposeMatrixd");
    glMultTransposeMatrixf = (PFNGLMULTTRANSPOSEMATRIXFPROC) lglGetProcAddress("glMultTransposeMatrixf");
    glMultTransposeMatrixd = (PFNGLMULTTRANSPOSEMATRIXDPROC) lglGetProcAddress("glMultTransposeMatrixd");
    glCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC) lglGetProcAddress("glCompressedTexImage3D");
    glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC) lglGetProcAddress("glCompressedTexImage2D");
    glCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1DPROC) lglGetProcAddress("glCompressedTexImage1D");
    glCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) lglGetProcAddress("glCompressedTexSubImage3D");
    glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) lglGetProcAddress("glCompressedTexSubImage2D");
    glCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC) lglGetProcAddress("glCompressedTexSubImage1D");
    glGetCompressedTexImage = (PFNGLGETCOMPRESSEDTEXIMAGEPROC) lglGetProcAddress("glGetCompressedTexImage");

    glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC) lglGetProcAddress("glSampleCoverage");
#endif
}

#endif /* __PROTOTYPE__ */

void InitSupportedExtensions( ExtensionTypes * SupportedExtensions )
{
    char *s = (char*) glGetString(GL_VERSION);
    s = strstr(s, "1.");
    if (s == NULL)
    {
        SupportedExtensions->OpenGL12 = 0;    
        SupportedExtensions->OpenGL13 = 0;    
    }
    if (s[2] < '2')
    {
        SupportedExtensions->OpenGL12 = 0;    
        SupportedExtensions->OpenGL13 = 0;    
    }
    if (s[2] <= '2')
    {
        SupportedExtensions->OpenGL12 = 1;    
        SupportedExtensions->OpenGL13 = 0;    
    }
    if (s[2] <= '3')
    {
        SupportedExtensions->OpenGL12 = 1;    
        SupportedExtensions->OpenGL13 = 1;    
    }
    SupportedExtensions->ARB_imaging = QueryExtension("GL_ARB_imaging ");
    SupportedExtensions->ARB_matrix_palette = QueryExtension("GL_ARB_matrix_palette ");
    SupportedExtensions->ARB_multisample = QueryExtension("GL_ARB_multisample ");
    SupportedExtensions->ARB_multitexture = QueryExtension("GL_ARB_multitexture ");
    SupportedExtensions->ARB_point_parameters = QueryExtension("GL_ARB_point_parameters ");
    SupportedExtensions->ARB_texture_border_clamp = QueryExtension("GL_ARB_texture_border_clamp ");
    SupportedExtensions->ARB_texture_compression = QueryExtension("GL_ARB_texture_compression ");
    SupportedExtensions->ARB_texture_cube_map = QueryExtension("GL_ARB_texture_cube_map ");
    SupportedExtensions->ARB_texture_env_add = QueryExtension("GL_ARB_texture_env_add ");
    SupportedExtensions->ARB_texture_env_combine = QueryExtension("GL_ARB_texture_env_combine ");
    SupportedExtensions->ARB_texture_env_crossbar = QueryExtension("GL_ARB_texture_env_crossbar ");
    SupportedExtensions->ARB_texture_env_dot3 = QueryExtension("GL_ARB_texture_env_dot3 ");
    SupportedExtensions->ARB_transpose_matrix = QueryExtension("GL_ARB_transpose_matrix ");
    SupportedExtensions->ARB_vertex_blend = QueryExtension("GL_ARB_vertex_blend ");
    SupportedExtensions->ATI_element_array = QueryExtension("GL_ATI_element_array ");
    SupportedExtensions->ATI_envmap_bumpmap = QueryExtension("GL_ATI_envmap_bumpmap ");
    SupportedExtensions->ATI_fragment_shader = QueryExtension("GL_ATI_fragment_shader ");
    SupportedExtensions->ATI_pn_triangles = QueryExtension("GL_ATI_pn_triangles ");
    SupportedExtensions->ATI_texture_mirror_once = QueryExtension("GL_ATI_texture_mirror_once ");
    SupportedExtensions->ATI_vertex_array_object = QueryExtension("GL_ATI_vertex_array_object ");
    SupportedExtensions->ATI_vertex_streams = QueryExtension("GL_ATI_vertex_streams ");
    SupportedExtensions->ATIX_point_sprites = QueryExtension("GL_ATIX_point_sprites ");
    SupportedExtensions->ATIX_texture_env_route = QueryExtension("GL_ATIX_texture_env_route ");
    SupportedExtensions->EXT_abgr = QueryExtension("GL_EXT_abgr ");
    SupportedExtensions->EXT_compiled_vertex_array = QueryExtension("GL_EXT_compiled_vertex_array ");
    SupportedExtensions->EXT_fog_coord = QueryExtension("GL_EXT_fog_coord ");
    SupportedExtensions->EXT_multi_draw_arrays = QueryExtension("GL_EXT_multi_draw_arrays ");
    SupportedExtensions->EXT_point_parameters = QueryExtension("GL_EXT_point_parameters ");
    SupportedExtensions->EXT_secondary_color = QueryExtension("GL_EXT_secondary_color ");
    SupportedExtensions->EXT_stencil_wrap = QueryExtension("GL_EXT_stencil_wrap ");
    SupportedExtensions->EXT_texture_filter_anisotropic = QueryExtension("GL_EXT_texture_filter_anisotropic ");
    SupportedExtensions->EXT_texture_lod_bias = QueryExtension("GL_EXT_texture_lod_bias ");
    SupportedExtensions->EXT_vertex_shader = QueryExtension("GL_EXT_vertex_shader ");
    SupportedExtensions->EXT_vertex_weighting = QueryExtension("GL_EXT_vertex_weighting ");
    SupportedExtensions->HP_occlusion_test = QueryExtension("GL_HP_occlusion_test ");
    SupportedExtensions->NV_blend_square = QueryExtension("GL_NV_blend_square ");
    SupportedExtensions->NV_copy_depth_to_color = QueryExtension("GL_NV_copy_depth_to_color ");
    SupportedExtensions->NV_evaluators = QueryExtension("GL_NV_evaluators ");
    SupportedExtensions->NV_fence = QueryExtension("GL_NV_fence ");
    SupportedExtensions->NV_fog_distance = QueryExtension("GL_NV_fog_distance ");
    SupportedExtensions->NV_light_max_exponent = QueryExtension("GL_NV_light_max_exponent ");
    SupportedExtensions->NV_packed_depth_stencil = QueryExtension("GL_NV_packed_depth_stencil ");
    SupportedExtensions->NV_register_combiners = QueryExtension("GL_NV_register_combiners ");
    SupportedExtensions->NV_register_combiners2 = QueryExtension("GL_NV_register_combiners2 ");
    SupportedExtensions->NV_texgen_reflection = QueryExtension("GL_NV_texgen_reflection ");
    SupportedExtensions->NV_texture_env_combine4 = QueryExtension("GL_NV_texture_env_combine4 ");
    SupportedExtensions->NV_texture_rectangle = QueryExtension("GL_NV_texture_rectangle ");
    SupportedExtensions->NV_texture_shader = QueryExtension("GL_NV_texture_shader ");
    SupportedExtensions->NV_texture_shader2 = QueryExtension("GL_NV_texture_shader2 ");
    SupportedExtensions->NV_vertex_array_range = QueryExtension("GL_NV_vertex_array_range ");
    SupportedExtensions->NV_vertex_array_range2 = QueryExtension("GL_NV_vertex_array_range2 ");
    SupportedExtensions->NV_vertex_program = QueryExtension("GL_NV_vertex_program ");
    SupportedExtensions->SGIS_generate_mipmap = QueryExtension("GL_SGIS_generate_mipmap ");
    SupportedExtensions->SGIX_depth_texture = QueryExtension("GL_SGIX_depth_texture ");
    SupportedExtensions->SGIX_shadow = QueryExtension("GL_SGIX_shadow ");
    
}

/* init the extensions and load all the functions */
/*int glInitialize()*/
int glInitExtensionLibrary( ExtensionTypes * SupportedExtensions )
{
    //error = 0;
    InitSupportedExtensions( SupportedExtensions );
    
    /* first load the etensions */
    InitARBImaging( SupportedExtensions );
    InitARBTransposeMatrix( SupportedExtensions );
    InitARBMultisample( SupportedExtensions );
    InitEXTCompiledVertexArray( SupportedExtensions );
    InitEXTSecondaryColor( SupportedExtensions );
    InitEXTFogCoord( SupportedExtensions );
    InitNVVertexArrayRange( SupportedExtensions );
    InitEXTPointParameters( SupportedExtensions );
    InitNVRegisterCombiners( SupportedExtensions );
    InitEXTVertexWeighting( SupportedExtensions );
    InitNVVertexProgram( SupportedExtensions );
    InitNVFence( SupportedExtensions );
    InitNVRegisterCombiners2( SupportedExtensions );
    InitATIPNTriangles( SupportedExtensions );
    InitARBPointParameters( SupportedExtensions );
    InitARBVertexBlend( SupportedExtensions );
    InitEXTMultiDrawArrays( SupportedExtensions );
    InitARBMatrixPalette( SupportedExtensions );
    InitEXTVertexShader( SupportedExtensions );
    InitATIEnvmapBumpmap( SupportedExtensions );
    InitATIFragmentShader( SupportedExtensions );
    InitATIElementArray( SupportedExtensions );
    InitATIVertexStreams( SupportedExtensions );
    InitATIVertexArrayObject( SupportedExtensions );
#ifdef _WIN32
    InitARBMultitexture( SupportedExtensions );
    /* now load core opengl */
    InitOpenGL1_2();
    InitOpenGL1_3();
#endif
    return 1;
}

