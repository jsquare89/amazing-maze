#pragma once

#include "Egl/3DPoint.hpp"

namespace Egl
{

    /** Interface for every 3D object that can be scaled. */
    class IScalable
    {
    public:

        /** 
         * Destructor. 
         */
        virtual ~IScalable(void) throw() = 0 {}

        /** 
         * Scales this object by a given amount in the
         * X, Y and Z dimensions.
         *
         * @param nXScale Amount to scale the X axis.
         * @param nYScale Amount to scale the Y axis.
         * @param bZScale Amoung to scale the Z axis.
         */
        virtual void ScaleBy(const float nXScale, const float nYScale, const float nZScale) = 0;

        /** 
         * Retrieves the X direction scaling factor this object uses.
         * 
         * @return The X direction scaling factor.
         */
        virtual const float GetXScale() const = 0;

        /** 
         * Retrieves the Y direction scaling factor this object uses.
         * 
         * @return The Y direction scaling factor.
         */
        virtual const float GetYScale() const = 0;

        /** 
         * Retrieves the Z direction scaling factor this object uses.
         * 
         * @return The Z direction scaling factor.
         */
        virtual const float GetZScale() const = 0;

    protected:

        /** 
         * Constructor. 
         */
        IScalable(void) {}
    };

} // namespace Egl