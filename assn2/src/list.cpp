#include "list.hpp"

Node::Node(const Student &data, Node *next)
    : data(data), next(next) {}

void List::sort(std::string metric) {
    throw std::runtime_error("List::sort() not implemented");
}

Node& List::operator[](int i) {
    if (i < 0 || i >= count)
        throw std::out_of_range("List index out of range");
    Node *node = head->next;
    for (int j = 0; j < i; j++)
        node = node->next;
    return node;
}

void save_node(List &list, Node *node) {
    list[list.count - 1].next = node;
}

void delete_node(List &list, Node *node) {
    Node *prev = &list[0];
    for (int i = 0; i < list.count; i++) {
        if (prev->next == node) {
            prev->next = node->next;
            delete node;
            break;
        }
        prev = prev->next;
    }
}

bool operator<(const Student &s, const List &list) {
    for (int i = 0; i < list.dept_cnt; i++)
        if (s[i] == list[i].data)
            return true;
    return false
}
