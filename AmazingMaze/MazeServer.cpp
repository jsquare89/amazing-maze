/** 
 * Note: For the time being this file is very much based on the 3D m_mMaze
 * program by Jeff Paquette.
 */
#include <Precompiled.hpp>
#include <memory>
#include "MazeServer.hpp"
#include "Maze.hpp"
#include "MazeRow.hpp"

namespace AmazingMaze
{   
    CMazeServer::CMazeServer()
    {
    }

    CMazeServer::~CMazeServer() throw()
    {
    }

    const MazePtr_t 
    CMazeServer::CreateMaze(const int nWidth, const int nHeight, const CMaze::MazeEndStyle_e eMazeEndStyle)
    {
        return MazePtr_t(new CMaze(nWidth, nHeight, eMazeEndStyle));
    }

    const bool 
    CMazeServer::Move(const MazePtr_t & pMaze, 
                      const MazeMoveDirection_e eMoveDirection)
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
} // namespace AmazingMaze