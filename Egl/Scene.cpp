#include "Precompiled.hpp"
#include "Egl/Scene.hpp"

namespace Egl
{
    CScene::CScene(const WindowPtr_t & pWindow) : m_pWindow(pWindow)
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
    }

    // virtual 
    void 
    CScene::OnUnload()
    {
        // Fire event
        CEventArgs args;
        this->Unload.Fire(*this, args);
    }
} // namespace Egl
