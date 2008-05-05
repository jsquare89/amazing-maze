#include "Precompiled.hpp"
#include <boost/bind.hpp>
#include "MainWindow.hpp"	
#include <locale>
#include "Egl/Context.hpp"
#include "Egl/LightingControl.hpp"
#include "Egl/Light.hpp"
#include "Egl/Camera.hpp"
#include "Egl/SurfaceProperties.hpp"	
#include "Egl/Texture.hpp"
#include "Egl/Image.hpp"
#include "Egl/ImageButton.hpp"
#include "3DMenu.hpp"
#include "MazeMusic.hpp"
#include "Egl/Menu.hpp"
#include "HelpWindow.hpp"


// Remove CreateWindow macro
#undef CreateWindow

namespace AmazingMaze
{
    CMainWindow::CMainWindow(void) : CWindow(),
                                     m_vLights(),
                                     m_pCamera(),
                                     m_pBackgroundTexture(),
                                     m_pMainMenu(new C3DMenu()),
                                     m_pCreditsMenu(new C3DMenu()),
                                     m_bInMainMenu(true),
                                     m_pMazeMusic(),
                                     m_pContextMenu(),
                                     m_pHelpWindow()
    {
        // We are interested in listening to
        // some events                
        this->OnCreate += boost::bind(&CMainWindow::HandleOnCreate, this);        
        this->OnDestroy += boost::bind(&CMainWindow::HandleOnDestroy, this);

        this->OnReshape += boost::bind(&CMainWindow::HandleOnReshape, this, _1, _2);
        this->OnKey += boost::bind(&CMainWindow::HandleOnKey, this, _1, _2, _3, _4, _5);        
    }

    CMainWindow::~CMainWindow(void)
    {
        // Close midi if open
        this->CloseMidi();
    }

    void
    CMainWindow::HandleOnDraw(void)
    {
        // Clear the background
        glMatrixMode(GL_MODELVIEW);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                            
        // Bind background texture
        m_pBackgroundTexture->Bind();

        // Draw background
        glBegin(GL_QUADS);
        {
            // Bottom Left
            glTexCoord2f(1, 1);
		    glVertex3f(-34.0f, -22.0f, -50.0f);	

            glTexCoord2f(1, 0);
            glVertex3f(-34.0f,  22.0f, -50.0f);	// Top Left

            glTexCoord2f(0, 0);
		    glVertex3f(34.0f,  22.0f, -50.0f);	// Top Right

            glTexCoord2f(0, 1);
		    glVertex3f(34.0f, -22.0f, -50.0f);	// Bottom Right
        }
        glEnd();

        m_pBackgroundTexture->UnBind();
        
        
        // Draw title
        m_pTitleImage->Draw();

        // Are we in the main menu?
        if (m_bInMainMenu)
        {
            // Draw main menu
            m_pMainMenu->Draw();
        }
        else
        {
            // Draw credits menu
            m_pCreditsMenu->Draw();
        }
            

        // Flush all actions
        glFlush();

        // Repaint screen with content of back buffer
        this->SwapBuffers();
    }

    void 
    CMainWindow::HandleOnReshape(int nWidth, int nHeight)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();	
        gluPerspective(
            30.0, // field of view in degrees
            static_cast<GLdouble>(nWidth) / nHeight, // aspect ratio
            1.0, // Z near 
            100.0 // Z far
        );	

