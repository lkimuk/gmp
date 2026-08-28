//   ___ __  __ ___
//  / __|  \/  | _ \\ GMP(Generative Metaprogramming)
// | (_ | |\/| |  _/  version 0.4.0
//  \___|_|  |_|_|    https://github.com/lkimuk/gmp
//
// SPDX-License-Identifier: MIT

#ifndef GMP_SERIALIZATION_JSON_HPP_
#define GMP_SERIALIZATION_JSON_HPP_

#include <charconv>
#include <cmath>
#include <concepts>
#include <cstdint>
#include <limits>
#include <string>
#include <string_view>
#include <type_traits>
#include <variant>
#include <vector>

#include <gmp/serialization/serialization.hpp>
#include <gmp/serialization/detail/text.hpp>
#include <gmp/serialization/detail/write_value.hpp>

namespace gmp {
namespace detail {

class json_parser {
public:
  json_parser(std::string_view input, json_read_options options)
      : input_(input), options_(options) {}

  serialization_result<serialization_value> parse() {
    if (input_.size() > options_.max_input_size)
      return error(serialization_errc::size_limit_exceeded,
                   "JSON input exceeds the configured size limit");
    skip_whitespace();
    auto value = parse_value(0);
    if (!value)
      return value.error();
    skip_whitespace();
    if (!at_end())
      return error(serialization_errc::invalid_syntax,
                   "unexpected characters after the JSON value");
    return value;
  }

private:
  [[nodiscard]] bool at_end() const noexcept {
    return position_ >= input_.size();
  }
  [[nodiscard]] char peek() const noexcept {
    return at_end() ? '\0' : input_[position_];
  }

  serialization_error error(serialization_errc code,
                            std::string message) const {
    return make_serialization_error(code, std::move(message), {}, position_);
  }

  void skip_whitespace() noexcept {
    while (!at_end()) {
      const char c = peek();
      if (c != ' ' && c != '\t' && c != '\n' && c != '\r')
        break;
      ++position_;
    }
  }

  bool consume(char expected) noexcept {
    if (peek() != expected)
      return false;
    ++position_;
    return true;
  }

  bool consume_literal(std::string_view literal) noexcept {
    if (input_.substr(position_, literal.size()) != literal)
      return false;
    position_ += literal.size();
    return true;
  }

  serialization_result<serialization_value> parse_value(std::size_t depth) {
    skip_whitespace();
    const auto start = position_;
    auto value = parse_value_impl(depth);
    if (value)
      value->source_offset(start);
    return value;
  }

  serialization_result<serialization_value>
  parse_value_impl(std::size_t depth) {
    if (depth > options_.max_depth)
      return error(serialization_errc::depth_limit_exceeded,
                   "maximum JSON nesting depth exceeded");
    switch (peek()) {
    case 'n':
      if (!consume_literal("null"))
        return error(serialization_errc::invalid_syntax,
                     "invalid null literal");
      return serialization_value(nullptr);
    case 't':
      if (!consume_literal("true"))
        return error(serialization_errc::invalid_syntax,
                     "invalid boolean literal");
      return serialization_value(true);
    case 'f':
      if (!consume_literal("false"))
        return error(serialization_errc::invalid_syntax,
                     "invalid boolean literal");
      return serialization_value(false);
    case '"': {
      auto string = parse_string();
      if (!string)
        return string.error();
      return serialization_value(std::move(*string));
    }
    case '[':
      if (depth >= options_.max_depth)
        return error(serialization_errc::depth_limit_exceeded,
                     "maximum JSON nesting depth exceeded");
      return parse_array(depth + 1);
    case '{':
      if (depth >= options_.max_depth)
        return error(serialization_errc::depth_limit_exceeded,
                     "maximum JSON nesting depth exceeded");
      return parse_object(depth + 1);
    default:
      if (peek() == '-' || (peek() >= '0' && peek() <= '9'))
        return parse_number();
      if (at_end())
        return error(serialization_errc::unexpected_end,
                     "expected a JSON value");
      return error(serialization_errc::invalid_syntax, "invalid JSON value");
    }
  }

