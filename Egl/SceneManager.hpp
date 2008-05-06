#pragma once

#include "Egl/Common.hpp"
#include <stack>

namespace Egl
{
    /** 
     * Manages scenes by keeping a stack of scenes. The current
     * scene can ask the scene manager to push another scene
     * onto the stack, pop the current scene from the stack
     * (go back to the previous scene) and clear the stack.
     */
    class CSceneManager
    {
    public:        
        
        /** Constructor. */
        CSceneManager();

        /** Destructor. */
        ~CSceneManager(void) throw();
                
        /** Pushes a scene onto the stack. */
        CSceneManager & PushScene(const ScenePtr_t & pScene);

        /** Pops N scenes from the stack. */
        CSceneManager & PopScene(const std::size_t nCount = 1);

        /** Retrieves the current scene. */
        const ScenePtr_t & GetCurrentScene() const { return m_sScenes.top(); }

    private:

        // Avoid copy ctor and op=
        CSceneManager(const CSceneManager &);
        CSceneManager & operator=(const CSceneManager &);

    private:

        /** Scene stack. */
        std::stack<ScenePtr_t> m_sScenes;
    };

} // namespace Egl
