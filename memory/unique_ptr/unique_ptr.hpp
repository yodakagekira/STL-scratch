#pragma once
#include <utility>   // std::swap
#include <cstddef>   // std::nullptr_t

template <typename T>
struct custom_deleter {
    void operator()(T* p) const noexcept { delete p; }
};

template <typename T>
class unique_ptr {
public:
    // types
    using element_type = T;
    using pointer      = T*;
    using deleter_type = custom_deleter<T>;

    // ctors
    constexpr unique_ptr() noexcept : m_ptr(nullptr) {}
    explicit unique_ptr(pointer p) noexcept : m_ptr(p) {}

    // non-copyable
    unique_ptr(const unique_ptr&)            = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;
    ~unique_ptr() { m_deleter(m_ptr); }

    // movable
    unique_ptr(unique_ptr&& other) noexcept : m_ptr(other.release()) {}
    unique_ptr& operator=(unique_ptr&& other) noexcept {
        if (this != &other) {
            reset(other.release()); // delete current, take other's
        }
        return *this;
    }



    // observers
    pointer get() const noexcept         { return m_ptr; }
    element_type& operator*() const      { return *m_ptr; }
    pointer operator->() const noexcept  { return m_ptr; }
    explicit operator bool() const noexcept { return m_ptr != nullptr; }

    // modifiers
    pointer release() noexcept {
        pointer tmp = m_ptr;
        m_ptr = nullptr;
        return tmp;
    }

    void reset(pointer p = nullptr) noexcept {
        if (m_ptr != p) {
            m_deleter(m_ptr);
            m_ptr = p;
        }
    }

    void swap(unique_ptr& other) noexcept {
        std::swap(m_ptr, other.m_ptr);
    }

    // utilities
    bool is_owning() const noexcept { return m_ptr != nullptr; }
    deleter_type&       get_deleter()       noexcept { return m_deleter; }
    const deleter_type& get_deleter() const noexcept { return m_deleter; }

private:
    pointer      m_ptr{nullptr};
    deleter_type m_deleter{};
};

// non-member swap
template <typename T>
inline void swap(unique_ptr<T>& a, unique_ptr<T>& b) noexcept { a.swap(b); }

// make_unique (basic version)
template <typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args) {
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}
