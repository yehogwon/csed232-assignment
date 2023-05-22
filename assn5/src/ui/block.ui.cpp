#include "block.ui.hpp"

BlockUi::BlockUi(Block &block_) : block_(block_) {
    setFixedSize(BLOCK_WIDTH, BLOCK_HEIGHT);
    setAlignment(Qt::AlignCenter);
    update_value();
}

void BlockUi::update_style() {
    // TODO: check border color
    setStyleSheet((std::string("QLabel { border-style: outset; border-width: 5px; border-color: green; font: 70pt; font: bold; color: black; ") + "background-color: " + block_.color() + ";}").c_str());
}

void BlockUi::update_value() {
    setText(QString::number(block_.value()));
    update_style();
}
