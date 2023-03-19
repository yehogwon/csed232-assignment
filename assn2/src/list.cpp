#include "list.hpp"

void List::sort(std::string metric) {
    throw std::runtime_error("List::sort() not implemented");
}

Student& List::operator[](int i) {
    if (i < 0 || i >= count)
        throw std::out_of_range("List index out of range");
    Node *node = head->next;
    for (int j = 0; j < i; j++)
        node = node->next;
    return node->data;
}

bool operator<(const Student &s, const List &list) {
    for (int i = 0; i < list.dept_cnt; i++)
        if (s[i] == list[i].data)
            return true;
    return false
}
