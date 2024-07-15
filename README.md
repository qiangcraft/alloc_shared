# Define custom allocator for std::shared_ptr

For introduce memory pool in my project, use custom allocator for std::shared_ptr

## Test 

```
cd alloc_shared
make build
cd build
cmake ..
make
./memory_pool
```

Allocate 10000 objects, `std::shared_ptr` vs `AllocShared`

```
146199ns total, average : 14619us.
73266ns total, average : 7326us.
```

## Usage

``` cpp
std::shared_ptr<Object> obj = AllocShared<Object>();
```


## Reference

* [Fixed Size Fast Memory Pool](https://arxiv.org/pdf/2210.16471)
* [SpinLock](https://rigtorp.se/spinlock/)
* [Allocator](https://en.cppreference.com/w/cpp/memory/allocator)
* [Building Your Own Allocators](https://docs.oracle.com/cd/E19205-01/819-3703/15_3.htm)


