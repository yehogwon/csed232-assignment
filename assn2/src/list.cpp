#include "list.hpp"

bool operator==(Node &n1, Node &n2) {
    return n1.data == n2.data;
}

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

void List::sort() { // sort algorithm: selection sort
    Node *cur = head->next;
    while (cur != nullptr) {
        Node *min = cur;
        Node *tmp = cur->next;
        while (tmp != nullptr) {
            if (tmp->data < min->data)
                min = tmp;
            tmp = tmp->next;
        }
        swap_node(cur, min);
        cur = cur->next;
    }
}

void List::add(Node *node) {
    Node *prev = head;
    while (prev != nullptr) {
        if (prev->next == nullptr) {
            prev->next = node;
            break;
        }
        prev = prev->next;
    }
    sort();
}

void List::remove(Node *node) {
    Node *prev = head;
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
