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

#ifndef GMP_HPP_
#define GMP_HPP_

/**
 * @defgroup macro_metaprogramming Macro Metaprogramming
 * @brief Preprocessor-based code-generation utilities, tuple helpers, and platform/compiler macros.
 */

/**
 * @defgroup reflection_metaprogramming Reflection Metaprogramming
 * @brief Compile-time enum and aggregate reflection utilities.
 */

/**
 * @defgroup compile_time_string_utilities Compile-Time String Utilities
 * @brief Fixed-string and string-oriented helpers for compile-time programming.
 */

/**
 * @defgroup type_utilities Type Utilities
 * @brief Type-level containers, naming helpers, and compile-time utility primitives.
 */

/**
 * @defgroup named_operators Named Operators
 * @brief Facilities for building custom infix syntax from callable objects.
 */

/**
 * @defgroup design_patterns Design Patterns
 * @brief Reusable singleton, factory, and locking helpers.
 */

#include <gmp/macro/macro.hpp>
#include <gmp/meta/string.hpp>
#include <gmp/meta/meta.hpp>
#include <gmp/dp/singleton.hpp>
#include <gmp/dp/object_factory.hpp>
#include <gmp/meta/type_size.hpp>
#include <gmp/meta/named_operator.hpp>

#endif // GMP_HPP_
