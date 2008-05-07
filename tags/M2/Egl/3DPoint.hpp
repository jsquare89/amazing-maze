#pragma once

#include <boost/operators.hpp>
#include <cmath>

namespace Egl
{

    /** 
     * A point in 3D space. 
     *
     * @tparam TPrecision Coordinate type (int, float, double, etc.)
     */
    template <class TPrecision>
    class C3DPoint : boost::addable< C3DPoint<TPrecision>,
                     boost::subtractable< C3DPoint<TPrecision>,     // point - point
                     boost::dividable2< C3DPoint<TPrecision>, TPrecision,    // point / TPrecision
                     boost::multipliable2< C3DPoint<TPrecision>, TPrecision // point * TPrecision, TPrecision * point
                     > > > >

    {
    public:

        /** 
         * Constructor. Initializes the point to (0,0,0).
         */
        C3DPoint(void) : m_nX(0), m_nY(0), m_nZ(0)
        {
        }

        /** 
         * Constructor. 
         *
         * @param rhs Other point.
         */
        C3DPoint(const C3DPoint & rhs) :
            m_nX(rhs.m_nX), m_nY(rhs.m_nY), m_nZ(rhs.m_nZ)
        {
        }

        /** 
         * Makes the coordinates of this point equal to the coordinates
         * of another point.
         *
         * @param rhs Other point.
         */
        C3DPoint & operator=(const C3DPoint & rhs)        
        {
            m_nX = rhs.m_nX;
            m_nY = rhs.m_nY;
            m_nZ = rhs.m_nZ;
            return *this;
        }

        /** 
         * Constructor. 
         *
         * @param nX X coordinate of the point.
         * @param nY Y coordinate of the point.
         * @param nZ Z coordinate of the point.
         */
        C3DPoint(const TPrecision nX, const TPrecision nY, const TPrecision nZ) :
            m_nX(nX), m_nY(nY), m_nZ(nZ)
        {        
        }

        /** Destructor. */
        ~C3DPoint(void) throw()
        {
        }

        /** 
         * Retrieves the X coordinate of this point.
         *
         * @return The X coordinate of this point.
         */
        TPrecision GetX() const { return m_nX; }

        /** 
         * Sets the X coordinate of this point.
         *
         * @param nX The X coordinate of this point.
         */
        void SetX(const TPrecision nX) { m_nX = nX; }

        /** 
         * Retrieves the Y coordinate of this point.
         *
         * @return The Y coordinate of this point.
         */
        TPrecision GetY() const { return m_nY; }

        /** 
         * Sets the Y coordinate of this point.
         *
         * @param nY The Y coordinate of this point.
         */
        void SetY(const TPrecision nY) { m_nY = nY; }

        /** 
         * Retrieves the Z coordinate of this point.
         *
         * @return The Z coordinate of this point.
         */
        TPrecision GetZ() const { return m_nZ; }

        /** 
         * Sets the Z coordinate of this point.
         *
         * @param nZ The Z coordinate of this point.
         */
        void SetZ(const TPrecision nZ) { m_nZ = nZ; }

        /** 
         * Sets the coordinates of this point.
         *
         * @param nX The X coordinate.
         * @param nY The Y coordinate.
         * @param nZ The Z coordinate.
         */
        void Set(const TPrecision nX, const TPrecision nY, const TPrecision nZ)
        {
            m_nX = nX;
            m_nY = nY;
            m_nZ = nZ;
        }

        /**
         * Adds another point to this point. Every member
         * of the point will be added.
         *
         * @param pPoint Point to add to this point.
         */
        C3DPoint & operator+=(const C3DPoint & pPoint)
        {
            m_nX += pPoint.m_nX;
            m_nY += pPoint.m_nY;
            m_nZ += pPoint.m_nZ;
            return *this;
        }

        /**
         * Subtract another point from this point. Every member
         * of the point will be subtracted.
         *
         * @param pPoint Point to subtract from this point.
         */
        C3DPoint & operator-=(const C3DPoint & pPoint)
        {
            m_nX -= pPoint.m_nX;
            m_nY -= pPoint.m_nY;
            m_nZ -= pPoint.m_nZ;
            return *this;
        }

        /**
         * Multiplies this point by a scalar. Every member
         * of the point will be multiplied.
         *
         * @param pScalar Scalar to multiply this point by.
         */
        C3DPoint & operator*=(const TPrecision nScalar)
        {
            m_nX *= nScalar;
            m_nY *= nScalar;
            m_nZ *= nScalar;
            return *this;
        }

        /**
         * Divides this point by a scalar. Every member
         * of the point will be divided.
         *
         * @param pScalar Scalar to divide this point by.
         */
        C3DPoint & operator/=(const TPrecision nScalar)
        {
            m_nX /= nScalar;
            m_nY /= nScalar;
            m_nZ /= nScalar;
            return *this;
        }

        /**
         * Calculates the distance between two this point and another point.
         *
         * @return The distance between this point and another point.
         */
        float DistanceTo(const C3DPoint & pPoint)
        {
            // Calculate distance
            return std::sqrt(std::pow(m_nX - pPoint.m_nX, 2) + 
                std::pow(m_nY - pPoint.m_nY, 2) + 
                std::pow(m_nZ - pPoint.m_nZ, 2));
        }

    private:

        /** X coordinate. */
        TPrecision m_nX;

        /** Y coordinate. */
        TPrecision m_nY;

        /** Z coordinate. */
        TPrecision m_nZ;
    };

} // namespace Egl