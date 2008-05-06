#pragma once

#include "Egl/Common.hpp"
#include "Egl/Model.hpp"
#include "Egl/Event.hpp"
#include <boost/array.hpp>

namespace Egl
{
    /**
     * A model that shows as 1 of 5 images for 
     * normal, highlighted, selected, pressed 
     * and disabled states.
     */
    class CImageButton : public CModel
    {
    public:

        /** Button states. */
        enum ButtonState
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
    
    private:

        // Enum of events
        enum ButtonEvent
        {
            /** Click event. */
            CLICK_EVENT
        };

    public:

        /** Type of the Click event. */
        typedef CEvent<CImageButton, CImageButton, CEventArgs, CLICK_EVENT> ClickEvent_t;

    public:

        /** 
         * Event that will fire when the button is clicked by the mouse
         * or when the return key is pressed while the button
         * is in the selected state.
         */
        ClickEvent_t Click;

    public:

        /** Constructor. */
        explicit CImageButton(const float nWidth, const float nHeight, 
                              const TexturePtr_t & pNormalStateImage);

        /** Constructor. */
        CImageButton(const float nX, const float nY, const float nZ, 
                     const float nWidth, const float nHeight,
                     const TexturePtr_t & pNormalStateImage);

        /** Destructor */
        virtual ~CImageButton(void) throw();

        /** Select this button (changes the state to SelectedState). */
        void Select();

        /** Press this button (changes the state to PressedState and fires Click event. */
        void Press();

        /** Reset state to NormalState. */
        void ResetState();

        /** Sets the image to use for a given state. */
        void SetStateImage(const ButtonState eButtonState, const TexturePtr_t & pImage);

        /** Resize to a given width and height. */
        void ResizeTo(const float nWidth, const float nHeight);

        // Inherited members
        virtual const float GetWidth() const;
        virtual const float GetHeight() const;
        virtual const float GetDepth() const { return 0; }
        virtual void Draw(void);

    private:

        /** Images. */
        boost::array<ImagePtr_t, 5> m_aImages;
        
        /** Current state. */
        ButtonState m_eState;

        /** Width. */
        float m_nWidth;

        /** Height. */
        float m_nHeight;
    };
} // namespace Egl