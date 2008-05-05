#pragma once

#include "Egl/Common.hpp"
#include "Egl/LightType.hpp"

namespace Egl
{

    /** A light. */
    class CLight
    {
    public:
        
        /**
         * Set the ambient RGBA intensity of the light.
         *
         * @param nRed Red intensity of light.
         * @param nGreen Green intensity of light.
         * @param nBlue Blue intensity of light.
         * @param nAlpha Alpha intensity of light.
         */
        void SetAmbientColor(const float nRed, const float nGreen, const float nBlue, const float nAlpha);

        /**
         * Set the difuse RGBA intensity of the light.
         *
         * @param nRed Red intensity of light.
         * @param nGreen Green intensity of light.
         * @param nBlue Blue intensity of light.
         * @param nAlpha Alpha intensity of light.
         */
        void SetDifuseColor(const float nRed, const float nGreen, const float nBlue, const float nAlpha);

        /**
         * Set the specular RGBA intensity of the light.
         *
         * @param nRed Red intensity of light.
         * @param nGreen Green intensity of light.
         * @param nBlue Blue intensity of light.
         * @param nAlpha Alpha intensity of light.
         */
        void SetSpecularColor(const float nRed, const float nGreen, const float nBlue, const float nAlpha);

        /**
         * Sets the position or the direction 
         * of this light (depending on whether the light is 
         * positional or directional).
         *
         * @param nX X position.
         * @param nY Y position.
         * @param nZ Z position.
         */
        void MoveTo(const float nX, const float nY, const float nZ);

        /**
         * Set the type of this light.
         *
         * @param eLightType Light type.
         */
        void SetType(const LightType eLightType) 
        {
            // Set type
            m_eLightType = eLightType;
        }

        /**
         * Enable this light.
         */
        void Enable();

        /** 
         * Disable this light.
         */
        void Disable();

    private:

        /** Constructor. */
        CLight(const int nId, const LightType eLightType);
        CLight(const CLight &);
        CLight & operator=(const CLight &);

    private:

        /** Light id. */
        int m_nId;

        /** Light type. */
        LightType m_eLightType;

    private:

        /** CLighting control can create us. */
        friend class CLightingControl;
    };

} // namespace Egl