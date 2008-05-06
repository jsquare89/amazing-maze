#include "Precompiled.hpp"
#include "Egl/ImageButton.hpp"
#include "Egl/Texture.hpp"
#include "Egl/Image.hpp"

namespace Egl
{
    // explicit 
    CImageButton::CImageButton(const float nWidth, 
                               const float nHeight,
                               const TexturePtr_t & pNormalStateImage) :
                               CModel(),
                               m_aImages(),
                               m_eState(CImageButton::NormalState),
                               m_nWidth(nWidth),
                               m_nHeight(nHeight)
    {
        // Set normal state image
        m_aImages[CImageButton::NormalState].reset(new
            CImage(nWidth, nHeight, pNormalStateImage));
    }

    CImageButton::CImageButton(const float nX, 
                               const float nY, 
                               const float nZ, 
                               const float nWidth, 
                               const float nHeight,
                               const TexturePtr_t & pNormalStateImage) :
                               CModel(nX, nY, nZ),
                               m_aImages(),
                               m_eState(CImageButton::NormalState),
                               m_nWidth(nWidth),
                               m_nHeight(nHeight)
    {
        // Set normal state image
        m_aImages[CImageButton::NormalState].reset(new
            CImage(nWidth, nHeight, pNormalStateImage));
    }

    // virtual 
    CImageButton::~CImageButton(void) throw()
    {
    }

    void 
    CImageButton::ResetState()
    {
        // Set normal state
        m_eState = CImageButton::NormalState;

        // Refresh window
        this->RefreshWindow();
    }

    void 
    CImageButton::Select()
    {
        // Set current state
        m_eState = CImageButton::SelectedState;

        // Refresh window
        this->RefreshWindow();
    }

    void 
    CImageButton::ResizeTo(const float nWidth, const float nHeight)
    {
        // Resize every image we have
        for (int i = 0; i < m_aImages.static_size; ++i)
        {
            if (m_aImages[i])
            {
                m_aImages[i]->ResizeTo(nWidth, nHeight);
            }
        }

        // Save width and height
        m_nWidth = nWidth;
        m_nHeight = nHeight;
    }


    void 
    CImageButton::Press()
    {
        // Set current state
        m_eState = CImageButton::PressedState;

        // Refresh window
        this->RefreshWindow();

        // Fire on click event
        CEventArgs args;
        this->Click.Fire(*this, args);
    }

    /** Sets the image to use for a given state. */
    void 
    CImageButton::SetStateImage(const ButtonState eButtonState, 
                                const TexturePtr_t & pImage)
    {
        // Add image        
        m_aImages[eButtonState].reset(new CImage(m_nWidth,
            m_nHeight, pImage));
    }


    // virtual 
    const float 
    CImageButton::GetWidth() const
    {
        // Cached width
        return m_aImages[CImageButton::NormalState]->GetWidth() * 
            this->GetXScale();
    }

    // virtual 
    const float 
    CImageButton::GetHeight() const
    {
        // Cached height
        return m_aImages[CImageButton::NormalState]->GetHeight() * 
            this->GetYScale();
    }    
   
    // virtual 
    void 
    CImageButton::Draw()
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

        // Do we have an image for the current state?
        // otherwise draw normal state image
        if (m_aImages[m_eState])
            m_aImages[m_eState]->Draw();
        else
            m_aImages[CImageButton::NormalState]->Draw();

        // Restore the original movel view matrix
        glPopMatrix();
    }

} // namespace Egl