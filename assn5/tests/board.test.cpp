#include "test.h"
#include "game/board.hpp"

bool constructor_test() {
    Board board_;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) 
            if (board_[i][j].value() != 0) return false;

    return true;
}

bool index_test() {
    Board board_;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) 
            board_[i][j].value() = i + j * 3;
    
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) 
            if (board_[i][j].value() != i + j * 3) return false;
    
    Board board__ = board_;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) 
            if (board__[i][j].value() != i + j * 3) return false;
    
    return true;
}

bool move_test() {
    std::vector<std::pair<BoardArray, BoardArray>> test_cases = { // before, after
        std::make_pair<BoardArray, BoardArray>({{ // LEFT
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(2), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}
        }}, {{
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(2), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}
        }}), 
        std::make_pair<BoardArray, BoardArray>({{ // UP
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(4), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(8), Block(32)}}, 
            {{Block(4), Block(0), Block(4), Block(0)}}
        }}, {{
            {{Block(4), Block(4), Block(8), Block(32)}}, 
            {{Block(0), Block(0), Block(4), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}
        }}), 
        std::make_pair<BoardArray, BoardArray>({{ // RIGHT
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(4), Block(0), Block(0)}}, 
            {{Block(2), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}
        }}, {{
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(4)}}, 
            {{Block(0), Block(0), Block(0), Block(2)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}
        }}), 
        std::make_pair<BoardArray, BoardArray>({{ // DOWN
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(8)}}, 
            {{Block(0), Block(32), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}
        }}, {{
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(32), Block(0), Block(8)}}
        }}), 
        std::make_pair<BoardArray, BoardArray>({{ // LEFT
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}
        }}, {{
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}
        }}), 
        std::make_pair<BoardArray, BoardArray>({{ // UP
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}
        }}, {{
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}
        }}), 
        std::make_pair<BoardArray, BoardArray>({{ // RIGHT
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}
        }}, {{
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}
        }}), 
        std::make_pair<BoardArray, BoardArray>({{ // DOWN
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}
        }}, {{
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}
        }}), 
        std::make_pair<BoardArray, BoardArray>({{ // LEFT
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}
        }}, {{
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}
        }}), 
        std::make_pair<BoardArray, BoardArray>({{ // UP
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}
        }}, {{
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}
        }}), 
        std::make_pair<BoardArray, BoardArray>({{ // RIGHT
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}
        }}, {{
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}
        }}), 
        std::make_pair<BoardArray, BoardArray>({{ // DOWN
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}
        }}, {{
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}, 
            {{Block(0), Block(0), Block(0), Block(0)}}
        }}), 
    };

    Board board_;
    for (int i = 0; i < test_cases.size(); i++) {
        BoardArray bef = test_cases[i].first, after = test_cases[i].second;
        for (int j = 0; j < SIZE; j++)
            for (int k = 0; k < SIZE; k++)
                board_[j][k] = bef[j][k];
        switch (i % 4) {
            case 0: board_.move<Left>(); break;
            case 1: board_.move<Up>(); break;
            case 2: board_.move<Right>(); break;
            case 3: board_.move<Down>(); break;
        }
        for (int j = 0; j < SIZE; j++)
            for (int k = 0; k < SIZE; k++)
                if (board_[j][k] != after[j][k]) {
                    std::cout << "Failed at " << i << "th test case :: (row: " << j + 1 << ", col: " << k + 1 << ")" << std::endl;
                    return false;
                }
    }
    
    return true;
}

// TODO: test pull(), merge() : they are private methods

int main(int argc, char **argv) {
    if (argc != 2) return 1; // invalid arguments (requires test name)

    std::vector<std::pair<std::string, fp>> tests {
        unittest("Board::Constructor", constructor_test), 
        unittest("Board::Indexing", index_test), 
        unittest("Board::Move", move_test)
    };
    return test(argv[1], tests);
}
