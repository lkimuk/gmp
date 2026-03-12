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

/**
 * @brief Count the number of enumerators in an enumeration type at compile-time.
 * 
 * @tparam E The enumeration type to count enumerators for.
 * @tparam P The prefix string used to identify enumerator names (defaults to type name + "::").
 * @tparam R The current recursion index.
 * @return The number of valid enumerators in the enumeration.
 * 
 * @note This function is consteval and evaluated entirely at compile-time.
 * 
 * @example
 * @code
 * enum class Color { Red, Green, Blue, Yellow };
 * enum class Empty {};
 * 
 * // Count enumerators
 * constexpr auto count = enum_count<Color>();
 * static_assert(count == 4);
 * static_assert(enum_count<Empty>() == 0);
 * 
 * // Can be used in template metaprogramming
 * template<typename E, size_t N = enum_count<E>()>
 * struct EnumTraits {
 *     static constexpr size_t size = N;
 * };
 * 
 * static_assert(EnumTraits<Color>::size == 4);
 * @endcode
 */
template<typename E, fixed_string P = type_name<E>() + fixed_string("::"), std::size_t R = 0>
consteval auto enum_count() {
    constexpr auto name =  detail::value_name_of<E(R)>();
    if constexpr (name.find(P.data()) != std::string_view::npos) {
        return enum_count<E, P, R + 1>();
    } else {
        return R;
    }
}

/**
 * @brief Get the name of an enumerator at compile-time.
 * 
 * @tparam E The enumerator value to get the name for.
 * @tparam P The prefix string to remove from the full name (defaults to type name + "::").
 * @return A fixed_string containing the enumerator name, or "<unnamed>" if not found.
 * 
 * @example
 * @code
 * enum class Status { Ok = 200, NotFound = 404, Error = 500 };
 * enum { A, B, C };  // Unscoped enumeration
 * 
 * // Get individual enumerator names
 * constexpr auto ok_name = enum_name<Status::Ok>();
 * static_assert(ok_name == "Ok");
 * 
 * constexpr auto not_found_name = enum_name<Status::NotFound>();
 * static_assert(not_found_name == "NotFound");
 * 
 * // Works with unscoped enums
 * constexpr auto a_name = enum_name<A>();
 * static_assert(a_name == "A");
 * 
 * // Compile-time string comparison
 * static_assert(enum_name<Status::Error>() == "Error");
 * @endcode
 */
template<auto E, fixed_string P = fixed_string("::")>
consteval auto enum_name() {
    constexpr auto name = detail::value_name_of<E>();
    constexpr auto start = name.rfind(P.data());
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

/**
 * @brief Get all enumerator names of an enumeration type at compile-time.
 * 
 * This function returns an array containing the names of all enumerators
 * in the enumeration type E.
 * 
 * @tparam E The enumeration type to get enumerator names for.
 * @return A std::array of std::string_view containing all enumerator names.
 *         Returns an empty array if the enumeration has no enumerators.
 * 
 * @example
 * @code
 * enum class Permission { Read, Write, Execute };
 * 
 * // Get all enumerator names
 * constexpr auto names = enum_names<Permission>();
 * static_assert(names.size() == 3);
 * static_assert(names[0] == "Read");
 * static_assert(names[1] == "Write");
 * static_assert(names[2] == "Execute");
 * 
 * // Iterate over enumerator names at compile-time
 * template<typename E>
 * constexpr bool has_enumerator(std::string_view name) {
 *     constexpr auto names = enum_names<E>();
 *     for (size_t i = 0; i < names.size(); ++i) {
 *         if (names[i] == name) return true;
 *     }
 *     return false;
 * }
 * 
 * static_assert(has_enumerator<Permission>("Write"));
 * static_assert(!has_enumerator<Permission>("Delete"));
 * 
 * // Empty enum
 * enum class Empty {};
 * constexpr auto empty_names = enum_names<Empty>();
 * static_assert(empty_names.empty());
 * @endcode
 */
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

/**
 * @brief Count the number of members in an aggregate type at compile-time.
 * 
 * @tparam T The aggregate type to count members for.
 * @tparam Args The accumulated parameter types for construction testing.
 * @return The number of members in the aggregate type.
 * 
 * @note This function is consteval and only works with aggregate types.
 * @note Requires std::is_aggregate_v<T> to be true.
 * 
 * @example
 * @code
 * struct Point { int x; int y; };
 * struct Empty {};
 * struct Mixed { int i; double d; char c; };
 * 
 * // Count members of aggregate types
 * static_assert(member_count<Point>() == 2);
 * static_assert(member_count<Empty>() == 0);
 * static_assert(member_count<Mixed>() == 3);
 * 
 * // Can be used in template constraints
 * template<typename T>
 * concept HasTwoMembers = std::is_aggregate_v<T> && member_count<T>() == 2;
 * 
 * static_assert(HasTwoMembers<Point>);
 * static_assert(!HasTwoMembers<Mixed>);
 * @endcode
 */
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