#include "Precompiled.hpp"
#include "Egl/Timer.hpp"
#include "Egl/detail/TimerImpl.hpp"

namespace Egl
{
    CTimer::CTimer() : m_pImpl(new detail::CTimerImpl())
    {
    }

    void 
    CTimer::StartInterval(const int nIntervalTime)
    {
        // Forward call
        m_pImpl->StartInterval(nIntervalTime);
    }
    
    void 
    CTimer::Stop()
    {
        // Forward call
        m_pImpl->Stop();
    }
    
    void 
    CTimer::StartTimeout(const int nTimeoutTime)
    {
        // Forward call
        m_pImpl->StartTimeout(nTimeoutTime);
    }
    
    CTimer::~CTimer(void) throw()
    {
    }
    
    const ContextPtr_t & 
    CTimer::GetContext() const
    {
        // forward call
        return m_pImpl->GetContext();
    }    

} // namespace Egl
