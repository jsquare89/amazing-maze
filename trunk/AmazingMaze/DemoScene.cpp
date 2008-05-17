#include "Precompiled.hpp"
#include <boost/bind.hpp>
#include "DemoScene.hpp"	
#include <locale>
#include "Egl/Context.hpp"
#include "Egl/Texture.hpp"
#include "Egl/Image.hpp"
#include "Egl/Timer.hpp"
#include "Egl/Camera.hpp"
#include "Egl/Light.hpp"
#include "Egl/LightingControl.hpp"
#include "Egl/ImageButton.hpp"
#include "Egl/Menu.hpp"
#include "Egl/Window.hpp"
#include "Egl/SceneManager.hpp"
#include "Maze.h"
#include "MazeMusic.hpp"

#include <GL/glut.h>

namespace AmazingMaze
{
    namespace detail
    {        
        const uint32 cu32RatID_2d    = 1;
        const uint32 cu32RatID_3d    = 2;
        const uint32 cu32NorthWallID = 3;
        const uint32 cu32EastWallID  = 4;

        static GLfloat theta[] = {0.0,0.0,0.0};
        static GLint axis = 2;
        static GLdouble viewer[]= {0.0, 0.0, 5.0}; /* initial viewer location */

        static GLfloat near_clip = 1;
        static GLfloat far_clip = 400.0;
        static GLfloat m_nFieldOfView = 65;
        static bool show_2d = false;
        static bool rats_view = true;

        GLfloat camX = 7., camY = 15.5, camZ = 8., 
		        camLookX = 23., camLookY = -400., camLookZ = 8., 
		        camUpX = 0., camUpY = 1., camUpZ = 0.;

        GLfloat east_vertices[][3] = {
          {-0.05f, 0, 0}, { 0.05f, 0, 0},
          { 0.05f, 0, 1}, {-0.05f, 0, 1},
          {-0.05f, 1, 0}, { 0.05f, 1, 0},
          { 0.05f, 1, 1}, {-0.05f, 1, 1},
        };

        GLfloat north_vertices[][3] = {
          {0, 0, -0.05f}, {1, 0, -0.05f},
          {1, 0,  0.05f}, {0, 0,  0.05f},
          {0, 1, -0.05f}, {1, 1, -0.05f},
          {1, 1,  0.05f}, {0, 1,  0.05f},
        };

