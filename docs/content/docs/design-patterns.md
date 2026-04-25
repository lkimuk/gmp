---
title: Generic Design Patterns
sidebar_position: 5
---

# Generic Design Patterns

The generic design-patterns module provides small runtime infrastructure helpers that pair well with generative code: a CRTP singleton and a string-keyed object factory. Both are header-only and available from C++11.

Use them through:

```cpp
#include <gmp/dp/singleton.hpp>
#include <gmp/dp/object_factory.hpp>
// or
#include <gmp/gmp.hpp>
```

## Runtime Infrastructure

The two main pieces are:

- `gmp::singleton<T, LongLifeTime>` for process-wide service objects
- `gmp::object_factory<AbstractProduct, ConstructorArgs...>` for creating derived objects by string key

Helper macros:

- `GMP_DISABLE_CONSTRUCTION(Class)` hides direct construction for a singleton-derived class
- `GMP_FACTORY_REGISTER(AbstractProduct, ConstructorArgs, ...)` registers concrete products with an object factory

## Why These Patterns Are Included

Metaprogramming libraries often need a little runtime glue: registries, factories, service-like objects, and product creation behind stable keys. Rewriting those pieces in every project leads to small differences in ownership, lifetime, and registration style.

GMP keeps these patterns compact. `singleton` gives CRTP types a consistent `instance()` entry point. `object_factory` builds a registry around that singleton model and offers raw, `std::shared_ptr`, and `std::unique_ptr` creation APIs.

## Singleton

Derive from `gmp::singleton<T>` and expose behavior on the derived type:

```cpp
#include <gmp/gmp.hpp>
#include <iostream>
#include <string>

struct logger : gmp::singleton<logger> {
  void write(const std::string& message) const {
    std::cout << message << "\n";
  }

  GMP_DISABLE_CONSTRUCTION(logger)
};

int main() {
  logger::instance().write("hello from GMP");
}
```

## Object Factory

Register product types and create them by key:

```cpp
#include <gmp/gmp.hpp>
#include <iostream>
#include <memory>

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
  auto object = gmp::object_factory<shape>::instance().create_unique("circle");
  std::cout << object->name() << "\n";
}
```

Use explicit keys when public names should differ from type names:

```cpp
GMP_FACTORY_REGISTER(shape, (), ("round", circle), ("box", square))

auto round = gmp::object_factory<shape>::instance().create_shared("round");
```

List constructor argument types in the factory specialization when products need arguments:

```cpp
struct command {
  virtual ~command() = default;
  virtual std::string run() const = 0;
};

struct echo_command : command {
  explicit echo_command(std::string text) : text_(std::move(text)) {}
  std::string run() const override { return text_; }
  std::string text_;
};

GMP_FACTORY_REGISTER(command, (std::string), ("echo", echo_command))

auto cmd = gmp::object_factory<command, std::string>::instance().create_unique("echo", "hello");
```
