#pragma once

#include <string>
#include <boost/scoped_ptr.hpp>
#include "Egl/Common.hpp"
#include "Egl/Event.hpp"
#include "Egl/KeyState.hpp"
#include "Egl/MouseButton.hpp"
#include "Egl/3DPoint.hpp"
#include <boost/cstdint.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "Egl/WindowReshapeEventArgs.hpp"
#include "Egl/KeyEventArgs.hpp"
#include "Egl/MenuItemEventArgs.hpp"

namespace Egl
{
    namespace detail
    {
        /** Forward declaration of CWindowImpl. */
        class CWindowImpl;
    } // namespace detail

    /** A window created using the GLUT library */
    class CWindow : public boost::enable_shared_from_this<CWindow>
    {
    public:

        /** Default window X. */
        static const int DEFAULT_X = 0;

        /** Default window Y. */
        static const int DEFAULT_Y = 0;

        /** Default window width. */
        static const int DEFAULT_WIDTH = 10;

        /** Default window height. */
        static const int DEFAULT_HEIGHT = 10;

    public:        

        /**
         * Gets the window title.
         *
         * @return The window title.         
         */
        const std::string & GetTitle() const;

        /**
         * Sets the window title.
         *
         * @param strTitle Window title.
         *
         * @return (*this).
         */
        CWindow & SetTitle(const std::string & strTitle);        

        /**
         * Gets the X position of this window.
         *
         * @return The X position of this window.         
         */
        int GetX() const;

        /**
         * Gets the Y position of this window.
         *
         * @return The Y position of this window.         
         */
        int GetY() const;

        /**
         * Sets the X and Y position of the window.
         *
         * @param nX The X position of the window.
         * @param nY The Y position of the window.
         *
         * @return (*this).
         */
        CWindow & MoveTo(int nX, int nY);

        /**
         * Gets the width of this window.
         *
         * @return The width of this window.         
         */
        int GetWidth() const;

        /**
         * Gets the height of this window.
         *
         * @return The height of this window.         
         */
        int GetHeight() const;

        /**
         * Sets the dimensions of the window.
         *
         * @param nWidth The width of the window.
         * @param nHeight The height of the window.
         *
         * @return (*this).
         */
        virtual CWindow & Resize(int nWidth, int nHeight);
        
        /**
         * Shows this window.
         * @return (*this).
         */
        virtual CWindow & Show(void);

        /**
         * Hides this window.
         * @return (*this).
         */
        virtual CWindow & Hide(void);

        /**
         * Makes this window full screen.
         * @return (*this).
         */
        virtual CWindow & SetFullScreen(void);

        /**
         * Creates a new window.
         * By default the window will be 10x10 pixels and it will be 
         * positioned at 0,0. By default the window has an empty title.
         *
         * @param nSurfaceProperties Surface properties. A bitwise combination
         *                           of the values in Egl::SurfaceProperties.
         */
        template <typename TWindow>
        const WindowPtr_t CreateEglWindow(const boost::int64_t nSurfaceProperties)
        {
            // Create window
            WindowPtr_t pWindow(new TWindow());
            return this->InitChildWindow(pWindow, 
                nSurfaceProperties, "", 
                CWindow::DEFAULT_X,
                CWindow::DEFAULT_Y,
                CWindow::DEFAULT_WIDTH,
                CWindow::DEFAULT_HEIGHT);
        }

        /**
         * Creates a new window.
         * By default the window will be 10x10 pixels and it will be 
         * positioned at 0,0. 
         *
         * @param nSurfaceProperties Surface properties. A bitwise combination
         *                           of the values in Egl::SurfaceProperties.
         * @param strTitle Window title.
         */
        template <typename TWindow>
        const WindowPtr_t CreateEglWindow(const boost::int64_t nSurfaceProperties, 
                                       const std::string & strTitle)
        {
            // Create window
            WindowPtr pWindow(new TWindow());
            return this->InitChildWindow(pWindow, 
                nSurfaceProperties, strTitle, 
                CWindow::DEFAULT_X,
                CWindow::DEFAULT_Y,
                CWindow::DEFAULT_WIDTH,
                CWindow::DEFAULT_HEIGHT);
        }

        /**
         * Creates a new window.
         * The default size of the window will be 10x10 pixels. 
         * By default the window has an empty title.
         *
         * @param nSurfaceProperties Surface properties. A bitwise combination
         *                           of the values in Egl::SurfaceProperties.
         * @param nX The X position of the window.
         * @param nY The Y position of the window.
         */
        template <typename TWindow>
        const WindowPtr_t CreateEglWindow(const boost::int64_t nSurfaceProperties, 
                                       int nX, int nY)
        {
            // Create window
            WindowPtr_t pWindow(new TWindow());
            return this->InitChildWindow(pWindow, 
                nSurfaceProperties, "", 
                nX,
                nY,
                CWindow::DEFAULT_WIDTH,
                CWindow::DEFAULT_HEIGHT);        
        }

