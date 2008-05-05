#pragma once

#include "Egl/Common.hpp"
#include "Egl/Event.hpp"

namespace Egl
{
    /** 
     * A base class for all animators. An animator takes a timer 
     * and it does something on every tick of the timer. Animators
     * start in the paused state.
     */
    class CAnimator
    {
    public:

        /** Type of animation start event. */
        typedef CEvent<CAnimator, void (), 0> OnAnimationBeginEvent_t;

        /** Type of animation end event. */
        typedef CEvent<CAnimator, void (), 1> OnAnimationEndEvent_t;

    public:        
        
        /** Destructor. */
        virtual ~CAnimator(void) throw() = 0;
        
        /** 
         * Retrieves the timer used by this animator.
         *
         * @return The timer used by this animator.
         */
        const TimerPtr_t & GetTimer() const { return m_pTimer; }

        /**
         * Sets the timer to be used by this animator.
         *
         * @param pTimer The timer this animator should use.
         */
        virtual void SetTimer(const TimerPtr_t & pTimer);

        /**
         * Retrieves the frequency divisor this animator is using.
         * The frequency divisor is the [0..1] ratio between the 
         * frequency of the timer ticks and the frequency at which 
         * this animator should animate. e.g. 1.0 if the animator should
         * animate on every tick of the timer, or 0.5 if the 
         * animator should animate every two ticks of the timer. 
         * If set to 0 the animator will not animate at all.
         *
         * @return The frquency divisor this animator is using.
         */
        float GetFrequencyDivisor() const { return m_nTimerFrequencyDivisor; }

        /** 
         * Speedup or slowdown this animator by setting the frequency
         * divisor this animator should use. 
         * The frequency divisor is the [0..1] ratio between the 
         * frequency of the timer ticks and the frequency at which 
         * this animator should animate. e.g. 1.0 if the animator should
         * animate on every tick of the timer, or 0.5 if the 
         * animator should animate every two ticks of the timer. 
         * If set to 0 the animator will not animate at all.
         *
         * @param nTimerFrequencyDivisor The frequency divisor this 
         *                               animator should use.
         */
        virtual void SetSpeed(const float nTimerFrequencyDivisor)
        {
            m_nTimerFrequencyDivisor = nTimerFrequencyDivisor;
        }

        /**
         * Pauses this animator.
         */
        virtual void Pause()
        {
            // Set paused
            m_bPaused = true;
        }

        /** 
         * Resumes this animator.
         */
        virtual void Resume()
        {
            // Set paused
            m_bPaused = false;
        }

        /**
         * Restart this animation.
         */
        virtual void Restart() = 0;

        /**
         * Resets this animation to its original position
         * and pauses the animation.
         */
        virtual void Rewind() = 0;

    public:

        /** 
         * Event fired when the animation begins.
         */
        OnAnimationBeginEvent_t OnAnimationBegin;

        /** 
         * Event fired when the animation ends.
         */
        OnAnimationEndEvent_t OnAnimationEnd;

    protected:

        /** Constructor. */
        CAnimator();

        /** 
         * Constructor.
         *
         * @param pTimer Timer this animator will use.
         *               This animator will animate on every tick of the 
         *               timer.
         */
        explicit CAnimator(const TimerPtr_t & pTimer);

        /** 
         * Constructor.
         *
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
        CAnimator(const TimerPtr_t & pTimer, const float nTimerFrequencyDivisor);

        /**
         * Does the work this animator is supposed to do
         * on every tick.
         */
        virtual void Tick() = 0;

        /** 
         * Fire the animation begin event. 
         */
        void FireOnAnimationBeginEvent()
        {
            this->OnAnimationBegin.Fire();
        }

        /** 
         * Fire the animation end event. 
         */
        void FireOnAnimationEndEvent()
        {
            this->OnAnimationEnd.Fire();
        }

    private:

        /** Receives timer ticks. */
        void HandleTimerOnTickEvent();

        // Avoid copy ctor and op=
        CAnimator(const CAnimator&);
        CAnimator & operator=(const CAnimator &);

    private:

        /** Timer. */
        TimerPtr_t m_pTimer;

        /** Timer frequency divisor. */
        volatile float m_nTimerFrequencyDivisor;

        /** Whether this timer is paused. */
        volatile bool m_bPaused;

        /** Current tick part. */
        volatile float m_nTickPart;
    };

} // namespace Egl
