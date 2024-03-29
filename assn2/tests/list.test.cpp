#include "list.hpp"
#include "test.h"
#include <sstream>
#include <initializer_list>
#include <tuple>

bool equal(double a, double b) {
    return std::abs(a - b) < 1e-3;
}

std::vector<std::string> split(const std::string &s, const char delimiter) {
    std::vector<std::string> v;
    std::istringstream iss(s);
    std::string buf_;
    while (getline(iss, buf_, delimiter))
        v.push_back(buf_);
    return v;
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
    Student in_list[] = {
        create_student("CS", "M", "John", 20),
        create_student("CS", "F", "Jane", 21),
        create_student("CS", "M", "Jack", 22),
        create_student("BIO", "F", "Jill", 23),
        create_student("BIO", "M", "James", 24),
        create_student("MATH", "M", "Kim", 20), 
        create_student("MATH", "F", "Katie", 23), 
        create_student("MATH", "M", "Karl", 24),
        create_student("MECH", "M", "Kurt", 26),
        create_student("MECH", "F", "Kathy", 27),
        create_student("MECH", "M", "Kenny", 28)
    };

    Student out_list[] = {
        create_student("BIO", "F", "Jenny", 25), 
        create_student("BIO", "M", "Joe", 26), 
        create_student("MATH", "M", "Kevin", 22),
        create_student("MATH", "F", "Kathy", 21),
        create_student("MECH", "F", "Kara", 25),
        create_student("PIAI", "M", "Gwon", 21), 
        create_student("PIAI", "M", "Kwak", 29)
    };

    List list;
    for (const Student &s : in_list)
        list.add(new Node(s));
    
    bool check = true;
    for (const Student &s : in_list) {
        if (!check) break;
        check = check &&
                s < list;
    }
    if (!check) return check;

    for (const Student &s : out_list) {
        if (!check) break;
        check = check &&
                !(s < list);
    }

    return check;
}

bool sort_test() {
    List list = create_list({
        create_student("MATH", "F", "Katie", 23),
        create_student("MATH", "M", "Karl", 24),
        create_student("BIO", "M", "Joe", 26), 
        create_student("CS", "M", "Jack", 22),
        create_student("MECH", "F", "Kara", 25), 
        create_student("BIO", "M", "James", 24),
        create_student("BIO", "F", "Jenny", 25), 
        create_student("MECH", "F", "Kathy", 27),
        create_student("BIO", "F", "Jill", 23),
        create_student("MATH", "M", "Kevin", 22),
        create_student("MATH", "F", "Kathy", 21),
        create_student("MECH", "M", "Kenny", 28), 
        create_student("MECH", "M", "Kurt", 26),
        create_student("CS", "M", "John", 20),
        create_student("CS", "F", "Jane", 21),
        create_student("MATH", "M", "Kim", 20)
    });
    
    bool check = true;
    list.sort();

    std::stringstream buffer;
    std::streambuf *sbuf = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());
    list.print();
    std::cout.rdbuf(sbuf);
    
    std::vector<Student> students;
    std::vector<std::string> lines = split(buffer.str(), '\n');
    for (const std::string &line : lines) {
        std::vector<std::string> tokens = split(line, '\t');
        students.push_back(create_student(tokens[0], tokens[1], tokens[2], stoi(tokens[3])));
    }

    for (int i = 0; i < students.size() - 1; i++) {
        if (!check) break;
        check = check &&
                (students[i] < students[i + 1] || students[i] == students[i + 1]);
    }

    return check;
}

bool pivot_table_test() {
    List list = create_list({
        create_student("MATH", "F", "Katie", 23),
        create_student("MATH", "M", "Karl", 24),
        create_student("BIO", "M", "Joe", 26), 
        create_student("CS", "M", "Jack", 22),
        create_student("MECH", "F", "Kara", 25), 
        create_student("BIO", "M", "James", 24),
        create_student("BIO", "F", "Jenny", 25), 
        create_student("MECH", "F", "Kathy", 27),
        create_student("BIO", "F", "Jill", 23),
        create_student("MATH", "M", "Kevin", 22),
        create_student("MATH", "F", "Kathy", 21),
        create_student("MECH", "M", "Kenny", 28), 
        create_student("MECH", "M", "Kurt", 26),
        create_student("CS", "M", "John", 20),
        create_student("CS", "F", "Jane", 21),
        create_student("MATH", "M", "Kim", 20)
    });

    std::vector<std::tuple<Operator, std::vector<double>>> dept_test_cases {
        std::make_tuple(AVG, std::vector<double>{24.5, 21, 22, 26.5}),
        std::make_tuple(MAX, std::vector<double>{26, 22, 24, 28}),
        std::make_tuple(MIN, std::vector<double>{23, 20, 20, 25})
    };

    std::vector<std::tuple<Operator, std::vector<double>>> gender_test_cases {
        std::make_tuple(AVG, std::vector<double>{23.6, 23.6}), 
        std::make_tuple(MAX, std::vector<double>{27, 28}),
        std::make_tuple(MIN, std::vector<double>{21, 20})
    };

    std::vector<std::tuple<Operator, std::vector<double>>> dept_gender_test_cases {
        std::make_tuple(AVG, std::vector<double>{24, 25, 21, 21, 22, 22, 26, 27}),
        std::make_tuple(MAX, std::vector<double>{25, 26, 21, 22, 23, 24, 27, 28}),
        std::make_tuple(MIN, std::vector<double>{23, 24, 21, 20, 21, 20, 25, 26})
    };

    std::tuple<void (*)(List&, Operator), int, std::vector<std::tuple<Operator, std::vector<double>>>> test_cases[] {
        std::make_tuple([](List &list, Operator op) { list.pivot_dept(op); }, 1, dept_test_cases), 
        std::make_tuple([](List &list, Operator op) { list.pivot_gender(op); }, 1, gender_test_cases), 
        std::make_tuple([](List &list, Operator op) { list.pivot_dept_gender(op); }, 2, dept_gender_test_cases)
    };
    
    bool check = true;

    for (const auto &test_case : test_cases) {
        auto pivot_func = std::get<0>(test_case);
        for (const auto &pivot_test_case : std::get<2>(test_case)) {
            std::stringstream buffer;
            std::streambuf *sbuf = std::cout.rdbuf();
            std::cout.rdbuf(buffer.rdbuf());
            pivot_func(list, std::get<0>(pivot_test_case));
            std::cout.rdbuf(sbuf);
            std::vector<std::string> lines = split(buffer.str(), '\n');
            lines = {lines.begin() + 1, lines.end()};

            const std::vector<double> &expected = std::get<1>(pivot_test_case);
            for (int i = 0; i < lines.size(); i++) {
                if (!check) break;
                std::vector<std::string> tokens = split(lines[i], '\t');
                const std::string &token = tokens[std::get<1>(test_case)];
                check = check && 
                        equal(stod(token), expected[i]);
            }
        }
    }

    return check;
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
        unittest("List::Add", add_test), 
        unittest("List::Remove", remove_test),
        unittest("List::In", in_test), 
        unittest("List::Sort", sort_test), 
        unittest("List::PivotTable", pivot_table_test),
        unittest("List::to_string", to_string_test), 
        unittest("List::max", max_test), 
        unittest("List::min", min_test), 
    };
    return test(argv[1], tests);
}
