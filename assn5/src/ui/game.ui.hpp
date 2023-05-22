#ifndef __GAME__UI__
#define __GAME__UI__

#include <QtWidgets>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

#include <array>

#include "game.hpp"
#include "block.ui.hpp"

const int WINDOW_WIDTH = 1300;
const int WINDOW_HEIGHT = 1000;

class GameUi : public QWidget {
    Q_OBJECT
private: 
    QGridLayout *board_;
    QLabel *score_label_;
    QPushButton *restore_button_;
    QPushButton *exit_button_;

    Game &game_;
    std::array<std::array<BlockUi*, 4>, 4> blocks_;

public: 
    GameUi(Game &game_);
    ~GameUi();
};

#endif // __GAME__UI__