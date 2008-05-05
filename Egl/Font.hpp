#pragma once

#include <string>
#include <boost/scoped_ptr.hpp>
#include "Egl/Common.hpp"

namespace Egl
{
    namespace detail
    {
        /** Forward declaration of CFontImpl. */
        class CFontImpl;
    } // namespace detail

    /** A font. */
    class CFont
    {
    public:        
        
        /** Destructor. */
        ~CFont(void) throw();
        
        /** 
         * Retrieves the context that was used to create 
         * this font.
         */
        const ContextPtr_t & GetContext() const;

    protected:

        /** Creates a font. */
        CFont();  

    private:

        /** 
         * Gets the impl of this font.
         */
        detail::CFontImpl & GetImpl() const { return *m_pImpl; }

        // Avoid copy ctor and op=
        CFont(const CFont&);
        CFont & operator=(const CFont &);

    private:

        /** Font impl. */
        boost::scoped_ptr<detail::CFontImpl> m_pImpl;        

    private:

        /** CContext is our friend so it can create us. */
        friend class CContext;

        /** CWindow is our friend so it can get to the impl. */
        friend class CWindow;
    };

} // namespace Egl
