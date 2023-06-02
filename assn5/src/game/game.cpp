#include "game.hpp"

Game::Game() : prev_board_(nullptr), board_(new Board()), score_(0), restore_count_(0) {
    std::srand(std::time(nullptr));
    const std::vector<std::pair<pos, int>> &&blocks__ = create_block(2, true);
    Logger::initial(blocks__[0].first, blocks__[1].first);
}

Game::~Game() {
    if (prev_board_)
        delete prev_board_;
    delete board_;
}

bool Game::is_game_win() const {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if ((*board_)[i][j] == GOAL) return true;
    return false;
}

bool Game::is_game_over() const {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if ((*board_)[i][j] == 0) return false;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE - 1; j++)
            if ((*board_)[i][j] == (*board_)[i][j + 1]) return false;
    for (int i = 0; i < SIZE - 1; i++)
        for (int j = 0; j < SIZE; j++)
            if ((*board_)[i][j] == (*board_)[i + 1][j]) return false;
    return true;
}

std::vector<std::pair<pos, int>> Game::create_block(int n, bool only_two) {
    std::vector<std::pair<int, int>> empty_blocks;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if ((*board_)[i][j] == 0)
                empty_blocks.push_back(std::make_pair(i, j));
    if (empty_blocks.size() == 0) return {};
    
    std::vector<std::pair<pos, int>> blocks;
    while (n-- && empty_blocks.size() > 0) {
        int index = std::rand() % empty_blocks.size();
        empty_blocks.erase(empty_blocks.begin() + index);
        int value = std::rand() % 5 == 0 && !only_two ? 4 : 2;
        int row = empty_blocks[index].first, col = empty_blocks[index].second;
        blocks.push_back(std::make_pair(std::make_pair(row + 1, col + 1), value));
        (*board_)[row][col] = value;
    }
    return blocks;
}

void Game::clear_merged() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            (*board_)[i][j].merged = false;
}

const Board& Game::prev() const {
    return *prev_board_;
}

const Board& Game::cur() const {
    return *board_;
}

int Game::score() const {
    return score_;
}

bool Game::move(key key) {
    Board *t_prev_ = new Board(*board_);
    bool moved = false;
    Logger::move(key);
    switch (key) {
        case UP: moved = move_<Up>(); break;
        case DOWN: moved = move_<Down>(); break;
        case LEFT: moved = move_<Left>(); break;
        case RIGHT: moved = move_<Right>(); break;
    }
    clear_merged();

    if (moved) {
        if (prev_board_) delete prev_board_;
        prev_board_ = t_prev_;
        Logger::score(score_);
        const std::vector<std::pair<pos, int>> &&blocks__ = create_block();
        Logger::generate(blocks__[0].first, blocks__[0].second);
        if (is_game_win()) throw GameWinException();
    } else {
        delete t_prev_;
        if (is_game_over()) throw GameOverException();
    }

    return moved;
}

bool Game::restore() {
    if (!prev_board_) return false;
    *board_ = *prev_board_;
    delete prev_board_;
    prev_board_ = nullptr;
    restore_count_++;
    Logger::restore(restore_remain());
    return true;
}

bool Game::restorable() const {
    return prev_board_ != nullptr;
}

int Game::restore_remain() const {
    return MAX_RESTORE - restore_count_;
}

std::array<Block, SIZE>& Game::operator[](int i) {
    return (*board_)[i];
}
const std::array<Block, SIZE>& Game::operator[](int i) const {
    return (*board_)[i];
}