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


#endif