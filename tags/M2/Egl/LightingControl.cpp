#include "Precompiled.hpp"
#include "LightingControl.hpp"
#include "Light.hpp"

namespace Egl
{
    namespace detail
    {
        /** Convert light model enum to OpenGL light model constant. */
        inline int ConvertLightModel(const CLightingControl::LightModel_e eLightModel)
        {
            //Convert model
            switch (eLightModel)
            {
                case CLightingControl::LIGHT_MODEL_LOCAL_VIEWER:  return GL_LIGHT_MODEL_LOCAL_VIEWER;
                case CLightingControl::LIGHT_MODEL_TWO_SIDE:      return GL_LIGHT_MODEL_TWO_SIDE;
                case CLightingControl::LIGHT_MODEL_AMBIENT: 
                default:                                          return GL_LIGHT_MODEL_AMBIENT;
            }
        }
    } // namespace detail

    //static 
    void 
    CLightingControl::EnableLighting()
    {
        glEnable(GL_LIGHTING);
    }

    //static 
    void 
    CLightingControl::DisableLighting()
    {
        glDisable(GL_LIGHTING);
    }

    // static
    void
    CLightingControl::SetLighModel(const LightModel_e eLightModel, const float nParam)
    {
        glLightModelf(detail::ConvertLightModel(eLightModel), nParam);
    }

    // static
    void
    CLightingControl::SetLighModel(const LightModel_e eLightModel, const float * nParams)
    {
        glLightModelfv(detail::ConvertLightModel(eLightModel), nParams);
    }

    // static
    const LightPtr_t 
    CLightingControl::CreateLight(const LightType eLightType)
    {
        // Create light
        return LightPtr_t(new CLight(GL_LIGHT0, eLightType));
    }

} // namespace Egl