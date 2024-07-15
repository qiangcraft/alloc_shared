#pragma once

#include <cstdint>
#include <thread>
#include <atomic>

/**
 * @brief A spin lock implementation.
 * 
 * The SpinLock class provides a simple spin lock mechanism using atomic operations.
 * It allows multiple threads to synchronize their access to a shared resource.
 * reference source: https://rigtorp.se/spinlock/
 */
struct SpinLock {
  std::atomic<bool> lock_ = {0};

  /**
   * @brief Acquires the lock.
   * 
   * This function blocks until the lock is acquired.
   */
  void lock() noexcept {
    for (;;) {
      // Optimistically assume the lock is free on the first try
      if (!lock_.exchange(true, std::memory_order_acquire)) {
        return;
      }
      // Wait for lock to be released without generating cache misses
      while (lock_.load(std::memory_order_relaxed)) {
        // Issue X86 PAUSE or ARM YIELD instruction to reduce contention between
        // hyper-threads
        __builtin_ia32_pause();
      }
    }
  }

  /**
   * @brief Tries to acquire the lock.
   * 
   * This function attempts to acquire the lock without blocking.
   * 
   * @return true if the lock was acquired, false otherwise.
   */
  bool try_lock() noexcept {
    // First do a relaxed load to check if lock is free in order to prevent
    // unnecessary cache misses if someone does while(!try_lock())
    return !lock_.load(std::memory_order_relaxed) &&
           !lock_.exchange(true, std::memory_order_acquire);
  }

  /**
   * @brief Releases the lock.
   * 
   * This function releases the lock, allowing other threads to acquire it.
   */
  void unlock() noexcept {
    lock_.store(false, std::memory_order_release);
  }
};
