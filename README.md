<p align="center">
<h1 align="center">GMP (Generative Metaprogramming)</h1>
<h6 align="center">A C++ metaprogramming library tailored for code generation at compile time</h6>
</p>

[![License](https://img.shields.io/github/license/lkimuk/gmp.svg)](https://img.shields.io/github/license/lkimuk/gmp)
![Language](https://img.shields.io/github/languages/top/lkimuk/gmp.svg)
![Last commit](https://img.shields.io/github/last-commit/lkimuk/gmp.svg)

- [Overview](#overview)
- [Compiler Support](#compiler-support)
- [Install](#install)
- [Macro Metaprogramming](#macro-metaprogramming)
  - [Features](#features)
  - [Examples](#examples)
- [Reflection Metaprogramming](#reflection-metaprogramming)
  - [Features](#features-1)
  - [Examples](#examples-1)
- [Named Operators](#named-operators)
  - [Features](#features-2)
  - [Examples](#examples-2)
- [Generic Design Patterns](#generic-design-patterns)
  - [Features](#features-3)
  - [Examples](#examples-3)
- [Compile-time Tests](#compile-time-tests)
- [Acknowledgments](#acknowledgments)

## Overview
GMP is a header-only C++ metaprogramming library for compile-time programming and code generation. It provides four complementary layers:

- **Macro metaprogramming**: Preprocessor utilities for boolean logic, arithmetic, tuple manipulation, loops, overload selection, and code generation. This layer is available in **C++11**.
- **Reflection metaprogramming**: Compile-time utilities for fixed strings, type names, enum reflection, and aggregate member introspection. This layer requires **C++20**.
- **Named operators**: Utilities for turning callables into custom infix operators with value-category-aware operand binding. This layer requires **C++20**.
- **Generic design patterns**: Lightweight synchronization, singleton, and object-factory helpers for reusable generic infrastructure. This layer is available in **C++11**, with some conveniences improving under **C++20**.

**Key Features**

- **Header-only design**: Zero compilation required, just include and use
- **Two-tier language support**:
  - Macro metaprogramming and generic design-pattern utilities require **C++11**
  - Reflection metaprogramming and named-operator utilities require **C++20**
- **Cross-platform**: Compatible with GCC, Clang, and MSVC
- **Zero dependencies**: Pure standard C++, with no external dependencies
- **Compile-time focused**: Designed for compile-time evaluation and code generation
- **Broad coverage**: Includes macros, reflection utilities, named operators, and reusable design-pattern components

## Compiler Support

GMP provides feature sets with different compiler requirements:

**Macro Metaprogramming and Generic Design Patterns**

The macro metaprogramming utilities and the core design-pattern components should work correctly with **C++11** compilers and later.

**Reflection Metaprogramming and Named Operators**

The reflection metaprogramming and named-operator utilities require **C++20** and the following compiler versions or newer:

| Compiler | Minimum Version |
|----------|-----------------|
| MSVC     | 19.37+          |
| GCC      | 11.1+           |
| Clang    | 18.1.0+         |

## Install
**Try online quickly:**

Compiler Explorer: [https://godbolt.org/z/W156818n5](https://godbolt.org/z/W156818n5)

**Header-only version**

Copy the [include](https://github.com/lkimuk/gmp/releases/download/v0.3.0/include.zip) folder to your build tree and include `gmp/gmp.hpp`.

**CMake integration**

Install system-wide and use CMake's `find_package`:
```bash
$ git clone https://github.com/lkimuk/gmp.git
$ cd gmp
$ cmake -B ./build
$ cmake --build ./build
$ cmake --install ./build # sudo on Linux/macOS
```

```cpp
find_package(gmp 0.3.0 REQUIRED)
target_link_libraries(your_target PRIVATE gmp::gmp)
```

## Macro Metaprogramming
### Features
#### Macro Utilities
- **Boolean operations**: `GMP_BOOL`, `GMP_NOT`, `GMP_AND`, `GMP_OR`, `GMP_XOR`, `GMP_IMPLIES`
- **Arithmetic macros**: `GMP_INC`, `GMP_DEC`, `GMP_ADD`, `GMP_SUB`
- **Comparison macros**: `GMP_EQUAL_INT`, `GMP_GREATER_INT`, `GMP_GREATER_EQUAL_INT`, `GMP_LESS_INT`, `GMP_LESS_EQUAL_INT`, `GMP_EQUAL_INT_INDEPENDENT`
- **Conditional macros**: `GMP_IF`, `GMP_IF_THEN_ELSE`
- **Stringification**: `GMP_STRINGIFY`, `GMP_CONCAT`, `GMP_CONCATS`
- **Variadic handling**: `GMP_SIZE_OF_VAARGS`, `GMP_GET_N`, `GMP_GET_FIRST_N`, `GMP_IS_EMPTY`
- **Algorithms**: `GMP_MAX`, `GMP_MIN`, `GMP_MINMAX`, `GMP_MAXMIN`, `GMP_SWAP`
- **Remove trailing comma**: `GMP_REMOVE_TRAILING_COMMA`
- **Identifiers**: `GMP_IDENTIFIERS`

#### Tuple Operations
- **Size & Access**: `GMP_TUPLE_SIZE`, `GMP_GET_TUPLE`
- **Modification**: `GMP_TUPLE_APPEND`, `GMP_TUPLE_PREPEND`, `GMP_TUPLE_CONCAT`
- **Slicing**: `GMP_TUPLE_SKIP`, `GMP_TUPLE_TAKE`
- **Detection**: `GMP_IS_TUPLE`

#### Advanced Features
- **Loop macros**: `GMP_REPEAT`, `GMP_WHILE`, `GMP_FOR_EACH`, `GMP_FOR_EACH_INDEPENDENT`
- **Overload dispatch**: `GMP_OVERLOAD_INVOKE`
- **Expansion control**: `GMP_EXPAND`, `GMP_EVAL`, `GMP_DEFER`
- **Index sequences**: `GMP_MAKE_INDEX_SEQUENCE`, `GMP_RANGE`
- **Namespace generation**: `GMP_GENERATE_NAMESPACES_BEGIN`, `GMP_GENERATE_NAMESPACES_END`

### Examples
#### Macro Utilities
```cpp
#include <gmp/gmp.hpp>

static_assert(GMP_BOOL(42) == 1, "Non-zero values are true");
static_assert(GMP_NOT(0) == 1, "NOT false is true");
static_assert(GMP_AND(1, 1) == 1, "Logical AND");
static_assert(GMP_OR(0, 1) == 1, "Logical OR");
static_assert(GMP_XOR(1, 0) == 1, "Logical XOR");

static_assert(GMP_INC(5) == 6, "Increment");
static_assert(GMP_DEC(8) == 7, "Decrement");
static_assert(GMP_ADD(2, 3) == 5, "Addition");
static_assert(GMP_SUB(10, 4) == 6, "Subtraction");

static_assert(GMP_EQUAL_INT(5, 5) == 1, "Equality check");
static_assert(GMP_GREATER_INT(7, 3) == 1, "Greater than");
static_assert(GMP_LESS_INT(2, 9) == 1, "Less than");
static_assert(GMP_MAX(3, 7) == 7, "Maximum value");
static_assert(GMP_MIN(10, 2) == 2, "Minimum value");

GMP_IF(1, expr)                   // expands to: expr
GMP_IF_THEN_ELSE(0, expr1, expr2) // expands to: expr2

GMP_SIZE_OF_VAARGS(a, b, c)       // expands to: 3
GMP_GET_N(1, a, b, c)             // expands to: b
GMP_IS_EMPTY()                    // expands to: 1
GMP_IS_TUPLE((a, b, c))           // expands to: 1

GMP_MINMAX(7, 3)                  // expands to: (3, 7)
GMP_MAXMIN(7, 3)                  // expands to: (7, 3)
GMP_SWAP(x, y)                    // expands to: y, x
```

#### Tuple Operations
```cpp
GMP_TUPLE_SIZE((a, b, c, d, e))       // expands to: 5
GMP_TUPLE_TAKE(2, (a, b, c, d, e))    // expands to: (a, b)
GMP_TUPLE_SKIP(2, (a, b, c, d, e))    // expands to: (c, d, e)
GMP_TUPLE_APPEND((a, b, c), d)        // expands to: (a, b, c, d)
GMP_TUPLE_PREPEND((b, c, d), a)       // expands to: (a, b, c, d)
GMP_TUPLE_CONCAT((a, b), (c, d))      // expands to: (a, b, c, d)
GMP_GET_TUPLE(1, (42, "hello", 3.14)) // expands to: "hello"
```

#### Advanced Features
```cpp
#define PRINT(x) std::cout << x << " ";
GMP_FOR_EACH(PRINT, 1, 2, 3)

#define OVERLOAD_FUNCTION_0 "OVERLOAD_FUNCTION_0"
#define OVERLOAD_FUNCTION_X_Y "OVERLOAD_FUNCTION_X_Y"
GMP_OVERLOAD_INVOKE(OVERLOAD_FUNCTION, 0)    // expands to: "OVERLOAD_FUNCTION_0"
GMP_OVERLOAD_INVOKE(OVERLOAD_FUNCTION, X, Y) // expands to: "OVERLOAD_FUNCTION_X_Y"

GMP_MAKE_INDEX_SEQUENCE(5)                   // expands to: 0, 1, 2, 3, 4
GMP_RANGE(5, 10)                             // expands to: 5, 6, 7, 8, 9

#define MYLIB_NAMESPACE_BEGIN GMP_GENERATE_NAMESPACES_BEGIN(mylib, parser)
#define MYLIB_NAMESPACE_END GMP_GENERATE_NAMESPACES_END(mylib, parser)
MYLIB_NAMESPACE_BEGIN
MYLIB_NAMESPACE_END
```

## Reflection Metaprogramming

### Features
#### Compile-time Fixed String and Type Utilities
- `fixed_string`: A compile-time string type whose content can be manipulated
- `operator+(fixed_string, fixed_string)`: Concatenates two `fixed_string` values
- `operator""_fs`: Creates `fixed_string` values from string literals
- `to_fixed_string_v<N>`: Converts an integer to `fixed_string` at compile time
- `type_name<T>()`: Returns the compiler-extracted name of `T` at compile time
- `pretty_type_name<T>()()`: Returns a more readable type name for supported standard types
- `remove_all<Values...>(constant_arg_t<fixed_string>)`: Removes all occurrences of `Values...` from a `fixed_string`

#### Utilities
- `constant_arg_t<V>`: Statically enforces the type of an NTTP compile-time argument
- `constant_arg<V>`: Statically enforces that `V` is a compile-time value
- `any`: A type implicitly convertible to any type
- `as_value<T>()`: Defines a compile-time value of type `T`

#### Enum Reflection
- `enum_count<E>()`: Returns the number of enumerators in an enumeration type at compile time
- `enum_name<V>()`: Returns the name of an enumerator at compile time
- `enum_names<E>()`: Returns all enumerator names of an enumeration type at compile time
- `enum_values<E>()`: Returns all enumerator values of an enumeration type at compile time
- `enum_entries<E>()`: Returns all enumerator `(value, name)` pairs at compile time
- `enum_index(value)`: Returns the index of an enumerator within `enum_values<E>()`
- `enum_cast<E>(name)`: Converts an enumerator name to `std::optional<E>`
- `GMP_ENUM_RANGE(Enum, Min, Max)`: Customizes the scanned range for enum reflection
- `GMP_ENUM_VALUES(Enum, ...)`: Supplies explicit enumerator values for enum reflection

#### Aggregate Introspection
- `member_count<T>()`: Returns the number of members in an aggregate type at compile time
- `member_name<I, T>()`: Returns the name of the `I`-th member of a type at compile time
- `member_names<T>()`: Returns the names of all members of a type at compile time
- `member_type_t<I, T>`: Returns the type of the `I`-th member of an aggregate type
- `member_type_names<T>()`: Returns readable member type names of an aggregate type
- `member_ref<I>(obj)`: Returns a reference to the `I`-th member of an aggregate object
- `for_each_member(obj, fn)`: Visits each member of an aggregate object together with its name
- `type_size<T>()`: Returns the aggregate payload size excluding padding

### Examples
#### Reflection Metaprogramming
```cpp
#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <gmp/gmp.hpp>

struct Person {
    std::string name;
    int age;
    std::array<int, 3> scores;
};

enum class Color { Red, Green, Blue };

int main() {
    constexpr auto type = gmp::type_name<std::vector<std::string>>();
    constexpr auto pretty = gmp::pretty_type_name<std::vector<std::string>>()();
    constexpr auto member_names = gmp::member_names<Person>();
    constexpr auto member_types = gmp::member_type_names<Person>();
    constexpr auto colors = gmp::enum_entries<Color>();

    static_assert(gmp::member_count<Person>() == 3);
    static_assert(std::is_same_v<gmp::member_type_t<1, Person>, int>);
    static_assert(gmp::type_size<Person>() == sizeof(std::string) + sizeof(int) + sizeof(std::array<int, 3>));

    std::cout << "raw type: " << type << "\n";
    std::cout << "pretty type: " << pretty << "\n";
    std::cout << "first member: " << member_names[0] << " -> " << member_types[0] << "\n";

    for (const auto& [value, name] : colors) {
        std::cout << static_cast<int>(value) << ": " << name << "\n";
    }

    Person person{ "Miles", 28, {95, 88, 91} };
    gmp::for_each_member(person, [](auto&& member_name, auto&& member_value) {
        std::cout << member_name << ": " << member_value << "\n";
    });

    gmp::member_ref<1>(person) = 29;
    auto color = gmp::enum_cast<Color>("Green");
    std::cout << "updated age: " << person.age << "\n";
    std::cout << "enum cast success: " << color.has_value() << "\n";
}
```

## Named Operators

### Features
- Expressive operator-like DSL syntax: Enables playful and readable forms such as `^_^`, `<_>`, `+_+`, `*_*`, `-_-`, `/_/`, `%_%`, `&_&`, `|_|`, and `^o^`
- `make_named_operator(...)`: Creates a token that turns a callable into a named operator
- `GMP_GENERATE_NAMED_OPERATOR_PAIRS(...)`: Generates named-operator pairs from explicit operator tuples
- `GMP_GENERATE_NAMED_OPERATOR_IDENTICAL_PAIRS(...)`: Generates named-operator pairs that use the same token on both sides
- `GMP_DISABLE_DEFAULT_NAMED_OPERATORS`: Disables the default predefined named-operator pairs so custom sets can be supplied
- Value-category-aware binding: Preserves lvalue/rvalue semantics for operands during operator composition
- Default operator forms: `lhs ^op^ rhs`, `lhs <op> rhs`, `lhs +op+ rhs`, `lhs *op* rhs`, `lhs -op- rhs`, `lhs /op/ rhs`, `lhs %op% rhs`, `lhs &op& rhs`, and `lhs |op| rhs`
- Expression-style examples: `a ^_^ b`, `a <_> b`, `a +_+ b`, `a *_* b`, `a -_- b`, `a /_/ b`, `a %_% b`, `a &_& b`, `a |_| b`, `a *_^ b`, and `a ^o^ b`

### Examples
#### Named Operators
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

    auto consume = gmp::make_named_operator([](std::unique_ptr<int> p, int n) {
        return *p + n;
    });

    assert((a ^_^ b) == 13);
    assert((a <_> b) == 13);
    assert((a +_+ b) == 13);
    assert((a *_* b) == 13);
    assert((a -_- b) == 13);
    assert((a /_/ b) == 13);
    assert((a %_% b) == 13);
    assert((a &_& b) == 13);
    assert((a |_| b) == 13);
    assert((a *_^ b) == 13);
    assert((a ^o^ b) == 30);
    assert((std::make_unique<int>(40) ^consume^ 2) == 42);
}
```

## Generic Design Patterns

### Features
- `spin_lock`: A lightweight synchronization primitive based on `std::atomic_flag`
- `singleton<T, LongLifeTime>`: A CRTP-based singleton utility with optional long-lifetime support
- `object_factory<AbstractProduct, ConstructorArgs...>`: A singleton-based object factory for runtime registration and creation
- `GMP_DISABLE_CONSTRUCTION(Class)`: Disables direct construction for `singleton`-derived types
- `GMP_FACTORY_REGISTER(...)`: Registers product types with `object_factory`

### Examples
#### Generic Design Patterns
```cpp
#include <iostream>
#include <memory>
#include <string>
#include <gmp/gmp.hpp>

struct logger : gmp::singleton<logger> {
    void write(const std::string& message) const {
        std::cout << message << "\n";
    }

    GMP_DISABLE_CONSTRUCTION(logger)
};

struct shape {
    virtual ~shape() = default;
    virtual const char* name() const = 0;
};

struct circle : shape {
    const char* name() const override { return "circle"; }
};

struct square : shape {
    const char* name() const override { return "square"; }
};

GMP_FACTORY_REGISTER(shape, (), circle, square)

int main() {
    logger::instance().write("hello from singleton");

    auto product = gmp::object_factory<shape>::instance().create_unique("circle");
    std::cout << product->name() << "\n";
}
```

## Compile-time Tests
The library includes compile-time-oriented tests using `static_assert` and build-time validation:
```bash
cmake -B ./build -DBUILD_TESTS=ON
cmake --build ./build
```

## Acknowledgments
Inspired by Boost.Preprocessor and other metaprogramming libraries.

## License
GMP is licensed under the MIT license, see [LICENSE](https://github.com/lkimuk/gmp/blob/main/LICENSE) for more information.
