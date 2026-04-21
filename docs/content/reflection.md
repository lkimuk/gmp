---
title: Reflection Metaprogramming
sidebar_position: 4
---

# Reflection Metaprogramming

The reflection metaprogramming layer provides compile-time utilities for fixed strings, type names, enum reflection, and aggregate member introspection.

This module requires **C++20**.

## Main Header

```cpp
#include <gmp/meta/meta.hpp>
```

Or through the umbrella header:

```cpp
#include <gmp/gmp.hpp>
```

## What This Module Is Good For

- Producing readable type names at compile time
- Enumerating enum values and names without handwritten lookup tables
- Inspecting aggregate members for serialization, debugging, or schema-like workflows
- Building constexpr-friendly utilities around strings and non-type template parameters

## Feature Groups

### Fixed Strings and Type Utilities

- `fixed_string`
- `operator+(fixed_string, fixed_string)`
- `operator""_fs`
- `to_fixed_string_v<N>`
- `type_name<T>()`
- `pretty_type_name<T>()()`
- `remove_all<Values...>(constant_arg_t<fixed_string>)`

### Utility Building Blocks

- `constant_arg_t<V>`
- `constant_arg<V>`
- `any`
- `as_value<T>()`

### Enum Reflection

- `enum_count<E>()`
- `enum_name<V>()`
- `enum_names<E>()`
- `enum_values<E>()`
- `enum_entries<E>()`
- `enum_index(value)`
- `enum_cast<E>(name)`
- `GMP_ENUM_RANGE(Enum, Min, Max)`
- `GMP_ENUM_VALUES(Enum, ...)`

### Aggregate Introspection

- `member_count<T>()`
- `member_name<I, T>()`
- `member_names<T>()`
- `member_type_t<I, T>`
- `member_type_names<T>()`
- `member_ref<I>(obj)`
- `for_each_member(obj, fn)`
- `type_size<T>()`

## Full Example

```cpp
#include <array>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include <gmp/gmp.hpp>

struct Person {
    std::string name;
    int age;
    std::array<int, 3> scores;
};

enum class Color { Red, Green, Blue };

int main() {
    constexpr auto type = gmp::type_name<std::vector<std::string>>();
    constexpr auto pretty = gmp::pretty_type_name<std::vector<std::string>>()();
    constexpr auto member_names = gmp::member_names<Person>();
    constexpr auto colors = gmp::enum_entries<Color>();

    static_assert(gmp::member_count<Person>() == 3);

    std::cout << type << "\n";
    std::cout << pretty << "\n";
    std::cout << member_names[0] << "\n";
    std::cout << colors[0].second << "\n";
}
```

## Practical Notes

- `type_name<T>()` exposes compiler-derived names, while `pretty_type_name<T>()()` aims to provide a cleaner representation for supported standard-library-heavy types.
- Enum reflection can be customized with `GMP_ENUM_RANGE` or `GMP_ENUM_VALUES` when the default scan strategy is not suitable.
- Aggregate introspection targets aggregate types and is most useful when you want structural access without handwritten boilerplate.

## Common Use Cases

- Debug and logging helpers that print readable type names
- Compile-time enum serialization and string conversion
- Generic visitors that iterate over aggregate members
- Lightweight metadata extraction without runtime reflection

## Related Pages

- [Getting Started](./getting-started.md)
- [Named Operators](./named-operators.md)
- [API Guide](./api-guide.md)
- [API Reference](https://lkimuk.github.io/gmp/api/)
