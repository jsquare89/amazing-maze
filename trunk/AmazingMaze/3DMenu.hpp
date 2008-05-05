#pragma once

#include <boost/scoped_ptr.hpp>
#include <boost/array.hpp>
#include "Egl/Common.hpp"
#include "Egl/Model.hpp"
#include <vector>

namespace AmazingMaze
{
    /**
     * A 3D menu item.
     */
    class C3DMenuItem
    {
    public:

        /** Menu item states. */
        enum MenuItemState
        {
            /** Normal state. */
            NormalState,

            /** Highlighted state. */
            HighlightedState,

            /** Selected state. */
            SelectedState,

            /** Pressed state. */
            PressedState,

            /** Disabled state. */
            DisabledState
        };

    public:

        /** Sets width and height of menu item. */
        C3DMenuItem & ResizeTo(const float nWidth, const float nHeight);
        
        /** Sets the margins of this item. */
        C3DMenuItem & SetMargins(const float nLeftMargin, const float nTopMargin);

        /** Sets the image to use for a given state of the menu item image button. */
        C3DMenuItem & SetStateImage(const MenuItemState eState, const Egl::TexturePtr_t & pTexture);
        
        /** Select this menu item. */
        void Select();

        /** Press this menu item. */
        void Press();

        /** Reset state to NormalState. */
        void ResetState();

        /** Get width. */
        const float GetWidth() const;

        /** Get height. */
        const float GetHeight() const;

        /** Retrieves the left margin of this item. */
        const float GetLeftMargin() const { return m_nLeftMargin; }

        /** Retrieves the top margin of this item. */
        const float GetTopMargin() const { return m_nTopMargin; }

        /** Retrieves the ID of this item. */
        int GetId() const { return m_nId; }        
        
    private:

        // Disable op= and copy ctor
        C3DMenuItem(const C3DMenuItem &);
        C3DMenuItem & operator=(C3DMenuItem &);

        /** Constructor. */
        C3DMenuItem(const int nId, const float nX, const float nY,
                    const float nZ,const float nWidth, const float nHeight, 
                    const Egl::TexturePtr_t & pTexture);

        /** Draw. */
        void Draw();

    private:

        /** Id. */
        const int m_nId;

        /** Image button. */
        Egl::ImageButtonPtr_t m_pImageButton;

        /** Left margin. */
        float m_nLeftMargin;

        /** Top margin. */
        float m_nTopMargin;

    private:

        /** C3DMenu is our friend so it can create us and draw us. */
        friend class C3DMenu;
    };

    /**
     * A 3D menu composed of textured 
     * items on the screen.
     */
    class C3DMenu : public Egl::CModel
    {
    public:

        /** Constructor. */
        C3DMenu(void);

        /** Destructor */
        virtual ~C3DMenu(void) throw();

        /** Add a new item to this menu. */
        C3DMenuItem & AddItem(const int nItemId, const float nWidth, 
            const float nHeight, const Egl::TexturePtr_t & pTexture);
        
        /** Select the next item in the menu. */
        void SelectNextItem();

        /** Select the previous item in the menu. */
        void SelectPrevItem();

        /** Retrieves the ID of the selected item. Note that at least one item must be preset. */
        int GetSelectedItemId() const;

        // Inherited members
        virtual const float GetWidth() const;
        virtual const float GetHeight() const;
        virtual const float GetDepth() const { return 0; }
        virtual void Draw(void);
        
    private:

        /** Type of menu item pointer. */
        typedef boost::shared_ptr<C3DMenuItem> MenuItemPtr_t;

    private:

        /** Items. */
        std::vector<MenuItemPtr_t> m_vItems;

        /** An iterator to the currently selected item. */
        std::vector<MenuItemPtr_t>::const_iterator m_citCurrentItem;
    };
} // namespace Project2