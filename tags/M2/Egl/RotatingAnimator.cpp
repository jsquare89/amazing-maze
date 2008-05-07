#include "Precompiled.hpp"
#include "Egl/RotatingAnimator.hpp"
#include "Egl/Rotatable.hpp"

namespace Egl
{
    CRotatingAnimator::CRotatingAnimator(const RotatablePtr_t & pObject,
                                         const float nStartAngle, 
                                         const float nEndAngle,
                                         const TimerPtr_t & pTimer) :
                                         CAnimator(pTimer),
                                         m_nStartAngle(nStartAngle),
                                         m_nEndAngle(nEndAngle),
                                         m_nXRotation(nStartAngle),
                                         m_nYRotation(nStartAngle),
                                         m_nZRotation(nStartAngle),
                                         m_nXRotationIncrement(0),
                                         m_nYRotationIncrement(0),
                                         m_nZRotationIncrement(0),
                                         m_bLoop(false),
                                         m_pObject(pObject)
    {
    }

    CRotatingAnimator::CRotatingAnimator(const RotatablePtr_t & pObject,
                                         const float nStartAngle, 
                                         const float nEndAngle,
                                         const TimerPtr_t & pTimer, 
                                         const float nTimerFrequencyDivisor) :
                                         CAnimator(pTimer, nTimerFrequencyDivisor),
                                         m_nStartAngle(nStartAngle),
                                         m_nEndAngle(nEndAngle),
                                         m_nXRotation(m_nStartAngle),
                                         m_nYRotation(m_nStartAngle),
                                         m_nZRotation(m_nStartAngle),
                                         m_nXRotationIncrement(0),
                                         m_nYRotationIncrement(0),
                                         m_nZRotationIncrement(0),
                                         m_bLoop(false),
                                         m_pObject(pObject)
    {
    }

    // virtual 
    void 
    CRotatingAnimator::Restart()
    {
        // Rewind, then resume
        this->Rewind();
        this->Resume();
    }

    // virtual 
    CRotatingAnimator::~CRotatingAnimator(void) throw()
    {
    }

    // virtual 
    void 
    CRotatingAnimator::Tick()
    {
        // If this is the first tick we tell everybody the
        // animation has started. This will also happen 
        // when we loop back which is not exactly right...
        // but not exactly wrong either so for now this 
        // is the way it is.
        if ((m_nXRotation == m_nStartAngle) &&
            (m_nYRotation == m_nStartAngle) &&
            (m_nZRotation == m_nStartAngle))
        {
            // Animation has started
            this->OnAnimationBegin();
        }

        // Effective rotation increments
        float nActualXRotationIncrement = 0;
        float nActualYRotationIncrement = 0;
        float nActualZRotationIncrement = 0;

        // Still need to go on X axis?
        if (m_nXRotation < m_nEndAngle)
        {
            nActualXRotationIncrement = m_nXRotationIncrement;
            m_nXRotation += m_nXRotationIncrement;
            if (m_nXRotation > m_nEndAngle)
            {
                nActualXRotationIncrement = m_nEndAngle - m_nXRotation;
                m_nXRotation = m_nEndAngle;
            }
        }

        // Still need to go on Y axis?
        if (m_nYRotation < m_nEndAngle)
        {
            nActualYRotationIncrement = m_nYRotationIncrement;
            m_nYRotation += m_nYRotationIncrement;
            if (m_nYRotation > m_nEndAngle)
            {
                nActualYRotationIncrement = m_nEndAngle - m_nYRotation;
                m_nYRotation = m_nEndAngle;
            }
        }

        // Still need to go on Z axis?
        if (m_nZRotation < m_nEndAngle)
        {
            nActualZRotationIncrement = m_nZRotationIncrement;
            m_nZRotation += m_nZRotationIncrement;
            if (m_nZRotation > m_nEndAngle)
            {
                nActualZRotationIncrement = m_nEndAngle - m_nZRotation;
                m_nZRotation = m_nEndAngle;
            }
        }

        // Rotate the object
        m_pObject->RotateBy(nActualXRotationIncrement, 
            nActualYRotationIncrement, nActualZRotationIncrement);

        // Are we at the end?
        if (((m_nXRotation == m_nEndAngle) || (0 == m_nXRotationIncrement)) &&
            ((m_nYRotation == m_nEndAngle) || (0 == m_nYRotationIncrement)) &&
            ((m_nZRotation == m_nEndAngle) || (0 == m_nZRotationIncrement)))
        {        
            // Animation has ended, let everybody know
            this->OnAnimationEnd();

            // Are we looping back?
            if (m_bLoop)
            {
                // Set all the angles back to the initial value
                m_nXRotation = m_nStartAngle;
                m_nYRotation = m_nStartAngle;
                m_nZRotation = m_nStartAngle;
            }
            else
            {
                // Pause the animation
                this->Pause();
            }
        }
    }

    // virtual 
    void 
    CRotatingAnimator::Rewind()
    {
        // Reset the animation to its original state and pause
        this->Pause();

        // Set all the angles back to the initial value
        m_nXRotation = m_nStartAngle;
        m_nYRotation = m_nStartAngle;
        m_nZRotation = m_nStartAngle;

        // TODO, rotate things an absolute angle 
        //m_pObject->RotateBy(nActualXRotationIncrement, 
        //    nActualYRotationIncrement, nActualZRotationIncrement);
    }

} // namespace Egl