        GLfloat normals[][3] = {
          {-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
          {1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0}, 
          {1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}
        };

        GLfloat colors[][3] = {
          {0.0,0.0,0.0},{1.0,0.0,0.0},
          {1.0,1.0,0.0}, {0.0,1.0,0.0}, {0.0,0.0,1.0}, 
          {1.0,0.0,1.0}, {1.0,1.0,1.0}, {0.0,1.0,1.0}
        };

		const float RADIUS = 0.4f; //The radius of the sphere	
		GLfloat lightColor[] = {0.6f, 0.6f, 0.6f, 1.0f};
		GLfloat lightPos[] = {.5f * RADIUS, 100.5f * RADIUS, 1.5 * RADIUS, 1.0f};
		GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
		GLfloat materialColor[] = {0.5f, 0.5f, 0.6f, 1.0f};
		//The specular (shiny) component of the material
		GLfloat materialSpecular[] = {.7, .7, .7, 1.0f};
		//The color emitted by the material
		GLfloat materialEmission[] = {0, 0, 0, 1.0f};

        /** Draws a polygon via list of vertices */
        void polygon(GLfloat v[][3], int a, int b, int c , int d)
        {          
            glBegin(GL_POLYGON);                
                glNormal3fv(normals[a]);
                glTexCoord2f(0, 1);
                glVertex3fv(v[a]);
                glNormal3fv(normals[b]);
                glTexCoord2f(0, 0);
                glVertex3fv(v[b]);
                glNormal3fv(normals[c]);
                glTexCoord2f(1, 0);
                glVertex3fv(v[c]);
                glNormal3fv(normals[d]);
                glTexCoord2f(1, 1);
                glVertex3fv(v[d]);
            glEnd();
        }

        void walls_init()
        {
            glNewList( cu32NorthWallID, GL_COMPILE );
            polygon(north_vertices,0,1,2,3);
            polygon(north_vertices,1,5,6,2);
            polygon(north_vertices,4,5,6,7);
            polygon(north_vertices,0,4,7,3);
            polygon(north_vertices,0,1,5,4);
            polygon(north_vertices,3,2,6,7);

            glEndList();

            glNewList( cu32EastWallID, GL_COMPILE );

            polygon(east_vertices,0,1,2,3);
            polygon(east_vertices,1,5,6,2);
            polygon(east_vertices,4,5,6,7);
            polygon(east_vertices,0,4,7,3);
            polygon(east_vertices,0,1,5,4);
            polygon(east_vertices,3,2,6,7);

            glEndList();
        }

        /** Draws the north wall of a given maze row. */
        int draw_north_wall(const bool present, pair_int * loc)
          {
            if (present)
            {
              glColor3f(0.0, 0, 1.00);
              glPushMatrix();
              glTranslatef((float)loc->first + 0.5f, 0.0f, (float)loc->second - 0.5f);
              glCallList(cu32NorthWallID);
              glPopMatrix();
            }

            loc->first++;

            return(0);
          }

        /** Draws the east wall of a given maze row. */
        int draw_east_wall(const bool present, pair_int * loc)
          {
            if (present)
            {
              glColor3f(1.0, 0, 0);

              glPushMatrix();
              glTranslatef((float)loc->first + 1.5f, 0.0, (float)loc->second - 0.5f);
              glCallList(cu32EastWallID);
              glPopMatrix();
            }

            loc->first++;

            return(0);
          }        

        /** Draws a single row of the maze in terms of its north and east walls. */
        int draw_row(const maze_row * row, int * r)
        {
        
            pair_int p1(0,*r);
            for (maze_row::walls::const_iterator cit = row->north_walls.begin();
                 cit != row->north_walls.end(); ++cit)
            {
                draw_north_wall(*cit, &p1);
            }

            pair_int p2(0,*r);
            for (maze_row::walls::const_iterator cit = row->east_walls.begin();
                 cit != row->east_walls.end(); ++cit)
            {
                draw_east_wall(*cit, &p2);
            }
            (*r)++;

            return (0);
        }

        void rat_init()
        {
            glNewList( cu32RatID_2d, GL_COMPILE );

            glPushAttrib( GL_ALL_ATTRIB_BITS );
            glColor3f( 1.0, 1.0, 0.5 );

            glBegin( GL_POLYGON );
            {
                glVertex2d( 0.4375,   0.0);
                glVertex2d( 0.25, -0.25 );
                glVertex2d( -0.3, -0.25 );
                glVertex2d( -0.375,  0 );
                glVertex2d( -0.3,  0.25 );
                glVertex2d( 0.25, 0.25 );
            }
            glEnd();

            glPopAttrib();

            glEndList();

            glNewList( cu32RatID_3d, GL_COMPILE );

            glPushAttrib( GL_ALL_ATTRIB_BITS );

			//Diffuse (non-shiny) light component
			glLightfv(GL_LIGHT3, GL_DIFFUSE, lightColor);
			//Specular (shiny) light component
			glLightfv(GL_LIGHT3, GL_SPECULAR, lightColor);
			glLightfv(GL_LIGHT3, GL_POSITION, lightPos);
			glEnable(GL_LIGHT3);

			glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
			glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
			glMaterialf(GL_FRONT, GL_SHININESS, 25); //The shininess parameter

			glutSolidSphere(RADIUS, 3, 20);

            glPopAttrib();

            glEndList();
        }

        void draw_floor(int nMazeWidth, int nMazeHeight, const Egl::TexturePtr_t & pTexture)
        {
            // red floor
            glPushAttrib( GL_ALL_ATTRIB_BITS );
            glColor3f(0,0,0);
            glPushMatrix();

            glTranslatef(1.45, 0.0, -0.5);

            pTexture->Bind();

			//Binds textures down the z-axis
			for(int i = 0; i < (nMazeHeight/2)-1; i++){
				//Binds textures down the x-axis
				for(int j = 0; j < nMazeWidth/2; j++){
            
		        glBegin(GL_QUADS);
			        glTexCoord2f(0, 1);
				    glVertex3f(0.0, 0.0f, 0.0);

					glTexCoord2f(0, 0);
	                glVertex3f(2.0, 0.0f, 0.0);

		            glTexCoord2f(1, 0);
			        glVertex3f(2.0, 0.0f, 2.0);

				    glTexCoord2f(1, 1);
					glVertex3f(0.0, 0.0f, 2.0);
	            glEnd();
				glTranslatef(2.0, 0.0, 0.0);
				}
				glTranslatef(1.0 - nMazeWidth, 0.0, 2.0);
			}
			//Last row of maze is only the left half of the floor texture
			for(int i = 0; i < nMazeWidth/2; i++){
		        glBegin(GL_QUADS);
			        glTexCoord2f(0, 1);
				    glVertex3f(0.0, 0.0f, 0.0);

					glTexCoord2f(0, 0);
	                glVertex3f(2.0, 0.0f, 0.0);

		            glTexCoord2f(0.5, 0);
			        glVertex3f(2.0, 0.0f, 1.0);

				    glTexCoord2f(0.5, 1);
					glVertex3f(0.0, 0.0f, 1.0);
	            glEnd();
				glTranslatef(2.0, 0.0, 0.0);
			}
           
			pTexture->UnBind();

            glPopMatrix();
            glPopAttrib();
        }

        void draw_rat(const node& rat_loc, const CMazeWalker::direction direction)
        {
            GLfloat angle = 0;
            glPushMatrix();

            switch(direction)
            {
                case CMazeWalker::north:
                    if (rats_view)
                        angle = -90.0;
                    else
                        angle = 90;
                break;

                case CMazeWalker::south:
                    if (rats_view)
                      angle = 90.0;
                    else
                      angle = -90.0;
                break;
                
                case CMazeWalker::east:
                    angle = 0.0;
                break;

                case CMazeWalker::west:
                    angle = 180.0;
                break;
            }

            glTranslatef(rat_loc.first + 1, 0.5, rat_loc.second);
            glRotatef(angle, 0, 1, 0);
            glCallList(cu32RatID_3d);                        

            glPopMatrix();
        }

    } // namespace detail

