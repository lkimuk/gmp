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

#ifndef GMP_SERIALIZATION_XML_HPP_
#define GMP_SERIALIZATION_XML_HPP_

#include <charconv>
#include <cmath>
#include <cstdint>
#include <limits>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <gmp/serialization/detail/text.hpp>
#include <gmp/serialization/detail/write_value.hpp>
#include <gmp/serialization/serialization.hpp>

namespace gmp::detail {

inline bool is_xml_code_point(std::uint32_t value) noexcept {
  return value == 0x9 || value == 0xa || value == 0xd || (value >= 0x20 && value <= 0xd7ff) ||
         (value >= 0xe000 && value <= 0xfffd) || (value >= 0x10000 && value <= 0x10ffff);
}

inline bool has_only_xml_characters(std::string_view text) noexcept {
  // Keep this helper safe even when called independently of the parser or
  // xml_escape.  In particular, never read continuation bytes past the end of
  // a malformed UTF-8 sequence.
  if (!is_valid_utf8(text)) {
    return false;
  }
  for (std::size_t i = 0; i < text.size();) {
    const auto first = static_cast<unsigned char>(text[i]);
    std::uint32_t code_point = first;
    std::size_t width = 1;
    if (first >= 0xc2 && first <= 0xdf) {
      code_point = first & 0x1f;
      width = 2;
    } else if (first >= 0xe0 && first <= 0xef) {
      code_point = first & 0x0f;
      width = 3;
    } else if (first >= 0xf0 && first <= 0xf4) {
      code_point = first & 0x07;
      width = 4;
    }
    for (std::size_t j = 1; j < width; ++j) {
      code_point = (code_point << 6) | (static_cast<unsigned char>(text[i + j]) & 0x3f);
    }
    if (!is_xml_code_point(code_point)) {
      return false;
    }
    i += width;
  }
  return true;
}

inline serialization_result<void> xml_escape(std::string &out, std::string_view text,
                                             std::size_t limit, bool attribute = false) {
  if (!is_valid_utf8(text)) {
    return make_serialization_error(serialization_errc::invalid_utf8, "string is not valid UTF-8");
  }
  if (!has_only_xml_characters(text)) {
    return make_serialization_error(serialization_errc::value_out_of_range,
                                    "string contains a character forbidden by XML 1.0");
  }
  for (const char c : text) {
    std::string_view replacement;
    switch (c) {
    case '&':
      replacement = "&amp;";
      break;
    case '<':
      replacement = "&lt;";
      break;
    case '>':
      replacement = "&gt;";
      break;
    case '"':
      if (attribute) {
        replacement = "&quot;";
      }
      break;
    case '\'':
      if (attribute) {
        replacement = "&apos;";
      }
      break;
    case '\t':
      if (attribute) {
        replacement = "&#x9;";
      }
      break;
    case '\n':
      if (attribute) {
        replacement = "&#xA;";
      }
      break;
    case '\r':
      replacement = "&#xD;";
      break;
    default:
      break;
    }
    if (replacement.empty()) {
      if (out.size() >= limit) {
        return make_serialization_error(serialization_errc::size_limit_exceeded,
                                        "XML output exceeds configured limit");
      }
      out.push_back(c);
    } else {
      if (out.size() > limit || replacement.size() > limit - out.size()) {
        return make_serialization_error(serialization_errc::size_limit_exceeded,
                                        "XML output exceeds configured limit");
      }
      out += replacement;
    }
  }
  return {};
}

class xml_writer {
public:
  explicit xml_writer(xml_write_options options = {}) : options_(options) {}

  serialization_result<void> write_null() {
    auto status = before_value();
    if (!status) {
      return status;
    }
    if (!(status = append("<value kind=\"null\"/>"))) {
      return status;
    }
    return complete_value();
  }

  serialization_result<void> write_bool(bool value) {
    return scalar(value ? "true" : "false", "boolean");
  }

  serialization_result<void> write_signed(std::int64_t value) {
    return number(value, "signed");
  }

  serialization_result<void> write_unsigned(std::uint64_t value) {
    return number(value, "unsigned");
  }

