---
title: Installation
sidebar_position: 2
---

# Installation

GMP is header-only, so installation can be as small as adding the released `include/` directory to your compiler's include path. If your project already uses CMake, you can also install GMP once and consume it through `find_package`.

## Use the Released Headers

Download the `include` archive from the latest release:

[Download include.zip](https://github.com/lkimuk/gmp/releases/download/v0.3.0/include.zip)

Extract it into your project or a third-party dependency directory, then include the aggregate header:

```cpp
#include <gmp/gmp.hpp>
```

This is the simplest setup for trying GMP or vendoring it into an existing codebase.

## Install with CMake

Clone, build, and install the project:

```bash
git clone https://github.com/lkimuk/gmp.git
cd gmp
cmake -B ./build
cmake --build ./build
cmake --install ./build
```

Linux and macOS installations may require `sudo` for the final install step, depending on the chosen install prefix.

Then consume GMP from another CMake project:

```cmake
find_package(gmp 0.3.0 REQUIRED)
target_link_libraries(your_target PRIVATE gmp::gmp)
```

## Compiler Requirements

The library has two compatibility tiers:

| Feature Area | Standard |
|--------------|----------|
| Macro metaprogramming | C++11 and later |
| Generic design patterns | C++11 and later |
| Reflection metaprogramming | C++20 and later |
| Named operators | C++20 and later |

For C++20 features, the recommended minimum compiler versions are:

| Compiler | Minimum Version |
|----------|-----------------|
| MSVC     | 19.37+          |
| GCC      | 11.1+           |
| Clang    | 18.1.0+         |
