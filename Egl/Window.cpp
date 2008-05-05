#include "Precompiled.hpp"
#include <boost/shared_ptr.hpp>
#include "Egl/Window.hpp"
#include "Egl/Context.hpp"
#include "Egl/detail/WindowImpl.hpp"
#include "Egl/Font.hpp"

// Save the current definition of CreateWindow.
// This is because CreateWindow is a macro defined in windows.h
#ifdef CreateWindow
    #define OldCreateWindowDef CreateWindow
    #undef CreateWindow
#endif

namespace Egl
{
    CWindow::CWindow() : m_pImpl(new detail::CWindowImpl())
    {
    }

    // virtual
    CWindow::~CWindow(void) throw()
    {
    }

    CWindow & 
    CWindow::SetTitle(const std::string & strTitle)
    {
        // Set title
        m_pImpl->SetTitle(strTitle);
        return (*this);
    }

    CWindow & 
    CWindow::MoveTo(int nX, int nY)
    {
        // Set position
        m_pImpl->MoveTo(nX, nY);
        return (*this);
    }

    CWindow & 
    CWindow::Resize(int nWidth, int nHeight)
    {
        // Set size
        m_pImpl->Resize(nWidth, nHeight);
        return (*this);
    }

    CWindow & 
    CWindow::Show(void)
    {
        // Show window
        m_pImpl->Show();
        return (*this);
    }

    CWindow & 
    CWindow::Hide(void)
    {
        // hide window
        m_pImpl->Hide();
        return (*this);
    }

    CWindow & 
    CWindow::SetFullScreen(void)
    {
        // Set full screen
        m_pImpl->SetFullScreen();
        return (*this);
    }
    
    void 
    CWindow::SwapBuffers()
    {
        // Forward call
        m_pImpl->SwapBuffers();
    }

    const WindowPtr_t &
    CWindow::InitChildWindow(const WindowPtr_t & pWindow,
                             const boost::int64_t nSurfaceProperties,
                             const std::string & strTitle, 
                             int nX, int nY, 
                             int nWidth, int nHeight) const
    {
        // Create and return child window
        return m_pImpl->GetContext()->InitWindow(pWindow,
            nSurfaceProperties, strTitle, nX, nY, nWidth, nHeight);
    }

    const std::string & 
    CWindow::GetTitle() const 
    { 
        return m_pImpl->GetTitle(); 
    }

    int 
    CWindow::GetX() const 
    { 
        return m_pImpl->GetX(); 
    }

    int 
    CWindow::GetY() const 
    { 
        return m_pImpl->GetY(); 
    }

    int 
    CWindow::GetWidth() const 
    { 
        return m_pImpl->GetWidth(); 
    }

    int 
    CWindow::GetHeight() const 
    { 
        return m_pImpl->GetHeight();; 
    }

    // virtual
    void 
    CWindow::Close()
    {
        // Forward call
        m_pImpl->Close();
    }

    const ContextPtr_t & 
    CWindow::GetContext() const
    {
        // Forward call
        return m_pImpl->GetContext();
    }

    // virtual
    CWindow & 
    CWindow::SetTitlebarMenu(const MenuPtr_t & pMenu)
    {
        // Forward call
        m_pImpl->SetTitlebarMenu(pMenu);
        return *this;
    }

    // virtual
    CWindow & 
    CWindow::SetContextMenu(const MenuPtr_t & pMenu, 
                            const MouseButton_e eMouseButton)
    {
        // Forward call
        m_pImpl->SetContextMenu(pMenu, eMouseButton);
        return *this;
    }

    // virtual 
    void 
    CWindow::Refresh()
    {
        // Forward call
        m_pImpl->Refresh();
    }

    void 
    CWindow::DrawString(const std::string & strText, 
                      const CFont & rFont,
                      const C3DPoint<float> & pPosition)
    {
        // Forward call
        m_pImpl->DrawString(strText, rFont.GetImpl(), pPosition);
    }

    bool 
    CWindow::IsFullScreen() const
    {
        // Forward call
        return m_pImpl->IsFullScreen();
    }

    CWindow &
    CWindow::Restore()
    {
        // Forward call
        m_pImpl->Restore();
        return *this;
    }
} // namespace Egl

// Restore the current definition of CreateWindow
#ifdef OldCreateWindowDef
    #define CreateWindow OldCreateWindowDef 
    #undef OldCreateWindowDef
#endif