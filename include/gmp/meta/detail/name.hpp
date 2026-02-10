#ifndef GMP_DETAIL_NAME_HPP_
#define GMP_DETAIL_NAME_HPP_

#include <string_view>
#include <tuple>

#include "macro/macro.hpp"
#include "meta/utility.hpp"

#define GMP_MAX_SUPPORTED_FIELDS 100

namespace gmp::detail {

template<auto V>
consteval auto value_name_of() {
    return std::string_view(std::source_location::current().function_name());
}

template<typename T>
consteval auto type_name_of() {
    using namespace std::string_view_literals;
#if GMP_COMPILER_CLANG
    constexpr auto prefix = "[T = "sv;
    constexpr auto suffix = "]"sv;
#elif GMP_COMPILER_GCC
    constexpr auto prefix = "with T = "sv;
    constexpr auto suffix = "]"sv;
#elif GMP_COMPILER_MSVC
    constexpr auto prefix = "gmp::detail::type_name_of<"sv;
    constexpr auto suffix = ">"sv;
#else
    return "Unknown type name"sv;
#endif

    const auto name = std::string_view(std::source_location::current().function_name());
    const auto start = name.find(prefix) + prefix.size();
    const auto end = name.find_last_of(suffix);
    return name.substr(start, end - start);
}

template<auto V>
consteval auto member_name_of() {
    using namespace std::string_view_literals;
#if GMP_COMPILER_CLANG
    constexpr auto prefix = "[T = "sv;
    constexpr auto suffix = "]"sv;
#elif GMP_COMPILER_GCC
    constexpr auto prefix = "with T = "sv;
    constexpr auto suffix = "]"sv;
#elif GMP_COMPILER_MSVC
    constexpr auto prefix = "long_lifetime_obj->value->"sv;
    constexpr auto suffix = ">"sv;
#else
    return "Unknown type name"sv;
#endif
    const auto name = std::string_view(std::source_location::current().function_name());
    // return name;
    const auto start = name.find(prefix) + prefix.size();
    const auto end = name.find_last_of(suffix);
    return name.substr(start, end - start);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<1>) {
    const auto& [_0] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<2>) {
    const auto& [_0, _1] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<3>) {
    const auto& [_0, _1, _2] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<4>) {
    const auto& [_0, _1, _2, _3] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<5>) {
    const auto& [_0, _1, _2, _3, _4] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<6>) {
    const auto& [_0, _1, _2, _3, _4, _5] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<7>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<8>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<9>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<10>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<11>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<12>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<13>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<14>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<15>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<16>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<17>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<18>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<19>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<20>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<21>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<22>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<23>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<24>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<25>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<26>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<27>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<28>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<29>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<30>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<31>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<32>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<33>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<34>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<35>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<36>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<37>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<38>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<39>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<40>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<41>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<42>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<43>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<44>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<45>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<46>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<47>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<48>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<49>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<50>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<51>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<52>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<53>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<54>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<55>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<56>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<57>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<58>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<59>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<60>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<61>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<62>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<63>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<64>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<65>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<66>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<67>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<68>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<69>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<70>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<71>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<72>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<73>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<74>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72, &_73);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<75>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72, &_73, &_74);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<76>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72, &_73, &_74, &_75);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<77>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72, &_73, &_74, &_75, &_76);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<78>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72, &_73, &_74, &_75, &_76, &_77);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<79>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72, &_73, &_74, &_75, &_76, &_77, &_78);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<80>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72, &_73, &_74, &_75, &_76, &_77, &_78, &_79);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<81>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72, &_73, &_74, &_75, &_76, &_77, &_78, &_79, &_80);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<82>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72, &_73, &_74, &_75, &_76, &_77, &_78, &_79, &_80, &_81);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<83>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72, &_73, &_74, &_75, &_76, &_77, &_78, &_79, &_80, &_81, &_82);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<84>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72, &_73, &_74, &_75, &_76, &_77, &_78, &_79, &_80, &_81, &_82, &_83);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<85>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72, &_73, &_74, &_75, &_76, &_77, &_78, &_79, &_80, &_81, &_82, &_83, &_84);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<86>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72, &_73, &_74, &_75, &_76, &_77, &_78, &_79, &_80, &_81, &_82, &_83, &_84, &_85);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<87>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72, &_73, &_74, &_75, &_76, &_77, &_78, &_79, &_80, &_81, &_82, &_83, &_84, &_85, &_86);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<88>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72, &_73, &_74, &_75, &_76, &_77, &_78, &_79, &_80, &_81, &_82, &_83, &_84, &_85, &_86, &_87);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<89>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72, &_73, &_74, &_75, &_76, &_77, &_78, &_79, &_80, &_81, &_82, &_83, &_84, &_85, &_86, &_87, &_88);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<90>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72, &_73, &_74, &_75, &_76, &_77, &_78, &_79, &_80, &_81, &_82, &_83, &_84, &_85, &_86, &_87, &_88, &_89);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<91>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72, &_73, &_74, &_75, &_76, &_77, &_78, &_79, &_80, &_81, &_82, &_83, &_84, &_85, &_86, &_87, &_88, &_89, &_90);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<92>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72, &_73, &_74, &_75, &_76, &_77, &_78, &_79, &_80, &_81, &_82, &_83, &_84, &_85, &_86, &_87, &_88, &_89, &_90, &_91);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<93>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, _92] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72, &_73, &_74, &_75, &_76, &_77, &_78, &_79, &_80, &_81, &_82, &_83, &_84, &_85, &_86, &_87, &_88, &_89, &_90, &_91, &_92);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<94>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, _92, _93] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72, &_73, &_74, &_75, &_76, &_77, &_78, &_79, &_80, &_81, &_82, &_83, &_84, &_85, &_86, &_87, &_88, &_89, &_90, &_91, &_92, &_93);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<95>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, _92, _93, _94] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72, &_73, &_74, &_75, &_76, &_77, &_78, &_79, &_80, &_81, &_82, &_83, &_84, &_85, &_86, &_87, &_88, &_89, &_90, &_91, &_92, &_93, &_94);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<96>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, _92, _93, _94, _95] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72, &_73, &_74, &_75, &_76, &_77, &_78, &_79, &_80, &_81, &_82, &_83, &_84, &_85, &_86, &_87, &_88, &_89, &_90, &_91, &_92, &_93, &_94, &_95);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<97>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, _92, _93, _94, _95, _96] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72, &_73, &_74, &_75, &_76, &_77, &_78, &_79, &_80, &_81, &_82, &_83, &_84, &_85, &_86, &_87, &_88, &_89, &_90, &_91, &_92, &_93, &_94, &_95, &_96);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<98>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, _92, _93, _94, _95, _96, _97] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72, &_73, &_74, &_75, &_76, &_77, &_78, &_79, &_80, &_81, &_82, &_83, &_84, &_85, &_86, &_87, &_88, &_89, &_90, &_91, &_92, &_93, &_94, &_95, &_96, &_97);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<99>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, _92, _93, _94, _95, _96, _97, _98] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72, &_73, &_74, &_75, &_76, &_77, &_78, &_79, &_80, &_81, &_82, &_83, &_84, &_85, &_86, &_87, &_88, &_89, &_90, &_91, &_92, &_93, &_94, &_95, &_96, &_97, &_98);
    return std::get<I>(tup);
}

