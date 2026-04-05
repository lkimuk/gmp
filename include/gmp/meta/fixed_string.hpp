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

#ifndef GMP_META_FIXED_STRING_HPP_
#define GMP_META_FIXED_STRING_HPP_

#include <algorithm>
#include <string_view>

#include "utility.hpp"

namespace gmp {

template<std::size_t N>
struct fixed_string final {
    using size_type = std::size_t;
    static constexpr size_type npos = size_type(-1);

    constexpr fixed_string(const char (&str)[N + 1]) {
        std::copy_n(str, N + 1, data_);
    }

    constexpr fixed_string(std::string_view sv) {
        std::copy_n(sv.data(), N, data_);
        data_[N] = '\0';
    }

    /// Element access
    [[nodiscard]] consteval char operator[](size_type pos) const noexcept {
        static_assert(pos <= N, "fixed_string: index out of range");
        return data_[pos];
    }

    consteval const char* data() const noexcept { return data_; }
    constexpr auto to_string_view() const noexcept { return std::string_view(data_, N); }

    constexpr operator char const*() const noexcept { return data_; }
    
    /// Capacity
    consteval size_type size() const noexcept { return N; }
    consteval size_type length() const noexcept { return N; }
    consteval bool empty() const noexcept { return N == 0; }

    /// Modifiers

    /// Operations
    consteval size_type find(const char* str, size_type pos = 0) const noexcept {
        auto sv = this->to_string_view();
        auto found_pos = sv.find(str, pos);
        return found_pos;
    }

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
fixed_string(char const(&)[N]) -> fixed_string<N - 1>;

template<std::size_t N1, std::size_t N2>
consteval fixed_string<N1 + N2> operator+(fixed_string<N1> const& s1, fixed_string<N2> const& s2) {
    char result[N1 + N2 + 1]{};
    std::copy_n(s1.data(), N1, result);
    std::copy_n(s2.data(), N2 + 1, result + N1);
    return fixed_string<N1 + N2>(result);
}

template<fixed_string s>
consteval auto operator""_fs() {
    return s;
}

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

template<fixed_string FirstValue, fixed_string... RestValues, auto String>
consteval auto remove_all(constant_arg_t<String>) {
    constexpr auto after = detail::remove_all_impl<FirstValue>(constant_arg<String>);
    if constexpr (sizeof...(RestValues) > 0) {
        return remove_all<RestValues...>(constant_arg<after>);
    } else {
        return after;
    }
}

} // namespace gmp

#endif // GMP_META_FIXED_STRING_HPP_