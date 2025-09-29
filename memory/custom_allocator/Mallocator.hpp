#pragma once
#include <cstddef>   // std::byte, std::size_t
#include <memory>    // allocator_traits knobs
#include "Arena.hpp"

template <typename T, std::size_t N>
class Mallocator {
public:
    using value_type = T;
    using arena_type = Arena<N>;

    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    using is_always_equal = std::false_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type;

private:
    arena_type* m_arena = nullptr;

public:
    Mallocator(arena_type& arena) noexcept : m_arena(&arena) {}
    Mallocator(const Mallocator&) = default;
    Mallocator& operator=(const Mallocator&) = default;

    template <class U>
    Mallocator(const Mallocator<U, N>& other) noexcept : m_arena(other.m_arena) {}

    pointer allocate(size_type n) {
        return reinterpret_cast<pointer>(m_arena->allocate(n * sizeof(T)));
    }
    void deallocate(pointer p, size_type n) noexcept {
        m_arena->deallocate(reinterpret_cast<std::byte*>(p), n * sizeof(T));
    }

    template <class U, std::size_t M>
    bool operator==(const Mallocator<U, M>& other) const noexcept {
        return N == M && m_arena == other.m_arena;
    }
    template <class U, std::size_t M>
    bool operator!=(const Mallocator<U, M>& other) const noexcept { return !(*this == other); }

    template <typename U>
    struct rebind { using other = Mallocator<U, N>; };

    template <class U, std::size_t M> friend class Mallocator;
};
