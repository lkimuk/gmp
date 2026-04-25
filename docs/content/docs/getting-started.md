---
title: Getting Started
sidebar_position: 3
---

# Getting Started

After GMP is on your include path, start from the aggregate header:

```cpp
#include <gmp/gmp.hpp>
```

The aggregate header is convenient while exploring the library. In larger projects, you can include only the module headers you use.

## Try a Small Example

Use the online demo if you want to see GMP without setting up a local project:

[Compiler Explorer Demo](https://godbolt.org/z/W156818n5)

For a local CMake project, link the imported target after installation:

```cmake
find_package(gmp 0.3.0 REQUIRED)
target_link_libraries(your_target PRIVATE gmp::gmp)
```

Then compile your target with the C++ standard required by the module you are using. Macro metaprogramming and design-pattern helpers work in C++11; reflection and named operators require C++20.

## Pick the Right Module

Start with the module that matches the shape of your problem:

- Use **Macro Metaprogramming** when you need preprocessor-time repetition, token manipulation, or generated declarations.
- Use **Reflection Metaprogramming** when you need enum names, type names, aggregate member names, member types, or member references at compile time.
- Use **Named Operators** when a callable reads more naturally between its operands.
- Use **Generic Design Patterns** when you need reusable singleton services or string-keyed object factories.

## Build the Test Suite

If you are changing GMP itself, enable and build the tests:

```bash
cmake -B ./build -DBUILD_TESTS=ON
cmake --build ./build
```

Most tests are compile-time oriented, so a successful build is already a meaningful validation pass.
