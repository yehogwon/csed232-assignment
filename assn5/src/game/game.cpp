#include "game.hpp"

const char* to_string(Key key) {
    switch (key) {
        case UP: return "UP";
        case DOWN: return "DOWN";
        case LEFT: return "LEFT";
        case RIGHT: return "RIGHT";
        default: return "";
    }
}

Game::Game() : prev_board_(nullptr), board_(new Board()), score_(0), restore_count_(0) {
    std::srand(std::time(nullptr));
    create_block(2, true);
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
    bool can_move = false;
    for (int i = 0; i < SIZE && !can_move; i++)
        for (int j = 0; j < SIZE && !can_move; j++)
            if ((*board_)[i][j] == 0) can_move = true;
    
    for (int i = 0; i < SIZE && !can_move; i++)
        for (int j = 0; j < SIZE - 1 && !can_move; j++)
            if ((*board_)[i][j] == (*board_)[i][j + 1]) can_move = true;
    
    for (int i = 0; i < SIZE - 1 && !can_move; i++)
        for (int j = 0; j < SIZE && !can_move; j++)
            if ((*board_)[i][j] == (*board_)[i + 1][j]) can_move = true;

    return !can_move;
}

bool Game::create_block(int n, bool only_two) {
    std::vector<std::pair<int, int>> empty_blocks;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if ((*board_)[i][j] == 0)
                empty_blocks.push_back(std::make_pair(i, j));
    if (empty_blocks.size() == 0) return false;
    
    int initial_size = empty_blocks.size(), n_ = n;
    std::cout << (only_two ? "INITIAL " : "GENERATE ");
    while (n_-- && empty_blocks.size() > 0) {
        int index = std::rand() % empty_blocks.size();
        empty_blocks.erase(empty_blocks.begin() + index);
        int value = std::rand() % 5 == 0 && !only_two ? 4 : 2;
        int row = empty_blocks[index].first, col = empty_blocks[index].second;
        std::cout << row + 1 << " " << col + 1 << " ";
        if (!only_two) std::cout << value << " ";
        (*board_)[row][col] = value;
    }
    std::cout << std::endl;
    return initial_size >= n;
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

bool Game::move(Key key) {
    Board *t_prev_ = new Board(*board_);
    bool moved = false;
    std::cout << to_string(key) << std::endl;
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
        std::cout << "SCORE " << score_ << std::endl;
        if (is_game_win()) throw GameWinException();
        create_block();
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
    return true;
}

bool Game::restorable() const {
    return prev_board_ != nullptr;
}

int Game::restore_remain() const {
    return MAX_RESTORE - restore_count_;
}

bool Game::save(const char *path) const {
    std::ofstream fout(path);
    if (!fout.is_open()) return false;
    fout << score_ << std::endl;
    fout << restore_count_ << std::endl;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE - 1; j++)
            fout << (*board_)[i][j].value() << std::endl;
    if (!prev_board_) {
        fout << "NOTNULL" << std::endl;
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE - 1; j++)
                fout << (*prev_board_)[i][j].value() << std::endl;
    } else
        fout << "NULL" << std::endl;
    fout.close();
    return true;
}

bool Game::load(const char *path) {
    std::ifstream fin(path);
    if (!fin.is_open()) return false;
    fin >> score_;
    fin >> restore_count_;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE - 1; j++)
            fin >> (*board_)[i][j].value();
    std::string prev_check_;
    fin >> prev_check_;
    if (prev_check_ == "NOTNULL") {
        if (!prev_board_) prev_board_ = new Board();
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE - 1; j++)
                fin >> (*prev_board_)[i][j].value();
    } else {
        if (prev_board_) delete prev_board_;
        prev_board_ = nullptr;
    }
    fin.close();
    return true;
}

std::array<Block, SIZE>& Game::operator[](int i) {
    return (*board_)[i];
}
const std::array<Block, SIZE>& Game::operator[](int i) const {
    return (*board_)[i];
}