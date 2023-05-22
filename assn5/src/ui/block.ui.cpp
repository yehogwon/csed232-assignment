#include "block.ui.hpp"

BlockUi::BlockUi(Block &block_) : block_(block_) {
    setFixedSize(BLOCK_WIDTH, BLOCK_HEIGHT);
    setStyleSheet("QLabel { border-style: solid; font: 70pt; font: bold; color: black; }");
    setAlignment(Qt::AlignCenter);
    setText(QString::number(block_.get_value()));
    set_background_color();
}

void BlockUi::set_background_color() {
    setStyleSheet((std::string("QLabel { border-style: solid; font: 70pt; font: bold; color: black; ") + "background-color: " + block_.get_color() + ";}").c_str());
}
