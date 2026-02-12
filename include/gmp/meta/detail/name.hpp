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

#ifndef GMP_DETAIL_NAME_HPP_
#define GMP_DETAIL_NAME_HPP_

#include <string_view>
#include <tuple>

#include <gmp/macro/macro.hpp>
#include <gmp/meta/utility.hpp>

namespace gmp::detail {

template<auto V>
consteval auto value_name_of() {
    return std::string_view(std::source_location::current().function_name());
}

template<typename T>
consteval auto type_name_of() {
    using namespace std::string_view_literals;
#if GMP_COMPILER_CLANG
    constexpr auto prefix = "[T = "sv;
    constexpr auto suffix = "]"sv;
#elif GMP_COMPILER_GCC
    constexpr auto prefix = "with T = "sv;
    constexpr auto suffix = "]"sv;
#elif GMP_COMPILER_MSVC
    constexpr auto prefix = "gmp::detail::type_name_of<"sv;
    constexpr auto suffix = ">"sv;
#else
    return "Unknown type name"sv;
#endif

    const auto name = std::string_view(std::source_location::current().function_name());
    const auto start = name.find(prefix) + prefix.size();
    const auto end = name.find_last_of(suffix);
    return name.substr(start, end - start);
}

template<auto V>
consteval auto member_name_of() {
    const auto name = std::string_view(std::source_location::current().function_name());

    using namespace std::string_view_literals;
#if GMP_COMPILER_CLANG
    constexpr auto prefix = "long_lifetime_obj.value."sv;
    constexpr auto suffix = "]"sv;
    const auto start = name.find(prefix) + prefix.size();
    const auto end = name.find_last_of(suffix);
#elif GMP_COMPILER_GCC
    constexpr auto prefix = "::"sv;
    constexpr auto suffix = ")]"sv;
    const auto start = name.rfind(prefix) + prefix.size();
    const auto end = name.rfind(suffix);
    return name.substr(start, end - start);
#elif GMP_COMPILER_MSVC
    constexpr auto prefix = "long_lifetime_obj->value->"sv;
    constexpr auto suffix = ">"sv;
    const auto start = name.find(prefix) + prefix.size();
    const auto end = name.find_last_of(suffix);
#else
    return "Unknown type name"sv;
#endif
    
    return name.substr(start, end - start);
}

#define FIELD_GETTER_DEFINE(i) \
    template<std::size_t I, typename T> \
    consteval auto field_getter(constant_arg_t<i>) { \
        const auto& [GMP_GET_FIRST_N(i, GMP_IDENTIFIERS)] = as_value<std::remove_cv_t<T>>(); \
        const auto get_ptr = [](const auto&... fields) { \
            return std::get<I>(std::tuple{&fields...}); \
        }; \
        return get_ptr(GMP_GET_FIRST_N(i, GMP_IDENTIFIERS)); \
    }

#if GMP_STANDARD_PREPROCESSOR
    #define GMP_MAX_SUPPORTED_FIELDS 255
    // Standard preprocessor supports 256 arguments
    GMP_FOR_EACH(FIELD_GETTER_DEFINE, GMP_RANGE(1, 256))
#else
    #define GMP_MAX_SUPPORTED_FIELDS 118
    // MSVC traditional preprocessor: MAX 199 due to nesting depth limit (fatal error C1009)
    GMP_FOR_EACH(FIELD_GETTER_DEFINE, GMP_RANGE(1, 119))
#endif

} // namespace gmp::detail

#endif // GMP_DETAIL_NAME_HPP_