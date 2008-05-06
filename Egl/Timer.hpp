#pragma once

#include <string>
#include <boost/shared_ptr.hpp>
#include "Egl/Common.hpp"
#include "Egl/Event.hpp"

namespace Egl
{
    namespace detail
    {
        /** Forward declaration of CTimerImpl. */
        class CTimerImpl;
    } // namespace detail

    /** A timer. */
    class CTimer
    {
    public:        
        
        /** 
         * Starts the timer in repeating mode. The timer will 
         * invoke the Tick event on a regular basis (how often 
         * depends on the interval parameter.
         *
         * @param nIntervalTime Time between ticks in milliseconds.
         */
        void StartInterval(const int nIntervalTime);

        /**
         * Stops the timer.
         */
        void Stop();

        /** 
         * Starts the timer in single-shot mode. The timer will 
         * invoke the Tick event once when the time is ellapsed.
         *
         * @param nTimeoutTime Time to wait before ticking.
         */
        void StartTimeout(const int nTimeoutTime);
        
        /** Destructor. */
        ~CTimer(void) throw();
        
        /** 
         * Retrieves the context that was used to create 
         * this timer.
         */
        const ContextPtr_t & GetContext() const;

    public:

        /** Type of the Draw event. */
        typedef CEvent<detail::CTimerImpl, CTimer, CEventArgs, 0> TickEvent_t;

    public:

        /** 
         * Event that will fire when the timer ticks.
         * To receive this event you must subscribe to it by using
         * the += operator. 
         */
        TickEvent_t Tick;

    protected:

        /** Creates a timer. */
        CTimer();  

    private:

        /** 
         * Gets the impl of this timer.
         */
        detail::CTimerImpl & GetImpl() const { return *m_pImpl; }

        // Avoid copy ctor and op=
        CTimer(const CTimer&);
        CTimer & operator=(const CTimer &);

    private:

        /** Timer impl. */
        boost::shared_ptr<detail::CTimerImpl> m_pImpl;        

    private:

        /** CContext is our friend so it can create us. */
        friend class CContext;
    };

} // namespace Egl
