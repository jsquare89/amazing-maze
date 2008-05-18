#pragma once

#include <vector>
#include <boost/shared_ptr.hpp>

namespace AmazingMaze
{   
    /** Forward declaration of CMazeRow. */
    class CMazeRow;

    /** Maze representation. */
    class CMaze
    {
    private:

        /** Type of maze internal representation. */
        typedef std::vector<CMazeRow*> Maze_t;

    public:

        /** Type of row iterator. */
        typedef Maze_t::const_iterator RowIterator_t;

        /** Possible maze start/end styles. */
        struct MazeEndStyle
        {
            /** @internal. Internal enum. */
            enum EnumType_t
            {
                /** Exits left and right. */
                LEFTRIGHT,

                /** Exts on top and bottom. */
                TOPBOTTOM
            };
        };

        /** Enum of possible maze start/end styles. */
        typedef MazeEndStyle::EnumType_t MazeEndStyle_e;

    public:

        /** Destructor. */
        ~CMaze() throw();

        /** Gets an iterator to the beginning row of this maze. */
        const RowIterator_t GetRowsBegin() const { return m_mMaze.begin(); }

        /** Gets an iterator to the end row in this maze. */
        const RowIterator_t GetRowsEnd() const { return m_mMaze.end(); }
        
        /** Gets a row. */
        const CMazeRow & GetRowAt(const int nIndex) const { return *m_mMaze[nIndex]; }

        /** Gets the width of this maze. */
        const int GetWidth() const { return m_nWidth; }

        /** Gets the height of this maze. */
        const int GetHeight() const { return m_nHeight; }
        
        /** Gets the row where the maze player starts. */
        const int GetStartRowIndex() { return m_nStartRowIndex; }

        /** Gets the column where the maze player starts. */
        const int GetStartColumn() { return m_nStartColumn; }

        /** Gets the row where the maze player ends. */
        const int GetEndRowIndex() { return m_nEndRowIndex; }

        /** Gets the column where the maze player ends. */
        const int GetEndColumn() { return m_nEndColumn; }

        /** Whether this maze is solved. */
        const bool IsSolved() const { return m_bSolved; }

        /** Retrieves the current player row index. */
        const int GetPlayerRowIndex() const { return m_nPlayerRowIndex; }

        /** Retrieves the current player row. */
        const CMazeRow & GetPlayerRow() const { return *m_mMaze[m_nPlayerRowIndex]; }

        /** Retrieves the current player column. */
        const int GetPlayerColumn() const { return m_nPlayerColumn; }

        /** Retrieves whether a column is valid. */
        const bool IsValidColumn(const int nColumn) const { return (nColumn >= 0) && (nColumn < m_nWidth); }

        /** Retrieves whether a row index is valid. */
        const bool IsValidRowIndex(const int nRowIndex) const { return (nRowIndex >= 0) && (nRowIndex < m_nHeight); }

    private:

        /** Constructor. */
        CMaze(const int nWidth, int const nHeight, const MazeEndStyle_e eMazeEndStyle);

        /** Generates the maze. */
        void Generate();

        /** Sets this maze as solved. */
        void MarkSolved() { m_bSolved = true; }

        /** Sets the new player row. */
        void SetPlayerRowIndex(const int nPlayerRowIndex) { m_nPlayerRowIndex = nPlayerRowIndex; }

        /** Sets the new player column index. */
        void SetPlayerColumn(const int nPlayerColumn) { m_nPlayerColumn = nPlayerColumn; }

        // Prevent copy construction and op=
        CMaze(const CMaze&);
        CMaze & operator=(const CMaze&);

    private:

        /** Maze. */
        Maze_t m_mMaze;

        /** The width of the m_mMaze. */
        int  m_nHeight;

        /** The height of the m_mMaze. */
        int  m_nWidth;
        
        /** Row index of start position. */
        int m_nStartRowIndex;

        /** Column of start position. */
        int m_nStartColumn;

        /** Row index of end position. */
        int m_nEndRowIndex;

        /** Column of end position. */
        int m_nEndColumn;

        /** Whether this maze is solved. */
        bool m_bSolved;

        /** Current player column. */
        int m_nPlayerColumn;

        /** Current player row index. */
        int m_nPlayerRowIndex;

    private:

        /** Maze server can create us. */
        friend class CMazeServer;
    };

    /** Type of Maze shared pointer. */
    typedef boost::shared_ptr<CMaze> MazePtr_t;
} // namespace AmazingMaze
