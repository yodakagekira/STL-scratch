#include <iostream>
#include "unique_ptr.hpp"

struct Foo {
    Foo(int x) : value(x) {
        std::cout << "Foo(" << value << ") constructed\n";
    }
    ~Foo() {
        std::cout << "Foo(" << value << ") destroyed\n";
    }
    void hello() {
        std::cout << "Hello from Foo(" << value << ")\n";
    }
    int value;
};

int main() {
    std::cout << "---- make_unique test ----\n";
    auto p1 = make_unique<Foo>(10);   // construct with make_unique
    p1->hello();

    std::cout << "---- move test ----\n";
    unique_ptr<Foo> p2 = std::move(p1); // transfer ownership
    if (!p1) std::cout << "p1 is now empty\n";
    p2->hello();

    std::cout << "---- reset test ----\n";
    p2.reset(new Foo(20));  // destroy old Foo(10), now own Foo(20)
    p2->hello();

    std::cout << "---- release test ----\n";
    Foo* raw = p2.release(); // manual control now
    if (!p2) std::cout << "p2 is empty after release\n";
    raw->hello();
    delete raw; // must manually free!

    std::cout << "---- swap test ----\n";
    auto a = make_unique<Foo>(100);
    auto b = make_unique<Foo>(200);
    std::cout << "Before swap: a=" << a->value << ", b=" << b->value << "\n";
    swap(a, b);
    std::cout << "After swap: a=" << a->value << ", b=" << b->value << "\n";

    std::cout << "---- end of main ----\n";
}
