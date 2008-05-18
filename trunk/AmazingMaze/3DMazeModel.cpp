#include "Precompiled.hpp"
#include "3DMazeModel.hpp"
#include "MazeEastWallTile.hpp"
#include "MazeNorthWallTile.hpp"
#include "Maze.hpp"
#include "Egl/Texture.hpp"
#include "MazeRow.hpp"

namespace AmazingMaze
{    
    // explicit
    C3DMazeModel::C3DMazeModel(const MazePtr_t & pMaze) : 
                               Egl::CModel(),
                               m_pNorthWallTile(new CMazeNorthWallTile()),
                               m_pEastWallTile(new CMazeEastWallTile()),
                               m_pMaze(pMaze),
                               m_pWallTexture(),
                               m_pFloorTexture()
    {           
    }

    // virtual
    C3DMazeModel::~C3DMazeModel(void) throw()
    {        
    }

    // virtual 
    const float 
    C3DMazeModel::GetWidth() const
    {
        float nWidth = static_cast<float>(m_pMaze->GetWidth());

        // Return width
        return nWidth * this->GetXScale();
    }

    // virtual 
    const float 
    C3DMazeModel::GetHeight() const
    {
        // Calculate height
        float nHeight = static_cast<float>(m_pMaze->GetHeight());
    
        // Return height
        return nHeight * this->GetYScale();
    }    

    // virtual 
    void 
    C3DMazeModel::Draw()
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
            

        // Draw floor
        glPushMatrix();
        glTranslatef(1.4f, 0.0f, -0.5f);
        glScalef(m_pMaze->GetWidth() - .8f, 1, m_pMaze->GetHeight() - 1);
        m_pFloorTexture->Bind();

        glBegin(GL_QUADS);
            glTexCoord2f(0, 1);
            glVertex3f(0.0, 0.0f, 0.0);

            glTexCoord2f(0, 0);
            glVertex3f(1.0, 0.0f, 0.0);

            glTexCoord2f(1, 0);
            glVertex3f(1.0, 0.0f, 1.0);

            glTexCoord2f(1, 1);
            glVertex3f(0.0, 0.0f, 1.0);
        glEnd();

        m_pFloorTexture->UnBind();
        glPopMatrix();


        // Bind wall texture
        m_pWallTexture->Bind();

        // Draw each row in the maze
        for (CMaze::RowIterator_t rit = m_pMaze->GetRowsBegin(); 
             rit != m_pMaze->GetRowsEnd(); ++rit)
        {
            for (int i = 0; i < m_pMaze->GetWidth(); ++i)
            {
                // Draw north wall if present
                if ((*rit)->HasNorthWall(i))
                {
                    m_pNorthWallTile->MoveTo(i + 0.5f, 0.0f, (*rit)->GetIndex() - 0.5f);
                    m_pNorthWallTile->Draw();
                }

                // Draw east wall if present
                if ((*rit)->HasEastWall(i))
                {
                    m_pEastWallTile->MoveTo(i + 1.5f, 0.0f, (*rit)->GetIndex() - 0.5f);
                    m_pEastWallTile->Draw();
                }
            }
        }

        // Unbind wall texture
        m_pWallTexture->UnBind();

        // Restore the original model view matrix
        glPopMatrix();
    }   

} // namespace AmazingMaze