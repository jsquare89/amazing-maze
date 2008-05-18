#pragma once

#include "Egl/Common.hpp"
#include "Egl/Model.hpp"

namespace AmazingMaze
{
    class CMazeWalker : public Egl::CModel
    {
    public:

        /** Maze walker directions. */
        struct Direction
        {
            /** @internal Enum of directions. */
            enum EnumType_t
            {
                /** NORTH. */
                NORTH,

                /** EAST. */
                EAST,

                /** SOUTH. */
                SOUTH,

                /** WEST. */
                WEST
            };
        };

        /** Enum of maze walker directions. */
        typedef Direction::EnumType_t Direction_e;

    public:

        /** Constructor. */
        CMazeWalker(void) : Egl::CModel(),
                            m_eDirection(Direction::NORTH)
        {
        }

        /** Destructor */
        virtual ~CMazeWalker(void) throw() = 0 {}

        /** Sets the direction that the player is facing. */
        virtual void SetDirection(const Direction_e eDirection)
        {
            // Set maze walker direction
            m_eDirection = eDirection;
        }

        /** Gets the current direction this walker is facing. */
        const Direction_e GetDirection() const { return m_eDirection; }

    private:

        /** Direction this walker is facing. */
        Direction_e m_eDirection;
    };
} // namespace AmazingMaze