        /**
         * Creates a new window. By default the window has an empty title.
         *
         * @param nSurfaceProperties Surface properties. A bitwise combination
         *                           of the values in Egl::SurfaceProperties.
         * @param nX The X position of the window.
         * @param nY The Y position of the window.
         * @param nWidth The width of the window.
         * @param nHeight The height of the window.
         */
        template <typename TWindow>
        const WindowPtr_t CreateEglWindow(const boost::int64_t nSurfaceProperties, 
                                       int nX, int nY, int nWidth, int nHeight)
        {
            // Create window
            WindowPtr_t pWindow(new TWindow());
            return this->InitChildWindow(pWindow, 
                nSurfaceProperties, "", 
                nX,
                nY,
                nWidth,
                nHeight);
        }

        /**
         * Creates a new window.
         * The default size of the window will be 10x10 pixels. 
         *
         * @param nSurfaceProperties Surface properties. A bitwise combination
         *                           of the values in Egl::SurfaceProperties.
         * @param strTitle Window title.
         * @param nX The X position of the window.
         * @param nY The Y position of the window.
         */
        template <typename TWindow>
        const WindowPtr_t CreateEglWindow(const boost::int64_t nSurfaceProperties,
                                       const std::string & strTitle, 
                                       int nX, int nY)
        {
            // Create window
            WindowPtr_t pWindow(new TWindow());
            return this->InitChildWindow(pWindow, 
                nSurfaceProperties, strTitle, 
                nX,
                nY,
                CWindow::DEFAULT_WIDTH,
                CWindow::DEFAULT_HEIGHT);
        }

        /**
         * Creates a new window.
         *
         * @param nSurfaceProperties Surface properties. A bitwise combination
         *                           of the values in Egl::SurfaceProperties.
         * @param strTitle Window title.
         * @param nX The X position of the window.
         * @param nY The Y position of the window.
         * @param nWidth The width of the window.
         * @param nHeight The height of the window.
         */
        template <typename TWindow>
        const WindowPtr_t CreateEglWindow(const boost::int64_t nSurfaceProperties,
                                       const std::string & strTitle, 
                                       int nX, int nY, int nWidth, int nHeight)
        {
            // Create window
            WindowPtr_t pWindow(new TWindow());
            return this->InitChildWindow(pWindow, 
                nSurfaceProperties, strTitle, 
                nX,
                nY,
                nWidth,
                nHeight);
        }

        /**
         * Swaps the back buffer of this window to the screen
         * (when using double buffering). 
         */
        virtual void SwapBuffers();

        /**
         * Closes and destroys this window.
         */
        virtual void Close();

        /** Destructor. */
        virtual ~CWindow(void) throw();
        
        /** 
         * Retrieves the context that was used to create 
         * this window.
         */
        const ContextPtr_t & GetContext() const;

        /**
         * Sets the titlebar menu of this window. To receive notifications
         * when the menu items are selected subscribe to the 
         * TitlebarMenuItemSelected event.
         *
         * @param pMenu Menu to set as title bar. This menu must have
         *              been created with the same CContext instance that
         *              created the window.
         *
         * @return *this.
         */
        virtual CWindow & SetTitlebarMenu(const MenuPtr_t & pMenu);

        /**
         * Sets the context menu of this window. To receive notifications
         * when the menu items are selected subscribe to the 
         * ContextMenuItemSelected event.
         *
         * @param pMenu Menu to set as title bar. This menu must have
         *              been created with the same CContext instance that
         *              created the window.
         * @param eMouseButton Mouse button that, when pressed, triggers 
         *                     the context menu to be shown.
         *
         * @return *this.
         */
        virtual CWindow & SetContextMenu(const MenuPtr_t & pMenu, const MouseButton_e eMouseButton);

        /**
         * Refreshes this window to refresh (redraw itself).
         */
        virtual void Refresh();

        /**
         * Draws text at a given location using a given font.
         *
         * @param strText Text to draw.
         * @param rFont Font to use.
         * @param pPosition 3D raster position where the text should be drawn.
         */
        virtual void DrawString(const std::string & strText, 
                              const CFont & rFont,
                              const C3DPoint<float> & pPosition);

