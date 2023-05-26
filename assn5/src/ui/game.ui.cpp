#include "game.ui.hpp"

GameUi::GameUi(Game &game_) : game_(game_) {
    resize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setStyleSheet("QWidget { background-color : #d9d9d9; } QInputDialog QWidget { color : black; }");
    
    root_ = new QHBoxLayout(this);
    board_ = new QGridLayout();
    pane_ = new QVBoxLayout();
    score_label_ = new QLabel(this);
    save_button_ = new QPushButton("Save", this);
    load_button_ = new QPushButton("Load", this);
    restore_button_ = new QPushButton("Restore", this);
    exit_button_ = new QPushButton("Exit", this);

    root_->addLayout(board_);
    root_->addLayout(pane_);
    root_->setSpacing(0);
    root_->setContentsMargins(0, 0, 0, 0);

    board_->setSpacing(10);
    board_->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    board_->setContentsMargins(0, 0, 0, 0);

    pane_->setAlignment(Qt::AlignRight | Qt::AlignTop);
    pane_->setSpacing(20);
    pane_->addWidget(score_label_);
    pane_->addStretch(1);
    pane_->addWidget(save_button_);
    pane_->addWidget(load_button_);
    pane_->addWidget(restore_button_);
    pane_->addWidget(exit_button_);

    score_label_->setText("Score: 0");
    score_label_->setAlignment(Qt::AlignCenter);
    score_label_->setStyleSheet("QLabel { font-size: 35pt; color: black; font: italic bold; }");
    
    save_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    save_button_->setStyleSheet("QPushButton { background-color: #b3b3b3; font-size: 20pt; color: black; font: italic bold; }");

    load_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    load_button_->setStyleSheet("QPushButton { background-color: #b3b3b3; font-size: 20pt; color: black; font: italic bold; }");

    restore_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    restore_button_->setStyleSheet("QPushButton { background-color: #b3b3b3; font-size: 20pt; color: black; font: italic bold; }");

    exit_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    exit_button_->setStyleSheet("QPushButton { background-color: #b3b3b3; font-size: 20pt; color: black; font: italic bold; }");
    
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board_->addWidget(blocks_[i][j] = new BlockUi(game_[i][j]), i, j);
    
    connect(save_button_, &QPushButton::clicked, this, &GameUi::save);
    connect(load_button_, &QPushButton::clicked, this, &GameUi::load);
    connect(restore_button_, &QPushButton::clicked, this, &GameUi::restore);
    connect(exit_button_, &QPushButton::clicked, this, &GameUi::exit);
    refresh();
}

// TODO: is it necessary?
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
    score_label_->setText("Score: " + QString::number(game_.score()));
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            blocks_[i][j]->update();
}

void GameUi::move(Key key) {
    try {
        if (game_.move(key)) refresh();
    } catch (GameWinException &e) {
        refresh();
        // TODO: wait for 1 second
        QMessageBox::information(this, "Win", QString("Congratulations!\n\nScore: ") + QString::number(game_.score()));
        QApplication::quit();
    } catch (GameOverException &e) {
        QMessageBox::information(this, "Lose", QString("You lose...\n\nScore: ") + QString::number(game_.score()));
        QApplication::quit();
    }
}

void GameUi::save() {
    bool ok_;
    QString text_;
    QInputDialog::getText(this, "Save", "file name", QLineEdit::Normal, text_, &ok_);
    if (ok_ && !game_.save(text_.toStdString().c_str()))
        QMessageBox::warning(this, "Save", "Cannot be stored.");
}

void GameUi::load() {
    bool ok_;
    QString text_;
    QInputDialog::getText(this, "Load", "file name", QLineEdit::Normal, text_, &ok_);
    if (ok_ && !game_.load(text_.toStdString().c_str()))
        QMessageBox::warning(this, "Load", "File not found.");
    refresh();
}

void GameUi::restore() {
    // no buffer
    if (!game_.restorable()) {
        QMessageBox::warning(this, "Restore", "There is no previously saved board in the buffer.");
        return;
    }

    // no more restore
    int restore_remain = game_.restore_remain();
    if (restore_remain == 0) {
        QMessageBox::warning(this, "Restore", "No more chance to restore the board to its previous state.");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Restore", QString("Restore the game board to its previous state?\n\nRemaining chances: ") + QString::number(game_.restore_remain()), QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        game_.restore();
        refresh();
        QMessageBox::information(this, "Restore", "The game board has been restored to its previous state! ");
    }

    std::cout << "RESTORE " << game_.restore_remain() << std::endl;
}

void GameUi::exit() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Exit", "Are you sure to quit?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}
