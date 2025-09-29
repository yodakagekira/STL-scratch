#include <iostream>
#include <vector>
#include <list>
#include "Arena.hpp"
#include "Mallocator.hpp"

int main() {
    constexpr std::size_t arena_size = 1024;
    Arena<arena_size> arena;

    {
        using A = Mallocator<int, arena_size>;
        std::vector<int, A> vec{ A{arena} };
        for (int i = 0; i < 100; ++i) vec.push_back(i);
        std::cout << "Vector size: " << vec.size()
                  << ", used arena bytes: " << arena.used() << "\n";
        // vec goes out of scope here — safe to reset afterwards
    }

    arena.reset(); 

    {
        using A = Mallocator<int, arena_size>;
        std::vector<int, A> vec{ A{arena} };
        for (int i = 0; i < 50; ++i) vec.push_back(i * 2);
        std::cout << "Vector size after reset: " << vec.size()
                  << ", used arena bytes: " << arena.used() << "\n";
    }

    {
        using A = Mallocator<int, arena_size>;
        std::list<int, A> lst{ A{arena} };
        for (int i = 0; i < 30; ++i) lst.push_back(i + 100);
        std::cout << "List size: " << lst.size()
                  << ", used arena bytes: " << arena.used() << "\n";
    }
}
