#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <chrono>
#include <list>

int rusiavimas = 2;

void test(int sz) {
    std::cout << "Size: " << sz << std::endl;

    auto start1 = std::chrono::high_resolution_clock::now();

    std::vector<int> v1;
    for (int i = 1; i <= sz; i++) {
        v1.push_back(i);
    }

    auto end1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration<double>(end1 - start1).count();

    auto start2 = std::chrono::high_resolution_clock::now();

    Vector<int> v2;
    for (int i = 1; i <= sz; i++) {
        v2.push_back(i);
    }

    auto end2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration<double>(end2 - start2).count();

    std::cout << "std::vector: " << duration1 * 1000 << " ms" << std::endl;
    std::cout << "Vector     : " << duration2 * 1000 << " ms" << std::endl;
    std::cout << "--------------------------" << std::endl;
}

size_t count_std_vector(size_t N) {
    std::vector<int> v;

    size_t count = 0;
    size_t cap = v.capacity();

    for (size_t i = 0; i < N; i++) {
        v.push_back(i);

        if (v.capacity() != cap) {
            count++;
            cap = v.capacity();
        }
    }

    return count;
}

size_t count_vector(size_t N) {
    Vector<int> v;

    size_t count = 0;
    size_t cap = v.capacity();

    for (size_t i = 0; i < N; i++) {
        v.push_back(i);

        if (v.capacity() != cap) {
            count++;
            cap = v.capacity();
        }
    }

    return count;
}

int getInt(const std::string &prompt, int min, int max) {
    int num;

    while (true) {
        try {
            std::cout << prompt;

            if (!(std::cin >> num) || (num < min || num > max)) throw std::runtime_error("Iveskite sveikaji skaiciu tarp " + std::to_string(min) + " ir " + std::to_string(max) + ".");
            
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return num;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Iveskite sveikaji skaiciu tarp " << min << " ir " << max << "." << std::endl;
        } catch (std::exception &e) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << e.what() << std::endl;
        }
        
    }

    return num;
}

int utf8_length(std::string s) {
    int length = 0;
    for (unsigned char c : s) {
        if ((c & 0xC0) != 0x80) length++;
    }
    return length;
}


void generateFile(const std::string &filename, int n, int nd) {
    std::ofstream file(filename);

    file << std::left << std::setw(25) << "Vardas" << std::left << std::setw(25) << "Pavarde";
    for (int i = 1; i <= nd; i++) {
        file << std::left << std::setw(10) << ("ND" + std::to_string(i));
    }
    file << "Egz.\n";

    for (int i = 1; i <= n; i++) {
        file << std::left << std::setw(25) << ("Vardas" + std::to_string(i)) << std::left << std::setw(25) << ("Pavarde" + std::to_string(i));

        for (int j = 0; j < nd; j++)file << std::left << std::setw(10) << (rand() % 11);

        file << std::left << std::setw(10) << (rand() % 11) << '\n';
    }
}


bool rusiuoti(const Student& s1, const Student& s2) {
    switch (rusiavimas) {
        case 1: return s1.getName() < s2.getName();
        case 2: return s1.getSurname() < s2.getSurname();
        case 3: return s1.getMean() < s2.getMean();
        case 4: return s1.getMedian() < s2.getMedian();
    }
    return false;
}

