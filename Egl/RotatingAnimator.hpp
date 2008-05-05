#pragma once

#include "Egl/Common.hpp"
#include "Egl/Animator.hpp"

namespace Egl
{
    /** 
     * An animator that rotates an object every time the 
     * animation advances (on every tick of the animation).
     */
    class CRotatingAnimator : public virtual CAnimator
    {
    public:

        /** 
         * Constructor.
         *
         * @param pObject Object to rotate.
         * @param nStartAngle Star angle of the animation.
         * @param nEndAngle End angle of the animation.
         * @param pTimer Timer this animator will use.
         *               This animator will animate on every tick of the 
         *               timer.
         */
        CRotatingAnimator(const RotatablePtr_t & pObject, 
                          const float nStartAngle, 
                          const float pEnd, 
                          const TimerPtr_t & pTimer);

        /** 
         * Constructor.
         *
         * @param pObject Object to move along the straight path.
         * @param nStartAngle Star angle of the animation.
         * @param nEndAngle End angle of the animation.
         * @param pTimer Timer this animator will use.
         *               This animator will animate on every tick of the 
         *               timer.
         * @param nTimerFrequencyDivisor The [0..1] ratio between the frequency of
         *                               the timer ticks and the frequency
         *                               at which this animator should animate.
         *                               e.g. set to 1.0 if the animator should
         *                               animate on every tick of the timer, or
         *                               0.5 if the animator should animate every
         *                               two ticks of the timer. If set to 0 the
         *                               animator will not animate at all.
         */
        CRotatingAnimator(const RotatablePtr_t & pObject, 
                          const float nStartAngle, 
                          const float nEndAngle,
                          const TimerPtr_t & pTimer, 
                          const float nTimerFrequencyDivisor);

        /**
         * Sets whether the animation should automatically restart 
         * at the starting point after it has reached the end point.
         * 
         * @param bLoop True of the animation should restart automatically
         *              false otherwise.
         */
        void SetLoopPlayback(const bool bLoop) { m_bLoop = bLoop; }

        /** 
         * Set the X axis rotation increment (how much the object
         * is rotated around the X axis every time the animation advances.
         *
         * @param nXRotationIncrement The X axis rotation increment.
         */
        void SetXRotationIncrement(const float nXRotationIncrement)
        {
            m_nXRotationIncrement = nXRotationIncrement;
        }

        /** 
         * Set the Y axis rotation increment (how much the object
         * is rotated around the Y axis every time the animation advances.
         *
         * @param nYRotationIncrement The Y axis rotation increment.
         */
        void SetYRotationIncrement(const float nYRotationIncrement)
        {
            m_nYRotationIncrement = nYRotationIncrement;
        }

        /** 
         * Set the Z axis rotation increment (how much the object
         * is rotated around the Z axis every time the animation advances.
         *
         * @param nZRotationIncrement The Z axis rotation increment.
         */
        void SetZRotationIncrement(const float nZRotationIncrement)
        {
            m_nZRotationIncrement = nZRotationIncrement;
        }
        
        /**
         * Restart this animation.
         */
        virtual void Restart();

        /**
         * Resets this animation to its original position
         * and pauses the animation.
         */
        virtual void Rewind();

        /** Destructor. */
        virtual ~CRotatingAnimator(void) throw();

    protected:

        /**
         * Does the work this animator is supposed to do
         * on every tick.
         */
        virtual void Tick();

    private:

        /** Starting angle. */
        float m_nStartAngle;

        /** Ending angle. */
        float m_nEndAngle;

        /** Current X rotation angle. */
        float m_nXRotation;

        /** Current Y rotation angle. */
        float m_nYRotation;

        /** Current Z rotation angle. */
        float m_nZRotation;

        /** X rotation increment. */
        float m_nXRotationIncrement;

        /** Y rotation increment. */
        float m_nYRotationIncrement;

        /** Z rotation increment. */
        float m_nZRotationIncrement;

        /** Loop playback. */
        bool m_bLoop;

        /** Object being rotated. */
        RotatablePtr_t m_pObject;
    };

} // namespace Egl
