#pragma once

#include <boost/shared_ptr.hpp>
#include "Egl/Common.hpp"
#include "Egl/Window.hpp"
#include <vector>

namespace AmazingMaze
{
    /** Forward declaration of C3DMenu. */
    class C3DMenu;

    class CMazeMusic;

    /** Main window for the project. */
    class CMainWindow : public Egl::CWindow
    {
    public:

        /** Constructor. */
        CMainWindow(void);

        /** Destructor. */
        virtual ~CMainWindow(void) throw();

    private:

        /** Menu item IDs. */
        enum MenuItemId
        {
            /** Quit. */
            MENU_ITEM_ID_QUIT,

            /** Start. */
            MENU_ITEM_ID_START,

            /** Instructions. */
            MENU_ITEM_ID_INSTRUCTIONS,

            /** Credits. */
            MENU_ITEM_ID_CREDITS
        };

        /** Enum of context menu item ids. */
        enum ContextMenuItemId_e
        {
            /** Toggle help menu item. */
            TOGGLE_HELP_MENU_ITEM_ID,

            /** Quit menu item. */
            QUIT_MENU_ITEM_ID,

            /** Toggle credits. */
            TOGGLE_CREDITS_MENU_ITEM_ID
        };

    private:

        /** Handles OnDraw event. */
        void HandleOnDraw(void);

        /** Handles OnReshape event. */
        void HandleOnReshape(int nWidth, int nHeight);

        /** Handle OnCreate event. */
        void HandleOnCreate(void);

        /** Handle OnDestroy event. */
        void HandleOnDestroy(void);

        /** Handle OnKey event. */
        void HandleOnKey(int nKeyCode, bool bIsSystemKey, Egl::KeyState_e eKeyState, int nCursorX, int nCursorY);

        /** Called when an item is selected on the context menu. */
        void HandleOnContextMenuItemSelected(int nMenuItemId);

        /** Close midi file. */
        void CloseMidi();

        /** Open midi file. */
        void OpenMidi(const std::string & strFilePath);

        /** Play midi file. */
        void PlayMidi();

    private:

        /** Lights. */
        std::vector<Egl::LightPtr_t> m_vLights;

        /** The camera. */
        Egl::CameraPtr_t m_pCamera;

        /** Background texture. */
        Egl::TexturePtr_t m_pBackgroundTexture;

        /** Title. */
        Egl::ImagePtr_t m_pTitleImage; 

        /** Model for main menu. */
        boost::shared_ptr<C3DMenu> m_pMainMenu;

        /** Model for credits menu. */
        boost::shared_ptr<C3DMenu> m_pCreditsMenu;

        /** Whether we are showing the main menu. */
        bool m_bInMainMenu;

        boost::shared_ptr<CMazeMusic> m_pMazeMusic;

        /** Context menu. */
        Egl::MenuPtr_t m_pContextMenu;

        /** Help window */
        Egl::WindowPtr_t m_pHelpWindow;
    };
} // namespace Project2