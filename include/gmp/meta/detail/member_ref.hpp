//   ___ __  __ ___ 
//  / __|  \/  | _ \ GMP(Generative Metaprogramming)
// | (_ | |\/| |  _/ version 0.2.0
//  \___|_|  |_|_|   https://github.com/lkimuk/gmp
//
// SPDX-FileCopyrightText: 2023-2026 Miles Li <https://www.cppmore.com/>
// SPDX-License-Identifier: MIT
//
// This file is part of the GMP (Generative Metaprogramming) library.
// Full project source: https://github.com/lkimuk/gmp

#ifndef GMP_DETAIL_MEMBER_REF_HPP_
#define GMP_DETAIL_MEMBER_REF_HPP_

#include <tuple>
#include <type_traits>
#include <utility>

#include <gmp/macro/macro.hpp>
#include <gmp/meta/config.hpp>
#include <gmp/meta/utility.hpp>

namespace gmp::detail {

#define GMP_GET_MEMBER_REF_DEFINE(N) \
  template<std::size_t I, typename T> \
  decltype(auto) member_ref(T&& value, constant_arg_t<N>) noexcept { \
    auto&& [GMP_GET_FIRST_N(N, GMP_IDENTIFIERS)] = std::forward<T>(value); \
    auto members = std::forward_as_tuple(GMP_GET_FIRST_N(N, GMP_IDENTIFIERS)); \
    if constexpr (std::is_lvalue_reference_v<T&&>) { \
      return std::get<I>(members); \
    } else { \
      return std::move(std::get<I>(members)); \
    } \
  }


GMP_FOR_EACH(GMP_GET_MEMBER_REF_DEFINE, GMP_RANGE(1, GMP_INC(GMP_MAX_SUPPORTED_FIELDS)))

#undef GMP_GET_MEMBER_REF_DEFINE

} // namespace gmp::detail

#endif // GMP_DETAIL_MEMBER_REF_HPP_
