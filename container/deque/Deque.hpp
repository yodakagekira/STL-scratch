#pragma once

#include <cstddef>
#include <stdexcept>
#include <cstdint>

template <typename T>
class Deque {

private:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    std::size_t count;

public:
    Deque();
    ~Deque();

    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();

    T& front();
    T& back();

    bool is_empty() const;
    std::size_t size() const;

};
