#include "Precompiled.hpp"
#include "MazeNorthWallTile.hpp"

namespace AmazingMaze
{
    namespace detail
    {
        const GLfloat north_vertices[][3] = {
          {0, 0, -0.05f}, {1, 0, -0.05f},
          {1, 0,  0.05f}, {0, 0,  0.05f},
          {0, 1, -0.05f}, {1, 1, -0.05f},
          {1, 1,  0.05f}, {0, 1,  0.05f},
        };

        const GLfloat normals[][3] = {
          {-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
          {1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0}, 
          {1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}
        };

        /** Draws a polygon via list of vertices */
        static void polygon(int a, int b, int c , int d)
        {          
            glBegin(GL_POLYGON);                
                glNormal3fv(normals[a]);
                glTexCoord2f(0, 1);
                glVertex3fv(north_vertices[a]);
                glNormal3fv(normals[b]);
                glTexCoord2f(0, 0);
                glVertex3fv(north_vertices[b]);
                glNormal3fv(normals[c]);
                glTexCoord2f(1, 0);
                glVertex3fv(north_vertices[c]);
                glNormal3fv(normals[d]);
                glTexCoord2f(1, 1);
                glVertex3fv(north_vertices[d]);
            glEnd();
        }
    } // namespace detail

    CMazeNorthWallTile::CMazeNorthWallTile(void) : Egl::CModel(),
                                                   m_nPrecompiledId(1)
    {   
        // TODO
        // We hardcode the precompiled id for now
        // we should have a class that takes care of assigning
        // precompiled ids so they don't collide.

        // Call the base class
        glNewList(m_nPrecompiledId, GL_COMPILE );
            detail::polygon(0, 1, 2, 3);
            detail::polygon(1, 5, 6, 2);
            detail::polygon(4, 5, 6, 7);
            detail::polygon(0, 4, 7, 3);
            detail::polygon(0, 1, 5, 4);
            detail::polygon(3, 2, 6, 7);
        glEndList();
    }

    // virtual
    CMazeNorthWallTile::~CMazeNorthWallTile(void) throw()
    {        
    }

    // virtual 
    const float 
    CMazeNorthWallTile::GetWidth() const
    {
        float nWidth = 1;

        // Return width
        return nWidth * this->GetXScale();
    }

    // virtual 
    const float 
    CMazeNorthWallTile::GetHeight() const
    {
        // Calculate height
        float nHeight = 1;
    
        // Return height
        return nHeight * this->GetYScale();
    }    

    // virtual 
    void 
    CMazeNorthWallTile::Draw()
    {   
        // Translate and scale the model to the right location.
        // Then draw at 0,0,0 and let the model view matrix do the rest
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        const Egl::C3DPoint<float> & pLocation = this->GetPosition();
        glTranslatef(pLocation.GetX(), pLocation.GetY(), pLocation.GetZ());

        if ((0 != this->GetXScale()) || (0 != this->GetYScale()) || (0 != this->GetZScale()))
            glScalef(this->GetXScale(), this->GetYScale(), this->GetZScale());
            
        // Rotate
        if (0 != this->GetXRotation())
            glRotatef(this->GetXRotation(), 1, 0, 0);

        if (0 != this->GetYRotation())
            glRotatef(this->GetYRotation(), 0, 1, 0);

        if (0 != this->GetZRotation())
            glRotatef(this->GetZRotation(), 0, 0, 1);
            
        glCallList(m_nPrecompiledId);
        
        // Restore the original model view matrix
        glPopMatrix();
    }   

} // namespace AmazingMaze