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

#ifndef GMP_DETAIL_MEMBER_REF_HPP_
#define GMP_DETAIL_MEMBER_REF_HPP_

#include <tuple>

#include <gmp/macro/macro.hpp>
#include <gmp/meta/utility.hpp>

namespace gmp::detail {

#define GMP_GET_MEMBER_REF_DEFINE(N) \
  template<std::size_t I, typename T> \
  decltype(auto) member_ref(T&& value, constant_arg_t<N>) { \
    auto&& [GMP_GET_FIRST_N(N, GMP_IDENTIFIERS)] = value; \
    return std::get<I>(std::forward_as_tuple(GMP_GET_FIRST_N(N, GMP_IDENTIFIERS))); \
  }

#if GMP_STANDARD_PREPROCESSOR
    // Standard preprocessor supports 256 arguments
    GMP_FOR_EACH(GMP_GET_MEMBER_REF_DEFINE, GMP_RANGE(1, 256))
#else
    // MSVC traditional preprocessor: MAX 199 due to nesting depth limit (fatal error C1009)
    GMP_FOR_EACH(GMP_GET_MEMBER_REF_DEFINE, GMP_RANGE(1, 119))
#endif

#undef GMP_GET_MEMBER_REF_DEFINE

} // namespace gmp::detail

#endif // GMP_DETAIL_MEMBER_REF_HPP_