#include "Precompiled.hpp"
#include "Egl/Model.hpp"
#include "Egl/Window.hpp"

namespace Egl
{
    void
    CModel::RefreshWindow()
    {
        if (m_pWindow)
            m_pWindow->Refresh();
    }

    // virtual 
    void 
    CModel::MoveTo(const float nX, const float nY, const float nZ)
    {
        // Set origin
        m_pOrigin.Set(nX, nY, nZ); 

        // Ask window to refresh
        this->RefreshWindow();
    }
        
    // virtual 
    void 
    CModel::MoveTo(const C3DPoint<float> & pPosition)
    {            
        // Set origin
        m_pOrigin = pPosition; 

        // Ask window to refresh
        this->RefreshWindow();
    }
                
    // virtual 
    void 
    CModel::MoveBy(const float nDeltaX, const float nDeltaY, const float nDeltaZ)
    {
        // Set origin
        m_pOrigin.Set(
            m_pOrigin.GetX() + nDeltaX, 
            m_pOrigin.GetY() + nDeltaY, 
            m_pOrigin.GetZ() + nDeltaZ); 

        // Ask window to refresh
        this->RefreshWindow();
    }

    // virtual 
    void 
    CModel::ScaleBy(const float nXScale, const float nYScale, const float nZScale)
    {
        // Set scaling factors
        m_nXScale = nXScale;
        m_nYScale = nYScale;
        m_nZScale = nZScale;

        // Ask window to refresh
        this->RefreshWindow();
    }        
        
    // virtual 
    void 
    CModel::RotateTo(const float nXDegrees, const float nYDegrees, const float nZDegrees)
    {
        m_nXRotation = nXDegrees;
        m_nYRotation = nYDegrees;
        m_nZRotation = nZDegrees;

        // Ask window to refresh
        this->RefreshWindow();
    }

    // virtual 
    void 
    CModel::RotateBy(const float nXDegrees, const float nYDegrees, const float nZDegrees)
    {
        // Change rotation
        m_nXRotation += nXDegrees;
        if (m_nXRotation >= 360)
            m_nXRotation = m_nXRotation - 360;

        m_nYRotation += nYDegrees;
        if (m_nYRotation >= 360)
            m_nYRotation = m_nYRotation - 360;

        m_nZRotation += nZDegrees;
        if (m_nYRotation >= 360)
            m_nYRotation = m_nYRotation - 360;

        // Ask window to refresh
        this->RefreshWindow();
    }                

    // virtual 
    CModel::~CModel(void) throw()
    {
    }

} // namespace Egl