/***************************************************************************/
/*                                                                         */
/*  cpw_primitives.c                                                       */
/*                                                                         */
/*    Primitives drawing interface.                                        */
/*                                                                         */
/*  Copyright 2001-2002 by                                                 */
/*  Jim Mathies, Silicon Graphics                                          */
/*                                                                         */
/*  Some of this code is copyright Silicon Graphics Inc. See the SGI       */
/*  copyright for more info. SGI code is plainly marked as such.           */
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

/***************************************************************************/
/*                                                                         */
/*  (c) Copyright 1993, Silicon Graphics, Inc.                             */
/*                                                                         */
/*  ALL RIGHTS RESERVED                                                    */
/*                                                                         */
/*  Permission to use, copy, modify, and distribute this software          */
/*  for any purpose and without fee is hereby granted, provided            */
/*  that the above copyright notice appear in all copies and that          */
/*  both the copyright notice and this permission notice appear in         */
/*  supporting documentation, and that the name of Silicon                 */
/*  Graphics, Inc. not be used in advertising or publicity                 */
/*  pertaining to distribution of the software without specific,           */
/*  written prior permission.                                              */
/*                                                                         */
/*  THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU              */
/*  "AS-IS" AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR          */
/*  OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF               */
/*  MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  IN NO            */
/*  EVENT SHALL SILICON GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE         */
/*  ELSE FOR ANY DIRECT, SPECIAL, INCIDENTAL, INDIRECT OR                  */
/*  CONSEQUENTIAL DAMAGES OF ANY KIND, OR ANY DAMAGES WHATSOEVER,          */
/*  INCLUDING WITHOUT LIMITATION, LOSS OF PROFIT, LOSS OF USE,             */
/*  SAVINGS OR REVENUE, OR THE CLAIMS OF THIRD PARTIES, WHETHER OR         */
/*  NOT SILICON GRAPHICS, INC.  HAS BEEN ADVISED OF THE POSSIBILITY        */
/*  OF SUCH LOSS, HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,           */
/*  ARISING OUT OF OR IN CONNECTION WITH THE POSSESSION, USE OR            */
/*  PERFORMANCE OF THIS SOFTWARE.                                          */
/*                                                                         */
/*  US Government Users Restricted Rights                                  */
/*                                                                         */
/*  Use, duplication, or disclosure by the Government is subject to        */
/*  restrictions set forth in FAR 52.227.19(c)(2) or subparagraph          */
/*  (c)(1)(ii) of the Rights in Technical Data and Computer                */
/*  Software clause at DFARS 252.227-7013 and/or in similar or             */
/*  successor clauses in the FAR or the DOD or NASA FAR                    */
/*  Supplement.  Unpublished-- rights reserved under the copyright         */
/*  laws of the United States.  Contractor/manufacturer is Silicon         */
/*  Graphics, Inc., 2011 N.  Shoreline Blvd., Mountain View, CA            */
/*  94039-7311.                                                            */
/*                                                                         */
/*  OpenGL(TM) is a trademark of Silicon Graphics, Inc.                    */
/*                                                                         */
/***************************************************************************/

#include "cpw_primitives.h"
#include "cpw_primdata.h"
#include "cpw_error.h"

/*************************************************************************/
/*                                                                       */
/*   init and exit.                                                      */
/*                                                                       */
/*************************************************************************/

bool cpw_primitives_init( pCpw cpw ) 
{
    /* allocate space for the prims context */

    pCpwPrim ctx = (pCpwPrim)cpwmalloc( sizeof( CpwPrimitivesState ) );

    if ( ctx == 0 ) {
        cpw_error_set( cpw, cpw_error_outofmemory );
        return false;
    }
    memset( ctx, 0, sizeof( CpwPrimitivesState ) );

    /* various inits */

    ctx->quadObj = gluNewQuadric();
    ctx->scale = 1;
    cpw->ctx_primitives = (pVoid) ctx;
    return true;
}

void cpw_primitives_exit( pCpw cpw ) 
{
    if ( cpw->ctx_primitives )
    cpwfree( cpw->ctx_primitives );
}

