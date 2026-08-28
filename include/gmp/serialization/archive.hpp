//   ___ __  __ ___
//  / __|  \/  | _ \ GMP(Generative Metaprogramming)
// | (_ | |\/| |  _/ version 0.4.0
//  \___|_|  |_|_|   https://github.com/lkimuk/gmp
//
// SPDX-FileCopyrightText: 2023-2026 Miles Li <https://www.cppmore.com/>
// SPDX-License-Identifier: MIT
//
// This file is part of the GMP (Generative Metaprogramming) library.
// Full project source: https://github.com/lkimuk/gmp

#ifndef GMP_SERIALIZATION_ARCHIVE_HPP_
#define GMP_SERIALIZATION_ARCHIVE_HPP_

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <string_view>
#include <type_traits>
#include <utility>

#include <gmp/serialization/error.hpp>

namespace gmp {

enum class serialization_kind {
  null,
  boolean,
  signed_integer,
  unsigned_integer,
  floating,
  string,
  array,
  object
};

template <typename A>
concept serialization_writer = requires(A &a, bool b, std::int64_t i, std::uint64_t u, double d,
                                        std::string_view s, std::size_t n) {
                                 { a.write_null() } -> std::same_as<serialization_result<void>>;
                                 { a.write_bool(b) } -> std::same_as<serialization_result<void>>;
                                 { a.write_signed(i) } -> std::same_as<serialization_result<void>>;
                                 {
                                   a.write_unsigned(u)
                                   } -> std::same_as<serialization_result<void>>;
                                 {
                                   a.write_floating(d)
                                   } -> std::same_as<serialization_result<void>>;
                                 { a.write_string(s) } -> std::same_as<serialization_result<void>>;
                                 { a.begin_array(n) } -> std::same_as<serialization_result<void>>;
                                 { a.end_array() } -> std::same_as<serialization_result<void>>;
                                 { a.begin_object(n) } -> std::same_as<serialization_result<void>>;
                                 { a.write_key(s) } -> std::same_as<serialization_result<void>>;
                                 { a.end_object() } -> std::same_as<serialization_result<void>>;
                               };

template <typename A>
concept serialization_reader =
    std::move_constructible<A> &&
    requires(const A &a, std::size_t i) {
      { a.kind() } -> std::same_as<serialization_kind>;
      { a.size() } -> std::same_as<std::size_t>;
      { a.read_bool() } -> std::same_as<bool>;
      { a.read_signed() } -> std::same_as<std::int64_t>;
      { a.read_unsigned() } -> std::same_as<std::uint64_t>;
      { a.read_floating() } -> std::same_as<double>;
      { a.read_string() } -> std::same_as<std::string_view>;
      { a.element(i) } -> std::same_as<A>;
      requires std::same_as<std::remove_cvref_t<decltype(a.member(i).value)>, A>;
      { a.member(i).name } -> std::convertible_to<std::string_view>;
    };

} // namespace gmp

#endif // GMP_SERIALIZATION_ARCHIVE_HPP_
