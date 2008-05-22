#include "Precompiled.hpp"
#include <boost/bind.hpp>
#include "StandardGameScene.hpp"	
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
#include "GameStartScene.hpp"
#include "HelpScene.hpp"

namespace AmazingMaze
{
    CStandardGameScene::CStandardGameScene(const Egl::WindowPtr_t & pWindow, 
                           const Egl::SceneManagerPtr_t & pSceneManager, 
                           const Egl::CameraPtr_t & pCamera,
                           const MazeServerPtr_t & pMazeServer,
                           const MazePtr_t & pMaze) : 
                           Egl::CScene(pWindow, pSceneManager),
                           m_pCamera(pCamera),
                           m_pContextMenu(),                           
                           m_nFieldOfView(65),
                           m_vLights(),
                           m_pAutoSolveWalkerTimer(pWindow->GetContext()->CreateTimer()),
                           m_vMazeSolution(),
                           m_citMazeSolutionStep(),
                           m_pCheersMusic(new CMazeMusic("sounds\\FX\\Cheers.mp3")),
                           m_pMazeServer(pMazeServer),
                           m_pMaze(pMaze),
                           m_pMazeModel(new C3DMazeModel(pMaze)),
                           m_pMazeWalker(),
                           m_bFirstLoad(true),
                           m_bAutoSolveMode(false),
                           m_pExitTimer()
    {
        // We want to listen to load an unload events fired by us
        this->Load += boost::bind(&CStandardGameScene::HandleLoad, this, _1, _2);
        this->Unload += boost::bind(&CStandardGameScene::HandleUnload, this, _1, _2);        
        m_pAutoSolveWalkerTimer->Tick += boost::bind(&CStandardGameScene::HandleAutoWalkerTimerTick, this, _1, _2);

        // Set the 3D maze model textures
        m_pMazeModel->SetFloorTexture(pWindow->GetContext()->LoadTexture("textures/floor-cracks.bmp"));
        m_pMazeModel->SetWallTexture(pWindow->GetContext()->LoadTexture("textures/wall-cracks.bmp"));
        
        // Create context menu
        m_pContextMenu = pWindow->GetContext()->CreateMenu();
        m_pContextMenu->AddItem("Show help window", CStandardGameScene::MENU_ITEM_ID_INSTRUCTIONS, false);        
        m_pContextMenu->AddItem("Back to main screen", CStandardGameScene::MENU_ITEM_ID_QUIT, false);                        
    }

    CStandardGameScene::~CStandardGameScene(void)
    {
    }

    void
    CStandardGameScene::HandleDraw(const Egl::CWindow &, Egl::CEventArgs &)
    {
        // Clear the background
        glMatrixMode(GL_MODELVIEW);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();

        // Center the maze horizontally on the screen
        glTranslatef(0,0,-1.5);

        // Draw maze and walker
        m_pMazeModel->Draw();
        m_pMazeWalker->Draw();
        
        glPopMatrix();

        // Flush all actions
        glFlush();

        // Repaint screen with content of back buffer
        this->GetWindow()->SwapBuffers();
    }

    void 
    CStandardGameScene::HandleKey(const Egl::CWindow &, Egl::CKeyEventArgs & rArgs)
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
                        // Exit 
                        case 'Q':
                            // Go back to the main screen
                            // if the exit timer is not set
                            if (!m_pMaze->IsSolved())
                                this->GetSceneManager()->PopScene();
                        break;

                        // Solve maze
                        case 'S':
                            // Solve maze unless it is already solved
                            if (!m_pMaze->IsSolved())
                                this->PlayMazeSolution(m_pMazeServer->Solve(m_pMaze));
                        break;

