#include "list.hpp"

List::List() {
    head = new Node(Student(), nullptr);
    for (int i = 0; i < MAX_DEPT; i++)
        dept_status[i] = {"", 0};
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

int List::get_total_dept_cnt() const {
    int cnt = 0;
    for (int i = 0; i < MAX_DEPT; i++)
        cnt += min(dept_status[i].cnt, 1); // 0 or 1
    return cnt;
}

bool List::add(Node *node) {
    if (node->data < *this) return false;
    
    std::string dept = node->data.get_dept();
    int index = -1;
    bool full = get_total_dept_cnt() == MAX_DEPT;
    for (int i = 0; i < MAX_DEPT; i++) {
        if ((full && dept_status[i].dept == dept) || (!full && dept_status[i].dept == "")) {
            index = i;
            break;
        }
    }

    if (index < 0) return false;
    if (!full)
        dept_status[index].dept = dept;
    dept_status[index].cnt++;

    Node *prev = head;
    while (prev != nullptr) {
        if (prev->next == nullptr) {
            prev->next = node;
            break;
        }
        prev = prev->next;
    }
    sort(); // TODO: Move it to print()?

    return true;
}

bool List::remove(Node *node) {
    if (!(node->data < *this)) return false;
    
    std::string dept = node->data.get_dept();

    Node *prev = head;
    while (prev != nullptr) {
        if (prev->next->data == node->data) {
            prev->next = prev->next->next;
            delete node;
            break;
        }
        prev = prev->next;
    }

    for (int i = 0; i < MAX_DEPT; i++) {
        if (dept_status[i].dept == dept) {
            if (--dept_status[i].cnt == 0) dept_status[i].dept = "";
            break;
        }
    }

    return true;
}

void List::print() const {
    Node *cur = head->next;
    while (cur != nullptr) {
        Student s = cur->data;
        std::cout << s;
        cur = cur->next;
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
            case AVG: std::cout + (double) pivots[i].sum / pivots[i].cnt << std::endl; break;
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
            case AVG: std::cout + (double) pivots[i].sum / pivots[i].cnt << std::endl; break;
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
            case AVG: std::cout + (double) pivots[i].sum / pivots[i].cnt << std::endl; break;
            case MAX: std::cout << pivots[i].max << std::endl; break;
            case MIN: std::cout << pivots[i].min << std::endl; break;
        }
    }
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
