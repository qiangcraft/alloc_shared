#include "custom_alloc.h"
#include "object.h"
#include "memory_pool.h"
#include "spin_lock.h"
#include <thread>
#include <memory>
#include <vector>
#include <iostream>

constexpr int N = 10000;

void TimeMeasure(void(*f)()){
    auto begin = std::chrono::high_resolution_clock::now();
    uint32_t iterations = 10;
    for(uint32_t i = 0; i < iterations; ++i)
    {
		f();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count();
    std::cout << duration << "us total, average : " << duration / iterations << "us." << std::endl;
}

void UseMakeShared() {
    std::vector<std::shared_ptr<Object>> vec;
    for(int i = 0; i < N; i ++) {
        vec.emplace_back(std::make_shared<Object>());
    }
}

void UseAllocateShared() {
    std::vector<std::shared_ptr<Object>> vec;
    for(int i = 0; i < N; i ++) {
        vec.emplace_back(AllocateShared<Object>());
    }
}

int main() {
    std::cout<<sizeof(Object)<<std::endl;
    TimeMeasure(UseMakeShared);
    TimeMeasure(UseAllocateShared);
    return 0;
}
