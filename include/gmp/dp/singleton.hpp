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

/** @addtogroup design_patterns
 * @{
 */

/**
 * @brief CRTP-based singleton helper with optional dead-reference recovery.
 *
 * Derive a type `T` from `singleton<T>` to obtain a process-wide `instance()`
 * accessor. The default specialization uses a function-local static object and
 * provides the simplest singleton lifetime model. The `LongLifeTime = true`
 * specialization keeps additional state so it can recreate the singleton after
 * destruction if `instance()` is accessed again.
 *
 * @tparam T The derived singleton type.
 * @tparam LongLifeTime When `false`, use a function-local static instance.
 * When `true`, enable dead-reference handling and recreation support.
 *
 * @par Example
 * @code
 * struct logger : gmp::singleton<logger> {
 *   GMP_DISABLE_CONSTRUCTION(logger)
 * };
 *
 * auto& log = logger::instance();
 * @endcode
 *
 * @since version 1.2.0
 */
template <typename T, bool LongLifeTime = false> class singleton;

/**
 * @brief Default singleton specialization using a function-local static object.
 *
 * This specialization is the usual zero-overhead singleton form. The first call
 * to `instance()` constructs the object, and subsequent calls return the same
 * instance for the lifetime of the program.
 *
 * @tparam T The derived singleton type.
 */
template <typename T> class singleton<T, false> {
public:
  /**
   * @brief Get the singleton instance.
   *
   * The first call constructs the object using the provided arguments. Later
   * calls ignore constructor arguments and return the same instance.
   *
   * @tparam Args Constructor argument types.
   * @param args Constructor arguments used on first initialization.
   * @return A reference to the singleton instance.
   */
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

/**
 * @brief Singleton specialization with dead-reference recovery support.
 *
 * This specialization keeps explicit state about the singleton lifetime and can
 * recreate the singleton if `instance()` is called after destruction.
 *
 * @tparam T The derived singleton type.
 */
template <typename T> class singleton<T, true> {
public:
  /**
   * @brief Get the singleton instance, recreating it if necessary.
   *
   * @tparam Args Constructor argument types.
   * @param args Constructor arguments used during creation or recreation.
   * @return A reference to the singleton instance.
   */
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

/**
 * @def GMP_DISABLE_CONSTRUCTION(Class)
 * @brief Prevent direct public construction of a singleton-derived type.
 *
 * This macro grants `gmp::singleton<Class>` friendship and makes the default
 * constructor private, which is a common pattern for CRTP singleton types.
 *
 * @param Class The singleton-derived class type.
 *
 * @par Example
 * @code
 * struct logger : gmp::singleton<logger> {
 *   GMP_DISABLE_CONSTRUCTION(logger)
 * };
 * @endcode
 */
#define GMP_DISABLE_CONSTRUCTION(Class) \
private:                                \
    friend class gmp::singleton<Class>; \
    Class() = default;

/** @} */

} // namespace gmp

#endif // GMP_DP_SINGLETON_HPP_
