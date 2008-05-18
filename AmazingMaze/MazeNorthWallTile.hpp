#pragma once

#include "Egl/Common.hpp"
#include "Egl/Model.hpp"

namespace AmazingMaze
{
    /**
     * One of the north wall tiles of the 3D maze.
     */
    class CMazeNorthWallTile : public Egl::CModel
    {
    public:

        /** Constructor. */
        CMazeNorthWallTile(void);

        /** Destructor */
        virtual ~CMazeNorthWallTile(void) throw();

        // Inherited members
        virtual const float GetWidth() const;
        virtual const float GetHeight() const;
        virtual const float GetDepth() const { return 0; }
        virtual void Draw(void);

    private:

        /** Precompiled id. */
        unsigned int m_nPrecompiledId;
    };
} // namespace Project2