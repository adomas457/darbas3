#define CATCH_CONFIG_MAIN
#include "catch2/catch_amalgamated.hpp"

#include "vector.h"

TEST_CASE("Constructor, empty") {
    Vector<int> v;
    REQUIRE(v.size() == 0);
    REQUIRE(v.empty() == true);
}

TEST_CASE("Range constructor") {
    int arr[] = {1, 2, 3, 4};

    Vector<int> v(arr, arr + 4);

    REQUIRE(v.size() == 4);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);
    REQUIRE(v[3] == 4);
}

TEST_CASE("Copy constructor") {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);

    Vector<int> copy(v);

    REQUIRE(copy.size() == 2);
    REQUIRE(copy[0] == 1);
    REQUIRE(copy[1] == 2);
}

TEST_CASE("Copy assignment") {
    Vector<int> v;
    v.push_back(1);

    Vector<int> a;
    a = v;

    REQUIRE(a.size() == 1);
    REQUIRE(a[0] == 1);
}

TEST_CASE("Move constructor") {
    Vector<int> v;
    v.push_back(10);

    Vector<int> moved(std::move(v));

    REQUIRE(moved.size() == 1);
    REQUIRE(moved[0] == 10);
    REQUIRE(v.size() == 0);
}

TEST_CASE("Move assignment") {
    Vector<int> v;
    v.push_back(5);

    Vector<int> a;
    a = std::move(v);

    REQUIRE(a.size() == 1);
    REQUIRE(a[0] == 5);
    REQUIRE(v.size() == 0);
}

TEST_CASE("insert") {
    Vector<int> v;
    v.push_back(1);
    v.push_back(3);

    v.insert(v.begin() + 1, 2);

    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);
}

TEST_CASE("erase single") {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    v.erase(v.begin() + 1);

    REQUIRE(v.size() == 2);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 3);
}

TEST_CASE("erase range") {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    v.erase(v.begin() + 1, v.begin() + 3);

    REQUIRE(v.size() == 2);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 4);
}

TEST_CASE("clear") {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);

    v.clear();

    REQUIRE(v.size() == 0);
    REQUIRE(v.empty() == true);
}

TEST_CASE("shrink_to_fit") {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);

    v.reserve(100);
    v.shrink_to_fit();

    REQUIRE(v.capacity() == v.size());
}

TEST_CASE("push_back, operator[]") {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);

    REQUIRE(v.size() == 2);
    REQUIRE(v[0] == 10);
    REQUIRE(v[1] == 20);
}

TEST_CASE("at, out of bounds") {
    Vector<int> v;

    REQUIRE_THROWS_AS(v.at(0), std::out_of_range);
}

TEST_CASE("front, back") {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);

    REQUIRE(v.front() == 1);
    REQUIRE(v.back() == 2);
}

TEST_CASE("resize") {
    Vector<int> v;
    v.resize(5);

    REQUIRE(v.size() == 5);
}

TEST_CASE("reserve") {
    Vector<int> v;
    v.reserve(100);

    REQUIRE(v.capacity() >= 100);
}

TEST_CASE("swap") {
    Vector<int> a, b;

    a.push_back(1);
    b.push_back(2);

    a.swap(b);

    REQUIRE(a[0] == 2);
    REQUIRE(b[0] == 1);
}

TEST_CASE("pop_back") {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    v.pop_back();

    REQUIRE(v.size() == 2);
    REQUIRE(v.back() == 2);
}