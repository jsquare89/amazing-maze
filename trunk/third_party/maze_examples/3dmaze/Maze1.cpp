#include <windows.h>
#include <iostream>
#include <time.h>
#include <limits>
#include <cstdlib>
#include <new>
#include <GL/gl.h>
#include <GL/glut.h>
#include <functional>
#include <algorithm>
#include <limits>

#include "mazedefs.h"
#include "CMaze.h"


#define PROGRAM_NAME "3D Maze - Jeff Paquette"

static void usage();

static CMaze        *maze = 0;
static maze_walker  *walker = 0;

const uint32 cu32wWidth     = 640;
const uint32 cu32wHeight    = 480;
const uint32 cu32wLeft      = 0;
const uint32 cu32wTop       = 0;

const uint32 cu32RatID_2d    = 1;
const uint32 cu32RatID_3d    = 2;
const uint32 cu32NorthWallID = 3;
const uint32 cu32EastWallID  = 4;

static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2;
static GLdouble viewer[]= {0.0, 0.0, 5.0}; /* initial viewer location */

static GLfloat near_clip = 0.25;
static GLfloat far_clip = 50.0;
static GLfloat field_of_view = 95;
static bool show_2d = false;
static bool rats_view = true;

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

void polygon(GLfloat v[][3], int a, int b, int c , int d)
{
  /* draw a polygon via list of vertices */
  glBegin(GL_POLYGON);
  glColor3fv(colors[a]);
  glNormal3fv(normals[a]);
  glVertex3fv(v[a]);
  glColor3fv(colors[b]);
  glNormal3fv(normals[b]);
  glVertex3fv(v[b]);
  glColor3fv(colors[c]);
  glNormal3fv(normals[c]);
  glVertex3fv(v[c]);
  glColor3fv(colors[d]);
  glNormal3fv(normals[d]);
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


//--
// function objects for drawing walls
class draw_north_wall_2d : public std::binary_function<const bool, pair_int *, int>
{
public:
  result_type operator()(first_argument_type present,
                         second_argument_type loc) const
  {
    if (present)
    {
      glVertex2f(loc->first - 0.5f, loc->second - 0.5f);
      glVertex2f(loc->first + 0.5f, loc->second - 0.5f);
    }
    loc->first++;

    return(0);
  }
};

class draw_east_wall_2d : public std::binary_function<const bool , pair_int *, int>
{
public:
  result_type operator()(first_argument_type present,
                         second_argument_type loc) const
  {
    if (present)
    {
      glVertex2f(loc->first + 0.5f, loc->second - 0.5f);
      glVertex2f(loc->first + 0.5f, loc->second + 0.5f);
    }
    loc->first++;

    return(0);
  }
};


class draw_row_2d : public std::binary_function<const maze_row *, int *, int>
{
public:
  result_type operator()(first_argument_type row,
                         second_argument_type r) const
  {
    std::for_each(row->north_walls.begin(), row->north_walls.end(), 
                  std::bind2nd(draw_north_wall_2d(), &pair_int(0,*r)));
    std::for_each(row->east_walls.begin(), row->east_walls.end(), 
                  std::bind2nd(draw_east_wall_2d(), &pair_int(0, *r)));
    (*r)++;

    return (0);
  }
};
//--

// function objects for drawing walls
class draw_north_wall : public std::binary_function<const bool, pair_int *, int>
{
public:
  result_type operator()(first_argument_type present,
                         second_argument_type loc) const
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
};

class draw_east_wall : public std::binary_function<const bool , pair_int *, int>
{
public:
  result_type operator()(first_argument_type present,
                         second_argument_type loc) const
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
};


class draw_row : public std::binary_function<const maze_row *, int *, int>
{
public:
  result_type operator()(first_argument_type row,
                         second_argument_type r) const
  {
    std::for_each(row->north_walls.begin(), row->north_walls.end(), 
                  std::bind2nd(draw_north_wall(), &pair_int(0,*r)));
    std::for_each(row->east_walls.begin(), row->east_walls.end(), 
                  std::bind2nd(draw_east_wall(), &pair_int(0, *r)));
    (*r)++;

    return (0);
  }
};



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
  glColor3f( 1.0, 1.0, 0.5 );

  glBegin( GL_POLYGON );
  {
    glVertex3d( 0.4375, 0.5,   0.0);
    glVertex3d( 0.25, 0.5, -0.25 );
    glVertex3d( -0.3, 0.5, -0.25 );
    glVertex3d( -0.375, 0.5,   0 );
    glVertex3d( -0.3, 0.5,  0.25 );
    glVertex3d( 0.25, 0.5,  0.25 );
  }
  glEnd();

  glPopAttrib();

  glEndList();
}

