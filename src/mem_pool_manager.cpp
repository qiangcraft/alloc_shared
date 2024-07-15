#include "mem_pool_manager.h"
#include <mutex>

MemoryPoolManager& MemoryPoolManager::GetInstance() {
    static MemoryPoolManager instance;
    return instance;
}

MemoryPoolManager::MemoryPoolManager() {
    pool_ = new FastMemoryPool();
    pool_->CreatePool(2048, 10240);
}

MemoryPoolManager::~MemoryPoolManager() {
    std::lock_guard<SpinLock> lock(spin_lock_);
    pool_->DestroyPool();
    delete pool_;
}

void* MemoryPoolManager::Alloc(size_t sz) {
    std::lock_guard<SpinLock> lock(spin_lock_);
    return pool_->allocate(sz);
}

void MemoryPoolManager::Free(void* p) {
    std::lock_guard<SpinLock> lock(spin_lock_);
    pool_->free(p);
}

