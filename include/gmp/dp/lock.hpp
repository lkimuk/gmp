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

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4514) // C4514: unreferenced inline function has been removed
#endif

/*!
@brief add lock via memory model

@since version 1.0.0
*/
class spin_lock {
private:
  std::atomic_flag flag_ = ATOMIC_FLAG_INIT;

public:
  spin_lock() = default;
  ~spin_lock() = default;

  spin_lock(const spin_lock&) = delete;
  spin_lock& operator=(const spin_lock&) = delete;
  spin_lock(spin_lock&&) = delete;
  spin_lock& operator=(spin_lock&&) = delete;

  void lock() {
    while (flag_.test_and_set(std::memory_order_acquire));
  }

  void unlock() {
    flag_.clear(std::memory_order_release);
  }
};

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

} // namespace gmp::dp

#endif // GMP_DP_LOCK_HPP_
