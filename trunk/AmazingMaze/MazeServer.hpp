#pragma once

#include <boost/shared_ptr.hpp>
#include "Maze.hpp"

namespace AmazingMaze
{   
    /** Maze game server. */
    class CMazeServer
    { 
    public:
  
        /** Possible motions inside the maze. */
        struct MazeMoveDirection
        {
            /** @internal Internal enum. */
            enum EnumType_t
            {
                /** Left. */
                LEFT,

                /** Up. */
                UP,

                /** Right. */
                RIGHT,

                /** Down. */
                DOWN
            };
        };
        
        /** Enum of possible motions the player can do. */
        typedef MazeMoveDirection::EnumType_t MazeMoveDirection_e;

        /** Type of maze solution vector. */
        typedef std::vector<MazeMoveDirection_e> MazeSolution_t;

    public:

        /** Constructor. */
        CMazeServer();

        /** Destructor. */
        ~CMazeServer() throw();

        /** Creates a maze. */
        const MazePtr_t CreateMaze(const int nWidth, const int nHeight, const CMaze::MazeEndStyle_e eMazeEndStyle) const;

        /** Move in a given direction within the maze. */
        const bool Move(const MazePtr_t & pMaze, const MazeMoveDirection_e eMoveDirection) const;

        /** Solve the maze and returns a list of steps that when executed put the player at the end of the maze. */
        const MazeSolution_t Solve(const MazePtr_t pMaze) const;

        /** Get the direction oposite to a given direction. */
        const MazeMoveDirection_e GetOpositeDirection(const MazeMoveDirection_e eDirection) const;

    private:

        /** Solve the maze and returns a list of steps that when executed put the player at the end of the maze. */
        const bool SolveMaze(const MazePtr_t & pMaze, 
                             MazeSolution_t & rSolution, 
                             const MazeMoveDirection_e eLastDirection, 
                             const bool bFirst) const;

    private:

        // Prevent copy ctor and op=
        CMazeServer(const CMazeServer&);
        CMazeServer& operator=(const CMazeServer&);
    };

} // namespace AmazingMaze