    CDemoScene::CDemoScene(const Egl::WindowPtr_t & pWindow, 
                           const Egl::SceneManagerPtr_t & pSceneManager, 
                           const Egl::CameraPtr_t & pCamera) : 
                           Egl::CScene(pWindow, pSceneManager),
                           m_pCamera(pCamera),
                           m_pBackgroundTexture(pWindow->GetContext()->LoadTexture("textures/floor-cracks.bmp")),
                           m_pWallsTexture(pWindow->GetContext()->LoadTexture("textures/wall-rough.bmp")),
                           m_pContextMenu(),
                           m_pMaze(new CMaze(15, 20)),
                           m_pMazeWalker(new CMazeWalker(*m_pMaze)),
                           m_nFieldOfView(65),
                           m_vLights(),
                           m_pWalkerTimer(pWindow->GetContext()->CreateTimer()),
                           m_vWalkerSteps(),
                           m_citWalkerStep(),
                           m_pMazeMusic(new CMazeMusic("sounds\\FX\\Cheers.mp3"))
    {
        // We want to listen to load an unload events fired by us
        this->Load += boost::bind(&CDemoScene::HandleLoad, this, _1, _2);
        this->Unload += boost::bind(&CDemoScene::HandleUnload, this, _1, _2);        
        m_pWalkerTimer->Tick += boost::bind(&CDemoScene::HandleTimerTick, this, _1, _2);

        // Initialize rat
        detail::rat_init();
        
        // Initialize walls
        detail::walls_init();

        // Create context menu
        m_pContextMenu = pWindow->GetContext()->CreateMenu();
        m_pContextMenu->AddItem("Show help window", CDemoScene::MENU_ITEM_ID_HELP, false);        
        m_pContextMenu->AddItem("Back to main screen", CDemoScene::MENU_ITEM_ID_QUIT, false);                

        // TODO, reorganize this so it is not soooo long. maybe not even hardcoded
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('l');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('r');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('l');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('r');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('r');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('l');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('r');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('l');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('l');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('l');
    
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('r');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('r');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('r');
        m_vWalkerSteps.push_back('u');        
        m_vWalkerSteps.push_back('l');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('l');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');               
        m_vWalkerSteps.push_back('l');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('r');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('r');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('r');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('l');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('l');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('r');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('r');

        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('r');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('l');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('r');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('r');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('l');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('l');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('r');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('r');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('l');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('l');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('l');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('r');

        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('r');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('l');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('l');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('r');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('l');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('r');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('l');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('l');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('l');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('r');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('r');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('l');

        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('r');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('r');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('u');
        m_vWalkerSteps.push_back('l');
    }

