#include "game.ui.hpp"

GameUi::GameUi(Game &game_) : game_(game_) {
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setStyleSheet("QWidget { background-color : gray; }");
    
    root_ = new QHBoxLayout(this);
    board_ = new QGridLayout();
    pane_ = new QVBoxLayout();
    score_label_ = new QLabel(this);
    restore_button_ = new QPushButton("Restore", this);
    exit_button_ = new QPushButton("Exit", this);

    root_->addLayout(board_);
    root_->addLayout(pane_);
    root_->setSpacing(0);
    root_->setContentsMargins(0, 0, 0, 0);

    board_->setSpacing(0);
    board_->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    board_->setContentsMargins(0, 0, 0, 0);

    pane_->setAlignment(Qt::AlignRight | Qt::AlignTop);
    pane_->addWidget(score_label_);
    pane_->addWidget(restore_button_);
    pane_->addWidget(exit_button_);

    score_label_->setText("Score !!");

    restore_button_->setText("Restore");
    restore_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);

    exit_button_->setText("Exit");
    exit_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);

    // move restore_button_ and exit_button_ to the bottom
    pane_->addStretch(5);

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board_->addWidget(blocks_[i][j] = new BlockUi(game_[i][j]), i, j);
    
    connect(restore_button_, &QPushButton::clicked, this, &GameUi::restore);
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

void GameUi::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Left: move(LEFT); break;
        case Qt::Key_Right: move(RIGHT); break;
        case Qt::Key_Up: move(UP); break;
        case Qt::Key_Down: move(DOWN); break;
    }
}

void GameUi::refresh() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            blocks_[i][j]->update_value();
}

void GameUi::move(Key key) {
    try {
        game_.move(key);
    } catch (GameWinException &e) {
        // TODO: do something
    } catch (GameOverException &e) {
        // TODO: do something
    }
    refresh();
}

void GameUi::restore() {
    // TODO: Show a dialog box
    if (game_.restore()) {
        refresh();
    }
}
