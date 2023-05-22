#include "block.ui.hpp"

BlockUi::BlockUi(Block &block_) : block_(block_) {
    setFixedSize(BLOCK_WIDTH, BLOCK_HEIGHT);
    setAlignment(Qt::AlignCenter);
    setText(QString::number(block_.get_value()));
    update_style();
}

void BlockUi::update_style() {
    // TODO: check border color
    setStyleSheet((std::string("QLabel { border-style: outset; border-width: 5px; border-color: green; font: 70pt; font: bold; color: black; ") + "background-color: " + block_.get_color() + ";}").c_str());
}
