# Getting Started

This page covers compiler requirements, installation options, and the quickest way to start using GMP.

## What GMP Includes

GMP is split into four major parts:

- Macro metaprogramming for preprocessor-time composition and code generation
- Reflection metaprogramming for compile-time type and aggregate inspection
- Named operators for custom infix syntax
- Generic design patterns for lightweight reusable runtime helpers

## Compiler Support

GMP exposes feature sets with different language requirements.

### C++11 and Later

The following modules are available with **C++11** compilers and later:

- Macro metaprogramming
- Generic design patterns

### C++20 and Later

The following modules require **C++20**:

- Reflection metaprogramming
- Named operators

Minimum recommended compiler versions for C++20 features:

| Compiler | Minimum Version |
|----------|-----------------|
| MSVC | 19.37+ |
| GCC | 11.1+ |
| Clang | 18.1.0+ |

## Quick Trial

You can try GMP online with Compiler Explorer:

- [Compiler Explorer Demo](https://godbolt.org/z/W156818n5)

## Header-Only Usage

Download the published headers and include `gmp/gmp.hpp` in your project:

- [Download include.zip](https://github.com/lkimuk/gmp/releases/download/v0.3.0/include.zip)

```cpp
#include <gmp/gmp.hpp>
```

If you only need a specific module, you can also include a narrower header, for example:

```cpp
#include <gmp/macro/macro.hpp>
#include <gmp/meta/meta.hpp>
#include <gmp/meta/named_operator.hpp>
#include <gmp/dp/singleton.hpp>
```

## CMake Integration

Clone, build, and install GMP:

```bash
git clone https://github.com/lkimuk/gmp.git
cd gmp
cmake -B ./build
cmake --build ./build
cmake --install ./build
```

Then consume it with CMake:

```cmake
find_package(gmp 0.3.0 REQUIRED)
target_link_libraries(your_target PRIVATE gmp::gmp)
```

### Typical Consumer Setup

```cmake
cmake_minimum_required(VERSION 3.16)
project(example LANGUAGES CXX)

find_package(gmp 0.3.0 REQUIRED)

add_executable(example main.cpp)
target_link_libraries(example PRIVATE gmp::gmp)
target_compile_features(example PRIVATE cxx_std_20)
```

Use `cxx_std_11` when you only depend on the macro or design-pattern modules.

## First Example

```cpp
#include <gmp/gmp.hpp>

struct logger : gmp::singleton<logger> {
    void write(const char* text) const {}
    GMP_DISABLE_CONSTRUCTION(logger)
};

int main() {
    static_assert(GMP_ADD(2, 3) == 5);
    logger::instance().write("hello");
}
```

This example combines one C++11 macro feature and one generic design-pattern utility. Reflection and named operators become available once your target is compiled as C++20.

## Running the Tests

GMP includes compile-time-oriented tests built around `static_assert` and build-time validation:

```bash
cmake -B ./build -DBUILD_TESTS=ON
cmake --build ./build
```

## Choosing a Starting Point

- Start with [Macro Metaprogramming](macro-metaprogramming.md) if you want preprocessor utilities or code generation helpers
- Start with [Reflection Metaprogramming](reflection.md) if you want type names, enum reflection, or aggregate inspection
- Start with [Named Operators](named-operators.md) if you want custom infix syntax
- Start with [Generic Design Patterns](design-patterns.md) if you want singleton or object-factory utilities

## Where to Go Next

- [Macro Metaprogramming](macro-metaprogramming.md)
- [Reflection Metaprogramming](reflection.md)
- [Named Operators](named-operators.md)
- [Generic Design Patterns](design-patterns.md)
- [API Reference](api/index.md)
