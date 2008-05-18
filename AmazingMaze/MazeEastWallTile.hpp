#pragma once

#include "Egl/Common.hpp"
#include "Egl/Model.hpp"

namespace AmazingMaze
{
    /**
     * One of the east wall tiles of the 3D maze.
     */
    class CMazeEastWallTile : public Egl::CModel
    {
    public:

        /** Constructor. */
        CMazeEastWallTile(void);

        /** Destructor */
        virtual ~CMazeEastWallTile(void) throw();

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