#pragma once

#include "Egl/KeyState.hpp"

namespace Egl
{
    namespace MouseButton
    {        
        namespace detail
        {
            /** Convert a CPW mouse button into a DGL mouse button. */
            Egl::MouseButton_e FromCpw(const int nCpwMouseButton)
            {
                // Convert button
                switch (nCpwMouseButton)
                {
                    case CPW_BUTTON_LEFT:   return MouseButton::LEFT;
                    case CPW_BUTTON_MIDDLE: return MouseButton::MIDDLE;
                    case CPW_BUTTON_RIGHT: 
                    default:                return MouseButton::RIGHT;
                }
            }

            /** Convert a DGL mouse button into a CPW mouse button. */
            const int ToCpw(Egl::MouseButton_e eMouseButton)
            {
                // Convert button
                switch (eMouseButton)
                {
                    case MouseButton::LEFT:   return CPW_BUTTON_LEFT;
                    case MouseButton::MIDDLE: return CPW_BUTTON_MIDDLE;
                    case MouseButton::RIGHT: 
                    default:                  return CPW_BUTTON_RIGHT;
                }
            }
        }
    } // namespace KeyState
} //namespace Egl
