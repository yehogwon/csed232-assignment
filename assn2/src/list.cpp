/*
 * CSED232 ASSN2
 * Author: Yeho Gwon (20220358)
 * Date: 2023/03/06
 * File Name: list.cpp
 */

#include "list.hpp"

List::List() {
    head = new Node(Student()); // create a dummy node
    for (int i = 0; i < MAX_DEPT; i++) // initialize the departments array
        dept_status[i] = {"", 0}; // empty string and 0
}

List::~List() {
    Node *cur = head; // start from the dummy node
    while (cur != nullptr) {
        Node *tmp = cur; // temporarily save the current node
        cur = cur->next; // move on to the next node
        delete tmp; // free the memory of the current node
    }
}

std::string to_string(Operator op) {
    switch (op) { // return the name of the corresponding operator
        case AVG: return "Average";
        case MAX: return "Max";
        case MIN: return "Min";
    }
}

int List::get_total_dept_cnt() const {
    int cnt = 0; // count the number of departments
    for (int i = 0; i < MAX_DEPT; i++)
        cnt += min(dept_status[i].cnt, 1); // cnt += (0 or 1 <- if the number of students in the department is 0, it is not counted)
    return cnt;
}

bool List::add(Node *node) {
    if (node->data < *this) return false; // if the student is already in the list, return false
    
    // check if the department is full
    std::string dept = node->data.get_dept(); // get the department of the student to be added
    int index = -1; // index of the department in the array (negative index indicates that the node cannot be added to the list)
    bool full = get_total_dept_cnt() == MAX_DEPT; // check if the department is full
    for (int i = 0; i < MAX_DEPT; i++) { // iterate throughout the array
        // In the case of full department, check if the department is already in the array so that we can just increment the number of students in the department.
        // In the case of not full department, check if the department is not in the array so that we can add the department to the array. 
        if ((full && dept_status[i].dept == dept) || (!full && dept_status[i].dept == "")) {
            index = i; // save the index where the node can be inserted/added to the list
            break; // stop the loop
        }
    }

    // TODO: Check if it works properly (restriction on the number of students in a department)
    if (index < 0 || (full && dept_status[index].cnt == MAX_STUDENT)) return false; // the node cannot be added when there is no palce to be added or the department is full
    if (!full) // if the node can be added and the department is not full
        dept_status[index].dept = dept; // insert the department to the array
    dept_status[index].cnt++; // increment the number of students in the department by 1

    Node *prev = head; // start from the dummy node (to add the first node easily (head->next))
    while (prev != nullptr) { // iterate throughout the list
        if (prev->next == nullptr) { // if the current node is the last node
            prev->next = node; // add the node at the end of the list
            break; // stop the loop
        }
        prev = prev->next; // move on to the next node
    }

    return true; // the node has been added successfully
}

bool List::remove(Node *node) {
    if (!(node->data < *this)) return false; // if the student is not in the list, return false
    
    std::string dept = node->data.get_dept(); // get the department of the student to be removed

    Node *prev = head; // start from the dummy node (to remove the first node easily (head->next))
    while (prev != nullptr) { // iterate throughout the list
        if (prev->next->data == node->data) { // if the node to be removed is found
            prev->next = prev->next->next; // remove the node
            delete node; // free the memory of the node
            break; // stop the loop
        }
        prev = prev->next; // move on to the next node
    }

    // update the array of departments
    for (int i = 0; i < MAX_DEPT; i++) {
        if (dept_status[i].dept == dept) { // if the department is in the array already
            if (--dept_status[i].cnt == 0) dept_status[i].dept = ""; // decrease the number of students in the department by 1
            // If after decreasing the number of students it is 0, then it means there is no student in the department any more. 
            // So remove the department from the array by setting the department name to an empty string.
            break;
        }
    }

    return true; // the node has been removed successfully
}

void List::print() {
    sort(); // FIXME: Check if it works properly
    Node *cur = head->next; // start from the first node
    while (cur != nullptr) {
        Student s = cur->data; // get the student data
        std::cout << s; // print the student data
        cur = cur->next; // move on to the next node
    }
}

