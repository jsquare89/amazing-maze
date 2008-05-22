#include "Precompiled.hpp"
#include <boost/bind.hpp>
#include "MainWindow.hpp"	
#include <locale>
#include "Egl/Context.hpp"
#include "Egl/LightingControl.hpp"
#include "Egl/Light.hpp"
#include "Egl/Camera.hpp"
#include "Egl/SurfaceProperties.hpp"	
#include "Egl/Timer.hpp"
#include "Egl/ImageButton.hpp"
#include "Egl/SceneManager.hpp"

#include "MainScene.hpp"
#include "MazeMusic.hpp"
#include "MazeMusicLibrary.hpp"

namespace AmazingMaze
{
    CMainWindow::CMainWindow(void) : Egl::CWindow(),
                                     m_pCamera(),
                                     m_pMazeMusic(),
									 m_pBackgroundMusicLibrary(),
                                     m_pBackgroundMusicTimer(),
                                     m_pSceneManager(new Egl::CSceneManager())
    {
        // We are interested in listening to
        // some events                
        this->Create += boost::bind(&CMainWindow::HandleCreate, this, _1, _2);        
        this->Destroy += boost::bind(&CMainWindow::HandleDestroy, this, _1, _2);
    }

    CMainWindow::~CMainWindow(void)
    {
        m_pBackgroundMusicTimer->Stop();
        m_pBackgroundMusicLibrary->stopCurrentSong();        
    }
    
    void 
    CMainWindow::HandleKey(const Egl::CWindow &, Egl::CKeyEventArgs & rArgs)
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
                    // +, increase volume
                    case '+':
                        m_pBackgroundMusicLibrary->increaseVolume();
                    break;

                    // -, decrease volume
                    case '-':
                        m_pBackgroundMusicLibrary->decreaseVolume();
                    break;

                    // N, play next song
					case 'N':
						m_pBackgroundMusicLibrary->playNextSong();
                    break;

                    // P, play previous song
					case 'P':
                        m_pBackgroundMusicLibrary->playPrevSong();
                    break;
                }
            }            
        }
    }

    void
    CMainWindow::HandleCreate(const Egl::CWindow &, Egl::CEventArgs &)
    {
        // Set the camera
        m_pCamera = this->GetContext()->CreateCamera();
        m_pCamera->SetWindow(this->shared_from_this());

        // Set background color
        glClearColor(0.0, 0.0, 0.0, 0.0);        
        
		m_pBackgroundMusicLibrary.reset(new CMazeMusicLibrary(L"sounds\\*.mp3"));
		m_pBackgroundMusicTimer = this->GetContext()->CreateTimer();
		m_pBackgroundMusicTimer->Tick += boost::bind(&CMazeMusicLibrary::playLibrary,m_pBackgroundMusicLibrary);
		m_pBackgroundMusicTimer->StartInterval(1000);

        // Push start scene
        m_pSceneManager->PushScene(Egl::ScenePtr_t(
            new CMainScene(this->shared_from_this(), m_pSceneManager, 
                m_pCamera)));        

        // Show ourselves in full screen.
        this->SetFullScreen();
        this->Show();

        // We want to listen for key events
        this->Key += boost::bind(&CMainWindow::HandleKey, this, _1, _2);
    }

    void
    CMainWindow::HandleDestroy(const Egl::CWindow &, Egl::CEventArgs &)
    {
        // Post quit message to message loop
        this->GetContext()->BreakMainLoop();
    }

} // namespace AmazingMaze