  serialization_result<serialization_value> parse_array(std::size_t depth) {
    consume('[');
    skip_whitespace();
    serialization_value::array array;
    if (consume(']'))
      return serialization_value(std::move(array));
    for (;;) {
      if (array.size() >= options_.max_container_size)
        return error(serialization_errc::size_limit_exceeded,
                     "JSON array exceeds the configured size limit");
      auto item = parse_value(depth);
      if (!item)
        return item.error();
      array.emplace_back(std::move(*item));
      skip_whitespace();
      if (consume(']'))
        break;
      if (!consume(','))
        return error(serialization_errc::invalid_syntax,
                     "expected ',' or ']' in array");
      skip_whitespace();
    }
    return serialization_value(std::move(array));
  }

  serialization_result<serialization_value> parse_object(std::size_t depth) {
    consume('{');
    skip_whitespace();
    serialization_value::object object;
    if (consume('}'))
      return serialization_value(std::move(object));
    for (;;) {
      if (object.size() >= options_.max_container_size)
        return error(serialization_errc::size_limit_exceeded,
                     "JSON object exceeds the configured size limit");
      if (peek() != '"')
        return error(serialization_errc::invalid_syntax,
                     "expected a string object key");
      auto key = parse_string();
      if (!key)
        return key.error();
      skip_whitespace();
      if (!consume(':'))
        return error(serialization_errc::invalid_syntax,
                     "expected ':' after object key");
      auto value = parse_value(depth);
      if (!value)
        return value.error();
      object.emplace_back(std::move(*key), std::move(*value));
      skip_whitespace();
      if (consume('}'))
        break;
      if (!consume(','))
        return error(serialization_errc::invalid_syntax,
                     "expected ',' or '}' in object");
      skip_whitespace();
    }
    return serialization_value(std::move(object));
  }

  serialization_result<std::uint32_t> parse_hex4() {
    if (input_.size() - position_ < 4)
      return error(serialization_errc::unexpected_end,
                   "incomplete Unicode escape");
    std::uint32_t value = 0;
    for (unsigned i = 0; i < 4; ++i) {
      const char c = input_[position_++];
      value <<= 4;
      if (c >= '0' && c <= '9')
        value |= static_cast<std::uint32_t>(c - '0');
      else if (c >= 'a' && c <= 'f')
        value |= static_cast<std::uint32_t>(c - 'a' + 10);
      else if (c >= 'A' && c <= 'F')
        value |= static_cast<std::uint32_t>(c - 'A' + 10);
      else
        return error(serialization_errc::invalid_escape,
                     "invalid Unicode escape");
    }
    return value;
  }

  serialization_result<std::string> parse_string() {
    consume('"');
    std::string output;
    while (!at_end()) {
      const unsigned char c = static_cast<unsigned char>(input_[position_++]);
      if (c == '"') {
        if (!is_valid_utf8(output))
          return error(serialization_errc::invalid_utf8,
                       "string is not valid UTF-8");
        return output;
      }
      if (c < 0x20)
        return error(serialization_errc::invalid_syntax,
                     "unescaped control character in string");
      if (c != '\\') {
        output.push_back(static_cast<char>(c));
      } else {
        if (at_end())
          return error(serialization_errc::unexpected_end,
                       "incomplete string escape");
        switch (input_[position_++]) {
        case '"':
          output.push_back('"');
          break;
        case '\\':
          output.push_back('\\');
          break;
        case '/':
          output.push_back('/');
          break;
        case 'b':
          output.push_back('\b');
          break;
        case 'f':
          output.push_back('\f');
          break;
        case 'n':
          output.push_back('\n');
          break;
        case 'r':
          output.push_back('\r');
          break;
        case 't':
          output.push_back('\t');
          break;
        case 'u': {
          auto first = parse_hex4();
          if (!first)
            return first.error();
          std::uint32_t code_point = *first;
          if (code_point >= 0xd800 && code_point <= 0xdbff) {
            if (!consume('\\') || !consume('u'))
              return error(
                  serialization_errc::invalid_escape,
                  "high surrogate must be followed by a low surrogate");
            auto second = parse_hex4();
            if (!second)
              return second.error();
            if (*second < 0xdc00 || *second > 0xdfff)
              return error(serialization_errc::invalid_escape,
                           "invalid low surrogate");
            code_point =
                0x10000 + ((code_point - 0xd800) << 10) + (*second - 0xdc00);
          } else if (code_point >= 0xdc00 && code_point <= 0xdfff) {
            return error(serialization_errc::invalid_escape,
                         "unexpected low surrogate");
          }
          append_utf8(output, code_point);
          break;
        }
        default:
          return error(serialization_errc::invalid_escape,
                       "invalid string escape");
        }
      }
      if (output.size() > options_.max_string_size)
        return error(serialization_errc::size_limit_exceeded,
                     "JSON string exceeds the configured size limit");
    }
    return error(serialization_errc::unexpected_end, "unterminated string");
  }

