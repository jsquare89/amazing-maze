#include "Precompiled.hpp"
#include "Egl/Texture.hpp"
#include "Egl/detail/DevIL.hpp"

namespace Egl
{
    namespace detail
    {
        /** Implementation of CTexture using DevIL library. */
        class CTextureImpl
        {
        public:
            /** Constructor. */
            CTextureImpl(const std::string & strTextureFilePath, 
                       const ContextPtr_t & pContext) :
                       m_pContext(pContext),
                       m_nILTexID(0),
                       m_nTexID(0),
                       m_nWidth(0),
                       m_nHeight(0)
            {
                // TODO, we proabably want to lock this since somebody
                // else can load the same image or generate the same id.

                // TODO, handle error

                // Load texture
                //m_nHandle = ilutGLLoadImage(const_cast<char*>(strTextureFilePath.c_str()));
                ilGenImages(1, &m_nILTexID);
                ilBindImage(m_nILTexID);
                ilLoadImage(strTextureFilePath.c_str());
                
                // Convert texture
                ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
                
                // Make OpenGL texture
                glGenTextures(1, &m_nTexID);
                glBindTexture(GL_TEXTURE_2D, m_nTexID);
                m_nWidth = ilGetInteger(IL_IMAGE_WIDTH);
                m_nHeight = ilGetInteger(IL_IMAGE_HEIGHT);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

                glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), m_nWidth, m_nHeight, 
                    0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
            }

            /** Destructor. */
            ~CTextureImpl()
            {
                // Delete image
                if (0 != m_nILTexID)
                    ilDeleteImage(m_nILTexID);

                // Delete texture
                if (0 != m_nTexID)
                    glDeleteTextures(1, &m_nTexID);
            }

            /**
             * Sets this texture as the current texture using 
             * glBindTexture.
             */
            void Bind()
            {
                glBindTexture(GL_TEXTURE_2D, m_nTexID);
            }

            /** 
             * Unbinds this texture. 
             */
            void UnBind()
            {
                glBindTexture(GL_TEXTURE_2D, 0);
            }

            /** 
             * Retrieves the context that was used to load
             * this image.
             */
            const ContextPtr_t & GetContext() const { return m_pContext; }

        private:

            /** DevIL image handle. */
            ILuint m_nILTexID;

            /** DevIL image handle. */
            GLuint m_nTexID;

            /** Width. */
            ILint m_nWidth;

            /** Height. */
            ILint m_nHeight;

            /** Context. */
            ContextPtr_t m_pContext;
        };

    } // namespace detail
    
    CTexture::CTexture(const std::string & strTextureFilePath, 
                   const ContextPtr_t & pContext) :
                   m_pImpl(new detail::CTextureImpl(
                       strTextureFilePath, pContext))
    {
    }

    CTexture::~CTexture(void) throw()
    {
    }

    const ContextPtr_t & 
    CTexture::GetContext() const
    {
        // Forward call
        return m_pImpl->GetContext(); 
    }
    
    void
    CTexture::Bind()
    {
        // Forward call
        m_pImpl->Bind();
    }

    void
    CTexture::UnBind()
    {
        // Forward call
        m_pImpl->UnBind();
    }

} // namespace Egl
