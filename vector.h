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

        void insert(size_t index, const T& value);
        void erase(size_t index);
        void pop_back();
        void clear();
        void swap(Vector& other) noexcept;

        T& front();
        const T& front() const;

        T& back();
        const T& back() const;

        T& at(size_t i);
        const T& at(size_t i) const;

        T* begin();
        const T* begin() const;

        T* end();
        const T* end() const;

        T* data();
        const T* data() const;

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
void Vector<T>::insert(size_t index, const T& value) {
    if (index > siz) return;
    if (siz == cap) reserve((cap == 0) ? 1 : cap * 2);

    for (size_t i = siz; i > index; i--) {
        data_[i] = data_[i-1];
    }
    data_[index] = value;

    siz++;
}

template <typename T>
void Vector<T>::erase(size_t index) {
    if (index >= siz) return;

    for (size_t i = index; i < siz - 1; i++) {
        data_[i] = data_[i+1];
    }

    siz--;
}

template <typename T>
void Vector<T>::pop_back() {
    if (siz > 0) {
        siz--;
    }
}

template <typename T>
void Vector<T>::clear() {
    siz = 0;
}

template <typename T>
void Vector<T>::swap(Vector &other) noexcept {
    T* temp = data_;
    data_ = other.data_;
    other.data_ = temp;

    size_t tempSiz = siz;
    siz = other.siz;
    other.siz = tempSiz;

    size_t tempCap = cap;
    cap = other.cap;
    other.cap = tempCap;
}

template <typename T>
T& Vector<T>::front() {
    if (siz == 0) throw std::out_of_range("front() invalid index");
    return data_[0];
}

template <typename T>
const T& Vector<T>::front() const {
    if (siz == 0) throw std::out_of_range("front() invalid index");
    return data_[0];
}

template <typename T>
T& Vector<T>::back() {
    if (siz == 0) throw std::out_of_range("back() invalid index");
    return data_[siz - 1];
}

template <typename T>
const T& Vector<T>::back() const {
    if (siz == 0) throw std::out_of_range("back() invalid index");
    return data_[siz - 1];
}

template <typename T>
T& Vector<T>::at(size_t i) {
    if (i >= siz) throw std::out_of_range("Vector::at invalid index");
    return data_[i];
}

template <typename T>
const T& Vector<T>::at(size_t i) const
{
    if (i >= siz) throw std::out_of_range("Vector::at invalid index");
    return data_[i];
}

template <typename T>
T* Vector<T>::begin() {
    return data_;
}

template <typename T>
const T* Vector<T>::begin() const
{
    return data_;
}

template <typename T>
T* Vector<T>::end() {
    return data_ + siz;
}

template <typename T>
const T* Vector<T>::end() const
{
    return data_ + siz;
}


template <typename T>
T* Vector<T>::data() {
    return this->data_;
}

template <typename T>
const T* Vector<T>::data() const
{
    return this->data_;
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

template <typename T>
bool operator==(const Vector<T>& a, const Vector<T>& b) {
    if (a.size() != b.size()) return false;

    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

#endif