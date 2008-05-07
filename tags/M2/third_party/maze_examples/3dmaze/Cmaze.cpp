#include "mazedefs.h"
#include <memory>
#include <new>
//#include <GL/glut.h>
#include "CMaze.h"

CMaze::CMaze(uint32 h, uint32 w) :
    _width(w + 1), _height(h + 1), maze(_height)
{
  for (row_iterator it = maze.begin(); it < maze.end(); it++)
  {
    // allocate a new row of walls
    *it = new maze_row(_width);

    // initialize all walls as present
    std::fill_n((*it)->north_walls.begin(), _width, true);
    std::fill_n((*it)->east_walls.begin(), _width, true);
  }

  // by convention, the 0th column and the last row are considered "phantoms" 
  // whose sole purpose is to delinate the bounds of the maze. [i,0] designates 
  // the entry point while [i,n] is the exit.

  std::fill_n((*maze.rbegin())->east_walls.begin(), _width, false);

  for (row_iterator iter = maze.begin(); iter < maze.end(); iter++)
  {
    *(*iter)->north_walls.begin() = false;
  }

  generate_maze();
}
  
CMaze::~CMaze()
{
  for (row_iterator it = maze.begin(); it < maze.end(); it++)
    delete *it;
}

void CMaze::generate_maze()
{
  node_stack  nodes;

  int r = rand() % (_height - 1);   // range: 0..m-1
  int c = rand() % (_width - 1) + 1;  // range: 1..n

  nodes.push(node(c, r));

  while (!nodes.empty())
    process_node(nodes);

  // now pick a starting point, then an end point
  int start = rand() % (_height - 1);
  maze[start]->east_walls[0] = 0;

  _entry_node.first = 0;
  _entry_node.second = start;

  int end = rand() % (_height - 1);
  maze[end]->east_walls[_width - 1] = 0;

  _exit_node.first = _width - 1;
  _exit_node.second = end;
}

void CMaze::process_node(node_stack& nodes)
{
  node  n = nodes.top();
  int nodes_to_process;

  nodes.pop();

  do {
    // examine neighboring cells...if they all have 4 walls then they
    // haven't yet been visited. Any cell that does not have all 4 walls
    // must, by definition, be on a path.

    node  left(n.col()-1, n.row());
    node  above(n.col(), n.row()+1);
    node  below(n.col(), n.row()-1);
    node  right(n.col()+1, n.row());

    std::vector<node> nv;

    // consider the 4 neighboring cells
    if (has_four_walls(above))
      nv.push_back(above);

    if (has_four_walls(left))
      nv.push_back(left);
    
    if (has_four_walls(right))
      nv.push_back(right);
    
    if (has_four_walls(below))
      nv.push_back(below);

    // if any of these nodes haven't been visited then add them to the stack
    // in random order.
    nodes_to_process = nv.size();
    if (nodes_to_process > 0)
    {
      for (int i = 0; i < nodes_to_process - 1; i++)
      {
        int node_index = rand() % nv.size();
        nodes.push(n);
        nv.erase(nv.begin()+node_index);
      }

      node  next_node = *nv.begin();

      if (next_node == below)
      {
        maze[n.row()]->north_walls[n.col()] = false;
      }
      else if (next_node == above)
      {
        maze[next_node.row()]->north_walls[next_node.col()] = false;
      }
      else if (next_node == left)
      {
        maze[next_node.row()]->east_walls[next_node.col()] = false;
      }
      else if (next_node == right)
      {
        maze[n.row()]->east_walls[n.col()] = false;
      }

      n = next_node;
    }
  } while (nodes_to_process > 0);
}

bool CMaze::is_valid_node(node& n) const
{
  return ((n.row() < _height) && (n.col() < (_width )));
}

bool CMaze::has_four_walls(node& n)
{
  // see if this node has four walls
  return (is_valid_node(n)            &&
          maze[n.row()]->north_walls[n.col()]   &&
          maze[n.row()]->east_walls[n.col()]    &&
          maze[n.row()+1]->north_walls[n.col()] &&
          maze[n.row()]->east_walls[n.col()-1]     );
}


maze_walker::direction maze_walker::turn(maze_walker::motion m)
{
  direction d = _facing;

  if (m == left)
  {
    d = static_cast<direction>((_facing + 3) % 4);
  }
  else if (m == right)
  {
    d = static_cast<direction>((_facing + 1) % 4);
  }

  _facing = d;
  return (_facing);
}

node& maze_walker::looking_at() 
{
  node  left(_curpos.col()-1, _curpos.row());
  node  above(_curpos.col(), _curpos.row()+1);
  node  below(_curpos.col(), _curpos.row()-1);
  node  right(_curpos.col()+1, _curpos.row());

  switch (_facing)
  {
  case north:
    _look_at = below;
    break;

  case east:
    _look_at = right;
    break;

  case south:
    _look_at = above;
    break;

  case west:
    _look_at = left;
    break;
  }

  return (_look_at);
}

bool maze_walker::walk( maze_walker::motion m )
{
  bool legal_motion( false );

  switch( m )
  {
  case left:
    turn( left );
    return (true);
    break;

  case forward:
    break;

  case right:
    turn( right );
    return (true);
    break;
  }

  node  left(_curpos.col()-1, _curpos.row());
  node  above(_curpos.col(), _curpos.row()+1);
  node  below(_curpos.col(), _curpos.row()-1);
  node  right(_curpos.col()+1, _curpos.row());
  node  next_node = _curpos;

  switch( _facing )
  {
  case north:
    next_node = below;
    if (_maze.is_valid_node(next_node))
      legal_motion = !(_maze.maze[_curpos.row()]->north_walls[_curpos.col()]);
    break;

  case east:
    next_node = right;
    if (_maze.is_valid_node(next_node))
      legal_motion = !(_maze.maze[_curpos.row()]->east_walls[_curpos.col()]);
    break;

  case south:
    next_node = above;
    if (_maze.is_valid_node(next_node))
      legal_motion =!(_maze.maze[next_node.row()]->north_walls[next_node.col()]);
    break;

  case west:
    next_node = left;
    if (_maze.is_valid_node(left))
      legal_motion = !(_maze.maze[left.row()]->east_walls[left.col()]);
    break;
  }

  if (legal_motion)
    _curpos = next_node;

  return (legal_motion);
}
