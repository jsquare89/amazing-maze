#pragma once

#include "Egl/Common.hpp"
#include "MazeWalker.hpp"

namespace AmazingMaze
{
    class CSphereMazeWalker : public CMazeWalker
    {
    public:

        /** Constructor. */
        CSphereMazeWalker(const float nRadius);

        /** Destructor */
        virtual ~CSphereMazeWalker(void) throw();

        // Inherited members
        virtual const float GetWidth() const;
        virtual const float GetHeight() const;
        virtual const float GetDepth() const;
        virtual void Draw(void);
        
    private:

        /** Radius. */
        float m_nRadius;

        /** Precompiled id. */
        unsigned int m_nPrecompiledId;
    };
} // namespace AmazingMaze