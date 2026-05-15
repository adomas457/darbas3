#ifndef UTILS_H
#define UTILS_H

#include "student.h"
#include "vector.h"
#include <string>
#include <vector>
#include <limits>
#include <iostream>
#include <chrono>
#include <list>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <deque>

void test(int sz);
size_t count_std_vector(size_t N);
size_t count_vector(size_t N);

int getInt(const std::string &prompt, int min = std::numeric_limits<int>::min(), int max = std::numeric_limits<int>::max());
int utf8_length(std::string s);

template<typename Container>
Container readFile(const std::string &filename) {
    Container students;
    std::ifstream file(filename);

    if (!file) {
        throw std::runtime_error("Failas nerastas.");
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Student s;
        s.readStudent(ss);
        students.push_back(s);
    }

    return students;
}


void generateFile(const std::string &filename, int n, int nd);

bool rusiuoti(const Student& s1, const Student& s2);

template<typename Container>
void splitStudent(Container &stud, const std::string &geri, const std::string &blogi) {

    Container blogiStud;

    auto splitPoint = std::partition(stud.begin(), stud.end(), [](const Student &s) { return s.getMean() >= 5.0; });

    blogiStud = Container(splitPoint, stud.end()); 
    stud.erase(splitPoint, stud.end());

    std::sort(stud.begin(), stud.end(), rusiuoti);
    std::sort(blogiStud.begin(), blogiStud.end(), rusiuoti);
}


extern int rusiavimas;

#endif