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

#ifndef GMP_META_TYPE_NAME_HPP_
#define GMP_META_TYPE_NAME_HPP_

#include <array>
#include <vector>

#include <gmp/meta/detail/name.hpp>
#include <gmp/meta/to_fixed_string.hpp>

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

template<typename T>
struct pretty_type_name {
    consteval auto operator()() { return type_name<T>(); }
};

template<>
struct pretty_type_name<std::string> {
    consteval auto operator()() { return fixed_string("std::string"); }
};

template<>
struct pretty_type_name<std::string_view> {
    consteval auto operator()() { return fixed_string("std::string_view"); }
};

template<typename T>
struct pretty_type_name<std::vector<T>> {
    consteval auto operator()() {
        return "std::vector<"_fs + pretty_type_name<T>()() + ">"_fs;
    }
};

template<typename T, std::size_t N>
struct pretty_type_name<std::array<T, N>> {
    consteval auto operator()() {
        return "std::array<"_fs + pretty_type_name<T>()() +
            ", "_fs + to_fixed_string_v<N> + ">"_fs;
    }
};

} // namespace gmp

#endif // GMP_META_TYPE_NAME_HPP_