/*************************************************************************/
/*                                                                       */
/*   set or reset a drawing option                                       */
/*                                                                       */
/*************************************************************************/

/* Instead of passing the parameters in when you draw a specific primitive,
   Cpw stores settings for use in all primitive drawing. Different options
   apply to each primitive. See the .h for more details */

bool cpwSetPrimitiveOpt( pCpw cpw, uint_32 option, float_32 value )
{
    pCpwPrim ctx = (pCpwPrim)cpw->ctx_primitives;
    
    switch( option ) {

        /* reset: destroys and recreates the glu quadratic used by some
           primitives, and resets all values to 0. */

        case CPW_PRIMOPT_RESET:
            gluDeleteQuadric( ctx->quadObj );
            memset( ctx, 0, sizeof( CpwPrimitivesState ) );
            ctx->quadObj = gluNewQuadric();
            ctx->scale = 1;

        /* values */

        case CPW_PRIMOPT_SIZE:
        ctx->size = value;            
        break;

        case CPW_PRIMOPT_RADIUS:
        ctx->radius = value;
        break;

        case CPW_PRIMOPT_INNERRADIUS:
        ctx->innerradius = value;
        break;

        case CPW_PRIMOPT_OUTERRADIUS:
        ctx->outerradius = value;
        break;

        case CPW_PRIMOPT_BASERADIUS:
        ctx->baseradius = value;
        break;

        case CPW_PRIMOPT_TOPRADIUS:
        ctx->topradius = value;
        break;

        case CPW_PRIMOPT_WIDTH:
        ctx->width = value;
        break;

        case CPW_PRIMOPT_HEIGHT:
        ctx->height = value;
        break;

        case CPW_PRIMOPT_SLICES:
        ctx->slices = (uint_32)value;
        break;

        case CPW_PRIMOPT_STACKS:
        ctx->stacks = (uint_32)value;
        break;

        case CPW_PRIMOPT_SCALE:
        ctx->scale = (float_32)value;
        break;

        case CPW_PRIMOPT_TEXTURE:
        if ( value == 1 ) {
          ctx->texture = true;
          gluQuadricTexture( ctx->quadObj, GL_TRUE );
        } else {
          ctx->texture = false;
          gluQuadricTexture( ctx->quadObj, GL_FALSE );
        }
        break;

        default:
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }
    return true;
}

/*************************************************************************/
/*                                                                       */
/*   draw primitive helper functions                                     */
/*                                                                       */
/*************************************************************************/

/*************************************************************************/
/*   3D primitives                                                       */
/*************************************************************************/

bool cpw_primitives_3d_wire_sphere( pCpw cpw )
{
    pCpwPrim ctx = (pCpwPrim)cpw->ctx_primitives;
    gluQuadricDrawStyle( ctx->quadObj, GLU_LINE );
    gluQuadricNormals( ctx->quadObj, GLU_SMOOTH );
    gluSphere( ctx->quadObj, ctx->radius, ctx->slices, ctx->stacks );
    return true;
}

bool cpw_primitives_3d_solid_sphere( pCpw cpw )
{
    pCpwPrim ctx = (pCpwPrim)cpw->ctx_primitives;
    gluQuadricDrawStyle( ctx->quadObj, GLU_FILL );
    gluQuadricNormals( ctx->quadObj, GLU_SMOOTH );
    gluSphere( ctx->quadObj, ctx->radius, ctx->slices, ctx->stacks );
    return true;
}

bool cpw_primitives_3d_wire_cone( pCpw cpw )
{
    pCpwPrim ctx = (pCpwPrim)cpw->ctx_primitives;
    gluQuadricDrawStyle( ctx->quadObj, GLU_LINE );
    gluQuadricNormals( ctx->quadObj, GLU_SMOOTH );
    gluCylinder( ctx->quadObj, ctx->baseradius, ctx->topradius, ctx->height, ctx->slices, 
                 ctx->stacks );
    return true;
}

bool cpw_primitives_3d_solid_cone( pCpw cpw )
{
    pCpwPrim ctx = (pCpwPrim)cpw->ctx_primitives;
    gluQuadricDrawStyle( ctx->quadObj, GLU_FILL );
    gluQuadricNormals( ctx->quadObj, GLU_SMOOTH );
    gluCylinder( ctx->quadObj, ctx->baseradius, ctx->topradius, ctx->height, ctx->slices, 
                 ctx->stacks );
    return true;
}

