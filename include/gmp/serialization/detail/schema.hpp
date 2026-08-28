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

#ifndef GMP_SERIALIZATION_DETAIL_SCHEMA_HPP_
#define GMP_SERIALIZATION_DETAIL_SCHEMA_HPP_

#include <tuple>
#include <type_traits>

#include <gmp/meta/meta.hpp>
#include <gmp/serialization/traits.hpp>

namespace gmp::detail {

template <typename T> consteval auto schema_fields() {
  if constexpr (requires { serialization_schema<T>::fields; })
    return serialization_schema<T>::fields;
  else
    return std::tuple{};
}

template <typename T, std::size_t I> struct automatic_field {
  static constexpr bool is_transient = false;
  static constexpr bool has_default = false;

  static constexpr std::string_view wire() {
    return member_name<I, T>();
  }

  static constexpr bool matches(std::string_view input) {
    return input == wire();
  }

  template <typename Other> static constexpr bool overlaps() {
    return Other::matches(wire());
  }

  static consteval bool names_unique() {
    return true;
  }

  template <typename M> static M make_default() = delete;
};

template <typename T, std::size_t I, std::size_t J = 0> consteval auto field_descriptor() {
  constexpr auto fields = schema_fields<T>();
  using tuple_type = decltype(fields);
  if constexpr (J == std::tuple_size_v<tuple_type>)
    return automatic_field<T, I>{};
  else {
    using D = std::tuple_element_t<J, tuple_type>;
    if constexpr (D::member.to_string_view() == member_name<I, T>())
      return D{};
    else
      return field_descriptor<T, I, J + 1>();
  }
}

template <typename T, std::size_t I> using field_descriptor_t = decltype(field_descriptor<T, I>());

template <typename D> constexpr std::string_view descriptor_wire() {
  if constexpr (requires { D::wire_name; })
    return D::wire_name.to_string_view();
  else
    return D::wire();
}

template <typename T> consteval bool schema_members_exist() {
  constexpr auto fields = schema_fields<T>();
  bool valid = true;
  std::apply(
      [&](auto... f) {
        ((valid = valid && has_member<T>(decltype(f)::member.to_string_view())), ...);
      },
      fields);
  return valid;
}

template <typename T> consteval bool schema_members_unique() {
  constexpr auto fields = schema_fields<T>();
  constexpr std::size_t N = std::tuple_size_v<decltype(fields)>;
  bool valid = true;
  [&]<std::size_t... I>(std::index_sequence<I...>) {
    auto one = [&]<std::size_t A>() {
      [&]<std::size_t... J>(std::index_sequence<J...>) {
        ((valid = valid &&
                  (std::tuple_element_t<A, decltype(fields)>::member.to_string_view() !=
                   std::tuple_element_t<A + 1 + J, decltype(fields)>::member.to_string_view())),
         ...);
      }
      (std::make_index_sequence<N - A - 1>{});
    };
    (one.template operator()<I>(), ...);
  }
  (std::make_index_sequence<N>{});
  return valid;
}

template <typename T> consteval bool schema_wire_names_unique() {
  constexpr std::size_t N = member_count_v<T>;
  bool valid = true;
  [&]<std::size_t... I>(std::index_sequence<I...>) {
    auto one = [&]<std::size_t A>() {
      using DA = field_descriptor_t<T, A>;
      [&]<std::size_t... J>(std::index_sequence<J...>) {
        ((valid = valid && !DA::template overlaps<field_descriptor_t<T, A + 1 + J>>()), ...);
      }
      (std::make_index_sequence<N - A - 1>{});
    };
    (one.template operator()<I>(), ...);
  }
  (std::make_index_sequence<N>{});
  return valid;
}

template <typename T> consteval bool schema_field_names_unique() {
  constexpr std::size_t N = member_count_v<T>;
  return []<std::size_t... I>(std::index_sequence<I...>) {
    return (field_descriptor_t<T, I>::names_unique() && ...);
  }
  (std::make_index_sequence<N>{});
}

template <typename T> consteval bool valid_schema() {
  return schema_members_exist<T>() && schema_members_unique<T>() && schema_wire_names_unique<T>() &&
         schema_field_names_unique<T>();
}

template <typename T> consteval std::size_t serialized_member_count() {
  constexpr std::size_t N = member_count_v<T>;
  return []<std::size_t... I>(std::index_sequence<I...>) {
    return (std::size_t{0} + ... + (field_descriptor_t<T, I>::is_transient ? 0u : 1u));
  }
  (std::make_index_sequence<N>{});
}

} // namespace gmp::detail

#endif // GMP_SERIALIZATION_DETAIL_SCHEMA_HPP_
