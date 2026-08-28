// SPDX-License-Identifier: MIT
#ifndef GMP_SERIALIZATION_DESERIALIZER_HPP_
#define GMP_SERIALIZATION_DESERIALIZER_HPP_
#include <gmp/meta/meta.hpp>
#include <gmp/serialization/archive.hpp>
#include <gmp/serialization/detail/schema.hpp>
#include <gmp/serialization/detail/std_types.hpp>
#include <gmp/serialization/options.hpp>
#include <concepts>
#include <cmath>
#include <limits>
#include <optional>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
namespace gmp {
template <typename Reader>
  requires serialization_reader<Reader>
class basic_deserializer {
public:
  basic_deserializer(const Reader &reader, deserialization_options options = {})
      : reader_(reader), options_(options) {}
  const deserialization_options &options() const noexcept { return options_; }
  template <typename T> serialization_result<T> decode() {
    return decode_value<T>(reader_);
  }

private:
  template <typename R> class decoder_archive {
  public:
    decoder_archive(basic_deserializer &owner, const R &reader)
        : owner_(owner), reader_(reader) {}
    template <typename T> serialization_result<T> decode() {
      return owner_.template decode_value<T>(reader_);
    }
    template <typename T>
    serialization_result<T> decode(const R &reader) {
      return owner_.template decode_value<T>(reader);
    }
    const deserialization_options &options() const noexcept {
      return owner_.options();
    }
    serialization_kind kind() const noexcept { return reader_.kind(); }
    std::size_t size() const noexcept { return reader_.size(); }
    bool read_bool() const { return reader_.read_bool(); }
    std::int64_t read_signed() const { return reader_.read_signed(); }
    std::uint64_t read_unsigned() const { return reader_.read_unsigned(); }
    double read_floating() const { return reader_.read_floating(); }
    std::string_view read_string() const { return reader_.read_string(); }
    auto element(std::size_t index) const { return reader_.element(index); }
    auto member(std::size_t index) const { return reader_.member(index); }

  private:
    basic_deserializer &owner_;
    const R &reader_;
  };
  class depth_guard {
  public:
    explicit depth_guard(basic_deserializer &s)
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
    basic_deserializer &s_;
    bool ok_;
  };
  template <typename T> serialization_result<T> decode_value(const Reader &r) {
    auto result = decode_value_impl<T>(r);
    if (!result &&
        result.error().offset == serialization_error::unknown_offset) {
      if constexpr (requires { r.value().source_offset(); })
        result.error().offset = r.value().source_offset();
    }
    return result;
  }

