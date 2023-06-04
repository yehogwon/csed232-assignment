#include "game.ui.hpp"

GameUi::GameUi(Game &game_) : game_(game_), block_(false) {
    resize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setStyleSheet("QWidget { background-color : #d9d9d9; }"); // set background color to gray
    
    root_ = new QHBoxLayout(this);
    board_ = new QGridLayout();
    pane_ = new QVBoxLayout();
    score_label_ = new QLabel();
    restore_button_ = new QPushButton();
    exit_button_ = new QPushButton();
    win_timer_ = new QTimer(this);

    root_->addLayout(board_);
    root_->addLayout(pane_);
    root_->setSpacing(0); // remove spacing between board_ and pane_
    root_->setContentsMargins(0, 0, 0, 0); // remove margins of root_ around the layout

    board_->setSpacing(10); // set spacing between blocks
    board_->setAlignment(Qt::AlignLeft | Qt::AlignTop); // set alignment of the board (to the left and top)
    board_->setContentsMargins(0, 0, 0, 0); // remove contents margin of board_ around the layout

    pane_->setAlignment(Qt::AlignRight | Qt::AlignTop); // set alignment of the pane (to the right and top)
    pane_->setSpacing(20); // set spacing between score_label_, restore_button_, and exit_button_
    pane_->addWidget(score_label_);
    pane_->addStretch(1); // space between label and buttons (label -> top, buttons -> bottom)
    pane_->addWidget(restore_button_);
    pane_->addWidget(exit_button_);

    score_label_->setText("Score: 0"); // default text
    score_label_->setAlignment(Qt::AlignCenter); // set alignment of the score_label_ (to the center; text alignment)
    score_label_->setStyleSheet("QLabel { font-size: 35pt; color: black; font: italic bold; }");

    restore_button_->setText("Restore"); // button label (text)
    restore_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT); // button size
    restore_button_->setStyleSheet("QPushButton { background-color: #b3b3b3; font-size: 20pt; color: black; font: italic bold; }"); // button style

    exit_button_->setText("Exit"); // button label (text)
    exit_button_->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT); // button size
    exit_button_->setStyleSheet("QPushButton { background-color: #b3b3b3; font-size: 20pt; color: black; font: italic bold; }"); // button style
    
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board_->addWidget(blocks_[i][j] = new BlockUi(game_[i][j]), i, j); // add block to the board (16 blocks)
    
    connect(restore_button_, &QPushButton::clicked, this, &GameUi::restore); // button click callback
    connect(exit_button_, &QPushButton::clicked, this, &GameUi::exit); // button click callback
    connect(win_timer_, SIGNAL(timeout()), this, SLOT(win())); // timer callback (when timeout signal is emitted)
    refresh(); // initially refresh the board
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
    score_label_->setText("Score: " + QString::number(game_.score())); // update score
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            blocks_[i][j]->update(); // update block (text & color)
}

void GameUi::move(key key) {
    if (block_) return; // if input is blocked, return (ignore the key input)
    try {
        if (game_.move(key)) refresh(); // move the blocks accordingly and if it has been moved, refresh the board
    } catch (GameWinException &e) { // user won the game
        block_ = true; // block the user input
        refresh(); // refresh the board
        win_timer_->start(1000); // after 1000ms (1s) show a dialog (win)
    } catch (GameOverException &e) { // game over
        QMessageBox::information(this, "Lose", QString("You lose...\n\nScore: ") + QString::number(game_.score())); // show a lose dialog
        QApplication::quit(); // quit the game
    }
}

void GameUi::win() {
    QMessageBox::information(this, "Win", QString("Congratulations!\n\nScore: ") + QString::number(game_.score())); // win the game -> show the dialog (score)
    QApplication::quit(); // quit the application as soon as the dialog is closed
}

void GameUi::restore() {
    if (!game_.restorable()) { // cannot be restored (no previous state in the buffer)
        QMessageBox::warning(this, "Restore", "There is no previously saved board in the buffer.");
        return;
    }

    int restore_remain = game_.restore_remain();
    if (restore_remain == 0) { // no more chance to restore
        QMessageBox::warning(this, "Restore", "No more chance to restore the board to its previous state.");
        return;
    }

    QMessageBox::StandardButton reply; // dialog box (yes / no)
    reply = QMessageBox::question(this, "Restore", QString("Restore the game board to its previous state?\n\nRemaining chances: ") + QString::number(game_.restore_remain()), QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) { // if the user confirmed to restore
        game_.restore(); // restore
        refresh(); // refresh the game board
        QMessageBox::information(this, "Restore", "The game board has been restored to its previous state! "); // notify the user
    }
}

void GameUi::exit() {
    QMessageBox::StandardButton reply; // dialog box (yes / no)
    reply = QMessageBox::question(this, "Exit", "Are you sure to quit?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) { // if user chose yes
        QApplication::quit(); // quit the application
    }
}
