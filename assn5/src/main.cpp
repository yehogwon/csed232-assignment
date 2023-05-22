#include <QApplication>
#include "game.ui.hpp"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    Game game;
    GameUi game_ui(game);
    game_ui.show();
    return app.exec();
}