bool cpw_primitives_3d_wire_disk( pCpw cpw )
{
    pCpwPrim ctx = (pCpwPrim)cpw->ctx_primitives;
    gluQuadricDrawStyle( ctx->quadObj, GLU_LINE );
    gluQuadricNormals( ctx->quadObj, GLU_SMOOTH );
    gluDisk( ctx->quadObj, ctx->innerradius, ctx->outerradius, ctx->slices, ctx->stacks );
    return true;
}

bool cpw_primitives_3d_solid_disk( pCpw cpw )
{
    pCpwPrim ctx = (pCpwPrim)cpw->ctx_primitives;
    gluQuadricDrawStyle( ctx->quadObj, GLU_FILL );
    gluQuadricNormals( ctx->quadObj, GLU_SMOOTH );
    gluDisk( ctx->quadObj, ctx->innerradius, ctx->outerradius, ctx->slices, ctx->stacks );
    return true;
}

/* Silicon Graphics data */

static GLfloat n[6][3] =
{
    {-1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, -1.0}
};
static GLint faces[6][4] =
{
    {0, 1, 2, 3},
    {3, 2, 6, 7},
    {7, 6, 5, 4},
    {4, 5, 1, 0},
    {5, 6, 2, 1},
    {7, 4, 0, 3}
};

/* Silicon Graphics function */

void cpw_primitives_3d_drawbox( GLfloat size, GLenum type )
{
    GLfloat v[8][3];
    GLint i;

    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

    for (i = 5; i >= 0; i--) {
        glBegin(type);
        glNormal3fv(&n[i][0]);
        glTexCoord2d(0.0, 0.0);
        glVertex3fv(&v[faces[i][0]][0]);
        glTexCoord2d(1.0, 0.0);
        glVertex3fv(&v[faces[i][1]][0]);
        glTexCoord2d(1.0, 1.0);
        glVertex3fv(&v[faces[i][2]][0]);
        glTexCoord2d(0.0, 1.0);
        glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
}

bool cpw_primitives_3d_wire_cube( pCpw cpw )
{
    pCpwPrim ctx = (pCpwPrim)cpw->ctx_primitives;
    cpw_primitives_3d_drawbox( ctx->size, GL_LINE_LOOP );
    return true;
}

bool cpw_primitives_3d_solid_cube( pCpw cpw )
{
    pCpwPrim ctx = (pCpwPrim)cpw->ctx_primitives;
    cpw_primitives_3d_drawbox( ctx->size, GL_QUADS );
    return true;
}

/* Silicon Graphics function */

void cpw_primitives_3d_teapot( GLint grid, float_32 scale, GLenum type )
{
    float p[4][4][3], q[4][4][3], r[4][4][3], s[4][4][3];
    long i, j, k, l;

    glPushAttrib(GL_ENABLE_BIT | GL_EVAL_BIT);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_MAP2_VERTEX_3);
    glEnable(GL_MAP2_TEXTURE_COORD_2);
    glPushMatrix();
    glRotatef(270.0, 1.0, 0.0, 0.0);
    glScalef((float)0.5 * scale, (float)0.5 * scale, (float)0.5 * scale);
    glTranslatef(0.0, 0.0, -1.5);

    for (i = 0; i < 10; i++) 
    {
        for (j = 0; j < 4; j++) 
        {
            for (k = 0; k < 4; k++) 
            {
                for (l = 0; l < 3; l++) 
                {
                    p[j][k][l] = (float)cpdata[patchdata[i][j * 4 + k]][l];
                    q[j][k][l] = (float)cpdata[patchdata[i][j * 4 + (3 - k)]][l];

                    if (l == 1)
                        q[j][k][l] *= -1.0;

                    if (i < 6) {
                        r[j][k][l] = (float)
                        cpdata[patchdata[i][j * 4 + (3 - k)]][l];
                        if (l == 0)
                            r[j][k][l] *= -1.0;
                        s[j][k][l] = (float)cpdata[patchdata[i][j * 4 + k]][l];
                        if (l == 0)
                            s[j][k][l] *= -1.0;
                        if (l == 1)
                            s[j][k][l] *= -1.0;
                    }
                }
            }
        }

        glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2, &tex[0][0][0]);
        glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &p[0][0][0]);
        glMapGrid2f(grid, 0.0, 1.0, grid, 0.0, 1.0);
        glEvalMesh2(type, 0, grid, 0, grid);
        glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &q[0][0][0]);
        glEvalMesh2(type, 0, grid, 0, grid);

        if (i < 6) {
            glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &r[0][0][0]);
            glEvalMesh2(type, 0, grid, 0, grid);
            glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &s[0][0][0]);
            glEvalMesh2(type, 0, grid, 0, grid);
        }
    }
    glPopMatrix();
    glPopAttrib();
}

