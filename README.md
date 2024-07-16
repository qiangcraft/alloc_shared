# Define custom allocator for std::shared_ptr

For introducing memory pool in my project, we can define a custom allocator for std::shared_ptr, overrided the `allocate` and `deallocate` methods, then we can make shared_ptr by the `std::alloc_shared`: 

``` cpp
std::allocate_shared<T>(custom_alloc, std::forward<Args>(args)...);
```

## Test 

```
cd alloc_shared
make build
cd build
cmake ..
make
./memory_pool
```

Allocate 10000 objects, the performance comparison result of `std::shared_ptr` and `AllocShared` is below:

```
146199us total, average : 14619us.
73266us total, average : 7326us.
```

## Usage

``` cpp
std::shared_ptr<Object> obj = AllocShared<Object>();
```


## Reference

* [AppShift-MemoryPool](https://github.com/DevShiftTeam/AppShift-MemoryPool)
* [Fixed Size Fast Memory Pool](https://arxiv.org/pdf/2210.16471)
* [SpinLock](https://rigtorp.se/spinlock/)
* [Allocator](https://en.cppreference.com/w/cpp/memory/allocator)
* [Building Your Own Allocators](https://docs.oracle.com/cd/E19205-01/819-3703/15_3.htm)
