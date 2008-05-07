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
        this->Draw += boost::bind(&CHelpWindow::HandleDraw, this, _1, _2);
        this->Create += boost::bind(&CHelpWindow::HandleCreate, this, _1, _2);
        this->Destroy += boost::bind(&CHelpWindow::HandleDestroy, this, _1, _2);
        this->Reshape += boost::bind(&CHelpWindow::HandleReshape, this, _1, _2);
        this->Key += boost::bind(&CHelpWindow::HandleKey, this, _1, _2);        
    }

    CHelpWindow::~CHelpWindow(void)
    {
    }

    void
    CHelpWindow::HandleDraw(const Egl::CWindow &, Egl::CEventArgs &)
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

        this->DrawString("Use the arrow keys to move around the main menu", *pFont, Egl::C3DPoint<float>(0.05f, 0.85f, 0));
        this->DrawString("and the credits menu. Press Enter to select.", *pFont, Egl::C3DPoint<float>(0.05f, 0.80f, 0));
        this->DrawString("Use i to show this help and i again to hide it.", *pFont, Egl::C3DPoint<float>(0.05f, 0.75f, 0));        
        this->DrawString("Select Start in the main menu for a demo of", *pFont, Egl::C3DPoint<float>(0.05f, 0.70f, 0));
        this->DrawString("the game. User movement in the maze has been disabled.", *pFont, Egl::C3DPoint<float>(0.05f, 0.65f, 0));

        // this->DrawString(" To move around the maze use:.", *pFont, Egl::C3DPoint<float>(0.05f, 0.85f, 0));
        // this->DrawString("- The left arrow key to move left.", *pFont, Egl::C3DPoint<float>(0.05f, 0.80f, 0));
        // this->DrawString("- The right arrow key to move right.", *pFont, Egl::C3DPoint<float>(0.05f, 0.75f, 0));        
        // this->DrawString("- The up arrow key to move up.", *pFont, Egl::C3DPoint<float>(0.05f, 0.70f, 0));
        // this->DrawString("- The down arrow key to move down.", *pFont, Egl::C3DPoint<float>(0.05f, 0.65f, 0));
        
        // Flush buffers
        glFlush();
     
        // Repaint screen with content of back buffer
        this->SwapBuffers();
    }

    void 
    CHelpWindow::UpdateProjectionMatrix(const int, const int)
    {
        // Set projection matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, 1.0, 0, 1.0);
    }

    void 
    CHelpWindow::UpdateViewport(const int nWidth, const int nHeight)
    {
        // Set vieweport
        glViewport(0, 0, nWidth, nHeight);
    }

    void 
    CHelpWindow::HandleReshape(const Egl::CWindow &, Egl::CWindowReshapeEventArgs & rArgs)
    {
        // Set projection matrix and viewport
        this->UpdateProjectionMatrix(rArgs.GetWidth(), rArgs.GetHeight());
        this->UpdateViewport(rArgs.GetWidth(), rArgs.GetHeight());
    }

    void 
    CHelpWindow::HandleKey(const Egl::CWindow &, Egl::CKeyEventArgs & rArgs)
    {
        // Non system key and key being released?
        if (!rArgs.IsSystemKey() && (Egl::KeyState::DOWN == rArgs.GetState()))
        {
            // Current locale
            std::locale loc("");

            // Switch on the key
            switch (std::use_facet<std::ctype<char> > (loc).
                toupper(static_cast<char>(rArgs.GetCharCode())))
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
    CHelpWindow::HandleCreate(const Egl::CWindow &, Egl::CEventArgs &)
    {
        // Set projection matrix and viewport
        this->UpdateProjectionMatrix(this->GetWidth(), this->GetHeight());
        this->UpdateViewport(this->GetWidth(), this->GetHeight());

        // Set background color
        glClearColor(0.0, 0.0, 0.0, 0.0);                
    }

    void
    CHelpWindow::HandleDestroy(const Egl::CWindow &, Egl::CEventArgs &)
    {
        // Post quit message to message loop
        //this->GetContext()->BreakMainLoop();
    }


} // namespace AmazingMaze