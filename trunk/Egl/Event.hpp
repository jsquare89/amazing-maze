#pragma once

#include <cassert>
#include <vector>
#include <boost/function.hpp>
#include <boost/mpl/void.hpp>
#include "Egl/Common.hpp"

namespace Egl
{
    /** 
     * Represents an event that some EventSource fires. 
     *
     * @tparam TEventSoure Type of source that owns this event.
     */
    template <typename TEventSource, typename TSinkSignature, int tEventId>
    class CEvent
    {
    public:

        /** Type of sink think event accepts. */
        typedef boost::function<TSinkSignature> EventSink_t;

    private:

        /** Type of sink vector. */
        typedef std::vector<EventSink_t> Sinks_t;

    public:

        /** 
         * Constructor. 
         */
        CEvent()
        {
        }

        /** 
         * Destructor. 
         */
        ~CEvent(void) throw()
        {
        }

        /**
         * Adds a sink (listener) to this event.
         * 
         * @param fSink A function that will be called
         *              when the event fires.
         *
         * @return *this.
         */
        template <class TSink>
        CEvent & operator+=(const TSink & fSink)
        {
            // Lock a mutex since there could be a race condition 
            // between the caller adding itself as a sink and 
            // the event firing. The same mutex must be locked 
            // in the Fire() function.
            // TODO add a scoped lock

            // Check if this sink is already in the list
            for (Sinks_t::const_iterator citSink = m_vSinks.begin(); 
                citSink != m_vSinks.end(); ++citSink)
            {
                if (*citSink == fSink)
                    break;
            }

            // Add new listener
            m_vSinks.push_back(fSink);

            // Add sink to list
            return *this;
        }

        /**
         * Removes a sink (listener) to this event.
         * 
         * @param fSink The sink to remove.
         *
         * @return *this.
         */
        template <class TSink>
        CEvent & operator-=(const TSink & fSink)
        {
            // Lock a mutex since there could be a race condition 
            // between the caller adding itself as a sink and 
            // the event firing. The same mutex must be locked 
            // in the Fire() function.
            // TODO add a scoped lock

            // Check if this sink is in the list
            for (Sinks_t::iterator itSink = m_vSinks.begin(); 
                itSink != m_vSinks.end(); ++itSink)
            {
                if (*itSink == fSink)
                {
                    // Erase sink
                    m_vSinks.erase(itSink);
                    break;
                }
            }

            return *this;
        }

        /** 
         * Retrieves whether this event has subscribers.
         *
         * @return True if this event has subscribers, false 
         *         otherwise.
         */
        bool HasSubscribers() const 
        { 
            // Lock a mutex to avoid race condition with sink being added or removed
            // TODO add a scoped lock
            return !m_vSinks.empty(); 
        }

    private:

        /**
         * Fires this event. Notify sinks (listeners).
         */
        void Fire() const
        {
            // Lock a mutex since there could be a race condition 
            // between the caller adding itself as a sink and 
            // the event firing. The same mutex must be locked 
            // in the operator+=() function.

            // TODO add a scoped lock

            // Notify sinks
            for (Sinks_t::const_iterator citSink = m_vSinks.begin(); 
                citSink != m_vSinks.end(); ++citSink)
            {
                // Call sink
                try
                {
                    // Call sink
                    (*citSink)();
                }
                catch (...)
                {
                    // The sink threw an exception
                    // TODO, add a log statement here
                }
            }
        }

        /**
         * Fires this event. Notify sinks (listeners).
         */
        template <typename TParam1>
        void Fire(TParam1 tParam1) const
        {
            // Lock a mutex since there could be a race condition 
            // between the caller adding itself as a sink and 
            // the event firing. The same mutex must be locked 
            // in the operator+=() function.

            // TODO add a scoped lock

            // Notify sinks
            for (Sinks_t::const_iterator citSink = m_vSinks.begin(); 
                citSink != m_vSinks.end(); ++citSink)
            {
                // Call sink
                try
                {
                    // Call sink
                    (*citSink)(tParam1);
                }
                catch (...)
                {
                    // The sink threw an exception
                    // TODO, add a log statement here
                }
            }
        }

        /**
         * Fires this event. Notify sinks (listeners).
         */
        template <typename TParam1, typename TParam2>
        void Fire(TParam1 tParam1, TParam2 tParam2) const
        {
            // Lock a mutex since there could be a race condition 
            // between the caller adding itself as a sink and 
            // the event firing. The same mutex must be locked 
            // in the operator+=() function.

            // TODO add a scoped lock

            // Notify sinks
            for (Sinks_t::const_iterator citSink = m_vSinks.begin(); 
                citSink != m_vSinks.end(); ++citSink)
            {
                // Call sink
                try
                {
                    // Call sink
                    (*citSink)(tParam1, tParam2);
                }
                catch (...)
                {
                    // The sink threw an exception
                    // TODO, add a log statement here
                }
            }
        }

        /**
         * Fires this event. Notify sinks (listeners).
         */
        template <typename TParam1, typename TParam2, typename TParam3, 
                  typename TParam4, typename TParam5>
        void Fire(TParam1 tParam1, TParam2 tParam2, TParam3 tParam3, 
                  TParam4 tParam4, TParam5 tParam5) const
        {
            // Lock a mutex since there could be a race condition 
            // between the caller adding itself as a sink and 
            // the event firing. The same mutex must be locked 
            // in the operator+=() function.

            // TODO add a scoped lock

            // Notify sinks
            for (Sinks_t::const_iterator citSink = m_vSinks.begin(); 
                citSink != m_vSinks.end(); ++citSink)
            {
                // Call sink
                try
                {
                    // Call sink
                    (*citSink)(tParam1, tParam2, tParam3, tParam4, tParam5);
                }
                catch (...)
                {
                    // The sink threw an exception
                    // TODO, add a log statement here
                }
            }
        }

        // Prevent copy ctor and operator=.
        CEvent(const CEvent &);
        CEvent & operator=(const CEvent &);

    private:

        /** List of subscribers to this event. */
        Sinks_t m_vSinks;

    private:

        /** The source is our friend so it can call Fire. */
        friend typename TEventSource;
    };

} // namespace Egl
