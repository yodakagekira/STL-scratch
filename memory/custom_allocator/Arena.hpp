#pragma once

#include <cstddef>
#include <cstdint>
#include <new>
#include <type_traits>

template <std::size_t N>
class Arena {

private:    
    static constexpr std::size_t alignment = alignof(std::max_align_t); // Max platform alignment (largest type guaranteed safe)
    alignas(alignment) std::byte buffer_[N]; // Raw aligned memory block
    std::byte* ptr_ = buffer_;  

    static std::size_t align_up(std::size_t n) noexcept { // Round n up to nearest multiple of alignment (power-of-2 trick)
        return (n + (alignment - 1)) & ~(alignment - 1);
    }

    // Check if pointer p lies within the buffer's memory range
    bool pointer_in_buffer(const std::byte* p) const noexcept {
        auto a = reinterpret_cast<std::uintptr_t>(buffer_);
        auto b = reinterpret_cast<std::uintptr_t>(p);
        return b >= a && b < (a + N);
    }         

public:
    Arena() noexcept = default;
    Arena(const Arena&) = delete;
    Arena& operator=(const Arena&) = delete;


    void reset() noexcept { ptr_ = buffer_; }

    static constexpr std::size_t size() noexcept { return N; }

    std::size_t used() const noexcept { return static_cast<std::size_t>(ptr_ - buffer_); } // Bytes currently allocated (distance from start to current bump)

    // Allocate n bytes, aligned up
    std::byte* allocate(std::size_t n) {
        const std::size_t aligned_n = align_up(n); 
        const std::size_t available = static_cast<std::size_t>(buffer_ + N - ptr_);

        if (available >= aligned_n) {
            std::byte* result = ptr_;
            ptr_ += aligned_n;
            return result;
        }

        // Fall back to global allocation if arena is full
        return static_cast<std::byte*>(::operator new(aligned_n));
    }

    // Deallocate only if p was *not* from our arena
    void deallocate(std::byte* p, std::size_t /*n*/) noexcept {
        if (!pointer_in_buffer(p)) {
            ::operator delete(p);
        }
        // Note: arena allocations cannot be individually freed
    }
};


