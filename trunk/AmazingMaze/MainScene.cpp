#include "Precompiled.hpp"
#include <boost/bind.hpp>
#include "MainScene.hpp"	
#include <locale>
#include "Egl/Context.hpp"
#include "Egl/Texture.hpp"
#include "Egl/Image.hpp"
#include "Egl/Timer.hpp"
#include "Egl/ImageButton.hpp"
#include "3DMenu.hpp"
#include "Egl/Menu.hpp"
#include "Egl/Window.hpp"
#include "CreditScene.hpp"
#include "DemoScene.hpp"
#include "Egl/SceneManager.hpp"
#include "MazeServer.hpp"

namespace AmazingMaze
{
    CMainScene::CMainScene(const Egl::WindowPtr_t & pWindow, 
                           const Egl::SceneManagerPtr_t & pSceneManager, 
                           const Egl::CameraPtr_t & pCamera) : 
                           CTextScene(pWindow, pSceneManager, pCamera),
                           m_pBackgroundImage(),
                           m_pTitleImage(),
                           m_p3DMenu(new C3DMenu()),                           
                           m_pContextMenu(),
                           m_pMazeServer(new CMazeServer())
    {
        // We want to listen to load an unload events fired by us
        this->Load += boost::bind(&CMainScene::HandleLoad, this, _1, _2);
        this->Unload += boost::bind(&CMainScene::HandleUnload, this, _1, _2);

        // Load background        
        // Position is <-34.5f, -22.0f, -50.0f>
        // Width is 69. Height is 44
        m_pBackgroundImage.reset(new Egl::CImage(-34.5f, -22.0f, -50.0f, 69.0f, 44.0f, 
            pWindow->GetContext()->LoadTexture("textures/background2.jpg")));
        m_pBackgroundImage->SetWindow(pWindow);

        // Title image
        // Position is <-6.5, 4.2, 0>
        // Width is 16, height is 3
        m_pTitleImage.reset(new Egl::CImage(-7.2f, 4.2f, 0,
            16.0f, 3.0f, pWindow->GetContext()->LoadTexture("textures/title.png")));
        m_pTitleImage->SetWindow(pWindow);

        // Create main menu
        m_p3DMenu->AddItem(CMainScene::MENU_ITEM_ID_START,
            6.0f, 2.0f, pWindow->GetContext()->LoadTexture("textures/start0.png"))
            .SetStateImage(C3DMenuItem::SelectedState, 
                pWindow->GetContext()->LoadTexture("textures/start1.png"));

        m_p3DMenu->AddItem(CMainScene::MENU_ITEM_ID_INSTRUCTIONS, 
            9.0f, 2.0f, pWindow->GetContext()->LoadTexture("textures/instr0.png"))
            .SetStateImage(C3DMenuItem::SelectedState, 
                pWindow->GetContext()->LoadTexture("textures/instr1.png"));

        m_p3DMenu->AddItem(CMainScene::MENU_ITEM_ID_CREDITS,
            6.0f, 2.0f, pWindow->GetContext()->LoadTexture("textures/credits0.png"))
            .SetStateImage(C3DMenuItem::SelectedState, 
                pWindow->GetContext()->LoadTexture("textures/credits1.png"));

        m_p3DMenu->AddItem(CMainScene::MENU_ITEM_ID_QUIT,
            6.0f, 2.0f, pWindow->GetContext()->LoadTexture("textures/quit0.png"))
            .SetStateImage(C3DMenuItem::SelectedState, 
                pWindow->GetContext()->LoadTexture("textures/quit1.png"));

        m_p3DMenu->MoveTo(-4.0f, 2.0f, 0);
        m_p3DMenu->SetWindow(pWindow);

        // Create menu
        m_pContextMenu = pWindow->GetContext()->CreateMenu();
        m_pContextMenu->AddItem("Show help window", CMainScene::MENU_ITEM_ID_HELP, false);        
        m_pContextMenu->AddItem("Show credits", CMainScene::MENU_ITEM_ID_CREDITS, false);
        m_pContextMenu->AddItem("Quit", CMainScene::MENU_ITEM_ID_QUIT, false);                
    }

    CMainScene::~CMainScene(void)
    {
    }

    void
    CMainScene::HandleDraw(const Egl::CWindow &, Egl::CEventArgs &)
    {
        // Clear the background
        glMatrixMode(GL_MODELVIEW);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                            
        // Draw background
        m_pBackgroundImage->Draw();        
        
        // Draw title
        m_pTitleImage->Draw();
        
        // Draw menu
        m_p3DMenu->Draw();            

        // Flush all actions
        glFlush();

        // Repaint screen with content of back buffer
        this->GetWindow()->SwapBuffers();
    }

