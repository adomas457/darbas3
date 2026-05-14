#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <stdexcept>

template <typename T>
class Vector {
    private:
        T* data_;
        size_t siz;
        size_t cap;
    
    public:

        Vector();
        ~Vector();
        Vector(const Vector& other);
        Vector& operator=(const Vector& other);
        Vector(Vector&& other) noexcept;
        Vector& operator=(Vector&& other) noexcept;

        void push_back(const T& value);
        void reserve (size_t newCap);
        void resize(size_t newSiz);
        void shrink_to_fit();
        size_t max_size() const;

        T& operator[](size_t index);
        const T& operator[](size_t index) const;

        size_t size() const;
        size_t capacity() const;
        bool empty() const;
};

template <typename T>
Vector<T>::Vector() : data_(nullptr), siz(0), cap(0) {}

template <typename T>
Vector<T>::~Vector() {
    delete[] data_;
}

template <typename T>
Vector<T>::Vector(const Vector& other)
{
    siz = other.siz;
    cap = other.cap;

    if (cap == 0) {
        data_ = nullptr;
        return;
    }

    data_ = new T[cap];

    for (size_t i = 0; i < siz; i++) {
        data_[i] = other.data_[i];
    }
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other)
{
    if (this == &other) return *this;

    delete[] data_;

    siz = other.siz;
    cap = other.cap;

    if (cap == 0) {
        data_ = nullptr;
        return *this;
    }

    data_ = new T[cap];

    for (size_t i = 0; i < siz; i++) {
        data_[i] = other.data_[i];
    }

    return *this;
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept
{
    data_ = other.data_;
    siz = other.siz;
    cap = other.cap;

    other.data_ = nullptr;
    other.siz = 0;
    other.cap = 0;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept
{
    if (this == &other) return *this;

    delete[] data_;

    data_ = other.data_;
    siz = other.siz;
    cap = other.cap;

    other.data_ = nullptr;
    other.siz = 0;
    other.cap = 0;

    return *this;
}

template <typename T>
void Vector<T>::reserve(size_t newCap)
{
    if (newCap <= cap) return;

    T* newData = new T[newCap];

    for (size_t i = 0; i < siz; i++) {
        newData[i] = data_[i];
    }

    delete[] data_;
    data_ = newData;
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
        data_[i] = T();
    }

    siz = newSize;
}

template <typename T>
void Vector<T>::shrink_to_fit() {
    if (cap == siz) return;

    if (siz == 0) {
        delete [] data_;
        data_ = nullptr;
        cap = 0;
        return;
    }

    T* newData = new T[siz];
    for (size_t i = 0; i < siz; i++) {
        newData[i] = data_[i];
    }
    delete [] data_;
    data_ = newData;
    cap = siz;
}

template<typename T>
size_t Vector<T>::max_size() const {
    return static_cast<size_t>(-1) / sizeof(T);
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
bool Vector<T>::empty() const {
    return siz == 0;
}

template <typename T>
T& Vector<T>::operator[](size_t index) {
    return data_[index];
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const
{
    return data_[index];
}

template <typename T>
void Vector<T>::push_back(const T& value) {
    if (siz == cap) {
        reserve((cap == 0) ? 1 : cap * 2);
    }

    data_[siz++] = value;
}

#endif