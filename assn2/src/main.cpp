#include <iostream>
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

bool add_student(List &student_list) {
    Student s;
    s.input_info();
    
    if (s < student_list) {
        std::cout << "The student already exists." << std::endl;
        return false;
    } else {
        save_node(student_list, new Node(s));
        std::cout << "A student is added in table!" << std::endl;
        return true;
    }
}

bool delete_student(List &student_list) {
    Student s;
    s.input_info();

    if (s < student_list) {
        Node *node = new Node(s);
        node->next = nullptr;
        delete_node(student_list, node);
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
    for (int i = 0; i < student_list.count; i++) {
        Student s = cur->data;
        std::cout << s.dept << "\t" << s.gender << "\t" << s.name << "\t" << s.age << std::endl;
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

    throw std::runtime_error("Not implemented perfectly");
}
