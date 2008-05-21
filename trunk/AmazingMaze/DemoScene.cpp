#include "Precompiled.hpp"
#include <boost/bind.hpp>
#include "DemoScene.hpp"	
#include <locale>
#include "Egl/Context.hpp"
#include "Egl/Texture.hpp"
#include "Egl/Image.hpp"
#include "Egl/Timer.hpp"
#include "Egl/Camera.hpp"
#include "Egl/Light.hpp"
#include "Egl/LightingControl.hpp"
#include "Egl/ImageButton.hpp"
#include "Egl/Menu.hpp"
#include "Egl/Window.hpp"
#include "Egl/SceneManager.hpp"
#include "Maze.hpp"
#include "MazeServer.hpp"
#include "MazeMusic.hpp"
#include "3DMazeModel.hpp"
#include "MazeWalker.hpp"
#include "SphereMazeWalker.hpp"
#include <sstream>

namespace AmazingMaze
{
    //float nXTrans, nYTrans, nZTrans;
    //float nXRot, nYRot, nZRot;

    CDemoScene::CDemoScene(const Egl::WindowPtr_t & pWindow, 
                           const Egl::SceneManagerPtr_t & pSceneManager, 
                           const Egl::CameraPtr_t & pCamera,
                           const MazeServerPtr_t & pMazeServer,
                           const MazePtr_t & pMaze) : 
                           Egl::CScene(pWindow, pSceneManager),
                           m_pCamera(pCamera),
                           m_pContextMenu(),                           
                           m_nFieldOfView(65),
                           m_vLights(),
                           m_pWalkerTimer(pWindow->GetContext()->CreateTimer()),
                           m_vWalkerSteps(),
                           m_citWalkerStep(),
                           m_pCheersMusic(new CMazeMusic("sounds\\FX\\Cheers.mp3")),
                           m_pMazeServer(pMazeServer),
                           m_pMaze(pMaze),
                           m_pMazeModel(new C3DMazeModel(pMaze)),
                           m_pMazeWalker(new CSphereMazeWalker(0.4f))
    {
        // We want to listen to load an unload events fired by us
        this->Load += boost::bind(&CDemoScene::HandleLoad, this, _1, _2);
        this->Unload += boost::bind(&CDemoScene::HandleUnload, this, _1, _2);        
        m_pWalkerTimer->Tick += boost::bind(&CDemoScene::HandleTimerTick, this, _1, _2);

        // Set the 3D maze model textures
        m_pMazeModel->SetFloorTexture(pWindow->GetContext()->LoadTexture("textures/floor-cracks.bmp"));
        m_pMazeModel->SetWallTexture(pWindow->GetContext()->LoadTexture("textures/wall-cracks.bmp"));
        //m_pMazeModel->SetWindow(this->GetWindow());

        // Update player position        
        this->UpdateWalker(CMazeWalker::Direction::NORTH, 
            m_pMaze->GetPlayerRowIndex(), 
            m_pMaze->GetPlayerColumn());

        // Create context menu
        m_pContextMenu = pWindow->GetContext()->CreateMenu();
        m_pContextMenu->AddItem("Show help window", CDemoScene::MENU_ITEM_ID_HELP, false);        
        m_pContextMenu->AddItem("Back to main screen", CDemoScene::MENU_ITEM_ID_QUIT, false);                        
    }

    CDemoScene::~CDemoScene(void)
    {
    }

    void
    CDemoScene::HandleDraw(const Egl::CWindow &, Egl::CEventArgs &)
    {
        // Clear the background
        glMatrixMode(GL_MODELVIEW);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();

        glTranslatef(0,0,-1.5);
        //glScalef(.8f, .8f, .8f);
        //glColor3f(0.0f, 0.0f, 0.0f);

        m_pMazeModel->Draw();
        m_pMazeWalker->Draw();
        
        glPopMatrix();

        // Flush all actions
        glFlush();

        // Repaint screen with content of back buffer
        this->GetWindow()->SwapBuffers();
    }

    void 
    CDemoScene::HandleKey(const Egl::CWindow &, Egl::CKeyEventArgs & rArgs)
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
                            this->GetSceneManager()->PopScene();