template<std::size_t I, typename T>
consteval auto field_getter(constant_arg_t<100>) {
    const auto& [_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, _92, _93, _94, _95, _96, _97, _98, _99] = as_value<std::remove_cv_t<T>>();
    const auto& tup = std::forward_as_tuple(&_0, &_1, &_2, &_3, &_4, &_5, &_6, &_7, &_8, &_9, &_10, &_11, &_12, &_13, &_14, &_15, &_16, &_17, &_18, &_19, &_20, &_21, &_22, &_23, &_24, &_25, &_26, &_27, &_28, &_29, &_30, &_31, &_32, &_33, &_34, &_35, &_36, &_37, &_38, &_39, &_40, &_41, &_42, &_43, &_44, &_45, &_46, &_47, &_48, &_49, &_50, &_51, &_52, &_53, &_54, &_55, &_56, &_57, &_58, &_59, &_60, &_61, &_62, &_63, &_64, &_65, &_66, &_67, &_68, &_69, &_70, &_71, &_72, &_73, &_74, &_75, &_76, &_77, &_78, &_79, &_80, &_81, &_82, &_83, &_84, &_85, &_86, &_87, &_88, &_89, &_90, &_91, &_92, &_93, &_94, &_95, &_96, &_97, &_98, &_99);
    return std::get<I>(tup);
}

} // namespace gmp::detail

#endif // GMP_DETAIL_NAME_HPP_