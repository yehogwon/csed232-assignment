#ifndef __STATUS__
#define __STATUS__

#include <exception>
#include <utility>

enum key { UP, DOWN, LEFT, RIGHT }; // arrow key enum
using pos = std::pair<int, int>; // position (row index, column index) pair (1 based)

class GameWinException : public std::exception { }; // exception for game win
class GameOverException : public std::exception { }; // exception for game over (lose)

#endif // __STATUS__