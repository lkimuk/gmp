// SPDX-License-Identifier: MIT
#ifndef GMP_SERIALIZATION_DETAIL_STD_TYPES_HPP_
#define GMP_SERIALIZATION_DETAIL_STD_TYPES_HPP_
#include <array>
#include <concepts>
#include <deque>
#include <list>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>
namespace gmp::detail {
template <typename T>
using unqualified_t = std::remove_cv_t<std::remove_reference_t<T>>;
template <typename T> inline constexpr bool always_false_v = false;
template <typename T> struct optional_traits : std::false_type {};
template <typename T>
struct optional_traits<std::optional<T>> : std::true_type {
  using value_type = T;
};
template <typename T>
inline constexpr bool is_optional_v = optional_traits<unqualified_t<T>>::value;
template <typename T> struct sequence_traits : std::false_type {};
template <typename T, typename A>
struct sequence_traits<std::vector<T, A>> : std::true_type {
  using value_type = T;
};
template <typename T, typename A>
struct sequence_traits<std::deque<T, A>> : std::true_type {
  using value_type = T;
};
template <typename T, typename A>
struct sequence_traits<std::list<T, A>> : std::true_type {
  using value_type = T;
};
template <typename T>
inline constexpr bool is_sequence_v = sequence_traits<unqualified_t<T>>::value;
template <typename T> struct set_traits : std::false_type {};
template <typename K, typename C, typename A>
struct set_traits<std::set<K, C, A>> : std::true_type {
  using value_type = K;
};
template <typename K, typename H, typename E, typename A>
struct set_traits<std::unordered_set<K, H, E, A>> : std::true_type {
  using value_type = K;
};
template <typename T>
inline constexpr bool is_set_v = set_traits<unqualified_t<T>>::value;
template <typename T> struct array_traits : std::false_type {};
template <typename T, std::size_t N>
struct array_traits<std::array<T, N>> : std::true_type {
  using value_type = T;
};
template <typename T>
inline constexpr bool is_array_v = array_traits<unqualified_t<T>>::value;
template <typename T> struct map_traits : std::false_type {};
template <typename K, typename V, typename C, typename A>
struct map_traits<std::map<K, V, C, A>> : std::true_type {
  using key_type = K;
  using mapped_type = V;
};
template <typename K, typename V, typename H, typename E, typename A>
struct map_traits<std::unordered_map<K, V, H, E, A>> : std::true_type {
  using key_type = K;
  using mapped_type = V;
};
template <typename T>
inline constexpr bool is_map_v = map_traits<unqualified_t<T>>::value;
template <typename T> struct is_pair : std::false_type {};
template <typename A, typename B>
struct is_pair<std::pair<A, B>> : std::true_type {};
template <typename T>
inline constexpr bool is_pair_v = is_pair<unqualified_t<T>>::value;
template <typename T, typename = void>
struct is_tuple_like : std::false_type {};
template <typename T>
struct is_tuple_like<
    T, std::void_t<decltype(std::tuple_size<unqualified_t<T>>::value)>>
    : std::true_type {};
template <typename T>
inline constexpr bool is_tuple_like_v =
    is_tuple_like<T>::value && !is_pair_v<T> && !is_array_v<T>;
template <typename T> struct is_variant : std::false_type {};
template <typename... T>
struct is_variant<std::variant<T...>> : std::true_type {};
template <typename T>
inline constexpr bool is_variant_v = is_variant<unqualified_t<T>>::value;
template <typename T>
inline constexpr bool is_char_array_v =
    std::is_array_v<std::remove_reference_t<T>> &&
    std::same_as<
        std::remove_const_t<std::remove_extent_t<std::remove_reference_t<T>>>,
        char>;
template <typename T>
inline constexpr bool is_string_key_v =
    std::same_as<unqualified_t<T>, std::string>;
} // namespace gmp::detail
#endif