void draw_floor()
{
  // red floor
  glPushAttrib( GL_ALL_ATTRIB_BITS );
  glColor3f(.5,0,0);
  glPushMatrix();

  glTranslatef(0.0, 0.0, -0.5);
  glScalef(maze->width() + 1, 1, maze->height() + 1);

  glBegin(GL_QUADS);
  glVertex3f(0.0, 0.0f, 0.0);
  glVertex3f(1.0, 0.0f, 0.0);
  glVertex3f(1.0, 0.0f, 1.0);
  glVertex3f(0.0, 0.0f, 1.0);
  glEnd();
  glPopMatrix();
  glPopAttrib();
}

void draw_rat(const node& rat_loc, bool b3D)
{
  GLfloat angle;
  glPushMatrix();

  switch(walker->facing())
  {
  case maze_walker::north:
    if (rats_view)
      angle = -90.0;
    else
      angle = 90;
    break;
  case maze_walker::south:
    if (rats_view)
      angle = 90.0;
    else
      angle = -90.0;
    break;
  case maze_walker::east:
    angle = 0.0;
    break;
  case maze_walker::west:
    angle = 180.0;
    break;
  }


  if (b3D)
  {
    glTranslatef(rat_loc.first + 1, 0.5, rat_loc.second);
    glRotatef(angle, 0, 1, 0);
    glCallList(cu32RatID_3d);
  }
  else
  {
    glTranslatef(rat_loc.first,  rat_loc.second, 0);
    glRotatef(angle, 0, 0, 1);
    glCallList(cu32RatID_2d);
  }

  glPopMatrix();
}

node scale_coords(node screen_loc)
{
  int       ww = glutGet( GLUT_WINDOW_WIDTH );
  int       wh = glutGet( GLUT_WINDOW_HEIGHT );
  float xm, ym;
  float mw, mh;

  mw = maze->width() + 1;
  mh = maze->height();

  float scale_x = mw / ww;
  float scale_y = mh / wh;

  xm = ceil(static_cast<float>(screen_loc.first) * scale_x);
  ym = mh - floor(static_cast<float>(screen_loc.second) * scale_y) - 1;
    
  return (node(static_cast<int>(xm), static_cast<int>(ym)));
}

inline bool in_range(int v, int lb, int ub)
{
  return (v > lb && v < ub);
}

inline bool in_maze (node& l)
{
  return (in_range(l.first, 0, maze->width()) &&
          in_range(l.second, 0, maze->height()));
}

void keyHandler(unsigned char k, int x, int y)
{
  bool valid_move = true;
  
  /* Use x, X, y, Y, z, and Z keys to move viewer */

  switch (k)
  {
  case '2':
    show_2d = !show_2d;
    break;
    
  case '+':
    field_of_view += 5.0f;
    if (field_of_view > 180.0)
      field_of_view = 180.0;
    break;

  case '-':
    field_of_view -= 5.0f;
    if (field_of_view < 5.0)
      field_of_view = 5.0;
    break;
    
  case ' ':
    valid_move = walker->walk(maze_walker::forward);
    break;

  case 'l':
  case 'L':
    valid_move = walker->walk(maze_walker::left);
    break;
    
  case 'r':
  case 'R':
    valid_move = walker->walk(maze_walker::right);
    break;

  default:
    valid_move = false;
  }

  if (valid_move)
    glutPostRedisplay();
}

void handleMouse(int button, int state, int x, int y)
{
  if (state == 1)   // only acknowledge button_up events
  {
    if (walker->walk(static_cast<maze_walker::motion>(button)))
      glutPostRedisplay();
  }
}

void specialKeyFunc(int key, int x, int y)
{
  bool valid_move = true;

  switch(key)
  {
  case GLUT_KEY_F1:
    rats_view = !rats_view;
    break;
  case GLUT_KEY_LEFT :
    valid_move = walker->walk(maze_walker::left);
    break;
  case GLUT_KEY_UP :
    valid_move = walker->walk(maze_walker::forward);
    break;
  case GLUT_KEY_RIGHT :
    valid_move = walker->walk(maze_walker::right);
    break;
  default:
    valid_move = false;
    break;
  }

  if (valid_move)
    glutPostRedisplay();
}

void set_viewpoint()
{
  GLfloat look_at[3];

  if (rats_view)
  {
    viewer[0] = walker->position().col();
    viewer[1] = 0.5;
    viewer[2] = walker->position().row();
    look_at[0] = walker->looking_at().col();
    look_at[1] = 0.5;
    look_at[2] = walker->looking_at().row();
  }
  else
  {
    viewer[0] = maze->width() / 2.0;
    viewer[1] = 5.0;
    viewer[2] = maze->height() / 2.0;
    look_at[0] = walker->position().col();
    look_at[1] = 0.5;
    look_at[2] = walker->position().row();
  }

  gluLookAt(viewer[0],viewer[1],viewer[2], // viewer location
            look_at[0],look_at[1],look_at[2],
            0.0, 1.0, 0.0);                // up vector

}


