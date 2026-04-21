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

#ifndef GMP_META_NAMED_OPERATOR_HPP_
#define GMP_META_NAMED_OPERATOR_HPP_

#include <concepts>
#include <functional>
#include <type_traits>
#include <tuple>
#include <utility>

#include <gmp/macro/macro.hpp>

namespace gmp {

namespace detail {

/**
 * @brief Store the operands captured while evaluating a named-operator expression.
 *
 * This holder is used internally in two stages:
 * first it stores the callable returned by make_named_operator(), then it stores
 * the bound left operand together with that callable until the right operand is
 * supplied.
 *
 * @tparam Ts The stored value or reference types.
 */
template<typename... Ts>
struct value_holder {
    std::tuple<Ts...> values;

    template<typename... Us>
        requires std::constructible_from<std::tuple<Ts...>, Us&&...>
    constexpr explicit value_holder(Us&&... us)
        : values(std::forward<Us>(us)...) {}
};

/**
 * @brief Select the storage type for the left operand of a named operator.
 *
 * Lvalues are stored as references so callables can observe and mutate the
 * original object. Rvalues are stored by value so temporaries remain alive until
 * the final operator invocation.
 *
 * @tparam T The deduced left operand type.
 */
template<typename T>
using named_operator_lhs_storage_t = std::conditional_t<
    std::is_lvalue_reference_v<T>, T, std::remove_cvref_t<T>>;

/**
 * @brief Bind the left operand to a named-operator token.
 *
 * This function implements the first half of an expression such as
 * `lhs ^op`, preserving lvalue/rvalue semantics for the left operand and moving
 * the stored callable into the intermediate holder.
 *
 * @tparam Lhs The deduced left operand type.
 * @tparam Func The stored callable type.
 * @param lhs The left operand.
 * @param holder The named-operator token created by make_named_operator().
 * @return A holder containing the bound left operand and callable.
 */
template<typename Lhs, typename Func>
[[nodiscard]]
constexpr auto bind_named_operator(Lhs&& lhs, value_holder<Func> holder) {
    using lhs_storage_t = named_operator_lhs_storage_t<Lhs&&>;

    return value_holder<lhs_storage_t, Func>(
        std::forward<Lhs>(lhs),
        std::get<0>(std::move(holder.values))
    );
}

/**
 * @brief Invoke a fully bound named-operator expression.
 *
 * This function implements the second half of an expression such as
 * `(lhs ^op) ^ rhs`. The callable is consumed, the stored left operand is
 * forwarded according to its storage type, and the right operand is forwarded
 * directly from the final operator expression.
 *
 * @tparam Lhs The stored left operand type.
 * @tparam Func The stored callable type.
 * @tparam Rhs The deduced right operand type.
 * @param holder The intermediate holder produced by bind_named_operator().
 * @param rhs The right operand.
 * @return The result of invoking the stored callable.
 */
template<typename Lhs, typename Func, typename Rhs>
    requires std::invocable<Func&&, Lhs, Rhs&&>
constexpr decltype(auto) invoke_named_operator(value_holder<Lhs, Func>&& holder, Rhs&& rhs) {
    auto&& [lhs, func] = holder.values;
    return std::invoke(std::move(func), std::forward<Lhs>(lhs), std::forward<Rhs>(rhs));
}

#define GMP_DEFINE_NAMED_OPERATOR_PAIR(pair)                                       \
    template<typename Lhs, typename Func>                                           \
        requires std::movable<Func>                                                 \
    constexpr auto operator GMP_GET_TUPLE(0, pair) (Lhs&& lhs, ::gmp::detail::value_holder<Func> holder) { \
        return ::gmp::detail::bind_named_operator(std::forward<Lhs>(lhs), std::move(holder)); \
    }                                                                               \
                                                                                    \
    template<typename Lhs, typename Func, typename Rhs>                             \
        requires std::invocable<Func&&, Lhs, Rhs&&>                                 \
    constexpr decltype(auto) operator GMP_GET_TUPLE(1, pair) (                                         \
        ::gmp::detail::value_holder<Lhs, Func>&& holder, Rhs&& rhs) {               \
        return ::gmp::detail::invoke_named_operator(std::move(holder), std::forward<Rhs>(rhs)); \
    }

#define GMP_TO_PAIR(x) (x, x),
#define GMP_TO_PAIRS(...) GMP_REMOVE_TRAILING_COMMA(GMP_FOR_EACH(GMP_TO_PAIR, __VA_ARGS__))

#define GMP_GENERATE_NAMED_OPERATOR_PAIRS(...) \
    GMP_FOR_EACH(GMP_DEFINE_NAMED_OPERATOR_PAIR, __VA_ARGS__)
#define GMP_GENERATE_NAMED_OPERATOR_IDENTICAL_PAIRS(...) \
    _GMP_GENERATE_NAMED_OPERATOR_IDENTICAL_PAIRS_MSVC_COMPAT(GMP_TO_PAIRS(__VA_ARGS__))
#define _GMP_GENERATE_NAMED_OPERATOR_IDENTICAL_PAIRS_MSVC_COMPAT(...) \
    GMP_FOR_EACH(GMP_DEFINE_NAMED_OPERATOR_PAIR, __VA_ARGS__)

#ifndef GMP_DISABLE_DEFAULT_NAMED_OPERATORS
GMP_GENERATE_NAMED_OPERATOR_PAIRS((<, >))
GMP_GENERATE_NAMED_OPERATOR_IDENTICAL_PAIRS(+, ^, *, -, /, %, &, |)
#endif

#undef _GMP_GENERATE_NAMED_OPERATOR_IDENTICAL_PAIRS_MSVC_COMPAT
#undef GMP_GENERATE_NAMED_OPERATOR_IDENTICAL_PAIRS
#undef GMP_GENERATE_NAMED_OPERATOR_PAIRS
#undef GMP_TO_PAIRS
#undef GMP_TO_PAIR
#undef GMP_DEFINE_NAMED_OPERATOR_PAIR

} // namespace detail

/** @addtogroup named_operators
 * @{
 */

/**
 * @brief Create a token that lets a callable be used as a named infix operator.
 *
 * The returned token can be placed between two matching operator symbols to
 * call the stored callable with the left and right operands. Default generated
 * forms include `lhs ^op^ rhs`, `lhs <op> rhs`, and matching
 * pairs for `+`, `*`, `-`, `/`, `%`, `&`, and `|`.
 *
 * The callable is stored by value. The left operand is stored as a reference
 * when it is an lvalue and by value when it is an rvalue. The right operand is
 * forwarded directly at the final invocation.
 *
 * @tparam Func The callable type.
 * @param f The callable object used by the named operator.
 * @return An internal token object that participates in named-operator syntax.
 *
 * @example
 * @code
 * auto plus = gmp::make_named_operator([](int x, int y) {
 *     return x + y;
 * });
 *
 * int a = 10;
 * int b = 3;
 * auto r1 = a ^plus^ b; // 13
 * auto r2 = a <plus> b; // 13
 *
 * auto add_assign = gmp::make_named_operator([](int& x, int y) -> int& {
 *     x += y;
 *     return x;
 * });
 *
 * // add_assign can mutate the original lvalue.
 * int x = 1;
 * x ^add_assign^ 2; // x == 3
 * @endcode
 */
template<typename Func>
[[nodiscard]]
constexpr auto make_named_operator(Func&& f) {
    using func_type = std::remove_cvref_t<Func>;

    return detail::value_holder<func_type>(std::forward<Func>(f));
}

/** @} */

} // namespace gmp

#endif // GMP_META_NAMED_OPERATOR_HPP_
