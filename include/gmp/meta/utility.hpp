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

template<auto>
struct constant_arg_t {
    explicit constant_arg_t() = default;
};

template<auto V>
inline constexpr constant_arg_t<V> constant_arg{};

struct any { template<typename T> operator T() const; };

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

template<typename T>
consteval const T& as_value() noexcept {
    return detail::wrapper<T>::long_lifetime_obj.value;
}

} // namespace gmp

#endif // GMP_META_UTILITY_HPP_