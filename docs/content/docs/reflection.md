---
title: Reflection Metaprogramming
sidebar_position: 3
---

# Reflection Metaprogramming

GMP's reflection layer provides C++20 compile-time introspection for the pieces of C++ that are often needed in library code: type names, enum values, enum names, aggregate member names, aggregate member types, and member references.

Use it through:

```cpp
#include <gmp/meta/meta.hpp>
// or
#include <gmp/gmp.hpp>
```

## Compile-time Metadata

The reflection module includes:

- `gmp::fixed_string`, `operator""_fs`, and `gmp::to_fixed_string_v<N>` for compile-time strings
- `gmp::type_name<T>()` and `gmp::pretty_type_name<T>()()` for compiler-derived type names
- `gmp::enum_values<E>()`, `gmp::enum_names<E>()`, `gmp::enum_entries<E>()`, and `gmp::enum_cast<E>(name)` for enum reflection
- `GMP_ENUM_RANGE` and `GMP_ENUM_VALUES` for enum scan customization
- `gmp::member_count<T>()`, `gmp::member_name<I, T>()`, `gmp::member_names<T>()`, `gmp::member_type_t<I, T>`, `gmp::member_type_names<T>()`, `gmp::member_ref<I>(object)`, and `gmp::for_each_member(object, fn)` for aggregate introspection

## Removing Hand-written Tables

Without reflection, projects often duplicate structural information in several places: enum-to-string tables, string-to-enum lookup functions, debug printers, serialization metadata, and hand-maintained member lists.

GMP keeps that information close to the C++ declarations. The compiler becomes the source of names and structure, while user code consumes small compile-time arrays or references.

This is a practical replacement for many small reflection use cases while the C++ standard still lacks full built-in reflection.

## Enum Reflection

For ordinary enum values, GMP can discover values and names at compile time:

```cpp
#include <gmp/gmp.hpp>

enum class color { red, green, blue };

static_assert(gmp::enum_count<color>() == 3);
static_assert(gmp::enum_names<color>()[1] == "green");
static_assert(gmp::enum_cast<color>("blue").value() == color::blue);

constexpr auto entries = gmp::enum_entries<color>();
```

For sparse or out-of-range enums, provide explicit values:

```cpp
enum class status { ok = 200, not_found = 404, error = 500 };

GMP_ENUM_VALUES(status, status::ok, status::not_found, status::error);

static_assert(gmp::enum_count<status>() == 3);
```

## Aggregate Introspection

Aggregate types can be inspected by member index:

```cpp
#include <gmp/gmp.hpp>
#include <string>
#include <type_traits>

struct person {
  std::string name;
  int age;
};

static_assert(gmp::member_count<person>() == 2);
static_assert(gmp::member_name<0, person>() == "name");
static_assert(std::is_same_v<gmp::member_type_t<1, person>, int>);
```

Runtime objects can be traversed without writing a separate member table:

```cpp
#include <gmp/gmp.hpp>
#include <iostream>
#include <string>

struct person {
  std::string name;
  int age;
};

int main() {
  person p{"Miles", 28};

  gmp::member_ref<1>(p) = 29;

  gmp::for_each_member(p, [](std::string_view name, auto&& value) {
    std::cout << name << ": " << value << "\n";
  });
}
```
