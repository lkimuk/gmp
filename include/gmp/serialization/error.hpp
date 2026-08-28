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

#ifndef GMP_SERIALIZATION_ERROR_HPP_
#define GMP_SERIALIZATION_ERROR_HPP_

#include <cstddef>
#include <limits>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <variant>

namespace gmp {

enum class serialization_errc {
  none,
  unexpected_end,
  invalid_syntax,
  invalid_escape,
  invalid_utf8,
  invalid_number,
  type_mismatch,
  missing_field,
  unknown_field,
  duplicate_field,
  duplicate_element,
  ambiguous_field,
  invalid_enum,
  integer_overflow,
  value_out_of_range,
  size_limit_exceeded,
  depth_limit_exceeded,
  unsupported_type,
  custom_error
};

struct serialization_error {
  static constexpr std::size_t unknown_offset = std::numeric_limits<std::size_t>::max();
  serialization_errc code = serialization_errc::none;
  std::string message;
  std::string path;
  std::size_t offset = unknown_offset;

  [[nodiscard]] std::string describe() const {
    std::string result = message;
    if (!path.empty()) {
      result += " at ";
      result += path;
    }
    if (offset != unknown_offset) {
      result += " (byte ";
      result += std::to_string(offset);
      result += ')';
    }
    return result;
  }
};

struct serialization_unexpected {
  serialization_error error;
};

template <typename T> class serialization_result {
public:
  serialization_result(T value) : storage_(std::in_place_index<0>, std::move(value)) {}

  serialization_result(serialization_error error)
      : storage_(std::in_place_index<1>, serialization_unexpected{std::move(error)}) {}

  [[nodiscard]] bool has_value() const noexcept {
    return storage_.index() == 0;
  }

  explicit operator bool() const noexcept {
    return has_value();
  }

  T &value() & {
    return std::get<0>(storage_);
  }

  const T &value() const & {
    return std::get<0>(storage_);
  }

  T &&value() && {
    return std::get<0>(std::move(storage_));
  }

  T &operator*() & {
    return value();
  }

  const T &operator*() const & {
    return value();
  }

  T &&operator*() && {
    return std::move(*this).value();
  }

  T *operator->() {
    return &value();
  }

  const T *operator->() const {
    return &value();
  }

  serialization_error &error() & {
    return std::get<1>(storage_).error;
  }

  const serialization_error &error() const & {
    return std::get<1>(storage_).error;
  }

private:
  std::variant<T, serialization_unexpected> storage_;
};

template <> class serialization_result<void> {
public:
  serialization_result() noexcept = default;

  serialization_result(serialization_error error) : error_(std::move(error)) {}

  [[nodiscard]] bool has_value() const noexcept {
    return !error_.has_value();
  }

  explicit operator bool() const noexcept {
    return has_value();
  }

  serialization_error &error() & {
    return error_.value();
  }

  const serialization_error &error() const & {
    return error_.value();
  }

private:
  std::optional<serialization_error> error_;
};

inline serialization_error
make_serialization_error(serialization_errc code, std::string message, std::string path = {},
                         std::size_t offset = serialization_error::unknown_offset) {
  return {code, std::move(message), std::move(path), offset};
}

inline serialization_error prepend_serialization_path(serialization_error error,
                                                      std::string_view segment) {
  if (!segment.empty()) {
    std::string path(segment);
    if (!error.path.empty()) {
      path.push_back('.');
      path += error.path;
    }
    error.path = std::move(path);
  }
  return error;
}

class serialization_exception : public std::runtime_error {
public:
  explicit serialization_exception(const serialization_error &error)
      : std::runtime_error(error.describe()), error_(error) {}

  const serialization_error &error() const noexcept {
    return error_;
  }

private:
  serialization_error error_;
};


} // namespace gmp

#endif // GMP_SERIALIZATION_ERROR_HPP_
