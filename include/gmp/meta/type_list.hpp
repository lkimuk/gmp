/**
 * \file type_list.h
 * \brief Definition of the type_list template structure.
 */
#ifndef GMP_TYPE_LIST_HPP_
#define GMP_TYPE_LIST_HPP_

#include <concepts>
#include <cstddef> // size_t
#include <utility> // index_sequence
#include <type_traits> // type_identify


namespace gmp
{

/**
 * \brief A variadic template structure representing a list of types.
 *
 * The type_list template can be used to hold a list of types at compile time.
 * It provides compile-time constants to retrieve the number of types and to check if the list is empty.
 *
 * \tparam Ts The types to be held in the type list.
 */
template<typename...> struct type_list {};


/// class type_list_size
template<typename> struct type_list_size;

template<typename... Types>
struct type_list_size<type_list<Types...>>
    : std::integral_constant<std::size_t, sizeof...(Types)> {};

template<typename T>
inline constexpr std::size_t type_list_size_v = type_list_size<T>::value;


/// class type_list_element
template<std::size_t Idx, typename T>
requires (Idx < type_list_size_v<T>)
struct type_list_element;

template<std::size_t Idx, typename Head, typename... Types>
struct type_list_element<Idx, type_list<Head, Types...>>
    : std::type_identity<typename type_list_element<Idx-1, type_list<Types...>>::type>
{};

template<typename Head, typename... Types>
struct type_list_element<0, type_list<Head, Types...>>
{
    using type = Head;
};

template<std::size_t Idx, typename T>
using type_list_element_t = type_list_element<Idx, T>::type;


/**
 * \brief Concept to check if a type is type_list-like.
 *
 * \tparam T The type to be checked.
 */
template<typename T>
concept type_list_like
    = !std::is_reference_v<T> && requires(T t) {
        typename type_list_size<T>::type;
        requires std::derived_from<
            type_list_size<T>,
            std::integral_constant<std::size_t, type_list_size_v<T>>
        >;
    } && []<std::size_t... Is>(std::index_sequence<Is...>) {
        return (requires(T) {
            typename type_list_element_t<Is, std::remove_const_t<T>>;
        } && ...);
    }(std::make_index_sequence<type_list_size_v<T>>{});


template<type_list_like T>
using type_list_head = type_list_element_t<0, T>;

template<type_list_like T>
using type_list_last = type_list_element_t<type_list_size_v<T> - 1, T>;


/// class type_list_tail
template<typename T>
requires type_list_like<T> && (type_list_size_v<T> > 0)
struct type_list_tail {};

template<typename Head, typename... Types>
struct type_list_tail<type_list<Head, Types...>>
    : std::type_identity<type_list<Types...>>
{};

template<typename T>
using type_list_tail_t = type_list_tail<T>::type;


/// class type_list_concat
template<type_list_like TypeList1, type_list_like TypeList2, type_list_like... RestTypeLists>
struct type_list_concat
    : std::type_identity<
        typename type_list_concat<
            typename type_list_concat<TypeList1, TypeList2>::type,
            RestTypeLists...
        >::type>
{};

template<typename... LTypes, typename... RTypes>
struct type_list_concat<type_list<LTypes...>, type_list<RTypes...>>
    : std::type_identity<type_list<LTypes..., RTypes...>>
{};

template<type_list_like... TypeLists>
using type_list_concat_t = type_list_concat<TypeLists...>::type;


/// class type_list_remove
template<std::size_t Idx, type_list_like T>
requires (Idx < type_list_size_v<T>)
struct type_list_remove;

template<std::size_t Idx, type_list_like T>
using type_list_remove_t = type_list_remove<Idx, T>::type;

template<type_list_like T>
using type_list_pop_front = type_list_remove_t<0, T>;

template<type_list_like T>
using type_list_pop_back = type_list_remove_t<type_list_size_v<T> - 1, T>;


/// contains
template<typename, type_list_like>
struct type_list_contains;

template<typename U, typename... Types>
struct type_list_contains<U, type_list<Types...>>
    : std::bool_constant<(std::same_as<Types, U> || ...)>
{};

template<typename U, type_list_like T>
inline constexpr bool type_list_contains_v = type_list_contains<U, T>::value;


/*!
 * \brief detail namespace with internal helper functions and types.
 *
 * This namespace collects functions, types, and utilities that are intended
 * for internal use only. It includes implementations of some template methods,
 * meta-programming helpers, and other internal details that should not be
 * exposed to users.
 */
namespace detail
{

/// remove impl
template<std::size_t, type_list_like, type_list_like>
struct type_list_remove_impl;

template<std::size_t Idx, typename Head, typename... Types, typename... Heads>
struct type_list_remove_impl<Idx, type_list<Head, Types...>, type_list<Heads...>>
    : std::type_identity<typename type_list_remove_impl<Idx-1, type_list<Types...>, type_list<Heads..., Head>>::type>
{};

template<typename Head, typename... Types, typename... Heads>
struct type_list_remove_impl<0, type_list<Head, Types...>, type_list<Heads...>>
    : std::type_identity<type_list_concat_t<type_list<Heads...>, type_list<Types...>>>
{};


/// insert impl
template<std::size_t, typename, type_list_like, type_list_like>
struct type_list_insert_impl;

template<std::size_t Idx, typename NewType, typename Head, typename... Heads, typename... Types>
requires (Idx > 0)
struct type_list_insert_impl<Idx, NewType, type_list<Heads...>, type_list<Head, Types...>>
    : std::type_identity<typename type_list_insert_impl<Idx-1, NewType, type_list<Heads..., Head>, type_list<Types...>>::type>
{};

template<typename NewType, typename... Heads, typename... Types>
struct type_list_insert_impl<0, NewType, type_list<Heads...>, type_list<Types...>>
    : std::type_identity<type_list<Heads..., NewType, Types...>>
{};


/// reverse impl
template<std::size_t, type_list_like, type_list_like>
struct type_list_reverse_impl;

template<std::size_t Idx, typename... NewTypes, typename... Types>
struct type_list_reverse_impl<Idx, type_list<NewTypes...>, type_list<Types...>>
    : std::type_identity<typename type_list_reverse_impl<Idx-1,
        type_list<NewTypes..., type_list_last<type_list<Types...>>>,
        type_list_pop_back<type_list<Types...>>>::type>
{};

template<typename... NewTypes>
struct type_list_reverse_impl<0, type_list<NewTypes...>, type_list<>>
    : std::type_identity<type_list<NewTypes...>>
{};


/// unique impl
template<std::size_t, type_list_like, type_list_like, typename, bool>
struct type_list_unique_impl;

template<std::size_t Idx, typename Head, typename CompType, typename... NewTypes, typename... Types>
struct type_list_unique_impl<Idx, type_list<NewTypes...>, type_list<Head, Types...>, CompType, true>
    : std::type_identity<typename type_list_unique_impl<Idx-1,
        type_list<NewTypes...>, type_list<Types...>, Head,
        type_list_contains_v<Head, type_list<NewTypes...>>>::type>
{};

template<std::size_t Idx, typename Head, typename CompType, typename... NewTypes, typename... Types>
struct type_list_unique_impl<Idx, type_list<NewTypes...>, type_list<Head, Types...>, CompType, false>
    : std::type_identity<typename type_list_unique_impl<Idx-1,
        type_list<NewTypes..., CompType>, type_list<Types...>, Head,
        type_list_contains_v<Head, type_list<NewTypes..., CompType>>>::type>
{};

template<typename CompType, typename... NewTypes, typename... Types>
struct type_list_unique_impl<0, type_list<NewTypes...>, type_list<Types...>, CompType, true>
    : std::type_identity<type_list<NewTypes..., Types...>>
{};

template<typename CompType, typename... NewTypes, typename... Types>
struct type_list_unique_impl<0, type_list<NewTypes...>, type_list<Types...>, CompType, false>
    : std::type_identity<type_list<NewTypes..., CompType, Types...>>
{};


/// filter impl
template<
    std::size_t,
    type_list_like,
    type_list_like,
    template<typename> class,
    typename, bool
>
struct type_list_filter_impl;

template<std::size_t Idx, template<typename> class Pred, typename Head, typename CompType, typename... Heads, typename... Types>
struct type_list_filter_impl<Idx, type_list<Heads...>, type_list<Head, Types...>, Pred, CompType, true>
    : std::type_identity<typename type_list_filter_impl<Idx-1,
        type_list<Heads..., CompType>, type_list<Types...>,
        Pred, Head, Pred<Head>::value>::type>
{};

template<std::size_t Idx, template<typename> class Pred, typename Head, typename CompType, typename... Heads, typename... Types>
struct type_list_filter_impl<Idx, type_list<Heads...>, type_list<Head, Types...>, Pred, CompType, false>
    : std::type_identity<typename type_list_filter_impl<Idx-1,
        type_list<Heads...>, type_list<Types...>,
        Pred, Head, Pred<Head>::value>::type>
{};

template<template<typename> class Pred, typename CompType, typename... Heads, typename... Types>
struct type_list_filter_impl<0, type_list<Heads...>, type_list<Types...>, Pred, CompType, true>
    : std::type_identity<type_list<Heads..., CompType, Types...>>
{};

template<template<typename> class Pred, typename CompType, typename... Heads, typename... Types>
struct type_list_filter_impl<0, type_list<Heads...>, type_list<Types...>, Pred, CompType, false>
    : std::type_identity<type_list<Heads..., Types...>>
{};

} // namespace detail



/// class type_list_remove
template<std::size_t Idx, typename Head, typename... Types>
struct type_list_remove<Idx, type_list<Head, Types...>>
    : std::type_identity<typename detail::type_list_remove_impl<Idx-1, type_list<Types...>, type_list<Head>>::type>
{};

template<typename Head, typename... Types>
struct type_list_remove<0, type_list<Head, Types...>>
    : std::type_identity<type_list<Types...>>
{};


/// insert
template<std::size_t Idx, typename, type_list_like T>
requires (Idx <= type_list_size_v<T>)
struct type_list_insert;

template<std::size_t Idx, typename NewType, typename Head, typename... Types>
requires (Idx > 0)
struct type_list_insert<Idx, NewType, type_list<Head, Types...>>
    : std::type_identity<typename detail::type_list_insert_impl<Idx-1, NewType, type_list<Head>, type_list<Types...>>::type>
{};

template<typename NewType, typename... Types>
struct type_list_insert<0, NewType, type_list<Types...>>
    : std::type_identity<type_list<NewType, Types...>>
{};

template<std::size_t Idx, typename NewType, type_list_like T>
using type_list_insert_t = type_list_insert<Idx, NewType, T>::type;

template<typename NewType, type_list_like T>
using type_list_push_front = type_list_insert_t<0, NewType, T>;

template<typename NewType, type_list_like T>
using type_list_push_back = type_list_insert_t<type_list_size_v<T>, NewType, T>;


/// filter
template<typename T, typename>
struct filter {};


/// reverse
template<type_list_like> struct type_list_reverse;

template<typename... Types>
struct type_list_reverse<type_list<Types...>>
    : std::type_identity<typename detail::type_list_reverse_impl<
            type_list_size_v<type_list<Types...>> - 1,
            type_list<type_list_last<type_list<Types...>>>,
            type_list_pop_back<type_list<Types...>>>::type>
{};

template<>
struct type_list_reverse<type_list<>>
    : std::type_identity<type_list<>>
{};

template<type_list_like T>
using type_list_reverse_t = type_list_reverse<T>::type;


/// unique
template<type_list_like> struct type_list_unique;

template<typename Head, typename... Types>
struct type_list_unique<type_list<Head, Types...>>
    : std::type_identity<typename detail::type_list_unique_impl<
        type_list_size_v<type_list<Head, Types...>> - 1,
        type_list<>, type_list<Types...>, Head, false>::type>
{};

template<>
struct type_list_unique<type_list<>>
    : std::type_identity<type_list<>>
{};

template<typename T>
using type_list_unique_t = type_list_unique<T>::type;


/// filter
template<type_list_like, template<typename> class Pred>
requires std::same_as<std::remove_const_t<decltype(Pred<void>::value)>, bool>
struct type_list_filter;

template<template<typename> class Pred, typename Head, typename... Types>
struct type_list_filter<type_list<Head, Types...>, Pred>
    : std::type_identity<typename detail::type_list_filter_impl<
        type_list_size_v<type_list<Head, Types...>> - 1,
        type_list<>, type_list<Types...>, Pred, Head,
        Pred<Head>::value>::type>
{};

template<template<typename> class Pred>
struct type_list_filter<type_list<>, Pred>
    : std::type_identity<type_list<>>
{};

template<type_list_like T, template<typename> class Pred>
using type_list_filter_t = type_list_filter<T, Pred>::type;


} // namespace gmp

#endif // GMP_TYPE_LIST_HPP_