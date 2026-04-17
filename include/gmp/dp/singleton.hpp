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
// This singleton implementation was originally written by the same author
// for the okdp library in 2020 and later adapted for GMP:
// https://github.com/lkimuk/okdp

#ifndef GMP_DP_SINGLETON_HPP_
#define GMP_DP_SINGLETON_HPP_

#include <cstdlib>
#include <new>

#include <gmp/dp/lock.hpp>

namespace gmp {

/*!
@brief a class template to implement singleton pattern
@tparam T type for singleton class
@tparam LongLifeTime type is a bool value that false is not supported dead-reference and true is on
the contrary.

@subclass Any subclass should use CRTP to become a singleton type.
For example, class Log : public gmp::singleton<T> {}; // non-dead-reference version
       class Log : public gmp::singleton<T, true> {}; // dead-reference version

@since version 1.2.0
*/
template <typename T, bool LongLifeTime = false> class singleton;

template <typename T> class singleton<T, false> {
public:
  template <typename... Args> static T& instance(Args&&... args) {
    static T obj(std::forward<Args>(args)...);
    return obj;
  }

protected:
  singleton() = default;
  virtual ~singleton() {}

private:
  singleton(const singleton&) = delete;
  singleton& operator=(const singleton&) = delete;
  singleton(singleton&&) = delete;
  singleton& operator=(singleton&&) = delete;
};

template <typename T> class singleton<T, true> {
public:
  template <typename... Args> static T& instance(Args&&... args) {
    if (!pInstance_) {
      // DCL
      lock_.lock();

      if (!pInstance_) {
        destroyed_ ? on_dead_reference(std::forward<Args>(args)...)
                   : create(std::forward<Args>(args)...);
      }

      lock_.unlock();
    }

    return *pInstance_;
  }

private:
  template <typename... Args> static void create(Args&&... args) {
    static T obj(std::forward<Args>(args)...);
    pInstance_ = &obj;
  }

  template <typename... Args> static void on_dead_reference(Args&&... args) {
    create(std::forward<Args>(args)...);
    new (pInstance_) T(std::forward<Args>(args)...);
    std::atexit(kill_singleton);
    destroyed_ = false;
  }

  static void kill_singleton() {
    pInstance_->~singleton();
  }

  singleton(const singleton&);
  singleton& operator=(const singleton&);
  singleton(singleton&&);
  singleton& operator=(singleton&&);

  static dp::spin_lock lock_;

protected:
  singleton() = default;
  virtual ~singleton() {
    pInstance_ = nullptr;
    destroyed_ = true;
  }

  static T* pInstance_;
  static bool destroyed_;
};

template<typename T> T* singleton<T, true>::pInstance_ = nullptr;
template<typename T> bool singleton<T, true>::destroyed_ = false;
template<typename T> dp::spin_lock singleton<T, true>::lock_;

#define GMP_DISABLE_CONSTRUCTION(Class) \
private:                                \
    friend class gmp::singleton<Class>; \
    Class() = default;

} // namespace gmp

#endif // GMP_DP_SINGLETON_HPP_
