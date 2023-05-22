#ifndef __BLOCK_UI__
#define __BLOCK_UI__

#include <QLabel>
#include <block.hpp>

class BlockUi : public QLabel {
    Q_OBJECT
private: 
    Block &block_;

    void set_color();
public: 
    BlockUi(Block &block_);
};

#endif // __BLOCK_UI__