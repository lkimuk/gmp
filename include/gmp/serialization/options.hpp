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

#ifndef GMP_SERIALIZATION_OPTIONS_HPP_
#define GMP_SERIALIZATION_OPTIONS_HPP_

#include <cstddef>
namespace gmp {
enum class unknown_field_policy { reject, ignore };
enum class duplicate_field_policy { reject, keep_first, keep_last };
enum class duplicate_element_policy { reject, ignore };
enum class enum_encoding { name, underlying };
enum class enum_decoding { name, underlying, name_or_underlying };
struct serialization_options {
  enum_encoding enums = enum_encoding::name;
  std::size_t max_depth = 128;
  std::size_t max_container_size = 1'000'000;
};
struct deserialization_options {
  unknown_field_policy unknown_fields = unknown_field_policy::reject;
  duplicate_field_policy duplicate_fields = duplicate_field_policy::reject;
  duplicate_element_policy duplicate_elements =
      duplicate_element_policy::reject;
  enum_decoding enums = enum_decoding::name;
  std::size_t max_depth = 128;
  std::size_t max_container_size = 1'000'000;
};
struct json_write_options {
  bool pretty = false;
  unsigned indent_width = 2;
  std::size_t max_depth = 128;
  std::size_t max_output_size = 64 * 1024 * 1024;
};
struct json_read_options {
  std::size_t max_depth = 128;
  std::size_t max_input_size = 64 * 1024 * 1024;
  std::size_t max_string_size = 16 * 1024 * 1024;
  std::size_t max_container_size = 1'000'000;
};
struct xml_write_options {
  bool pretty = false;
  unsigned indent_width = 2;
  std::size_t max_depth = 128;
  std::size_t max_output_size = 64 * 1024 * 1024;
};
struct xml_read_options {
  std::size_t max_depth = 128;
  std::size_t max_input_size = 64 * 1024 * 1024;
  std::size_t max_string_size = 16 * 1024 * 1024;
  std::size_t max_container_size = 1'000'000;
};
} // namespace gmp
#endif
