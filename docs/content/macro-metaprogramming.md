---
title: Macro Metaprogramming
sidebar_position: 3
---

# Macro Metaprogramming

The macro metaprogramming layer provides C++ preprocessor utilities for boolean logic, arithmetic, tuple manipulation, iteration, overload dispatch, and namespace generation.

This module is available in **C++11**.

## Main Header

```cpp
#include <gmp/macro/macro.hpp>
```

You can also access it through the umbrella header:

```cpp
#include <gmp/gmp.hpp>
```

## What This Module Is Good For

- Generating repetitive declarations from a single macro invocation
- Dispatching to different macro names based on argument count or token sequences
- Manipulating tuple-like token groups without introducing templates
- Building lightweight DSL-like preprocessing layers for registration, code expansion, or namespace construction

## Feature Groups

### Macro Utilities

- Boolean operations: `GMP_BOOL`, `GMP_NOT`, `GMP_AND`, `GMP_OR`, `GMP_XOR`, `GMP_IMPLIES`
- Arithmetic macros: `GMP_INC`, `GMP_DEC`, `GMP_ADD`, `GMP_SUB`
- Comparison macros: `GMP_EQUAL_INT`, `GMP_GREATER_INT`, `GMP_GREATER_EQUAL_INT`, `GMP_LESS_INT`, `GMP_LESS_EQUAL_INT`, `GMP_EQUAL_INT_INDEPENDENT`
- Conditional macros: `GMP_IF`, `GMP_IF_THEN_ELSE`
- Stringification and concatenation: `GMP_STRINGIFY`, `GMP_CONCAT`, `GMP_CONCATS`
- Variadic handling: `GMP_SIZE_OF_VAARGS`, `GMP_GET_N`, `GMP_GET_FIRST_N`, `GMP_IS_EMPTY`
- Utility algorithms: `GMP_MAX`, `GMP_MIN`, `GMP_MINMAX`, `GMP_MAXMIN`, `GMP_SWAP`
- Miscellaneous helpers: `GMP_REMOVE_TRAILING_COMMA`, `GMP_IDENTIFIERS`

### Tuple Operations

- Size and access: `GMP_TUPLE_SIZE`, `GMP_GET_TUPLE`
- Modification: `GMP_TUPLE_APPEND`, `GMP_TUPLE_PREPEND`, `GMP_TUPLE_CONCAT`
- Slicing: `GMP_TUPLE_SKIP`, `GMP_TUPLE_TAKE`
- Detection: `GMP_IS_TUPLE`

### Advanced Facilities

- Loop macros: `GMP_REPEAT`, `GMP_WHILE`, `GMP_FOR_EACH`, `GMP_FOR_EACH_INDEPENDENT`
- Overload dispatch: `GMP_OVERLOAD_INVOKE`
- Expansion control: `GMP_EXPAND`, `GMP_EVAL`, `GMP_DEFER`
- Index generation: `GMP_MAKE_INDEX_SEQUENCE`, `GMP_RANGE`
- Namespace generation: `GMP_GENERATE_NAMESPACES_BEGIN`, `GMP_GENERATE_NAMESPACES_END`

## Quick Examples

```cpp
#include <gmp/gmp.hpp>

static_assert(GMP_BOOL(42) == 1, "Non-zero values are true");
static_assert(GMP_NOT(0) == 1, "NOT false is true");
static_assert(GMP_AND(1, 1) == 1, "Logical AND");
static_assert(GMP_ADD(2, 3) == 5, "Addition");
static_assert(GMP_TUPLE_SIZE((a, b, c)) == 3, "Tuple size");

#define PRINT(x) std::cout << x << " ";
GMP_FOR_EACH(PRINT, 1, 2, 3)

#define OVERLOAD_FUNCTION_0 "OVERLOAD_FUNCTION_0"
#define OVERLOAD_FUNCTION_X_Y "OVERLOAD_FUNCTION_X_Y"
GMP_OVERLOAD_INVOKE(OVERLOAD_FUNCTION, 0)
GMP_OVERLOAD_INVOKE(OVERLOAD_FUNCTION, X, Y)
```

### Tuple Operations

```cpp
GMP_TUPLE_SIZE((a, b, c, d, e))
GMP_TUPLE_TAKE(2, (a, b, c, d, e))
GMP_TUPLE_SKIP(2, (a, b, c, d, e))
GMP_TUPLE_APPEND((a, b, c), d)
GMP_TUPLE_PREPEND((b, c, d), a)
GMP_TUPLE_CONCAT((a, b), (c, d))
GMP_GET_TUPLE(1, (42, "hello", 3.14))
```

### Namespace Generation

```cpp
#define MYLIB_NAMESPACE_BEGIN GMP_GENERATE_NAMESPACES_BEGIN(mylib, parser)
#define MYLIB_NAMESPACE_END GMP_GENERATE_NAMESPACES_END(mylib, parser)

MYLIB_NAMESPACE_BEGIN
// declarations
MYLIB_NAMESPACE_END
```

## Notes

- Macro facilities work best when you need token-level manipulation rather than type-level computation.
- The tuple helpers operate on preprocessor tuples such as `(a, b, c)`, not on `std::tuple`.
- `GMP_OVERLOAD_INVOKE` is especially useful when building macro front-ends with multiple argument forms.

## Related Pages

- [Getting Started](./getting-started.md)
- [Reflection Metaprogramming](./reflection.md)
- [API Guide](./api-guide.md)
- [API Reference](https://lkimuk.github.io/gmp/api/)