        /** 
         * Retrieves whether this window is full screen. 
         *
         * @return True if this window is full screen, false otherwise.
         */
        bool IsFullScreen() const;

        /** 
         * Restores this window. 
         *
         * @return *this.
         */
        CWindow & Restore();

    private:

        // Enum of events
        enum WindowEvent
        {
            /** Event that fires when the window needs to draw. */
            DRAW_EVENT = 0,
            
            /** Event that fires when the window is being resized. */
            RESHAPE_EVENT = 1,

            /** Event that fires when a key is pressed. */
            WINDOW_KEY_EVENT = 2,

            /** The window is being created. */
            CREATE_EVENT = 3,

            /** The window is being destroyed. */
            DESTROY_EVENT = 4,

            /** An item is selected in the titlebar menu. */
            TITLEBAR_MENU_ITEM_SELECT_EVENT,

            /** An item is selected in the context menu. */
            CONTEXT_MENU_ITEM_SELECT_EVENT
        };
        
    public:

        /** Type of the Draw event. */
        typedef CEvent<detail::CWindowImpl, CWindow, CEventArgs, DRAW_EVENT> DrawEvent_t;

        /** Type of the Reshape event. */
        typedef CEvent<detail::CWindowImpl, CWindow, CWindowReshapeEventArgs, RESHAPE_EVENT> ReshapeEvent_t;

        /** Type of the Key event. */
        typedef CEvent<detail::CWindowImpl, CWindow, CKeyEventArgs, WINDOW_KEY_EVENT> KeyEvent_t;

        /** Type of the Create event. */
        typedef CEvent<detail::CWindowImpl, CWindow, CEventArgs, CREATE_EVENT> CreateEvent_t;

        /** Type of the Destroy event. */
        typedef CEvent<detail::CWindowImpl, CWindow, CEventArgs, DESTROY_EVENT> DestroyEvent_t;

        /** Type of the TitlebarMenuItemSelected event. */
        typedef CEvent<detail::CWindowImpl, CWindow, CMenuItemEventArgs, TITLEBAR_MENU_ITEM_SELECT_EVENT> TitlebarMenuItemSelectedEvent_t;

        /** Type of the ContextMenuItemSelected event. */
        typedef CEvent<detail::CWindowImpl, CWindow, CMenuItemEventArgs, CONTEXT_MENU_ITEM_SELECT_EVENT> ContextMenuItemSelectedEvent_t;

    public:

        /** 
         * Event that will fire when the window needs to fraw itself.
         * To receive this event you must subscribe to it by using
         * the += operator. 
         */
        DrawEvent_t Draw;

        /**
         * Event that will fire when the window is resized.
         * To receive this event you must subscribe to it by using
         * the += operator.
         */
        ReshapeEvent_t Reshape;

        /**
         * Event that will fire when a key is pressed or released while the 
         * To receive this event you must subscribe to it by using
         * the += operator.
         */
        KeyEvent_t Key;

        /**
         * Event that will fire when the window is created.
         * To receive this event you must subscribe to it by using
         * the += operator.
         */
        CreateEvent_t Create;

        /**
         * Event that will fire when the window is destroyed.
         * To receive this event you must subscribe to it by using
         * the += operator.
         */
        DestroyEvent_t Destroy;

        /**
         * Event that will fire when an item is selected in thre
         * the titlebar menu of this window. 
         * To receive this event you must subscribe to it by using
         * the += operator.
         */
        TitlebarMenuItemSelectedEvent_t TitlebarMenuItemSelected;

        /**
         * Event that will fire when an item is selected in thre
         * the context menu of this window. 
         * To receive this event you must subscribe to it by using
         * the += operator.
         */
        ContextMenuItemSelectedEvent_t ContextMenuItemSelected;


    protected:

        /** Creates a window. */
        CWindow();  
    
    private:

        /** Initializes a child window. */
        virtual const WindowPtr_t & InitChildWindow(const WindowPtr_t & pWindow, 
                                                    const boost::int64_t nSurfaceProperties,
                                                    const std::string & strTitle, 
                                                    int nX, int nY, 
                                                    int nWidth, int nHeight) const;

        /** 
         * Gets the impl of this window.
         */
        detail::CWindowImpl & GetImpl() const { return *m_pImpl; }

        // Avoid copy ctor and op=
        CWindow(const CWindow&);
        CWindow & operator=(const CWindow &);

    private:

        /** Window impl. */
        boost::scoped_ptr<detail::CWindowImpl> m_pImpl;        
        
    private:

        /** CContext is our friend so it can create us. */
        friend class CContext;
    };

} // namespace Egl

