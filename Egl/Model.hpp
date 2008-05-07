#pragma once

#include "Egl/Common.hpp"
#include "Egl/3DPoint.hpp"
#include "Egl/Positionable.hpp"
#include "Egl/Scalable.hpp"
#include "Egl/Rotatable.hpp"

namespace Egl
{

    /** Parent class for all models. */
    class CModel : public IPositionable,
                   public IScalable,
                   public IRotatable
    {
    public:

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
         * Retrieves the width of this model.
         *
         * @return The width of this model.
         */
        virtual const float GetWidth() const = 0;

        /** 
         * Retrieves the height of this model.
         *
         * @return The height of this model.
         */
        virtual const float GetHeight() const = 0;

        /** 
         * Retrieves the depth of this model.
         *
         * @return The depth of this model.
         */
        virtual const float GetDepth() const = 0;

        // Inherited from IPositionable
        virtual void MoveTo(const float nX, const float nY, const float nZ);
        virtual void MoveTo(const C3DPoint<float> & pPosition);
        virtual void MoveBy(const float nDeltaX, const float nDeltaY, const float nDeltaZ);

        // Inherited from IPositionable
        virtual const C3DPoint<float> & GetPosition() const
        {
            return m_pOrigin; 
        }

        // Inherited from IScalable
        virtual void ScaleBy(const float nXScale, const float nYScale, const float nZScale);

        // Inherited from IScalable
        virtual const float GetXScale() const
        { 
            return m_nXScale; 
        }

        // Inherited from IScalable
        virtual const float GetYScale() const
        { 
            return m_nYScale; 
        }

        // Inherited from IScalable
        virtual const float GetZScale() const
        { 
            return m_nZScale; 
        }
        
        // Inherited from IScalable
        virtual void RotateBy(const float nXDegrees, const float nYDegrees, const float nZDegrees);
        virtual void RotateTo(const float nXDegrees, const float nYDegrees, const float nZDegrees);

        // Inherited from IScalable
        virtual float GetXRotation() const
        {
            // Get X rotation
            return m_nXRotation;
        }

        // Inherited from IScalable
        virtual float GetYRotation() const
        {
            // Get Y rotation
            return m_nYRotation;
        }

        // Inherited from IScalable
        virtual float GetZRotation() const
        {
            // Get Z rotation
            return m_nZRotation;
        }

        /** 
         * Draws this model at the current location.
         */
        virtual void Draw(void) = 0;

        /** Destructor. */
        virtual ~CModel(void) throw();

    protected:

        /** 
         * Constructor. 
         *
         * The model origin is set to 0,0,0 and
         * the scaling factor is set to 1.0 (no scaling)
         * on every axis.
         */
        CModel(void) : m_pOrigin(), m_nXScale(1), 
                       m_nYScale(1), m_nZScale(1),
                       m_nXRotation(0), m_nYRotation(0),
                       m_nZRotation(0)
        {
        }

        /** 
         * Constructor. 
         *
         * The scaling factor is set to 1.0 (no scaling)
         * on every axis.
         */
        CModel(const float nX, const float nY, const float nZ) : 
               m_pOrigin(nX, nY, nZ), 
               m_nXScale(1), 
               m_nYScale(1), 
               m_nZScale(1),
               m_nXRotation(0), 
               m_nYRotation(0),
               m_nZRotation(0)
        {
        }

        /** Asks the window showing this model to refresh itself. */
        void RefreshWindow();

    private:

        /** Current origin. */
        C3DPoint<float> m_pOrigin;

        /** Scale on the X direction. */
        float m_nXScale;

        /** Scale on the Y direction. */
        float m_nYScale;

        /** Scale on the Z direction. */
        float m_nZScale;

        /** Rotation on the X direction. */
        float m_nXRotation;

        /** Rotation on the Y direction. */
        float m_nYRotation;

        /** Rotation on the Z direction. */
        float m_nZRotation;

        /** Window this model is rendered in. */
        WindowPtr_t m_pWindow;
    };

} // namespace Egl