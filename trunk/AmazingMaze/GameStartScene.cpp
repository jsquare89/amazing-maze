#include "Precompiled.hpp"
#include <boost/bind.hpp>
#include "GameStartScene.hpp"	
#include <locale>
#include "Egl/Context.hpp"
#include "Egl/Timer.hpp"
#include "Egl/Menu.hpp"
#include "Egl/Window.hpp"
#include "Egl/SceneManager.hpp"
#include "3DMazeModel.hpp"
#include <sstream>

namespace AmazingMaze
{
   CGameStartScene::CGameStartScene(const Egl::WindowPtr_t & pWindow, 
                                    const Egl::SceneManagerPtr_t & pSceneManager,                        
                                    const Egl::ModelPtr_t & pMazeModel) : 
                                    Egl::CScene(pWindow, pSceneManager),
                                    m_pContextMenu(),                                                               
                                    m_pTimer(pWindow->GetContext()->CreateTimer()),
                                    m_pMazeModel(pMazeModel)
    {
        // We want to listen to load an unload events fired by us
        this->Load += boost::bind(&CGameStartScene::HandleLoad, this, _1, _2);
        this->Unload += boost::bind(&CGameStartScene::HandleUnload, this, _1, _2);        
        m_pTimer->Tick += boost::bind(&CGameStartScene::HandleTimerTick, this, _1, _2);

        // Create context menu
        m_pContextMenu = pWindow->GetContext()->CreateMenu();
        m_pContextMenu->AddItem("Back to main screen", CGameStartScene::MENU_ITEM_ID_QUIT, false);                        
    }

    CGameStartScene::~CGameStartScene(void)
    {
    }

    void
    CGameStartScene::HandleDraw(const Egl::CWindow &, Egl::CEventArgs &)
    {
        // Clear the background
        glMatrixMode(GL_MODELVIEW);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();

        // Translate to center horizontally on the screen
        glTranslatef(0,0,-1.5);

        // Draw model
        m_pMazeModel->Draw();        
        
        glPopMatrix();

        // Flush all actions
        glFlush();

        // Repaint screen with content of back buffer
        this->GetWindow()->SwapBuffers();
    }

    void 
    CGameStartScene::HandleKey(const Egl::CWindow &, Egl::CKeyEventArgs & rArgs)
    {
        // Make sure we only handle this event if
        // this scene is active
        if (this->IsActive())
        {
            // Non system key and key being released?
            if ((Egl::KeyState::DOWN == rArgs.GetState()))
            {
                // Regular key?
                if (!rArgs.IsSystemKey())
                {
                    // Current locale
                    std::locale loc("");

                    // Switch on the key
                    switch (std::use_facet<std::ctype<char> > (loc).
                        toupper(static_cast<char>(rArgs.GetCharCode())))
                    {
                        // Exit key
                        case 'Q':
                            // Go back to the main screen 
                            // (poping this scene and the previous one too)
                            this->GetSceneManager()->PopScene(2);
                        break;
                    }
                }
            }
        } // if scene active
    }

    void
    CGameStartScene::HandleLoad(const Egl::CScene &, Egl::CEventArgs &)
    {   
        // Get our window
        Egl::WindowPtr_t pWindow = this->GetWindow();

        // Update projection and viewport
        this->UpdateProjectionMatrix(pWindow->GetWidth(), pWindow->GetHeight());
        this->UpdateViewport(pWindow->GetWidth(), pWindow->GetHeight());
        
        // Maze model initial position/rotation
        m_pMazeModel->MoveTo(1, 28, 0);
        m_pMazeModel->RotateTo(0, 0, -80);

        // We want to handle window events now
        pWindow->Reshape += boost::bind(&CGameStartScene::HandleReshape, this, _1, _2);
        pWindow->ContextMenuItemSelected += boost::bind(&CGameStartScene::HandleContextMenuItemSelected, this, _1, _2);
        pWindow->Key += boost::bind(&CGameStartScene::HandleKey, this, _1, _2);
        pWindow->Draw += boost::bind(&CGameStartScene::HandleDraw, this, _1, _2);        

        // We want to make sure the right contex menu shows up for this scene
        pWindow->SetContextMenu(m_pContextMenu, Egl::MouseButton::RIGHT);

        // Start animation
        m_pTimer->StartInterval(100);
    }