void List::sort() { // sort algorithm: selection sort
    Node *cur = head->next; // start from the first node
    while (cur != nullptr) { // iterate throughout the list
        Node *min = cur; // mark the current node as the minimum node (temporarily)
        Node *tmp = cur->next; // temporary cursor for nested loop
        while (tmp != nullptr) { // iterate throughout the list
            if (tmp->data < min->data) // if the current node is smaller than the node marked as the minimum node
                min = tmp; // mark the current node as the minimum node
            tmp = tmp->next; // move on to the next node
        }
        swap_node(cur, min); // swap the current node and the node marked as the minimum node
        cur = cur->next; // move on to the next node
    }
}

void List::sort(Comp comp) {
    Node *cur = head->next; // start from the first node
    while (cur != nullptr) { // iterate throughout the list
        Node *min = cur; // mark the current node as the minimum node (temporarily)
        Node *tmp = cur->next; // temporary cursor for nested loop
        while (tmp != nullptr) { // iterate throughout the list
            if (!comp(tmp->data, min->data)) // if the current node is smaller than the node marked as the minimum node (compare them using the manually defined comparison function)
                min = tmp; // mark the current node as the minimum node
            tmp = tmp->next; // move on to the next node
        }
        swap_node(cur, min); // swap the current node and the node marked as the minimum node
        cur = cur->next; // move on to the next node
    }
}

void List::pivot_dept(Operator op) {
    sort(comp_dept); // sort the list by department in ascending order

    Pivot pivots[MAX_DEPT]; // array to store the pivots
    std::string depts[MAX_DEPT]; // array to store the departments
    int num_of_pivots = 0; // the number of stored pivot data

    // initialize the pivot data
    for (int i = 0; i < MAX_DEPT; i++) {
        pivots[i] = {MIN_AGE, MAX_AGE, 0, 0}; // initialize the pivot data
        // Note that min is initialized to the maximum age and max is initialized to the minimum age.
    }

    Node *cur = head->next; // start from the first node
    while (cur != nullptr) { // iterate throughout the list
        Student s = cur->data; // get the student data
        if (num_of_pivots - 1 < 0 || depts[num_of_pivots - 1] != s.get_dept()) {
            // If it is the first iteration or the department has changed (next department has emerged)
            depts[num_of_pivots++] = s.get_dept(); // add the department to the array (move on to the next department)
        }
        
        pivots[num_of_pivots - 1].min = min(pivots[num_of_pivots - 1].min, s.get_age()); // compute the minimum age in the current department
        pivots[num_of_pivots - 1].max = max(pivots[num_of_pivots - 1].max, s.get_age()); // compute the maximum age in the current department
        pivots[num_of_pivots - 1].sum += s.get_age(); // compute the sum of ages in the current department (accumulate)
        pivots[num_of_pivots - 1].cnt++; // increase the number of students in the current department by 1
        
        cur = cur->next; // move on to the next node
    }

    std::cout << "Dept\t" << to_string(op) << std::endl;
    for (int i = 0; i < num_of_pivots; i++) {
        if (pivots[i].sum == 0) continue; // There is no student in this pivot. 
        std::cout << depts[i] << "\t"; // print the current department
        switch (op) { // print the result according to the operator
            // Note that + operator is overloaded to print the double value properly (decimal place at most 1)
            case AVG: std::cout + (double) pivots[i].sum / pivots[i].cnt << std::endl; break;
            case MAX: std::cout << pivots[i].max << std::endl; break;
            case MIN: std::cout << pivots[i].min << std::endl; break;
        }
    }

    sort(); // sort the list by the original order (dept > gender > name > age)
}

