#include "Precompiled.hpp"
#include "Egl/Image.hpp"
#include "Egl/Texture.hpp"

namespace Egl
{
    CImage::CImage(void) : CModel(),
                           m_pTexture(),
                           m_nWidth(0),
                           m_nHeight(0)
    {
    }

    CImage::CImage(const float nX, 
                   const float nY, 
                   const float nZ) :
                   CModel(nX, nY, nZ),
                   m_pTexture(),
                   m_nWidth(0),
                   m_nHeight(0)
    {
    }

    CImage::CImage(const float nWidth, 
                   const float nHeight,
                   const TexturePtr_t & pTexture) :
                   CModel(),
                   m_pTexture(pTexture),
                   m_nWidth(nWidth),
                   m_nHeight(nHeight)
    {
    }

    CImage::CImage(const float nX, 
                   const float nY, 
                   const float nZ, 
                   const float nWidth, 
                   const float nHeight,
                   const TexturePtr_t & pTexture) : 
                   CModel(nX, nY, nZ),
                   m_pTexture(pTexture),
                   m_nWidth(nWidth),
                   m_nHeight(nHeight)
    {
    }

    // virtual 
    CImage::~CImage(void) throw()
    {
    }
    
    void 
    CImage::SetTexture(const TexturePtr_t & pTexture, 
                       const float nWidth, 
                       const float nHeight)
    {
        // Set texture, width and height
        m_pTexture = pTexture;
        m_nWidth = nWidth;
        m_nHeight = nHeight;

        // Refresh window holding this image
        this->RefreshWindow();
    }

    void 
    CImage::ResizeTo(const float nWidth, const float nHeight)
    {
        // Resize and refresh window
        m_nWidth = nWidth;
        m_nHeight = nHeight;
        this->RefreshWindow();
    }

    // virtual 
    const float 
    CImage::GetWidth() const
    {
        // Cached width
        return m_nWidth * this->GetXScale();
    }

    // virtual 
    const float 
    CImage::GetHeight() const
    {
        // Cached height
        return m_nHeight * this->GetYScale();
    }    
   
    // virtual 
    void 
    CImage::Draw()
    {   
        // Only draw if we have a texture and our width and height is not 0
        if (m_pTexture && (m_nWidth > 0) && (m_nHeight > 0))
        {
            // Translate and scale the model to the right location.
            // Then draw at 0,0,0 and let the model view matrix do the rest
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            const Egl::C3DPoint<float> & pLocation = this->GetPosition();
            glTranslatef(pLocation.GetX(), pLocation.GetY(), pLocation.GetZ());
            glScalef(this->GetXScale(), this->GetYScale(), this->GetZScale());
            
            // Rotate
            if (0 != this->GetXRotation())
                glRotatef(this->GetXRotation(), 1, 0, 0);

            if (0 != this->GetYRotation())
                glRotatef(this->GetYRotation(), 0, 1, 0);

            if (0 != this->GetZRotation())
                glRotatef(this->GetZRotation(), 0, 0, 1);
                        
            // Bind texture
            m_pTexture->Bind();

            // Draw item at the right place                
            glBegin(GL_QUADS);
            {
                // Bottom Left
                glTexCoord2f(0, 0);
	            glVertex3f(this->GetPosition().GetX(), 
                    this->GetPosition().GetY(), 
                    this->GetPosition().GetZ());

                // Top Left
                glTexCoord2f(0, 1);
                glVertex3f(this->GetPosition().GetX(),  
                    this->GetPosition().GetY() - m_nHeight, 
                    this->GetPosition().GetZ());

                // Top Right
                glTexCoord2f(1, 1);
	            glVertex3f(this->GetPosition().GetX() + m_nWidth,  
                    this->GetPosition().GetY() - m_nHeight, 
                    this->GetPosition().GetZ());

                // Bottom Right
                glTexCoord2f(1, 0);
	            glVertex3f(this->GetPosition().GetX() + m_nWidth, 
                    this->GetPosition().GetY(), 
                    this->GetPosition().GetZ());
            }
            glEnd();

            // Unbind texture
            m_pTexture->UnBind();

            // Restore the original movel view matrix
            glPopMatrix();
        }
    }

} // namespace Egl