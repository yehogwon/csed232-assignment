#include "block.ui.hpp"

BlockUi::BlockUi(Block &block_) : block_(block_) {
    setFixedSize(BLOCK_WIDTH, BLOCK_HEIGHT);
    setAlignment(Qt::AlignCenter);
    update();
}

void BlockUi::update() {
    setText(block_.value() != 0 ? QString::number(block_.value()) : "");
    setStyleSheet((std::string("QLabel { ") + "background: " + block_.color() + "; color: black; border-style: solid; font: 70pt; font: bold; }").c_str());
}
