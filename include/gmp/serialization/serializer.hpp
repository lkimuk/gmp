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

#ifndef GMP_SERIALIZATION_SERIALIZER_HPP_
#define GMP_SERIALIZATION_SERIALIZER_HPP_

#include <cmath>
#include <concepts>
#include <gmp/meta/meta.hpp>
#include <gmp/serialization/archive.hpp>
#include <gmp/serialization/detail/schema.hpp>
#include <gmp/serialization/detail/std_types.hpp>
#include <gmp/serialization/options.hpp>
#include <gmp/serialization/traits.hpp>
#include <limits>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
namespace gmp {
template <typename Writer>
  requires serialization_writer<Writer>
class basic_serializer {
public:
  basic_serializer(Writer &writer, serialization_options options = {})
      : writer_(writer), options_(options) {}
  const serialization_options &options() const noexcept { return options_; }
  template <typename T> serialization_result<void> encode(const T &value) {
    return encode_value(value);
  }

  class object_archive {
  public:
    template <typename T>
    serialization_result<void> field(std::string_view name, const T &value) {
      auto status = owner_.write_key(name);
      if (!status)
        return status;
      status = owner_.encode_value(value);
      if (!status)
        return prepend_serialization_path(status.error(), name);
      ++count_;
      return {};
    }

  private:
    friend class basic_serializer;
    explicit object_archive(basic_serializer &owner) : owner_(owner) {}
    basic_serializer &owner_;
    std::size_t count_ = 0;
  };

  class array_archive {
  public:
    template <typename T> serialization_result<void> element(const T &value) {
      auto status = owner_.encode_value(value);
      if (!status)
        return prepend_serialization_path(status.error(),
                                          std::to_string(count_));
      ++count_;
      return {};
    }

  private:
    friend class basic_serializer;
    explicit array_archive(basic_serializer &owner) : owner_(owner) {}
    basic_serializer &owner_;
    std::size_t count_ = 0;
  };

  template <typename F>
  serialization_result<void> object(std::size_t size, F &&write_fields) {
    if (size > options_.max_container_size)
      return make_serialization_error(
          serialization_errc::size_limit_exceeded,
          "container size exceeds configured limit");
    depth_guard depth(*this);
    if (!depth)
      return make_serialization_error(serialization_errc::depth_limit_exceeded,
                                      "maximum serialization depth exceeded");
    auto status = begin_object(size);
    if (!status)
      return status;
    structure_guard structure(*this, true);
    object_archive archive(*this);
    status = std::forward<F>(write_fields)(archive);
    if (!status)
      return status;
    if (archive.count_ != size)
      return make_serialization_error(
          serialization_errc::custom_error,
          "custom object field count does not match declared size");
    return structure.finish();
  }

  template <typename F>
  serialization_result<void> array(std::size_t size, F &&write_elements) {
    if (size > options_.max_container_size)
      return make_serialization_error(
          serialization_errc::size_limit_exceeded,
          "container size exceeds configured limit");
    depth_guard depth(*this);
    if (!depth)
      return make_serialization_error(serialization_errc::depth_limit_exceeded,
                                      "maximum serialization depth exceeded");
    auto status = begin_array(size);
    if (!status)
      return status;
    structure_guard structure(*this, false);
    array_archive archive(*this);
    status = std::forward<F>(write_elements)(archive);
    if (!status)
      return status;
    if (archive.count_ != size)
      return make_serialization_error(
          serialization_errc::custom_error,
          "custom array element count does not match declared size");
    return structure.finish();
  }

  serialization_result<void> write_null() { return writer_.write_null(); }
  serialization_result<void> write_bool(bool v) {
    return writer_.write_bool(v);
  }
  serialization_result<void> write_signed(std::int64_t v) {
    return writer_.write_signed(v);
  }
  serialization_result<void> write_unsigned(std::uint64_t v) {
    return writer_.write_unsigned(v);
  }
  serialization_result<void> write_floating(double v) {
    return writer_.write_floating(v);
  }
  serialization_result<void> write_string(std::string_view v) {
    return writer_.write_string(v);
  }
  serialization_result<void> begin_array(std::size_t n) {
    return writer_.begin_array(n);
  }
  serialization_result<void> end_array() { return writer_.end_array(); }
  serialization_result<void> begin_object(std::size_t n) {
    return writer_.begin_object(n);
  }
  serialization_result<void> write_key(std::string_view v) {
    return writer_.write_key(v);
  }
  serialization_result<void> end_object() { return writer_.end_object(); }

private:
  class depth_guard {
  public:
    explicit depth_guard(basic_serializer &s)
        : s_(s), ok_(s.depth_ < s.options_.max_depth) {
      if (ok_)
        ++s_.depth_;
    }
    ~depth_guard() {
      if (ok_)
        --s_.depth_;
    }
    explicit operator bool() const noexcept { return ok_; }

