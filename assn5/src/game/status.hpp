#ifndef __STATUS__
#define __STATUS__

#include <exception>
#include <utility>

enum Key { UP, DOWN, LEFT, RIGHT };
using pos = std::pair<int, int>;

const char* to_string(Key key);

class GameWinException : public std::exception { };
class GameOverException : public std::exception { };

#endif // __STATUS__