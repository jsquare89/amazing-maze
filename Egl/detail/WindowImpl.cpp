#include "Precompiled.hpp"
#include "Egl/Window.hpp"
#include "Egl/Context.hpp"
#include "Egl/detail/WindowImpl.hpp"
#include "Egl/detail/SurfacePropertiesUtil.hpp"
#include "Egl/detail/KeyStateUtil.hpp"
#include "Egl/detail/MouseButtonUtil.hpp"
#include "Egl/Menu.hpp"
#include "Egl/detail/MenuImpl.hpp"
#include "Egl/Font.hpp"
#include "Egl/detail/FontImpl.hpp"

namespace Egl
{
    namespace detail
    {        
        /** Called when the window wants to be displayed. */
        static void OnWindowDisplay(pCpw cpw, uint_32 nId)
        {
            // Get the window impl for this CPW window
            CWindowImpl * pWindowImpl = reinterpret_cast<CWindowImpl *>(
                cpwGetWindowUserdata(cpw, nId));

            // If there is a CWindowImpl pointer use it to call the right method
            if (0 != pWindowImpl)
            {
                try
                {
                    // Fire the event
                    pWindowImpl->FireOnDrawEvent();
                }
                catch (...)
                {
                    // An error occurred firing the event
                    // TODO log an error
                }
            }
        }

        /** Called when the window is being resized. */
        static void OnWindowReshape(pCpw cpw, uint_32 nId, uint_32 nWidth, uint_32 nHeight)
        {
            // Get the window impl for this CPW window
            CWindowImpl * pWindowImpl = reinterpret_cast<CWindowImpl *>(
                cpwGetWindowUserdata(cpw, nId));

            // If there is a CWindowImpl pointer use it to call the right method
            if (0 != pWindowImpl)
            {
                try
                {
                    // Fire the draw event
                    pWindowImpl->FireOnReshapeEvent(nWidth, nHeight);
                }
                catch (...)
                {
                    // An error occurred firing the event
                    // TODO log an error
                }
            }
        }

        /** Called when a non-system key is pressed. */
        static void OnWindowKeyboard(pCpw cpw, uint_32 nId, uint_32 nKeyCode, uint_32 nKeyState, uint_32 nCursorX, uint_32 nCursorY)
        {
            // Get the window impl for this CPW window
            CWindowImpl * pWindowImpl = reinterpret_cast<CWindowImpl *>(
                cpwGetWindowUserdata(cpw, nId));

            // If there is a CWindowImpl pointer use it to call the right method
            if (0 != pWindowImpl)
            {
                try
                {
                    // Fire the event
                    pWindowImpl->FireOnKeyEvent(nKeyCode, false, 
                        Egl::KeyState::detail::FromCpw(nKeyState), nCursorX, nCursorY);
                }
                catch (...)
                {
                    // An error occurred firing the event
                    // TODO log an error
                }
            }
        }

        /** Called when a non-system key is pressed. */
        static void OnWindowSystemKeyboard(pCpw cpw, uint_32 nId, uint_32 nKeyCode, uint_32 nKeyState, uint_32 nCursorX, uint_32 nCursorY)
        {
            // Get the window impl for this CPW window
            CWindowImpl * pWindowImpl = reinterpret_cast<CWindowImpl *>(
                cpwGetWindowUserdata(cpw, nId));

            // If there is a CWindowImpl pointer use it to call the right method
            if (0 != pWindowImpl)
            {
                try
                {
                    // Fire the event
                    pWindowImpl->FireOnKeyEvent(nKeyCode, true, 
                        Egl::KeyState::detail::FromCpw(nKeyState), nCursorX, nCursorY);
                }
                catch (...)
                {
                    // An error occurred firing the event
                    // TODO log an error
                }
            }
        }

        /** Called when a window is created or destroyed. */
        static void OnWindowCreateOrDestroy(pCpw cpw, uint_32 nId, BOOL bFlag)
        {
            // Get the window impl for this CPW window
            CWindowImpl * pWindowImpl = reinterpret_cast<CWindowImpl *>(
                cpwGetWindowUserdata(cpw, nId));

            // If there is a CWindowImpl pointer use it to call the right method
            if (0 != pWindowImpl)
            {
                try
                {
                    // Fire the event
                    if (bFlag)
                        pWindowImpl->FireOnCreateEvent();
                    else
                        pWindowImpl->FireOnDestroyEvent();
                }
                catch (...)
                {
                    // An error occurred firing the event
                    // TODO log an error
                }
            }
        }

