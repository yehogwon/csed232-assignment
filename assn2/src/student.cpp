void Student::input_info() {
    std::cout << "Dept: "; std::cin >> dept;
    std::cout << "Gender: "; std::cin >> gender;
    std::cout << "Name: "; std::cin >> name;
    std::cout << "Age: "; std::cin >> age;
}

bool Student::operator==(const Student &s) {
    return dept == s.dept && gender == s.gender && name == s.name && age == s.age;
}
