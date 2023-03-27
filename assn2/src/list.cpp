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

void List::sort(Comp comp) {
    Node *cur = head->next;
    while (cur != nullptr) {
        Node *min = cur;
        Node *tmp = cur->next;
        while (tmp != nullptr) {
            if (!comp(min->data, tmp->data))
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
            prev->next = prev->next->next;
            delete node;
            break;
        }
        prev = prev->next;
    }
}

void List::pivot_dept(int op) {
    sort(comp_dept);

    Pivot pivots[MAX_DEPT];
    std::string depts[MAX_DEPT];
    int num_of_depts = 0;

    for (int i = 0; i < MAX_DEPT; i++) {
        pivots[i] = {0, INT_MAX, 0, 0};
    }

    Node *cur = head->next;
    while (cur != nullptr) {
        Student s = cur->data;
        if (num_of_depts - 1 < 0 || depts[num_of_depts - 1] != s.get_dept()) {
            depts[num_of_depts++] = s.get_dept();
        }
        
        pivots[num_of_depts - 1].min = min(pivots[num_of_depts - 1].min, s.get_age());
        pivots[num_of_depts - 1].max = max(pivots[num_of_depts - 1].max, s.get_age());
        pivots[num_of_depts - 1].sum += s.get_age();
        pivots[num_of_depts - 1].cnt++;
        
        cur = cur->next;
    }

    // TODO: Print them
    std::cout << "Dept\t???" << std::endl;
    for (int i = 0; i < num_of_depts; i++)
        std::cout << depts[i] << "\t" << "CAL_RESULT" << std::endl;

    sort();
}

void List::pivot_gender(int op) {
    throw "Not implemented yet";
}

void List::pivot_dept_gender(int op) {
    // without sorting (already sorted)
    throw "Not implemented yet";
}

template <typename T>
T max(T a, T b) {
    return a > b ? a : b;
}

template <typename T>
T min(T a, T b) {
    return a < b ? a : b;
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
