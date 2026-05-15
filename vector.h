#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <stdexcept>

/**
 * @brief Vector klasė
 * @tparam T elementų tipas
 */

template <typename T>
class Vector {
    private:
        T* data_;
        size_t siz;
        size_t cap;
    
    public:

        /// @brief Konstruktorius (sukuria tuščią Vector)
        Vector();

        /// @brief Konstruktorius iš intervalo
        Vector(T* first, T* last);

        /// @brief Destruktorius
        ~Vector();

        /// @brief Copy konstruktorius
        Vector(const Vector& other);

        /// @brief Copy assingment
        Vector& operator=(const Vector& other);

        /// @brief Move konstruktorius
        Vector(Vector&& other) noexcept;

        /// @brief Move assignment
        Vector& operator=(Vector&& other) noexcept;

        /// @brief Prideda elementą į galą
        void push_back(const T& value);

        /// @brief Keičia capacity
        void reserve(size_t newCap);

        /// @brief Keičia size
        void resize(size_t newSiz);

        /// @brief Sumažina capacity iki size
        void shrink_to_fit();

        /// @brief Maksimalus galimas size
        size_t max_size() const;

        /// @brief Įterpia elementą
        T* insert(T* pos, const T& value);

        /// @brief Ištrina elementą
        T* erase(T* pos);

        /// @brief Ištrina elementų intervalą
        T* erase(T* first, T* last);

        /// @brief Pašalina paskutinį elementą
        void pop_back();

        /// @brief Ištrina visus elementus (pravalo Vector)
        void clear();

        /// @brief Sukeičia du Vector
        void swap(Vector& other) noexcept;

        /// @brief Grąžina pirmą elementą
        T& front();
        const T& front() const;

        /// @brief Grąžina paskutinį elementą
        T& back();
        const T& back() const;

        /// @brief Saugi prieiga (bounds tikrinimas)
        T& at(size_t i);
        const T& at(size_t i) const;

        /// @brief Grąžina pradinį iteratorių
        T* begin();
        const T* begin() const;

        /// @brief Grąžina paskutinį iteratorių
        T* end();
        const T* end() const;

        /// @brief Rodyklė į Vectoriaus masyvą (duomenis)
        T* data();
        const T* data() const;

        /// @brief Operatorius []
        T& operator[](size_t index);
        const T& operator[](size_t index) const;

        /// @brief Grąžina elementų skaičių
        size_t size() const;

        /// @brief Grąžina capacity
        size_t capacity() const;

        /// @brief Tikrina ar Vector tuščias
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
Vector<T>::Vector(T* first, T* last) {
    siz = last - first;
    cap = siz;
    data_ = new T[cap];

    for (size_t i = 0; i < siz; i++) {
        data_[i] = *(first + i);
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
T* Vector<T>::insert(T* pos, const T& value) {
    size_t index = pos - data_;

    if (siz == cap) reserve((cap == 0) ? 1 : cap * 2);

    pos = data_ + index;

    for (T* it = data_ + siz; it > pos; it--) {
        *it = *(it - 1);
    }
    *pos = value;

    siz++;

    return pos;
}

template <typename T>
T* Vector<T>::erase(T* pos) {

    for (T* it = pos; it < data_ + siz - 1; it++) {
        *it = *(it + 1);
    }

    siz--;

    return pos;
}

template <typename T>
T* Vector<T>::erase(T* first, T* last)
{
    T* newEnd = first;

    for (T* it = last; it < data_ + siz; it++) {
        *newEnd = *it;
        newEnd++;
    }

    siz -= (last - first);
    return first;
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

#endif