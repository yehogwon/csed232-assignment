#ifndef __STATUS__
#define __STATUS__

#include <exception>

class GameWinException : public std::exception { };
class GameOverException : public std::exception { };

#endif // __STATUS__