#if !defined(CMAZE_H)
#define CMAZE_H

#include <vector>
#include <stack>


struct maze_row;

struct node : public pair_int {
  node () : pair_int() {};
  node (int c, int r) : pair_int(c,r) {};
  
  int row () const { return (second); };
  int col () const { return (first); };
};

class maze_walker;

class CMaze {
private:
  uint32  _height;
  uint32  _width;
  node    _entry_node;
  node    _exit_node;

  CMaze ();       // no implementation
  CMaze (const CMaze&); // no implementation

  std::vector<maze_row *> maze;

  typedef std::vector<maze_row *>::iterator           row_iterator;
  typedef std::vector<maze_row *>::reverse_iterator   row_reverse_iterator;
  typedef std::stack<node>                            node_stack;

  void generate_maze();
  void process_node(node_stack&);
  bool has_four_walls(node& node);
  bool is_valid_node(node& n) const;

public:
  uint32 height() const { return _height; };
  uint32 width()  const { return _width; };
  const node& entry_node() const { return _entry_node; };
  const node& exit_node() const { return _exit_node; };
  
  row_iterator begin()
  {
    return maze.begin();
  }

  row_iterator end()
  {
    return maze.end();
  }

  friend class maze_walker;

  // generate a maze wxh 
  CMaze (uint32 w, uint32 h);
  ~CMaze();
};

class maze_walker {
public:
  enum direction {north, east, south, west};
  enum motion {left, forward, right};

private:
  node          _curpos;    // current position in maze
  node          _look_at;   // look_at position, ie, what cell we're facing
  const CMaze&  _maze;
  direction     _facing;

  direction turn(motion m);

public:
  maze_walker(CMaze& maze) : _maze(maze), _facing(east)
  {
    _curpos = _maze.entry_node();
    _look_at = _maze.entry_node();
    // look at next cell
    _look_at.second++;
  }
  
  ~maze_walker() {}

  const node& position() { return (_curpos); }
  const direction facing() 
  { 
    return (_facing); 
  }

  const char *facing_as_str()
  {
    switch(_facing)
    {
    case north:
      return("north");
    case south:
      return("south");
    case east:
      return("east");
    case west:
      return("west");
    }

    return("unknown");
  }

  node& looking_at();

  bool walk(motion m);
};

#endif
