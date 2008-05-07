#pragma once

#include "Egl/Common.hpp"
#include "Egl/Model.hpp"

namespace Egl
{
    /**
     * A model that appears as a 2D image.
     */
    class CImage : public CModel
    {
    public:

        /** Constructor. */
        CImage(void);

        /** Constructor. */
        CImage(const float nX, const float nY, const float nZ);

        /** Constructor. */
        CImage(const float nWidth, const float nHeight, const TexturePtr_t & pTexture);

        /** Constructor. */
        CImage(const float nX, const float nY, const float nZ, 
               const float nWidth, const float nHeight,
               const TexturePtr_t & pTexture);

        /** Destructor */
        virtual ~CImage(void) throw();

        /** Retrieves the texture used by this image. */
        const TexturePtr_t & GetTexture() const { return m_pTexture; }

        /** Sets the texture this image should use. */
        void SetTexture(const TexturePtr_t & pTexture, const float nWidth, const float nHeight);

        /** Resize to a given width and height. */
        void ResizeTo(const float nWidth, const float nHeight);

        // Inherited members
        virtual const float GetWidth() const;
        virtual const float GetHeight() const;
        virtual const float GetDepth() const { return 0; }
        virtual void Draw(void);
        
    private:

        /** Texture. */
        TexturePtr_t m_pTexture;

        /** Width. */
        float m_nWidth;

        /** Height. */
        float m_nHeight;
    };
} // namespace Egl