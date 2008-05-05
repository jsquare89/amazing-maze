#include "Precompiled.hpp"
#include "Egl/Context.hpp"
#include "Egl/Window.hpp"
#include "Egl/detail/WindowImpl.hpp"
#include "Egl/Menu.hpp"
#include "Egl/detail/MenuImpl.hpp"
#include "Egl/Timer.hpp"
#include "Egl/detail/TimerImpl.hpp"
#include "Egl/Camera.hpp"
#include "Egl/Font.hpp"
#include "Egl/detail/FontImpl.hpp"
#include "Egl/Texture.hpp"
#include "Egl/detail/DevIL.hpp"
#include <string>

// Remove CreateWindow, a macro defined in windows.h
#undef CreateWindow

namespace Egl
{
    namespace detail
    {
        /** Implementation of CContext using Cpw */
        class CContextImpl
        {
        public:

            /** Constructor. */
            CContextImpl(void) : m_hCpwHandle(0)
            {
                // Creates a new context
                if (FALSE == cpwInitContext(&m_hCpwHandle))
                {
                    // TODO throw exception
                }
            }

            /** Destructor */
            ~CContextImpl(void) throw()
            {
                // Destroy context
                cpwFreeContext(&m_hCpwHandle);
            }

            /** Creates a window. */
            void InitWindowImpl(
                    CWindowImpl & rWindowImpl,
                    CWindow * pWindow,
                    const ContextPtr_t & pContext,
                    const boost::int64_t nSurfaceProperties,
                    const std::string & strTitle, 
                    const int nX, 
                    const int nY, 
                    const int nWidth, 
                    const int nHeight)
            {
                // Create window from impl
                rWindowImpl.Init(pWindow, pContext, m_hCpwHandle,
                    nSurfaceProperties, strTitle, nX, nY, 
                    nWidth, nHeight);
            }

            /** 
             * Runs the message loop while the main window
             * is on the screen.
             */
            void RunMainLoop()
            {
                // TODO if false throw exception
                cpwMainLoop(m_hCpwHandle);
            }

            /** 
             * Breaks the message loop started by RunMainLoop()
             */
            void BreakMainLoop()
            {
                // TODO if false throw exception
                cpwBreakMainLoop(m_hCpwHandle);
            }

            /** Init a menu impl. */
            void InitMenuImpl(CMenuImpl & rMenuImpl, 
                              const ContextPtr_t & pContext)
            {
                // Init menu impl
                rMenuImpl.Init(pContext, m_hCpwHandle, false);
            }

            /** Creates a tmer impl. */
            void InitTimerImpl(CTimerImpl & rTimerImpl, 
                               const CTimer * pTimer,
                               const ContextPtr_t & pContext)
            {
                // Init timer impl
                rTimerImpl.Init(pTimer, pContext, m_hCpwHandle);
            }

            /** Initializes font impl. */
            void InitFontImpl(CFontImpl & rFontImpl, 
                              const std::string & strFontName,
                              const int nFontSize,
                              const ContextPtr_t & pContext)
            {
                // Init font impl
                rFontImpl.Init(strFontName, nFontSize, pContext, m_hCpwHandle);
            }

        private:

            /** Prevent copy ctor and op=. */
            CContextImpl(const CContextImpl &);
            CContextImpl & operator=(const CContextImpl &);

        private:

            /** CPW handle. */
            pCpw m_hCpwHandle;
        };

    } // namespace detail

    CContext::CContext(void) : m_pImpl(new detail::CContextImpl())
    {        
    }

    // virtual
    CContext::~CContext(void) throw()
    {
    }

    void 
    CContext::RunMainLoop()
    {
        // Forward call
        m_pImpl->RunMainLoop();
    }

    void 
    CContext::BreakMainLoop()
    {
        // Forward call
        m_pImpl->BreakMainLoop();
    }

    const WindowPtr_t &
    CContext::InitWindow(const WindowPtr_t & pWindow,
                         const boost::int64_t nSurfaceProperties,
                         const std::string & strTitle, 
                         int nX, int nY, int nWidth, int nHeight)
    {
        // Forward call to impl
        assert(pWindow);
        m_pImpl->InitWindowImpl(pWindow->GetImpl(),
            pWindow.get(), this->shared_from_this(), nSurfaceProperties, 
            strTitle, nX, nY, nWidth, nHeight);
        return pWindow;
    }

    const MenuPtr_t 
    CContext::CreateMenu()
    {
        // Forward call
        MenuPtr_t pMenu(new CMenu());
        m_pImpl->InitMenuImpl(pMenu->GetImpl(),
            this->shared_from_this());
        return pMenu;
    }

    const TimerPtr_t 
    CContext::CreateTimer()
    {
        // Forward call
        TimerPtr_t pTimer(new CTimer());
        m_pImpl->InitTimerImpl(pTimer->GetImpl(),
            pTimer.get(), this->shared_from_this());
        return pTimer;
    }

    const CameraPtr_t 
    CContext::CreateCamera()
    {
        // Forward call
        return CameraPtr_t(new CCamera(this->shared_from_this()));
    }

    const FontPtr_t 
    CContext::LoadFont(const std::string & strFontName,const int nFontSize)
    {
        // Create font
        FontPtr_t pFont(new CFont());

        // Forward call
        m_pImpl->InitFontImpl(pFont->GetImpl(), strFontName, 
            nFontSize, this->shared_from_this());
        return pFont;
    }

    const TexturePtr_t 
    CContext::LoadTexture(const std::string & strTextureFilePath)
    {
        // Initialize the DevIL library once
        // TODO, use boost::once to make sure this happens once 
        // in a thread safe manner
        static int s_bInitialized = false;
        if (!s_bInitialized)
        {
            ilInit();
            iluInit();
            ilutRenderer(ILUT_OPENGL);
            s_bInitialized = true;
        }

        // Creat image object, image will load itself
        TexturePtr_t pTexture(new CTexture(strTextureFilePath, this->shared_from_this()));
        return pTexture;
    }
} // namespace Egl

