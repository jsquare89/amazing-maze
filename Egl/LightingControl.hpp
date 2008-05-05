#pragma once

#include "Egl/Common.hpp"
#include "Egl/LightType.hpp"

namespace Egl
{

    /** Controls lights. */
    class CLightingControl
    {
    public:
        /**
         * Light Model.
         */
        enum LightModel_e
        {
            LIGHT_MODEL_LOCAL_VIEWER,
            LIGHT_MODEL_TWO_SIDE,
            LIGHT_MODEL_AMBIENT
        };

    public:
        
        /**
         * Enable lighting.
         */
        static void EnableLighting();
        
        /**
         * Sets the lighting model.
         *
         * @param eLightModel Type of light model.
         * @param nParam Light model param.
         */
        static void SetLighModel(const LightModel_e eLightModel, const float nParam);

        /**
         * Sets the lighting model.
         *
         * @param eLightModel Type of light model.
         * @param nParams Light model params.
         */
        static void SetLighModel(const LightModel_e eLightModel, const float *nParams);

        /** 
         * Creates a light.
         */
        // TODO enable this only if teLightType is LightType::POSITIONAL_LIGHT
        // or LightType::DIRECTIONAL_LIGHT
        template <LightType teLightType>
        static const LightPtr_t CreateLight()
        {
            // Create a light of the given type
            return CLightingControl::CreateLight(teLightType);
        }

    private:

        /** Create light. */
        static const LightPtr_t CreateLight(const LightType eLightType);
    };

} // namespace Egl