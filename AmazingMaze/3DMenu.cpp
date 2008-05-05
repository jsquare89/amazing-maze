#include "Precompiled.hpp"
#include "3DMenu.hpp"

#include "Egl/ImageButton.hpp"

namespace AmazingMaze
{
    C3DMenuItem::C3DMenuItem(const int nId, 
                             const float nX,
                             const float nY,
                             const float nZ,
                             const float nWidth, 
                             const float nHeight, 
                             const Egl::TexturePtr_t & pTexture) :
                             m_nId(nId),
                             m_pImageButton(new Egl::CImageButton(
                                nX, nY, nZ, nWidth, nHeight, pTexture)),
                             m_nLeftMargin(0),
                             m_nTopMargin(0)
    {
    }

    C3DMenuItem & 
    C3DMenuItem::ResizeTo(const float nWidth, 
                          const float nHeight)
    {
        // Set button size if we have a button
        m_pImageButton->ResizeTo(nWidth, nHeight);

        // return ourselves
        return *this;
    }

    C3DMenuItem & 
    C3DMenuItem::SetMargins(const float nLeftMargin, const float nTopMargin)
    {
        // Remove old margins
        m_pImageButton->MoveBy(-m_nLeftMargin, m_nTopMargin, 0);

        // Set new margins
        m_pImageButton->MoveBy(nLeftMargin, -nTopMargin, 0);
        m_nLeftMargin = nLeftMargin;
        m_nTopMargin = nTopMargin;
        return *this;
    }

    C3DMenuItem & 
    C3DMenuItem::SetStateImage(const MenuItemState eState, 
                               const Egl::TexturePtr_t & pTexture)
    {
        switch (eState)
        {
            // Normal
            case C3DMenuItem::NormalState:
                m_pImageButton->SetStateImage(Egl::CImageButton::NormalState, pTexture);
            break;

            // Highlighted
            case C3DMenuItem::HighlightedState:
                m_pImageButton->SetStateImage(Egl::CImageButton::HighlightedState, pTexture);
            break;

            // Selected
            case C3DMenuItem::SelectedState:
                m_pImageButton->SetStateImage(Egl::CImageButton::SelectedState, pTexture);
            break;

            // Pressed
            case C3DMenuItem::PressedState:
                m_pImageButton->SetStateImage(Egl::CImageButton::PressedState, pTexture);
            break;

            // Disabled
            case C3DMenuItem::DisabledState:
            default:
                m_pImageButton->SetStateImage(Egl::CImageButton::DisabledState, pTexture);
            break;
        }
        return *this;
    }

    const float 
    C3DMenuItem::GetWidth() const
    {
        // Return button width
        return m_pImageButton->GetWidth();
    }

    const float 
    C3DMenuItem::GetHeight() const
    {
        // Return buttin height
        return m_pImageButton->GetHeight();
    }

    void 
    C3DMenuItem::Draw()
    {
        // Ask button to draw itself
        m_pImageButton->Draw();
    }

    void 
    C3DMenuItem::ResetState()
    {
        // Ask the button to reset its state
        m_pImageButton->ResetState();
    }

    void 
    C3DMenuItem::Select()
    {
        // Forward call
        m_pImageButton->Select();
    }

    void 
    C3DMenuItem::Press()
    {
        // Forward call
        m_pImageButton->Press();
    }

    C3DMenu::C3DMenu(void) : m_vItems()
    {        
        m_citCurrentItem = m_vItems.end();
    }

    // virtual
    C3DMenu::~C3DMenu(void) throw()
    {        
    }

    // virtual 
    const float 
    C3DMenu::GetWidth() const
    {
        // Calculate width
        float nWidth = 0;
    
        // Go through items
        for (std::vector<MenuItemPtr_t>::const_iterator cit = m_vItems.begin();
            cit != m_vItems.end(); ++cit)
        {
            // Width of item is width plus left margin if any
            float nItemWidth = (*cit)->GetLeftMargin() + (*cit)->GetWidth();
            nWidth = std::max(nWidth, nItemWidth);
        }

        // Return width
        return nWidth * this->GetXScale();
    }

    // virtual 
    const float 
    C3DMenu::GetHeight() const
    {
        // Calculate height
        float nHeight = 0;
    
        // Go through items
        for (std::vector<MenuItemPtr_t>::const_iterator cit = m_vItems.begin();
            cit != m_vItems.end(); ++cit)
        {
            // Width of item is width plus left margin if any
            float nItemHeight = (*cit)->GetTopMargin() + (*cit)->GetHeight();
            nHeight += nItemHeight;
        }

        // Return height
        return nHeight * this->GetYScale();
    }    

    void 
    C3DMenu::SelectNextItem()
    {
        // We can only move next if the list has at least 2 elements
        if (m_vItems.size() > 1)
        {
            // See if we have selected the last possible item
            std::vector<MenuItemPtr_t>::const_iterator citItem =
                m_citCurrentItem;
            if (++citItem != m_vItems.end())
            {
                // We are able to select a new item
                // Unselect the previous one first
                (*m_citCurrentItem)->ResetState();
                m_citCurrentItem = citItem;
                (*m_citCurrentItem)->Select();

                // Refresh the window that holds this menu
                this->RefreshWindow();
            }
        }
    }

    void 
    C3DMenu::SelectPrevItem()
    {
        // We can only move back if the list has at least 2 elements
        if (m_vItems.size() > 1)
        {
            // See if we have selected the last possible item
            std::vector<MenuItemPtr_t>::const_iterator citItem =
                m_citCurrentItem;
            if (citItem != m_vItems.begin())
            {
                // Find prev item
                --citItem;

                // We are able to select a new item
                // Unselect the previous one first
                (*m_citCurrentItem)->ResetState();
                m_citCurrentItem = citItem;
                (*m_citCurrentItem)->Select();

                // Refresh the window that holds this menu
                this->RefreshWindow();
            }
        }
    }

    int 
    C3DMenu::GetSelectedItemId() const
    {
        // Get current item id.
        return (*m_citCurrentItem)->GetId();
    }

    C3DMenuItem & 
    C3DMenu::AddItem(const int nItemId, 
                     const float nWidth, 
                     const float nHeight, 
                     const Egl::TexturePtr_t & pTexture)
    {
        // Add item to menu
        MenuItemPtr_t pMenuItem(new C3DMenuItem(nItemId, 
            0, -this->GetHeight(), 0, nWidth, nHeight, pTexture));        

        // If this menu item is the first one then
        // select it
        if (0 == m_vItems.size())
        {
            m_vItems.push_back(pMenuItem);
            pMenuItem->Select();
            m_citCurrentItem = m_vItems.begin(); 
        }        
        else
        {
            // Check where the selected item is
            std::size_t nCurrentItemIndex = (m_citCurrentItem - m_vItems.begin());            
            m_vItems.push_back(pMenuItem);
            m_citCurrentItem = m_vItems.begin() + nCurrentItemIndex; 
        }

        // Refresh window holding this menu
        this->RefreshWindow();

        return *pMenuItem;
    }

    // virtual 
    void 
    C3DMenu::Draw()
    {   
        // Do we have items to draw?
        if (!m_vItems.empty())
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
            
            // Go through items
            for (std::vector<MenuItemPtr_t>::const_iterator cit = m_vItems.begin();
                cit != m_vItems.end(); ++cit)
            {
                // Draw image
                (*cit)->Draw();
            }

            // Restore the original movel view matrix
            glPopMatrix();
        }
    }

} // namespace AmazingMaze