#include "status.hpp"

const char* to_string(Key key) {
    switch (key) {
        case UP: return "UP";
        case DOWN: return "DOWN";
        case LEFT: return "LEFT";
        case RIGHT: return "RIGHT";
        default: return "";
    }
}
