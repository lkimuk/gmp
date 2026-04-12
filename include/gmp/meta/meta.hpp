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

#include <source_location>

#include <gmp/meta/type_name.hpp>
#include <gmp/meta/detail/member_ref.hpp>

namespace gmp {

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
  requires std::is_aggregate_v<std::remove_cvref_t<T>>
consteval int member_count() {
    using value_type = std::remove_cvref_t<T>;
    if constexpr (requires { value_type{Args{}...}; }) {
        return member_count<value_type, Args..., gmp::any>();
    } else {
        return sizeof...(Args) - 1;
    }
}

/**
 * @brief Get the name of a specific member of an aggregate type at compile-time.
 * 
 * @tparam I The zero-based index of the member to get the name for.
 * @tparam T The aggregate type containing the member.
 * @return A fixed_string containing the member name.
 * 
 * @note This function is consteval and requires:
 *       - T to be an aggregate type
 *       - I to be within the valid range [0, member_count<T>())
 *       - member_count<T>() to not exceed GMP_MAX_SUPPORTED_FIELDS
 * 
 * @throws Compile-time error if any of the above requirements are not met.
 * 
 * @example
 * @code
 * struct Person {
 *     std::string name;
 *     int age;
 *     double height;
 * };
 * 
 * struct Empty {};
 * 
 * // Get individual member names
 * constexpr auto first_member = member_name<0, Person>();
 * static_assert(first_member == "name");
 * 
 * constexpr auto second_member = member_name<1, Person>();
 * static_assert(second_member == "age");
 * 
 * constexpr auto third_member = member_name<2, Person>();
 * static_assert(third_member == "height");
 * 
 * // Use in static assertions
 * static_assert(member_name<0, Person>().size() == 4);
 * 
 * // Template metaprogramming
 * template<typename T, size_t I>
 * struct MemberTraits {
 *     static constexpr auto name = member_name<I, T>();
 *     static constexpr size_t index = I;
 * };
 * 
 * static_assert(MemberTraits<Person, 1>::name == "age");
 * 
 * // These would cause compile-time errors:
 * // member_name<0, Empty>();     // Error: I < member_count<T>() fails
 * // member_name<3, Person>();    // Error: Index out of bounds
 * // member_name<0, int>();       // Error: Not an aggregate
 * @endcode
 */
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

/**
 * @brief Get all member names of an aggregate type at compile-time.
 * 
 * This function returns an array containing the names of all members
 * of the aggregate type T.
 * 
 * @tparam T The aggregate type to get member names for.
 * @return A std::array of std::string_view containing all member names.
 *         Returns an empty array if the aggregate has no members.
 * 
 * @example
 * @code
 * struct Vector3 { float x; float y; float z; };
 * struct Empty {};
 * struct Config { int timeout; bool enabled; std::string host; };
 * 
 * // Get all member names
 * constexpr auto vec_members = member_names<Vector3>();
 * static_assert(vec_members.size() == 3);
 * static_assert(vec_members[0] == "x");
 * static_assert(vec_members[1] == "y");
 * static_assert(vec_members[2] == "z");
 * 
 * // Empty aggregate
 * constexpr auto empty_members = member_names<Empty>();
 * static_assert(empty_members.empty());
 * 
 * // Compile-time iteration
 * template<typename T>
 * constexpr bool has_member(std::string_view name) {
 *     constexpr auto names = member_names<T>();
 *     for (size_t i = 0; i < names.size(); ++i) {
 *         if (names[i] == name) return true;
 *     }
 *     return false;
 * }
 * 
 * static_assert(has_member<Config>("timeout"));
 * static_assert(has_member<Config>("host"));
 * static_assert(!has_member<Config>("port"));
 * 
 * // Generate compile-time member name list
 * template<typename T>
 * struct MemberList {
 *     static constexpr auto names = member_names<T>();
 *     static constexpr size_t size = names.size();
 *     
 *     template<size_t I>
 *     static constexpr auto get() { return names[I]; }
 * };
 * 
 * using Vector3Members = MemberList<Vector3>;
 * static_assert(Vector3Members::size == 3);
 * static_assert(Vector3Members::get<1>() == "y");
 * @endcode
 */
template<typename T>
consteval auto member_names() {
    using value_type = std::remove_cvref_t<T>;
    constexpr auto size = member_count<value_type>();
    if constexpr (size == 0) {
        return std::array<std::string_view, 0>{};
    } else {
        return []<std::size_t... Is>(std::index_sequence<Is...>) {
            return (std::array<std::string_view, size> {
                member_name<Is, value_type>()...
            });
        }(std::make_index_sequence<size>{});
    }
}

/**
 * @brief Extract the type of the I-th member (field) from a struct/class T
 * 
 * @tparam I - Index of the member to extract (0-based)
 * @tparam T - The struct/class type to introspect
 * 
 * @returns The type of the I-th member, stripped of const, volatile, and reference qualifiers
 * 
 * @note Requires that T is an aggregate type (struct/class with public members)
 * @note The member count must be known at compile time
 * 
 * @example
 * struct Point { int x; float y; };
 * using XType = member_type_t<0, Point>;  // int
 * using YType = member_type_t<1, Point>;  // float
 */
template<std::size_t I, typename T>
using member_type_t = std::remove_cvref_t<
    decltype(*detail::field_getter<I, T>(constant_arg<member_count<T>()>))>;

namespace detail {

template<typename T>
struct member_type_names_holder {
    static constexpr std::size_t N = member_count<T>();

