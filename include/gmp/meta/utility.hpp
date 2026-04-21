//   ___ __  __ ___ 
//  / __|  \/  | _ \ GMP(Generative Metaprogramming)
// | (_ | |\/| |  _/ version 0.2.0
//  \___|_|  |_|_|   https://github.com/lkimuk/gmp
//
// SPDX-FileCopyrightText: 2023-2026 Gaoxing Li <https://www.cppmore.com/>
// SPDX-License-Identifier: MIT
//
// This file is part of the GMP (Generative Metaprogramming) library.
// Full project source: https://github.com/lkimuk/gmp

#ifndef GMP_META_UTILITY_HPP_
#define GMP_META_UTILITY_HPP_

namespace gmp {

/** @addtogroup type_utilities
 * @{
 */

/**
 * @brief Wrap a compile-time value as a distinct function argument type.
 * 
 * `constant_arg_t<V>` is used to pass non-type template parameter values
 * through overload sets while preserving them as part of the type.
 * 
 * @tparam The compile-time value being wrapped.
 */
template<auto>
struct constant_arg_t {
    explicit constant_arg_t() = default;
};

/**
 * @brief A ready-to-use `constant_arg_t<V>` object for a compile-time value.
 * 
 * @tparam V The wrapped compile-time value.
 */
template<auto V>
inline constexpr constant_arg_t<V> constant_arg{};

/**
 * @brief A placeholder type implicitly convertible to any type.
 * 
 * `any` is primarily used in compile-time aggregate probing and other
 * metaprogramming contexts where a value of arbitrary type is required.
 */
struct any { template<typename T> operator T() const; };

/** @} */

namespace detail {

template<typename T>
struct wrapper {
    const T value{};
    static const wrapper<T> long_lifetime_obj;

    wrapper() = default;
    wrapper(const wrapper&) = delete;
    wrapper& operator=(const wrapper&) = delete;
    wrapper& operator=(wrapper&&) = delete;
};

template<typename T>
const wrapper<T> wrapper<T>::long_lifetime_obj{};

} // namespace detail

/** @addtogroup type_utilities
 * @{
 */

/**
 * @brief Expose a default-constructed value of type `T` as a compile-time reference.
 * 
 * @tparam T The type whose static compile-time value should be returned.
 * @return A reference to a long-lived default-constructed `T`.
 */
template<typename T>
consteval const T& as_value() noexcept {
    return detail::wrapper<T>::long_lifetime_obj.value;
}

/** @} */

} // namespace gmp

#endif // GMP_META_UTILITY_HPP_
