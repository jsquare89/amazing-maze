#include "Precompiled.hpp"
#include "Egl/StraightPathAnimator.hpp"
#include "Egl/Positionable.hpp"

namespace Egl
{
    CStraightPathAnimator::CStraightPathAnimator(const PositionablePtr_t & pObject,
                                                 const C3DPoint<float> & pStart, 
                                                 const C3DPoint<float> & pEnd,
                                                 const TimerPtr_t & pTimer) :
                                                 CAnimator(pTimer),
                                                 m_pStart(pStart),
                                                 m_pEnd(pEnd),
                                                 m_nPositionConstant(0),
                                                 m_bLoop(false),
                                                 m_nStep(0.1f),
                                                 m_pObject(pObject)
    {
    }

    CStraightPathAnimator::CStraightPathAnimator(const PositionablePtr_t & pObject,
                                                 const C3DPoint<float> & pStart, 
                                                 const C3DPoint<float> & pEnd,
                                                 const TimerPtr_t & pTimer, 
                                                 const float nTimerFrequencyDivisor) :
                                                 CAnimator(pTimer, nTimerFrequencyDivisor),
                                                 m_pStart(pStart),
                                                 m_pEnd(pEnd),
                                                 m_nPositionConstant(0),
                                                 m_bLoop(false),
                                                 m_nStep(0.1f),
                                                 m_pObject(pObject)
    {
    }

    // virtual 
    void 
    CStraightPathAnimator::Restart()
    {
        // Rewind, then resume
        this->Rewind();
        this->Resume();
    }

    // virtual 
    CStraightPathAnimator::~CStraightPathAnimator(void) throw()
    {
    }

    // virtual 
    void 
    CStraightPathAnimator::Tick()
    {
        // If this is the first tick we tell everybody the
        // animation has started. This will also happen 
        // when we loop back which is not exactly right...
        // but not exactly wrong either so for now this 
        // is the way it is.
        if (0 == m_nPositionConstant)
            this->OnAnimationBegin();

        // On every tick we increment the position constant 
        // so we know where we are
        m_nPositionConstant += m_nStep;

        // Is the path done?
        if (m_nPositionConstant >= 1.0)
        {
            // Move the object to the end position
            m_pObject->MoveTo(m_pEnd);

            // Animation has ended, let everybody know
            this->OnAnimationEnd();

            // Are we looping back?
            if (m_bLoop)
            {
                m_nPositionConstant = 0;
            }
            else // not looping back
            {
                m_nPositionConstant = 1.0;

                // Pause the animation
                this->Pause();
            }
        }
        else // not at the end of the path
        {
            // Calculate the new point
            C3DPoint<float> pCurrent = ((m_pEnd - m_pStart) * m_nPositionConstant) + m_pStart;

            // Move the object to the current position
            m_pObject->MoveTo(pCurrent);
        }
    }

    // virtual 
    void 
    CStraightPathAnimator::Rewind()
    {
        // Reset the animation to its original state and pause
        this->Pause();

        // Set position constant back to the initial value
        m_nPositionConstant = 0;

        // Object is back at the beginning
        m_pObject->MoveTo(m_pStart);
    }

} // namespace Egl
