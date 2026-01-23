//   ___ __  __ ___ 
//  / __|  \/  | _ \ GMP(Generative Metaprogramming)
// | (_ | |\/| |  _/ version 0.1.0
//  \___|_|  |_|_|   https://github.com/lkimuk/gmp
//
// SPDX-FileCopyrightText: 2023-2026 Gaoxing Li <https://www.cppmore.com/>
// SPDX-License-Identifier: MIT
//
// This file is part of the GMP (Generative Metaprogramming) library.
// Full project source: https://github.com/lkimuk/gmp

#ifndef GMP_STRING_HPP_
#define GMP_STRING_HPP_

namespace gmp {

constexpr bool is_equal(const char* lhs, const char* rhs) noexcept {
    return *lhs == *rhs && (!*lhs || is_equal(lhs + 1, rhs + 1));
}

} // namespace gmp

#endif // GMP_STRING_HPP_