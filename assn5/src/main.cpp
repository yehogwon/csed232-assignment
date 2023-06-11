#include <QApplication>
#include <iostream>
#include <fstream>
#include "ui/game.ui.hpp"

int main(int argc, char **argv) {
    std::ofstream logger("progress.txt"); // open file output stream for log (progress.txt)
    std::streambuf *__sbuf__ = std::cout.rdbuf(); // original buffer of std::cout
    std::cout.rdbuf(logger.rdbuf()); // redirect std::cout to logger (progress.txt)

    QApplication app(argc, argv); // Application for the game
    Game game; // Game object
    GameUi game_ui(game);
    game_ui.show(); // show the game ui
    int exit_code = app.exec(); // execute the application (show the window application; restore the exit code)
    
    std::cout.rdbuf(__sbuf__); // restore the original buffer of std::cout
    logger.close(); // close the file output stream

    return exit_code; // return with the exit code
}
