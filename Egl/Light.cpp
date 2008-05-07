#include "Precompiled.hpp"
#include "Light.hpp"

namespace Egl
{
    void 
    CLight::SetAmbientColor(const float nRed, 
                            const float nGreen, 
                            const float nBlue, 
                            const float nAlpha)
    {
        // Set intensity
        GLfloat aIntensity[4] = { nRed, nGreen, nBlue, nAlpha };
        glLightfv(m_nId, GL_AMBIENT, &aIntensity[0]);
    }

    void 
    CLight::SetDifuseColor(const float nRed, 
                           const float nGreen, 
                           const float nBlue, 
                           const float nAlpha)
    {
        // Set intensity
        GLfloat aIntensity[4] = { nRed, nGreen, nBlue, nAlpha };
        glLightfv(m_nId, GL_DIFFUSE, &aIntensity[0]);
    }

    void 
    CLight::SetSpecularColor(const float nRed, 
                             const float nGreen, 
                             const float nBlue, 
                             const float nAlpha)
    {
        // Set intensity
        GLfloat aIntensity[4] = { nRed, nGreen, nBlue, nAlpha };
        glLightfv(m_nId, GL_SPECULAR, &aIntensity[0]);
    }

    void 
    CLight::MoveTo(const float nX, 
                        const float nY, 
                        const float nZ)
    {
        // Set intensity
        GLfloat aPosition[4] = { nX, nY, nZ, 
            (Egl::POSITIONAL_LIGHT == m_eLightType) ? 1.0f : 0};
        glLightfv(m_nId, GL_POSITION, &aPosition[0]);
    }

    void 
    CLight::Enable()
    {
        // Enable
        glEnable(m_nId);
    }

    void 
    CLight::Disable()
    {
        // Disable
        glDisable(m_nId);
    }

    CLight::CLight(const int nId, 
                   const LightType eLightType) : 
                   m_nId(nId),
                   m_eLightType(eLightType)
    {
    }
} // namespace Egl