  serialization_result<void> write_floating(double value) {
    if (!std::isfinite(value)) {
      return make_serialization_error(serialization_errc::value_out_of_range,
                                      "non-finite number cannot be represented");
    }
    char buffer[64];
    const auto result =
        std::to_chars(buffer, buffer + sizeof(buffer), value, std::chars_format::general,
                      std::numeric_limits<double>::max_digits10);
    if (result.ec != std::errc{}) {
      return make_serialization_error(serialization_errc::invalid_number,
                                      "failed to format floating point value");
    }
    return scalar(std::string_view(buffer, result.ptr - buffer), "floating");
  }

  serialization_result<void> write_string(std::string_view value) {
    return scalar(value, "string", true);
  }

  serialization_result<void> begin_array(std::size_t) {
    return begin("array");
  }

  serialization_result<void> end_array() {
    return end("array");
  }

  serialization_result<void> begin_object(std::size_t) {
    return begin("object");
  }

  serialization_result<void> write_key(std::string_view key) {
    if (stack_.empty() || stack_.back().kind != "object" || stack_.back().expecting_value) {
      return make_serialization_error(serialization_errc::custom_error,
                                      "object key in invalid archive state");
    }
    serialization_result<void> status;
    if (options_.pretty && !(status = newline_and_indent(stack_.back().value_depth + 1))) {
      return status;
    }
    status = append("<member name=\"");
    if (!status) {
      return status;
    }
    if (!(status = xml_escape(output_, key, options_.max_output_size, true))) {
      return status;
    }
    if (!(status = append("\">"))) {
      return status;
    }
    stack_.back().expecting_value = true;
    return {};
  }

  serialization_result<void> end_object() {
    return end("object");
  }

  serialization_result<std::string> finish() {
    if (finished_) {
      return make_serialization_error(serialization_errc::custom_error,
                                      "XML archive is already finished");
    }
    if (!stack_.empty() || !has_root_) {
      return make_serialization_error(serialization_errc::custom_error, "incomplete XML archive");
    }
    serialization_result<void> status;
    if (options_.pretty) {
      status = newline_and_indent(0);
      if (!status) {
        return status.error();
      }
      status = append("</gmp>");
    } else {
      status = append("</gmp>");
    }
    if (!status) {
      return status.error();
    }
    finished_ = true;
    return std::move(output_);
  }

private:
  struct frame {
    std::string_view kind;
    bool expecting_value = false;
    std::size_t count = 0;
    std::size_t value_depth = 0;
  };

  serialization_result<void> append(std::string_view text) {
    if (output_.size() > options_.max_output_size ||
        text.size() > options_.max_output_size - output_.size()) {
      return make_serialization_error(serialization_errc::size_limit_exceeded,
                                      "XML output exceeds configured limit");
    }
    output_ += text;
    return {};
  }

  serialization_result<void> before_value() {
    if (finished_) {
      return make_serialization_error(serialization_errc::custom_error,
                                      "XML archive is already finished");
    }
    if (stack_.empty()) {
      if (has_root_) {
        return make_serialization_error(serialization_errc::custom_error, "multiple root values");
      }
      if (!document_open_) {
        auto status = append("<gmp version=\"1\">");
        if (!status) {
          return status;
        }
        document_open_ = true;
      }
      if (options_.pretty) {
        auto status = newline_and_indent(1);
        if (!status) {
          return status;
        }
      }
      return {};
    }
    auto &parent = stack_.back();
    if (parent.kind == "object" && !parent.expecting_value) {
      return make_serialization_error(serialization_errc::custom_error, "object value without key");
    }
    if (options_.pretty && parent.kind == "array") {
      return newline_and_indent(parent.value_depth + 1);
    }
    return {};
  }

  serialization_result<void> complete_value() {
    if (stack_.empty()) {
      has_root_ = true;
      return {};
    }
    auto &parent = stack_.back();
    if (parent.kind == "object") {
      auto status = append("</member>");
      if (!status) {
        return status;
      }
      parent.expecting_value = false;
    }
    ++parent.count;
    return {};
  }

