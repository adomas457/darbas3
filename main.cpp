#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>
#include <chrono>
#include "utils.h"
#include <deque>
#include <list>
#include <sstream>
#include "vector.h"

int main() {

    std::vector<int> v1;
    Vector<int> v2;
    
    for (int i = 0; i < 5; i++) {
        v1.push_back(i);
        v2.push_back(i);
    }

    // FUNCTION 1 PUSH_BACK
    /*
    std::cout << "push_back: " << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << v1[i] << " " << v2[i] << std::endl;
    }*/

    // FUNCTION 2 INSERT
    /*
    v1.insert(v1.begin() + 2, 99);
    v2.insert(2, 99);

    std::cout << "insert: " << std::endl;
    for (size_t i = 0; i < v1.size(); i++) {
        std::cout << v1[i] << " " << v2[i] << std::endl;
    }*/
    
    // FUNCTION 3 ERASE
    /*
    v1.erase(v1.begin() + 1);
    v2.erase(1);

    std::cout << "erase: " << std::endl;
    for (size_t i = 0; i < v1.size(); i++) {
        std::cout << v1[i] << " " << v2[i] << std::endl;
    }*/
    
    // FUNCTION 4 SWAP
    /*
    std::vector<int> a;
    Vector<int> b;

    for (int i = 6; i < 9; i++) {
        a.push_back(i);
        b.push_back(i);
    }

    v1.swap(a);
    v2.swap(b);

    std::cout << "swap: " << std::endl;
    std::cout << "std::vector:  ";
    for (auto i : v1) std::cout << i << " ";
    std::cout << std::endl;
    std::cout << "my vector: ";
    for (auto i : v2) std::cout << i << " ";
    */

    // FUNCTION 5 OPERATOR[]
    /*
    v1[1] = 100;
    v2[1] = 100;

    std::cout << "operator[]: ";
    std::cout << v1[1] << " " << v2[1] << std::endl; */







    
    /*using Container = std::vector<Student>;
    //using Container = std::deque<Student>;
    //using Container = std::list<Student>;

    Container students;
    std::srand(std::time(nullptr));

    while (true) {
        std::cout << "1 - Generuoti failus (1 atvejis)" << std::endl;
        std::cout << "2 - Generuoti failus (2 atvejis)" << std::endl;
        std::cout << "3 - Exit" << std::endl;

        int choice = getInt("Veiksmas: ", 1, 3);

        if (choice == 1) {
            int test = getInt("Įveskite įrašų skaičių: ", 1);

            generateFile("studentai" + std::to_string(test) + ".txt", test, 10);

            
        } else if (choice == 2) {
            int test = getInt("Įveskite įrašų skaičių: ", 1);
            rusiavimas = getInt("Surūšiuoti pagal: vardą (1); pavardę (2); pagal vidurkį (3); pagal medianą (4): ", 1, 4);
            int pasirinkimas = getInt("Strategijos nr.: ", 1, 3);
            try {

                students = readFile<Container>("studentai" + std::to_string(test) + ".txt");

                if (pasirinkimas == 1) {
                    splitStudent<Container>(students, "geri" + std::to_string(test) + ".txt", "blogi"+ std::to_string(test) + ".txt");
                } else if (pasirinkimas == 2) {
                    splitStudent2<Container>(students, "geri" + std::to_string(test) + ".txt", "blogi"+ std::to_string(test) + ".txt");
                } else {
                    splitStudent3<Container>(students, "geri" + std::to_string(test) + ".txt", "blogi"+ std::to_string(test) + ".txt");
                }
                
                
                students.clear();
            } 
            catch (std::exception& e) {
                std::cout << e.what() << std::endl;
                continue;
            }
        }
        else {
            break;
        }

        std::cout << std::string(100, '-') << std::endl;
    }*/

    return 0;
}