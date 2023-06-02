#include "block.ui.hpp"

BlockUi::BlockUi(Block &block_) : block_(block_) {
    setFixedSize(BLOCK_WIDTH, BLOCK_HEIGHT); // set block size
    setAlignment(Qt::AlignCenter); // set text alignment (to the center)
    update(); // update the value & color of the block
}

void BlockUi::update() {
    setText(block_.value() != 0 ? QString::number(block_.value()) : ""); // if the value is zero (empty), show nothing but otherwise, show the text
    setStyleSheet((std::string("QLabel { ") + "background: " + block_.color() + "; color: black; border-style: solid; font: 70pt; font: bold; }").c_str()); // set the background color of the block accordingly to the value
}