    CDemoScene::~CDemoScene(void)
    {
    }

    void
    CDemoScene::HandleDraw(const Egl::CWindow &, Egl::CEventArgs &)
    {
        // Clear the background
        glMatrixMode(GL_MODELVIEW);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();

        glTranslatef(-1,0,0);
        glScalef(.8, .8, .8);
        glColor3f(0.0, 0.0, 0.0);
        int r = 0;

        m_pWallsTexture->Bind();
        for (CMaze::row_iterator cit = m_pMaze->begin();
             cit != m_pMaze->end(); ++cit)
        {
            detail::draw_row(*cit, &r);
        }
        m_pWallsTexture->UnBind();

        detail::draw_rat(m_pMazeWalker->position(), m_pMazeWalker->facing());
		detail::draw_floor(m_pMaze->width()/*edit*//*edit*/, m_pMaze->height()/*edit*//*edit*/, m_pBackgroundTexture);
		
        glPopMatrix();

        // Flush all actions
        glFlush();

        // Repaint screen with content of back buffer
        this->GetWindow()->SwapBuffers();
    }

    void 
    CDemoScene::HandleKey(const Egl::CWindow &, Egl::CKeyEventArgs & rArgs)
    {
        // Make sure we only handle this event if
        // this scene is active
        if (this->IsActive())
        {
            // Non system key and key being released?
            if ((Egl::KeyState::DOWN == rArgs.GetState()))
            {
                // Regular key?
                if (!rArgs.IsSystemKey())
                {
                    switch (rArgs.GetCharCode())
                    {
                        case 'X':
                            m_pCamera->MoveTo(m_pCamera->GetPosition().GetX() + 1, 
                                m_pCamera->GetPosition().GetY(), 
                                m_pCamera->GetPosition().GetZ());
                        break;

                        case 'x':
                            m_pCamera->MoveTo(m_pCamera->GetPosition().GetX() - 1, 
                                m_pCamera->GetPosition().GetY(), 
                                m_pCamera->GetPosition().GetZ());
                        break;

                        case 'Y':
                            m_pCamera->MoveTo(m_pCamera->GetPosition().GetX(), 
                                m_pCamera->GetPosition().GetY() + 1, 
                                m_pCamera->GetPosition().GetZ());
                        break;

                        case 'y':
                            m_pCamera->MoveTo(m_pCamera->GetPosition().GetX(), 
                                m_pCamera->GetPosition().GetY() - 1, 
                                m_pCamera->GetPosition().GetZ());
                        break;

                        case 'Z':
                            m_pCamera->MoveTo(m_pCamera->GetPosition().GetX(),
                                m_pCamera->GetPosition().GetY(), 
                                m_pCamera->GetPosition().GetZ() + 1);
                        break;

                        case 'z':
                            m_pCamera->MoveTo(m_pCamera->GetPosition().GetX(), 
                                m_pCamera->GetPosition().GetY(), 
                                m_pCamera->GetPosition().GetZ() - 1);
                        break;

                        // F key to increase the field of view up to 180
                        case 'F':
                            if (m_nFieldOfView < 180.0)
                            {
                                m_nFieldOfView += 5.0f;
                                this->UpdateProjectionMatrix();
                            }
                        break;

                        // f key to decrease the field of view down to 5
                        case 'f':
                            if (m_nFieldOfView > 5.0)
                            {
                                m_nFieldOfView -= 5.0f;
                                this->UpdateProjectionMatrix();
                            }
                        break;
                    }

                    // Current locale
                    std::locale loc("");

                    // Switch on the key
                    switch (std::use_facet<std::ctype<char> > (loc).
                        toupper(static_cast<char>(rArgs.GetCharCode())))
                    {
                        // Exit key
                        case 'Q':
                            // Go back to the main screen
                            this->GetSceneManager()->PopScene();

                        break;

                        // Help key
                        case 'I': 
                            //m_pHelpWindow->Show();
                        break;

                        // Space to move forward
                        case ' ':
                            //if (m_pMazeWalker->walk(CMazeWalker::forward))
                            //    this->Refresh();
                        break;

                        // L to move left
                        case 'L':
                            //if (m_pMazeWalker->walk(CMazeWalker::left))
                            //    this->Refresh();
                        break;
                      
                        // R to move right
                        case 'R':
                            //if (m_pMazeWalker->walk(CMazeWalker::right))
                            //    this->Refresh();
                        break;
                    }
                }
                else // System key
                {
                    switch (rArgs.GetCharCode())
                    {
                        // Left arrow, move left
                        case 13:
                            //if (m_pMazeWalker->walk(CMazeWalker::left))
                            //    this->Refresh();
                        break;

                        // Up arrow, move forward
                        case 14:
                            //if (m_pMazeWalker->walk(CMazeWalker::forward))
                            //    this->Refresh();
                        break;

                        // Right arrow, move right
                        case 15:
                            //if (m_pMazeWalker->walk(CMazeWalker::right))
                            //    this->Refresh();
                        break;

                        // Down arrow, move back
                        case 16:
                            
                        break;
                    }
                }
            }
        } // if scene active
    }

