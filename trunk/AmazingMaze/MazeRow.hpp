#pragma once

#include <vector>

namespace AmazingMaze
{    
    /**
     * Describes a single row in terms of its north walls and its east walls.
     * A wall N is present if the bit[N] is SET. Inspired on the 3D maze
     * program by Jeff Paquette.
     */
    class CMazeRow
    {
    private:

        /** The type of wall vector for this row. */
        typedef std::vector<bool> WallVector_t;

    public:

        /** Copy constructor. */
        CMazeRow(const CMazeRow & rhs) : 
                 m_vNorthWalls(rhs.m_vNorthWalls),
                 m_vEastWalls(rhs.m_vEastWalls),
                 m_nIndex(rhs.m_nIndex)
        {
        }

        /** Operator=. */
        CMazeRow & operator=(const CMazeRow & rhs)
        {
            // Check for self assignment
            if (this == &rhs)
                return *this;

            // Assign
            m_vNorthWalls = rhs.m_vNorthWalls;
            m_vEastWalls = rhs.m_vEastWalls;
            m_nIndex = rhs.m_nIndex;

            // Return ourselves
            return *this;
        }

        /** Wall iterator. */
        typedef WallVector_t::const_iterator WallIterator_t;

        /** Retrieves the beginning iterator of the north walls. */
        const WallIterator_t GetNorthWallsBegin() const { return m_vNorthWalls.begin(); }

        /** Retrieves the end iterator of the north walls. */
        const WallIterator_t GetNorthWallsEnd() const { return m_vNorthWalls.end(); }

        /** Retrieves the beginning iterator of the east walls. */
        const WallIterator_t GetEastWallsBegin() const { return m_vEastWalls.begin(); }

        /** Retrieves the end iterator of the east walls. */
        const WallIterator_t GetEastWallsEnd() const { return m_vEastWalls.end(); }

        /** Gets whether a given north wall exists. */
        bool HasNorthWall(const WallVector_t::size_type nIndex) const { return m_vNorthWalls[nIndex]; }

        /** Sets whether a given north wall exists. */
        void SetNorthWall(const WallVector_t::size_type nIndex) { m_vNorthWalls[nIndex] = true; }

        /** Sets whether a given north wall exists. */
        void ClearNorthWall(const WallVector_t::size_type nIndex) { m_vNorthWalls[nIndex] = false; }

        /** Gets whether a given east wall exists. */
        bool HasEastWall(const WallVector_t::size_type nIndex) const { return m_vEastWalls[nIndex]; }

        /** Sets whether a given east wall exists. */
        void SetEastWall(const WallVector_t::size_type nIndex) { m_vEastWalls[nIndex] = true; }

        /** Sets whether a given east wall exists. */
        void ClearEastWall(const WallVector_t::size_type nIndex) { m_vEastWalls[nIndex] = false; }

        /** Sets every north wall in this row. */
        void SetNorthWalls() { std::fill(m_vNorthWalls.begin(), m_vNorthWalls.end(), true); }

        /** Sets every east wall in this row. */
        void SetEastWalls() { std::fill(m_vEastWalls.begin(), m_vEastWalls.end(), true); }

        /** Clears every north wall in this row. */
        void ClearNorthWalls() { std::fill(m_vNorthWalls.begin(), m_vNorthWalls.end(), false); }

        /** Clears every east wall in this row. */
        void ClearEastWalls() { std::fill(m_vEastWalls.begin(), m_vEastWalls.end(), false); }

        /** Gets the index of this row. */
        const int GetIndex() const { return m_nIndex; }

        /** Destructor. */
        ~CMazeRow() throw() {}        

    private:

        /** Constructor. */
        explicit CMazeRow(const int nIndex, const size_t nLength) : 
            m_vNorthWalls(nLength), 
            m_vEastWalls(nLength) ,
            m_nIndex(nIndex)
       {
           // initialize all walls as present
            this->SetNorthWalls();
            std::fill_n(m_vEastWalls.begin(), nLength, true);
       }

    private:

        /** North walls for this row. */
        WallVector_t m_vNorthWalls;

        /** East walls for this row. */
        WallVector_t m_vEastWalls;     

        /** Index. */
        int m_nIndex;

    private:

        /** Maze is our friend. */
        friend class CMaze;
    };

} // namespace AmazingMaze
