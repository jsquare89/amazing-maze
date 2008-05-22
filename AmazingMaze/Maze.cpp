#include "Precompiled.hpp"
#include "Maze.hpp"
#include "MazeRow.hpp"
#include <stack>
#include <sstream>

namespace AmazingMaze
{   
    namespace detail
    {
        /** A node of the m_mMaze (a row and a column). */
        struct node : public std::pair<int, int>
        {
            node () : std::pair<int, int>() {};
            node (int c, int r) : std::pair<int, int>(c,r) {};

            int row () const { return (second); };
            int col () const { return (first); };
        };

        typedef std::stack<node> node_stack;

        /** Retrieves whethera node is valid. */
        inline bool IsValidNode(detail::node& n, const int nWidth, const int nHeight)
        {
            return (n.row() >= 0) && ((n.row() < nHeight) && (n.col() >= 0) && (n.col() < (nWidth)));
        }
        
        /** Retrieves whether a given node has all 4 walls. */
        inline bool HasFourWalls(detail::node& n, const std::vector<CMazeRow*> & rMaze, const int nWidth, const int nHeight)
        {
            // see if this node has four walls
            return (detail::IsValidNode(n, nWidth, nHeight) &&
                rMaze[n.row()]->HasNorthWall(n.col())   &&
                rMaze[n.row()]->HasEastWall(n.col())    &&
                rMaze[n.row()+1]->HasNorthWall(n.col()) &&
                rMaze[n.row()]->HasEastWall(n.col()-1));
        }

        /** Processes a given node while the rMaze is being generated. */
        void ProcessNode(std::vector<CMazeRow*> & rMaze, 
                         const int nWidth, 
                         const int nHeight, 
                         detail::node_stack & sNodes)
        {
            // Get the top node from the stack
            detail::node nTopNode = sNodes.top();        
            sNodes.pop();

            // nodes to process
            std::size_t nNodesToProcess = 0;

            do 
            {
                // examine neighboring cells...if they all have 4 walls then they
                // haven't yet been visited. Any cell that does not have all 4 walls
                // must, by definition, be on a path.
                detail::node nLeft(nTopNode.col() - 1, nTopNode.row());
                detail::node nAbove(nTopNode.col(), nTopNode.row() + 1);
                detail::node nBelow(nTopNode.col(), nTopNode.row() - 1);
                detail::node nRight(nTopNode.col() + 1, nTopNode.row());

                // Vector of neighbor nodes that have 4 walls
                std::vector<detail::node> vNeighboringNodes;

                // consider the 4 neighboring cells
                if (HasFourWalls(nAbove, rMaze, nWidth, nHeight))
                    vNeighboringNodes.push_back(nAbove);

                if (HasFourWalls(nLeft, rMaze, nWidth, nHeight))
                  vNeighboringNodes.push_back(nLeft);
                
                if (HasFourWalls(nRight, rMaze, nWidth, nHeight))
                  vNeighboringNodes.push_back(nRight);
                
                if (HasFourWalls(nBelow, rMaze, nWidth, nHeight))
                  vNeighboringNodes.push_back(nBelow);

                // if any of these nodes haven't been visited then add them to the stack
                // in random order.
                nNodesToProcess = vNeighboringNodes.size();
                if (nNodesToProcess > 0)
                {
                    for (std::size_t i = 0; i < nNodesToProcess - 1; i++)
                    {
                        int nNodeIndex = std::rand() % vNeighboringNodes.size();
                        sNodes.push(nTopNode);
                        vNeighboringNodes.erase(vNeighboringNodes.begin() + nNodeIndex);
                    }

                    // Get the first neighboring node (the next node of the top node)
                    detail::node nNextNode = vNeighboringNodes.front();

                    // Set the right walls depending which node is below the other
                    // and which one is to the left of the other.
                    if (nNextNode == nBelow)
                    {
                        rMaze[nTopNode.row()]->ClearNorthWall(nTopNode.col());
                    }
                    else if (nNextNode == nAbove)
                    {
                        rMaze[nNextNode.row()]->ClearNorthWall(nNextNode.col());
                    }
                    else if (nNextNode == nLeft)
                    {
                        rMaze[nNextNode.row()]->ClearEastWall(nNextNode.col());
                    }
                    else if (nNextNode == nRight)
                    {
                        rMaze[nTopNode.row()]->ClearEastWall(nTopNode.col());
                    }

                    nTopNode = nNextNode;
                }
            } while (nNodesToProcess > 0);
        }
        
    } // namespace detail

