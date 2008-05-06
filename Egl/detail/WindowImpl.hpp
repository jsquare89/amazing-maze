#pragma once

#include "Egl/Common.hpp"
#include "Egl/KeyState.hpp"
#include "Egl/MouseButton.hpp"
#include "Egl/3DPoint.hpp"

namespace Egl
{
    /** Forward declaration of CWindow. */
    class CWindow;

    namespace detail
    {        
        /** Forward declaration of CFontImpl. */
        class CFontImpl;

        /** 
         * Callback function invoked when a menu is selected. This
         * function declaration is exposed here because the menu class
         * needs it to be able to create menus. 
         */
        void OnMenuItemSelected(pCpw cpw, uint_32 nWindowId, unsigned int nMenuId, unsigned int nEntryId);

        /** CWindow implementation using Cpw. */
        class CWindowImpl
        {
        public:

            /** Constructor. */
            CWindowImpl();

            /** Initializes this window impl. */
            void Init(const CWindow * pWindow,
                      const ContextPtr_t & pContext,                      
                      const pCpw pContextHandle,
                      const boost::int64_t nSurfaceProperties,
                      const std::string & strTitle, 
                      const int nX, 
                      const int nY, 
                      const int nWidth, 
                      const int nHeight);

            /** Destructor. */
            ~CWindowImpl() throw();

            /** Set title. */
            void SetTitle(const std::string & strTitle);

            /** Set position. */
            void MoveTo(int nX, int nY);

            /** Set size. */
            void Resize(int nWidth, int nHeight);

            /** Show. */
            void Show(void);

            /** Hide. */
            void Hide(void);

            /** Set full screen. */
            void SetFullScreen(void);

            /** Retrieves whether this window is full screen. */
            bool IsFullScreen() const { return m_bFullScreen; }

            /** Restores this window. */
            void Restore();

            /** Retrieves the context for this window. */
            const ContextPtr_t & GetContext() const { return m_pContext; }

            /** Fire draw event. */
            void OnDraw();

            /** Fire reshape event. */
            void OnReshape(int nWidth, int nHeight);

            /** Fire Key event. */
            void OnKey(int nKeyCode, bool bIsSystemKey, Egl::KeyState_e eKeyState, int nCursorX, int nCursorY);

            /** Fire Create event. */
            void OnCreate();

            /** Fire Destroy event. */
            void OnDestroy();

            /** Fire TitlebarMenuItemSelected or ContextMenuItemSelected event. */
            void OnMenuItemSelected(int nMenuId, int nItemId);

            /** Swaps the buffers of this screen. */
            void SwapBuffers();

            /**
             * Gets the window title.
             *
             * @return The window title.         
             */
            const std::string & GetTitle() const { return m_strTitle; }

            /**
             * Gets the X position of this window.
             *
             * @return The X position of this window.         
             */
            int GetX() const { return m_nX; }

            /**
             * Gets the Y position of this window.
             *
             * @return The Y position of this window.         
             */
            int GetY() const { return m_nY; }

            /**
             * Gets the width of this window.
             *
             * @return The width of this window.         
             */
            int GetWidth() const { return m_nWidth; }

            /**
             * Gets the height of this window.
             *
             * @return The height of this window.         
             */
            int GetHeight() const { return m_nHeight; }

            /**
             * Closes and destroys this window.
             */
            void Close();

            /**
             * Sets the titlebar menu of this window. To receive notifications
             * when the menu items are selected subscribe to the 
             * TitlebarMenuItemSelected event.
             */
            void SetTitlebarMenu(const MenuPtr_t & pMenu);

            /**
             * Sets the context menu of this window. To receive notifications
             * when the menu items are selected subscribe to the 
             * ContextMenuItemSelected event.
             */
            void SetContextMenu(const MenuPtr_t & pMenu, const MouseButton_e eMouseButton);

            /** Refreshes this window to refresh (redraw itself). */
            void Refresh();

            /**
             * Draws text at a given location using a given font.
             *
             * @param strText Text to draw.
             * @param rFontImpl Font to use.
             * @param pPosition 3D raster position where the text should be drawn.
             */
            void DrawString(const std::string & strText, 
                          const CFontImpl & rFontImpl,
                          const C3DPoint<float> & pPosition);

        private:

            /** Prevent copy ctor and op=. */
            CWindowImpl(const CWindowImpl &);
            CWindowImpl & operator=(const CWindowImpl &);
        
        private:

            /** Cpw window handle. */
            unsigned int m_nHandle;

            /** Context that created the window. */
            ContextPtr_t m_pContext;

            /** Cpw window handle. */
            pCpw m_pContextHandle;

            /** Surface properties.. */
            const boost::int64_t m_nSurfaceProperties;
            
            /** Title. */
            std::string m_strTitle;

            /** X position. */
            int m_nX;

            /** Y position. */
            int m_nY;

            /** Width. */
            int m_nWidth;

            /** Height. */
            int m_nHeight;

            /** Titlebar menu. */
            MenuPtr_t m_pTitlebarMenu;

            /** Context menu. */
            MenuPtr_t m_pContextMenu;

            /** Mouse button for context menu. */
            MouseButton_e m_eContextMenuMouseButton;

            /** Raw window pointer. */
            const CWindow * m_pWindow;

            /** Whether this window is fullscreen. */
            bool m_bFullScreen;
        };
    } // namespace detail
} // namespace Egl