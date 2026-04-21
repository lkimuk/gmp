//   ___ __  __ ___ 
//  / __|  \/  | _ \ GMP(Generative Metaprogramming)
// | (_ | |\/| |  _/ version 0.3.0
//  \___|_|  |_|_|   https://github.com/lkimuk/gmp
//
// SPDX-FileCopyrightText: 2020-2026 Gaoxing Li <https://www.cppmore.com/>
// SPDX-License-Identifier: MIT
//
// This file is part of the GMP (Generative Metaprogramming) library.
// Full project source: https://github.com/lkimuk/gmp
//
// This object factory implementation was originally written by the same author
// for the okdp library in 2020 and later adapted for GMP:
// https://github.com/lkimuk/okdp

#ifndef GMP_DP_OBJECT_FACTORY_HPP_
#define GMP_DP_OBJECT_FACTORY_HPP_

#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

#include <gmp/dp/singleton.hpp>
#include <gmp/macro/macro.hpp>

#if GMP_CPP_AT_LEAST(20)
#include <concepts>
#endif // C++20 or later

namespace gmp {

/** @addtogroup design_patterns
 * @{
 */

/**
 * @brief A singleton-backed runtime factory that creates products by string key.
 *
 * `object_factory` stores a mapping from textual identifiers to constructor
 * callbacks for concrete types derived from `AbstractProduct`. Product types are
 * typically registered through `register_type` or the
 * `GMP_FACTORY_REGISTER(...)` helper macro, and can later be instantiated by
 * calling `create`, `create_shared`, or `create_unique`.
 *
 * The factory itself is a singleton so registrations and lookups operate on a
 * single process-wide registry for a given `<AbstractProduct, ConstructorArgs...>`
 * specialization.
 *
 * @tparam AbstractProduct The abstract base type returned by the factory.
 * @tparam ConstructorArgs The constructor argument types forwarded to concrete products.
 *
 * @since version 1.0.0
 */
template <typename AbstractProduct, typename... ConstructorArgs>
class object_factory : public singleton<object_factory<AbstractProduct, ConstructorArgs...>> {
  using this_type = object_factory<AbstractProduct, ConstructorArgs...>;

public:
  /**
   * @brief Register a concrete product type under a string key.
   *
   * Constructing an instance of this helper inserts a constructor callback into
   * the owning factory specialization. The callback creates `T` with the
   * `ConstructorArgs...` supplied later at lookup time.
   *
   * @tparam T The concrete product type to register.
   */
  template <typename T>
#if GMP_CPP_AT_LEAST(20)
    requires std::derived_from<T, AbstractProduct>
#endif
  struct register_type {
    // Registers T into object factory
    /**
     * @brief Register `T` with the specified lookup key.
     *
     * @param key The textual identifier used to create objects of type `T`.
     */
    register_type(const std::string& key) {
      this_type::instance().map_.emplace(key,
        [](const ConstructorArgs&... args) { return new T(args...); });
    }
  };

  /**
   * @brief Remove a previously registered product key from the factory.
   *
   * Removing a key only affects future lookups. It does not modify or destroy
   * any objects that were already created.
   *
   * @param key The registered lookup key to erase.
   */
  void unregister_type(const std::string& key) {
    this_type::instance().map_.erase(key);
  }

  /**
   * @brief Create a concrete product with raw `new` semantics.
   *
   * This function looks up `key`, invokes the registered constructor callback,
   * and returns the resulting object as a raw pointer.
   *
   * @param key The registered lookup key of the desired concrete type.
   * @param args The constructor arguments forwarded to the concrete product.
   * @return A raw pointer to the newly created product.
   *
   * @throws std::invalid_argument If `key` is not registered.
   *
   * @warning The caller owns the returned pointer and must delete it to avoid
   * memory leaks. Prefer `create_shared()` or `create_unique()` when ownership
   * should be explicit.
   */
  AbstractProduct* create(const std::string& key, const ConstructorArgs&... args) {
    if (this_type::instance().map_.find(key) == this_type::instance().map_.end())
      throw std::invalid_argument("Unknown object type passed to factory!");
    return this_type::instance().map_[key](args...);
  }

  /**
   * @brief Create a concrete product and return it as `std::shared_ptr`.
   *
   * @param key The registered lookup key of the desired concrete type.
   * @param args The constructor arguments forwarded to the concrete product.
   * @return A shared pointer owning the newly created product.
   *
   * @throws std::invalid_argument If `key` is not registered.
   */
  std::shared_ptr<AbstractProduct> create_shared(
    const std::string& key, const ConstructorArgs&... args) {
    return std::shared_ptr<AbstractProduct>(create(key, args...));
  }

