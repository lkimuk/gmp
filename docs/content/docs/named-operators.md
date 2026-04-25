---
title: Named Operators
sidebar_position: 4
---

# Named Operators

Named operators let a callable appear between its operands. A token created with `gmp::make_named_operator` participates in generated operator pairs, so an expression such as `lhs ^op^ rhs` invokes the callable stored inside `op`.

Use it through:

```cpp
#include <gmp/meta/named_operator.hpp>
// or
#include <gmp/gmp.hpp>
```

## Callable-backed Infix Syntax

By default, GMP supports these forms:

- `lhs ^op^ rhs`
- `lhs <op> rhs`
- `lhs +op+ rhs`
- `lhs *op* rhs`
- `lhs -op- rhs`
- `lhs /op/ rhs`
- `lhs %op% rhs`
- `lhs &op& rhs`
- `lhs |op| rhs`

The callable is stored by value. Lvalue left operands are stored by reference, rvalue left operands are stored by value, and the right operand is forwarded when the expression completes.

## Why Use It

Named operators are most useful in small DSLs and expression-heavy code where the operation reads more naturally between two values than as a function call around them.

They are not meant to hide ordinary function calls everywhere. The sweet spot is when the infix form makes the domain relationship clearer: composition, joining, matching, combining, binding, or experimenting with symbolic notation.

## Basic Usage

Create a token with `make_named_operator`:

```cpp
#include <cassert>
#include <gmp/gmp.hpp>

int main() {
  auto add = gmp::make_named_operator([](int lhs, int rhs) {
    return lhs + rhs;
  });

  assert((10 ^add^ 3) == 13);
  assert((10 <add> 3) == 13);
  assert((10 +add+ 3) == 13);
}
```

Use any callable whose signature matches the operands:

```cpp
#include <cassert>
#include <gmp/gmp.hpp>
#include <string>

int main() {
  auto join = gmp::make_named_operator([](std::string lhs, std::string rhs) {
    return lhs + "/" + rhs;
  });

  assert(("usr" ^join^ "local") == "usr/local");
}
```

Preserve lvalue semantics when mutation is intentional:

```cpp
#include <cassert>
#include <gmp/gmp.hpp>

int main() {
  auto add_assign = gmp::make_named_operator([](int& lhs, int rhs) -> int& {
    lhs += rhs;
    return lhs;
  });

  int value = 40;
  value ^add_assign^ 2;

  assert(value == 42);
}
```
