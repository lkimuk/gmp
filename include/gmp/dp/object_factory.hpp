/*
 *
MIT License

Copyright (c) 2020-2026 Gaoxing Li

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
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

/*!
@brief Automatically register type into factory and yield them by identifier "key".

This class template is inherited from okdp::singleton and it can hence be used as a "singleton
class".

@tparam AbstractProduct The abstract base class of the products, all registered types are its
subclass.

@since version 1.0.0
*/
template <typename AbstractProduct, typename... ConstructorArgs>
class object_factory : public singleton<object_factory<AbstractProduct, ConstructorArgs...>> {
  using this_type = object_factory<AbstractProduct, ConstructorArgs...>;

public:
  /*!
  @brief register type into map using functor.

  @tparam T the creating type.
  */
  template <typename T>
#if GMP_CPP_AT_LEAST(20)
    requires std::derived_from<T, AbstractProduct>
#endif
  struct register_type {
    // Registers T into object factory
    register_type(const std::string& key) {
      this_type::instance().map_.emplace(key,
        [](const ConstructorArgs&... args) { return new T(args...); });
    }
  };

  // removes object
  void unregister_type(const std::string& key) {
    this_type::instance().map_.erase(key);
  }

  /// return concrete object by invoking new operator
  /// !!!note!!! if use this method user should delete it to avoid memory leaks.
  AbstractProduct* create(const std::string& key, const ConstructorArgs&... args) {
    if (this_type::instance().map_.find(key) == this_type::instance().map_.end())
      throw std::invalid_argument("Unknown object type passed to factory!");
    return this_type::instance().map_[key](args...);
  }

  /// return concrete object by invoking shared ptr
  std::shared_ptr<AbstractProduct> create_shared(
    const std::string& key, const ConstructorArgs&... args) {
    return std::shared_ptr<AbstractProduct>(create(key, args...));
  }

  /// return concrete object by invoking unique ptr
  std::unique_ptr<AbstractProduct> create_unique(
    const std::string& key, const ConstructorArgs&... args) {
    return std::unique_ptr<AbstractProduct>(create(key, args...));
  }

private:
  std::map<std::string, std::function<AbstractProduct*(const ConstructorArgs&... args)>> map_;
};

#define _GMP_GET_CONCRETE_PRODUCT_CLASS(ConcreteProduct) GMP_IF_THEN_ELSE(GMP_IS_TUPLE(ConcreteProduct), GMP_GET_TUPLE, ConcreteProduct)GMP_IF(GMP_IS_TUPLE(ConcreteProduct), (1, ConcreteProduct))
#define _GMP_GET_CONSTRUCTOR_TYPES(ConstructorArgs) GMP_IF_THEN_ELSE(GMP_IS_TUPLE(ConstructorArgs), GMP_REMOVE_PARENS, ConstructorArgs)GMP_IF(GMP_IS_TUPLE(ConstructorArgs), (ConstructorArgs))
#define GMP_FACTORY_REGISTER_ONE(AbstractProduct, ConstructorArgs, ConcreteProduct) \
  static gmp::object_factory<AbstractProduct, _GMP_GET_CONSTRUCTOR_TYPES(ConstructorArgs)>::register_type<_GMP_GET_CONCRETE_PRODUCT_CLASS(ConcreteProduct)> \
        GMP_CONCATS(gmp_reg_, AbstractProduct, _, _GMP_GET_CONCRETE_PRODUCT_CLASS(ConcreteProduct))(GMP_IF_THEN_ELSE(GMP_IS_TUPLE(ConcreteProduct), GMP_STRINGIFY(GMP_GET_TUPLE(0, ConcreteProduct)), GMP_STRINGIFY(ConcreteProduct)));

/**
 * @brief 
 * 
 * @example
 * GMP_FACTORY_REGISTER(base_class, constructor_arg_type, (name1, derived_class1), (name2, derived_class2))
 * GMP_FACTORY_REGISTER(base_class, (constructor_arg1_type, arg2_type), derived_class1, class2)
 */
#define GMP_FACTORY_REGISTER(AbstractProduct, ConstructorArgs, ...) \
  GMP_EVAL( _GMP_FACTORY_REGISTER_IMPL(AbstractProduct, ConstructorArgs, __VA_ARGS__) )
#define _GMP_FACTORY_REGISTER_IMPL(AbstractProduct, ConstructorArgs, ...) \
  GMP_EXPAND( GMP_OVERLOAD_INVOKE(_GMP_FACTORY_REGISTER_WHEN, GMP_BOOL(GMP_SIZE_OF_VAARGS(__VA_ARGS__)))(AbstractProduct, ConstructorArgs, __VA_ARGS__) )
#define _GMP_FACTORY_REGISTER_WHEN_0(...)
#define _GMP_FACTORY_REGISTER_WHEN_1(AbstractProduct, ConstructorArgs, ConcreteProduct, ...) \
  GMP_FACTORY_REGISTER_ONE(AbstractProduct, ConstructorArgs, ConcreteProduct) \
  GMP_IF(GMP_BOOL(GMP_SIZE_OF_VAARGS(__VA_ARGS__)), _GMP_FACTORY_REGISTER_WHEN_1_CONTINUE) GMP_IF(GMP_BOOL(GMP_SIZE_OF_VAARGS(__VA_ARGS__)), (AbstractProduct, ConstructorArgs, __VA_ARGS__))
#define _GMP_FACTORY_REGISTER_WHEN_1_CONTINUE(AbstractProduct, ConstructorArgs, ...) \
  GMP_DEFER(_GMP_FACTORY_REGISTER_INDIRECT)()(AbstractProduct, ConstructorArgs, __VA_ARGS__)
#define _GMP_FACTORY_REGISTER_INDIRECT() _GMP_FACTORY_REGISTER_IMPL

} // namespace gmp

#endif // GMP_DP_OBJECT_FACTORY_HPP_
