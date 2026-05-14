#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

template <typename T>
class Vector {
    private:
        T* data;
        size_t siz;
        size_t cap;
    
    public:
        Vector();
        ~Vector();
        Vector(const Vector& other);
        Vector& operator=(const Vector& other);

        void push_back(const T& value);
        void reserve (size_t newCap);
        void resize(size_t newSiz);

        size_t size() const;
        size_t capacity() const;

        T& operator[](size_t index);
};

template <typename T>
Vector<T>::Vector() : data(nullptr), siz(0), cap(0) {}

template <typename T>
Vector<T>::~Vector() {
    delete[] data;
}

template <typename T>
Vector<T>::Vector(const Vector& other)
{
    siz = other.siz;
    cap = other.cap;

    if (cap == 0) {
        data = nullptr;
        return;
    }

    data = new T[cap];

    for (size_t i = 0; i < siz; i++) {
        data[i] = other.data[i];
    }
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other)
{
    if (this == &other) return *this;

    delete[] data;

    siz = other.siz;
    cap = other.cap;

    if (cap == 0) {
        data = nullptr;
        return *this;
    }

    data = new T[cap];

    for (size_t i = 0; i < siz; i++) {
        data[i] = other.data[i];
    }

    return *this;
}

template <typename T>
void Vector<T>::reserve(size_t newCap)
{
    if (newCap <= cap) return;

    T* newData = new T[newCap];

    for (size_t i = 0; i < siz; i++) {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
    cap = newCap;
}

template <typename T>
void Vector<T>::resize(size_t newSize)
{
    if (newSize < siz) {
        siz = newSize;
        return;
    }

    if (newSize > cap) {
        reserve(newSize);
    }

    for (size_t i = siz; i < newSize; i++) {
        data[i] = T();
    }

    siz = newSize;
}

template <typename T>
size_t Vector<T>::size() const {
    return siz;
}

template <typename T>
size_t Vector<T>::capacity() const {
    return cap;
}

template <typename T>
T& Vector<T>::operator[](size_t index) {
    return data[index];
}

template <typename T>
void Vector<T>::push_back(const T& value) {
    if (siz == cap) {
        size_t newCap = (cap == 0) ? 1 : cap * 2;

        T* newData = new T[newCap];

        for (size_t i = 0; i < siz; i++) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        cap = newCap;
    }

    data[siz++] = value;
}

#endif