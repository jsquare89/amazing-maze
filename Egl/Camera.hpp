#pragma once

#include "Egl/Common.hpp"
#include "Egl/3DPoint.hpp"
#include "Egl/Positionable.hpp"
#include "Egl/Rotatable.hpp"

namespace Egl
{
    /** A camera. */
    class CCamera : public IPositionable,
                    public IRotatable
    {
    public:        
        
        /** Destructor. */
        ~CCamera(void) throw();
        
        /** 
         * Sets the window where this model is being displayed. 
         * Every time the model changes (e.g. somebody changes its
         * position or rotation of the model) it will ask this 
         * window to redraw itself.
         */
        virtual void SetWindow(const WindowPtr_t & pWindow)
        {
            m_pWindow = pWindow;
        }

        /** 
         * Retrieves the context that was used to create 
         * this camera.
         */
        const ContextPtr_t & GetContext() const { return m_pContext; }    

        /**
         * Moves the eye of the camera to a given position.
         *
         * @param nX X position of the eye of the camera.
         * @param nY Y position of the eye of the camera.
         * @param nZ Z position of the eye of the camera.
         */
        virtual void MoveTo(const float nX, const float nY, const float nZ);
        
        /**
         * Moves the eye of the camera to a given position.
         *
         * @param pPosition Position of the eye of the camera.
         */
        virtual void MoveTo(const C3DPoint<float> & pPosition);
        
        /**
         * Moves the eye of the camera by a given delta.
         */
        virtual void MoveBy(const float nDeltaX, const float nDeltaY, const float nDeltaZ);

        /**
         * Retrieves the position of the eye of the camera.
         *
         * @return The position of the eye of the camera.
         */
        virtual const C3DPoint<float> & GetPosition() const { return m_pEye; }

        /** 
         * Set the UP vector of the camera. The UP vector tells the
         * camera what direction is UP.
         */
        virtual void SetUpVector(const float nX, const float nY, const float nZ);

        /** 
         * Set the position the camera is looking at.
         *
         * @param pLookAt The position the camera is looking at.
         */
        virtual void LookAt(const C3DPoint<float> & pLookAt);

        // Inherited from IRotatable
        virtual void RotateBy(const float nXDegrees, const float nYDegrees, const float nZDegrees);
        virtual void RotateTo(const float nXDegrees, const float nYDegrees, const float nZDegrees);

        // Inherited from IRotatable
        virtual float GetXRotation() const { return m_nXRotation; }

        // Inherited from IRotatable
        virtual float GetYRotation() const { return m_nYRotation; }

        // Inherited from IRotatable
        virtual float GetZRotation() const { return m_nZRotation; }

    private:

        /** Creates a camera. */
        explicit CCamera(const ContextPtr_t & pContext);  

        // Avoid copy ctor and op=
        CCamera(const CCamera&);
        CCamera & operator=(const CCamera &);

        /** Refreshes the view of the camera. */
        virtual void Refresh();

    private:

        /** Eye position. */
        C3DPoint<float> m_pEye;

        /** Rotation on the X direction. */
        float m_nXRotation;

        /** Rotation on the Y direction. */
        float m_nYRotation;

        /** Rotation on the Z direction. */
        float m_nZRotation;

        /** Context. */
        ContextPtr_t m_pContext;

        /** Lookat position. */
        C3DPoint<float> m_pLookAt;

        /** Up vector. */
        float m_aUp[3];

        /** Window using this camera. */
        WindowPtr_t m_pWindow;

    private:

        /** CContext is our friend so it can create us. */
        friend class CContext;
    };

} // namespace Egl
