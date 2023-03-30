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

std::string List::to_string(Operator op) const {
    switch (op) {
        case AVG: return "Average";
        case MAX: return "Max";
        case MIN: return "Min";
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
            if (!comp(tmp->data, min->data))
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

void List::pivot_dept(Operator op) {
    sort(comp_dept);

    Pivot pivots[MAX_DEPT];
    std::string depts[MAX_DEPT];
    int num_of_pivots = 0;

    for (int i = 0; i < MAX_DEPT; i++) {
        pivots[i] = {0, MAX_AGE, 0, 0};
    }

    Node *cur = head->next;
    while (cur != nullptr) {
        Student s = cur->data;
        if (num_of_pivots - 1 < 0 || depts[num_of_pivots - 1] != s.get_dept()) {
            depts[num_of_pivots++] = s.get_dept();
        }
        
        pivots[num_of_pivots - 1].min = min(pivots[num_of_pivots - 1].min, s.get_age());
        pivots[num_of_pivots - 1].max = max(pivots[num_of_pivots - 1].max, s.get_age());
        pivots[num_of_pivots - 1].sum += s.get_age();
        pivots[num_of_pivots - 1].cnt++;
        
        cur = cur->next;
    }

    std::cout << "Dept\t" << to_string(op) << std::endl;
    for (int i = 0; i < num_of_pivots; i++) {
        if (pivots[i].sum == 0) continue; // There is no student in this pivot. 
        std::cout << depts[i] << "\t";
        switch (op) {
            // FIXME: The above decimal place modification shows even when it is an integer. 
            case AVG: std::cout << std::fixed << std::setprecision(1) << (double) pivots[i].sum / pivots[i].cnt << std::endl; break;
            case MAX: std::cout << pivots[i].max << std::endl; break;
            case MIN: std::cout << pivots[i].min << std::endl; break;
        }
    }

    sort();
}

void List::pivot_gender(Operator op) {
    sort(comp_gender);

    Pivot pivots[MAX_GENDER];
    std::string genders[MAX_GENDER];
    int num_of_pivots = 0;

    for (int i = 0; i < MAX_GENDER; i++) {
        pivots[i] = {0, MAX_AGE, 0, 0};
    }

    Node *cur = head->next;
    while (cur != nullptr) {
        Student s = cur->data;
        if (num_of_pivots - 1 < 0 || genders[num_of_pivots - 1] != s.get_gender()) {
            genders[num_of_pivots++] = s.get_gender();
        }
        
        pivots[num_of_pivots - 1].min = min(pivots[num_of_pivots - 1].min, s.get_age());
        pivots[num_of_pivots - 1].max = max(pivots[num_of_pivots - 1].max, s.get_age());
        pivots[num_of_pivots - 1].sum += s.get_age();
        pivots[num_of_pivots - 1].cnt++;
        
        cur = cur->next;
    }

    std::cout << "Gender\t" << to_string(op) << std::endl;
    for (int i = 0; i < num_of_pivots; i++) {
        if (pivots[i].sum == 0) continue; // There is no student in this pivot. 
        std::cout << genders[i] << "\t";
        switch (op) {
            case AVG: std::cout << std::fixed << std::setprecision(1) << (double) pivots[i].sum / pivots[i].cnt << std::endl; break;
            case MAX: std::cout << pivots[i].max << std::endl; break;
            case MIN: std::cout << pivots[i].min << std::endl; break;
        }
    }

    sort();
}

void List::pivot_dept_gender(Operator op) {
    Pivot pivots[MAX_DEPT_GENDER];
    std::string depts[MAX_DEPT_GENDER];
    std::string genders[MAX_DEPT_GENDER];
    int num_of_pivots = 0;

    for (int i = 0; i < MAX_DEPT_GENDER; i++) {
        pivots[i] = {0, MAX_AGE, 0, 0};
    }

    Node *cur = head->next;
    while (cur != nullptr) {
        Student s = cur->data;
        if (num_of_pivots - 1 < 0 || depts[num_of_pivots - 1] != s.get_dept() || genders[num_of_pivots - 1] != s.get_gender()) {
            depts[num_of_pivots] = s.get_dept();
            genders[num_of_pivots++] = s.get_gender();
        }
        
        pivots[num_of_pivots - 1].min = min(pivots[num_of_pivots - 1].min, s.get_age());
        pivots[num_of_pivots - 1].max = max(pivots[num_of_pivots - 1].max, s.get_age());
        pivots[num_of_pivots - 1].sum += s.get_age();
        pivots[num_of_pivots - 1].cnt++;
        
        cur = cur->next;
    }

    std::cout << "Dept\tGender\t" << to_string(op) << std::endl;
    for (int i = 0; i < num_of_pivots; i++) {
        if (pivots[i].sum == 0) continue; // There is no student in this pivot. 
        std::cout << depts[i] << "\t" << genders[i] << "\t";
        switch (op) {
            case AVG: std::cout << std::fixed << std::setprecision(1) << (double) pivots[i].sum / pivots[i].cnt << std::endl; break;
            case MAX: std::cout << pivots[i].max << std::endl; break;
            case MIN: std::cout << pivots[i].min << std::endl; break;
        }
    }
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