    CMaze::CMaze(const int nWidth, 
                 const int nHeight,
                 const MazeEndStyle_e eMazeEndStyle) : 
                 m_nWidth(nWidth),
                 m_nHeight(nHeight),
                 m_mMaze(nHeight),
                 m_bSolved(false),
                 m_nPlayerColumn(0)
    {
        // Creates rows
        int nRowIndex = 0;
        for (Maze_t::iterator it = m_mMaze.begin(); it < m_mMaze.end(); ++it)
        {
            *it = new CMazeRow(nRowIndex++, m_nWidth);
        }

        // by convention, the 0th column and the last row are considered "phantoms" 
        // whose sole purpose is to delinate the bounds of the m_mMaze. [i,0] designates 
        // the entry point while [i,n] is the exit.
        m_mMaze.back()->ClearEastWalls();
        for (Maze_t::iterator it = m_mMaze.begin(); it < m_mMaze.end(); ++it)
        {
            (*it)->ClearNorthWall(0);
        }
        
        // Generate ourselves
        this->Generate();

        // What end style are we creating?
        if (MazeEndStyle::LEFTRIGHT == eMazeEndStyle)
        {
            // Randomly pick a row for the start
            m_nStartRowIndex = std::rand() % (m_nHeight - 1);
            m_mMaze[m_nStartRowIndex]->ClearEastWall(0);
            m_nStartColumn = 0;

            // Randomly pick a row for the end
            m_nEndRowIndex = rand() % (m_nHeight - 1);
            m_mMaze[m_nEndRowIndex]->ClearEastWall(m_nWidth - 1);        
            m_nEndColumn = m_nWidth - 1;
        }
        else 
        {
            // Randomly pick a column for the start
            m_nStartColumn = std::rand() % (m_nWidth - 1) + 1;
            m_mMaze.front()->ClearNorthWall(m_nStartColumn);
            m_nStartRowIndex = 0;

            // Randomly pick a column for the end
            m_nEndColumn = rand() % (m_nWidth - 1) + 1;
            m_mMaze.back()->ClearEastWall(m_nEndColumn);        
            m_nEndRowIndex = m_nHeight - 1;
        }   

        // Set player row and column
        m_nPlayerRowIndex = m_nStartRowIndex;
        m_nPlayerColumn = m_nStartColumn;
    }

    CMaze::CMaze(const CMaze & rhs) :
                 m_nWidth(rhs.m_nWidth),
                 m_nHeight(rhs.m_nHeight),
                 m_mMaze(rhs.m_nHeight),
                 m_nStartRowIndex(rhs.m_nStartRowIndex),
                 m_nStartColumn(rhs.m_nStartColumn),
                 m_nEndRowIndex(rhs.m_nEndRowIndex),
                 m_nEndColumn(rhs.m_nEndColumn),
                 m_bSolved(rhs.m_bSolved),
                 m_nPlayerColumn(rhs.m_nPlayerColumn),
                 m_nPlayerRowIndex(rhs.m_nPlayerRowIndex)
    {
        // Create rows as copies of the rows in the other maze
        Maze_t::const_iterator cit = rhs.m_mMaze.begin();
        for (Maze_t::iterator it = m_mMaze.begin(); it < m_mMaze.end(); ++it, ++cit)
        {
            *it = new CMazeRow(**cit);
        }
    }
        
    CMaze & 
    CMaze::operator=(const CMaze & rhs)
    {
        // Check for self assignment
        if (this == &rhs)
            return *this;

        // Delete our rows
        for (Maze_t::iterator it = m_mMaze.begin(); it < m_mMaze.end(); it++)
            delete *it;

        // Assign
        m_nWidth = rhs.m_nWidth;
        m_nHeight = rhs.m_nHeight;
        m_mMaze.resize(rhs.m_nHeight);
        m_nStartRowIndex = rhs.m_nStartRowIndex;
        m_nStartColumn = rhs.m_nStartColumn;
        m_nEndRowIndex = rhs.m_nEndRowIndex;
        m_nEndColumn = rhs.m_nEndColumn;
        m_bSolved = rhs.m_bSolved;
        m_nPlayerColumn = rhs.m_nPlayerColumn;
        m_nPlayerRowIndex = rhs.m_nPlayerRowIndex;

        // Create our rows as copies of the rows in the other maze
        Maze_t::const_iterator cit = rhs.m_mMaze.begin();
        for (Maze_t::iterator it = m_mMaze.begin(); it < m_mMaze.end(); ++it, ++cit)
        {
            *it = new CMazeRow(**cit);
        }

        // Return ourselves
        return *this;
    }

    CMaze::~CMaze() throw()
    {
        for (Maze_t::iterator it = m_mMaze.begin(); it < m_mMaze.end(); it++)
            delete *it;
    }

    void 
    CMaze::Generate()
    {
        // A stack of nodes for the m_mMaze.
        detail::node_stack  sNodes;

        // Randomly generate the row and column
        // of the initial node.
        int initialNodeRow = std::rand() % (m_nHeight - 1);   // range: 0..m-1
        int initialNodeColumn = std::rand() % (m_nWidth - 1) + 1;  // range: 1..n

        // Add the initial node
        sNodes.push(detail::node(initialNodeColumn, initialNodeRow));

        // Process all nodes
        while (!sNodes.empty())
            detail::ProcessNode(m_mMaze, m_nWidth, m_nHeight, sNodes);            
    }

    void 
    CMaze::SetPlayerRowIndex(const int nPlayerRowIndex) 
    { 
        // Assign
        m_nPlayerRowIndex = nPlayerRowIndex; 

        // Check if we have won
        if ((m_nPlayerRowIndex == m_nEndRowIndex) && (m_nPlayerColumn == m_nEndColumn))
            m_bSolved = true;
    }

        
    void 
    CMaze::SetPlayerColumn(const int nPlayerColumn) 
    { 
        // Assign
        m_nPlayerColumn = nPlayerColumn; 

        // Check if we have won
        if ((m_nPlayerRowIndex == m_nEndRowIndex) && (m_nPlayerColumn == m_nEndColumn))
            m_bSolved = true;
    }

} // namespace AmazingMaze
