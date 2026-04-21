//   ___ __  __ ___ 
//  / __|  \/  | _ \ GMP(Generative Metaprogramming)
// | (_ | |\/| |  _/ version 0.3.0
//  \___|_|  |_|_|   https://github.com/lkimuk/gmp
//
// SPDX-FileCopyrightText: 2026 Gaoxing Li <https://www.cppmore.com/>
// SPDX-License-Identifier: MIT
//
// This file is part of the GMP (Generative Metaprogramming) library.
// Full project source: https://github.com/lkimuk/gmp

#ifndef GMP_META_TYPE_SIZE_HPP_
#define GMP_META_TYPE_SIZE_HPP_

#include <cstddef>
#include <type_traits>
#include <utility>

#include <gmp/meta/meta.hpp>

namespace gmp {

namespace detail {

template<typename T>
consteval std::size_t type_size_impl();

template<typename T, std::size_t... Is>
consteval std::size_t aggregate_type_size_impl(std::index_sequence<Is...>) {
    return (std::size_t{} + ... + type_size_impl<member_type_t<Is, T>>());
}

template<typename T>
consteval std::size_t type_size_impl() {
    using value_type = std::remove_cvref_t<T>;

    if constexpr (std::is_unbounded_array_v<value_type>) {
        static_assert(!std::is_unbounded_array_v<value_type>,
            "type_size() cannot calculate the size of an unbounded array type.");
    } else if constexpr (std::is_bounded_array_v<value_type>) {
        return std::extent_v<value_type> * type_size_impl<std::remove_extent_t<value_type>>();
    } else if constexpr (std::is_aggregate_v<value_type>) {
        constexpr auto size = member_count<value_type>();
        static_assert(size <= GMP_MAX_SUPPORTED_FIELDS,
            "type_size() only supports up to " GMP_STRINGIFY(GMP_MAX_SUPPORTED_FIELDS) " fields.");

        return aggregate_type_size_impl<value_type>(std::make_index_sequence<size>{});
    } else {
        return sizeof(value_type);
    }
}

} // namespace detail

/** @addtogroup type_utilities
 * @{
 */

/**
 * @brief Calculate the actual payload size of a type without aggregate padding.
 *
 * For aggregate types, this function sums the sizes of members in declaration
 * order and does not count padding bytes inserted between members or after the
 * final member. Nested aggregate members and bounded array types are calculated
 * recursively. Non-aggregate leaf types use sizeof(T).
 *
 * @tparam T The type to calculate.
 * @return The payload size of T, excluding aggregate padding.
 *
 * @example
 * @code
 * struct Packet {
 *     char tag;
 *     int value;
 * };
 *
 * static_assert(gmp::type_size<Packet>() == sizeof(char) + sizeof(int));
 * static_assert(gmp::type_size<Packet>() <= sizeof(Packet));
 * @endcode
 */
template<typename T>
consteval std::size_t type_size() {
    return detail::type_size_impl<T>();
}

/** @} */

} // namespace gmp

#endif // GMP_META_TYPE_SIZE_HPP_
