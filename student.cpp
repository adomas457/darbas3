#include "student.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>

Student::Student(const Student& other) : homework(other.homework), exam(other.exam),
    mean(other.mean), median(other.median) { 
        name = other.name;
        surname = other.surname;
    }

Student& Student::operator=(const Student& other) {
    if (this == &other) return *this;

    name = other.name;
    surname = other.surname;
    homework = other.homework;
    exam = other.exam;
    mean = other.mean;
    median = other.median;

    return *this;
}

Student::Student(Student&& other) noexcept : homework(std::move(other.homework)),
      exam(other.exam), mean(other.mean), median(other.median) {
        name = std::move(other.name);
        surname = std::move(other.surname);
       }

Student& Student::operator=(Student&& other) noexcept {
    if (this == &other) return *this;

    name = std::move(other.name);
    surname = std::move(other.surname);
    homework = std::move(other.homework);
    exam = other.exam;
    mean = other.mean;
    median = other.median;

    return *this;

}

Student::~Student() { 
    std::cout << "Objektas ištrintas" << std::endl;
}

double calculateMean(const std::vector<int> &hm, int exam) {
    if (hm.empty()) return exam * 0.6;
    double s = 0;
    for (int g : hm) {
        s += g;
    }
    s /= hm.size();
    return s * 0.4 + 0.6 * exam;
}

double calculateMedian(std::vector<int> hm, int exam) {
    if (hm.empty()) return exam * 0.6;

    std::sort(hm.begin(), hm.end());
    int pos = hm.size() / 2;
    if (hm.size() % 2 == 0) {
        return (hm[pos - 1] + hm[pos]) / 2.0 * 0.4 + exam * 0.6;
    } else {
        return hm[pos] * 0.4 + exam * 0.6;
    }
}

Student::Student(std::istream& is) {
    readStudent(is);
}


std::istream& Student::readStudent(std::istream& is) {
   
    std::string line;
    std::getline(is >> std::ws, line);

    std::stringstream ss(line);

    ss >> name >> surname;

    int grade;
    homework.clear();

    while (ss >> grade) {
        homework.push_back(grade);
    }

    if (!homework.empty()) {
        exam = homework.back();
        homework.pop_back();
    } else {
        exam = 0;
    }

    mean = calculateMean(homework, exam);
    median = calculateMedian(homework, exam);

    return is;
}

std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << std::left << std::setw(10) << s.name << std::left << std::setw(10) << s.surname;

    for (int g : s.homework) {
        os << std::left << std::setw(5) << g;
    }

    os << std::left << std::setw(5) << s.exam << std::left << std::setw(7) << s.mean << std::left << std::setw(7) << s.median << '\n';

    return os;
}

std::istream& operator>>(std::istream& is, Student& s) {
    return s.readStudent(is);
}
