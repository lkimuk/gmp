<p align="center">
<h1 align="center">GMP (Generative Metaprogramming)</h1>
<h6 align="center">A C++ metaprogramming library tailored for code generation at compile time</h6>
</p>

[![License](https://img.shields.io/github/license/lkimuk/gmp.svg)](https://img.shields.io/github/license/lkimuk/gmp)
![Language](https://img.shields.io/github/languages/top/lkimuk/gmp.svg)
![Last commit](https://img.shields.io/github/last-commit/lkimuk/gmp.svg)

- [Overview](#overview)
- [Install](#install)
- [Macro metaprogramming](#macro-metaprogramming)
  - [Macro Features](#macro-features)
  - [Macro Examples](#macro-examples)
- [Reflection Metaprogramming](#reflection-metaprogramming)
  - [Meta Features](#meta-features)
  - [Meta Examples](#meta-examples)
- [Compile-time Tests](#compile-time-tests)
- [Acknowledgments](#acknowledgments)

## Overview
GMP is a comprehensive, header-only C++11 library designed for advanced compile-time programming and code generation. It provides a rich set of macros and utilities that enable expressive metaprogramming patterns, making complex template code more manageable and readable.

**Key Features**

- **Header-only design**: Zero compilation required, just include and use
- **C++11 compatible**: Works with modern C++ compilers without C++14/17 requirements
- **Cross-platform**: Fully compatible with GCC, Clang, and MSVC
- **Zero dependencies**: Pure C++ standard library, no external dependencies
- **Compile-time focused**: All operations evaluated at compile time, zero runtime overhead
- **Comprehensive utilities**: From basic boolean logic to advanced tuple manipulation

## Install
**Try online quickly:**

Compiler Explorer: [https://godbolt.org/z/W156818n5](https://godbolt.org/z/W156818n5)

**Header-only version**

Copy the [include](https://github.com/lkimuk/gmp/releases/download/v0.1.0/include.zip) folder to your build tree and use a C++11 compiler.

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
find_package(gmp 0.1.0 REQUIRED)
target_link_libraries(your_target PRIVATE gmp::gmp)
```

## Macro Metaprogramming
### Features
#### Macro Utilities
- **Boolean operations**: `GMP_BOOL`, `GMP_NOT`, `GMP_AND`, `GMP_OR`, `GMP_XOR`, `GMP_IMPLIES`
- **Arithmetic macros**: `GMP_INC`, `GMP_DEC`, `GMP_ADD`, `GMP_SUB`
- **Comparison macros**: `GMP_EQUAL_INT`, `GMP_GREATER_INT`, `GMP_GREATER_EQUAL_INT`,`GMP_LESS_INT`, `GMP_LESS_EQUAL_INT`, `GMP_EQUAL_INT_INDEPENDENT`
- **Conditional macros**: `GMP_IF`, `GMP_IF_THEN_ELSE`
- **Stringification**: `GMP_STRINGIFY`, `GMP_CONCAT`, `GMP_CONCATS`
- **Variadic handling**: `GMP_SIZE_OF_VAARGS`, `GMP_GET_N`, `GMP_IS_EMPTY`
- **Algorithms**: `GMP_MAX`, `GMP_MIN`, `GMP_MINMAX`, `GMP_MAXMIN`, `GMP_SWAP`
- **Remove trailing comma**: `GMP_REMOVE_TRAILING_COMMA`
- **Identifies**: `GMP_IDENTIFIERS`

#### Tuple Operations
- **Size & Access**: `GMP_TUPLE_SIZE`, `GMP_GET_TUPLE`
- **Modification**: `GMP_TUPLE_APPEND`, `GMP_TUPLE_PREPEND`, `GMP_TUPLE_CONCAT`
- **Slicing**: `GMP_TUPLE_SKIP`, `GMP_TUPLE_TAKE`

#### Advanced Feature
- **Loop macros**: `GMP_REPEAT`, `GMP_WHILE`, `GMP_FOR_EACH`, `GMP_FOR_EACH_INDEPENDENT`
- **Overload functions matching**: `GMP_OVERLOAD_INVOKE`
- **Expand control**: `GMP_EXPAND`, `GMP_EVAL`, `GMP_DEFER`
- **Index sequences**: `GMP_MAKE_INDEX_SEQUENCE`, `GMP_RANGE`
- **Namespace generation**: `GMP_GENERATE_NAMESPACES_BEGIN`, `GMP_GENERATE_NAMESPACES_END`

### Examples
#### Macro Utilities
```cpp
#include <gmp/gmp.hpp>

// Boolean and logical operations
static_assert(GMP_BOOL(42) == 1, "Non-zero values are true");
static_assert(GMP_NOT(0) == 1, "NOT false is true");
static_assert(GMP_AND(1, 1) == 1, "Logical AND");
static_assert(GMP_OR(0, 1) == 1, "Logical OR");
static_assert(GMP_XOR(1, 0) == 1, "Logical XOR");

// Arithmetic operations
static_assert(GMP_INC(5) == 6, "Increment");
static_assert(GMP_DEC(8) == 7, "Decrement");
static_assert(GMP_ADD(2, 3) == 5, "Addition");
static_assert(GMP_SUB(10, 4) == 6, "Subtraction");
static_assert(GMP_SUB(3, 5) == -2, "Negative subtraction");

// Comparison operations
static_assert(GMP_EQUAL_INT(5, 5) == 1, "Equality check");
static_assert(GMP_GREATER_INT(7, 3) == 1, "Greater than");
static_assert(GMP_LESS_INT(2, 9) == 1, "Less than");
static_assert(GMP_MAX(3, 7) == 7, "Maximum value");
static_assert(GMP_MIN(10, 2) == 2, "Minimum value");

// Conditional operations
GMP_IF(1, expr)                                     // expands to: expr
GMP_IF(0, expr)                                     // expands to:
GMP_IF_THEN_ELSE(1, expr1, expr2)                   // expands to: expr1
GMP_IF_THEN_ELSE(0, expr1, expr2)                   // expands to: expr2

// Variadic operations
GMP_SIZE_OF_VAARGS()                                // expands to: 0
GMP_SIZE_OF_VAARGS(1)                               // expands to: 1
GMP_SIZE_OF_VAARGS('a', 'b')                        // expands to: 2
GMP_SIZE_OF_VAARGS('a', 'b', 'c')                   // expands to: 3
GMP_SIZE_OF_VAARGS('a', 'b', 1, 2)                  // expands to: 4
GMP_SIZE_OF_VAARGS('a', 'b', 1, 2, 3)               // expands to: 5
GMP_SIZE_OF_VAARGS('a', 'b', 1, 2, 3, 4)            // expands to: 6
GMP_SIZE_OF_VAARGS('a', 'b', 1, 2, 3, 4, 5)         // expands to: 7

GMP_IS_EMPTY()                                      // expands to: 1
GMP_IS_EMPTY(1)                                     // expands to: 0
GMP_IS_EMPTY(1, 2)                                  // expands to: 0

GMP_GET_N(0, a, b, c)                               // expands to: a
GMP_GET_N(1, a, b, c)                               // expands to: b  
GMP_GET_N(2, a, b, c)                               // expands to: c

// Algorithms
GMP_MINMAX(7, 3)                                    // expands to: (3, 7)
GMP_MINMAX(2, 10)                                   // expands to: (2, 10)
GMP_MINMAX(5, 5)                                    // expands to: (5, 5)
GMP_MAXMIN(7, 3)                                    // expands to: (7, 3)
GMP_MAXMIN(2, 10)                                   // expands to: (10, 2)
GMP_MAXMIN(5, 5)                                    // expands to: (5, 5)
GMP_SWAP(x, y)                                      // expands to: y, x
```

#### Tuple Operations
```cpp
GMP_TUPLE_SIZE(());                                 // expands to: 0
GMP_TUPLE_SIZE((a, b, c, d, e))                     // expands to: 5

GMP_TUPLE_TAKE(2, (a, b, c, d, e))                  // expands to: (a, b)
GMP_TUPLE_TAKE(0, (a, b, c, d, e))                  // expands to: ()
GMP_TUPLE_TAKE(5, (a, b, c, d, e))                  // expands to: (a, b, c, d, e)
GMP_TUPLE_TAKE(10, (a, b, c, d, e))                 // expands to: (a, b, c, d, e)

GMP_TUPLE_SKIP(2, (a, b, c, d, e))                  // expands to: (c, d, e)
GMP_TUPLE_SKIP(0, (a, b, c, d, e))                  // expands to: (a, b, c, d, e)
GMP_TUPLE_SKIP(5, (a, b, c, d, e))                  // expands to: ()
GMP_TUPLE_SKIP(10, (a, b, c, d, e))                 // expands to: ()

GMP_TUPLE_APPEND((a, b, c, d, e), f)                // expands to: (a, b, c, d, e, f)
GMP_TUPLE_APPEND((), f)                             // expands to: (f)

GMP_TUPLE_PREPEND((b, c, d), a)                     // expands to: (a, b, c, d)
GMP_TUPLE_PREPEND((), x)                            // expands to: (x)
GMP_TUPLE_PREPEND(GMP_TUPLE_PREPEND((c, d), b), a)  // expands to: (a, b, c, d)

GMP_TUPLE_CONCAT((), (a, b, c))                     // expands to: (a, b, c)
GMP_TUPLE_CONCAT((a, b, c), (a, b, c))              // expands to: (a, b, c, a, b, c)
GMP_TUPLE_CONCAT((a, b, c), ())                     // expands to: (a, b, c)
GMP_TUPLE_CONCAT((), ())                            // expands to: ()

GMP_GET_TUPLE(0, (int, float, char))                // expands to: int
GMP_GET_TUPLE(1, (42, "hello", 3.14))               // expands to: "hello"
```

#### Advanced Feature
```cpp
#define Bar(arg1, arg2) bar(arg1, arg2); 
// Expands to: bar(1, "arg2"); bar(1, "arg2"); bar(1, "arg2"); ... (100 times)
GMP_REPEAT(Bar, 100, 1, "arg2")

#define PRINT(x) std::cout << x << " ";
// Expands to: std::cout << 1 << " "; std::cout << 2 << " "; std::cout << 3 << " ";
GMP_FOR_EACH(PRINT, 1, 2, 3)

#define OVERLOAD_FUNCTION_0 "OVERLOAD_FUNCTION_0"
#define OVERLOAD_FUNCTION_1 "OVERLOAD_FUNCTION_1"
#define OVERLOAD_FUNCTION_X_Y "OVERLOAD_FUNCTION_X_Y"
GMP_OVERLOAD_INVOKE(OVERLOAD_FUNCTION, 0)           // expands to: "OVERLOAD_FUNCTION_0"
GMP_OVERLOAD_INVOKE(OVERLOAD_FUNCTION, 1)           // expands to: "OVERLOAD_FUNCTION_1"
GMP_OVERLOAD_INVOKE(OVERLOAD_FUNCTION, X, Y)        // expands to: "OVERLOAD_FUNCTION_X_Y"

GMP_MAKE_INDEX_SEQUENCE(0)                          // expands to: 
GMP_MAKE_INDEX_SEQUENCE(5)                          // expands to: 0, 1, 2, 3, 4
GMP_MAKE_INDEX_SEQUENCE(42)                         // expands to: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41

GMP_RANGE(0, 0)                                     // expands to: 
GMP_RANGE(0, 5)                                     // expands to: 0 , 1 , 2 , 3 , 4
GMP_RANGE(5, 10)                                    // expands to: 5 , 6 , 7 , 8 , 9

GMP_STRINGIFY(GMP_CONCATS(abc, 123, def, 456))     // expands to: "abc123def456"

#define MYLIB_NAMESPACE_BEGIN GMP_GENERATE_NAMESPACES_BEGIN(mylib, parser)
#define MYLIB_NAMESPACE_END GMP_GENERATE_NAMESPACES_END(mylib, parser)

/// expands to:
/// namespace mylib { namespace parser {
/// } }
MYLIB_NAMESPACE_BEGIN
MYLIB_NAMESPACE_END
```

## Reflection Metaprogramming
MSVC >= v19.37
GCC >= 11.1
Clang >= 18.1.0

### Meta Features
**Compile-time Fixed String**
- `fixed_string`: A compile-time string type whose content can be manipulated
- `operator+(fixed_string, fixed_string)`: Concatenates two `fixed_string` values
- `remove_all<Values...>(constant_arg_t<fixed_string>)`: Removes all occurrences of `Values...` from a `fixed_string`

**Utilities**
- `constant_arg_t<V>`: Statically enforces the type of an NTTP compile-time argument
- `constant_arg<V>`: Statically enforces that `V` is a compile-time value
- `any`: A type implicitly convertible to any type
- `as_value<T>()`: Defines a compile-time value of type `T`

**Meta Functions**
- `type_name<T>()`: Returns the string representation of `T` at compile time
- `enum_count<E>()`: Returns the number of enumerators in an enumeration type at compile time
- `enum_name<V>()`: Returns the name of an enumerator at compile time
- `enum_names<E>()`: Returns all enumerator names of an enumeration type at compile time
- `member_count<T>()`: Returns the number of members in an aggregate type at compile time
- `member_name<I, T>()`: Returns the name of the `I`-th member of a type at compile time
- `member_names<T>()`: Returns the names of all members of a type at compile time

### Meta Examples
**Reflection Metaprogramming**
```cpp
#include <gmp/gmp.hpp>

struct S {
    double b;
    std::string str;
};

enum class Color { Red, Green, Blue, Yellow };
enum class Empty {};

int main() {
    constexpr auto int_name = gmp::type_name<int>();
    std::cout << "int: " << int_name << "\n";
    std::cout << "float: " << gmp::type_name<float>().to_string_view() << "\n";
    std::cout << "std::vector<std::string>: " << gmp::type_name<std::vector<std::string>>() << "\n";

    std::cout << gmp::member_count<S>() << "\n";
    std::cout << gmp::member_name<0, S>() << "\n";
    std::cout << gmp::member_name<1, S>() << "\n";

    std::cout << "------------------------\n";

    for (const auto& e : gmp::enum_names<enum_test::Color>()) {
        std::cout << e << ", ";
    }

    std::cout << "\n------------------------\n";

    for (const auto& e : gmp::member_names<S>()) {
        std::cout << e << ", ";
    }

    std::cout << "\n------------------------\n";
}
```

**Outputs**:

Clang
```text
int: int
float: float
std::vector<std::string>: std::vector<std::basic_string<char>>
2
b
str
------------------------
Red, Green, Blue, Yellow, 
------------------------
b, str, 
------------------------
```

GCC:
```text
int: int
float: float
std::vector<std::string>: std::vector<std::__cxx11::basic_string<char> >
2
b
str
------------------------
Red, Green, Blue, Yellow, 
------------------------
b, str, 
------------------------
```

MSVC:
```text
int: int
float: float
std::vector<std::string>: std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > >
2
b
str
------------------------
Red, Green, Blue, Yellow, 
------------------------
b, str, 
------------------------
```

## Compile-time Tests
The library includes comprehensive compile-time tests using `static_assert`:
```bash
# Build tests
# The tests are compile-time only - successful build means all tests passed.
cmake -B ./build -DBUILD_TESTS=ON
cmake --build ./build
```

## Acknowledgments
Inspired by Boost.Preprocessor and other metaprogramming libraries.

## License
GMP is licensed under the MIT license, see [LICENSE](https://github.com/lkimuk/gmp/blob/main/LICENSE) for more information.