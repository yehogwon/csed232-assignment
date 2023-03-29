#include "node.hpp"

bool operator==(Node &n1, Node &n2) {
    return n1.data == n2.data;
}