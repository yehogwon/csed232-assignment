#ifndef __GAME__
#define __GAME__

#include <array>
#include <vector>
#include "block.hpp"
#include "board.hpp"

class Game {
    using callback_ = void (*)();
private: 
    Board *prev_board_;
    Board *board_;
    std::vector<callback_> callback_v_;

    bool create_block();
public: 
    Game();
    ~Game();

    void add_update_callback(callback_ callback);

    const Board& prev() const;
    const Board& cur() const;

    bool left();
    bool right();
    bool up();
    bool down();
    
    bool is_game_over();

    std::array<Block, SIZE>& operator[](int i);
    const std::array<Block, SIZE>& operator[](int i) const;    
};

#endif // __GAME__