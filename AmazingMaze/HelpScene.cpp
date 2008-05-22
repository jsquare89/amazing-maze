#include "Precompiled.hpp"
#include <boost/bind.hpp>
#include "HelpScene.hpp"	
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
    CHelpScene::CHelpScene(const Egl::WindowPtr_t & pWindow, 
                           const Egl::SceneManagerPtr_t & pSceneManager, 
                           const Egl::CameraPtr_t & pCamera) : 
                           CTextScene(pWindow, pSceneManager, pCamera),
                           m_pBackgroundImage(),
                           m_pTitleImage(),
                           m_p3DHelpMenu(new C3DMenu()),
                           m_pContextMenu()
    {
        // We want to listen to load an unload events fired by us
        this->Load += boost::bind(&CHelpScene::HandleLoad, this, _1, _2);
        this->Unload += boost::bind(&CHelpScene::HandleUnload, this, _1, _2);

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

		m_pHelpImage.reset(new Egl::CImage(-10.f, -2.1f, 0,
            20.0f, 5.0f, pWindow->GetContext()->LoadTexture("textures/commands.png")));
        m_pHelpImage->SetWindow(pWindow);

        // Set up menu
        
		// Add back item which can be selected
        m_p3DHelpMenu->AddItem(CHelpScene::MENU_ITEM_ID_BACK,
            6.0f, 2.0f, pWindow->GetContext()->LoadTexture("textures/back0.png"))
            .SetStateImage(C3DMenuItem::SelectedState, 
                pWindow->GetContext()->LoadTexture("textures/back1.png"))
            .SetMargins(16.0f, 6.4f);
    
        // Select back
        m_p3DHelpMenu->SelectItem(CHelpScene::MENU_ITEM_ID_BACK);

        // Move the whole menu into position
        m_p3DHelpMenu->MoveTo(-10.0f, 1.5f, 0);
        m_p3DHelpMenu->SetWindow(pWindow);

        // Create context menu
        m_pContextMenu = pWindow->GetContext()->CreateMenu();
        m_pContextMenu->AddItem("Back to main screen", CHelpScene::MENU_ITEM_ID_BACK, false);
    }

    CHelpScene::~CHelpScene(void)
    {
    }

    void
    CHelpScene::HandleDraw(const Egl::CWindow &, Egl::CEventArgs &)
    {
        // Clear the background
        glMatrixMode(GL_MODELVIEW);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                            
        // Draw background
        m_pBackgroundImage->Draw();
        
        // Draw title
        m_pTitleImage->Draw();
        
        // Draw menus
		m_pHelpImage->Draw();
        m_p3DHelpMenu->Draw();

        // Flush all actions
        glFlush();

        // Repaint screen with content of back buffer
        this->GetWindow()->SwapBuffers();
    }

    void 
    CHelpScene::HandleKey(const Egl::CWindow &, Egl::CKeyEventArgs & rArgs)
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
                        // Back key
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
                        // Enter
                        case 30:
                        {
                            // Get currently selected menu item id
                            switch (m_p3DHelpMenu->GetSelectedItemId())
                            {
                                // Back
                                case CHelpScene::MENU_ITEM_ID_BACK:
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
    CHelpScene::HandleLoad(const Egl::CScene &, Egl::CEventArgs &)
    {   
        // Now we can handle window events
        Egl::WindowPtr_t pWindow = this->GetWindow();
        pWindow->ContextMenuItemSelected += boost::bind(&CHelpScene::HandleContextMenuItemSelected, this, _1, _2);
        pWindow->Key += boost::bind(&CHelpScene::HandleKey, this, _1, _2);
        pWindow->Draw += boost::bind(&CHelpScene::HandleDraw, this, _1, _2);        

        // We want to make sure the right contex menu shows up for this scene
        pWindow->SetContextMenu(m_pContextMenu, Egl::MouseButton::RIGHT);
    }

    void
    CHelpScene::HandleUnload(const Egl::CScene &, Egl::CEventArgs &)
    {
        // We are not interested on events any longer
        Egl::WindowPtr_t pWindow = this->GetWindow();
        pWindow->Draw -= boost::bind(&CHelpScene::HandleDraw, this, _1, _2);        
        pWindow->Key -= boost::bind(&CHelpScene::HandleKey, this, _1, _2);
        pWindow->ContextMenuItemSelected -= boost::bind(&CHelpScene::HandleContextMenuItemSelected, this, _1, _2);        
    }
   
    void 
    CHelpScene::HandleContextMenuItemSelected(const Egl::CWindow &, Egl::CMenuItemEventArgs & rArgs)
    {
        // Make sure we only handle this event if
        // this scene is active
        if (this->IsActive())
        {
            // Switch on the ID of the item
            switch (rArgs.GetItemId())
            {
                // Back menu item.
                case MENU_ITEM_ID_BACK:
                    this->GetSceneManager()->PopScene();
                break;
            }
        } // if scene active
    }

    
} // namespace AmazingMaze