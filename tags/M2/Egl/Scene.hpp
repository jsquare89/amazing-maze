#pragma once

#include "Egl/Common.hpp"
#include "Egl/Event.hpp"
#include <boost/weak_ptr.hpp>

namespace Egl
{
    /** 
     * Base class for all scenes that can be stringed together and managed
     * via the SceneManager.
     */
    class CScene
    {
    public:

        /** Type of scene load event. */
        typedef CEvent<CScene, CScene, CEventArgs, 0> LoadEvent_t;

        /** Type of scene unload event. */
        typedef CEvent<CScene, CScene, CEventArgs, 1> UnloadEvent_t;

    public:        
        
        /** Destructor. */
        virtual ~CScene(void) throw() = 0;

        /**
         * Retrieves whether this scene is active. 
         */
        bool IsActive() const { return m_bActive; }

    public:

        /** 
         * Event fired when the scene loads.
         */
        LoadEvent_t Load;

        /** 
         * Event fired when the scene unloads.
         */
        UnloadEvent_t Unload;
        
    protected:

        /** Constructor. */
        CScene(const WindowPtr_t & pWindow, const SceneManagerPtr_t & pSceneManager);

        /** Gets the window showing this scene. */
        const WindowPtr_t GetWindow() const { return m_pWindow.lock(); }

        /** Gets the scene manager managing this scene. */
        const SceneManagerPtr_t GetSceneManager() const { return m_pSceneManager.lock(); } 

    private:

        /** 
         * Fire the load load event. 
         */
        void OnLoad();

        /** 
         * Fire the unload event. 
         */
        void OnUnload();

        // Avoid copy ctor and op=
        CScene(const CScene&);
        CScene & operator=(const CScene &);    

    private:

        /** Window where this scene is displayed. */
        boost::weak_ptr<CWindow> m_pWindow;

        /** Scene manager. */
        boost::weak_ptr<CSceneManager> m_pSceneManager;

    private:

        /** Scene manager is our friend so it can call load and unload. */
        friend class CSceneManager;

        /** Active. */
        volatile bool m_bActive;
    };

} // namespace Egl
