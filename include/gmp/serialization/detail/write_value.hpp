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

#ifndef GMP_SERIALIZATION_DETAIL_WRITE_VALUE_HPP_
#define GMP_SERIALIZATION_DETAIL_WRITE_VALUE_HPP_

#include <concepts>
#include <type_traits>
#include <variant>

#include <gmp/serialization/archive.hpp>
#include <gmp/serialization/value.hpp>

namespace gmp::detail {

template <serialization_writer Writer>
serialization_result<void> write_serialization_value(Writer &writer,
                                                     const serialization_value &value) {
  return std::visit(
      [&](const auto &item) -> serialization_result<void> {
        using T = std::remove_cvref_t<decltype(item)>;
        if constexpr (std::same_as<T, serialization_value::null_t>)
          return writer.write_null();
        else if constexpr (std::same_as<T, bool>)
          return writer.write_bool(item);
        else if constexpr (std::same_as<T, std::int64_t>)
          return writer.write_signed(item);
        else if constexpr (std::same_as<T, std::uint64_t>)
          return writer.write_unsigned(item);
        else if constexpr (std::same_as<T, double>)
          return writer.write_floating(item);
        else if constexpr (std::same_as<T, std::string>)
          return writer.write_string(item);
        else if constexpr (std::same_as<T, serialization_value::array>) {
          auto status = writer.begin_array(item.size());
          if (!status)
            return status;
          for (const auto &element : item)
            if (!(status = write_serialization_value(writer, element)))
              return status;
          return writer.end_array();
        } else {
          auto status = writer.begin_object(item.size());
          if (!status)
            return status;
          for (const auto &[name, member] : item) {
            if (!(status = writer.write_key(name)) ||
                !(status = write_serialization_value(writer, member)))
              return status;
          }
          return writer.end_object();
        }
      },
      value.data());
}

} // namespace gmp::detail

#endif // GMP_SERIALIZATION_DETAIL_WRITE_VALUE_HPP_
