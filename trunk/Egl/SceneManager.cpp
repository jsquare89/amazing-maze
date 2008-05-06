#include "Precompiled.hpp"
#include "Egl/SceneManager.hpp"
#include "Egl/Scene.hpp"
#include <boost/bind.hpp>

namespace Egl
{
    // explicit 
    CSceneManager::CSceneManager(const ScenePtr_t & pScene) : m_sScenes()
    {
        m_sScenes.push(pScene);
    }

    CSceneManager::~CSceneManager(void) throw()
    {
    }

    CSceneManager & 
    CSceneManager::PushScene(const ScenePtr_t & pScene)
    {
        // Push scene
        m_sScenes.push(pScene);
        return *this;
    }

    CSceneManager & 
    CSceneManager::PopScene(const std::size_t nCount /* = 1 */)
    {
        // Pop scenes
        for (std::size_t i = 0; i < nCount; ++i)
        {
            m_sScenes.pop();
        }

        return *this;
    }

} // namespace Egl
