#ifndef __BLOCK_UI__
#define __BLOCK_UI__

#include <QLabel>
#include <string>
#include "../game/block.hpp"

const int BLOCK_WIDTH = 250;
const int BLOCK_HEIGHT = 250;

class BlockUi : public QLabel {
private: 
    Block &block_; // reference to the block (this block is to be shown on the screen)

public: 
    BlockUi(Block &block_); // constructor; it gets block_ reference

    void update(); // update the text and color of the block according to the block_ value
};

#endif // __BLOCK_UI__