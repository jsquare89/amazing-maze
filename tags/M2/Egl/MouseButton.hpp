#pragma once

namespace Egl
{
    /** Key states */
    namespace MouseButton
    {   
        enum EnumType_t
        {
            /* Right mouse button. */
            RIGHT,

            /** Middle mouse button. */
            MIDDLE,

            /** Left mouse button. */
            LEFT
        };
    } // namespace MouseButton

    /** Typedef for MouseButton enum. */
    typedef MouseButton::EnumType_t MouseButton_e;

} //namespace Egl
