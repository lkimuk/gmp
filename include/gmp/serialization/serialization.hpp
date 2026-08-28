// SPDX-License-Identifier: MIT
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
serialization_result<T>
from_serialization_value(const serialization_value &value,
                         deserialization_options options = {}) {
  value_reader reader(value);
  basic_deserializer archive(reader, options);
  return archive.template decode<T>();
}
} // namespace gmp
#endif
