---
title: 通用设计模式
sidebar_position: 6
---

# 通用设计模式

通用设计模式模块提供可复用的基础设施工具，包括 spin lock、CRTP 单例和运行时对象工厂。

本模块支持 **C++11**。

## 主头文件

```cpp
#include <gmp/dp/lock.hpp>
#include <gmp/dp/singleton.hpp>
#include <gmp/dp/object_factory.hpp>
```

## 组件

- `spin_lock`
- `singleton<T, LongLifeTime>`
- `object_factory<AbstractProduct, ConstructorArgs...>`
- `GMP_DISABLE_CONSTRUCTION(Class)`
- `GMP_FACTORY_REGISTER(...)`

## 相关页面

- [快速开始](./getting-started.md)
- [命名操作符](./named-operators.md)
- [API Reference (English)](https://lkimuk.github.io/gmp/api/)
