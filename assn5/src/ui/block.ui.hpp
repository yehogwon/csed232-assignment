#ifndef __BLOCK_UI__
#define __BLOCK_UI__

#include <QLabel>
#include "block.hpp"

const int BLOCK_WIDTH = 250;
const int BLOCK_HEIGHT = 250;

class BlockUi : public QLabel {
    Q_OBJECT
private: 
    Block &block_;

    void update_style();
public: 
    BlockUi(Block &block_);

    void update_value();
};

#endif // __BLOCK_UI__