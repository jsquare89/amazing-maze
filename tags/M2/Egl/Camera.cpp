#include "Precompiled.hpp"
#include "Egl/Camera.hpp"
#include "Egl/Window.hpp"
#include <cmath>

namespace Egl
{
    namespace detail
    {
        // Conversion of degrees to radians
        inline float DegreesToRadians(const float nDegrees)
        {
            return nDegrees * 3.14159265358979323846f / 180.0f;
        }

    } // namespace detail

    // explicit
    CCamera::CCamera(const ContextPtr_t & pContext) : 
                     m_pEye(),
                     m_nXRotation(0),
                     m_nYRotation(0),
                     m_nZRotation(0),
                     m_pContext(pContext),
                     m_pLookAt(),
                     m_pWindow()

    {
        m_aUp[0] = 0;
        m_aUp[1] = 1;
        m_aUp[2] = 0;
    }

    CCamera::~CCamera(void) throw()
    {
    }

    // virtual 
    void 
    CCamera::SetUpVector(const float nX, 
                         const float nY, 
                         const float nZ)
    {
        m_aUp[0] = nX;
        m_aUp[1] = nY;
        m_aUp[2] = nZ;
        this->Refresh();
    }

    // virtual 
    void 
    CCamera::LookAt(const C3DPoint<float> & pLookAt)
    {
        // Set look at poinyt
        m_pLookAt = pLookAt;
        this->Refresh();
    }

    // virtual 
    void 
    CCamera::MoveTo(const float nX, 
                  const float nY, 
                  const float nZ)
    {
        // Set eye position
        m_pEye.Set(nX, nY, nZ);
        this->Refresh();
    }
    
    // virtual 
    void 
    CCamera::MoveTo(const C3DPoint<float> & pPosition)
    {
        // Forward call
        this->MoveTo(
            pPosition.GetX(), 
            pPosition.GetY(), 
            pPosition.GetZ());
    }
    
    // virtual 
    void 
    CCamera::MoveBy(const float nDeltaX, const float nDeltaY, const float nDeltaZ)
    {
        // Set origin
        this->MoveTo(
            m_pEye.GetX() + nDeltaX, 
            m_pEye.GetY() + nDeltaY, 
            m_pEye.GetZ() + nDeltaZ); 
    }

    // virtual 
    void 
    CCamera::RotateBy(const float nXDegrees, 
                    const float nYDegrees, 
                    const float nZDegrees)
    {
        // Calculate the distance between the eye and the center
        float nEyeToCenterDistance = m_pEye.DistanceTo(m_pLookAt);

        // Are we setting X rotation?
        if (nXDegrees > 0)
        {
            // Save rotation
            m_nXRotation += nXDegrees;
            if (m_nXRotation >= 360)
                m_nXRotation = m_nXRotation - 360;

            // TODO, calculate new eye vector
        }

        // Are we setting Y rotation?
        if (nYDegrees > 0)
        {
            // Save rotation
            m_nYRotation += nYDegrees;
            if (m_nYRotation >= 360)
                m_nYRotation = m_nYRotation - 360;

            // Change position of the eye while
            // keeping center and up
            m_pEye.SetX(nEyeToCenterDistance * std::sin(detail::DegreesToRadians(m_nYRotation)));
            m_pEye.SetZ(nEyeToCenterDistance * std::cos(detail::DegreesToRadians(m_nYRotation)));
        }

        // Are we setting Z rotation?
        if (nZDegrees > 0)
        {
            // Calculate Z rotation
            m_nZRotation += nZDegrees;
            if (m_nZRotation >= 360)
                m_nZRotation = m_nZRotation - 360;

            // TODO calculate the new position 
        }

        // Refresh the camera
        this->Refresh();
    }

    // virtual 
    void 
    CCamera::RotateTo(const float nXDegrees, const float nYDegrees, const float nZDegrees)
    {
        // Calculate the distance between the eye and the center
        float nEyeToCenterDistance = m_pEye.DistanceTo(m_pLookAt);

        // Adjust X rotation
        m_nXRotation = nXDegrees;
        
        // TODO, calculate new eye vector

        //Adjust Y rotation
        m_nYRotation = nYDegrees;
        m_pEye.SetX(nEyeToCenterDistance * std::sin(detail::DegreesToRadians(m_nYRotation)));
        m_pEye.SetZ(nEyeToCenterDistance * std::cos(detail::DegreesToRadians(m_nYRotation)));
        
        // Adjust 
        m_nZRotation = nZDegrees;

        // TODO, calculate new position
    }

    // virtual 
    void 
    CCamera::Refresh()
    {
        // Change the camera
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(m_pEye.GetX(), m_pEye.GetY(), m_pEye.GetZ(), 
		    m_pLookAt.GetX(), m_pLookAt.GetY(), m_pLookAt.GetZ(),
		    m_aUp[0], m_aUp[1], m_aUp[2]);

        // If we have a window to refresh do so
        if (m_pWindow)
            m_pWindow->Refresh();
    }

} // namespace Egl