    static constexpr auto fixed_names = []<std::size_t... Is>(std::index_sequence<Is...>) {
        return std::tuple{ pretty_type_name<member_type_t<Is, T>>()()... };
    }(std::make_index_sequence<N>{});

    static constexpr auto views = []<std::size_t... Is>(std::index_sequence<Is...>) {
        return std::array<std::string_view, N>{
            std::get<Is>(fixed_names).to_string_view()...
        };
    }(std::make_index_sequence<N>{});
};

} // namespace detail

/**
 * @brief Returns an array of string_view containing the type names of all members of aggregate type T
 * 
 * @tparam T - The aggregate type to introspect (struct/class with public members)
 * 
 * @return std::array<std::string_view, N> where N is the member count of T,
 *         containing the demangled/pretty type names of each member in declaration order
 * 
 * @note The type names are generated at compile time and stored as static data
 * @note The returned string_views remain valid for the entire program lifetime
 * @note Requires T to be an aggregate type with known member count at compile time
 * 
 * @example
 * struct Person {
 *     int age;
 *     std::string name;
 *     double height;
 * };
 * 
 * auto names = member_type_names<Person>();
 * // names[0] == "int"
 * // names[1] == "std::string" (or "std::basic_string<char>")
 * // names[2] == "double"
 * 
 * @see member_type_t, member_count
 */
template<typename T>
constexpr auto member_type_names() {
    return detail::member_type_names_holder<T>::views;
}

template<std::size_t I, typename T>
    requires std::is_aggregate_v<T> &&
        (I < member_count<T>()) &&
        (member_count<T>() <= GMP_MAX_SUPPORTED_FIELDS)     
decltype(auto) member_ref(T&& value) noexcept {
    return detail::member_ref<I, T>(value, constant_arg<member_count<T>>);
}

template<std::size_t I, typename T>
decltype(auto) member_ref(T&&) noexcept {
    static_assert(std::is_aggregate_v<T>, "member_ref() can only be used with aggregate types.");
    static_assert(I < member_count<T>(), "Index out of bounds in member_ref().");
    static_assert(member_count<T>() <= GMP_MAX_SUPPORTED_FIELDS, "member_ref() only supports up to " GMP_STRINGIFY(GMP_MAX_SUPPORTED_FIELDS) " fields.");
}

namespace detail {

#define GMP_FOR_EACH_MEMBER_DEFINE(N) \
  template<typename T, typename F> \
  void for_each_member_impl(T&& value, F&& f, constant_arg_t<N>) noexcept { \
    auto&& [GMP_GET_FIRST_N(N, GMP_IDENTIFIERS)] = value; \
    auto members = std::forward_as_tuple(GMP_GET_FIRST_N(N, GMP_IDENTIFIERS)); \
    constexpr auto mem_names = gmp::member_names<T>(); \
    std::size_t index = 0; \
    std::apply( \
      [&](auto&&... member) { (f(mem_names[index++], std::forward<decltype(member)>(member)), ...); }, members); \
  }

#if GMP_STANDARD_PREPROCESSOR
    // Standard preprocessor supports 256 arguments
    GMP_FOR_EACH(GMP_FOR_EACH_MEMBER_DEFINE, GMP_RANGE(1, 256))
#else
    // MSVC traditional preprocessor: MAX 199 due to nesting depth limit (fatal error C1009)
    GMP_FOR_EACH(GMP_FOR_EACH_MEMBER_DEFINE, GMP_RANGE(1, 119))
#endif

#undef GMP_FOR_EACH_MEMBER_DEFINE

} // namespace detail

template<typename T, typename F>
    requires std::is_aggregate_v<std::remove_cvref_t<T>>
void for_each_member(T&& value, F&& func) noexcept {
    detail::for_each_member_impl(
        std::forward<T>(value),
        std::forward<F>(func),
        constant_arg<member_count<T>()>
    );
}

template<typename T, typename F>
void for_each_member(T&& value, F&& func) noexcept {
    static_assert(std::is_aggregate_v<std::remove_cvref_t<T>>,
        "for_each_member() can only be used with aggregate types.");
}

} // namespace gmp

#endif // GMP_META_HPP_