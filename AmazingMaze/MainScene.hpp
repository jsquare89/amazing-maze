#pragma once

#include <boost/shared_ptr.hpp>
#include "Egl/Common.hpp"
#include "TextScene.hpp"

namespace AmazingMaze
{
    /** Forward declaration of C3DMenu. */
    class C3DMenu;

    /** Main scene. */
    class CMainScene : public CTextScene
    {
    public:

        /** Constructor. */
        CMainScene(const Egl::WindowPtr_t & pWindow, 
                   const Egl::SceneManagerPtr_t & pSceneManager, 
                   const Egl::CameraPtr_t & pCamera);

        /** Destructor. */
        virtual ~CMainScene(void) throw();

    private:

        /** Menu item IDs (for 3D menu and context menu). */
        enum MenuItemId
        {
            /** Quit. */
            MENU_ITEM_ID_QUIT,

            /** Start. */
            MENU_ITEM_ID_START,

            /** Instructions. */
            MENU_ITEM_ID_INSTRUCTIONS,

            /** Credits. */
            MENU_ITEM_ID_CREDITS,

            /** Toggle help menu item. */
            MENU_ITEM_ID_HELP,
        };

    private:

        /** Handles scene load. */
        void HandleLoad(const Egl::CScene &, Egl::CEventArgs &);

        /** Handles scene unload. */
        void HandleUnload(const Egl::CScene &, Egl::CEventArgs &);

        /** Handles Draw event. */
        void HandleDraw(const Egl::CWindow &, Egl::CEventArgs & rArgs);

        /** Handle Key event. */
        void HandleKey(const Egl::CWindow &, Egl::CKeyEventArgs & rArgs);

        /** Called when an item is selected on the context menu. */
        void HandleContextMenuItemSelected(const Egl::CWindow &, Egl::CMenuItemEventArgs & rArgs);

        /** Show credits scene. */
        void ShowCreditScene();

        /** Show demo scene. */
        void ShowDemoScene();

    private:

        /** Background. */
        Egl::ImagePtr_t m_pBackgroundImage; 

        /** Title. */
        Egl::ImagePtr_t m_pTitleImage; 

        /** Model for main menu (3D menu). */
        boost::shared_ptr<C3DMenu> m_p3DMenu;

        /** Context menu. */
        Egl::MenuPtr_t m_pContextMenu;        
    };
} // namespace Project2