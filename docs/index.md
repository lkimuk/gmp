# GMP Documentation

Language: English | [简体中文](zh/index.html)

**GMP** is a header-only C++ metaprogramming library for compile-time programming and code generation.

It provides four complementary layers:

- **Macro metaprogramming** for preprocessor-driven code generation and token manipulation
- **Reflection metaprogramming** for compile-time type, enum, and aggregate introspection
- **Named operators** for expressive infix-style DSLs
- **Generic design patterns** for reusable singleton, synchronization, and factory utilities

## Quick Links

- [Getting Started](getting-started.html)
- [Macro Metaprogramming](macro-metaprogramming.html)
- [Reflection Metaprogramming](reflection.html)
- [Named Operators](named-operators.html)
- [Generic Design Patterns](design-patterns.html)
- [API Reference](api/)

## Feature Overview

| Module | Minimum Standard | Notes |
|--------|------------------|-------|
| Macro metaprogramming | C++11 | Preprocessor utilities, tuples, loops, overload dispatch |
| Reflection metaprogramming | C++20 | Fixed strings, enum reflection, aggregate introspection |
| Named operators | C++20 | Custom infix syntax with callable binding |
| Generic design patterns | C++11 | Singleton, spin lock, object factory |

## Why GMP

- **Header-only**: no separate library build is required
- **Zero dependencies**: built on standard C++ only
- **Cross-platform**: designed for GCC, Clang, and MSVC
- **Compile-time focused**: optimized for metaprogramming and code generation workflows

## Module Map

If you want to know where a feature lives in the source tree:

| Area | Main Public Header | Notes |
|------|--------------------|-------|
| Full umbrella include | `gmp/gmp.hpp` | Pulls in the public library surface |
| Macros | `gmp/macro/macro.hpp` | Preprocessor utilities and code generation helpers |
| Reflection and type utilities | `gmp/meta/meta.hpp` | Fixed strings, type names, enum reflection, member introspection |
| Named operators | `gmp/meta/named_operator.hpp` | Infix-style callable composition |
| Design patterns | `gmp/dp/*.hpp` | Singleton, lock, and object factory helpers |

## Documentation Style

The current documentation is organized by capability rather than by file. Each page explains what a module is for, what language level it needs, and which APIs to look at first.

## Languages

- English is the primary documentation language
- A Simplified Chinese guide set is available under [zh/](zh/index.html)
- The [API Reference](api/) is currently available in English only

## Next Steps

Start with [Getting Started](getting-started.html), then jump to the module you want to explore in depth.
