#include "game.ui.hpp"

GameUi::GameUi(Game &game_) : game_(game_) {
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    // game_.add_update_callback(update_game);
    board_ = new QGridLayout(this);
    score_label_ = new QLabel(this);
    restore_button_ = new QPushButton("Restore", this);
    exit_button_ = new QPushButton("Exit", this);

    board_->setSpacing(0);

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            board_->addWidget(blocks_[i][j] = new BlockUi(game_[i][j]), i, j);
}

GameUi::~GameUi() {
    delete board_;
    delete score_label_;
    delete restore_button_;
    delete exit_button_;

    for (auto &row : blocks_) {
        for (auto &block : row) {
            delete block;
        }
    }
}
