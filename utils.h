#ifndef UTILS_H
#define UTILS_H

#include "student.h"
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

    if constexpr (std::is_same_v<Container, std::list<Student>>) {
        stud.sort(rusiuoti);
    } else {
        std::sort(stud.begin(), stud.end(), rusiuoti);
    }


    auto start = std::chrono::high_resolution_clock::now();

    Container geriStud, blogiStud;

    for (const auto &s : stud) {
        if (s.getMean() >= 5.0) {
            geriStud.push_back(s);
        }
        else {
            blogiStud.push_back(s);
        }
    }


    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Studentų skirstymo į dvi grupes laikas: " << std::chrono::duration<double>(end - start).count() << " s\n" << std::endl;


    /* std::ofstream fileGeri(geri);
    std::ofstream fileBlogi(blogi);

    fileGeri << std::left << std::setw(25) << "Vardas" << std::left << std::setw(25) << "Pavarde" << std::left << std::setw(25) << "Galutinis (Vid.)" << 
    "Galutinis (Med.)" << '\n';
    for (const auto &s : geriStud) {
        fileGeri << std::left << std::setw(25) << s.getName() << std::left << std::setw(25) << s.getSurname() << std::left << std::setw(25) 
        << std::fixed << std::setprecision(2) << s.getMean() << std::fixed << std::setprecision(2) << s.getMedian() << '\n';
    }

    fileBlogi << std::left << std::setw(25) << "Vardas" << std::left << std::setw(25) << "Pavarde" << std::left << std::setw(25) << "Galutinis (Vid.)" << 
    "Galutinis (Med.)" << '\n';
    for (const auto &s : blogiStud) {
        fileBlogi << std::left << std::setw(25) << s.getName() << std::left << std::setw(25) << s.getSurname() << std::left << std::setw(25) 
        << std::fixed << std::setprecision(2) << s.getMean() << std::fixed << std::setprecision(2) << s.getMedian() << '\n';
    }
    */
}



template<typename Container>
void splitStudent2(Container &stud, const std::string &geri, const std::string &blogi) {


    if constexpr (std::is_same_v<Container, std::list<Student>>) {
        stud.sort(rusiuoti);
    } else {
        std::sort(stud.begin(), stud.end(), rusiuoti);
    }


    auto start = std::chrono::high_resolution_clock::now();

    Container blogiStud;

    
    auto it = stud.begin();
    while (it != stud.end()) {
        if (it->getMean() < 5.0) {
            blogiStud.push_back(*it);
            it = stud.erase(it);
        } else {
            it++;
        }
    }
    

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Studentų skirstymo į dvi grupes laikas: " << std::chrono::duration<double>(end - start).count() << " s\n" << std::endl;

}


template<typename Container>
void splitStudent3(Container &stud, const std::string &geri, const std::string &blogi) {


    if constexpr (std::is_same_v<Container, std::list<Student>>) {
        
        stud.sort(rusiuoti);
        
    } else if (std::is_same_v<Container, std::deque<Student>>) {
        
        std::sort(stud.begin(), stud.end(), rusiuoti);

    }


    auto start = std::chrono::high_resolution_clock::now();

    Container blogiStud;

    if constexpr (!std::is_same_v<Container, std::vector<Student>>) {
        auto it = stud.begin();
        while (it != stud.end()) {
            if (it->getMean() < 5.0) {
                blogiStud.push_back(*it);
                it = stud.erase(it);
            } else {
                it++;
            }
        }
        
    } else {
        auto splitPoint = std::partition(stud.begin(), stud.end(), [](const Student &s) { return s.getMean() >= 5.0; });

        blogiStud = Container(splitPoint, stud.end()); 
        stud.erase(splitPoint, stud.end());

    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Studentų skirstymo į dvi grupes laikas: " << std::chrono::duration<double>(end - start).count() << " s\n" << std::endl;

    /*if constexpr (std::is_same_v<Container, std::vector<Student>>) {
        std::sort(stud.begin(), stud.end(), rusiuoti);
        std::sort(blogiStud.begin(), blogiStud.end(), rusiuoti);
    }*/
}


extern int rusiavimas;

#endif