  /**
   * @brief Create a concrete product and return it as `std::unique_ptr`.
   *
   * @param key The registered lookup key of the desired concrete type.
   * @param args The constructor arguments forwarded to the concrete product.
   * @return A unique pointer owning the newly created product.
   *
   * @throws std::invalid_argument If `key` is not registered.
   */
  std::unique_ptr<AbstractProduct> create_unique(
    const std::string& key, const ConstructorArgs&... args) {
    return std::unique_ptr<AbstractProduct>(create(key, args...));
  }

private:
  std::map<std::string, std::function<AbstractProduct*(const ConstructorArgs&... args)>> map_;
};

#define _GMP_GET_CONCRETE_PRODUCT_CLASS(ConcreteProduct) GMP_IF_THEN_ELSE(GMP_IS_TUPLE(ConcreteProduct), GMP_GET_TUPLE, ConcreteProduct)GMP_IF(GMP_IS_TUPLE(ConcreteProduct), (1, ConcreteProduct))
#define _GMP_GET_CONSTRUCTOR_TYPES(ConstructorArgs) GMP_IF_THEN_ELSE(GMP_IS_TUPLE(ConstructorArgs), GMP_REMOVE_PARENS, ConstructorArgs)GMP_IF(GMP_IS_TUPLE(ConstructorArgs), (ConstructorArgs))
#define GMP_FACTORY_REGISTER_WITH_ARGS(AbstractProduct, ConstructorArgs, ConcreteProduct) \
  static gmp::object_factory<AbstractProduct, _GMP_GET_CONSTRUCTOR_TYPES(ConstructorArgs)>::register_type<_GMP_GET_CONCRETE_PRODUCT_CLASS(ConcreteProduct)> \
        GMP_CONCATS(gmp_reg_, AbstractProduct, _, _GMP_GET_CONCRETE_PRODUCT_CLASS(ConcreteProduct))(GMP_IF_THEN_ELSE(GMP_IS_TUPLE(ConcreteProduct), GMP_STRINGIFY(GMP_GET_TUPLE(0, ConcreteProduct)), GMP_STRINGIFY(ConcreteProduct)));
#define GMP_FACTORY_REGISTER_NO_ARGS(AbstractProduct, ConcreteProduct) \
    static gmp::object_factory<AbstractProduct>::register_type<_GMP_GET_CONCRETE_PRODUCT_CLASS(ConcreteProduct)> \
        GMP_CONCATS(gmp_reg_, AbstractProduct, _, _GMP_GET_CONCRETE_PRODUCT_CLASS(ConcreteProduct))(GMP_IF_THEN_ELSE(GMP_IS_TUPLE(ConcreteProduct), GMP_STRINGIFY(GMP_GET_TUPLE(0, ConcreteProduct)), GMP_STRINGIFY(ConcreteProduct)));

/**
 * @def GMP_FACTORY_REGISTER(AbstractProduct, ConstructorArgs, ...)
 * @brief Register one or more concrete product types with an object factory.
 *
 * This macro creates static registration objects for
 * `gmp::object_factory<AbstractProduct, ...>`. It supports both single
 * constructor-argument forms and tuple forms, and it also supports explicit
 * `(key, type)` registration pairs.
 *
 * @param AbstractProduct The abstract product base type managed by the factory.
 * @param ConstructorArgs Either a single constructor argument type or a tuple of types.
 * @param ... Concrete product registrations. Each item can be:
 *   - a concrete type name, using that type name as the registration key
 *   - a tuple `(key, ConcreteType)` for an explicit string key
 *
 * @par Example
 * @code
 * GMP_FACTORY_REGISTER(shape, (), circle, square)
 * GMP_FACTORY_REGISTER(shape, (), ("round", circle), ("box", square))
 * GMP_FACTORY_REGISTER(widget, (int, std::string), basic_widget, fancy_widget)
 * @endcode
 */
#define GMP_FACTORY_REGISTER(AbstractProduct, ConstructorArgs, ...) \
  _GMP_FACTORY_REGISTER_IMPL(AbstractProduct, ConstructorArgs, __VA_ARGS__)
#define _GMP_FACTORY_REGISTER_IMPL(AbstractProduct, ConstructorArgs, ...) \
  _GMP_FACTORY_REGISTER_IMPL_COMPAT_MSVC(AbstractProduct, ConstructorArgs, GMP_IS_EMPTY(__VA_ARGS__), GMP_TUPLE_EMPTY(ConstructorArgs), __VA_ARGS__)
#define _GMP_FACTORY_REGISTER_IMPL_COMPAT_MSVC(AbstractProduct, ConstructorArgs, _0, _1, ...) \
  GMP_EXPAND( GMP_OVERLOAD_INVOKE(_GMP_FACTORY_REGISTER_WHEN, _0, _1)(AbstractProduct, ConstructorArgs, __VA_ARGS__) )
#define _GMP_FACTORY_REGISTER_WHEN_1(...)
#define _GMP_FACTORY_REGISTER_WHEN_0_1(AbstractProduct, ConstructorArgs, ConcreteProduct, ...) \
  GMP_FACTORY_REGISTER_NO_ARGS(AbstractProduct, ConcreteProduct) \
  GMP_IF(GMP_BOOL(GMP_SIZE_OF_VAARGS(__VA_ARGS__)), _GMP_FACTORY_REGISTER_WHEN_1_CONTINUE) GMP_IF(GMP_BOOL(GMP_SIZE_OF_VAARGS(__VA_ARGS__)), (AbstractProduct, ConstructorArgs, __VA_ARGS__))
#define _GMP_FACTORY_REGISTER_WHEN_0_0(AbstractProduct, ConstructorArgs, ConcreteProduct, ...) \
  GMP_FACTORY_REGISTER_WITH_ARGS(AbstractProduct, ConstructorArgs, ConcreteProduct) \
  GMP_IF(GMP_BOOL(GMP_SIZE_OF_VAARGS(__VA_ARGS__)), _GMP_FACTORY_REGISTER_WHEN_1_CONTINUE) GMP_IF(GMP_BOOL(GMP_SIZE_OF_VAARGS(__VA_ARGS__)), (AbstractProduct, ConstructorArgs, __VA_ARGS__))
#define _GMP_FACTORY_REGISTER_WHEN_1_CONTINUE(AbstractProduct, ConstructorArgs, ...) \
  GMP_DEFER(_GMP_FACTORY_REGISTER_INDIRECT)()(AbstractProduct, ConstructorArgs, __VA_ARGS__)
#define _GMP_FACTORY_REGISTER_INDIRECT() _GMP_FACTORY_REGISTER_IMPL

/** @} */

} // namespace gmp

#endif // GMP_DP_OBJECT_FACTORY_HPP_
