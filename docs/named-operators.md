# Named Operators

The named operator layer lets you build custom infix-style syntax by wrapping callables in lightweight operator tokens.

This module requires **C++20**.

## Main Header

```cpp
#include <gmp/meta/named_operator.hpp>
```

Or through:

```cpp
#include <gmp/gmp.hpp>
```

## What This Module Is Good For

- Making domain-specific operations read more like a small embedded language
- Composing binary callables with concise infix syntax
- Preserving move semantics while keeping expressions readable

## Highlights

- Expressive operator-like DSL syntax such as `^_^`, `<_>`, `+_+`, `*_*`, `-_-`, `/_/`, `%_%`, `&_&`, `|_|`, and `^o^`
- `make_named_operator(...)` for turning a callable into a named operator token
- `GMP_GENERATE_NAMED_OPERATOR_PAIRS(...)` for generating explicit operator pairs
- `GMP_GENERATE_NAMED_OPERATOR_IDENTICAL_PAIRS(...)` for generating symmetric operator pairs
- `GMP_DISABLE_DEFAULT_NAMED_OPERATORS` to disable predefined operator pairs
- Value-category-aware operand binding for lvalue/rvalue-sensitive composition

## Example

```cpp
#include <iostream>
#include <memory>
#include <gmp/gmp.hpp>

int main() {
    int a = 10;
    int b = 3;

    auto _ = gmp::make_named_operator([](int x, int y) {
        return x + y;
    });

    auto o = gmp::make_named_operator([](int x, int y) {
        return x * y;
    });

    assert((a ^_^ b) == 13);
    assert((a <_> b) == 13);
    assert((a ^o^ b) == 30);
}
```

## Notes

- The predefined operator forms are meant to be playful but still practical for DSL-style code.
- Named operators are best suited to local domain abstractions where readability clearly improves over a regular function call.
- Because binding preserves value category, they can work naturally with move-only types and forwarding-sensitive callables.

## Related Pages

- [Reflection Metaprogramming](reflection.md)
- [Generic Design Patterns](design-patterns.md)
- [API Reference](api/)