    void 
    CMainScene::HandleKey(const Egl::CWindow &, Egl::CKeyEventArgs & rArgs)
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
                            // Close window
                            // This would be the place for an 
                            // "are you sure?" dialog
                            this->GetWindow()->Close();
                        break;

                        // Help key
                        case 'I': 
                            //m_pHelpWindow->Show();
                        break;
                    }
                }
                else // System key
                {
                    switch (rArgs.GetCharCode())
                    {
                        // Up arrow
                        case 14:
                        {
                            // select the previous menu item
                            m_p3DMenu->SelectPrevItem();
                        }
                        break;

                        // Down arrow
                        case 16:
                        {
                            // select the next menu item
                            m_p3DMenu->SelectNextItem();
                        }
                        break;

                        // Enter
                        case 30:
                        {
                            // Get currently selected menu item id
                            switch (m_p3DMenu->GetSelectedItemId())
                            {
                                // Demo
                                case CMainScene::MENU_ITEM_ID_START:
                                    // Show credits
                                    this->ShowDemoScene();
                                break;

                                // Credits
                                case CMainScene::MENU_ITEM_ID_CREDITS:
                                    // Show credits
                                    this->ShowCreditScene();
                                break;

                                // Quit
                                case CMainScene::MENU_ITEM_ID_QUIT:
                                    this->GetWindow()->Close();
                                break;
                            }                        
                        }
                        break;
                    }
                }
            }
        } // if scene active
    }

    void
    CMainScene::HandleLoad(const Egl::CScene &, Egl::CEventArgs &)
    {   
        // Now we can handle window events
        Egl::WindowPtr_t pWindow = this->GetWindow();
        pWindow->ContextMenuItemSelected += boost::bind(&CMainScene::HandleContextMenuItemSelected, this, _1, _2);
        pWindow->Key += boost::bind(&CMainScene::HandleKey, this, _1, _2);
        pWindow->Draw += boost::bind(&CMainScene::HandleDraw, this, _1, _2);        

        // We want to make sure the right contex menu shows up for this scene
        pWindow->SetContextMenu(m_pContextMenu, Egl::MouseButton::RIGHT);
    }

    void
    CMainScene::HandleUnload(const Egl::CScene &, Egl::CEventArgs &)
    {
        // We are not interested on events any longer
        Egl::WindowPtr_t pWindow = this->GetWindow();
        pWindow->Draw -= boost::bind(&CMainScene::HandleDraw, this, _1, _2);        
        pWindow->Key -= boost::bind(&CMainScene::HandleKey, this, _1, _2);
        pWindow->ContextMenuItemSelected -= boost::bind(&CMainScene::HandleContextMenuItemSelected, this, _1, _2);        
    }
   
    void 
    CMainScene::HandleContextMenuItemSelected(const Egl::CWindow &, Egl::CMenuItemEventArgs & rArgs)
    {
        // Make sure we only handle this event if
        // this scene is active
        if (this->IsActive())
        {
            // Switch on the ID of the item
            switch (rArgs.GetItemId())
            {
                // Toggle help
                case CMainScene::MENU_ITEM_ID_HELP:
                    //m_pHelpWindow->Show();
                break;

                // Quit menu item.
                case CMainScene::MENU_ITEM_ID_QUIT:
                    this->GetWindow()->Close();
                break;

                // Credits
                case CMainScene::MENU_ITEM_ID_CREDITS:
                    // Show credit window
                    this->ShowCreditScene();
                break;

                // Start
                case CMainScene::MENU_ITEM_ID_START:
                    // Show credit window
                    this->ShowDemoScene();
                break;
            }
        }
    }

    void 
    CMainScene::ShowCreditScene()
    {
        // Push the credits scene onto the stack
        Egl::SceneManagerPtr_t pSceneManager = this->GetSceneManager();
        Egl::WindowPtr_t pWindow = this->GetWindow();
        pSceneManager->PushScene(Egl::ScenePtr_t(
            new CCreditScene(pWindow, pSceneManager, this->GetCamera())));

        // Refresh the window so the right scene is shown
        pWindow->Refresh();
    }

    void 
    CMainScene::ShowDemoScene()
    {
        // Push the credits scene onto the stack
        Egl::SceneManagerPtr_t pSceneManager = this->GetSceneManager();
        Egl::WindowPtr_t pWindow = this->GetWindow();
        pSceneManager->PushScene(Egl::ScenePtr_t(
            new CDemoScene(pWindow, pSceneManager, this->GetCamera(), 
            m_pMazeServer, m_pMazeServer->CreateMaze(16, 21, CMaze::MazeEndStyle::LEFTRIGHT))));

        // Refresh the window so the right scene is shown
        pWindow->Refresh();
    }

} // namespace AmazingMaze