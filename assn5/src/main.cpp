#include <QApplication>
#include <iostream>
#include <fstream>
#include "logger.hpp"
#include "game.ui.hpp"

int main(int argc, char **argv) {
    START_COUT(cout_) // start recording std::cout

    QApplication app(argc, argv);
    Game game;
    GameUi game_ui(game);
    game_ui.show();
    int exit_code = app.exec();
    
    STOP_COUT // stop recording std::cout

    std::ofstream logger("progress.txt");
    logger << cout_.rdbuf();
    logger.close();

    return exit_code;
}