    void
    CDemoScene::HandleLoad(const Egl::CScene &, Egl::CEventArgs &)
    {   
        std::srand(3412548653);

        // Get our window
        Egl::WindowPtr_t pWindow = this->GetWindow();

        // Update projection and viewport
        this->UpdateProjectionMatrix(pWindow->GetWidth(), pWindow->GetHeight());
        this->UpdateViewport(pWindow->GetWidth(), pWindow->GetHeight());
        
        // Enable texture
        //glDisable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_2D);
        glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);				// Sky blue Background
	    glClearDepth(1.0f);									// Depth Buffer Setup
	    
        glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

        // Setup lights
        Egl::LightPtr_t pLight = Egl::CLightingControl::CreateLight<Egl::DIRECTIONAL_LIGHT>();
        pLight->MoveTo(1.0f, 1.0f, 1.0f);
        pLight->SetDifuseColor(1.0f, 0, 0, 0);
        pLight->SetAmbientColor(0.5f, 0.5f, 0.5f, 1.0f);
        pLight->Enable();
        m_vLights.push_back(pLight);
        
        pLight = Egl::CLightingControl::CreateLight<Egl::DIRECTIONAL_LIGHT>();
        pLight->MoveTo(-1.0f, -1.0f, 1.0f);
        pLight->SetDifuseColor(0, 1.0f, 0, 0);
        pLight->Enable();
        m_vLights.push_back(pLight);

        pLight = Egl::CLightingControl::CreateLight<Egl::DIRECTIONAL_LIGHT>();
        pLight->MoveTo(1.0f, -1.0f, 1.0f);
        pLight->SetDifuseColor(0, 0, 1.0f, 0);
        pLight->Enable();
        m_vLights.push_back(pLight);

        Egl::CLightingControl::EnableLighting();        
        //Egl::CLightingControl::DisableLighting();

        // Set the camera
        // Camera eye is at (0,0,30)
        //m_pCamera->MoveTo(0.0, 0.0, 30.0); 
        m_pCamera->MoveTo(7.0f, 15.0f, 8.0f); 
        
        // Camera is looking at (0,0,0)
        //m_pCamera->LookAt(Egl::C3DPoint<float>(0.0, 0.0, 0.0)); 
        m_pCamera->LookAt(Egl::C3DPoint<float>(23.0f, -400.0f, 8.0f)); 

        // Up is in positive Y direction for the camera
        m_pCamera->SetUpVector(0.0f, 1.0f, 0.0f);	

        // Set background color
        glClearColor(0.0, 0.0, 0.0, 0.0);        

        //Enable alpha-blending
        //glDisable(GL_ALPHA_TEST);
        glEnable(GL_ALPHA_TEST); 
        glAlphaFunc(GL_GREATER, 0.6f);        

        // We want to handle window events now
        pWindow->Reshape += boost::bind(&CDemoScene::HandleReshape, this, _1, _2);
        pWindow->ContextMenuItemSelected += boost::bind(&CDemoScene::HandleContextMenuItemSelected, this, _1, _2);
        pWindow->Key += boost::bind(&CDemoScene::HandleKey, this, _1, _2);
        pWindow->Draw += boost::bind(&CDemoScene::HandleDraw, this, _1, _2);        