/* Silicon Graphics function */

void doughnut( GLfloat r, GLfloat R, GLint nsides, GLint rings )
{
    int i, j;
    GLfloat theta, phi, theta1;
    GLfloat cosTheta, sinTheta;
    GLfloat cosTheta1, sinTheta1;
    GLfloat ringDelta, sideDelta;

    ringDelta = (float)2.0 * M_PI / rings;
    sideDelta = (float)2.0 * M_PI / nsides;

    theta = (float)0.0;
    cosTheta = (float)1.0;
    sinTheta = (float)0.0;

    for (i = rings - 1; i >= 0; i--) {
        theta1 = theta + ringDelta;
        cosTheta1 = (float)cos(theta1);
        sinTheta1 = (float)sin(theta1);
        glBegin(GL_QUAD_STRIP);
        phi = 0.0;
        for (j = nsides; j >= 0; j--) {
            GLfloat cosPhi, sinPhi, dist;

            phi += sideDelta;
            cosPhi = (float)cos(phi);
            sinPhi = (float)sin(phi);
            dist = R + r * cosPhi;

            glNormal3f(cosTheta1 * cosPhi, -sinTheta1 * cosPhi, sinPhi);
            glVertex3f(cosTheta1 * dist, -sinTheta1 * dist, r * sinPhi);
            glNormal3f(cosTheta * cosPhi, -sinTheta * cosPhi, sinPhi);
            glVertex3f(cosTheta * dist, -sinTheta * dist,  r * sinPhi);
        }
        glEnd();
        theta = theta1;
        cosTheta = cosTheta1;
        sinTheta = sinTheta1;
    }
}

void cpw_primitives_3d_wiretorus( GLfloat ir, GLfloat or, GLint sides, GLint rings )
{
  glPushAttrib( GL_POLYGON_BIT );
  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  doughnut( ir, or, sides, rings );
  glPopAttrib();
}

void cpw_primitives_3d_solidtorus( GLfloat ir, GLfloat or, GLint sides, GLint rings )
{
  doughnut( ir, or, sides, rings );
}

/*************************************************************************/
/*   2D primitives                                                       */
/*************************************************************************/

bool cpw_primitives_2d_square( pCpw cpw, float_32 scale, GLenum type )
{
    glPushMatrix();

    glScalef( (float)scale, (float)scale, (float)1.0 );

    /* GL_LINE_LOOP/GL_QUADS */

    glBegin( type );

    glTexCoord2d(0.0, 0.0);    
    glVertex3f( 0.0, 0.0, 0.0 );
    glTexCoord2d(1.0, 0.0);
    glVertex3f( 1.0, 0.0, 0.0 );
    glTexCoord2d(1.0, 1.0);
    glVertex3f( 1.0, 1.0, 0.0 );
    glTexCoord2d(0.0, 1.0);
    glVertex3f( 0.0, 1.0, 0.0 );

    glEnd();

    glPopMatrix();
    return true;
}

