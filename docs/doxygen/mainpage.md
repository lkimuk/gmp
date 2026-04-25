# Overview

Welcome to the generated API reference for **GMP**.

## Summary

GMP is a header-only C++ metaprogramming library for compile-time programming
and code generation. It provides four complementary layers:

- **Macro metaprogramming**: Preprocessor utilities for boolean logic,
  arithmetic, tuple manipulation, loops, overload selection, and code
  generation. This layer is available in **C++11**.
- **Reflection metaprogramming**: Compile-time utilities for fixed strings,
  type names, enum reflection, and aggregate member introspection. This layer
  requires **C++20**.
- **Named operators**: Utilities for turning callables into custom infix
  operators with value-category-aware operand binding. This layer requires
  **C++20**.
- **Generic design patterns**: Lightweight synchronization, singleton, and
  object-factory helpers for reusable generic infrastructure. This layer is
  available in **C++11**, with some conveniences improving under **C++20**.

## Key Features

- **Header-only design**: Zero compilation required, just include and use.
- **Two-tier language support**: Macro metaprogramming and generic design
  patterns support **C++11**; reflection and named operators require
  **C++20**.
- **Cross-platform**: Compatible with GCC, Clang, and MSVC.
- **Zero dependencies**: Pure standard C++ with no external runtime
  dependencies.
- **Compile-time focused**: Designed for compile-time evaluation and code
  generation.

## Compiler Support

GMP provides feature sets with different compiler requirements:

- **Macro Metaprogramming and Generic Design Patterns**: Intended to work with
  **C++11** compilers and later.
- **Reflection Metaprogramming and Named Operators**: Require **C++20** and
  the following compiler versions or newer:

| Compiler | Minimum Version |
|----------|-----------------|
| MSVC     | 19.37+          |
| GCC      | 11.1+           |
| Clang    | 18.1.0+         |

## Install

**Try online quickly:**

- Compiler Explorer: [https://godbolt.org/z/W156818n5](https://godbolt.org/z/W156818n5)

**Header-only usage**

Copy the [include](https://github.com/lkimuk/gmp/releases/download/v0.3.0/include.zip)
folder into your build tree and include `gmp/gmp.hpp`.

**CMake integration**

Install system-wide and use CMake's `find_package`:

```bash
git clone https://github.com/lkimuk/gmp.git
cd gmp
cmake -B ./build
cmake --build ./build
cmake --install ./build
```

```cmake
find_package(gmp 0.3.0 REQUIRED)
target_link_libraries(your_target PRIVATE gmp::gmp)
```

## Recommended Reading

Start with the hand-written docs for concepts and walkthroughs:

- [Documentation home](../../)
- [Docs overview](../../docs/)
- [Installation](../../docs/installation)
- [Getting Started](../../docs/getting-started)
- [Macro Metaprogramming](../../docs/macro-metaprogramming)
- [Reflection Metaprogramming](../../docs/reflection)
- [Named Operators](../../docs/named-operators)
- [Generic Design Patterns](../../docs/design-patterns)
- [Simplified Chinese docs](../../zh-Hans/docs/)

## Examples

The files in this section are standalone examples that demonstrate core GMP
features. They are intended to be compiled as regular programs from the
`examples/` directory.

- `reflection_enum.cpp`: Enumerate values and names with GMP reflection helpers.
- `aggregate_reflection.cpp`: Inspect aggregate members by name, count, and reference.
- `named_operator.cpp`: Build and use custom infix-style operators.
- `type_name_and_size.cpp`: Query compile-time type names and aggregate payload sizes.