        // We want to make sure the right contex menu shows up for this scene
        pWindow->SetContextMenu(m_pContextMenu, Egl::MouseButton::RIGHT);

        // Start demo
        m_citWalkerStep = m_vWalkerSteps.begin();
        m_pWalkerTimer->StartInterval(300);
    }

    void
    CDemoScene::HandleTimerTick(const Egl::CTimer &, Egl::CEventArgs &)
    {
        // End?
        if (m_citWalkerStep == m_vWalkerSteps.end())
        {
            m_pWalkerTimer->Stop();

            // Play winning music
            m_pMazeMusic->getSoundObject()->play();
        }
        else
        {
            switch (*m_citWalkerStep)
            {
                // l, move left
                case 'l':
                    if (m_pMazeWalker->walk(CMazeWalker::left))
                        this->Refresh();
                break;

                // u, move forward
                case 'u':
                    if (m_pMazeWalker->walk(CMazeWalker::forward))
                        this->Refresh();
                break;

                // r, move right
                case 'r':
                    if (m_pMazeWalker->walk(CMazeWalker::right))
                        this->Refresh();
                break;
            }

            ++m_citWalkerStep;
        }
    }

    void
    CDemoScene::HandleUnload(const Egl::CScene &, Egl::CEventArgs &)
    {
        // We are not interested on events any longer
        Egl::WindowPtr_t pWindow = this->GetWindow();
        pWindow->Reshape -= boost::bind(&CDemoScene::HandleReshape, this, _1, _2);
        pWindow->Draw -= boost::bind(&CDemoScene::HandleDraw, this, _1, _2);        
        pWindow->Key -= boost::bind(&CDemoScene::HandleKey, this, _1, _2);
        pWindow->ContextMenuItemSelected -= boost::bind(&CDemoScene::HandleContextMenuItemSelected, this, _1, _2);        
    }
   
    void 
    CDemoScene::HandleContextMenuItemSelected(const Egl::CWindow &, Egl::CMenuItemEventArgs & rArgs)
    {
        // Make sure we only handle this event if
        // this scene is active
        if (this->IsActive())
        {
            // Switch on the ID of the item
            switch (rArgs.GetItemId())
            {
                // Toggle help
                case MENU_ITEM_ID_HELP:
                    //m_pHelpWindow->Show();
                break;

                // Quit menu item.
                case MENU_ITEM_ID_QUIT:
                    this->GetSceneManager()->PopScene();
                break;
            }
        } // if scene active
    }

    void 
    CDemoScene::UpdateProjectionMatrix()
    {
        Egl::WindowPtr_t pWindow = this->GetWindow();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();	
        gluPerspective(
            m_nFieldOfView, // field of view in degrees
            static_cast<GLdouble>(pWindow->GetWidth()) / pWindow->GetHeight(), // aspect ratio
            .2, // Z near 
            16.0 // Z far
        );
        pWindow->Refresh();
    }

    void 
    CDemoScene::UpdateProjectionMatrix(const int nWidth, const int nHeight)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();	
        gluPerspective(
            m_nFieldOfView, // field of view in degrees
            static_cast<GLdouble>(nWidth) / nHeight, // aspect ratio
            .2, // Z near 
            16.0 // Z far
        );
    }

    void 
    CDemoScene::UpdateViewport(const int nWidth, const int nHeight)
    {
        // Set new viewport        
        glViewport(0, 0, nWidth, nHeight);        
    }
    
    void
    CDemoScene::Refresh()
    {
        this->GetWindow()->Refresh();
    }

    void 
    CDemoScene::HandleReshape(const Egl::CWindow &, Egl::CWindowReshapeEventArgs & rArgs)
    {
        // Make sure we only handle this event if
        // this scene is active
        if (this->IsActive())
        {
            // Update projection matrix.
            this->UpdateProjectionMatrix(rArgs.GetWidth(), rArgs.GetHeight());

            // update viewport
            this->UpdateViewport(rArgs.GetWidth(), rArgs.GetHeight());        
        }
    }
} // namespace AmazingMaze