        /** Called when a menu item is selected. */
        void OnMenuItemSelected(pCpw cpw, uint_32 nWindowId, uint_32 nMenuId, uint_32 nEntryId)
        {
            // Get the window impl for this CPW window
            CWindowImpl * pWindowImpl = reinterpret_cast<CWindowImpl *>(
                cpwGetWindowUserdata(cpw, nWindowId));

            // If there is a CWindowImpl pointer use it to call the right method
            if (0 != pWindowImpl)
            {
                try
                {
                    // Fire the event
                    pWindowImpl->FireOnMenuItemSelectedEvent(nMenuId, nEntryId);
                }
                catch (...)
                {
                    // An error occurred firing the event
                    // TODO log an error
                }
            }
        }

        /** CWindow implementation using Cpw. */
        CWindowImpl::CWindowImpl() : m_nHandle(0),
                                     m_pContext(),
                                     m_pContextHandle(0),
                                     m_nSurfaceProperties(0),                                     
                                     m_strTitle(),
                                     m_nX(0),
                                     m_nY(0),
                                     m_nWidth(0),
                                     m_nHeight(0),
                                     m_pTitlebarMenu(),
                                     m_pContextMenu(),
                                     m_eContextMenuMouseButton(MouseButton::LEFT),
                                     m_pWindow(0),
                                     m_bFullScreen(false)
        {
        }

        void 
        CWindowImpl::Init(const CWindow * pWindow,
                          const ContextPtr_t & pContext,
                          const pCpw pContextHandle,
                          const boost::int64_t nSurfaceProperties,
                          const std::string & strTitle, 
                          const int nX, 
                          const int nY, 
                          const int nWidth, 
                          const int nHeight)
        {
            // Initialize all the internal values
            m_pWindow = pWindow;
            m_pContext = pContext;
            m_pContextHandle = pContextHandle;
            m_strTitle = strTitle;
            m_nX = nX;
            m_nY = nY;
            m_nWidth = nWidth;
            m_nHeight = nHeight;

            // Set surface properties of the window we are creating
            if (!cpwInitDisplayMode(m_pContextHandle, 
                SurfaceProperties::detail::ToCpw(nSurfaceProperties)))
            {
                // TODO throw exception
            }

            // Create the window
            m_nHandle = cpwCreateWindowEx(m_pContextHandle, 
                const_cast<char*>(strTitle.c_str()), 
                m_nX, m_nY, m_nWidth, nHeight);

            // Set the event as user data for the CPW window
            cpwSetWindowUserdata(m_pContextHandle, this, m_nHandle);

            // Set viewport 
            glViewport(m_nX, m_nY, m_nWidth, m_nHeight);

            // Signup for all events
            cpwWindowDisplayCallback(m_pContextHandle, &OnWindowDisplay, m_nHandle);
            cpwWindowReshapeCallback(m_pContextHandle, &OnWindowReshape, m_nHandle);
            cpwWindowKeyboardCallback(m_pContextHandle, &detail::OnWindowKeyboard, m_nHandle);
            cpwWindowSystemKeyboardCallback(m_pContextHandle, &detail::OnWindowSystemKeyboard, m_nHandle);
            cpwWindowCreateCallback(m_pContextHandle, &OnWindowCreateOrDestroy, m_nHandle);
            cpwWindowCreateCallback(m_pContextHandle, &OnWindowCreateOrDestroy, m_nHandle);
            
            // If titlebar menu has been set after contruction but
            // before init, attach it to the window now
            if (m_pTitlebarMenu)
            {
                // Set titlebar menu
                cpwAssignMenuToWindow(m_pContextHandle, m_pTitlebarMenu->GetImpl().GetId(),
                    m_nHandle);
            }

            // If context menu has been set after contruction but
            // before init, attach it to the window now
            if (m_pContextMenu)
            {
                cpwAttachMenuToButton(m_pContextHandle, m_pContextMenu->GetImpl().GetId(),
                    Egl::MouseButton::detail::ToCpw(m_eContextMenuMouseButton), m_nHandle);
            }
        }

        CWindowImpl::~CWindowImpl() throw()
        {
            // Set the event as user data for the CPW window
            cpwSetWindowUserdata(m_pContextHandle, 0, m_nHandle);
        }

        /** Set title. */
        void 
        CWindowImpl::SetTitle(const std::string & strTitle)
        {
            // Set title
            cpwSetWindowTitle(m_pContextHandle,
                const_cast<char*>(strTitle.c_str()), m_nHandle);
            m_strTitle = strTitle;
        }

        void
        CWindowImpl::MoveTo(int nX, int nY)
        {
            // Set position
            cpwPositionWindow(m_pContextHandle, 
                static_cast<unsigned int>(nX), 
                static_cast<unsigned int>(nY),
                m_nHandle);
            m_nX = nX;
            m_nY = nY;
        }

