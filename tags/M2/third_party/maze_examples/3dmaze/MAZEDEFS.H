#if !defined(MAZEDEFS)
#define MAZEDEFS

#include <utility>
#include <functional>
#include <vector>

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

#endif