  private:
    basic_serializer &s_;
    bool ok_;
  };
  class structure_guard {
  public:
    structure_guard(basic_serializer &owner, bool object)
        : owner_(owner), object_(object) {}
    ~structure_guard() {
      if (active_) {
        if (object_)
          (void)owner_.end_object();
        else
          (void)owner_.end_array();
      }
    }
    serialization_result<void> finish() {
      active_ = false;
      return object_ ? owner_.end_object() : owner_.end_array();
    }

  private:
    basic_serializer &owner_;
    bool object_;
    bool active_ = true;
  };
  template <typename T>
  serialization_result<void> encode_value(const T &value) {
    using U = detail::unqualified_t<T>;
    if constexpr (requires(basic_serializer & a, const U &v) {
                    {
                      serialization_traits<U>::serialize(a, v)
                      } -> std::same_as<serialization_result<void>>;
                  })
      return serialization_traits<U>::serialize(*this, value);
    else if constexpr (std::same_as<U, std::nullptr_t>)
      return write_null();
    else if constexpr (std::same_as<U, bool>)
      return write_bool(value);
    else if constexpr (std::is_integral_v<U> && std::is_signed_v<U>)
      return write_signed(static_cast<std::int64_t>(value));
    else if constexpr (std::is_integral_v<U> && std::is_unsigned_v<U>)
      return write_unsigned(static_cast<std::uint64_t>(value));
    else if constexpr (std::is_floating_point_v<U>) {
      if (!std::isfinite(static_cast<double>(value)))
        return make_serialization_error(serialization_errc::value_out_of_range,
                                        "non-finite floating point value");
      return write_floating(static_cast<double>(value));
    } else if constexpr (std::same_as<U, std::string>)
      return write_string(value);
    else if constexpr (std::same_as<U, std::string_view>)
      return write_string(value);
    else if constexpr (detail::is_char_array_v<T>) {
      constexpr auto extent = std::extent_v<std::remove_reference_t<T>>;
      const auto size = extent != 0 && value[extent - 1] == '\0'
                            ? extent - 1
                            : extent;
      return write_string(std::string_view(value, size));
    }
    else if constexpr (std::same_as<U, const char *> ||
                       std::same_as<U, char *>) {
      if (value == nullptr)
        return write_null();
      return write_string(std::string_view(value));
    } else if constexpr (std::is_enum_v<U>) {
      if (options_.enums == enum_encoding::underlying)
        return encode_value(gmp::enum_underlying(value));
      auto i = gmp::enum_index(value);
      if (!i)
        return make_serialization_error(serialization_errc::invalid_enum,
                                        "enum value is not reflected");
      return write_string(gmp::enum_names<U>()[*i]);
    } else if constexpr (detail::is_optional_v<U>) {
      return value ? encode_value(*value) : write_null();
    } else if constexpr (detail::is_sequence_v<U> || detail::is_set_v<U>) {
      if (value.size() > options_.max_container_size)
        return make_serialization_error(
            serialization_errc::size_limit_exceeded,
            "container size exceeds configured limit");
      depth_guard guard(*this);
      if (!guard)
        return make_serialization_error(
            serialization_errc::depth_limit_exceeded,
            "maximum serialization depth exceeded");
      auto r = begin_array(value.size());
      if (!r)
        return r;
      std::size_t i = 0;
      for (const auto &e : value) {
        serialization_result<void> q;
        if constexpr (detail::is_sequence_v<U>) {
          using element_type = typename detail::sequence_traits<U>::value_type;
          if constexpr (std::same_as<element_type, bool>)
            q = encode_value(static_cast<bool>(e));
          else
            q = encode_value(e);
        } else {
          q = encode_value(e);
        }
        if (!q)
          return prepend_serialization_path(q.error(), std::to_string(i));
        ++i;
      }
      return end_array();
    } else if constexpr (detail::is_array_v<U> || detail::is_pair_v<U> ||
                         detail::is_tuple_like_v<U>) {
      constexpr auto N = std::tuple_size_v<U>;
      if (N > options_.max_container_size)
        return make_serialization_error(
            serialization_errc::size_limit_exceeded,
            "container size exceeds configured limit");
      depth_guard guard(*this);
      if (!guard)
        return make_serialization_error(
            serialization_errc::depth_limit_exceeded,
            "maximum serialization depth exceeded");
      auto r = begin_array(N);
      if (!r)
        return r;
      auto each = [&]<std::size_t... I>(std::index_sequence<I...>) {
        serialization_result<void> status;
        auto encode_element = [&]<std::size_t J>() {
          if (!status)
            return;
          status = encode_value(std::get<J>(value));
          if (!status)
            status.error() = prepend_serialization_path(
                status.error(), std::to_string(J));
        };
        (encode_element.template operator()<I>(), ...);
        return status;
      };
      r = each(std::make_index_sequence<N>{});
      if (!r)
        return r;
      return end_array();
    } else if constexpr (detail::is_map_v<U>) {
      if (value.size() > options_.max_container_size)
        return make_serialization_error(
            serialization_errc::size_limit_exceeded,
            "container size exceeds configured limit");
      depth_guard guard(*this);
      if (!guard)
        return make_serialization_error(
            serialization_errc::depth_limit_exceeded,
            "maximum serialization depth exceeded");
      using K = typename detail::map_traits<U>::key_type;
      if constexpr (detail::is_string_key_v<K>) {
        auto r = begin_object(value.size());
        if (!r)
          return r;
        for (const auto &[k, v] : value) {
          if (!(r = write_key(k)))
            return r;
          if (!(r = encode_value(v)))
            return prepend_serialization_path(r.error(), k);
        }
        return end_object();
      } else {
        auto r = begin_array(value.size());
        if (!r)
          return r;
        std::size_t index = 0;
        for (const auto &[k, v] : value) {
          depth_guard entry_depth(*this);
          if (!entry_depth)
            return make_serialization_error(
                serialization_errc::depth_limit_exceeded,
                "maximum serialization depth exceeded",
                std::to_string(index));
          auto q = begin_array(2);
          if (!q)
            return q;
          if (!(q = encode_value(k)))
            return prepend_serialization_path(q.error(),
                                              std::to_string(index) + ".0");
          if (!(q = encode_value(v)))
            return prepend_serialization_path(q.error(),
                                              std::to_string(index) + ".1");
          if (!(q = end_array()))
            return q;
          ++index;
        }
        return end_array();
      }
    } else if constexpr (detail::is_variant_v<U>) {
      if (value.valueless_by_exception())
        return make_serialization_error(
            serialization_errc::value_out_of_range,
            "valueless variant cannot be serialized");
      if (std::size_t{2} > options_.max_container_size)
        return make_serialization_error(
            serialization_errc::size_limit_exceeded,
            "container size exceeds configured limit");
      depth_guard guard(*this);
      if (!guard)
        return make_serialization_error(
            serialization_errc::depth_limit_exceeded,
            "maximum serialization depth exceeded");
      auto r = begin_object(2);
      if (!r)
        return r;
      if (!(r = write_key("index")))
        return r;
      if (!(r = write_unsigned(value.index())))
        return r;
      if (!(r = write_key("value")))
        return r;
      r = std::visit([&](const auto &x) { return encode_value(x); }, value);
      if (!r)
        return r;
      return end_object();
    } else if constexpr (reflectable<U>) {
      static_assert(detail::valid_schema<U>(),
                    "serialization_schema contains an unknown/duplicate member "
                    "or an overlapping wire/alias name");
      constexpr auto N = member_count_v<U>;
      constexpr auto serialized_size = detail::serialized_member_count<U>();
      if (serialized_size > options_.max_container_size)
        return make_serialization_error(
            serialization_errc::size_limit_exceeded,
            "container size exceeds configured limit");
      depth_guard guard(*this);
      if (!guard)
        return make_serialization_error(
            serialization_errc::depth_limit_exceeded,
            "maximum serialization depth exceeded");
      auto r = begin_object(serialized_size);
      if (!r)
        return r;
      auto each = [&]<std::size_t... I>(std::index_sequence<I...>) {
        serialization_result<void> status;
        auto one = [&](auto ic) {
          constexpr std::size_t J = decltype(ic)::value;
          using descriptor = detail::field_descriptor_t<U, J>;
          if constexpr (!descriptor::is_transient) {
            constexpr auto name = detail::descriptor_wire<descriptor>();
            if (status) {
              if (!(status = write_key(name)))
                return;
              status = encode_value(member_ref<J>(value));
              if (!status)
                status.error() =
                    prepend_serialization_path(status.error(), name);
            }
          }
        };
        (one(std::integral_constant<std::size_t, I>{}), ...);
        return status;
      };
      r = each(std::make_index_sequence<N>{});
      if (!r)
        return r;
      return end_object();
    } else
      static_assert(
          detail::always_false_v<U>,
          "type is not serializable; specialize serialization_traits<T>");
  }
  Writer &writer_;
  serialization_options options_;
  std::size_t depth_ = 0;
};
} // namespace gmp
#endif
