#include "node.hpp"

bool operator==(Node &n1, Node &n2) {
    return n1.data == n2.data;
}

void swap_node(Node *node1, Node *node2) {
    Student tmp = node1->data;
    node1->data = node2->data;
    node2->data = tmp;
}
