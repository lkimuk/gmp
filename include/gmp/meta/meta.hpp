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

#ifndef GMP_META_HPP_
#define GMP_META_HPP_

#include <array>
#include <source_location>

#include <gmp/meta/fixed_string.hpp>
#include <gmp/meta/detail/name.hpp>

namespace gmp {

/**
 * @brief Get the string representation of a type at compile-time.
 * 
 * This function returns a compile-time string representing the name of the 
 * given type T. The implementation is compiler-specific and extracts the 
 * type name from compiler-generated function signatures.
 * 
 * @tparam T The type whose name is to be retrieved.
 * @return A fixed_string containing the type name. If the compiler is not 
 *         supported (currently GCC, Clang, and MSVC are supported), returns 
 *         "Unknown type name".
 * 
 * @note This function is marked as consteval, ensuring it's evaluated 
 *       entirely at compile-time. The returned string is suitable for 
 *       compile-time string manipulation and comparison.
 * 
 * @example
 * @code
 * auto int_name = type_name<int>();     // "int" on all compilers
 * auto vec_name = type_name<std::vector<int>>(); // Compiler-specific representation
 * 
 * // Can be used in static assertions
 * static_assert(type_name<int>().size() == 3);
 * @endcode
 */
template<typename T>
consteval auto type_name() {
    constexpr auto name = detail::type_name_of<T>();
#if GMP_COMPILER_MSVC
    constexpr fixed_string<name.size()> type(name);
    return remove_all<"class ", "struct ", "enum ">(constant_arg<type>);
#else
    return fixed_string<name.size()>(name);
#endif
}

template<typename E, fixed_string P = type_name<E>() + fixed_string("::"), std::size_t R = 0>
consteval auto enum_count() {
    constexpr auto name =  detail::value_name_of<E(R)>();
    if constexpr (name.find(P.data()) != std::string_view::npos) {
        return enum_count<E, P, R + 1>();
    } else {
        return R;
    }
}

template<auto E, fixed_string P = type_name<decltype(E)>() + fixed_string("::")>
consteval auto enum_name() {
    constexpr auto name = detail::value_name_of<E>();
    constexpr auto start = name.find(P.data());
    if constexpr (start != std::string_view::npos) {
#if GMP_COMPILER_CLANG || GMP_COMPILER_GCC
        constexpr auto end = name.find_last_of("]");
#else
        constexpr auto end = name.find_last_of(">");
#endif
        return name.substr(start + P.size(), end - start - P.size());
    } else {
        return "<unnamed>";
    }
}

template<typename E>
consteval auto enum_names() {
    constexpr auto size = enum_count<E>();
    if constexpr (size == 0) {
        return std::array<std::string_view, 0>{};
    } else {
        return []<std::size_t... Is>(std::index_sequence<Is...>) {
            return (std::array<std::string_view, size> {
                enum_name<E(Is)>()...
            });
        }(std::make_index_sequence<size>{});
    }
}

template<typename T, typename... Args>
  requires std::is_aggregate_v<T>
consteval int member_count() {
    if constexpr (requires { T{Args{}...}; }) {
        return member_count<T, Args..., gmp::any>();
    } else {
        return sizeof...(Args) - 1;
    }
}

template<std::size_t I, typename T>
    requires std::is_aggregate_v<T> &&
        (I < member_count<T>()) &&
        (member_count<T>() <= GMP_MAX_SUPPORTED_FIELDS)     
consteval auto member_name() noexcept {
    constexpr auto name = detail::member_name_of<detail::field_getter<I, T>(constant_arg<member_count<T>()>)>();
    return name;
}

template<std::size_t I, typename T>
consteval auto member_name() noexcept {
    static_assert(std::is_aggregate_v<T>, "member_name() can only be used with aggregate types.");
    static_assert(I < member_count<T>(), "Index out of bounds in member_name().");
    static_assert(member_count<T>() <= GMP_MAX_SUPPORTED_FIELDS, "member_name() only supports up to " GMP_STRINGIFY(GMP_MAX_SUPPORTED_FIELDS) " fields.");
}

template<typename T>
consteval auto member_names() {
    constexpr auto size = member_count<T>();
    if constexpr (size == 0) {
        return std::array<std::string_view, 0>{};
    } else {
        return []<std::size_t... Is>(std::index_sequence<Is...>) {
            return (std::array<std::string_view, size> {
                member_name<Is, T>()...
            });
        }(std::make_index_sequence<size>{});
    }
}

} // namespace gmp

#endif // GMP_META_HPP_