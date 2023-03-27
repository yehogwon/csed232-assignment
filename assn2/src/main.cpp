// TODO: Handle some exceptions
// TODO: Update error messages
#include <iostream>
#include <cmath>
#include "student.hpp"
#include "list.hpp"

void show_menu();
bool add_student(List &student_list);
bool delete_student(List &student_list);
void print(List &student_list);
void pivot_table(List &student_list);

int main() {
    List student_list;

    int menu;
    bool stop = false;
    do {
        show_menu();
        std::cout << "Selection: ";
        std::cin >> menu;

        switch (menu) {
            case 1: // Add
                add_student(student_list);
                break;
            case 2: // Delete
                delete_student(student_list);
                break;
            case 3: // Print
                print(student_list);
                break;
            case 4: // Pivot Table
                pivot_table(student_list);
                break;
            case 5: 
                stop = true;
                return 0;
        }
    } while (!stop);

    return 0;
}

void show_menu() {
    std::cout << "----------MENU----------" << std::endl;
    std::cout << "1. Add a student" << std::endl;
    std::cout << "2. Delete a student" << std::endl;
    std::cout << "3. Print the student's list" << std::endl;
    std::cout << "4. Pivot Table" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "------------------------" << std::endl;
}

// TODO: Check if duplication check works properly
bool add_student(List &student_list) {
    Student s;
    s.input_info();
    
    if (s < student_list) {
        std::cout << "The student already exists." << std::endl;
        return false;
    } else {
        student_list.add(new Node{s, nullptr});
        std::cout << "A student is added in table!" << std::endl;
        return true;
    }
}

bool delete_student(List &student_list) {
    Student s;
    s.input_info();

    if (s < student_list) {
        student_list.remove(new Node{s, nullptr});
        std::cout << "Deleted!" << std::endl;
        return true;
    } else {
        std::cout << "Can't Delete it" << std::endl;
        return false;
    }
}

void print(List &student_list) {
    std::cout << "Dept\tGender\tName\tAge" << std::endl;
    Node *cur = (student_list.head)->next;
    while (cur != nullptr) {
        Student s = cur->data;
        std::cout << s << std::endl;
        cur = cur->next;
    }
}

void pivot_table(List &student_list) {
    int category, function;
    std::cout << "-----------Category-----------" << std::endl;
    std::cout << "1. Dept" << std::endl;
    std::cout << "2. Gender" << std::endl;
    std::cout << "3. Dept and Gender" << std::endl;
    std::cout << "------------------------------" << std::endl;
    std::cout << "Selection: ";
    std::cin >> category;

    std::cout << "-----------Function-----------" << std::endl;
    std::cout << "1. Average" << std::endl;
    std::cout << "2. Max" << std::endl;
    std::cout << "3. Min" << std::endl;
    std::cout << "------------------------------" << std::endl;
    std::cout << "Selection: ";
    std::cin >> function;

    switch (category) {
        case 1: // Dept
            student_list.pivot_dept(static_cast<Operator>(function));
            break;
        case 2: // Gender
            student_list.pivot_gender(static_cast<Operator>(function));
            break;
        case 3: // Dept + Gender
            student_list.pivot_dept_gender(static_cast<Operator>(function));
            break;
        default: 
            std::cout << "Unexpected Input" << std::endl;
            throw std::runtime_error("Unexpected Input");
    }
}