  serialization_result<void> newline_and_indent(std::size_t depth) {
    auto status = append("\n");
    if (!status) {
      return status;
    }
    if (output_.size() > options_.max_output_size) {
      return make_serialization_error(serialization_errc::size_limit_exceeded,
                                      "XML output exceeds configured limit");
    }
    const auto remaining = options_.max_output_size - output_.size();
    if (depth != 0 && options_.indent_width > remaining / depth) {
      return make_serialization_error(serialization_errc::size_limit_exceeded,
                                      "XML output exceeds configured limit");
    }
    output_.append(depth * options_.indent_width, ' ');
    return {};
  }

  std::size_t next_value_depth() const noexcept {
    if (stack_.empty()) {
      return 1;
    }
    const auto &parent = stack_.back();
    return parent.value_depth + (parent.kind == "object" ? 2 : 1);
  }

  serialization_result<void> scalar(std::string_view value, std::string_view kind,
                                    bool escape_text = false) {
    auto status = before_value();
    if (!status) {
      return status;
    }
    status = append("<value kind=\"");
    if (!status) {
      return status;
    }
    status = append(kind);
    if (!status) {
      return status;
    }
    status = append("\">");
    if (!status) {
      return status;
    }
    if (escape_text) {
      status = xml_escape(output_, value, options_.max_output_size);
    } else {
      status = append(value);
    }
    if (!status) {
      return status;
    }
    status = append("</value>");
    if (!status) {
      return status;
    }
    return complete_value();
  }

  template <typename I> serialization_result<void> number(I value, std::string_view kind) {
    char buffer[32];
    const auto result = std::to_chars(buffer, buffer + sizeof(buffer), value);
    if (result.ec != std::errc{}) {
      return make_serialization_error(serialization_errc::invalid_number,
                                      "failed to format integer");
    }
    return scalar(std::string_view(buffer, result.ptr - buffer), kind);
  }

  serialization_result<void> begin(std::string_view kind) {
    if (stack_.size() >= options_.max_depth) {
      return make_serialization_error(serialization_errc::depth_limit_exceeded,
                                      "maximum XML output depth exceeded");
    }
    const auto value_depth = next_value_depth();
    auto status = before_value();
    if (!status) {
      return status;
    }
    if (!(status = append("<value kind=\"")) || !(status = append(kind)) ||
        !(status = append("\">"))) {
      return status;
    }
    stack_.push_back({kind, false, 0, value_depth});
    return {};
  }

  serialization_result<void> end(std::string_view kind) {
    if (stack_.empty() || stack_.back().kind != kind || stack_.back().expecting_value) {
      return make_serialization_error(serialization_errc::custom_error,
                                      "mismatched XML archive end");
    }
    const auto frame = stack_.back();
    stack_.pop_back();
    serialization_result<void> status;
    if (options_.pretty && frame.count && !(status = newline_and_indent(frame.value_depth))) {
      return status;
    }
    status = append("</value>");
    if (!status) {
      return status;
    }
    return complete_value();
  }

  xml_write_options options_;
  std::string output_;
  std::vector<frame> stack_;
  bool has_root_ = false;
  bool document_open_ = false;
  bool finished_ = false;
};

class xml_parser {
public:
  xml_parser(std::string_view input, xml_read_options options) : input_(input), options_(options) {}