bool cpw_primitives_2d_rectangle( pCpw cpw, float_32 scale, float_32 width, float_32 height, GLenum type )
{
    glPushMatrix();

    glScalef( (float)scale, (float)scale, (float)1.0 );

    /* GL_LINE_LOOP/GL_QUADS */

    glBegin( type );
    
    glTexCoord2d(0.0, 0.0);    
    glVertex3f( 0.0, 0.0, 0.0 );
    glTexCoord2d(1.0, 0.0);
    glVertex3f( width, 0.0, 0.0 );
    glTexCoord2d(1.0, 1.0);
    glVertex3f( width, height, 0.0 );
    glTexCoord2d(0.0, 1.0);
    glVertex3f( 0.0, height, 0.0 );

    glEnd();

    glPopMatrix();
    return true;
}

bool cpw_primitives_2d_line( pCpw cpw, float_32 length )
{
    glPushMatrix();

    glBegin( GL_LINE );
    
    glVertex3f( 0, 0.0, 0.0 );
    glVertex3f( length, 0.0, 0.0 );

    glEnd();

    glPopMatrix();
    return true;
}

/*************************************************************************/
/*                                                                       */
/*   draw a primitive                                                    */
/*                                                                       */
/*************************************************************************/

bool cpwDrawPrimitive( pCpw cpw, uint_32 primitive )
{
    pCpwPrim ctx = (pCpwPrim)cpw->ctx_primitives;
    switch( primitive ) {

        /* 3D primitives */

        case CPW_PRIM_3D_WIRESPHERE:
        cpw_primitives_3d_wire_sphere( cpw );
        break;

        case CPW_PRIM_3D_SOLIDSPHERE:
        cpw_primitives_3d_solid_sphere( cpw );
        break;

        case CPW_PRIM_3D_WIRECONE:
        cpw_primitives_3d_wire_cone( cpw );
        break;

        case CPW_PRIM_3D_SOLIDCONE:
        cpw_primitives_3d_solid_cone( cpw );
        break;

        case CPW_PRIM_3D_WIRECUBE:
        cpw_primitives_3d_wire_cube( cpw );
        break;

        case CPW_PRIM_3D_SOLIDCUBE:
        cpw_primitives_3d_solid_cube( cpw );
        break;

        case CPW_PRIM_3D_WIRETORUS:
        case CPW_PRIM_3D_WIREDOUGHNUT:
        cpw_primitives_3d_wiretorus( ctx->innerradius, ctx->outerradius, ctx->slices, ctx->stacks );
        break;

        case CPW_PRIM_3D_SOLIDTORUS:
        case CPW_PRIM_3D_SOLIDDOUGHNUT:
        cpw_primitives_3d_solidtorus( ctx->innerradius, ctx->outerradius, ctx->slices, ctx->stacks );
        break;

        case CPW_PRIM_3D_WIRETEAPOT:
        cpw_primitives_3d_teapot( 7, ctx->scale, GL_LINE );
        break;

        case CPW_PRIM_3D_SOLIDTEAPOT:
        case CPW_PRIM_3D_TEAPOTAHEDRON: /* http://www.sjbaker.org/teapot/ */
        cpw_primitives_3d_teapot( 10, ctx->scale, GL_FILL );
        break;

        case CPW_PRIM_3D_WIREDISK:
        cpw_primitives_3d_wire_disk( cpw );
        break;

        case CPW_PRIM_3D_SOLIDDISK:
        cpw_primitives_3d_solid_disk( cpw );
        break;

        /* 2D primitives */

        case CPW_PRIM_2D_SQUARE:
        cpw_primitives_2d_square( cpw, ctx->scale, GL_LINE_LOOP );
        break;

        case CPW_PRIM_2D_FILLEDSQUARE:
        cpw_primitives_2d_square( cpw, ctx->scale, GL_QUADS );
        break;

        case CPW_PRIM_2D_RECTANGLE:
        cpw_primitives_2d_rectangle( cpw, ctx->scale, ctx->width, ctx->height, GL_LINE_LOOP );
        break;

        case CPW_PRIM_2D_FILLEDRECTANGLE:
        cpw_primitives_2d_rectangle( cpw, ctx->scale, ctx->width, ctx->height, GL_QUADS );
        break;

        case CPW_PRIM_2D_LINE:
        cpw_primitives_2d_line( cpw, ctx->width );
        break;

        default:
        cpw_error_set( cpw, cpw_error_invalidparameter );
        return false;
    }
    return true;
}

