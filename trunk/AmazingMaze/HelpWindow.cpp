#include "Precompiled.hpp"
#include <boost/bind.hpp>
#include <locale>
#include "HelpWindow.hpp"
#include "Egl/Context.hpp"	
#include "Egl/Font.hpp"	

namespace AmazingMaze
{
    CHelpWindow::CHelpWindow(void) : CWindow()
    {
        // We are interested in listening to
        // some events        
        this->OnDraw += boost::bind(&CHelpWindow::HandleOnDraw, this);
        this->OnCreate += boost::bind(&CHelpWindow::HandleOnCreate, this);
        this->OnDestroy += boost::bind(&CHelpWindow::HandleOnDestroy, this);
        this->OnReshape += boost::bind(&CHelpWindow::HandleOnReshape, this, _1, _2);
        this->OnKey += boost::bind(&CHelpWindow::HandleOnKey, this, _1, _2, _3, _4, _5);        
    }

    CHelpWindow::~CHelpWindow(void)
    {
    }

    void
    CHelpWindow::HandleOnDraw(void)
    {
        // Set background color
        glClearColor(0, 0, 0, 0.0);

        // Clear buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set line width and color for border
        glLineWidth(3);
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0.01f, 0.01f);
            glVertex2f(0.01f, 0.99f);
            glVertex2f(0.99f, 0.99f);
            glVertex2f(0.99f, 0.01f);
        glEnd();

        // Inner border
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0.03f, 0.03f);
            glVertex2f(0.03f, 0.97f);
            glVertex2f(0.97f, 0.97f);
            glVertex2f(0.97f, 0.03f);
        glEnd();

        // Text color
        glColor3f(1, 1, 1);

        // Load font
        Egl::FontPtr_t pFont = this->GetContext()->LoadFont("ARIAL.TTF", 18);

        this->DrawString(" Welcome to the Amazing Maze ", *pFont, Egl::C3DPoint<float>(0.25f, 0.90f, 0));
        this->DrawString(" To move around the maze use:.", *pFont, Egl::C3DPoint<float>(0.05f, 0.85f, 0));
        this->DrawString("- The left arrow key to move left.", *pFont, Egl::C3DPoint<float>(0.05f, 0.80f, 0));
        this->DrawString("- The right arrow key to move right.", *pFont, Egl::C3DPoint<float>(0.05f, 0.75f, 0));        
        this->DrawString("- The up arrow key to move up.", *pFont, Egl::C3DPoint<float>(0.05f, 0.70f, 0));
        this->DrawString("- The down arrow key to move down.", *pFont, Egl::C3DPoint<float>(0.05f, 0.65f, 0));
        
        // Flush buffers
        glFlush();
     
        // Repaint screen with content of back buffer
        this->SwapBuffers();
    }

    void 
    CHelpWindow::HandleOnReshape(int nWidth, int nHeight)
    {
        glViewport(0, 0, nWidth, nHeight);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, 1.0, 0, 1.0);
    }

    void 
    CHelpWindow::HandleOnKey(int nKeyCode, bool bIsSystemKey, Egl::KeyState_e eKeyState, int nCursorX, int nCursorY)
    {
        // Avoid warning
        nCursorX;
        nCursorY;

        // Non system key and key being released?
        if (!bIsSystemKey && (Egl::KeyState::DOWN == eKeyState))
        {
            // Current locale
            std::locale loc("");

            // Switch on the key
            switch (std::use_facet<std::ctype<char> > (loc).
                toupper(static_cast<char>(nKeyCode)))
            {
                // help key
                case 'I': 
                {
                    // Hide this window
                    this->Hide();
                }
                break;
            }
        }
    }

    void
    CHelpWindow::HandleOnCreate(void)
    {
        // Force a "reshape" so the right 
        // projection matrix and viewport
        // are set
        this->HandleOnReshape(this->GetWidth(), this->GetHeight());        	

        // Set background color
        glClearColor(0.0, 0.0, 0.0, 0.0);                
    }

    void
    CHelpWindow::HandleOnDestroy(void)
    {
        // Post quit message to message loop
        //this->GetContext()->BreakMainLoop();
    }


} // namespace AmazingMaze