        // Set new viewport
        glMatrixMode(GL_MODELVIEW);
        glViewport(0, 0, nWidth, nHeight);        
    }

    void 
    CMainWindow::HandleOnKey(int nKeyCode, bool bIsSystemKey, Egl::KeyState_e eKeyState, int nCursorX, int nCursorY)
    {
        // Avoid warning
        nCursorX;
        nCursorY;

        // Non system key and key being released?
        if ((Egl::KeyState::DOWN == eKeyState))
        {
            // Regular key?
            if (!bIsSystemKey)
            {
                // Current locale
                std::locale loc("");

                // Switch on the key
                switch (std::use_facet<std::ctype<char> > (loc).
                    toupper(static_cast<char>(nKeyCode)))
                {
                    // Exit key
                    case 'Q':
                        this->Close();
                    break;

                    // Increase volume
                    case '+':
                        m_pMazeMusic->setVolume(m_pMazeMusic->getSoundObject()->getVolume() + .1);
                    break;

                    // Decrease volume
                    case '-':
                        m_pMazeMusic->setVolume(m_pMazeMusic->getSoundObject()->getVolume() - .1);
                    break;

                    // help key
                    case 'I': 
                        m_pHelpWindow->Show();
                    break;
                }
            }
            else // System key
            {
                switch (nKeyCode)
                {
                    // Left arrow
                    case 13:
                    {
                        
                    }
                    break;

                    // Up arrow
                    case 14:
                    {
                        // If we are showing the main menu
                        // select the previous menu item
                        if (m_bInMainMenu)
                            m_pMainMenu->SelectPrevItem();
                    }
                    break;

                    // Right arrow
                    case 15:
                    {
                        
                    }
                    break;

                    // Down arrow
                    case 16:
                    {
                        // If we are showing the main menu
                        // select the next menu item
                        if (m_bInMainMenu)
                            m_pMainMenu->SelectNextItem();
                    }
                    break;

                    // Enter
                    case 30:
                    {
                        // Are we showing main menu?
                        if (m_bInMainMenu)
                        {
                            // Get currently selected menu item id
                            switch (m_pMainMenu->GetSelectedItemId())
                            {
                                // Credits
                                case CMainWindow::MENU_ITEM_ID_CREDITS:
                                    // We are not showing the main window anymore
                                    m_bInMainMenu = false;
                                    this->Refresh();
                                break;

                                // Quit
                                case CMainWindow::MENU_ITEM_ID_QUIT:
                                    this->Close();
                                break;
                            }
                        }
                        else
                        {
                            // Get currently selected menu item id
                            switch (m_pCreditsMenu->GetSelectedItemId())
                            {
                                // Quit -> Back to main menu
                                case CMainWindow::MENU_ITEM_ID_QUIT:
                                    m_bInMainMenu = true;
                                    this->Refresh();
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    void
    CMainWindow::HandleOnCreate(void)
    {
        // Load background texture
        m_pBackgroundTexture = this->GetContext()->LoadTexture("textures/background2.jpg");
        
        // Force a "reshape" so the right 
        // projection matrix and viewport
        // are set
        this->HandleOnReshape(this->GetWidth(), this->GetHeight());        	        
        
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
        m_pCamera = this->GetContext()->CreateCamera();
        
        m_pCamera->MoveTo(0.0, 0.0, 30.0); // eye is at (0,0,30)
        m_pCamera->LookAt(Egl::C3DPoint<float>(0.0, 0.0, 0.0)); // center is at (0,0,0)
        m_pCamera->SetUpVector(0.0, 1.0, 0.0);	// up is in positive Y direction 

        // Tell the camera about the window
        m_pCamera->SetWindow(this->shared_from_this());

        // Set background color
        glClearColor(0.0, 0.0, 0.0, 0.0);        

        //Enable alpha-blending
        glEnable(GL_ALPHA_TEST); 
        glAlphaFunc(GL_GREATER, 0.6f);
        //glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        // Tittle image
        m_pTitleImage.reset(new Egl::CImage(0, 0, 0,
            10.0f, 2.0f, this->GetContext()->LoadTexture("textures/title.png")));
        m_pTitleImage->MoveTo(-2, 3, 0);        
        m_pTitleImage->SetWindow(this->shared_from_this());

        // Create main menu
        m_pMainMenu->AddItem(CMainWindow::MENU_ITEM_ID_START,
            6.0f, 2.0f, this->GetContext()->LoadTexture("textures/start0.png"))
            .SetStateImage(C3DMenuItem::SelectedState, 
                this->GetContext()->LoadTexture("textures/start1.png"));

        m_pMainMenu->AddItem(CMainWindow::MENU_ITEM_ID_INSTRUCTIONS, 
            9.0f, 2.0f, this->GetContext()->LoadTexture("textures/instr0.png"))
            .SetStateImage(C3DMenuItem::SelectedState, 
                this->GetContext()->LoadTexture("textures/instr1.png"));

        m_pMainMenu->AddItem(CMainWindow::MENU_ITEM_ID_CREDITS,
            6.0f, 2.0f, this->GetContext()->LoadTexture("textures/credits0.png"))
            .SetStateImage(C3DMenuItem::SelectedState, 
                this->GetContext()->LoadTexture("textures/credits1.png"));

        m_pMainMenu->AddItem(CMainWindow::MENU_ITEM_ID_QUIT,
            6.0f, 2.0f, this->GetContext()->LoadTexture("textures/quit0.png"))
            .SetStateImage(C3DMenuItem::SelectedState, 
                this->GetContext()->LoadTexture("textures/quit1.png"));

        m_pMainMenu->MoveTo(-4, 2.5, 0);
        m_pMainMenu->SetWindow(this->shared_from_this());

        // Set up credits menu
        m_pCreditsMenu->AddItem(-1,
            10.0f, 2.0f, this->GetContext()->LoadTexture("textures/delfin.png"));

        m_pCreditsMenu->AddItem(-1, 
            9.0f, 2.0f, this->GetContext()->LoadTexture("textures/anthony.png"));

        m_pCreditsMenu->AddItem(-1,
            10.0f, 2.0f, this->GetContext()->LoadTexture("textures/george.png"));

        m_pCreditsMenu->AddItem(-1,
            10.0f, 2.0f, this->GetContext()->LoadTexture("textures/carlos.png"));

        m_pCreditsMenu->AddItem(CMainWindow::MENU_ITEM_ID_QUIT,
            6.0f, 2.0f, this->GetContext()->LoadTexture("textures/quit0.png"))
            .SetStateImage(C3DMenuItem::SelectedState, 
                this->GetContext()->LoadTexture("textures/quit1.png"));
        m_pCreditsMenu->SelectNextItem();
        m_pCreditsMenu->SelectNextItem();
        m_pCreditsMenu->SelectNextItem();
        m_pCreditsMenu->SelectNextItem();

        m_pCreditsMenu->MoveTo(-4, 2.9f, 0);
        m_pCreditsMenu->SetWindow(this->shared_from_this());

        // Create help window and hide it
        m_pHelpWindow = this->CreateWindow<CHelpWindow>(
            Egl::SurfaceProperties::SURFACE_RGBA | 
            Egl::SurfaceProperties::SURFACE_SINGLE,
            0, 0, 
            800, 600);                        
        m_pHelpWindow->Hide();

        // Create menu
        m_pContextMenu = this->GetContext()->CreateMenu();
        m_pContextMenu->AddItem("Show help window", TOGGLE_HELP_MENU_ITEM_ID, false);        
        m_pContextMenu->AddItem("Show credits", TOGGLE_CREDITS_MENU_ITEM_ID, false);
        m_pContextMenu->AddItem("Quit", QUIT_MENU_ITEM_ID, false);
        this->OnContextMenuItemSelected += boost::bind(&CMainWindow::HandleOnContextMenuItemSelected, this, _1);
        this->SetContextMenu(m_pContextMenu, Egl::MouseButton::RIGHT);

        // 
        // Start playing audio
        //this->OpenMidi("voltes_v_opening_midi.mid");
        m_pMazeMusic.reset(new CMazeMusic("sounds\\Tool - Reflection.mp3"));
        m_pMazeMusic->getSoundObject()->play();
        m_pMazeMusic->getSoundObject()->setRepeat(true);

        // Now we can handle draw events
        this->OnDraw += boost::bind(&CMainWindow::HandleOnDraw, this);        
    }

    void
    CMainWindow::HandleOnDestroy(void)
    {
        // Post quit message to message loop
        this->GetContext()->BreakMainLoop();
    }

    void 
    CMainWindow::CloseMidi()
    {
        // Close midi
        ::mciSendString("close CSC310P2cMidi", 0, 0, 0);        
    }

    void 
    CMainWindow::OpenMidi(const std::string & strFilePath)
    {
        // Open midi
        this->CloseMidi();
        std::string strFullPath = (std::string("open ") + strFilePath + " type sequencer alias CSC310P2cMidi");
        ::mciSendString(strFullPath.c_str(), 0, 0, 0);
    }

    void 
    CMainWindow::PlayMidi()
    {
        // Play midi
        ::mciSendString("stop CSC310P2cMidi", 0, 0, 0);
        ::mciSendString("play CSC310P2cMidi", 0, 0, 0);
    }

    void 
    CMainWindow::HandleOnContextMenuItemSelected(int nMenuItemId)
    {
        // Switch on the ID of the item
        switch (nMenuItemId)
        {
            // Toggle help
            case TOGGLE_HELP_MENU_ITEM_ID:
                m_pHelpWindow->Show();
            break;

            // Quit menu item.
            case QUIT_MENU_ITEM_ID:
                this->Close();
            break;

            // Credits
            case TOGGLE_CREDITS_MENU_ITEM_ID:
                m_bInMainMenu = false;
                this->Refresh();
            break;
        }
    }
} // namespace AmazingMaze