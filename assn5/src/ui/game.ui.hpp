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

#include <iostream>
#include <array>

#include "game.hpp"
#include "block.ui.hpp"
#include "status.hpp"

const int WINDOW_WIDTH = 1300;
const int WINDOW_HEIGHT = 1000;

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;

class GameUi : public QWidget {
    Q_OBJECT
private: QHBoxLayout *root_;
    QGridLayout *board_;
    QVBoxLayout *pane_;
    QLabel *score_label_;
    QPushButton *save_button_;
    QPushButton *load_button_;
    QPushButton *restore_button_;
    QPushButton *exit_button_;

    QInputDialog *text_dialog_;

    Game &game_;
    std::array<std::array<BlockUi*, SIZE>, SIZE> blocks_;

    void refresh();
    void move(Key key);
    void save();
    void load();
    void restore();
    void exit();

protected: 
    void keyPressEvent(QKeyEvent *event) override;

public: 
    GameUi(Game &game_);
    ~GameUi();
};

#endif // __GAME__UI__