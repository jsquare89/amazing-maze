#pragma once

#include <boost/shared_ptr.hpp>
#include "Egl/Common.hpp"
#include "Egl/Scene.hpp"
#include "MazeWalker.hpp"

namespace AmazingMaze
{
    /** Forward declaration of CMaze. */
    class CMaze;

    /** Type of CMaze shared pointer. */
    typedef boost::shared_ptr<CMaze> MazePtr_t;

    /** Forward declaration of CMazeServer. */
    class CMazeServer;

    /** Type of CMazeServer shared pointer. */
    typedef boost::shared_ptr<CMazeServer> MazeServerPtr_t;
    
    /** Forward declaration of CMazeMusic */
    class CMazeMusic;

    /** Forward declaration of C3DMazeModel. */
    class C3DMazeModel;

    /** Main scene. */
    class CDemoScene : public Egl::CScene
    {
    public:

        /** Constructor. */
        CDemoScene(const Egl::WindowPtr_t & pWindow, 
                   const Egl::SceneManagerPtr_t & pSceneManager, 
                   const Egl::CameraPtr_t & pCamera,
                   const MazeServerPtr_t & pMazeServer,
                   const MazePtr_t & pMaze);

        /** Destructor. */
        virtual ~CDemoScene(void) throw();
        
    private:

        /** Menu item IDs (for 3D menu and context menu). */
        enum MenuItemId
        {
            /** Quit. */
            MENU_ITEM_ID_QUIT,

            /** Instructions. */
            MENU_ITEM_ID_INSTRUCTIONS,

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

        /** Handles Reshape event. */
        void HandleReshape(const Egl::CWindow &, Egl::CWindowReshapeEventArgs & rArgs);

        /** Handles walker timer ticks. */
        void HandleTimerTick(const Egl::CTimer &, Egl::CEventArgs &);

        /** Updates the projection matrix. */
        void UpdateProjectionMatrix(const int nWidth, const int nHeight);

        /** Updates the projection matrix. */
        void UpdateProjectionMatrix();

        /** Updates the viewport. */
        void UpdateViewport(const int nWidth, const int nHeight);

        /** Refreshes this scene. */
        void Refresh();

        /** Updates all the walker parameters given its new position and direction. */
        void UpdateWalker(const CMazeWalker::Direction_e eDirection, const int nRow, const int nColumn);

    private:

        /** Camera. */
        Egl::CameraPtr_t m_pCamera;

        /** Context menu. */
        Egl::MenuPtr_t m_pContextMenu; 

        /** Field of view. */
        double m_nFieldOfView;

        /** Lights. */
        std::vector<Egl::LightPtr_t> m_vLights;

        /** Walker timer. */
        Egl::TimerPtr_t m_pWalkerTimer;

        /** Array of movements for demo. */
        std::vector<char> m_vWalkerSteps;

        /** Iterator pointing to the current step. */
        std::vector<char>::const_iterator m_citWalkerStep;

        /** Single sound for cheers. */
        boost::shared_ptr<CMazeMusic> m_pCheersMusic;

        /** Maze server. */
        MazeServerPtr_t m_pMazeServer;

        /** Maze. */
        MazePtr_t m_pMaze;

        /** Maze model. */
        boost::shared_ptr<C3DMazeModel> m_pMazeModel;

        /** Maze walker. */
        boost::shared_ptr<CMazeWalker> m_pMazeWalker;
    };
} // namespace Project2