    void
    CGameStartScene::HandleTimerTick(const Egl::CTimer &, Egl::CEventArgs &)
    {
        // Update position and rotation of the maze
        if (m_pMazeModel->GetPosition().GetY() > 0)
            m_pMazeModel->MoveBy(0, -.56f, 0);

        if (m_pMazeModel->GetPosition().GetX() > -1)
            m_pMazeModel->MoveBy(-.04f, 0, 0);

        if (m_pMazeModel->GetZRotation() < 0)
            m_pMazeModel->RotateBy(0, 0, 1.6f);

        // Redraw
        this->Refresh();

        // If we are where we want then stop the timer.
        if (m_pMazeModel->GetZRotation() >= 0)
        {
            // Stop the timer
            m_pTimer->Stop();

            // Pop this scene
            this->GetSceneManager()->PopScene();
        }
    }

    void
    CGameStartScene::HandleUnload(const Egl::CScene &, Egl::CEventArgs &)
    {
        // We are not interested on events any longer
        Egl::WindowPtr_t pWindow = this->GetWindow();
        pWindow->Reshape -= boost::bind(&CGameStartScene::HandleReshape, this, _1, _2);
        pWindow->Draw -= boost::bind(&CGameStartScene::HandleDraw, this, _1, _2);        
        pWindow->Key -= boost::bind(&CGameStartScene::HandleKey, this, _1, _2);
        pWindow->ContextMenuItemSelected -= boost::bind(&CGameStartScene::HandleContextMenuItemSelected, this, _1, _2);        
    }
   
    void 
    CGameStartScene::HandleContextMenuItemSelected(const Egl::CWindow &, Egl::CMenuItemEventArgs & rArgs)
    {
        // Make sure we only handle this event if
        // this scene is active
        if (this->IsActive())
        {
            // Switch on the ID of the item
            switch (rArgs.GetItemId())
            {
                // Quit menu item.
                case MENU_ITEM_ID_QUIT:
                    // We pop this scene and the previous one
                    this->GetSceneManager()->PopScene(2);
                break;
            }
        } // if scene active
    }

    void 
    CGameStartScene::UpdateProjectionMatrix()
    {
        Egl::WindowPtr_t pWindow = this->GetWindow();
        this->UpdateProjectionMatrix(pWindow->GetWidth(), 
            pWindow->GetHeight());
    }

    void 
    CGameStartScene::UpdateProjectionMatrix(const int nWidth, const int nHeight)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();	
        gluPerspective(
            65, // field of view in degrees
            static_cast<GLdouble>(nWidth) / nHeight, // aspect ratio
            .2, // Z near 
            1000 // Z far
        );
        this->Refresh();
    }

    void 
    CGameStartScene::UpdateViewport(const int nWidth, const int nHeight)
    {
        // Set new viewport        
        glViewport(0, 0, nWidth, nHeight);        
    }
    
    void
    CGameStartScene::Refresh()
    {
        this->GetWindow()->Refresh();
    }

    void 
    CGameStartScene::HandleReshape(const Egl::CWindow &, Egl::CWindowReshapeEventArgs & rArgs)
    {
        // Make sure we only handle this event if
        // this scene is active
        if (this->IsActive())
        {
            // Update projection matrix.
            this->UpdateProjectionMatrix(rArgs.GetWidth(), rArgs.GetHeight());

            // update viewport
            this->UpdateViewport(rArgs.GetWidth(), rArgs.GetHeight());        
        }
    }

} // namespace AmazingMaze