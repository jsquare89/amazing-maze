#pragma once

#include "Egl/3DPoint.hpp"

namespace Egl
{

    /** Interface for all objects whose 3D position may be set. */
    class IPositionable
    {
    public:

        /** Destructor. */
        virtual ~IPositionable(void) throw() = 0 {}

        /**
         * Moves to a given position. 
         *
         * @param nX New X location.
         * @param nY New Y location.
         * @param nZ New Z location.
         */
        virtual void MoveTo(const float nX, const float nY, const float nZ) = 0;

        /**
         * Moves to a given position.
         *
         * @param pPosition New position.
         */
        virtual void MoveTo(const C3DPoint<float> & pPosition) = 0;

        /**
         * Moves a given amount. 
         *
         * @param nDeltaX Delta X location.
         * @param nDeltaY Delta Y location.
         * @param nDeltaZ Delta Z location.
         */
        virtual void MoveBy(const float nDeltaX, const float nDeltaY, const float nDeltaZ) = 0;

        /**
         * Retrieves the position of this model.
         *
         * @return The position of this model.
         */
        virtual const C3DPoint<float> & GetPosition() const = 0;
        
    protected:

        /** Constructor. */
        IPositionable(void) {}
    };

} // namespace Egl