  template <typename T>
  serialization_result<T> decode_value_impl(const Reader &r) {
    using U = detail::unqualified_t<T>;
    if constexpr (requires(decoder_archive<Reader> & a) {
                    {
                      serialization_traits<U>::deserialize(a, type_tag<U>{})
                      } -> std::same_as<serialization_result<U>>;
                  }) {
      decoder_archive<Reader> archive(*this, r);
      return serialization_traits<U>::deserialize(archive, type_tag<U>{});
    } else if constexpr (std::same_as<U, std::nullptr_t> ||
                         std::same_as<U, std::monostate>) {
      if (r.kind() != serialization_kind::null)
        return make_serialization_error(serialization_errc::type_mismatch,
                                        "expected null");
      return U{};
    } else if constexpr (std::same_as<U, bool>) {
      if (r.kind() != serialization_kind::boolean)
        return make_serialization_error(serialization_errc::type_mismatch,
                                        "expected boolean");
      return r.read_bool();
    } else if constexpr (std::is_integral_v<U> && std::is_signed_v<U>) {
      if (r.kind() == serialization_kind::signed_integer) {
        const auto n = r.read_signed();
        if (n < static_cast<std::int64_t>(std::numeric_limits<U>::min()) ||
            n > static_cast<std::int64_t>(std::numeric_limits<U>::max()))
          return make_serialization_error(serialization_errc::integer_overflow,
                                          "integer value is out of range");
        return static_cast<U>(n);
      }
      if (r.kind() == serialization_kind::unsigned_integer) {
        const auto n = r.read_unsigned();
        if (n > static_cast<std::uint64_t>(std::numeric_limits<U>::max()))
          return make_serialization_error(serialization_errc::integer_overflow,
                                          "integer value is out of range");
        return static_cast<U>(n);
      }
      return make_serialization_error(serialization_errc::type_mismatch,
                                      "expected signed integer");
    } else if constexpr (std::is_integral_v<U> && std::is_unsigned_v<U>) {
      if (r.kind() == serialization_kind::unsigned_integer) {
        const auto n = r.read_unsigned();
        if (n > static_cast<std::uint64_t>(std::numeric_limits<U>::max()))
          return make_serialization_error(serialization_errc::integer_overflow,
                                          "integer value is out of range");
        return static_cast<U>(n);
      }
      if (r.kind() == serialization_kind::signed_integer) {
        const auto n = r.read_signed();
        if (n < 0 ||
            static_cast<std::uint64_t>(n) >
                static_cast<std::uint64_t>(std::numeric_limits<U>::max()))
          return make_serialization_error(serialization_errc::integer_overflow,
                                          "integer value is out of range");
        return static_cast<U>(n);
      }
      return make_serialization_error(serialization_errc::type_mismatch,
                                      "expected unsigned integer");
    } else if constexpr (std::is_floating_point_v<U>) {
      long double n = 0;
      if (r.kind() == serialization_kind::floating)
        n = r.read_floating();
      else if (r.kind() == serialization_kind::signed_integer)
        n = r.read_signed();
      else if (r.kind() == serialization_kind::unsigned_integer)
        n = r.read_unsigned();
      else
        return make_serialization_error(serialization_errc::type_mismatch,
                                        "expected number");
      if (!std::isfinite(static_cast<long double>(n)) ||
          n < std::numeric_limits<U>::lowest() ||
          n > std::numeric_limits<U>::max())
        return make_serialization_error(serialization_errc::value_out_of_range,
                                        "floating point value is out of range");
      return static_cast<U>(n);
    } else if constexpr (std::same_as<U, std::string>) {
      if (r.kind() != serialization_kind::string)
        return make_serialization_error(serialization_errc::type_mismatch,
                                        "expected string");
      return std::string(r.read_string());
    } else if constexpr (std::is_enum_v<U>) {
      if (r.kind() == serialization_kind::string &&
          options_.enums != enum_decoding::underlying) {
        auto v = enum_cast<U>(r.read_string());
        if (!v)
          return make_serialization_error(serialization_errc::invalid_enum,
                                          "unknown enum name");
        return *v;
      }
      if ((options_.enums == enum_decoding::underlying ||
           options_.enums == enum_decoding::name_or_underlying) &&
          (r.kind() == serialization_kind::signed_integer ||
           r.kind() == serialization_kind::unsigned_integer)) {
        using B = std::underlying_type_t<U>;
        auto n = decode_value<B>(r);
        if (!n)
          return n.error();
        U v = static_cast<U>(*n);
        if (!enum_contains(v))
          return make_serialization_error(serialization_errc::invalid_enum,
                                          "unknown enum value");
        return v;
      }
      return make_serialization_error(serialization_errc::type_mismatch,
                                      "expected enum name");
    } else if constexpr (detail::is_optional_v<U>) {
      if (r.kind() == serialization_kind::null)
        return U{};
      auto v = decode_value<typename detail::optional_traits<U>::value_type>(r);
      if (!v)
        return v.error();
      return U{std::move(*v)};
    } else if constexpr (detail::is_sequence_v<U>) {
      if (r.kind() != serialization_kind::array)
        return make_serialization_error(serialization_errc::type_mismatch,
                                        "expected an array");
      if (r.size() > options_.max_container_size)
        return make_serialization_error(
            serialization_errc::size_limit_exceeded,
            "container size exceeds configured limit");
      depth_guard guard(*this);
      if (!guard)
        return make_serialization_error(
            serialization_errc::depth_limit_exceeded,
            "maximum deserialization depth exceeded");
      U out;
      if constexpr (requires { out.reserve(r.size()); })
        out.reserve(r.size());
      for (std::size_t i = 0; i < r.size(); ++i) {
        auto v = decode_value<typename detail::sequence_traits<U>::value_type>(
            r.element(i));
        if (!v)
          return prepend_serialization_path(v.error(), std::to_string(i));
        out.emplace_back(std::move(*v));
      }
      return out;
    } else if constexpr (detail::is_set_v<U>) {
      if (r.kind() != serialization_kind::array)
        return make_serialization_error(serialization_errc::type_mismatch,
                                        "expected an array");
      if (r.size() > options_.max_container_size)
        return make_serialization_error(
            serialization_errc::size_limit_exceeded,
            "container size exceeds configured limit");
      depth_guard guard(*this);
      if (!guard)
        return make_serialization_error(
            serialization_errc::depth_limit_exceeded,
            "maximum deserialization depth exceeded");
      U out;
      for (std::size_t i = 0; i < r.size(); ++i) {
        auto v = decode_value<typename detail::set_traits<U>::value_type>(
            r.element(i));
        if (!v)
          return prepend_serialization_path(v.error(), std::to_string(i));
        auto [it, inserted] = out.emplace(std::move(*v));
        if (!inserted &&
            options_.duplicate_elements == duplicate_element_policy::reject)
          return make_serialization_error(serialization_errc::duplicate_element,
                                          "duplicate set element",
                                          std::to_string(i));
      }
      return out;
    } else if constexpr (detail::is_array_v<U> || detail::is_pair_v<U> ||
                         detail::is_tuple_like_v<U>) {
      constexpr auto N = std::tuple_size_v<U>;
      if (r.kind() == serialization_kind::array &&
          r.size() > options_.max_container_size)
        return make_serialization_error(
            serialization_errc::size_limit_exceeded,
            "container size exceeds configured limit");
      if (r.kind() != serialization_kind::array)
        return make_serialization_error(serialization_errc::type_mismatch,
                                        "expected an array");
      if (r.size() != N)
        return make_serialization_error(serialization_errc::value_out_of_range,
                                        "tuple length does not match input");
      depth_guard guard(*this);
      if (!guard)
        return make_serialization_error(
            serialization_errc::depth_limit_exceeded,
            "maximum deserialization depth exceeded");
      return decode_tuple<U>(r, std::make_index_sequence<N>{});
    } else if constexpr (detail::is_map_v<U>) {
      if (r.kind() != serialization_kind::array &&
          r.kind() != serialization_kind::object)
        return make_serialization_error(serialization_errc::type_mismatch,
                                        "expected map array/object");
      if (r.size() > options_.max_container_size)
        return make_serialization_error(
            serialization_errc::size_limit_exceeded,
            "container size exceeds configured limit");
      depth_guard guard(*this);
      if (!guard)
        return make_serialization_error(
            serialization_errc::depth_limit_exceeded,
            "maximum deserialization depth exceeded");
      U out;
      using K = typename detail::map_traits<U>::key_type;
      using V = typename detail::map_traits<U>::mapped_type;
      if constexpr (detail::is_string_key_v<K>) {
        if (r.kind() != serialization_kind::object)
          return make_serialization_error(serialization_errc::type_mismatch,
                                          "expected object map");
        for (std::size_t i = 0; i < r.size(); ++i) {
          auto m = r.member(i);
          auto it = out.find(std::string(m.name));
          if (it != out.end()) {
            if (options_.duplicate_fields == duplicate_field_policy::reject)
              return make_serialization_error(
                  serialization_errc::duplicate_field, "duplicate map key",
                  std::string(m.name));
            if (options_.duplicate_fields == duplicate_field_policy::keep_first)
              continue;
          }
          auto v = decode_value<V>(m.value);
          if (!v)
            return prepend_serialization_path(v.error(), m.name);
          if (it != out.end())
            out.erase(it);
          out.emplace(std::string(m.name), std::move(*v));
        }
      } else {
        if (r.kind() != serialization_kind::array)
          return make_serialization_error(serialization_errc::type_mismatch,
                                          "expected map entry array");
        for (std::size_t i = 0; i < r.size(); ++i) {
          auto e = r.element(i);
          if (e.kind() != serialization_kind::array || e.size() != 2)
            return make_serialization_error(
                serialization_errc::type_mismatch,
                "map entry must contain key and value", std::to_string(i));
          depth_guard entry_depth(*this);
          if (!entry_depth)
            return make_serialization_error(
                serialization_errc::depth_limit_exceeded,
                "maximum deserialization depth exceeded",
                std::to_string(i));
          auto k = decode_value<K>(e.element(0));
          if (!k)
            return prepend_serialization_path(
                k.error(), std::to_string(i) + ".0");
          auto v = decode_value<V>(e.element(1));
          if (!v)
            return prepend_serialization_path(
                v.error(), std::to_string(i) + ".1");
          auto [it, inserted] = out.emplace(std::move(*k), std::move(*v));
          if (!inserted &&
              options_.duplicate_elements == duplicate_element_policy::reject)
            return make_serialization_error(
                serialization_errc::duplicate_element, "duplicate map key",
                std::to_string(i));
        }
      }
      return out;
    } else if constexpr (detail::is_variant_v<U>) {
      if (r.kind() != serialization_kind::object)
        return make_serialization_error(serialization_errc::type_mismatch,
                                        "expected variant object");
      if (r.size() > options_.max_container_size)
        return make_serialization_error(
            serialization_errc::size_limit_exceeded,
            "container size exceeds configured limit");
      depth_guard guard(*this);
      if (!guard)
        return make_serialization_error(
            serialization_errc::depth_limit_exceeded,
            "maximum deserialization depth exceeded");
      std::optional<std::uint64_t> index;
      std::optional<Reader> payload;
      for (std::size_t i = 0; i < r.size(); ++i) {
        auto m = r.member(i);
        auto should_replace = [&](bool present)
            -> serialization_result<bool> {
          if (!present)
            return true;
          if (options_.duplicate_fields == duplicate_field_policy::reject)
            return make_serialization_error(serialization_errc::duplicate_field,
                                            "duplicate variant field",
                                            std::string(m.name));
          return options_.duplicate_fields == duplicate_field_policy::keep_last;
        };
        if (m.name == "index") {
          auto replace = should_replace(index.has_value());
          if (!replace)
            return replace.error();
          if (*replace) {
            if (m.value.kind() != serialization_kind::unsigned_integer)
              return make_serialization_error(
                  serialization_errc::type_mismatch,
                  "variant index must be unsigned", "index");
            index = m.value.read_unsigned();
          }
        } else if (m.name == "value") {
          auto replace = should_replace(payload.has_value());
          if (!replace)
            return replace.error();
          if (*replace)
            payload.emplace(std::move(m.value));
        } else if (options_.unknown_fields == unknown_field_policy::reject)
          return make_serialization_error(serialization_errc::unknown_field,
                                          "unknown variant field",
                                          std::string(m.name));
      }
      if (!index || !payload)
        return make_serialization_error(serialization_errc::invalid_syntax,
                                        "variant requires index and value");
      const auto variant_index = *index;
      if (variant_index >= std::variant_size_v<U>)
        return make_serialization_error(
            serialization_errc::value_out_of_range,
            "variant index is out of range", "index");
      auto result = decode_variant<U>(variant_index, *payload);
      if (!result)
        return prepend_serialization_path(result.error(), "value");
      return result;
    } else if constexpr (reflectable<U>) {
      return decode_aggregate<U>(r);
    } else
      static_assert(
          detail::always_false_v<U>,
          "type is not deserializable; specialize serialization_traits<T>");
  }
  template <typename T, std::size_t... I>
  serialization_result<T> decode_tuple(const Reader &r,
                                       std::index_sequence<I...>) {
    auto decode_element = [&]<std::size_t J>()
        -> serialization_result<std::tuple_element_t<J, T>> {
      auto value = decode_value<std::tuple_element_t<J, T>>(r.element(J));
      if (!value)
        return prepend_serialization_path(value.error(), std::to_string(J));
      return value;
    };
    std::tuple<serialization_result<std::tuple_element_t<I, T>>...> vals{
        decode_element.template operator()<I>()...};
    bool ok = true;
    serialization_error e;
    std::apply(
        [&](auto &...v) {
          auto check = [&](auto &x) {
            if (!x && ok) {
              ok = false;
              e = x.error();
            }
          };
          (check(v), ...);
        },
        vals);
    if (!ok)
      return e;
    return T{std::move(*std::get<I>(vals))...};
  }
  template <typename V, std::size_t I = 0>
  serialization_result<V> decode_variant(std::size_t index,
                                         const Reader &payload) {
    if constexpr (I == std::variant_size_v<V>)
      return make_serialization_error(serialization_errc::value_out_of_range,
                                      "variant index is out of range");
    else if (index == I) {
      auto v = decode_value<std::variant_alternative_t<I, V>>(payload);
      if (!v)
        return v.error();
      return V{std::in_place_index<I>, std::move(*v)};
    } else
      return decode_variant<V, I + 1>(index, payload);
  }
  template <typename T>
  serialization_result<T> decode_aggregate(const Reader &r) {
    static_assert(detail::valid_schema<T>(),
                  "serialization_schema contains an unknown/duplicate member "
                  "or an overlapping wire/alias name");
    if (r.kind() != serialization_kind::object)
      return make_serialization_error(serialization_errc::type_mismatch,
                                      "expected object");
    if (r.size() > options_.max_container_size)
      return make_serialization_error(
          serialization_errc::size_limit_exceeded,
          "container size exceeds configured limit");
    depth_guard guard(*this);
    if (!guard)
      return make_serialization_error(serialization_errc::depth_limit_exceeded,
                                      "maximum deserialization depth exceeded");
    constexpr auto N = member_count_v<T>;
    return decode_aggregate_impl<T>(r, std::make_index_sequence<N>{});
  }
  template <typename T, std::size_t... I>
  serialization_result<T> decode_aggregate_impl(const Reader &r,
                                                std::index_sequence<I...>) {
    std::tuple<std::optional<member_type_t<I, T>>...> slots;
    bool ok = true;
    serialization_error error;
    auto field = [&](std::size_t pos) {
      auto m = r.member(pos);
      bool matched = false;
      auto one = [&]<std::size_t J>() {
        using D = detail::field_descriptor_t<T, J>;
        if (D::matches(m.name)) {
          if (matched) {
            ok = false;
            error = make_serialization_error(
                serialization_errc::ambiguous_field,
                "input field matches multiple schema members",
                std::string(m.name));
          } else {
            matched = true;
            if constexpr (!D::is_transient) {
              auto &slot = std::get<J>(slots);
              if (slot &&
                  options_.duplicate_fields ==
                      duplicate_field_policy::reject) {
                ok = false;
                error = make_serialization_error(
                    serialization_errc::duplicate_field,
                    "duplicate object field", std::string(m.name));
                return;
              }
              if (slot && options_.duplicate_fields ==
                              duplicate_field_policy::keep_first)
                return;
              auto v = decode_value<member_type_t<J, T>>(m.value);
              if (!v) {
                ok = false;
                error = prepend_serialization_path(v.error(), m.name);
              } else
                slot = std::move(*v);
            }
          }
        }
      };
      (one.template operator()<I>(), ...);
      if (!matched && ok &&
          options_.unknown_fields == unknown_field_policy::reject) {
        ok = false;
        error = make_serialization_error(serialization_errc::unknown_field,
                                         "unknown object field",
                                         std::string(m.name));
      }
    };
    if (r.kind() != serialization_kind::object)
      return make_serialization_error(serialization_errc::type_mismatch,
                                      "expected object");
    for (std::size_t p = 0; p < r.size() && ok; ++p)
      field(p);
    auto missing = [&]<std::size_t J>() {
      auto &s = std::get<J>(slots);
      using M = member_type_t<J, T>;
      if (!s) {
        using D = detail::field_descriptor_t<T, J>;
        if constexpr (D::has_default)
          s.emplace(D::template make_default<M>());
        else if constexpr (D::is_transient && std::default_initializable<M>)
          s.emplace();
        else if constexpr (detail::is_optional_v<M>)
          s.emplace(std::nullopt);
        else if (ok) {
          ok = false;
          error = make_serialization_error(
              serialization_errc::missing_field,
              "missing required object field",
              std::string(detail::descriptor_wire<D>()));
        }
      }
    };
    (missing.template operator()<I>(), ...);
    if (!ok)
      return error;
    return T{std::move(*std::get<I>(slots))...};
  }
  const Reader &reader_;
  deserialization_options options_;
  std::size_t depth_ = 0;
};
} // namespace gmp
#endif
