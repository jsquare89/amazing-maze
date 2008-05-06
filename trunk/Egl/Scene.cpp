#include "Precompiled.hpp"
#include "Egl/Scene.hpp"

namespace Egl
{
    CScene::CScene(const WindowPtr_t & pWindow,
                   const SceneManagerPtr_t & pSceneManager) : 
                   m_pWindow(pWindow),
                   m_pSceneManager(pSceneManager),
                   m_bActive(false)
    {
    }

    // virtual 
    CScene::~CScene(void) throw()
    {        
    }

    // virtual 
    void 
    CScene::OnLoad()
    {        
        // Fire event
        CEventArgs args;
        this->Load.Fire(*this, args);

        // We are now active
        m_bActive = true;
    }

    // virtual 
    void 
    CScene::OnUnload()
    {
        // Fire event
        CEventArgs args;
        this->Unload.Fire(*this, args);

        // We are unactive
        m_bActive = false;        
    }
} // namespace Egl
