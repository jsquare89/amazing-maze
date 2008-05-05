#pragma once

#include "Egl/Common.hpp"
#include "Egl/Timer.hpp"
#include <boost/weak_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <vector>

namespace Egl
{
    namespace detail
    {        
        /** CTimer implementation using Cpw. */
        class CTimerImpl : public boost::enable_shared_from_this<CTimerImpl>
        {
        public:

            /** Constructor. */
            CTimerImpl();

            /** 
             * Initializer. We use 2 phase initialization because 
             * it is easier for CContext to create us that way. 
             */
            void Init(const CTimer * pTimer,
                      const ContextPtr_t & pContext,
                      const pCpw pContextHandle);

            /** Destructor. */
            ~CTimerImpl() throw();
        
            /** 
             * Starts the timer in repeating mode. The timer will 
             * invoke the OnTick event on a regular basis (how often 
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
             * invoke the OnTick event once when the time is ellapsed.
             *
             * @param nTimeoutTime Time to wait before ticking.
             */
            void StartTimeout(const int nTimeoutTime);

            /** Retrieves the context for this timer. */
            const ContextPtr_t & GetContext() const { return m_pContext; }

            /** Fire OnTick event. */
            void FireOnTickEvent();
            
            /** 
             * Registers a given timer.
             *
             * @param pTimerImpl Timer impl.
             *
             * @return The id of the new timer.
             */
            static int RegisterTimer(const boost::shared_ptr<CTimerImpl> & pTimerImpl);

            /**
             * Unregisters a given timer.
             *
             * @param nTimerId The timer id.
             */
            static void UnregisterTimer(const int nTimerId);

            /**
             * Gets the timer that has a given id.
             *
             * @param nTimerId The timer id.
             *
             * @return The timer.
             */
            static const boost::shared_ptr<CTimerImpl> GetTimerImpl(const int nTimerId);

        private:

            /** Type of timer map. */
            typedef std::vector<boost::weak_ptr<CTimerImpl> > TimerMap_t;

        private:

            /** Prevent copy ctor and op=. */
            CTimerImpl(const CTimerImpl &);
            CTimerImpl & operator=(const CTimerImpl &);
                
        private:

            /** Cpw timer identifier. */
            unsigned int m_nId;

            /** Context that created the window. */
            ContextPtr_t m_pContext;

            /** Cpw handle. */
            pCpw m_pContextHandle;

            /** Raw timer. */
            const CTimer * m_pTimer;

            /** Map of timer id to timer weak pointer. */
            static TimerMap_t s_vTimerMap;

            /** TODO, add a mutex for timer map. */
        };
    } // namespace detail
} // namespace Egl