  serialization_result<serialization_value> parse_number() {
    const std::size_t start = position_;
    consume('-');
    if (consume('0')) {
      if (peek() >= '0' && peek() <= '9')
        return error(serialization_errc::invalid_number,
                     "leading zero in JSON number");
    } else {
      if (peek() < '1' || peek() > '9')
        return error(serialization_errc::invalid_number, "invalid JSON number");
      while (peek() >= '0' && peek() <= '9')
        ++position_;
    }
    bool floating = false;
    if (consume('.')) {
      floating = true;
      if (peek() < '0' || peek() > '9')
        return error(serialization_errc::invalid_number,
                     "fraction requires at least one digit");
      while (peek() >= '0' && peek() <= '9')
        ++position_;
    }
    if (peek() == 'e' || peek() == 'E') {
      floating = true;
      ++position_;
      if (peek() == '+' || peek() == '-')
        ++position_;
      if (peek() < '0' || peek() > '9')
        return error(serialization_errc::invalid_number,
                     "exponent requires at least one digit");
      while (peek() >= '0' && peek() <= '9')
        ++position_;
    }

    const auto token = input_.substr(start, position_ - start);
    if (!floating) {
      if (!token.empty() && token.front() == '-') {
        std::int64_t integer = 0;
        const auto parsed =
            std::from_chars(token.data(), token.data() + token.size(), integer);
        if (parsed.ec == std::errc{} &&
            parsed.ptr == token.data() + token.size())
          return serialization_value(integer);
      } else {
        std::uint64_t integer = 0;
        const auto parsed =
            std::from_chars(token.data(), token.data() + token.size(), integer);
        if (parsed.ec == std::errc{} &&
            parsed.ptr == token.data() + token.size())
          return serialization_value(integer);
      }
    }

    double number = 0;
    const auto parsed =
        std::from_chars(token.data(), token.data() + token.size(), number,
                        std::chars_format::general);
    if (parsed.ec != std::errc{} || parsed.ptr != token.data() + token.size() ||
        !std::isfinite(number))
      return error(serialization_errc::invalid_number,
                   "JSON number is out of range");
    return serialization_value(number);
  }

