#include "Precompiled.hpp"
#include <boost/bind.hpp>
#include "TextScene.hpp"	
#include <locale>
#include "Egl/Window.hpp"
#include "Egl/Context.hpp"
#include "Egl/LightingControl.hpp"
#include "Egl/Light.hpp"
#include "Egl/Camera.hpp"
#include "Egl/WindowReshapeEventArgs.hpp"

namespace AmazingMaze
{
    CTextScene::CTextScene(const Egl::WindowPtr_t & pWindow, 
                           const Egl::SceneManagerPtr_t & pSceneManager,
                           const Egl::CameraPtr_t & pCamera) : 
                           Egl::CScene(pWindow, pSceneManager),
                           m_vLights(),
                           m_pCamera(pCamera)                           
    {
        // We want to listen to load an unload events fired by us
        this->Load += boost::bind(&CTextScene::HandleLoad, this, _1, _2);
        this->Unload += boost::bind(&CTextScene::HandleUnload, this, _1, _2);
    }

    CTextScene::~CTextScene(void)
    {
    }

    void 
    CTextScene::UpdateProjectionMatrix(const int nWidth, const int nHeight)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();	
        gluPerspective(
            30.0, // field of view in degrees
            static_cast<GLdouble>(nWidth) / nHeight, // aspect ratio
            1.0, // Z near 
            100.0 // Z far
        );
    }

    void 
    CTextScene::UpdateViewport(const int nWidth, const int nHeight)
    {
        // Set new viewport        
        glViewport(0, 0, nWidth, nHeight);        
    }

    void 
    CTextScene::HandleReshape(const Egl::CWindow &, Egl::CWindowReshapeEventArgs & rArgs)
    {
        // Make sure we only handle this event if
        // this scene is active
        if (this->IsActive())
        {
            // Update projection matrix.
            this->UpdateProjectionMatrix(rArgs.GetWidth(), rArgs.GetHeight());

            // update viewport
            this->UpdateViewport(rArgs.GetWidth(), rArgs.GetHeight());        
        }
    }
    
    // virtual
    void
    CTextScene::HandleLoad(const Egl::CScene &, Egl::CEventArgs &)
    {
        // Update projection and viewport
        Egl::WindowPtr_t pWindow = this->GetWindow();
        this->UpdateProjectionMatrix(pWindow->GetWidth(), pWindow->GetHeight());
        this->UpdateViewport(pWindow->GetWidth(), pWindow->GetHeight());
        
        // Enable texture
        glEnable(GL_TEXTURE_2D);
        glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);				// Sky blue Background
	    glClearDepth(1.0f);									// Depth Buffer Setup
	    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

        // Setup lights
        Egl::LightPtr_t pLight = Egl::CLightingControl::CreateLight<Egl::DIRECTIONAL_LIGHT>();
        pLight->MoveTo(1.0f, 1.0f, 1.0f);
        pLight->SetDifuseColor(1.0f, 0, 0, 0);
        pLight->SetAmbientColor(0.5f, 0.5f, 0.5f, 1.0f);
        pLight->Enable();
        m_vLights.push_back(pLight);
        
        pLight = Egl::CLightingControl::CreateLight<Egl::DIRECTIONAL_LIGHT>();
        pLight->MoveTo(-1.0f, -1.0f, 1.0f);
        pLight->SetDifuseColor(0, 1.0f, 0, 0);
        pLight->Enable();
        m_vLights.push_back(pLight);

        pLight = Egl::CLightingControl::CreateLight<Egl::DIRECTIONAL_LIGHT>();
        pLight->MoveTo(1.0f, -1.0f, 1.0f);
        pLight->SetDifuseColor(0, 0, 1.0f, 0);
        pLight->Enable();
        m_vLights.push_back(pLight);

        Egl::CLightingControl::EnableLighting();        

        // Set the camera
        m_pCamera->MoveTo(0.0, 0.0, 30.0); // eye is at (0,0,30)
        m_pCamera->LookAt(Egl::C3DPoint<float>(0.0, 0.0, 0.0)); // center is at (0,0,0)
        m_pCamera->SetUpVector(0.0, 1.0, 0.0);	// up is in positive Y direction 

        // Set background color
        glClearColor(0.0, 0.0, 0.0, 0.0);        

        //Enable alpha-blending
        glEnable(GL_ALPHA_TEST); 
        glAlphaFunc(GL_GREATER, 0.6f);
        //glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        // We are interested in listening to some events                
        pWindow->Reshape += boost::bind(&CTextScene::HandleReshape, this, _1, _2);
    }

    // virtual
    void
    CTextScene::HandleUnload(const Egl::CScene &, Egl::CEventArgs &)
    {
        // We are not interested in listening to the window events anymore
        this->GetWindow()->Reshape -= boost::bind(&CTextScene::HandleReshape, this, _1, _2);
    }
    
} // namespace AmazingMaze