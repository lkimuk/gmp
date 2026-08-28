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

#ifndef GMP_SERIALIZATION_TRAITS_HPP_
#define GMP_SERIALIZATION_TRAITS_HPP_

#include <array>
#include <concepts>
#include <cstddef>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>

#include <gmp/meta/fixed_string.hpp>

namespace gmp {

template <typename T> struct serialization_traits {};

template <typename T> struct serialization_schema {};

template <typename T> struct type_tag {
  using type = T;
};

namespace detail {

struct no_serialization_default {
  friend constexpr bool operator==(no_serialization_default, no_serialization_default) = default;
};

inline constexpr no_serialization_default no_default{};

} // namespace detail

template <fixed_string Member, fixed_string Wire = Member, bool Transient = false,
          auto Default = detail::no_default, fixed_string... Aliases>
struct serialization_field {
  static constexpr auto member = Member;
  static constexpr auto wire_name = Wire;
  static constexpr bool is_transient = Transient;
  static constexpr auto default_provider = Default;
  static constexpr bool has_default =
      !std::same_as<std::remove_cv_t<decltype(Default)>, detail::no_serialization_default>;

  template <fixed_string Name> consteval auto name() const {
    return serialization_field<Member, Name, Transient, Default, Aliases...>{};
  }

  template <fixed_string Name> consteval auto alias() const {
    return serialization_field<Member, Wire, Transient, Default, Aliases..., Name>{};
  }

  consteval auto transient() const {
    return serialization_field<Member, Wire, true, Default, Aliases...>{};
  }

  template <auto Value> consteval auto defaulted() const {
    return serialization_field<Member, Wire, Transient, Value, Aliases...>{};
  }

  template <auto Provider> consteval auto default_with() const {
    static_assert(std::is_invocable_v<decltype(Provider)>);
    return serialization_field<Member, Wire, Transient, Provider, Aliases...>{};
  }

  [[nodiscard]] static constexpr bool matches(std::string_view input) {
    return input == Wire.to_string_view() || ((input == Aliases.to_string_view()) || ...);
  }

  template <typename Other> [[nodiscard]] static constexpr bool overlaps() {
    return Other::matches(Wire.to_string_view()) ||
           (Other::matches(Aliases.to_string_view()) || ...);
  }

  [[nodiscard]] static consteval bool names_unique() {
    constexpr std::array names{Wire.to_string_view(), Aliases.to_string_view()...};
    for (std::size_t i = 0; i < names.size(); ++i)
      for (std::size_t j = i + 1; j < names.size(); ++j)
        if (names[i] == names[j])
          return false;
    return true;
  }

  template <typename T> static constexpr T make_default() {
    static_assert(has_default);
    if constexpr (std::is_invocable_v<decltype(Default)>)
      return static_cast<T>(Default());
    else
      return static_cast<T>(Default);
  }
};

template <fixed_string Member> inline constexpr serialization_field<Member> field{};

template <typename... Fields> consteval auto define_schema(Fields... fields) {
  return std::tuple<Fields...>{fields...};
}

} // namespace gmp

#endif // GMP_SERIALIZATION_TRAITS_HPP_