  serialization_result<serialization_value> parse() {
    if (input_.size() > options_.max_input_size) {
      return error(serialization_errc::size_limit_exceeded,
                   "XML input exceeds the configured size limit");
    }
    if (!is_valid_utf8(input_)) {
      return error(serialization_errc::invalid_utf8, "XML input is not valid UTF-8");
    }
    if (starts("\xef\xbb\xbf")) {
      position_ += 3;
    }
    if (starts("<?xml")) {
      auto declaration = parse_declaration();
      if (!declaration) {
        return declaration.error();
      }
    }
    skip_space();
    if (starts("<!DOCTYPE")) {
      return error(serialization_errc::unsupported_type,
                   "XML DTDs and external entities are not supported");
    }
    if (!consume("<gmp")) {
      return error(serialization_errc::invalid_syntax, "expected GMP XML document element");
    }
    if (position_ >= input_.size() || (input_[position_] != ' ' && input_[position_] != '\t' &&
                                       input_[position_] != '\r' && input_[position_] != '\n')) {
      return error(serialization_errc::invalid_syntax,
                   "expected whitespace after GMP XML document name");
    }
    auto version = attribute("version");
    if (!version) {
      return version.error();
    }
    if (*version != "1") {
      return error(serialization_errc::unsupported_type, "unsupported GMP XML format version");
    }
    skip_space();
    if (!consume(">")) {
      return error(serialization_errc::invalid_syntax, "expected GMP XML document close");
    }
    skip_space();
    auto value = parse_node(0);
    if (!value) {
      return value.error();
    }
    skip_space();
    if (!consume("</gmp>")) {
      return error(serialization_errc::invalid_syntax, "expected GMP XML document end");
    }
    skip_space();
    if (position_ != input_.size()) {
      return error(serialization_errc::invalid_syntax, "unexpected characters after XML value");
    }
    return value;
  }

private:
  serialization_error error(serialization_errc code, std::string message) const {
    return make_serialization_error(code, std::move(message), {}, position_);
  }

  bool starts(std::string_view text) const {
    return input_.substr(position_, text.size()) == text;
  }

  static bool is_space(char value) noexcept {
    return value == ' ' || value == '\t' || value == '\r' || value == '\n';
  }

  void skip_space() {
    while (position_ < input_.size() && is_space(input_[position_])) {
      ++position_;
    }
  }

  bool consume(std::string_view text) {
    if (!starts(text)) {
      return false;
    }
    position_ += text.size();
    return true;
  }

  serialization_result<std::string> declaration_attribute(std::string_view expected) {
    if (!consume(expected)) {
      return error(serialization_errc::invalid_syntax, "invalid XML declaration attribute order");
    }
    skip_space();
    if (!consume("=")) {
      return error(serialization_errc::invalid_syntax, "expected '=' in XML declaration");
    }
    skip_space();
    if (position_ >= input_.size() || (input_[position_] != '"' && input_[position_] != '\'')) {
      return error(serialization_errc::invalid_syntax, "expected quoted XML declaration value");
    }
    const char quote = input_[position_++];
    const auto start = position_;
    while (position_ < input_.size() && input_[position_] != quote) {
      const auto c = static_cast<unsigned char>(input_[position_]);
      if (c >= 0x80 || !is_xml_code_point(c) || input_[position_] == '<' ||
          input_[position_] == '&') {
        return error(serialization_errc::invalid_syntax, "invalid XML declaration value");
      }
      ++position_;
    }
    if (position_ >= input_.size()) {
      return error(serialization_errc::unexpected_end, "unterminated XML declaration value");
    }
    std::string value(input_.substr(start, position_ - start));
    ++position_;
    return value;
  }

  static bool ascii_iequal(std::string_view left, std::string_view right) noexcept {
    if (left.size() != right.size()) {
      return false;
    }
    for (std::size_t i = 0; i < left.size(); ++i) {
      auto a = left[i];
      auto b = right[i];
      if (a >= 'A' && a <= 'Z') {
        a = static_cast<char>(a - 'A' + 'a');
      }
      if (b >= 'A' && b <= 'Z') {
        b = static_cast<char>(b - 'A' + 'a');
      }
      if (a != b) {
        return false;
      }
    }
    return true;
  }

