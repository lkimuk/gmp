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

#ifndef GMP_SERIALIZATION_VALUE_ARCHIVE_HPP_
#define GMP_SERIALIZATION_VALUE_ARCHIVE_HPP_

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include <gmp/serialization/archive.hpp>
#include <gmp/serialization/value.hpp>

namespace gmp {

class value_writer {
public:
  serialization_result<void> write_null() {
    return put(serialization_value(nullptr));
  }

  serialization_result<void> write_bool(bool v) {
    return put(serialization_value(v));
  }

  serialization_result<void> write_signed(std::int64_t v) {
    return put(serialization_value(v));
  }

  serialization_result<void> write_unsigned(std::uint64_t v) {
    return put(serialization_value(v));
  }

  serialization_result<void> write_floating(double v) {
    return put(serialization_value(v));
  }

  serialization_result<void> write_string(std::string_view v) {
    return put(serialization_value(std::string(v)));
  }

  serialization_result<void> begin_array(std::size_t size) {
    serialization_value::array value;
    value.reserve(size);
    return begin(serialization_kind::array, serialization_value(std::move(value)));
  }

  serialization_result<void> end_array() {
    return end(serialization_kind::array);
  }

  serialization_result<void> begin_object(std::size_t size) {
    serialization_value::object value;
    value.reserve(size);
    return begin(serialization_kind::object, serialization_value(std::move(value)));
  }

  serialization_result<void> write_key(std::string_view key) {
    if (finished_) {
      return make_serialization_error(serialization_errc::custom_error,
                                      "value archive is already finished");
    }
    if (stack_.empty() || stack_.back().kind != serialization_kind::object) {
      return make_serialization_error(serialization_errc::custom_error,
                                      "object key outside object");
    }
    if (stack_.back().has_key) {
      return make_serialization_error(serialization_errc::custom_error,
                                      "object key requires a value");
    }
    stack_.back().key = std::string(key);
    stack_.back().has_key = true;
    return {};
  }

  serialization_result<void> end_object() {
    return end(serialization_kind::object);
  }

  serialization_result<serialization_value> finish() {
    if (finished_) {
      return make_serialization_error(serialization_errc::custom_error,
                                      "value archive is already finished");
    }
    if (!stack_.empty() || !root_) {
      return make_serialization_error(serialization_errc::custom_error, "incomplete archive");
    }
    auto result = std::move(*root_);
    root_.reset();
    finished_ = true;
    return result;
  }

private:
  struct frame {
    serialization_kind kind;
    serialization_value value;
    std::string key;
    bool has_key = false;
  };

  serialization_result<void> put(serialization_value v) {
    if (finished_) {
      return make_serialization_error(serialization_errc::custom_error,
                                      "value archive is already finished");
    }
    auto status = validate_value_position();
    if (!status) {
      return status;
    }
    if (stack_.empty()) {
      root_ = std::move(v);
      return {};
    }
    auto &f = stack_.back();
    if (f.kind == serialization_kind::array) {
      f.value.get<serialization_value::array>().push_back(std::move(v));
      return {};
    }
    f.value.get<serialization_value::object>().emplace_back(std::move(f.key), std::move(v));
    f.key.clear();
    f.has_key = false;
    return {};
  }

  serialization_result<void> begin(serialization_kind kind, serialization_value v) {
    if (finished_) {
      return make_serialization_error(serialization_errc::custom_error,
                                      "value archive is already finished");
    }
    auto status = validate_value_position();
    if (!status) {
      return status;
    }
    stack_.push_back({kind, std::move(v), {}});
    return {};
  }

  serialization_result<void> validate_value_position() const {
    if (stack_.empty()) {
      if (root_) {
        return make_serialization_error(serialization_errc::custom_error, "multiple root values");
      }
      return {};
    }
    if (stack_.back().kind == serialization_kind::object && !stack_.back().has_key) {
      return make_serialization_error(serialization_errc::custom_error, "object value without key");
    }
    return {};
  }

  serialization_result<void> end(serialization_kind expected) {
    if (finished_) {
      return make_serialization_error(serialization_errc::custom_error,
                                      "value archive is already finished");
    }
    if (stack_.empty()) {
      return make_serialization_error(serialization_errc::custom_error,
                                      "archive end without begin");
    }
    if (stack_.back().kind != expected) {
      return make_serialization_error(serialization_errc::custom_error, "mismatched archive end");
    }
    if (stack_.back().kind == serialization_kind::object && stack_.back().has_key) {
      return make_serialization_error(serialization_errc::custom_error,
                                      "object ended with missing value");
    }
    auto v = std::move(stack_.back().value);
    stack_.pop_back();
    return put(std::move(v));
  }

  std::optional<serialization_value> root_;
  std::vector<frame> stack_;
  bool finished_ = false;
};

class value_reader {
public:
  struct member_view;

  explicit value_reader(const serialization_value &value) : value_(&value) {}

  serialization_kind kind() const noexcept {
    if (value_->is<serialization_value::null_t>()) {
      return serialization_kind::null;
    }
    if (value_->is<bool>()) {
      return serialization_kind::boolean;
    }
    if (value_->is<std::int64_t>()) {
      return serialization_kind::signed_integer;
    }
    if (value_->is<std::uint64_t>()) {
      return serialization_kind::unsigned_integer;
    }
    if (value_->is<double>()) {
      return serialization_kind::floating;
    }
    if (value_->is<std::string>()) {
      return serialization_kind::string;
    }
    if (value_->is<serialization_value::array>()) {
      return serialization_kind::array;
    }
    return serialization_kind::object;
  }

  std::size_t size() const noexcept {
    if (value_->is<serialization_value::array>()) {
      return value_->get<serialization_value::array>().size();
    }
    if (value_->is<serialization_value::object>()) {
      return value_->get<serialization_value::object>().size();
    }
    return 0;
  }

  bool read_bool() const {
    return value_->get<bool>();
  }

  std::int64_t read_signed() const {
    return value_->get<std::int64_t>();
  }

  std::uint64_t read_unsigned() const {
    return value_->get<std::uint64_t>();
  }

  double read_floating() const {
    return value_->get<double>();
  }

  std::string_view read_string() const {
    return value_->get<std::string>();
  }

  value_reader element(std::size_t i) const {
    return value_reader(value_->get<serialization_value::array>().at(i));
  }

  member_view member(std::size_t i) const;

  const serialization_value &value() const noexcept {
    return *value_;
  }

private:
  const serialization_value *value_;
};

struct value_reader::member_view {
  std::string_view name;
  value_reader value;
};

inline value_reader::member_view value_reader::member(std::size_t i) const {
  const auto &p = value_->get<serialization_value::object>().at(i);
  return {p.first, value_reader(p.second)};
}

} // namespace gmp

#endif // GMP_SERIALIZATION_VALUE_ARCHIVE_HPP_