void List::pivot_gender(Operator op) {
    sort(comp_gender); // sort the list by department in ascending order

    Pivot pivots[MAX_GENDER]; // array to store the pivots
    std::string genders[MAX_GENDER]; // array to store the departments
    int num_of_pivots = 0; // the number of stored pivot data

    // initialize the pivot data
    for (int i = 0; i < MAX_GENDER; i++) {
        pivots[i] = {MIN_AGE, MAX_AGE, 0, 0}; // initialize the pivot data
        // Note that min is initialized to the maximum age and max is initialized to the minimum age.
    }

    Node *cur = head->next; // start from the first node
    while (cur != nullptr) { // iterate throughout the list
        Student s = cur->data; // get the student data
        if (num_of_pivots - 1 < 0 || genders[num_of_pivots - 1] != s.get_gender()) {
            // If it is the first iteration or the gender has changed (next gender has emerged)
            genders[num_of_pivots++] = s.get_gender(); // add the gender to the array (move on to the next gender)
        }
        
        pivots[num_of_pivots - 1].min = min(pivots[num_of_pivots - 1].min, s.get_age()); // compute the minimum age in the current gender
        pivots[num_of_pivots - 1].max = max(pivots[num_of_pivots - 1].max, s.get_age()); // compute the maximum age in the current gender
        pivots[num_of_pivots - 1].sum += s.get_age(); // compute the sum of ages in the current gender (accumulate)
        pivots[num_of_pivots - 1].cnt++; // increase the number of students in the current gender by 1
        
        cur = cur->next; // move on to the next node
    }

    std::cout << "Gender\t" << to_string(op) << std::endl;
    for (int i = 0; i < num_of_pivots; i++) {
        if (pivots[i].sum == 0) continue; // There is no student in this pivot. 
        std::cout << genders[i] << "\t"; // print the current gender
        switch (op) { // print the result according to the operator
            // Note that + operator is overloaded to print the double value properly (decimal place at most 1)
            case AVG: std::cout + (double) pivots[i].sum / pivots[i].cnt << std::endl; break;
            case MAX: std::cout << pivots[i].max << std::endl; break;
            case MIN: std::cout << pivots[i].min << std::endl; break;
        }
    }

    sort(); // sort the list by the original order (dept > gender > name > age)
}

void List::pivot_dept_gender(Operator op) {
    // In this case, additional sort is not needed because the list is already sorted by dept > gender. 

    Pivot pivots[MAX_DEPT_GENDER]; // array to store the pivots
    std::string depts[MAX_DEPT_GENDER]; // array to store the departments
    std::string genders[MAX_DEPT_GENDER]; // array to store the genders
    int num_of_pivots = 0; // the number of stored pivot data

    // initialize the pivot data
    for (int i = 0; i < MAX_DEPT_GENDER; i++) {
        pivots[i] = {MIN_AGE, MAX_AGE, 0, 0};
        // Note that min is initialized to the maximum age and max is initialized to the minimum age.
    }

    Node *cur = head->next; // start from the first node
    while (cur != nullptr) { // iterate throughout the list
        Student s = cur->data; // get the student data
        if (num_of_pivots - 1 < 0 || depts[num_of_pivots - 1] != s.get_dept() || genders[num_of_pivots - 1] != s.get_gender()) {
            // If it is the first iteration or the department/gender has changed (next department/gender has emerged)
            depts[num_of_pivots] = s.get_dept(); // add the department to the array
            genders[num_of_pivots++] = s.get_gender(); // add the gender to the array
            // Move on to the next department and gender
        }
        
        pivots[num_of_pivots - 1].min = min(pivots[num_of_pivots - 1].min, s.get_age()); // compute the minimum age in the current pivot (department & gender)
        pivots[num_of_pivots - 1].max = max(pivots[num_of_pivots - 1].max, s.get_age()); // compute the maximum age in the current pivot (department & gender)
        pivots[num_of_pivots - 1].sum += s.get_age(); // compute the sum of ages in the current pivot (department & gender) (accumulate)
        pivots[num_of_pivots - 1].cnt++; // increase the number of students in the current pivot (department & gender) by 1
        
        cur = cur->next; // move on to the next node
    }

    std::cout << "Dept\tGender\t" << to_string(op) << std::endl;
    for (int i = 0; i < num_of_pivots; i++) {
        if (pivots[i].sum == 0) continue; // There is no student in this pivot. 
        std::cout << depts[i] << "\t" << genders[i] << "\t"; // print the current department and gender
        switch (op) { // print the result according to the operator
            // Note that + operator is overloaded to print the double value properly (decimal place at most 1)
            case AVG: std::cout + (double) pivots[i].sum / pivots[i].cnt << std::endl; break;
            case MAX: std::cout << pivots[i].max << std::endl; break;
            case MIN: std::cout << pivots[i].min << std::endl; break;
        }
    }
}

bool operator<(const Student &s, const List &list) {
    Node *cur = list.head->next; // Set the cursor to the first node (skip the dummy node)
    while (cur != nullptr) { // While the cursor is not pointing to the last node (repeat until the end)
        if (s == cur->data) // if the target is found
            return true;
        cur = cur->next; // move on to the next node
    }
    return false; // the target has not been found
}
