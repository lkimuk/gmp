---
title: Macro Metaprogramming
sidebar_position: 2
---

# Macro Metaprogramming

GMP's macro layer is a C++11 preprocessor toolkit for generating tokens before the compiler parses the program. It handles the unglamorous but necessary parts of macro programming: argument counting, tuple-like macro data, conditional expansion, repetition, overload dispatch, token concatenation, and namespace generation.

Use it through:

```cpp
#include <gmp/macro/macro.hpp>
// or
#include <gmp/gmp.hpp>
```

## The Preprocessor Layer

The module is organized around a few reusable building blocks:

- Conditional expansion with `GMP_BOOL`, `GMP_NOT`, `GMP_AND`, `GMP_OR`, `GMP_IF`, and `GMP_IF_THEN_ELSE`
- Token utilities such as `GMP_STRINGIFY`, `GMP_CONCAT`, `GMP_CONCATS`, and `GMP_EXPAND`
- Variadic argument tools such as `GMP_SIZE_OF_VAARGS`, `GMP_GET_N`, `GMP_GET_FIRST_N`, and `GMP_IS_EMPTY`
- Tuple helpers such as `GMP_TUPLE_SIZE`, `GMP_GET_TUPLE`, `GMP_TUPLE_APPEND`, `GMP_TUPLE_TAKE`, and `GMP_TUPLE_SKIP`
- Generation helpers such as `GMP_REPEAT`, `GMP_FOR_EACH`, `GMP_OVERLOAD_INVOKE`, `GMP_RANGE`, and `GMP_GENERATE_NAMESPACES_BEGIN`

## When It Helps

Templates are excellent once C++ syntax exists, but they cannot create new tokens before parsing. Macro metaprogramming is still useful when a library needs to generate declarations, repeat similar code, build identifiers, select a generated macro overload, or support older standards where newer template techniques are unavailable.

GMP gives those patterns stable names. Instead of writing another private recursive macro system, you can use the same primitives for repeated fields, generated overloads, dispatch tables, or namespace wrappers.

## Common Patterns

Use conditionals when the generated code depends on preprocessor-time state:

```cpp
#include <gmp/gmp.hpp>

GMP_IF(1, int enabled;)
GMP_IF_THEN_ELSE(0, int yes;, int no;)
```

Treat variadic arguments and tuple-like macro values as data:

```cpp
GMP_SIZE_OF_VAARGS(a, b, c)      // 3
GMP_GET_N(1, a, b, c)            // b

GMP_TUPLE_SIZE((x, y, z))        // 3
GMP_GET_TUPLE(1, (x, y, z))      // y
GMP_TUPLE_APPEND((x, y), z)      // (x, y, z)
GMP_TUPLE_TAKE(2, (x, y, z, w))  // (x, y)
```

Generate repeated declarations from a compact list:

```cpp
#define DECLARE_FIELD(name) int name;

struct record {
  GMP_FOR_EACH(DECLARE_FIELD, id, count, flags)
};

#undef DECLARE_FIELD
```

Build macro names from arguments:

```cpp
#define HANDLER_read read_handler
#define HANDLER_read_write read_write_handler

GMP_OVERLOAD_INVOKE(HANDLER, read)        // HANDLER_read
GMP_OVERLOAD_INVOKE(HANDLER, read, write) // HANDLER_read_write
```

Generate nested namespace blocks:

```cpp
GMP_GENERATE_NAMESPACES_BEGIN(my_library, detail)

struct generated_type {};

GMP_GENERATE_NAMESPACES_END(my_library, detail)
```
