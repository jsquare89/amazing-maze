#pragma once

#include "Egl/Common.hpp"
#include <boost/scoped_ptr.hpp>

namespace Egl
{
    namespace detail
    {
        /** Forward declaration of CTextureImpl. */
        class CTextureImpl;
    } // namespace detail

    /** An image. */
    class CTexture
    {
    public:        
        
        /** Destructor. */
        ~CTexture(void) throw();
             
        /**
         * Sets this texture as the current texture using 
         */
        void Bind();

        /** 
         * Unbinds this texture. 
         */
        void UnBind();

        /** 
         * Retrieves the context that was used to load
         * this image.
         */
        const ContextPtr_t & GetContext() const;
        
    private:

        /** Creates a Texture. */
        CTexture(const std::string & strTextureFilePath, const ContextPtr_t & pContext);  

        // Avoid copy ctor and op=
        CTexture(const CTexture&);
        CTexture & operator=(const CTexture &);

    private:

        /** Impl. */
        boost::scoped_ptr<detail::CTextureImpl> m_pImpl;

    private:

        /** CContext is our friend so it can create us. */
        friend class CContext;
    };

} // namespace Egl
