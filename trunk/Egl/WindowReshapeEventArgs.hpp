#pragma once

#include "Egl/EventArgs.hpp"

namespace Egl
{
    /** Arguments for Window Reshape events. */
    class CWindowReshapeEventArgs : public CEventArgs
    {
    public:

        /** Constructor. */
        CWindowReshapeEventArgs(const int nWidth, const int nHeight) : 
                                m_nWidth(nWidth), 
                                m_nHeight(nHeight)
        {
        }

        /** Retrieves width. */
        int GetWidth() const { return m_nWidth; }

        /** Retrieves height. */
        int GetHeight() const { return m_nHeight; }

    private:

        /** Width. */
        int m_nWidth;

        /** Height. */
        int m_nHeight;
    };
    
} // namespace Egl

