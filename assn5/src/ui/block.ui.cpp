#include "block.ui.hpp"

BlockUi::BlockUi(Block &block_) : block_(block_) {
    setStyleSheet("background-color: rgb(255, 255, 255); border: 5px solid black;");
    setAlignment(Qt::AlignCenter);
    setText(QString::number(block_.get_value()));
    set_color();
}

void BlockUi::set_color() {
    setStyleSheet((("background-color: " + block_.get_color()) + ";").c_str());
}
