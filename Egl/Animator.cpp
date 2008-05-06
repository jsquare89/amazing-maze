#include "Precompiled.hpp"
#include "Egl/Animator.hpp"
#include "Egl/Timer.hpp"
#include <boost/bind.hpp>

namespace Egl
{
    CAnimator::CAnimator() : m_pTimer(),
                             m_nTimerFrequencyDivisor(1.0f),
                             m_bPaused(true),
                             m_nTickPart(0)
    {
    }

    // explicit 
    CAnimator::CAnimator(const TimerPtr_t & pTimer) :
                         m_pTimer(pTimer),
                         m_nTimerFrequencyDivisor(1.0f),
                         m_bPaused(true),
                         m_nTickPart(0)
    {
        // Subscribe to timer.
        if (m_pTimer)
            m_pTimer->Tick += boost::bind(&CAnimator::HandleTimerTick, this, _1, _2);
    }

    CAnimator::CAnimator(const TimerPtr_t & pTimer, 
                        const float nTimerFrequencyDivisor) :
                        m_pTimer(pTimer),
                        m_nTimerFrequencyDivisor(nTimerFrequencyDivisor),
                        m_bPaused(true),
                        m_nTickPart(0)
    {
        // Subscribe to timer.
        if (m_pTimer)
            m_pTimer->Tick += boost::bind(&CAnimator::HandleTimerTick, this, _1, _2);
    }

    // virtual 
    CAnimator::~CAnimator(void) throw()
    {
        // Unsubscribe from timer.
        if (m_pTimer)
            m_pTimer->Tick -= boost::bind(&CAnimator::HandleTimerTick, this, _1, _2);
    }

    void
    CAnimator::HandleTimerTick(const CTimer &, CEventArgs &)
    {
        // Are we paused?
        if (!m_bPaused)
        {
            // m_nTimerFrequencyDivisor represents how much
            // of our tick is complete every time the timer
            // ticks. We keep track of this partial tick count.        

            // Increase our partial tick count
            m_nTickPart += m_nTimerFrequencyDivisor;
            if (m_nTickPart >= 1.0f)
            {            
                // Our whole tick completed
                m_nTickPart = 0;
                this->Tick();            
            }
        }
    }

    // virtual 
    void 
    CAnimator::SetTimer(const TimerPtr_t & pTimer) 
    { 
        // Unsubscribe from previous timer
        if (m_pTimer)
            m_pTimer->Tick -= boost::bind(&CAnimator::HandleTimerTick, this, _1, _2);

        m_pTimer = pTimer; 

        // Subscribe to this timer
        if (m_pTimer)
            m_pTimer->Tick += boost::bind(&CAnimator::HandleTimerTick, this, _1, _2);
    }

} // namespace Egl