  serialization_result<void> parse_declaration() {
    consume("<?xml");
    if (position_ >= input_.size() || !is_space(input_[position_])) {
      return error(serialization_errc::invalid_syntax, "XML declaration requires a version");
    }
    skip_space();
    auto version = declaration_attribute("version");
    if (!version) {
      return version.error();
    }
    if (*version != "1.0") {
      return error(serialization_errc::unsupported_type, "only XML 1.0 is supported");
    }
    bool has_encoding = false;
    bool has_standalone = false;
    for (;;) {
      const auto before_space = position_;
      skip_space();
      const bool separated = position_ != before_space;
      if (consume("?>")) {
        return {};
      }
      if (!separated) {
        return error(serialization_errc::invalid_syntax,
                     "XML declaration attributes must be separated");
      }
      if (starts("encoding")) {
        if (has_encoding || has_standalone) {
          return error(serialization_errc::invalid_syntax,
                       "invalid XML declaration attribute order");
        }
        auto encoding = declaration_attribute("encoding");
        if (!encoding) {
          return encoding.error();
        }
        if (!ascii_iequal(*encoding, "UTF-8")) {
          return error(serialization_errc::unsupported_type, "only UTF-8 XML input is supported");
        }
        has_encoding = true;
      } else if (starts("standalone")) {
        if (has_standalone) {
          return error(serialization_errc::invalid_syntax, "duplicate XML standalone declaration");
        }
        auto standalone = declaration_attribute("standalone");
        if (!standalone) {
          return standalone.error();
        }
        if (*standalone != "yes" && *standalone != "no") {
          return error(serialization_errc::invalid_syntax, "invalid XML standalone declaration");
        }
        has_standalone = true;
      } else {
        return error(serialization_errc::invalid_syntax, "unknown XML declaration attribute");
      }
    }
  }

  serialization_result<std::string> entity() {
    const auto start = position_;
    const auto end = input_.find(';', position_);
    if (end == std::string_view::npos) {
      return error(serialization_errc::unexpected_end, "unterminated XML entity");
    }
    position_ = end + 1;
    const auto name = input_.substr(start, end - start);
    if (name == "amp") {
      return std::string("&");
    }
    if (name == "lt") {
      return std::string("<");
    }
    if (name == "gt") {
      return std::string(">");
    }
    if (name == "quot") {
      return std::string("\"");
    }
    if (name == "apos") {
      return std::string("'");
    }
    if (!name.empty() && name.front() == '#') {
      std::uint32_t code_point = 0;
      std::string_view digits = name.substr(1);
      int base = 10;
      if (!digits.empty() && digits.front() == 'x') {
        base = 16;
        digits.remove_prefix(1);
      }
      const auto parsed =
          std::from_chars(digits.data(), digits.data() + digits.size(), code_point, base);
      if (digits.empty() || parsed.ec != std::errc{} ||
          parsed.ptr != digits.data() + digits.size() || !is_xml_code_point(code_point)) {
        return error(serialization_errc::invalid_escape, "invalid XML character reference");
      }
      std::string result;
      append_utf8(result, code_point);
      return result;
    }
    return error(serialization_errc::invalid_escape, "unknown XML entity");
  }

  serialization_result<std::string> text_until_tag() {
    std::string text;
    while (position_ < input_.size() && input_[position_] != '<') {
      if (starts("]]>")) {
        return error(serialization_errc::invalid_syntax,
                     "']]>' is not allowed in XML character data");
      }
      if (input_[position_] == '&') {
        ++position_;
        auto part = entity();
        if (!part) {
          return part.error();
        }
        text += *part;
      } else {
        if (input_[position_] == '\r') {
          ++position_;
          if (position_ < input_.size() && input_[position_] == '\n') {
            ++position_;
          }
          text.push_back('\n');
        } else {
          text.push_back(input_[position_++]);
        }
      }
      if (text.size() > options_.max_string_size) {
        return error(serialization_errc::size_limit_exceeded,
                     "XML text exceeds the configured size limit");
      }
    }
    if (!is_valid_utf8(text)) {
      return error(serialization_errc::invalid_utf8, "XML text is not valid UTF-8");
    }
    if (!has_only_xml_characters(text)) {
      return error(serialization_errc::invalid_syntax, "XML text contains a forbidden character");
    }
    return text;
  }

