# Generic Design Patterns

The generic design patterns layer provides reusable infrastructure helpers such as a spin lock, a CRTP singleton, and a runtime object factory.

This module is available in **C++11**, with some conveniences improving under newer standards.

## Main Headers

```cpp
#include <gmp/dp/lock.hpp>
#include <gmp/dp/singleton.hpp>
#include <gmp/dp/object_factory.hpp>
```

Or:

```cpp
#include <gmp/gmp.hpp>
```

## What This Module Is Good For

- Reusing a small singleton helper without pulling in a framework
- Registering named runtime products behind a common abstract interface
- Providing a tiny lock primitive for simple low-level synchronization scenarios

## Components

- `spin_lock`: a lightweight synchronization primitive based on `std::atomic_flag`
- `singleton<T, LongLifeTime>`: a CRTP-based singleton helper
- `object_factory<AbstractProduct, ConstructorArgs...>`: a singleton-backed runtime factory
- `GMP_DISABLE_CONSTRUCTION(Class)`: disables direct construction for singleton-derived types
- `GMP_FACTORY_REGISTER(...)`: registers concrete products with an object factory

## Example

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

GMP_FACTORY_REGISTER(shape, (), circle)

int main() {
    logger::instance().write("hello from singleton");
    auto product = gmp::object_factory<shape>::instance().create_unique("circle");
    std::cout << product->name() << "\n";
}
```

## Notes

- `singleton` is designed for low-friction infrastructure code and can be used with CRTP-style derived types.
- `object_factory` is a good fit when you need runtime selection by string or identifier while keeping construction logic centralized.
- `spin_lock` should be used thoughtfully, especially around longer critical sections, because it is a busy-wait primitive.

## Related Pages

- [Getting Started](getting-started.md)
- [Named Operators](named-operators.md)
- [API Reference](api/)
