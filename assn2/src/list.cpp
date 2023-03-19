#include "list.hpp"

Node::Node(const Student &data, Node *next)
    : data(data), next(next) {}

void List::sort(std::string metric) {
    // TODO: Check how to implement it; lack of instructions
    throw std::runtime_error("List::sort() not implemented");
}

void save_node(List &list, Node *node) {
    Node *prev = (list.head)->next;
    for (int i = 0; i < list.count; i++) {
        if (prev->next == nullptr) {
            prev->next = node;
            break;
        }
        prev = prev->next;
    }
    list.count++;
    // TODO: call list.sort() here
}

void delete_node(List &list, Node *node) {
    Node *prev = list.head;
    for (int i = 0; i < list.count; i++) {
        if (prev->next->data == node->data) {
            prev->next = node->next;
            delete node;
            break;
        }
        prev = prev->next;
    }
    list.count--;
}

bool operator<(const Student &s, const List &list) {
    Node *cur = list.head->next;
    for (int i = 0; i < list.count; i++) {
        if (s == cur->data)
            return true;
        cur = cur->next;
    }
    return false;
}
