#ifndef __GAME__UI__
#define __GAME__UI__

#include <QtWidgets>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QKeyEvent>
#include <QTimer>

#include <iostream>
#include <array>

#include "game.hpp"
#include "block.ui.hpp"
#include "status.hpp"

// window size
const int WINDOW_WIDTH = 1300;
const int WINDOW_HEIGHT = 1000;

// button size
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;

class GameUi : public QWidget {
    Q_OBJECT
private: 
    QHBoxLayout *root_; // the overall layout
    QGridLayout *board_; // grid for 4x4 blocks
    QVBoxLayout *pane_; // pane layout for score and two buttons
    QLabel *score_label_; // label for score
    QPushButton *restore_button_; // button for restore
    QPushButton *exit_button_; // button for exit
    QTimer *win_timer_; // timer for win animation (wait for a specific time and show the dialog)

    Game &game_; // game object (this class is updated following the value of game_)
    std::array<std::array<BlockUi*, SIZE>, SIZE> blocks_; // 4x4 blocks

    bool block_; // whether the game is blocked (cannot move) <- after the game is over (user win), the game is blocked

    void refresh(); // refresh the game (update the score, the value & color of the blocks)
    void move(key key); // repond to the key event (move the blocks)
    void restore(); // restore the game (get back to the previous state; button event)
    void exit(); // exit the game (button event)

private slots: 
    void win(); // slots for win animation (callback for win_timer_)

protected: 
    void keyPressEvent(QKeyEvent *event) override; // override the keyPressEvent (to respond to the key event, particularly the arrow keys)

public: 
    GameUi(Game &game_); // constructor of the class
};

#endif // __GAME__UI__