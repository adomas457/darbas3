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

    //std::vector<int> v1;
    //Vector<int> v2;

    /*
    // UZDUOTIS 2
    test(10000);
    test(100000);
    test(1000000);
    test(10000000);
    test(100000000); 
    */

    // UZDUOTIS 3
    /*
    size_t N = 100000000;
    std::cout << "Elementu skaicius: " << N << std::endl;
    size_t count1 = count_std_vector(N);
    size_t count2 = count_vector(N);
    std::cout << "std::vector perskirstymai: " << count1 << std::endl;
    std::cout << "Vector perskirstymai: " << count2 << std::endl;
    std::cout << "Skirtumas: " << static_cast<int>(count1) - static_cast<int>(count2) << std::endl; */


    /*
    for (int i = 0; i < 5; i++) {
        v1.push_back(i);
        v2.push_back(i);
    }*/

    // FUNCTION 1 PUSH_BACK
    /*
    std::cout << "push_back: " << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << v1[i] << " " << v2[i] << std::endl;
    }*/

    // FUNCTION 2 INSERT
    /*
    v1.insert(v1.begin() + 2, 99);
    v2.insert(v2.begin() + 2, 99);

    std::cout << "insert: " << std::endl;
    for (size_t i = 0; i < v1.size(); i++) {
        std::cout << v1[i] << " " << v2[i] << std::endl;
    }*/
    
    // FUNCTION 3 ERASE(T* pos)
    /*
    v1.erase(v1.begin() + 1);
    v2.erase(v2.begin() + 1);

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

     
    //using Container = std::vector<Student>;
    using Container = Vector<Student>;

    Container students;
    std::srand(std::time(nullptr));

    while (true) {
        std::cout << "1 - Generuoti failus (1 atvejis)" << std::endl;
        std::cout << "2 - Generuoti failus (2 atvejis)" << std::endl;
        std::cout << "3 - Exit" << std::endl;

        int choice = getInt("Veiksmas: ", 1, 3);

        if (choice == 1) {
            int test = getInt("Iveskite irasu skaiciu: ", 1);

            generateFile("studentai" + std::to_string(test) + ".txt", test, 10);

            
        } else if (choice == 2) {
            int test = getInt("Iveskite irasu skaiciu: ", 1);
            rusiavimas = getInt("Surusiuoti pagal: varda (1); pavarde (2); pagal vidurki (3); pagal mediana (4): ", 1, 4);
            try {

                auto start = std::chrono::high_resolution_clock::now();

                students = readFile<Container>("studentai" + std::to_string(test) + ".txt");
                splitStudent<Container>(students, "geri" + std::to_string(test) + ".txt", "blogi"+ std::to_string(test) + ".txt");

                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Veikimo laikas: " << std::chrono::duration<double>(end - start).count() << " s" << std::endl;

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
    }
    
    return 0;
}