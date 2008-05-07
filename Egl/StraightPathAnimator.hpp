#pragma once

#include "Egl/Common.hpp"
#include "Egl/Animator.hpp"
#include "Egl/3DPoint.hpp"

namespace Egl
{
    /** 
     * An animator that changes the position of a model
     * on every tick of the animation going from a starting
     * point to an end point in a straight line. A straight
     * line is represented by the parametric equation:
     *
     * P = P1 * k (P2 - P1)
     * 
     * Where P2 and P1 are the starting and ending points 
     * of the animation, P is the position of the animation
     * at any given time, and k is the animation position 
     * constant. This position constant starts
     * at 0 and is increased by a given amount (@see 
     * CStraightPathAnimator::SetStep()) every time 
     * the animation advances (on every tick of the animation). 
     * The speed of the animation will depend on the speed of 
     * the timer powering this animator, the timer frequency 
     * divisor being used and the position constant increment
     * (the step).
     */
    class CStraightPathAnimator : public virtual CAnimator
    {
    public:

        /** 
         * Constructor.
         *
         * @param pObject Object to move along the straight path.
         * @param pStart Star position of the animation.
         * @param pEnd   End position of the animation.
         * @param pTimer Timer this animator will use.
         *               This animator will animate on every tick of the 
         *               timer.
         */
        CStraightPathAnimator(const PositionablePtr_t & pObject, 
                              const C3DPoint<float> & pStart, 
                              const C3DPoint<float> & pEnd, 
                              const TimerPtr_t & pTimer);

        /** 
         * Constructor.
         *
         * @param pObject Object to move along the straight path.
         * @param pStart Star position of the animation.
         * @param pEnd   End position of the animation.
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
        CStraightPathAnimator(const PositionablePtr_t & pObject, 
                              const C3DPoint<float> & pStart, 
                              const C3DPoint<float> & pEnd,
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
         * Sets the step of this animation. The step of the animation
         * is the amount that the position constant is increased
         * every time the animation advances. Initialy the step is 0.1.
         *
         * @param nStep The step of the animation.
         */
        void SetStep(const float nStep) { m_nStep = nStep; }

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
        virtual ~CStraightPathAnimator(void) throw();

    protected:

        /**
         * Does the work this animator is supposed to do
         * on every tick.
         */
        virtual void Tick();

    private:

        /** Starting point of the animation. */
        C3DPoint<float> m_pStart;

        /** Ending point of the animation. */
        C3DPoint<float> m_pEnd;

        /** Current position constant. */
        float m_nPositionConstant;

        /** Loop playback. */
        bool m_bLoop;

        /** Step. */
        float m_nStep;

        /** Object being moved. */
        PositionablePtr_t m_pObject;
    };

} // namespace Egl
