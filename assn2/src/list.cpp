#include "list.hpp"

List::List() : count(0), dept_cnt(0) {
    head = new Node();
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
    for (int i = 0; i < count; i++) {
        Node *cur = head->next;
        for (int j = 0; j < count - i - 1; j++) {
            if (cur->data > cur->next->data) {
                swap_node(cur, cur->next);
            }
            cur = cur->next;
        }
    }
}

void save_node(List &list, Node *node) {
    Node *prev = list.head;
    list.count++;
    for (int i = 0; i < list.count; i++) {
        if (prev->next == nullptr) {
            prev->next = node;
            break;
        }
        prev = prev->next;
    }
    list.sort();
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

void swap_node(Node *node1, Node *node2) {
    Student tmp = node1->data;
    node1->data = node2->data;
    node2->data = tmp;
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
