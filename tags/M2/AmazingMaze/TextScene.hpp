#pragma once

#include "Egl/Common.hpp"
#include "Egl/Scene.hpp"
#include <vector>

namespace AmazingMaze
{
    /** 
     * Base class for all project scenes that show text, 
     * hence they have the same lights, perspective, etc. 
     * This may not be the case with the game scenes.
     */
    class CTextScene : public Egl::CScene
    {
    public:

        /** Constructor. */
        CTextScene(const Egl::WindowPtr_t & pWindow, 
                   const Egl::SceneManagerPtr_t & pSceneManager, 
                   const Egl::CameraPtr_t & pCamera);

        /** Destructor. */
        virtual ~CTextScene(void) throw() = 0;
        
    protected:

        /** Retrieves the camera used by text scenes. */
        const Egl::CameraPtr_t & GetCamera() const { return m_pCamera; }

    private:

        /** Handles Reshape event. */
        void HandleReshape(const Egl::CWindow &, Egl::CWindowReshapeEventArgs & rArgs);

        /** Handles scene load. */
        void HandleLoad(const Egl::CScene &, Egl::CEventArgs &);

        /** Handles scene unload. */
        void HandleUnload(const Egl::CScene &, Egl::CEventArgs &);

        /** Updates the projection matrix. */
        void UpdateProjectionMatrix(const int nWidth, const int nHeight);

        /** Updates the viewport. */
        void UpdateViewport(const int nWidth, const int nHeight);

    private:

        /** Lights. */
        std::vector<Egl::LightPtr_t> m_vLights;

        /** The camera. */
        Egl::CameraPtr_t m_pCamera;
    };
} // namespace Project2