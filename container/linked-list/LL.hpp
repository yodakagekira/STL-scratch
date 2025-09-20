// LL.hpp
#pragma once
#include <cstddef>
#include <iostream>

template <typename T>
struct ListNode {
    T data;
    ListNode* next;

    ListNode(const T& value) : data(value), next(nullptr) {}
};

template <typename T>
class LL {
private:
    ListNode<T>* head;
    ListNode<T>* tail;
    std::size_t size;

    void clear();

public:
    LL();
    ~LL();

    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();
    void remove(const T& value);      
    ListNode<T>* find(const T& value) const;

    void print() const;
    std::size_t get_size() const;
    bool empty() const;
};
