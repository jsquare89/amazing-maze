#include "Precompiled.hpp"
#include "Egl/SceneManager.hpp"
#include "Egl/Scene.hpp"
#include <boost/bind.hpp>

namespace Egl
{
    CSceneManager::CSceneManager() : m_sScenes()
    {
        
    }

    CSceneManager::~CSceneManager(void) throw()
    {
    }

    CSceneManager & 
    CSceneManager::PushScene(const ScenePtr_t & pScene)
    {
        // If we have a current scene then unload it. 
        if (!m_sScenes.empty())
            m_sScenes.top()->OnUnload();

        // Push scene
        m_sScenes.push(pScene);

        // Load the new top scene
        m_sScenes.top()->OnLoad();

        return *this;
    }

    CSceneManager & 
    CSceneManager::PopScene(const std::size_t nCount /* = 1 */)
    {
        // If we have a current scene then unload it. 
        if (!m_sScenes.empty())
            m_sScenes.top()->OnUnload();

        // Pop scenes
        for (std::size_t i = 0; i < nCount; ++i)
        {
            // Pop it
            m_sScenes.pop();
        }

        // If we have a current scene then load it. 
        if (!m_sScenes.empty())
            m_sScenes.top()->OnLoad();

        return *this;
    }

} // namespace Egl
