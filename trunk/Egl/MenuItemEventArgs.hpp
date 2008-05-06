#pragma once

#include "Egl/EventArgs.hpp"

namespace Egl
{
    /** Event args for menu item events. */
    class CMenuItemEventArgs : public CEventArgs
    {
    public:

        /** Constructor. */
        explicit CMenuItemEventArgs(const int nItemId) :
                                    m_nItemId(nItemId)
        {
        }

        /** Gets the menu item id. */
        int GetItemId() const { return m_nItemId; }

    private:

        /** Menu item id. */
         int m_nItemId;
    };
} // namespace Egl

