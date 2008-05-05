#pragma once

#include "Egl/3DPoint.hpp"

namespace Egl
{

    /** Interface for all objects that may be rotated in 3D space. */
    class IRotatable
    {
    public:

        /** 
         * Destructor. 
         */
        virtual ~IRotatable(void) throw() = 0 {}

        /**
         * Rotate this object to a specific angle in the X, Y and Z axis.
         *
         * @param nXDegrees X axis degrees to rotate to
         *                  (positive = CCW, negative = CW).
         * @param nYDegrees Y axis degrees to rotate to
         *                  (positive = CCW, negative = CW).
         * @param nZDegrees Z axis degrees to rotate to
         *                  (positive = CCW, negative = CW).
         */
        virtual void RotateTo(const float nXDegrees, const float nYDegrees, const float nZDegrees) = 0;

        /**
         * Rotate this object around the X, Y and Z axis.
         *
         * @param nXDegrees Degrees to rotate around the X
         *                  axis (positive = CCW, negative = CW).
         * @param nYDegrees Degrees to rotate around the Y
         *                  axis (positive = CCW, negative = CW).
         * @param nZDegrees Degrees to rotate around the Z
         *                  axis (positive = CCW, negative = CW).
         */
        virtual void RotateBy(const float nXDegrees, const float nYDegrees, const float nZDegrees) = 0;

        /**
         * Retrieves this object's rotation around the X axis
         * (with respect to its original orientation.)
         *
         * @return This object's rotation around the X axis.
         */
        virtual float GetXRotation() const = 0;

        /**
         * Retrieves this object's rotation around the Y axis
         * (with respect to its original orientation.)
         *
         * @return This object's rotation around the Y axis.
         */
        virtual float GetYRotation() const = 0;

        /**
         * Retrieves this object's rotation around the Z axis
         * (with respect to its original orientation.)
         *
         * @return This object's rotation around the Z axis.
         */
        virtual float GetZRotation() const = 0;

    protected:

        /** 
         * Constructor. 
         */
        IRotatable(void) {}
    };

} // namespace Egl