void display_3d(void)
{
  glMatrixMode(GL_MODELVIEW);
  /* Update viewer position in modelview matrix */

  glLoadIdentity();
  set_viewpoint();
  glTranslatef(-1,0,0);

  glColor3f(0.5, 0.5, 0.5);
  int r = 0;
  std::for_each(maze->begin(), maze->end(), std::bind2nd(draw_row(), &r));
  draw_rat(walker->position(), true);
  draw_floor();
}

void display_2d(void)
{
  glColor3f(1.0, 1.0, 0.5);
  glBegin(GL_LINES);
  {
    int r = 0;
    std::for_each(maze->begin(), maze->end(), std::bind2nd(draw_row_2d(), &r));
  }
  glEnd();
  draw_rat(walker->position(), false);
}

void display (void)
{
  // clear the window
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  uint32 ww = glutGet(GLUT_WINDOW_WIDTH);
  uint32 wh = glutGet(GLUT_WINDOW_HEIGHT);

  if (show_2d)
    wh = wh / 2 - 1;

  glViewport(0, 0, ww, wh);

  /* Use a perspective view */

  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity();
  gluPerspective(field_of_view, ww/wh, near_clip, far_clip); 

  glMatrixMode(GL_MODELVIEW);

  display_3d();

  if (show_2d)
  {
    // now show the 2d maze
    glViewport(0, wh + 10, ww, (wh + 1));

    uint32 w = maze->width() + 1;
    uint32 h = maze->height() + 1;
    /* Use a perspective view */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w + 1, -1, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    display_2d();

    float x = walker->looking_at().col();
    float y = walker->looking_at().row();

    glColor3f(0, 1, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x - 0.25, y - 0.25);
    glVertex2f(x - 0.25, y + 0.25);
    glVertex2f(x + 0.25, y + 0.25);
    glVertex2f(x + 0.25, y - 0.25);
    glEnd();

    x = walker->position().col();
    y = walker->position().row();
   
  }

  glFlush();
  glutSwapBuffers();
}

void maze_init_gl(uint32 m, uint32 n)
{
  glColor3f(1.0,0.0,1.0);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  near_clip = .2f;
  far_clip = m + 1.0;
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  try {
    maze = new CMaze(m, n);
    walker = new maze_walker(*maze);
  }

  catch (std::bad_alloc)
  {
    std::cerr << "Cannot generate maze: out of memory" << std::endl;
    exit(EXIT_FAILURE);
  }

}

void myReshape(int w, int h)
{
  glViewport(0, 0, w, h);

  /* Use a perspective view */

  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity();

  if (maze)
    gluPerspective(field_of_view, w/h, near_clip, far_clip); 

  glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char *argv[])
{
  int       m, n;

  srand(time(0));

  glutInitWindowSize(cu32wWidth, cu32wHeight);
  glutInitWindowPosition(0, 0);
  glutInit(&argc, argv);

  if (argc != 3)
  {
    usage();
    exit(EXIT_FAILURE);
  }

  m = atoi( argv[1] );
  n = atoi( argv[2] );

  if ( m <= 1 || n <= 1 )
  {
    std::cerr << "I'm sorry, but I can't generate a maze of size " << m
              << "x" << n << "!" << std::endl;
    exit(EXIT_FAILURE);
  }

  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow(PROGRAM_NAME);
  
  maze_init_gl(m, n);

  rat_init();
  walls_init();

  glutDisplayFunc(display);
  glutMouseFunc(handleMouse);
  glutKeyboardFunc(keyHandler);
  glutReshapeFunc(myReshape);
  glutSpecialFunc(specialKeyFunc);
  glutMainLoop();

  delete maze;
  delete walker;

  return 0;
}

void usage()
{
  std::cout << "Maze1 - an OpenGL maze Generator for CS436 by Jeff Paquette " << std::endl
            << "To use this program, you need to supply the width and the " << std::endl
            << "height of the maze to be generated. For example:" << std::endl << std::endl
            << "\tmaze1 15 20" << std::endl << std::endl
            << "That would generate a maze that was 20 columns " << std::endl
            << "wide and 15 rows high." << std::endl << std::endl
            << "You may guide the rat through the maze by clicking the mouse buttons."
            << std::endl
            << "Click the left button to turn left, the right button to turn right, "
            << std::endl
            << "and the middle button to go forward." << std::endl
            << "Alternatively, you may press 'L' to turn left," << std::endl
            << "'R' to turn right, and the spacebar to move forward." << std::endl;
}
