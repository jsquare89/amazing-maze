#pragma once

#include <boost/shared_ptr.hpp>
#include "Egl/Common.hpp"
#include "Egl/Window.hpp"
#include <vector>

namespace AmazingMaze
{
    /** Forward declaration of CMazeMusic. */
    class CMazeMusic;

    /** Forward declaration of CMazeMusicLibrary. */
    class CMazeMusicLibrary;

    /** Forward declaration of CSceneManager. */
    class CSceneManager;

    /** Main window for the project. */
    class CMainWindow : public Egl::CWindow
    {
    public:

        /** Constructor. */
        CMainWindow(void);

        /** Destructor. */
        virtual ~CMainWindow(void) throw();
        
    private:

        /** Handle Create event. */
        void HandleCreate(const Egl::CWindow &, Egl::CEventArgs & rArgs);

        /** Handle Destroy event. */
        void HandleDestroy(const Egl::CWindow &, Egl::CEventArgs & rArgs);

        /** Handle Key event. */
        void HandleKey(const Egl::CWindow &, Egl::CKeyEventArgs & rArgs);
        
    private:

        /** The camera. */
        Egl::CameraPtr_t m_pCamera;

        boost::shared_ptr<CMazeMusic>			m_pMazeMusic;
        boost::shared_ptr<CMazeMusicLibrary>	m_pBackgroundMusicLibrary;
        Egl::TimerPtr_t  m_pBackgroundMusicTimer;

        /** Scene manager. */
        Egl::SceneManagerPtr_t m_pSceneManager;
		
    };
} // namespace Project2