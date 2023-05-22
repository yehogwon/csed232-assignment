#ifndef __GAME__
#define __GAME__

#include <array>
#include <vector>
#include "block.hpp"
#include "board.hpp"

class Game {
    using callback_ = void (*)();
private: 
    Board board_;
    std::vector<callback_> callback_v_;

    bool is_game_over();
public: 
    void add_update_callback(callback_ callback);

    std::array<Block, 4>& operator[](int i);
    const std::array<Block, 4>& operator[](int i) const;    
};

#endif // __GAME__