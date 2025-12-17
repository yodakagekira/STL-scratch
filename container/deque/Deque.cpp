#include "Deque.hpp"

#include <iostream>

template <typename T>
Deque<T>::Deque() : head(nullptr), tail(nullptr), count(0) {}

template <typename T>
Deque<T>::~Deque() {
    while (!is_empty()) {
        pop_front();
    }
}

template <typename T>
void Deque<T>::push_front(const T& value) {
    Node* new_node = new Node(value);
    if (is_empty()) {
        head = tail = new_node;
    } else {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
    ++count;
}

template <typename T>
void Deque<T>::push_back(const T& value) {
    Node* new_node = new Node(value);
    if (is_empty()) {
        head = tail = new_node;
    } else {
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node;
    }
    ++count;
}

template <typename T>
void Deque<T>::pop_front() {
    if (is_empty()) {
        throw std::out_of_range("Deque is empty");
    }
    Node* temp = head;
    head = head->next;
    if (head) {
        head->prev = nullptr;
    } else {
        tail = nullptr; // Deque is now empty
    }
    delete temp;
    --count;
}

template <typename T>
void Deque<T>::pop_back() {
    if (is_empty()) {
        throw std::out_of_range("Deque is empty");
    }
    Node* temp = tail;
    tail = tail->prev;
    if (tail) {
        tail->next = nullptr;
    } else {
        head = nullptr; // Deque is now empty
    }
    delete temp;
    --count;
}

template <typename T>
T& Deque<T>::front() {
    if (is_empty()) {
        throw std::out_of_range("Deque is empty");
    }
    return head->data;
}

template <typename T>
T& Deque<T>::back() {
    if (is_empty()) {
        throw std::out_of_range("Deque is empty");
    }
    return tail->data;
}

template <typename T>
bool Deque<T>::is_empty() const {
    return count == 0;
}

template <typename T>
std::size_t Deque<T>::size() const {
    return count;
}

// Explicit template instantiation
template class Deque<int>;
template class Deque<double>;
template class Deque<std::string>;
