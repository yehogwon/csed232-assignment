#include <QApplication>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "game.ui.hpp"

int main(int argc, char **argv) {
    std::stringstream cout_;
    std::streambuf *sbuf__ = std::cout.rdbuf();
    std::cout.rdbuf(cout_.rdbuf());

    QApplication app(argc, argv);
    Game game;
    GameUi game_ui(game);
    game_ui.show();
    int exit_code = app.exec();
    
    std::cout.rdbuf(sbuf__);
    std::ofstream logger("progress.txt");
    logger << cout_.rdbuf();
    logger.close();

    return exit_code;
}
