#include "Precompiled.hpp"
#include "SphereMazeWalker.hpp"

namespace AmazingMaze
{
    namespace detail
    {
        struct QuadricInitializer
        {
            QuadricInitializer()
            {
                m_pGluQuadric = gluNewQuadric();
                gluQuadricTexture(m_pGluQuadric, GL_TRUE);
            }

            ~QuadricInitializer()
            {
                if (0 != m_pGluQuadric)
                    gluDeleteQuadric(m_pGluQuadric);
            }

            GLUquadric * m_pGluQuadric;
        };

        static QuadricInitializer s_Quadric;

        const float RADIUS = 0.4f; //The radius of the sphere	
	    GLfloat lightColor[] = {0.6f, 0.6f, 0.6f, 1.0f};
	    GLfloat lightPos[] = {.5f * RADIUS, 100.5f * RADIUS, 1.5f * RADIUS, 1.0f};
	    GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
	    GLfloat materialColor[] = {0.5f, 0.5f, 0.6f, 1.0f};
	    //The specular (shiny) component of the material
	    GLfloat materialSpecular[] = {.7f, .7f, .7f, 1.0f};
	    //The color emitted by the material
	    GLfloat materialEmission[] = {0, 0, 0, 1.0f};
    } // namespace detail

    CSphereMazeWalker::CSphereMazeWalker(const float nRadius) :
                                         CMazeWalker(),
                                         m_nRadius(nRadius),
                                         m_nPrecompiledId(3)
    {        
        GLUquadricObj * pQuadric = gluNewQuadric();
        glNewList(m_nPrecompiledId, GL_COMPILE );

        glPushAttrib( GL_ALL_ATTRIB_BITS );

		//Diffuse (non-shiny) light component
        glLightfv(GL_LIGHT3, GL_DIFFUSE, detail::lightColor);
		
        //Specular (shiny) light component
		glLightfv(GL_LIGHT3, GL_SPECULAR, detail::lightColor);
		glLightfv(GL_LIGHT3, GL_POSITION, detail::lightPos);
		glEnable(GL_LIGHT3);

		glMaterialfv(GL_FRONT, GL_SPECULAR, detail::materialSpecular);
		glMaterialfv(GL_FRONT, GL_EMISSION, detail::materialEmission);
		glMaterialf(GL_FRONT, GL_SHININESS, 25); //The shininess parameter

        gluQuadricNormals(pQuadric, GLU_SMOOTH);
        gluQuadricTexture(pQuadric, GLU_TRUE);
		gluSphere(pQuadric, m_nRadius, 3, 20);           

        glPopAttrib();

        glEndList();
        gluDeleteQuadric(pQuadric);
    }

    // virtual
    CSphereMazeWalker::~CSphereMazeWalker(void) throw()
    {        
    }

    // virtual 
    const float 
    CSphereMazeWalker::GetWidth() const
    {
        return 1 * this->GetXScale();
    }

    // virtual 
    const float 
    CSphereMazeWalker::GetHeight() const
    {
        return 1 * this->GetYScale();
    }

    // virtual 
    const float 
    CSphereMazeWalker::GetDepth() const
    {
        return 1 * this->GetZScale();
    }

    // virtual 
    void 
    CSphereMazeWalker::Draw()
    {                
        // Translate and scale the model to the right location.
        // Then draw at 0,0,0 and let the model view matrix do the rest
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        const Egl::C3DPoint<float> & pLocation = this->GetPosition();
        glTranslatef(pLocation.GetX(), pLocation.GetY(), pLocation.GetZ());
        glScalef(this->GetXScale(), this->GetYScale(), this->GetZScale());
        
        // Rotate
        if (0 != this->GetXRotation())
            glRotatef(this->GetXRotation(), 1, 0, 0);

        if (0 != this->GetYRotation())
            glRotatef(this->GetYRotation(), 0, 1, 0);

        if (0 != this->GetZRotation())
            glRotatef(this->GetZRotation(), 0, 0, 1);

        // Draw sphere
        glCallList(m_nPrecompiledId); 
        
        // Restore the original model view matrix
        glPopMatrix();
    }

} // namespace AmazingMaze