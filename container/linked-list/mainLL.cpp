#include "LL.hpp"

int main() {
    LL<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_front(5);
    list.print(); // Output: 5 10 20

    list.pop_back();
    list.print(); // Output: 5 10

    list.remove(5);
    list.print(); // Output: 10

    return 0;
}
