#include "list.hpp"

List::List() {
    head = new Node{Student(), nullptr};
}

List::~List() {
    Node *cur = head;
    while (cur != nullptr) {
        Node *tmp = cur;
        cur = cur->next;
        delete tmp;
    }
}

void List::sort() {
    throw std::runtime_error("Not Implemented");
}

void save_node(List &list, Node *node) {
    Node *prev = list.head;
    while (prev != nullptr) {
        if (prev->next == nullptr) {
            prev->next = node;
            break;
        }
        prev = prev->next;
    }
    // TODO: Call sort() here
}

void delete_node(List &list, Node *node) {
    Node *prev = list.head;
    while (prev != nullptr) {
        if (prev->next->data == node->data) {
            prev->next = node->next;
            delete node;
            break;
        }
        prev = prev->next;
    }
}

void swap_node(Node *node1, Node *node2) {
    Student tmp = node1->data;
    node1->data = node2->data;
    node2->data = tmp;
}

bool operator<(const Student &s, const List &list) {
    Node *cur = list.head->next;
    while (cur != nullptr) {
        if (s == cur->data)
            return true;
        cur = cur->next;
    }
    return false;
}
