#pragma once

#include "Egl/KeyState.hpp"

namespace Egl
{
    /** Key states */
    namespace KeyState
    {        
        namespace detail
        {
            /** Convert a CPW key state into a DGL key state. */
            Egl::KeyState_e FromCpw(const int nCpwKeyState)
            {
                // Convert state
                switch (nCpwKeyState)
                {
                    case CPW_KEYMOD_DOWN: return KeyState::DOWN;
                    case CPW_KEYMOD_UP: 
                    default:              return KeyState::UP;
                }
            }
        }
    } // namespace KeyState
} //namespace Egl
