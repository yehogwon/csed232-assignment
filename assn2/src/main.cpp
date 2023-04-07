/*
 * CSED232 ASSN2
 * Author: Yeho Gwon (20220358)
 * Date: 2023/03/05
 * File Name: main.cpp
 */

#include <iostream>
#include <cmath>
#include "student.hpp"
#include "list.hpp"
#include "io.hpp"
#include "exception.hpp"

/**
 * @brief print the main menu
 * @return none
 */
void show_menu();

/**
 * @brief add a student to the list unless he/she is in student_list (get student information from user)
 * @param student_list the list of students to add a student in
 * @return true if the student is successfully added, false otherwise
 */
bool add_student(List &student_list);

/**
 * @brief delete a student from the list if he/she is in student_list (get student information from user)
 * @param student_list the list of students to delete a student from
 * @return true if the student is successfully deleted, false otherwise
 */
bool delete_student(List &student_list);

/**
 * @brief print the list of students
 * @param student_list the list of students to print
 * @return none
 */
void print(List &student_list);

/**
 * @brief process and print the pivot table of students
 * @param student_list the list of students to conduct on
 * @return none
 */
void pivot_table(List &student_list);

int main() {
    List student_list; // the list of students

    int menu; // the menu selection from user
    bool stop = false; // the flag to stop the program
    do {
        show_menu();
        try {
            // get the menu selection from user within the range of 1 to 5
            Format::range_input(std::cin, std::cout, "Selection: ", menu, 1, 5);
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
                    std::cout << "Exit!" << std::endl;
                    stop = true; // stop the program
                    return 0;
            }
        } catch (InterruptedInputException &e) { // If the user input is interrupted (the user wants to get back to the main menu)
            continue;
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
    Student s(std::cin, std::cout); // get student information from user and create a student
    
    // add the student to the list
    try {
        if (student_list.add(new Node(s))) { // if the student is not in the list yet so that he/she has been successfully added
            std::cout << "A student is added in table!" << std::endl;
            return true;
        } else { // the student is already in the list
            std::cout << "The student already exists. " << std::endl;
            return false;
        }
    } catch (MaxDepartmentException &e) { // if the department capacity has been full
        std::cout << "The department capacity of the list is full. " << std::endl;
        return false;
    }
}

bool delete_student(List &student_list) {
    Student s(std::cin, std::cout); // get student information from user and create a student

    if (student_list.remove(new Node(s))) { // if the student is in the list so that he/she has been successfully deleted
        std::cout << "Deleted!" << std::endl;
        return true;
    } else { // the student is not in the list
        std::cout << "Can't Delete it" << std::endl;
        return false;
    }
}

void print(List &student_list) {
    std::cout << "Dept\tGender\tName\tAge" << std::endl;
    student_list.print();
}

void pivot_table(List &student_list) {
    int category, function;

    // get the category and function from user within the range of 1 to 3
    std::cout << "-----------Category-----------" << std::endl;
    std::cout << "1. Dept" << std::endl;
    std::cout << "2. Gender" << std::endl;
    std::cout << "3. Dept and Gender" << std::endl;
    std::cout << "------------------------------" << std::endl;
    Format::range_input(std::cin, std::cout, "Selection: ", category, 1, 3);

    std::cout << "-----------Function-----------" << std::endl;
    std::cout << "1. Average" << std::endl;
    std::cout << "2. Max" << std::endl;
    std::cout << "3. Min" << std::endl;
    std::cout << "------------------------------" << std::endl;
    Format::range_input(std::cin, std::cout, "Selection: ", function, 1, 3);

    // depending on the category, call the corresponding function
    // Note that function (int) is casted to Operator (enum) for the convenience purpose
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
    }
}
