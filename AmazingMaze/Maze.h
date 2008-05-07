#pragma once

/** 
 * Note: For the time being this file is very much based on the 3D maze
 * program by Jeff Paquette.
 */
#include <vector>
#include <stack>

namespace AmazingMaze
{

    typedef unsigned int uint32;
    typedef std::pair<int, int> pair_int;

    // describe a single row in terms of its north walls and its east walls.
    // a wall N is present if the bit[N] is SET.
    struct maze_row {
      typedef std::vector<bool> walls;
      typedef walls::iterator iterator;

      walls north_walls;
      walls east_walls;

      maze_row(size_t length) : north_walls(length), east_walls(length) {};
      ~maze_row() {};

    private:

      // hidden to prevent accidental construction
      maze_row();   // no implementation
    };

    struct node : public pair_int {
      node () : pair_int() {};
      node (int c, int r) : pair_int(c,r) {};
      
      int row () const { return (second); };
      int col () const { return (first); };
    };

    class CMazeWalker;

    class CMaze {
    private:
      uint32  _height;
      uint32  _width;
      node    _entry_node;
      node    _exit_node;

      CMaze ();       // no implementation
      CMaze (const CMaze&); // no implementation

      std::vector<maze_row *> maze;

      typedef std::stack<node>                            node_stack;

      void generate_maze();
      void process_node(node_stack&);
      bool has_four_walls(node& node);
      bool is_valid_node(node& n) const;

    public:
        typedef std::vector<maze_row *>::iterator           row_iterator;
      typedef std::vector<maze_row *>::reverse_iterator   row_reverse_iterator;
      

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

      friend class CMazeWalker;

      // generate a maze wxh 
      CMaze (uint32 w, uint32 h);
      ~CMaze();
    };

    class CMazeWalker {
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
      CMazeWalker(CMaze& maze) : _maze(maze), _facing(east)
      {
        _curpos = _maze.entry_node();
        _look_at = _maze.entry_node();
        // look at next cell
        _look_at.second++;
      }
      
      ~CMazeWalker() {}

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

} // namespace AmazingMaze
