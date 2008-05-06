#pragma once

#include "Egl/Common.hpp"
#include "Egl/Event.hpp"

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
        explicit CScene(const WindowPtr_t & pWindow);

        /** 
         * Fire the load load event. 
         */
        virtual void OnLoad();

        /** 
         * Fire the unload event. 
         */
        virtual void OnUnload();

    private:

        // Avoid copy ctor and op=
        CScene(const CScene&);
        CScene & operator=(const CScene &);    

    private:

        /** Window where this scene is displayed. */
        WindowPtr_t m_pWindow;
    };

} // namespace Egl
