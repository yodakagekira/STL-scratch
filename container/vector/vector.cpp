#include "vector.h"
#include <string>
#include <utility>
#include <stdexcept>

// default constructor
template <typename T>
vector<T>::vector() = default;

// destructor
template <typename T>
vector<T>::~vector() {
    delete[] m_arr;
}

// copy constructor
template <typename T>
vector<T>::vector(const vector& other)
    : m_capacity(other.m_capacity), m_size(other.m_size), m_arr(new T[other.m_capacity])
{
    for (size_t i = 0; i < m_size; i++) {
        m_arr[i] = other.m_arr[i];
    }
}

// move constructor
template <typename T>
vector<T>::vector(vector&& other) noexcept
    : m_capacity(other.m_capacity), m_size(other.m_size), m_arr(other.m_arr)
{
    other.m_capacity = 0;
    other.m_size = 0;
    other.m_arr = nullptr;
}

// copy assignment
template <typename T>
vector<T>& vector<T>::operator=(const vector& other) {
    if (this == &other) return *this;

    T* new_arr = new T[other.m_capacity];
    for (size_t i = 0; i < other.m_size; i++) {
        new_arr[i] = other.m_arr[i];
    }

    delete[] m_arr;
    m_arr = new_arr;
    m_capacity = other.m_capacity;
    m_size = other.m_size;

    return *this;
}

// move assignment
template <typename T>
vector<T>& vector<T>::operator=(vector&& other) noexcept {
    if (this == &other) return *this;

    delete[] m_arr;

    m_capacity = other.m_capacity;
    m_size = other.m_size;
    m_arr = other.m_arr;

    other.m_capacity = 0;
    other.m_size = 0;
    other.m_arr = nullptr;

    return *this;
}

// push_back
template <typename T>
void vector<T>::push_back(T element) {
    if (m_size == m_capacity) {
        m_capacity = (m_capacity == 0) ? 1 : m_capacity * 3;
        T* new_arr = new T[m_capacity];
        for (size_t i = 0; i < m_size; i++) {
            new_arr[i] = std::move(m_arr[i]);
        }
        delete[] m_arr;
        m_arr = new_arr;
    }
    m_arr[m_size++] = std::move(element);
}

// at (non-const)
template <typename T>
T& vector<T>::at(std::size_t index) {
    if (index >= m_size) {
        throw std::out_of_range("index out of range");
    }
    return m_arr[index];
}

// at (const)
template <typename T>
const T& vector<T>::at(std::size_t index) const {
    if (index >= m_size) {
        throw std::out_of_range("index out of range");
    }
    return m_arr[index];
}

// get_size
template <typename T>
std::size_t vector<T>::get_size() const {
    return m_size;
}

// get_capacity
template <typename T>
std::size_t vector<T>::get_capacity() const {
    return m_capacity;
}

// shrink_to_fit
template <typename T>
void vector<T>::shrink_to_fit() {
    if (m_capacity == m_size) return;

    if (m_size == 0) {
        delete[] m_arr;
        m_capacity = 1;
        m_arr = new T[m_capacity];
        return;
    }

    T* new_arr = new T[m_size];
    for (size_t i = 0; i < m_size; i++) {
        new_arr[i] = std::move(m_arr[i]);
    }
    delete[] m_arr;
    m_arr = new_arr;
    m_capacity = m_size;
}

// pop_back
template <typename T>
void vector<T>::pop_back() {
    if (m_size > 0) {
        m_size--;
    }
}

// ---------- explicit instantiations ----------
template class vector<int>;
template class vector<double>;
template class vector<char>;
template class vector<std::string>;
