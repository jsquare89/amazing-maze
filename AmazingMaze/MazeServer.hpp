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

        

        /** Move in a given direction within the maze. */
        const bool Move(const MazePtr_t & pMaze, const MazeMoveDirection_e eMoveDirection);

    public:

        /** Constructor. */
        CMazeServer();

        /** Destructor. */
        ~CMazeServer() throw();

        /** Creates a maze. */
        const MazePtr_t CreateMaze(const int nWidth, const int nHeight, const CMaze::MazeEndStyle_e eMazeEndStyle);

    private:

        // Prevent copy ctor and op=
        CMazeServer(const CMazeServer&);
        CMazeServer& operator=(const CMazeServer&);
    };

} // namespace AmazingMaze
