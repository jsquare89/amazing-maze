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
        /** CFont implementation using Cpw. */
        class CFontImpl : public boost::enable_shared_from_this<CFontImpl>
        {
        public:

            /** Constructor. */
            CFontImpl();

            /** 
             * Initializer. We use 2 phase initialization because 
             * it is easier for CContext to create us that way. 
             */
            void Init(const std::string & strFontName,
                      const int nFontSize,
                      const ContextPtr_t & pContext,
                      const pCpw pContextHandle);

            /** Destructor. */
            ~CFontImpl() throw();        

            /** Retrieves the context for this timer. */
            const ContextPtr_t & GetContext() const { return m_pContext; }
            
            /**
             * Draws a string using this font.
             */
            void DrawString(const std::string & strText) const;

        private:

            /** Type of timer map. */
            typedef std::vector<boost::weak_ptr<CFontImpl> > TimerMap_t;

        private:

            /** Prevent copy ctor and op=. */
            CFontImpl(const CFontImpl &);
            CFontImpl & operator=(const CFontImpl &);
                
        private:

            /** Cpw font handle. */
            CpwFontFace m_pHandle;

            /** Context that created the window. */
            ContextPtr_t m_pContext;

            /** Cpw handle. */
            pCpw m_pContextHandle;
        };
    } // namespace detail
} // namespace Egl