#pragma once

namespace Egl
{
    /** Key states */
    namespace KeyState
    {   
        enum EnumType_t
        {
            /* Key is pressed. */
            DOWN,

            /** Key is released. */
            UP
        };
    } // namespace KeyState

    /** Typedef for KeyState enum. */
    typedef KeyState::EnumType_t KeyState_e;

} //namespace Egl
