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

#ifndef GMP_SERIALIZATION_SERIALIZATION_HPP_
#define GMP_SERIALIZATION_SERIALIZATION_HPP_

#include <gmp/serialization/archive.hpp>
#include <gmp/serialization/deserializer.hpp>
#include <gmp/serialization/error.hpp>
#include <gmp/serialization/options.hpp>
#include <gmp/serialization/serializer.hpp>
#include <gmp/serialization/traits.hpp>
#include <gmp/serialization/value.hpp>
#include <gmp/serialization/value_archive.hpp>

namespace gmp {

template <typename T>
serialization_result<serialization_value>
to_serialization_value(const T &value, serialization_options options = {}) {
  value_writer writer;
  basic_serializer archive(writer, options);
  auto status = archive.encode(value);
  if (!status)
    return status.error();
  return writer.finish();
}

template <typename T>
serialization_result<T> from_serialization_value(const serialization_value &value,
                                                 deserialization_options options = {}) {
  value_reader reader(value);
  basic_deserializer archive(reader, options);
  return archive.template decode<T>();
}

} // namespace gmp

#endif // GMP_SERIALIZATION_SERIALIZATION_HPP_
