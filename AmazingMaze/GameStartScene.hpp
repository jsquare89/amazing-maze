#pragma once

#include <boost/shared_ptr.hpp>
#include "Egl/Common.hpp"
#include "Egl/Scene.hpp"

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
    
    /** Forward declaration of C3DMazeModel. */
    class C3DMazeModel;

    /** Main scene. */
    class CGameStartScene : public Egl::CScene
    {
    public:

        /** Constructor. */
        CGameStartScene(const Egl::WindowPtr_t & pWindow, 
                        const Egl::SceneManagerPtr_t & pSceneManager,                        
                        const Egl::ModelPtr_t & pMazeModel);

        /** Destructor. */
        virtual ~CGameStartScene(void) throw();
        
    private:

        /** Menu item IDs (for context menu). */
        enum MenuItemId
        {
            /** Quit. */
            MENU_ITEM_ID_QUIT
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
        
    private:

        /** Context menu. */
        Egl::MenuPtr_t m_pContextMenu; 

        /** Timer (for intro animation). */
        Egl::TimerPtr_t m_pTimer;

        /** Maze model. */
        Egl::ModelPtr_t m_pMazeModel;
    };
} // namespace Project2