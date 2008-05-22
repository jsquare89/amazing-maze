/** 
 * Note: For the time being this file is very much based on the 3D m_mMaze
 * program by Jeff Paquette.
 */
#include <Precompiled.hpp>
#include <memory>
#include "MazeServer.hpp"
#include "Maze.hpp"
#include "MazeRow.hpp"
#include <boost/scoped_ptr.hpp>

namespace AmazingMaze
{   
    CMazeServer::CMazeServer()
    {
    }

    CMazeServer::~CMazeServer() throw()
    {
    }

    const MazePtr_t 
    CMazeServer::CreateMaze(const int nWidth, 
                            const int nHeight, 
                            const CMaze::MazeEndStyle_e eMazeEndStyle) const
    {
        return MazePtr_t(new CMaze(nWidth, nHeight, eMazeEndStyle));
    }

    const bool 
    CMazeServer::Move(const MazePtr_t & pMaze, 
                      const MazeMoveDirection_e eMoveDirection) const
    {
        // Check arguments
        if (!pMaze)
            throw std::invalid_argument("null pMaze.");

        // Which direction do we want to move to?
        switch (eMoveDirection)
        {
            // LEFT
            case MazeMoveDirection::LEFT:
            {
                // If the position to our left (same row) is valid
                // and the position to our left doesn't have an east wall
                // (i.e. same as our position having a west wall)
                // then allow the move.
                if (pMaze->IsValidColumn(pMaze->GetPlayerColumn() - 1) && 
                    !pMaze->GetPlayerRow().HasEastWall(pMaze->GetPlayerColumn() - 1))
                {
                    pMaze->SetPlayerColumn(pMaze->GetPlayerColumn() - 1);
                    return true;
                }
            }
            break;

            // UP
            case MazeMoveDirection::UP:
            {
                // If the position above us (same column) is valid
                // and our position doesn't have a north wall
                // then allow the move
                if (pMaze->IsValidRowIndex(pMaze->GetPlayerRowIndex() - 1) && 
                    !pMaze->GetPlayerRow().HasNorthWall(pMaze->GetPlayerColumn()))
                {
                    pMaze->SetPlayerRowIndex(pMaze->GetPlayerRowIndex() - 1);
                    return true;
                }
            }
            break;

            // RIGHT
            case MazeMoveDirection::RIGHT:
            {
                // If the position to our right (same row) if valid and
                // our position doesn't have an east wall then
                // allow the move.
                if (pMaze->IsValidColumn(pMaze->GetPlayerColumn() + 1) && 
                    !pMaze->GetPlayerRow().HasEastWall(pMaze->GetPlayerColumn()))
                {
                    pMaze->SetPlayerColumn(pMaze->GetPlayerColumn() + 1);
                    return true;
                }
            }
            break;

            // DOWN
            case MazeMoveDirection::DOWN:
            {
                // If the position below us (same column) is valid
                // and the position below us doesn't have a north wall
                // (same as our position having a south wall) then
                // allow the move
                if (pMaze->IsValidRowIndex(pMaze->GetPlayerRowIndex() + 1) && 
                    !pMaze->GetRowAt(pMaze->GetPlayerRowIndex() + 1).HasNorthWall(pMaze->GetPlayerColumn()))
                {
                    pMaze->SetPlayerRowIndex(pMaze->GetPlayerRowIndex() + 1);
                    return true;
                }
            }
            break;
        }

        // Don't allow the move
        return false;
    }

    const CMazeServer::MazeSolution_t 
    CMazeServer::Solve(const MazePtr_t pMaze) const
    {
        // Check arguments
        if (!pMaze)
            throw std::invalid_argument("null pMaze.");

        // Create solutions vector
        MazeSolution_t vSolutionSteps;

        // Check the maze is not already solved
        if (pMaze->IsSolved())
            return vSolutionSteps;

        // Make a copy of the maze
        MazePtr_t pUnsolvedMaze(new CMaze(*pMaze));

        // Recursively solve the maze
        this->SolveMaze(pUnsolvedMaze, vSolutionSteps, 
            MazeMoveDirection::UP, true);

        // Reverse solutions
        std::reverse(vSolutionSteps.begin(), vSolutionSteps.end());

        // Return solutions
        return vSolutionSteps;        
    }

    const bool
    CMazeServer::SolveMaze(const MazePtr_t & pMaze, 
                           MazeSolution_t & rSolution,
                           const MazeMoveDirection_e eLastDirection,
                           const bool bFirst) const
    {
        // Check if the maze is solved
        if (pMaze->IsSolved())
            return true;

        // Array of posible directions
        MazeMoveDirection_e aDirections[4] = 
        { 
            MazeMoveDirection::UP,
            MazeMoveDirection::LEFT,
            MazeMoveDirection::DOWN,
            MazeMoveDirection::RIGHT
        };

        // Check the direction we have to avoid
        MazeMoveDirection_e eAvoidDirection = 
            this->GetOpositeDirection(eLastDirection);

        // Try every direction
        for (int i = 0; i < 4; ++i)
        {
            // Check we don't go back to the previous one
            // unless this is the first time we run
            if (bFirst || (eAvoidDirection != aDirections[i]))
            {
                // Try going up
                if (this->Move(pMaze, aDirections[i]))
                {
                    // Check if we can solve from here
                    if (this->SolveMaze(pMaze, rSolution, aDirections[i], false))
                    {
                        // We could solve, so push step into solution
                        rSolution.push_back(aDirections[i]);
                        return true;
                    }
                    else
                    {
                        // We could not solve, undo
                        this->Move(pMaze, 
                            this->GetOpositeDirection(aDirections[i]));
                    }
                }
            }
        }

        // We could not solve the maze going this way
        return false;
    }

    const CMazeServer::MazeMoveDirection_e 
    CMazeServer::GetOpositeDirection(const MazeMoveDirection_e eDirection) const
    {
        // Switch on the direction
        switch (eDirection)
        {
            // Up
            case MazeMoveDirection::UP:
                return MazeMoveDirection::DOWN;

            // Down
            case MazeMoveDirection::DOWN:
                return MazeMoveDirection::UP;

            // Left
            case MazeMoveDirection::LEFT:
                return MazeMoveDirection::RIGHT;

            // Right
            case MazeMoveDirection::RIGHT:
                return MazeMoveDirection::LEFT;

            // Other?
            default:
                throw std::invalid_argument("Unknown maze move direction.");
        }        
    }

} // namespace AmazingMaze