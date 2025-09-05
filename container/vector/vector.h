#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T>
class vector {
private:
    size_t m_capacity {1};
    size_t m_size {0};
    T* m_arr { new T[m_capacity] };

public:
    vector();                                // default
    ~vector();                               // destructor
    vector(const vector& other);             // copy constructor
    vector(vector&& other) noexcept;         // move constructor
    vector& operator=(const vector& other);  // copy assignment
    vector& operator=(vector&& other) noexcept; // move assignment

    void push_back(T element);
    T& at(std::size_t index);
    const T& at(std::size_t index) const;

    std::size_t get_size() const;
    std::size_t get_capacity() const;

    void shrink_to_fit();
    void pop_back();

    friend std::ostream& operator<< (std::ostream& out, const vector& v) {
        for (size_t i = 0; i < v.m_size; i++) {
            out << v.m_arr[i];
            if (i + 1 < v.m_size) out << " ";
        }
        return out;
    }
};

#endif // VECTOR_H