  std::string_view input_;
  json_read_options options_;
  std::size_t position_ = 0;
};

inline serialization_result<void> append_json_string(std::string &output,
                                                     std::string_view string,
                                                     std::size_t max_size) {
  if (!is_valid_utf8(string))
    return make_serialization_error(serialization_errc::invalid_utf8,
                                    "string is not valid UTF-8");
  std::size_t encoded_size = 2;
  for (const unsigned char c : string) {
    const std::size_t width =
        c == '"' || c == '\\' || c == '\b' || c == '\f' || c == '\n' ||
                c == '\r' || c == '\t'
            ? 2
            : c < 0x20 ? 6 : 1;
    if (encoded_size > max_size || width > max_size - encoded_size)
      return make_serialization_error(
          serialization_errc::size_limit_exceeded,
          "JSON output exceeds configured limit");
    encoded_size += width;
  }
  if (output.size() > max_size ||
      encoded_size > max_size - output.size())
    return make_serialization_error(serialization_errc::size_limit_exceeded,
                                    "JSON output exceeds configured limit");
  output.reserve(output.size() + encoded_size);
  constexpr char hex[] = "0123456789abcdef";
  output.push_back('"');
  for (const unsigned char c : string) {
    switch (c) {
    case '"':
      output += "\\\"";
      break;
    case '\\':
      output += "\\\\";
      break;
    case '\b':
      output += "\\b";
      break;
    case '\f':
      output += "\\f";
      break;
    case '\n':
      output += "\\n";
      break;
    case '\r':
      output += "\\r";
      break;
    case '\t':
      output += "\\t";
      break;
    default:
      if (c < 0x20) {
        output += "\\u00";
        output.push_back(hex[c >> 4]);
        output.push_back(hex[c & 15]);
      } else
        output.push_back(static_cast<char>(c));
    }
  }
  output.push_back('"');
  return {};
}
class json_writer {
public:
  explicit json_writer(json_write_options options = {}) : options_(options) {}
  serialization_result<void> write_null() { return scalar("null"); }
  serialization_result<void> write_bool(bool v) {
    return scalar(v ? "true" : "false");
  }
  serialization_result<void> write_signed(std::int64_t v) { return number(v); }
  serialization_result<void> write_unsigned(std::uint64_t v) {
    return number(v);
  }
  serialization_result<void> write_floating(double v) {
    if (!std::isfinite(v))
      return make_serialization_error(
          serialization_errc::value_out_of_range,
          "non-finite number cannot be represented");
    char b[64];
    auto c = std::to_chars(b, b + sizeof(b), v, std::chars_format::general,
                           std::numeric_limits<double>::max_digits10);
    if (c.ec != std::errc{})
      return make_serialization_error(serialization_errc::invalid_number,
                                      "failed to format floating point value");
    auto s = before_value();
    if (!s)
      return s;
    return append(std::string_view(b, static_cast<std::size_t>(c.ptr - b)));
  }
  serialization_result<void> write_string(std::string_view v) {
    auto s = before_value();
    if (!s)
      return s;
    return append_json_string(output_, v, options_.max_output_size);
  }
  serialization_result<void> begin_array(std::size_t) { return begin(false); }
  serialization_result<void> end_array() { return end(false); }
  serialization_result<void> begin_object(std::size_t) { return begin(true); }
  serialization_result<void> write_key(std::string_view key) {
    if (stack_.empty() || !stack_.back().object ||
        stack_.back().expecting_value)
      return make_serialization_error(serialization_errc::custom_error,
                                      "object key in invalid archive state");
    auto &f = stack_.back();
    serialization_result<void> s;
    if (f.count && !(s = append_char(',')))
      return s;
    if (options_.pretty) {
      if (!(s = append_char('\n')) || !(s = append_indent(stack_.size())))
        return s;
    }
    if (!(s = append_json_string(output_, key, options_.max_output_size)))
      return s;
    if (!(s = append(options_.pretty ? ": " : ":")))
      return s;
    ++f.count;
    f.expecting_value = true;
    return {};
  }
  serialization_result<void> end_object() { return end(true); }
  serialization_result<std::string> finish() {
    if (finished_)
      return make_serialization_error(serialization_errc::custom_error,
                                      "JSON archive is already finished");
    if (!stack_.empty() || !has_root_)
      return make_serialization_error(serialization_errc::custom_error,
                                      "incomplete JSON archive");
    finished_ = true;
    return std::move(output_);
  }

private:
  struct frame {
    bool object;
    std::size_t count = 0;
    bool expecting_value = false;
  };
  serialization_result<void> before_value() {
    if (finished_)
      return make_serialization_error(serialization_errc::custom_error,
                                      "JSON archive is already finished");
    if (stack_.empty()) {
      if (has_root_)
        return make_serialization_error(serialization_errc::custom_error,
                                        "multiple root values");
      has_root_ = true;
      return {};
    }
    auto &f = stack_.back();
    if (f.object) {
      if (!f.expecting_value)
        return make_serialization_error(serialization_errc::custom_error,
                                        "object value without key");
      f.expecting_value = false;
    } else {
      serialization_result<void> s;
      if (f.count && !(s = append_char(',')))
        return s;
      if (options_.pretty) {
        if (!(s = append_char('\n')) || !(s = append_indent(stack_.size())))
          return s;
      }
      ++f.count;
    }
    return {};
  }
  serialization_result<void> begin(bool object) {
    if (stack_.size() >= options_.max_depth)
      return make_serialization_error(serialization_errc::depth_limit_exceeded,
                                      "maximum JSON output depth exceeded");
    auto s = before_value();
    if (!s)
      return s;
    if (!(s = append_char(object ? '{' : '[')))
      return s;
    stack_.push_back({object});
    return {};
  }
  serialization_result<void> end(bool object) {
    if (stack_.empty() || stack_.back().object != object ||
        stack_.back().expecting_value)
      return make_serialization_error(serialization_errc::custom_error,
                                      "mismatched JSON archive end");
    auto f = stack_.back();
    stack_.pop_back();
    serialization_result<void> s;
    if (options_.pretty && f.count) {
      if (!(s = append_char('\n')) || !(s = append_indent(stack_.size())))
        return s;
    }
    return append_char(object ? '}' : ']');
  }
  serialization_result<void> scalar(std::string_view text) {
    auto s = before_value();
    if (!s)
      return s;
    return append(text);
  }
  template <typename I> serialization_result<void> number(I v) {
    char b[32];
    auto c = std::to_chars(b, b + sizeof(b), v);
    if (c.ec != std::errc{})
      return make_serialization_error(serialization_errc::invalid_number,
                                      "failed to format integer");
    auto s = before_value();
    if (!s)
      return s;
    return append(std::string_view(b, static_cast<std::size_t>(c.ptr - b)));
  }
  serialization_result<void> append(std::string_view text) {
    if (output_.size() > options_.max_output_size ||
        text.size() > options_.max_output_size - output_.size())
      return make_serialization_error(serialization_errc::size_limit_exceeded,
                                      "JSON output exceeds configured limit");
    output_.append(text);
    return {};
  }
  serialization_result<void> append_char(char value) {
    return append(std::string_view(&value, 1));
  }
  serialization_result<void> append_indent(std::size_t depth) {
    if (output_.size() > options_.max_output_size)
      return make_serialization_error(serialization_errc::size_limit_exceeded,
                                      "JSON output exceeds configured limit");
    const auto remaining = options_.max_output_size >= output_.size()
                               ? options_.max_output_size - output_.size()
                               : 0;
    if (depth != 0 && options_.indent_width > remaining / depth)
      return make_serialization_error(serialization_errc::size_limit_exceeded,
                                      "JSON output exceeds configured limit");
    output_.append(depth * options_.indent_width, ' ');
    return {};
  }
  json_write_options options_;
  std::string output_;
  std::vector<frame> stack_;
  bool has_root_ = false;
  bool finished_ = false;
};
} // namespace detail

inline serialization_result<serialization_value>
parse_json(std::string_view input, json_read_options options = {}) {
  return detail::json_parser(input, options).parse();
}
inline serialization_result<std::string>
write_json(const serialization_value &value, json_write_options options = {}) {
  detail::json_writer writer(options);
  auto s = detail::write_serialization_value(writer, value);
  if (!s)
    return s.error();
  return writer.finish();
}
template <typename T>
serialization_result<std::string>
to_json(const T &value, serialization_options serialization = {},
        json_write_options json = {}) {
  detail::json_writer writer(json);
  basic_serializer archive(writer, serialization);
  auto s = archive.encode(value);
  if (!s)
    return s.error();
  return writer.finish();
}
template <typename T>
serialization_result<T> from_json(std::string_view input,
                                  deserialization_options deserialization = {},
                                  json_read_options json = {}) {
  auto value = parse_json(input, json);
  if (!value)
    return value.error();
  return from_serialization_value<T>(*value, deserialization);
}
template <typename T>
std::string to_json_or_throw(const T &value,
                             serialization_options serialization = {},
                             json_write_options json = {}) {
  auto r = to_json(value, serialization, json);
  if (!r)
    throw serialization_exception(r.error());
  return std::move(*r);
}
template <typename T>
T from_json_or_throw(std::string_view input,
                     deserialization_options deserialization = {},
                     json_read_options json = {}) {
  auto r = from_json<T>(input, deserialization, json);
  if (!r)
    throw serialization_exception(r.error());
  return std::move(*r);
}
} // namespace gmp
#endif
