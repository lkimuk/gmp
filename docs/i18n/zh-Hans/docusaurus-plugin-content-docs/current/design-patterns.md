---
title: 泛型设计模式
sidebar_position: 5
---

# 泛型设计模式

泛型设计模式模块提供少量运行时基础设施工具，适合与产生式代码配合使用：CRTP singleton 和字符串 key 对象工厂。两者都是 header-only，并支持 C++11。

入口头文件：

```cpp
#include <gmp/dp/singleton.hpp>
#include <gmp/dp/object_factory.hpp>
// 或
#include <gmp/gmp.hpp>
```

## 运行时基础设施

两个主要组件：

- `gmp::singleton<T, LongLifeTime>`：用于进程级服务对象
- `gmp::object_factory<AbstractProduct, ConstructorArgs...>`：根据字符串 key 创建派生对象

辅助宏：

- `GMP_DISABLE_CONSTRUCTION(Class)`：隐藏 singleton 派生类的直接构造
- `GMP_FACTORY_REGISTER(AbstractProduct, ConstructorArgs, ...)`：向对象工厂注册具体产品类型

## 为什么包含这些模式

元编程库经常需要一点运行时胶水：注册表、工厂、服务对象，以及基于稳定 key 的产品创建。每个项目都重新写这些代码，容易在所有权、生命周期和注册风格上出现细微差异。

GMP 把这些模式保持在紧凑接口里。`singleton` 为 CRTP 类型提供统一的 `instance()` 入口。`object_factory` 基于 singleton 模型维护注册表，并支持 raw pointer、`std::shared_ptr` 和 `std::unique_ptr` 创建方式。

## Singleton

从 `gmp::singleton<T>` 派生：

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

注册产品类型并根据 key 创建：

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

当公开 key 不想等于类型名时，可以使用显式 key：

```cpp
GMP_FACTORY_REGISTER(shape, (), ("round", circle), ("box", square))

auto round = gmp::object_factory<shape>::instance().create_shared("round");
```
