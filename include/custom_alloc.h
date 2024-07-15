#pragma once
#include <memory>
#include "memory_pool.h"
#include "mem_pool_manager.h"
template <typename T>
class CustomAllocator {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    CustomAllocator() = default;
    ~CustomAllocator() = default;

    template <typename U>
    CustomAllocator(const CustomAllocator<U>&) noexcept {}

    T* allocate(size_t n) {
        return static_cast<T*>(MemoryPoolManager::GetInstance().Alloc(n * sizeof(T)));
    }

    void deallocate(T* p, size_t) {
        MemoryPoolManager::GetInstance().Free(p);
    }

    size_type max_size() const noexcept {
        return std::numeric_limits<size_type>::max() / sizeof(T);
    }
    template <typename U>
    struct rebind {
        using other = CustomAllocator<U>;
    };

private:
    template <typename U>
    friend class CustomAllocator;
};

template <typename T, typename... Args>
std::shared_ptr<T> AllocateShared(Args&&... args) {
    return std::allocate_shared<T>(CustomAllocator<T>(), std::forward<Args>(args)...);
}
