// SPDX-License-Identifier: MIT
#ifndef GMP_SERIALIZATION_VALUE_HPP_
#define GMP_SERIALIZATION_VALUE_HPP_
#include <concepts>
#include <cstdint>
#include <cstddef>
#include <gmp/serialization/error.hpp>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>
namespace gmp {
class serialization_value {
public:
  using null_t = std::monostate;
  using array = std::vector<serialization_value>;
  using object = std::vector<std::pair<std::string, serialization_value>>;
  using storage = std::variant<null_t, bool, std::int64_t, std::uint64_t,
                               double, std::string, array, object>;
  serialization_value() noexcept = default;
  serialization_value(std::nullptr_t) noexcept : data_(null_t{}) {}
  serialization_value(bool v) noexcept : data_(v) {}
  template <std::integral I>
    requires(!std::same_as<I, bool>)
  serialization_value(I v) noexcept
      : data_(std::is_signed_v<I> ? storage(std::int64_t(v))
                                  : storage(std::uint64_t(v))) {}
  template <std::floating_point F>
    requires(!std::same_as<F, double>)
  serialization_value(F v) noexcept : data_(static_cast<double>(v)) {}
  serialization_value(std::int64_t v) noexcept : data_(v) {}
  serialization_value(std::uint64_t v) noexcept : data_(v) {}
  serialization_value(double v) noexcept : data_(v) {}
  serialization_value(std::string v) : data_(std::move(v)) {}
  serialization_value(std::string_view v) : data_(std::string(v)) {}
  // A null C string has no useful string representation.  Treat it as the
  // value-level null instead of passing it to std::string (which is UB).
  serialization_value(const char *v)
      : data_(v ? storage(std::string(v)) : storage(null_t{})) {}
  serialization_value(array v) : data_(std::move(v)) {}
  serialization_value(object v) : data_(std::move(v)) {}
  template <typename T> bool is() const noexcept {
    return std::holds_alternative<T>(data_);
  }
  template <typename T> T &get() & { return std::get<T>(data_); }
  template <typename T> const T &get() const & { return std::get<T>(data_); }
  template <typename T> T &&get() && { return std::get<T>(std::move(data_)); }
  const storage &data() const noexcept { return data_; }
  storage &data() noexcept { return data_; }
  std::size_t source_offset() const noexcept { return source_offset_; }
  void source_offset(std::size_t v) noexcept { source_offset_ = v; }

private:
  storage data_;
  std::size_t source_offset_ = serialization_error::unknown_offset;
};
} // namespace gmp
#endif
