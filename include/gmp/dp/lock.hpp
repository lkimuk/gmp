//   ___ __  __ ___ 
//  / __|  \/  | _ \ GMP(Generative Metaprogramming)
// | (_ | |\/| |  _/ version 0.3.0
//  \___|_|  |_|_|   https://github.com/lkimuk/gmp
//
// SPDX-FileCopyrightText: 2020-2026 Gaoxing Li <https://www.cppmore.com/>
// SPDX-License-Identifier: MIT
//
// This file is part of the GMP (Generative Metaprogramming) library.
// Full project source: https://github.com/lkimuk/gmp
//
// This spin lock implementation was originally written by the same author
// for the okdp library in 2020 and later adapted for GMP:
// https://github.com/lkimuk/okdp

#ifndef GMP_DP_LOCK_HPP_
#define GMP_DP_LOCK_HPP_

#include <atomic>

namespace gmp::dp {

/** @addtogroup design_patterns
 * @{
 */

/**
 * @brief A minimal spin lock built on `std::atomic_flag`.
 *
 * `spin_lock` provides a tiny mutual-exclusion primitive for short critical
 * sections. It repeatedly attempts to acquire the lock until it succeeds.
 *
 * @warning Because this lock busy-waits, it should only be used for brief
 * low-contention regions. It is not a replacement for heavier blocking mutexes
 * when waiting may be prolonged.
 *
 * @since version 1.0.0
 */
class spin_lock {
private:
  std::atomic_flag flag_ = ATOMIC_FLAG_INIT;

public:
  /**
   * @brief Acquire the lock by spinning until it becomes available.
   */
  void lock() {
    while (flag_.test_and_set(std::memory_order_acquire));
  }

  /**
   * @brief Release the lock.
   */
  void unlock() {
    flag_.clear(std::memory_order_release);
  }
};

/** @} */

} // namespace gmp::dp

#endif // GMP_DP_LOCK_HPP_
