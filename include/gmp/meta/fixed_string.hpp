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

#ifndef GMP_META_FIXED_STRING_HPP_
#define GMP_META_FIXED_STRING_HPP_

#include <algorithm>
#include <string_view>

#include "utility.hpp"

namespace gmp {

/** @addtogroup compile_time_string_utilities
 * @{
 */

/**
 * @brief A compile-time string type with fixed length and constexpr operations.
 * 
 * `fixed_string<N>` stores `N` characters plus a trailing null terminator and
 * is intended for non-type template parameter and compile-time string
 * manipulation use cases.
 * 
 * @tparam N The number of characters excluding the null terminator.
 */
template<std::size_t N>
struct fixed_string final {
    using size_type = std::size_t;
    static constexpr size_type npos = size_type(-1);

    /**
     * @brief Construct a fixed string from a string literal.
     * 
     * @param str The source character array including the terminating null byte.
     */
    [[maybe_unused]] constexpr fixed_string(const char (&str)[N + 1]) {
        std::copy_n(str, N + 1, data_);
    }

    /**
     * @brief Construct a fixed string from a string view of matching length.
     * 
     * @param sv The source string view.
     */
    [[maybe_unused]] constexpr fixed_string(std::string_view sv) {
        std::copy_n(sv.data(), N, data_);
        data_[N] = '\0';
    }

    /// Element access
    /**
     * @brief Access a character at the specified compile-time index.
     * 
     * @param pos The zero-based character position.
     * @return The character at `pos`.
     */
    [[nodiscard]] consteval char operator[](size_type pos) const noexcept {
        static_assert(pos <= N, "fixed_string: index out of range");
        return data_[pos];
    }

    /**
     * @brief Get a pointer to the underlying null-terminated character data.
     * 
     * @return Pointer to the stored character buffer.
     */
    consteval const char* data() const noexcept { return data_; }

    /**
     * @brief Convert the fixed string to `std::string_view`.
     * 
     * @return A string view covering the stored characters.
     */
    constexpr auto to_string_view() const noexcept { return std::string_view(data_, N); }

    /**
     * @brief Implicitly convert to `const char*`.
     * 
     * @return Pointer to the stored character buffer.
     */
    constexpr operator char const*() const noexcept { return data_; }
    
    /// Capacity
    /**
     * @brief Get the number of stored characters.
     * 
     * @return The string length excluding the null terminator.
     */
    consteval size_type size() const noexcept { return N; }

    /**
     * @brief Get the number of stored characters.
     * 
     * @return The string length excluding the null terminator.
     */
    consteval size_type length() const noexcept { return N; }

    /**
     * @brief Check whether the fixed string is empty.
     * 
     * @return `true` if the string contains no characters, otherwise `false`.
     */
    consteval bool empty() const noexcept { return N == 0; }

    /// Modifiers

    /// Operations
    /**
     * @brief Find the first occurrence of a C-string inside the fixed string.
     * 
     * @param str The substring to search for.
     * @param pos The starting position of the search.
     * @return The index of the first match, or `npos` if not found.
     */
    consteval size_type find(const char* str, size_type pos = 0) const noexcept {
        auto sv = this->to_string_view();
        auto found_pos = sv.find(str, pos);
        return found_pos;
    }

    /**
     * @brief Extract a compile-time substring.
     * 
     * @tparam Pos The starting position.
     * @tparam Count The number of characters to extract, or `npos` for the suffix.
     * @param The compile-time starting position wrapper.
     * @param The compile-time count wrapper.
     * @return A new `fixed_string` containing the selected substring.
     */
    template<auto Pos, auto Count = fixed_string::npos>
    consteval auto substr(constant_arg_t<Pos>, constant_arg_t<Count> = constant_arg<fixed_string::npos>) const noexcept {
        constexpr std::size_t actual_count = (Count == fixed_string<N>::npos) ? 
                                          (N - Pos) : Count;
        static_assert(Pos <= N, "fixed_string::substr: position out of range");
        static_assert(Pos + actual_count <= N, "fixed_string::substr: count out of range");

        char buffer[actual_count + 1]{};
        std::copy_n(data_ + Pos, actual_count, buffer);
        buffer[actual_count] = '\0';
        return fixed_string<actual_count>(buffer);
    }

    friend consteval auto operator<=>(fixed_string const&, fixed_string const&) = default;
    
    char data_[N + 1];
};

template<std::size_t N>
/**
 * @brief Deduce `fixed_string` length from a string literal.
 * 
 * @tparam N The size of the source character array including the null terminator.
 */
fixed_string(char const(&)[N]) -> fixed_string<N - 1>;

/**
 * @brief Concatenate two fixed strings at compile time.
 * 
 * @tparam N1 The length of the left-hand string.
 * @tparam N2 The length of the right-hand string.
 * @param s1 The left-hand operand.
 * @param s2 The right-hand operand.
 * @return A new `fixed_string` containing the concatenated result.
 */
template<std::size_t N1, std::size_t N2>
consteval fixed_string<N1 + N2> operator+(fixed_string<N1> const& s1, fixed_string<N2> const& s2) {
    char result[N1 + N2 + 1]{};
    std::copy_n(s1.data(), N1, result);
    std::copy_n(s2.data(), N2 + 1, result + N1);
    return fixed_string<N1 + N2>(result);
}

/**
 * @brief User-defined literal for constructing `fixed_string` values.
 * 
 * @tparam s The compile-time string literal value.
 * @return A `fixed_string` initialized from the literal.
 */
template<fixed_string s>
consteval auto operator""_fs() {
    return s;
}

/** @} */

namespace detail {

template<fixed_string Value, auto String>
consteval auto remove_all_impl(constant_arg_t<String>) {
    constexpr auto pos = String.find(Value.data());
    if constexpr (pos == decltype(String)::npos) {
        return String;
    } else {
        constexpr auto after = String.substr(constant_arg<0>, constant_arg<pos>);
        if constexpr (pos + Value.size() < String.size()) {
            constexpr auto res = after + String.substr(constant_arg<pos + Value.size()>);
            return remove_all<Value>(constant_arg<res>);
        } else {
            return after;
        }
    }
}

} // namespace detail

/** @addtogroup compile_time_string_utilities
 * @{
 */

/**
 * @brief Remove all occurrences of one or more compile-time substrings.
 * 
 * @tparam FirstValue The first substring to remove.
 * @tparam RestValues Additional substrings to remove after `FirstValue`.
 * @tparam String The input compile-time string.
 * @param The compile-time input string wrapper.
 * @return A new `fixed_string` with all requested substrings removed.
 */
template<fixed_string FirstValue, fixed_string... RestValues, auto String>
consteval auto remove_all(constant_arg_t<String>) {
    constexpr auto after = detail::remove_all_impl<FirstValue>(constant_arg<String>);
    if constexpr (sizeof...(RestValues) > 0) {
        return remove_all<RestValues...>(constant_arg<after>);
    } else {
        return after;
    }
}

/** @} */

} // namespace gmp

#endif // GMP_META_FIXED_STRING_HPP_
