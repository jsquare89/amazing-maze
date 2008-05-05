#pragma once

#include <boost/scoped_ptr.hpp>
#include <string>
#include "Egl/Common.hpp"
#include <boost/enable_shared_from_this.hpp>
#include <boost/cstdint.hpp>

// Save the current definition of CreateWindow.
// This is because CreateWindow is a macro defined in windows.h
#ifdef CreateWindow
    #define OldCreateWindowDef CreateWindow
    #undef CreateWindow
#endif

namespace Egl
{
    namespace detail
    {
        // Forward declaration of CContextImpl
        class CContextImpl;
    }

    /** Forward declaration of CWindow. */
    class CWindow;

    /** 
     * An application context in the Egl library. Users
     * should create a CContext instance per thread and not
     * call into the CContext from a thread other than the
     * one that create it.
     */
    class CContext : public boost::enable_shared_from_this<CContext>
    {
    public:

        /** 
         * Creates a new context.
         */
        CContext(void);

        /** Destructor. */
        virtual ~CContext(void) throw();

        /**
         * Creates a new window.
         * By default the window will be 10x10 pixels and it will be 
         * positioned at 0,0. By default the window has an empty title.
         *
         * @param nSurfaceProperties Surface properties. A bitwise combination
         *                           of the values in Egl::SurfaceProperties.
         */
        template <typename TWindow>
        const WindowPtr_t CreateWindow(const boost::int64_t nSurfaceProperties)
        {
            // Create window
            WindowPtr pWindow(new TWindow());
            return this->InitWindow(pWindow, 
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
        const WindowPtr_t CreateWindow(const boost::int64_t nSurfaceProperties, 
                                       const std::string & strTitle)
        {
            // Create window
            WindowPtr pWindow(new TWindow());
            return this->InitWindow(pWindow, 
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
        const WindowPtr_t CreateWindow(const boost::int64_t nSurfaceProperties, 
                                       int nX, int nY)
        {
            // Create window
            WindowPtr pWindow(new TWindow());
            return this->InitWindow(pWindow, 
                nSurfaceProperties,
                "", 
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
        const WindowPtr_t CreateWindow(const boost::int64_t nSurfaceProperties,
                                       int nX, int nY, int nWidth, int nHeight)
        {
            // Create window
            WindowPtr pWindow(new TWindow());
            return this->InitWindow(pWindow, 
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
        const WindowPtr_t CreateWindow(const boost::int64_t nSurfaceProperties,
                                       const std::string & strTitle, 
                                       int nX, int nY)
        {
            // Create window
            WindowPtr pWindow(new TWindow());
            return this->InitWindow(pWindow, 
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
        const WindowPtr_t CreateWindow(const boost::int64_t nSurfaceProperties,
                                       const std::string & strTitle, 
                                       int nX, int nY, int nWidth, int nHeight)
        {
            // Create window
            WindowPtr_t pWindow(new TWindow());
            return this->InitWindow(pWindow, 
                nSurfaceProperties, strTitle, 
                nX,
                nY,
                nWidth,
                nHeight);
        }

        /** 
         * Runs the message loop while the main window
         * is on the screen.
         */
        virtual void RunMainLoop();

        /** 
         * Breaks the message loop started by RunMainLoop()
         */
        void BreakMainLoop();

        /** 
         * Creates a menu.
         *
         * @return A new menu. You can assign this menu to a window.
         */
        const MenuPtr_t CreateMenu();

        /** 
         * Creates a timer.
         *
         * @return A new timer.
         */
        const TimerPtr_t CreateTimer();

        /**
         * Creates a camera.
         *
         * @return A new camera.
         */
        const CameraPtr_t CreateCamera();

        /**
         * Loads a font.
         *
         * @param strFontName The font name.
         * @param nFontSize Font point size.
         *
         * @return The loaded font.
         */
        const FontPtr_t LoadFont(const std::string & strFontName, const int nFontSize);

        /**
         * Loads an image.
         *
         * @param strTextureFilePath Path to the image file.
         */
        const TexturePtr_t LoadTexture(const std::string & strTextureFilePath);
        
    private:

        /** Initializes a window that has just been created. */
        const WindowPtr_t & InitWindow(const WindowPtr_t & pWindow, 
                                       const boost::int64_t nSurfaceProperties, 
                                       const std::string & strTitle, 
                                       int nX, int nY, 
                                       int nWidth, int nHeight);

    private:

        /** Implementation. */
        boost::scoped_ptr<detail::CContextImpl> m_pImpl;

    private:

        /** CWindow needs the ability to initialize child windows. */
        friend class CWindow;
    };
} // namespace Egl

// Restore the current definition of CreateWindow
#ifdef OldCreateWindowDef
    #define CreateWindow OldCreateWindowDef 
    #undef OldCreateWindowDef
#endif