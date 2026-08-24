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

#ifndef GMP_META_CONFIG_HPP_
#define GMP_META_CONFIG_HPP_

#include <gmp/macro/platform.hpp>

#if GMP_STANDARD_PREPROCESSOR
    // Standard preprocessor supports 256 arguments
    #define GMP_DETAIL_PLATFORM_MAX_FIELDS 255
#else
    // MSVC traditional preprocessor: MAX 199 due to nesting depth limit (fatal error C1009)
    #define GMP_DETAIL_PLATFORM_MAX_FIELDS 118
#endif

#ifndef GMP_MAX_SUPPORTED_FIELDS
    #define GMP_MAX_SUPPORTED_FIELDS GMP_DETAIL_PLATFORM_MAX_FIELDS
#endif

#if GMP_MAX_SUPPORTED_FIELDS < 1
    #error "GMP_MAX_SUPPORTED_FIELDS must be at least 1."
#endif

#if GMP_MAX_SUPPORTED_FIELDS > GMP_DETAIL_PLATFORM_MAX_FIELDS
    #error "GMP_MAX_SUPPORTED_FIELDS exceeds the maximum supported by the platform."
#endif

#endif // GMP_META_CONFIG_HPP_