                        break;
                    }
                }
                else // System key
                {
                    switch (rArgs.GetCharCode())
                    {
                        // Left
                        case 13:
                            if (m_pMazeServer->Move(m_pMaze, CMazeServer::MazeMoveDirection::UP))
                            {
                                // Update player position
                                this->UpdateWalker(CMazeWalker::Direction::NORTH,
                                    m_pMaze->GetPlayerRowIndex(), m_pMaze->GetPlayerColumn());

                                // Check if game is won
                                if ((m_pMaze->GetEndRowIndex() == m_pMaze->GetPlayerRowIndex()) &&
                                    (m_pMaze->GetEndColumn() == m_pMaze->GetPlayerColumn()))
                                {
                                    // We have won
                                    this->OnWin();
                                }
                            }
                        break;

                        // Up 
                        case 14:
                            if (m_pMazeServer->Move(m_pMaze, CMazeServer::MazeMoveDirection::RIGHT))
                            {
                                // Update player position
                                this->UpdateWalker(CMazeWalker::Direction::WEST,
                                    m_pMaze->GetPlayerRowIndex(), m_pMaze->GetPlayerColumn());

                                // Check if game is won
                                if ((m_pMaze->GetEndRowIndex() == m_pMaze->GetPlayerRowIndex()) &&
                                    (m_pMaze->GetEndColumn() == m_pMaze->GetPlayerColumn()))
                                {
                                    // We have won
                                    this->OnWin();
                                }
                            }
                        break;

                        // Right 
                        case 15:
                            if (m_pMazeServer->Move(m_pMaze, CMazeServer::MazeMoveDirection::DOWN))
                            {
                                // Update player position
                                this->UpdateWalker(CMazeWalker::Direction::SOUTH,
                                    m_pMaze->GetPlayerRowIndex(), m_pMaze->GetPlayerColumn());

                                // Check if game is won
                                if ((m_pMaze->GetEndRowIndex() == m_pMaze->GetPlayerRowIndex()) &&
                                    (m_pMaze->GetEndColumn() == m_pMaze->GetPlayerColumn()))
                                {
                                    // We have won
                                    this->OnWin();
                                }
                            }
                        break;

                        // Down 
                        case 16:
                            if (m_pMazeServer->Move(m_pMaze, CMazeServer::MazeMoveDirection::LEFT))
                            {
                                // Update player position
                                this->UpdateWalker(CMazeWalker::Direction::EAST,
                                    m_pMaze->GetPlayerRowIndex(), m_pMaze->GetPlayerColumn());

                                // Check if game is won
                                if ((m_pMaze->GetEndRowIndex() == m_pMaze->GetPlayerRowIndex()) &&
                                    (m_pMaze->GetEndColumn() == m_pMaze->GetPlayerColumn()))
                                {
                                    // We have won
                                    this->OnWin();
                                }
                            }
                        break;
                    }
                }
            }
        } // if scene active
    }

    void
    CDemoScene::HandleLoad(const Egl::CScene &, Egl::CEventArgs &)
    {   
        // Get our window
        Egl::WindowPtr_t pWindow = this->GetWindow();

        // Update projection and viewport
        this->UpdateProjectionMatrix(pWindow->GetWidth(), pWindow->GetHeight());
        this->UpdateViewport(pWindow->GetWidth(), pWindow->GetHeight());
        
        // Enable texture
        glEnable(GL_TEXTURE_2D);
        glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);				// Sky blue Background
	    glClearDepth(1.0f);									// Depth Buffer Setup
	    
        glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

        // Setup lights
        Egl::LightPtr_t pLight = Egl::CLightingControl::CreateLight<Egl::DIRECTIONAL_LIGHT>();
        pLight->MoveTo(1.0f, 1.0f, 1.0f);
        pLight->SetDifuseColor(1.0f, 0, 0, 0);
        pLight->SetAmbientColor(0.5f, 0.5f, 0.5f, 1.0f);
        pLight->Enable();
        m_vLights.push_back(pLight);
        
        pLight = Egl::CLightingControl::CreateLight<Egl::DIRECTIONAL_LIGHT>();
        pLight->MoveTo(-1.0f, -1.0f, 1.0f);
        pLight->SetDifuseColor(0, 1.0f, 0, 0);
        pLight->Enable();
        m_vLights.push_back(pLight);

        pLight = Egl::CLightingControl::CreateLight<Egl::DIRECTIONAL_LIGHT>();
        pLight->MoveTo(1.0f, -1.0f, 1.0f);
        pLight->SetDifuseColor(0, 0, 1.0f, 0);
        pLight->Enable();
        m_vLights.push_back(pLight);

        Egl::CLightingControl::EnableLighting();        
        
        // Set the camera
        // Camera eye is at (0,0,30)
        //m_pCamera->MoveTo(0.0, 0.0, 30.0); 
        m_pCamera->MoveTo(7.0f, 15.0f, 8.0f); 
        
        // Camera is looking at (0,0,0)
        //m_pCamera->LookAt(Egl::C3DPoint<float>(0.0, 0.0, 0.0)); 
        m_pCamera->LookAt(Egl::C3DPoint<float>(23.0f, -400.0f, 8.0f)); 

        // Up is in positive Y direction for the camera
        m_pCamera->SetUpVector(0.0f, 1.0f, 0.0f);	

        // Set background color
        glClearColor(0.0, 0.0, 0.0, 0.0);        

        //Enable alpha-blending
        glEnable(GL_ALPHA_TEST); 
        glAlphaFunc(GL_GREATER, 0.6f);        

        m_pMazeModel->MoveTo(1, 28, 0);
        m_pMazeModel->RotateTo(0, 0, -80);

        // We want to handle window events now
        pWindow->Reshape += boost::bind(&CDemoScene::HandleReshape, this, _1, _2);
        pWindow->ContextMenuItemSelected += boost::bind(&CDemoScene::HandleContextMenuItemSelected, this, _1, _2);
        pWindow->Key += boost::bind(&CDemoScene::HandleKey, this, _1, _2);
        pWindow->Draw += boost::bind(&CDemoScene::HandleDraw, this, _1, _2);        

        // We want to make sure the right contex menu shows up for this scene
        pWindow->SetContextMenu(m_pContextMenu, Egl::MouseButton::RIGHT);

        // Start demo
        m_citWalkerStep = m_vWalkerSteps.begin();
        m_pWalkerTimer->StartInterval(100);
    }

    void
    CDemoScene::HandleTimerTick(const Egl::CTimer &, Egl::CEventArgs &)
    {
        if (m_pMazeModel->GetPosition().GetY() > 0)
            m_pMazeModel->MoveBy(0, -.56f, 0);

        if (m_pMazeModel->GetPosition().GetX() > -1)
            m_pMazeModel->MoveBy(-.04f, 0, 0);

        if (m_pMazeModel->GetZRotation() < 0)
            m_pMazeModel->RotateBy(0, 0, 1.6f);

        this->Refresh();

        if (m_pMazeModel->GetZRotation() >= 0)
        {
            this->UpdateWalker(
                m_pMazeWalker->GetDirection(), 
                m_pMaze->GetPlayerRowIndex(), 
                m_pMaze->GetPlayerColumn());
            m_pWalkerTimer->Stop();
        }
    }

    void
    CDemoScene::OnWin()
    {
        // Play winning music
        m_pCheersMusic->getSoundObject()->reset();
        m_pCheersMusic->getSoundObject()->play();
    }

    void
    CDemoScene::HandleUnload(const Egl::CScene &, Egl::CEventArgs &)
    {
        // We are not interested on events any longer
        Egl::WindowPtr_t pWindow = this->GetWindow();
        pWindow->Reshape -= boost::bind(&CDemoScene::HandleReshape, this, _1, _2);
        pWindow->Draw -= boost::bind(&CDemoScene::HandleDraw, this, _1, _2);        
        pWindow->Key -= boost::bind(&CDemoScene::HandleKey, this, _1, _2);
        pWindow->ContextMenuItemSelected -= boost::bind(&CDemoScene::HandleContextMenuItemSelected, this, _1, _2);        
    }
   
    void 
    CDemoScene::HandleContextMenuItemSelected(const Egl::CWindow &, Egl::CMenuItemEventArgs & rArgs)
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
                    this->GetSceneManager()->PopScene();
                break;
            }
        } // if scene active
    }

    void 
    CDemoScene::UpdateProjectionMatrix()
    {
        Egl::WindowPtr_t pWindow = this->GetWindow();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();	
        gluPerspective(
            m_nFieldOfView, // field of view in degrees
            static_cast<GLdouble>(pWindow->GetWidth()) / pWindow->GetHeight(), // aspect ratio
            .2, // Z near 
            1000 // Z far
        );
        pWindow->Refresh();
    }

    void 
    CDemoScene::UpdateProjectionMatrix(const int nWidth, const int nHeight)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();	
        gluPerspective(
            m_nFieldOfView, // field of view in degrees
            static_cast<GLdouble>(nWidth) / nHeight, // aspect ratio
            .2, // Z near 
            1000 // Z far
        );
    }

    void 
    CDemoScene::UpdateViewport(const int nWidth, const int nHeight)
    {
        // Set new viewport        
        glViewport(0, 0, nWidth, nHeight);        
    }
    
    void
    CDemoScene::Refresh()
    {
        this->GetWindow()->Refresh();
    }

    void 
    CDemoScene::HandleReshape(const Egl::CWindow &, Egl::CWindowReshapeEventArgs & rArgs)
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

    void 
    CDemoScene::UpdateWalker(const CMazeWalker::Direction_e eDirection,
                             const int nRow, 
                             const int nColumn)
    {
        // Set new walker position and direction
        m_pMazeWalker->SetDirection(eDirection);
        Egl::C3DPoint<float> pMazePosition = m_pMazeModel->GetPosition();
        m_pMazeWalker->MoveTo(
            pMazePosition.GetX() + static_cast<float>(nColumn) + 1.0f, 
            pMazePosition.GetY() + 0.5f, 
            pMazePosition.GetZ() + static_cast<float>(nRow));
        m_pMazeWalker->RotateTo(
            m_pMazeModel->GetXRotation(), 
            m_pMazeModel->GetYRotation(), 
            m_pMazeModel->GetZRotation());
        this->GetWindow()->Refresh();
    }

} // namespace AmazingMaze