#include "unique_ptr.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main()
{   
    unique_ptr<int> ptr1(new int(1)); 
    std::cout << ptr1.is_owning();

    int* ptr2 {new int(2)};
    ptr1.reset(ptr2);
    
    ptr1.release();
};