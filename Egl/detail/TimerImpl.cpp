#include "Precompiled.hpp"
#include "Egl/Context.hpp"
#include "Egl/Timer.hpp"
#include "Egl/detail/TimerImpl.hpp"

namespace Egl
{
    namespace detail
    {        
        /** Called when the timer ticks. */
        static void OnTimerTick(pCpw cpw, uint_32 nTimerId)
        {
            // TODO: Find the right timer ptr based on the timer id.
            boost::shared_ptr<CTimerImpl> pTimerImpl = CTimerImpl::GetTimerImpl(nTimerId);
            cpw;
            if (pTimerImpl)
            {
                try
                {
                    // Fire the event
                    pTimerImpl->OnTick();
                }
                catch (...)
                {
                    // An error occurred firing the event
                    // TODO log an error
                }
            }
        }

        // We create a map with two entries initially because we will 
        // start map IDs at 1.

        // static
        CTimerImpl::TimerMap_t CTimerImpl::s_vTimerMap;

        // static 
        int 
        CTimerImpl::RegisterTimer(const boost::shared_ptr<CTimerImpl> & pTimerImpl)
        {
            // TODO, add lock on static mutex.

            // New id 
            TimerMap_t::size_type nIndex;

            // Find first un-used slot in timer map
            for (nIndex = 0; nIndex < s_vTimerMap.size(); ++nIndex)
            {
                // Break if we find a gap
                if (s_vTimerMap[nIndex].expired())
                {
                    // Use slot for new timer
                    s_vTimerMap[nIndex] = pTimerImpl;
                    return nIndex + 1;
                }
            }

            // Put in a new slot
            s_vTimerMap.push_back(pTimerImpl);
            return nIndex + 1;
        }

        // static 
        void 
        CTimerImpl::UnregisterTimer(const int nTimerId)
        {
            // TODO, add lock on static mutex

            // Reset timer at position
            s_vTimerMap[nTimerId - 1].reset();
        }

        // static 
        const boost::shared_ptr<CTimerImpl> 
        CTimerImpl::GetTimerImpl(const int nTimerId)
        {
            // TODO, add lock on static mutex

            // Return timer
            return s_vTimerMap[nTimerId - 1].lock();
        }

        CTimerImpl::CTimerImpl() : m_nId(0),
                                   m_pContext(),
                                   m_pContextHandle(0),
                                   m_pTimer(0)
        {
        }

        void 
        CTimerImpl::Init(const CTimer * pTimer,
                         const ContextPtr_t & pContext,
                         const pCpw pContextHandle)
        {
            // Initialize all the internal values
            m_pTimer = pTimer;
            m_pContext = pContext;
            m_pContextHandle = pContextHandle;            
        }

        CTimerImpl::~CTimerImpl() throw()
        {
            // Kill the timer
            this->Stop();
        }

        void 
        CTimerImpl::StartInterval(const int nIntervalTime)
        {
            // Get new ID for timer
            int nId = CTimerImpl::RegisterTimer(this->shared_from_this());

            // Create timer
            if (!cpwTimerCallback(m_pContextHandle, nIntervalTime,
                nId, true, &OnTimerTick))
            {
                // Unregister timer id
                CTimerImpl::UnregisterTimer(nId);

                // TODO, communicate error (throw)
            }
            
            // Set id of timer
            m_nId = nId;
        }

        void 
        CTimerImpl::Stop()
        {
            // Unregister timer
            if (m_nId > 0)
                CTimerImpl::UnregisterTimer(m_nId);

            // Kill timer
            cpwKillTimer(m_pContextHandle, m_nId);
        }

        void 
        CTimerImpl::StartTimeout(const int nTimeoutTime)
        {
            // Get new ID for timer
            int nId = CTimerImpl::RegisterTimer(this->shared_from_this());


            // Create timer
            if (!cpwTimerCallback(m_pContextHandle, nTimeoutTime,
                nId, false, &OnTimerTick))
            {
                // Unregister timer id
                CTimerImpl::UnregisterTimer(nId);

                // TODO, communicate error (throw)
            }
            
            // Set id of timer
            m_nId = nId;
        }
        
        void 
        CTimerImpl::OnTick()
        {
            CEventArgs args;
            m_pTimer->Tick.Fire(*m_pTimer, args);            
        }        
    }    
} // namespace Egl