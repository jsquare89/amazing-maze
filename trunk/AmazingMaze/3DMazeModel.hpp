#pragma once

#include "Egl/Common.hpp"
#include "Egl/Model.hpp"

namespace AmazingMaze
{
    /** Forward declaration of CMaze. */
    class CMaze;

    /** Type of shared pointer to a maze. */
    typedef boost::shared_ptr<CMaze> MazePtr_t;

    /**
     * 3D model of the maze.
     */
    class C3DMazeModel : public Egl::CModel
    {
    public:

        /** Constructor. */
        explicit C3DMazeModel(const MazePtr_t & pMaze);

        /** Destructor */
        virtual ~C3DMazeModel(void) throw();

        /** Set wall texture. */
        void SetWallTexture(const Egl::TexturePtr_t & pWallTexture) { m_pWallTexture = pWallTexture; }
                               
        /** Set floor texture. */
        void SetFloorTexture(const Egl::TexturePtr_t & pFloorTexture) { m_pFloorTexture = pFloorTexture; }

        // Inherited members
        virtual const float GetWidth() const;
        virtual const float GetHeight() const;
        virtual const float GetDepth() const { return 0; }
        virtual void Draw(void);

    private:

        /** North wall tile. */
        Egl::ModelPtr_t m_pNorthWallTile;

        /** East wall tile. */
        Egl::ModelPtr_t m_pEastWallTile;

        /** Maze. */
        MazePtr_t m_pMaze;        

        /** Wall texture. */
        Egl::TexturePtr_t m_pWallTexture;

        /** Floor texture. */
        Egl::TexturePtr_t m_pFloorTexture;
    };
} // namespace Project2