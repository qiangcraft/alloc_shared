#include "fast_memory_pool.h"
#include "memory_pool.h"
#include "spin_lock.h"

class MemoryPoolManager
{
public:
	static MemoryPoolManager &GetInstance();
	void *Alloc(size_t sz);
	void Free(void *p);
	~MemoryPoolManager();

private:
	MemoryPoolManager();
	MemoryPoolManager(const MemoryPoolManager &) = delete;
	MemoryPoolManager &operator=(const MemoryPoolManager &) = delete;
	FastMemoryPool *pool_;
	SpinLock spin_lock_;
};