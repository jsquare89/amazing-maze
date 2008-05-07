#include "Precompiled.hpp"
#include <boost/bind.hpp>
#include "CreditScene.hpp"	
#include <locale>
#include "Egl/Context.hpp"
#include "Egl/Texture.hpp"
#include "Egl/Image.hpp"
#include "Egl/Timer.hpp"
#include "Egl/ImageButton.hpp"
#include "3DMenu.hpp"
#include "Egl/Menu.hpp"
#include "Egl/Window.hpp"
#include "Egl/SceneManager.hpp"

namespace AmazingMaze
{
    CCreditScene::CCreditScene(const Egl::WindowPtr_t & pWindow, 
                           const Egl::SceneManagerPtr_t & pSceneManager, 
                           const Egl::CameraPtr_t & pCamera) : 
                           CTextScene(pWindow, pSceneManager, pCamera),
                           m_pBackgroundImage(),
                           m_pTitleImage(),
                           m_p3DNamesMenu(new C3DMenu()),
                           m_p3DEmailsMenu(new C3DMenu()),
                           m_pContextMenu()
    {
        // We want to listen to load an unload events fired by us
        this->Load += boost::bind(&CCreditScene::HandleLoad, this, _1, _2);
        this->Unload += boost::bind(&CCreditScene::HandleUnload, this, _1, _2);

        // Load background        
        // Position is <-34.5f, -22.0f, -50.0f>
        // Width is 69. Height is 44
        m_pBackgroundImage.reset(new Egl::CImage(-34.5f, -22.0f, -50.0f, 69.0f, 44.0f, 
            pWindow->GetContext()->LoadTexture("textures/background2.jpg")));
        m_pBackgroundImage->SetWindow(pWindow);

        // Title image
        // Position is <-6.5, 4.2, 0>
        // Width is 16, height is 3
        m_pTitleImage.reset(new Egl::CImage(-6.5f, 4.2f, 0,
            16.0f, 3.0f, pWindow->GetContext()->LoadTexture("textures/title.png")));
        m_pTitleImage->SetWindow(pWindow);

        // Set up credits menu
        // We use item id -1 for the items we don't
        // care about (cannot be selected)
        m_p3DNamesMenu->AddItem(-1,
            10.0f, 1.5f, pWindow->GetContext()->LoadTexture("textures/delfin.png"));

        m_p3DEmailsMenu->AddItem(-1,
            8.0f, 2.0f, pWindow->GetContext()->LoadTexture("textures/emaildel.png"));

		m_p3DNamesMenu->AddItem(-1, 
            10.0f, 1.5f, pWindow->GetContext()->LoadTexture("textures/anthony.png"));

        m_p3DEmailsMenu->AddItem(-1,
            8.0f, 2.0f, pWindow->GetContext()->LoadTexture("textures/emailant.png"));

		m_p3DNamesMenu->AddItem(-1,
            10.0f, 1.5f, pWindow->GetContext()->LoadTexture("textures/george.png"));

        m_p3DEmailsMenu->AddItem(-1,
            8.0f, 2.0f, pWindow->GetContext()->LoadTexture("textures/emailgeo.png"));

		m_p3DNamesMenu->AddItem(-1,
            10.0f, 1.5f, pWindow->GetContext()->LoadTexture("textures/carlos.png"));

        m_p3DEmailsMenu->AddItem(-1,
            8.0f, 2.0f, pWindow->GetContext()->LoadTexture("textures/emailcar.png"));

		// Add quit item which can be selected
        m_p3DNamesMenu->AddItem(CCreditScene::MENU_ITEM_ID_QUIT,
            6.0f, 2.0f, pWindow->GetContext()->LoadTexture("textures/quit0.png"))
            .SetStateImage(C3DMenuItem::SelectedState, 
                pWindow->GetContext()->LoadTexture("textures/quit1.png"))
            .SetMargins(12.0f, 3.4f);

    
        // Select Quit/back
        m_p3DNamesMenu->SelectItem(CCreditScene::MENU_ITEM_ID_QUIT);

        // Move the whole menu into position
        m_p3DNamesMenu->MoveTo(-8.0f, 1.5f, 0);
        m_p3DNamesMenu->SetWindow(pWindow);
        m_p3DEmailsMenu->MoveTo(4.0f, 1.5f, 0);
        m_p3DEmailsMenu->SetWindow(pWindow);

        // Create context menu
        m_pContextMenu = pWindow->GetContext()->CreateMenu();
        m_pContextMenu->AddItem("Show help window", CCreditScene::MENU_ITEM_ID_HELP, false);        
        m_pContextMenu->AddItem("Back to main screen", CCreditScene::MENU_ITEM_ID_QUIT, false);                
    }

    CCreditScene::~CCreditScene(void)
    {
    }

    void
    CCreditScene::HandleDraw(const Egl::CWindow &, Egl::CEventArgs &)
    {
        // Clear the background
        glMatrixMode(GL_MODELVIEW);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                            
        // Draw background
        m_pBackgroundImage->Draw();
        
        // Draw title
        m_pTitleImage->Draw();
        
        // Draw menus
        m_p3DNamesMenu->Draw();            
        m_p3DEmailsMenu->Draw();

        // Flush all actions
        glFlush();

        // Repaint screen with content of back buffer
        this->GetWindow()->SwapBuffers();
    }

    void 
    CCreditScene::HandleKey(const Egl::CWindow &, Egl::CKeyEventArgs & rArgs)
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
                        // Enter
                        case 30:
                        {
                            // Get currently selected menu item id
                            switch (m_p3DNamesMenu->GetSelectedItemId())
                            {
                                // Quit/Back
                                case CCreditScene::MENU_ITEM_ID_QUIT:
                                    this->GetSceneManager()->PopScene();
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
    CCreditScene::HandleLoad(const Egl::CScene &, Egl::CEventArgs &)
    {   
        // Now we can handle window events
        Egl::WindowPtr_t pWindow = this->GetWindow();
        pWindow->ContextMenuItemSelected += boost::bind(&CCreditScene::HandleContextMenuItemSelected, this, _1, _2);
        pWindow->Key += boost::bind(&CCreditScene::HandleKey, this, _1, _2);
        pWindow->Draw += boost::bind(&CCreditScene::HandleDraw, this, _1, _2);        

        // We want to make sure the right contex menu shows up for this scene
        pWindow->SetContextMenu(m_pContextMenu, Egl::MouseButton::RIGHT);
    }

    void
    CCreditScene::HandleUnload(const Egl::CScene &, Egl::CEventArgs &)
    {
        // We are not interested on events any longer
        Egl::WindowPtr_t pWindow = this->GetWindow();
        pWindow->Draw -= boost::bind(&CCreditScene::HandleDraw, this, _1, _2);        
        pWindow->Key -= boost::bind(&CCreditScene::HandleKey, this, _1, _2);
        pWindow->ContextMenuItemSelected -= boost::bind(&CCreditScene::HandleContextMenuItemSelected, this, _1, _2);        
    }
   
    void 
    CCreditScene::HandleContextMenuItemSelected(const Egl::CWindow &, Egl::CMenuItemEventArgs & rArgs)
    {
        // Make sure we only handle this event if
        // this scene is active
        if (this->IsActive())
        {
            // Switch on the ID of the item
            switch (rArgs.GetItemId())
            {
                // Toggle help
                case MENU_ITEM_ID_HELP:
                    //m_pHelpWindow->Show();
                break;

                // Quit menu item.
                case MENU_ITEM_ID_QUIT:
                    this->GetSceneManager()->PopScene();
                break;
            }
        } // if scene active
    }

    
} // namespace AmazingMaze