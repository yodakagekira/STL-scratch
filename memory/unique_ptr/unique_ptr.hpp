#ifndef UNIQUE_PTR_HPP
#define UNIQUE_PTR_HPP

#include <utility>

namespace getcracked
{
    template <typename T>
    struct custom_deleter
    {
        void operator()(T* pointer) const
        {
            delete pointer;
        }
    };

    template <typename T, typename Deleter = custom_deleter<T>>
    class unique_ptr
    {
    public:
        unique_ptr() noexcept
            : data(nullptr), is_owner(true) {}

        explicit unique_ptr(T* pointer) noexcept
            : data(pointer), is_owner(true) {}

        unique_ptr(const unique_ptr&) = delete;
        unique_ptr& operator=(const unique_ptr&) = delete;

        unique_ptr(unique_ptr&& other) noexcept
            : data(other.data), is_owner(true)
        {
            other.data = nullptr;
            other.is_owner = false;
        }

        unique_ptr& operator=(unique_ptr&& other) noexcept
        {
            if (this != &other)
            {
                if (is_owner && data)
                    deleter(data);

                data = other.data;
                is_owner = true;

                other.data = nullptr;
                other.is_owner = false;
            }
            return *this;
        }

        ~unique_ptr()
        {
            if (is_owner && data)
                deleter(data);
        }

        T* get() const noexcept
        {
            return data;
        }

        T& operator*() const
        {
            return *data;
        }

        T* operator->() const noexcept
        {
            return data;
        }

        explicit operator bool() const noexcept
        {
            return data != nullptr;
        }

        T* release() noexcept
        {
            T* temp = data;
            data = nullptr;
            is_owner = false;
            return temp;
        }

        void reset(T* pointer = nullptr) noexcept
        {
            if (is_owner && data)
                deleter(data);

            data = pointer;
            is_owner = true;
        }

        void swap(unique_ptr& other) noexcept
        {
            std::swap(data, other.data);
            std::swap(is_owner, other.is_owner);
        }

    private:
        T* data;
        bool is_owner;
        Deleter deleter;
    };

} // namespace getcracked

#endif // UNIQUE_PTR_HPP
