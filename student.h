#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class Person {
    protected:
        std::string name;
        std::string surname;
    public:
        virtual ~Person() = default;

        virtual std::string getName() const = 0;
        virtual std::string getSurname() const = 0;
};

class Student : public Person{
private:
    std::vector<int> homework;
    int exam;
    double mean;
    double median;

public:
    
    Student() : exam(0), mean(0), median(0) { }
    Student(std::istream& is);

    Student(const Student& other);
    Student& operator=(const Student& other);
    Student(Student&& other) noexcept;
    Student& operator=(Student&& other) noexcept;
    ~Student() override;

    std::string getName() const override { return name; }
    std::string getSurname() const override { return surname; }
    int getExam() const { return exam; }
    double getMean() const { return mean; }
    double getMedian() const { return median; }
    const std::vector<int>& getHomework() const { return homework; }

    std::istream& readStudent(std::istream& is);

    friend std::ostream& operator<<(std::ostream& os, const Student& s);
    friend std::istream& operator>>(std::istream& is, Student &s);

};

double calculateMean(const std::vector<int>& hm, int exam);
double calculateMedian(std::vector<int> hm, int exam);

#endif