  serialization_result<std::string> attribute(std::string_view expected) {
    skip_space();
    if (!consume(expected)) {
      return error(serialization_errc::invalid_syntax, "expected XML attribute");
    }
    skip_space();
    if (!consume("=")) {
      return error(serialization_errc::invalid_syntax, "expected quoted XML attribute");
    }
    skip_space();
    if (position_ >= input_.size() || (input_[position_] != '\"' && input_[position_] != '\'')) {
      return error(serialization_errc::invalid_syntax, "expected quoted XML attribute");
    }
    const char quote = input_[position_++];
    std::string value;
    while (position_ < input_.size() && input_[position_] != quote) {
      if (input_[position_] == '&') {
        ++position_;
        auto part = entity();
        if (!part) {
          return part.error();
        }
        value += *part;
      } else {
        if (input_[position_] == '<') {
          return error(serialization_errc::invalid_syntax,
                       "'<' is not allowed in an XML attribute");
        }
        if (input_[position_] == '\r') {
          ++position_;
          if (position_ < input_.size() && input_[position_] == '\n') {
            ++position_;
          }
          value.push_back(' ');
        } else if (input_[position_] == '\n' || input_[position_] == '\t') {
          ++position_;
          value.push_back(' ');
        } else {
          value.push_back(input_[position_++]);
        }
      }
      if (value.size() > options_.max_string_size) {
        return error(serialization_errc::size_limit_exceeded,
                     "XML attribute exceeds the configured size limit");
      }
    }
    if (position_ >= input_.size() || input_[position_] != quote) {
      return error(serialization_errc::unexpected_end, "unterminated XML attribute");
    }
    ++position_;
    if (!is_valid_utf8(value)) {
      return error(serialization_errc::invalid_utf8, "XML attribute is not valid UTF-8");
    }
    if (!has_only_xml_characters(value)) {
      return error(serialization_errc::invalid_syntax,
                   "XML attribute contains a forbidden character");
    }
    return value;
  }

  serialization_result<serialization_value> parse_node(std::size_t depth) {
    const auto source_offset = position_;
    if (!consume("<value")) {
      return error(serialization_errc::invalid_syntax, "expected XML value element");
    }
    if (position_ >= input_.size() || (input_[position_] != ' ' && input_[position_] != '\t' &&
                                       input_[position_] != '\r' && input_[position_] != '\n')) {
      return error(serialization_errc::invalid_syntax,
                   "expected whitespace after XML element name");
    }
    auto kind = attribute("kind");
    if (!kind) {
      return kind.error();
    }
    skip_space();
    if (consume("/>")) {
      if (*kind != "null") {
        return error(serialization_errc::invalid_syntax,
                     "only null XML values may be self-closing");
      }
      serialization_value result(nullptr);
      result.source_offset(source_offset);
      return result;
    }
    if (!consume(">")) {
      return error(serialization_errc::invalid_syntax, "expected XML value close");
    }
    serialization_value result;
    if (*kind == "array") {
      if (depth >= options_.max_depth) {
        return error(serialization_errc::depth_limit_exceeded,
                     "maximum XML nesting depth exceeded");
      }
      serialization_value::array values;
      skip_space();
      while (!starts("</value>")) {
        if (values.size() >= options_.max_container_size) {
          return error(serialization_errc::size_limit_exceeded,
                       "XML array exceeds the configured size limit");
        }
        auto item = parse_node(depth + 1);
        if (!item) {
          return item.error();
        }
        values.push_back(std::move(*item));
        skip_space();
      }
      consume("</value>");
      result = serialization_value(std::move(values));
    } else if (*kind == "object") {
      if (depth >= options_.max_depth) {
        return error(serialization_errc::depth_limit_exceeded,
                     "maximum XML nesting depth exceeded");
      }
      serialization_value::object values;
      skip_space();
      while (!starts("</value>")) {
        if (values.size() >= options_.max_container_size) {
          return error(serialization_errc::size_limit_exceeded,
                       "XML object exceeds the configured size limit");
        }
        if (!consume("<member")) {
          return error(serialization_errc::invalid_syntax, "expected XML object member");
        }
        if (position_ >= input_.size() ||
            (input_[position_] != ' ' && input_[position_] != '\t' && input_[position_] != '\r' &&
             input_[position_] != '\n')) {
          return error(serialization_errc::invalid_syntax,
                       "expected whitespace after XML member name");
        }
        auto name = attribute("name");
        if (!name) {
          return name.error();
        }
        skip_space();
        if (!consume(">")) {
          return error(serialization_errc::invalid_syntax, "expected XML member close");
        }
        skip_space();
        auto item = parse_node(depth + 1);
        if (!item) {
          return item.error();
        }
        skip_space();
        if (!consume("</member>")) {
          return error(serialization_errc::invalid_syntax, "expected XML member end");
        }
        values.emplace_back(std::move(*name), std::move(*item));
        skip_space();
      }
      consume("</value>");
      result = serialization_value(std::move(values));
    } else {
      auto text = text_until_tag();
      if (!text) {
        return text.error();
      }
      if (!consume("</value>")) {
        return error(serialization_errc::invalid_syntax, "expected XML value end");
      }
      if (*kind == "string") {
        result = serialization_value(std::move(*text));
      } else if (*kind == "boolean") {
        if (*text != "true" && *text != "false") {
          return error(serialization_errc::invalid_syntax, "invalid XML boolean");
        }
        result = serialization_value(*text == "true");
      } else if (*kind == "signed") {
        std::int64_t number = 0;
        const auto parsed = std::from_chars(text->data(), text->data() + text->size(), number);
        if (parsed.ec != std::errc{} || parsed.ptr != text->data() + text->size()) {
          return error(serialization_errc::invalid_number, "invalid XML signed integer");
        }
        result = serialization_value(number);
      } else if (*kind == "unsigned") {
        std::uint64_t number = 0;
        const auto parsed = std::from_chars(text->data(), text->data() + text->size(), number);
        if (parsed.ec != std::errc{} || parsed.ptr != text->data() + text->size()) {
          return error(serialization_errc::invalid_number, "invalid XML unsigned integer");
        }
        result = serialization_value(number);
      } else if (*kind == "floating") {
        double number = 0;
        const auto parsed = std::from_chars(text->data(), text->data() + text->size(), number,
                                            std::chars_format::general);
        if (parsed.ec != std::errc{} || parsed.ptr != text->data() + text->size() ||
            !std::isfinite(number)) {
          return error(serialization_errc::invalid_number, "invalid XML floating point value");
        }
        result = serialization_value(number);
      } else {
        return error(serialization_errc::invalid_syntax, "unknown XML value kind");
      }
    }
    result.source_offset(source_offset);
    return result;
  }

