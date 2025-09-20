// LL.cpp
#include "LL.hpp"
#include <stdexcept>

template <typename T>
LL<T>::LL() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
LL<T>::~LL() {
    clear();
}

template <typename T>
void LL<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template <typename T>
void LL<T>::push_front(const T& value) {
    ListNode<T>* newNode = new ListNode<T>(value);
    if (empty()) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
    size++;
}

template <typename T>
void LL<T>::push_back(const T& value) {
    ListNode<T>* newNode = new ListNode<T>(value);
    if (empty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

template <typename T>
void LL<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }

    ListNode<T>* temp = head;
    head = head->next;
    delete temp;
    size--;

    if (size == 0) {
        tail = nullptr;
    }
}

template <typename T>
void LL<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }

    if (size == 1) {
        delete head;
        head = tail = nullptr;
    } else {
        ListNode<T>* curr = head;
        while (curr->next != tail) {
            curr = curr->next;
        }
        delete tail;
        tail = curr;
        tail->next = nullptr;
    }
    size--;
}

template <typename T>
void LL<T>::remove(const T& value) {
    while (head && head->data == value) {
        pop_front();
    }

    ListNode<T>* curr = head;
    while (curr && curr->next) {
        if (curr->next->data == value) {
            ListNode<T>* toDelete = curr->next;
            curr->next = curr->next->next;
            if (toDelete == tail) {
                tail = curr;
            }
            delete toDelete;
            size--;
        } else {
            curr = curr->next;
        }
    }
}

template <typename T>
ListNode<T>* LL<T>::find(const T& value) const {
    ListNode<T>* curr = head;
    while (curr) {
        if (curr->data == value) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

template <typename T>
void LL<T>::print() const {
    ListNode<T>* curr = head;
    while (curr) {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

template <typename T>
std::size_t LL<T>::get_size() const {
    return size;
}

template <typename T>
bool LL<T>::empty() const {
    return size == 0;
}

template class LL<int>;       
template class LL<double>;
