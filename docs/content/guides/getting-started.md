---
title: Getting Started
sidebar_position: 2
---

# Getting Started

This page covers compiler requirements, installation options, and the quickest way to start using GMP.

## Compiler Support

- **C++11**: macro metaprogramming and generic design patterns
- **C++20**: reflection metaprogramming and named operators

## Quick Trial

- [Compiler Explorer Demo](https://godbolt.org/z/W156818n5)

## CMake Integration

```cmake
find_package(gmp 0.3.0 REQUIRED)
target_link_libraries(your_target PRIVATE gmp::gmp)
```

## Where To Go Next

- [First Project](./first-project.md)
- [Docs](/docs/)
- [Examples](/examples/)
