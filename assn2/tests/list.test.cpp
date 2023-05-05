#include "list.hpp"
#include "test.h"
#include <sstream>
#include <initializer_list>

bool equal(double a, double b) {
    return std::abs(a - b) < 1e-3;
}

Student create_student(std::string dept, std::string gender, std::string name, int age) {
    std::istringstream iss(dept + "\n" + gender + "\n" + name + "\n" + std::to_string(age) + "\n");
    std::ostringstream oss;
    return Student(iss, oss);
}

List create_list(std::initializer_list<Student> students) {
    List list;
    for (auto &student : students) {
        list.add(new Node(student));
    }
    return list;
}

bool add_test() {
    List list = create_list({
        create_student("CS", "F", "Jane", 21),
        create_student("MATH", "M", "Karl", 24),
        create_student("MECH", "F", "Kathy", 27)
    });

    Student s = create_student("MATH", "F", "Katie", 23);
    list.add(new Node(s));
    return s < list;
}

bool remove_test() {
    Student in_list[] = {
        create_student("CS", "M", "Jack", 22),
        create_student("BIO", "M", "James", 24),
        create_student("BIO", "F", "Jenny", 25), 
        create_student("BIO", "M", "Joe", 26), 
        create_student("MATH", "M", "Kevin", 22),
        create_student("MATH", "M", "Karl", 24),
        create_student("MECH", "M", "Kurt", 26),
        create_student("MECH", "F", "Kathy", 27)
    };

    Student out_list[] = {
        create_student("CS", "M", "John", 20),
        create_student("CS", "F", "Jane", 21),
        create_student("BIO", "F", "Jill", 23),
        create_student("MATH", "M", "Kim", 20), 
        create_student("MATH", "F", "Kathy", 21),
        create_student("MATH", "F", "Katie", 23),
        create_student("MECH", "F", "Kara", 25), 
        create_student("MECH", "M", "Kenny", 28)
    };

    List list;
    for (int i = 0; i < 8; i++) {
        list.add(new Node(in_list[i]));
        list.add(new Node(out_list[i]));
    }

    for (const Student &s : out_list)
        list.remove(new Node(s));
    
    bool check = true;
    for (int i = 0; i < 8; i++) {
        if (!check) break;
        check = check &&
                in_list[i] < list && 
                !(out_list[i] < list);
    }

    return check;
}

bool in_test() {
    Student s1 = create_student("MATH", "M", "Kim", 20), 
            s2 = create_student("MATH", "F", "Katie", 23), 
            s3 = create_student("MECH", "M", "Kurt", 26),
            s4 = create_student("PIAI", "M", "Gwon", 21), 
            s5 = create_student("PIAI", "F", "Kwak", 29);
    List list = create_list({
        create_student("CS", "M", "John", 20),
        create_student("CS", "F", "Jane", 21),
        create_student("CS", "M", "Jack", 22),
        create_student("BIO", "F", "Jill", 23),
        create_student("BIO", "M", "James", 24),
        create_student("BIO", "F", "Jenny", 25), 
        create_student("BIO", "M", "Joe", 26), 
        s1, 
        create_student("MATH", "F", "Kathy", 21),
        create_student("MATH", "M", "Kevin", 22),
        s2,
        create_student("MATH", "M", "Karl", 24),
        create_student("MECH", "F", "Kara", 25),
        s3,
        create_student("MECH", "F", "Kathy", 27),
        create_student("MECH", "M", "Kenny", 28)
    });
    
    return s1 < list && s2 < list && s3 < list && !(s4 < list) && !(s5 < list);
}

bool sort_test() {
    // TODO: to be implemented
    return true;
}

bool pivot_table_test() {
    // TODO: to be implemented
    return true;
}

bool to_string_test() {
    return to_string(static_cast<Operator>(AVG)) == "Average" && to_string(static_cast<Operator>(MAX)) == "Max" && to_string(static_cast<Operator>(MIN)) == "Min";
}

bool max_test() {
    return max(3, 4) == 4 && max(-10, 8) == 8 && max(-23, -50) == -23 && max(0, 0) == 0 && equal(max(3.1, 3.8), 3.8);
}

bool min_test() {
    return min(3, 4) == 3 && min(-10, 8) == -10 && min(-23, -50) == -50 && min(0, 0) == 0 && equal(min(3.1, 3.8), 3.1);
}

int main(int argc, char **argv) {
    if (argc != 2) return 1; // invalid arguments (requires test name)

    std::vector<std::pair<std::string, fp>> tests {
        std::make_pair("List::Add", add_test), 
        std::make_pair("List::Remove", remove_test),
        std::make_pair("List::In", in_test), 
        std::make_pair("List::Sort", sort_test), 
        std::make_pair("List::PivotTable", pivot_table_test),
        std::make_pair("List::to_string", to_string_test), 
        std::make_pair("List::max", max_test), 
        std::make_pair("List::min", min_test), 
    };
    return test(argv[1], tests);
}