        void
        CWindowImpl::Resize(int nWidth, int nHeight)
        {
            // Set size
            cpwReshapeWindow(m_pContextHandle, 
                static_cast<unsigned int>(nWidth),
                static_cast<unsigned int>(nHeight),
                m_nHandle);
            m_nWidth = nWidth;
            m_nHeight = nHeight;            
        }

        void
        CWindowImpl::Restore()
        {
            // Set size            
            cpwRestoreWindow(m_pContextHandle, m_nHandle);
            m_bFullScreen = false;
        }

        void
        CWindowImpl::Show(void)
        {
            // Show window
            cpwShowWindow(m_pContextHandle, m_nHandle);
        }

        void
        CWindowImpl::Hide(void)
        {
            // hide window
            cpwHideWindow(m_pContextHandle, m_nHandle);
        }

        void
        CWindowImpl::SetFullScreen(void)
        {
            // Set full screen
            cpwFullscreenWindow(m_pContextHandle, m_nHandle);
            m_bFullScreen = true;
        }
        
        void 
        CWindowImpl::FireOnDrawEvent()
        {
            m_pWindow->OnDraw.Fire();            
        }

        void 
        CWindowImpl::FireOnReshapeEvent(int nWidth, int nHeight)
        {
            m_pWindow->OnReshape.Fire(nWidth, nHeight);       
        }

        void 
        CWindowImpl::FireOnKeyEvent(int nKeyCode, bool bIsSystemKey, Egl::KeyState_e eKeyState, int nCursorX, int nCursorY)
        {
            m_pWindow->OnKey.Fire(nKeyCode, bIsSystemKey, eKeyState, nCursorX, nCursorY);
        }

        void 
        CWindowImpl::FireOnCreateEvent()
        {
            m_pWindow->OnCreate.Fire();
        }

        void 
        CWindowImpl::FireOnDestroyEvent()
        {
            m_pWindow->OnDestroy.Fire();
        }

        void 
        CWindowImpl::FireOnMenuItemSelectedEvent(int nMenuId, int nItemId)
        {
            if (m_pTitlebarMenu && (m_pTitlebarMenu->GetImpl().GetId() == nMenuId))
                m_pWindow->OnTitlebarMenuItemSelected.Fire(nItemId);
            else if (m_pContextMenu && (m_pContextMenu->GetImpl().GetId() == nMenuId))
                m_pWindow->OnContextMenuItemSelected.Fire(nItemId);
        }

        void 
        CWindowImpl::SwapBuffers()
        {
            // Forward call
            cpwSwapWindowBuffers(m_pContextHandle, m_nHandle);
        }

        void 
        CWindowImpl::Close()
        {
            // Forward call
            cpwDestroyWindow(m_pContextHandle, m_nHandle);
        }

        void 
        CWindowImpl::SetTitlebarMenu(const MenuPtr_t & pMenu)
        {
            m_pTitlebarMenu = pMenu;

            // If titlebar menu has been set after contruction but
            // before init, attach it to the window now
            if (m_pTitlebarMenu)
            {
                // Set titlebar menu
                cpwAssignMenuToWindow(m_pContextHandle, m_pTitlebarMenu->GetImpl().GetId(),
                    m_nHandle);
            }
            else // no menu
            {
                // Unset titlebar menu
                cpwAssignMenuToWindow(m_pContextHandle, 0, m_nHandle);
            }
        }

        void 
        CWindowImpl::SetContextMenu(const MenuPtr_t & pMenu, 
                                    const MouseButton_e eMouseButton)
        {
            m_pContextMenu = pMenu;
            m_eContextMenuMouseButton = eMouseButton;
           
            // If context menu has been set after contruction but
            // before init, attach it to the window now
            if (m_pContextMenu)
            {
                cpwAttachMenuToButton(m_pContextHandle, m_pContextMenu->GetImpl().GetId(),
                    Egl::MouseButton::detail::ToCpw(m_eContextMenuMouseButton), m_nHandle);
            }
            else
            {
                cpwAttachMenuToButton(m_pContextHandle, 0,
                    Egl::MouseButton::detail::ToCpw(m_eContextMenuMouseButton), m_nHandle);
            }
        }

        void 
        CWindowImpl::Refresh()
        {
            // Forward call
            cpwPostWindowRedisplay(m_pContextHandle, m_nHandle);
        }

        void 
        CWindowImpl::DrawString(const std::string & strText, 
                                const CFontImpl & rFontImpl,
                                const C3DPoint<float> & pPosition)
        {
            // Set rater position
            glRasterPos3d(pPosition.GetX(), pPosition.GetY(), pPosition.GetZ());

            // Ask the font to draw the text
            rFontImpl.DrawString(strText);
        }
    }    
} // namespace Egl