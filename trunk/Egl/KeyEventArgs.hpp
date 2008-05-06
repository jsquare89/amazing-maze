#pragma once

#include "Egl/Common.hpp"
#include "Egl/KeyState.hpp"
#include "Egl/EventArgs.hpp"

namespace Egl
{    
    /** Arguments for Window Key events. */
    class CKeyEventArgs : public CEventArgs
    {
    public:

        /** Constructor. */
        CKeyEventArgs(const int nCharCode, 
                      const bool bSystemKey, 
                      const KeyState_e eKeyState, 
                      const int nX, 
                      const int nY) :
                      m_nCharCode(nCharCode),
                      m_bSystemKey(bSystemKey),
                      m_eKeyState(eKeyState),
                      m_nX(nX),
                      m_nY(nY)
        {
        }

        /** Gets the char code. */
        int GetCharCode() const { return m_nCharCode; }

        /** Gets whether the key is a system key. */
        bool IsSystemKey() const { return m_bSystemKey; }

        /** Gets the state of the key. */
        KeyState_e GetState() const { return m_eKeyState; }

    private:

        /** Key code. */
        int m_nCharCode;

        /** Whether key is system key. */
        bool m_bSystemKey;

        /** State. */
        KeyState_e m_eKeyState;
        
        /** X pos. */
        int m_nX;
        
        /** Y pos. */
        int m_nY;
    };
        
} // namespace Egl

