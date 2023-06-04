#include <QApplication>
#include <iostream>
#include <fstream>
#include "logger.hpp"
#include "game.ui.hpp"

int main(int argc, char **argv) {
    START_COUT(cout_) // start recording std::cout

    QApplication app(argc, argv); // Application for the game
    Game game; // Game object
    GameUi game_ui(game);
    game_ui.show(); // show the game ui
    int exit_code = app.exec(); // execute the application (show the window application; restore the exit code)
    
    STOP_COUT // stop recording std::cout (restore the original buffer)

    std::ofstream logger("progress.txt"); // open file output stream for log (progress.txt)
    logger << cout_.rdbuf(); // write the accumulated log to the file
    logger.close(); // close the file output stream

    return exit_code; // return with the exit code
}