  std::string_view input_;
  xml_read_options options_;
  std::size_t position_ = 0;
};

} // namespace gmp::detail

namespace gmp {

inline serialization_result<serialization_value> parse_xml(std::string_view input,
                                                           xml_read_options options = {}) {
  return detail::xml_parser(input, options).parse();
}

inline serialization_result<std::string> write_xml(const serialization_value &value,
                                                   xml_write_options options = {}) {
  detail::xml_writer writer(options);
  auto status = detail::write_serialization_value(writer, value);
  if (!status) {
    return status.error();
  }
  return writer.finish();
}

template <typename T>
serialization_result<std::string> to_xml(const T &value, serialization_options serialization = {},
                                         xml_write_options xml = {}) {
  detail::xml_writer writer(xml);
  basic_serializer archive(writer, serialization);
  auto status = archive.encode(value);
  if (!status) {
    return status.error();
  }
  return writer.finish();
}

template <typename T>
serialization_result<T> from_xml(std::string_view input,
                                 deserialization_options deserialization = {},
                                 xml_read_options xml = {}) {
  auto value = parse_xml(input, xml);
  if (!value) {
    return value.error();
  }
  return from_serialization_value<T>(*value, deserialization);
}

template <typename T>
std::string to_xml_or_throw(const T &value, serialization_options serialization = {},
                            xml_write_options xml = {}) {
  auto result = to_xml(value, serialization, xml);
  if (!result) {
    throw serialization_exception(result.error());
  }
  return std::move(*result);
}

template <typename T>
T from_xml_or_throw(std::string_view input, deserialization_options deserialization = {},
                    xml_read_options xml = {}) {
  auto result = from_xml<T>(input, deserialization, xml);
  if (!result) {
    throw serialization_exception(result.error());
  }
  return std::move(*result);
}

} // namespace gmp

#endif // GMP_SERIALIZATION_XML_HPP_
