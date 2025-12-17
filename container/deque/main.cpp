#include "deque.hpp"

#include <iostream>

int main() {
    Deque<int> deque;

    deque.push_back(10);
    deque.push_front(20);
    deque.push_back(30);

    std::cout << "Front element: " << deque.front() << std::endl; // 20
    std::cout << "Back element: " << deque.back() << std::endl;   // 30
    std::cout << "Size: " << deque.size() << std::endl;           // 3

    deque.pop_front();
    std::cout << "Front element after pop_front: " << deque.front() << std::endl; // 10

    deque.pop_back();
    std::cout << "Back element after pop_back: " << deque.back() << std::endl;   // 10

    std::cout << "Is deque empty? " << (deque.is_empty() ? "Yes" : "No") << std::endl; // No

    deque.pop_back();
    std::cout << "Is deque empty after popping all elements? " << (deque.is_empty() ? "Yes" : "No") << std::endl; // Yes

    deque.push_front(40);
    std::cout << "Front element after pushing 40 to front: " << deque.front() << std::endl; // 40
    
    
    
    return 0;

}