                        // Help key
                        case 'I': 
                            // Show instructions if we are not in auto mode
                            if (!m_bAutoSolveMode)
                                this->ShowHelpScene();
                        break;
                    }
                }
                else // System key
                {
                    switch (rArgs.GetCharCode())
                    {
                        // Left
                        case 13:
                            // Check we are not in auto mode
                            if (!this->m_bAutoSolveMode && !m_pMaze->IsSolved())
                            {
                                // Can we move left (left is up since the maze is rotated)
                                if (m_pMazeServer->Move(m_pMaze, CMazeServer::MazeMoveDirection::UP))
                                {
                                    // Update player position
                                    this->UpdateWalker(CMazeWalker::Direction::NORTH,
                                        m_pMaze->GetPlayerRowIndex(), m_pMaze->GetPlayerColumn());

                                    // Check if game is won
                                    if (m_pMaze->IsSolved())
                                    {
                                        // We have won
                                        this->OnWin();
                                    }
                                }
                            }
                        break;

                        // Up 
                        case 14:
                            // Check we are not in auto mode
                            if (!this->m_bAutoSolveMode && !m_pMaze->IsSolved())
                            {
                                // Can we move up, up is right b/c the maze is rotated
                                if (m_pMazeServer->Move(m_pMaze, CMazeServer::MazeMoveDirection::RIGHT))
                                {
                                    // Update player position
                                    this->UpdateWalker(CMazeWalker::Direction::WEST,
                                        m_pMaze->GetPlayerRowIndex(), m_pMaze->GetPlayerColumn());

                                    // Check if game is won
                                    if (m_pMaze->IsSolved())
                                    {
                                        // We have won
                                        this->OnWin();
                                    }
                                }
                            }
                        break;

                        // Right 
                        case 15:
                            // Check we are not in auto mode
                            if (!this->m_bAutoSolveMode && !m_pMaze->IsSolved())
                            {
                                // Can we move right? Rightis down b/c the maze is rotated
                                if (m_pMazeServer->Move(m_pMaze, CMazeServer::MazeMoveDirection::DOWN))
                                {
                                    // Update player position
                                    this->UpdateWalker(CMazeWalker::Direction::SOUTH,
                                        m_pMaze->GetPlayerRowIndex(), m_pMaze->GetPlayerColumn());

                                    // Check if game is won
                                    if (m_pMaze->IsSolved())
                                    {
                                        // We have won
                                        this->OnWin();
                                    }
                                }
                            }
                        break;

                        // Down 
                        case 16:
                            // Check we are not in auto mode
                            if (!this->m_bAutoSolveMode && !m_pMaze->IsSolved())
                            {
                                // Can we move down? Down is left b/c the maze is rotated
                                if (m_pMazeServer->Move(m_pMaze, CMazeServer::MazeMoveDirection::LEFT))
                                {
                                    // Update player position
                                    this->UpdateWalker(CMazeWalker::Direction::EAST,
                                        m_pMaze->GetPlayerRowIndex(), m_pMaze->GetPlayerColumn());

                                    // Check if game is won
                                    if (m_pMaze->IsSolved())
                                    {
                                        // We have won
                                        this->OnWin();
                                    }
                                }
                            }
                        break;
                    }
                }
            }
        } // if scene active
    }

    void
    CStandardGameScene::HandleLoad(const Egl::CScene &, Egl::CEventArgs &)
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

        // Is this the first time we load this scene?
        if (m_bFirstLoad)
        {
            // Not first load anymore
            m_bFirstLoad = false;
            
            // Show intro scene
            Egl::SceneManagerPtr_t pSceneManager = this->GetSceneManager();
            pSceneManager->PushScene(Egl::ScenePtr_t(
                new CGameStartScene(pWindow, pSceneManager, m_pMazeModel)));
        }
        else
        {
            // We should be done with the intro by now so 
            // create the maze walker.
            m_pMazeWalker.reset(new CSphereMazeWalker(0.4f)),

            // We want to handle window events now
            pWindow->Reshape += boost::bind(&CStandardGameScene::HandleReshape, this, _1, _2);
            pWindow->ContextMenuItemSelected += boost::bind(&CStandardGameScene::HandleContextMenuItemSelected, this, _1, _2);
            pWindow->Key += boost::bind(&CStandardGameScene::HandleKey, this, _1, _2);
            pWindow->Draw += boost::bind(&CStandardGameScene::HandleDraw, this, _1, _2);        

            // We want to make sure the right contex menu shows up for this scene
            pWindow->SetContextMenu(m_pContextMenu, Egl::MouseButton::RIGHT);        

            // Update the walker's position and rotation
            // relative to the maze.
            this->UpdateWalker(
                CMazeWalker::Direction::NORTH, 
                m_pMaze->GetPlayerRowIndex(), 
                m_pMaze->GetPlayerColumn());
        }        
    }

    void
    CStandardGameScene::HandleAutoWalkerTimerTick(const Egl::CTimer &, Egl::CEventArgs &)
    {
        // Stop timer when we reach the end
        if (m_citMazeSolutionStep == m_vMazeSolution.end())
        {
            m_pAutoSolveWalkerTimer->Stop();
            this->OnWin();
        }
        else
        {
            // Advance one step
            if (m_pMazeServer->Move(m_pMaze, *m_citMazeSolutionStep))
            {
                // Update player position
                this->UpdateWalker(CMazeWalker::Direction::WEST,
                    m_pMaze->GetPlayerRowIndex(), m_pMaze->GetPlayerColumn());
            }

            // Advance
            ++m_citMazeSolutionStep;
        }        
    }

    void
    CStandardGameScene::OnWin()
    {
        // Play winning music
        m_pCheersMusic->getSoundObject()->reset();
        m_pCheersMusic->getSoundObject()->play();

        // Set up timer to go back to main scene
        m_pExitTimer = this->GetWindow()->GetContext()->CreateTimer();
        m_pExitTimer->Tick += boost::bind(&CStandardGameScene::HandleExitTimerTick, this, _1, _2);
        m_pExitTimer->StartTimeout(16000);

    }

    void
    CStandardGameScene::HandleExitTimerTick(const Egl::CTimer &, Egl::CEventArgs &)
    {
        // Return to the main scene
        this->GetSceneManager()->PopScene();
    }

    void
    CStandardGameScene::HandleUnload(const Egl::CScene &, Egl::CEventArgs &)
    {
        // We are not interested on events any longer
        Egl::WindowPtr_t pWindow = this->GetWindow();
        pWindow->Reshape -= boost::bind(&CStandardGameScene::HandleReshape, this, _1, _2);
        pWindow->Draw -= boost::bind(&CStandardGameScene::HandleDraw, this, _1, _2);        
        pWindow->Key -= boost::bind(&CStandardGameScene::HandleKey, this, _1, _2);
        pWindow->ContextMenuItemSelected -= boost::bind(&CStandardGameScene::HandleContextMenuItemSelected, this, _1, _2);        
    }
   
    void 
    CStandardGameScene::HandleContextMenuItemSelected(const Egl::CWindow &, Egl::CMenuItemEventArgs & rArgs)
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

                // Quit menu item.
                case MENU_ITEM_ID_INSTRUCTIONS:
                    this->ShowHelpScene();
                break;
            }
        } // if scene active
    }

    void 
    CStandardGameScene::UpdateProjectionMatrix()
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
    CStandardGameScene::UpdateProjectionMatrix(const int nWidth, const int nHeight)
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
    CStandardGameScene::UpdateViewport(const int nWidth, const int nHeight)
    {
        // Set new viewport        
        glViewport(0, 0, nWidth, nHeight);        
    }
    
    void
    CStandardGameScene::Refresh()
    {
        this->GetWindow()->Refresh();
    }

    void 
    CStandardGameScene::HandleReshape(const Egl::CWindow &, Egl::CWindowReshapeEventArgs & rArgs)
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
    CStandardGameScene::UpdateWalker(const CMazeWalker::Direction_e eDirection,
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
    
    void 
    CStandardGameScene::PlayMazeSolution(const CMazeServer::MazeSolution_t & vMazeSolution)
    {
        // Start auto mode
        m_bAutoSolveMode = true;

        // Assign solution
        m_vMazeSolution = vMazeSolution;               
        m_citMazeSolutionStep = m_vMazeSolution.begin();

        // Start timer
        m_pAutoSolveWalkerTimer->StartInterval(300);
    }

    void 
    CStandardGameScene::ShowHelpScene()
    {
        // Push the credits scene onto the stack
        Egl::SceneManagerPtr_t pSceneManager = this->GetSceneManager();
        Egl::WindowPtr_t pWindow = this->GetWindow();
        pSceneManager->PushScene(Egl::ScenePtr_t(
            new CHelpScene(pWindow, pSceneManager, m_pCamera)));

        // Refresh the window so the right scene is shown
        pWindow->Refresh();
    }

} // namespace AmazingMaze