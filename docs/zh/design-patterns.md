# 通用设计模式

语言：简体中文 | [English](../design-patterns.html)

通用设计模式模块提供可复用的基础设施工具，包括 spin lock、CRTP 单例和运行时对象工厂。

本模块支持 **C++11**，在更高标准下体验会更好。

## 主头文件

```cpp
#include <gmp/dp/lock.hpp>
#include <gmp/dp/singleton.hpp>
#include <gmp/dp/object_factory.hpp>
```

或者使用：

```cpp
#include <gmp/gmp.hpp>
```

## 适用场景

- 希望复用一个轻量级单例工具，而不引入完整框架
- 希望通过字符串或标识符在运行时选择具体产品类型
- 希望使用一个足够小的低层同步原语

## 组件

- `spin_lock`：基于 `std::atomic_flag` 的轻量级同步原语
- `singleton<T, LongLifeTime>`：基于 CRTP 的单例辅助模板
- `object_factory<AbstractProduct, ConstructorArgs...>`：基于单例的运行时工厂
- `GMP_DISABLE_CONSTRUCTION(Class)`：禁用单例派生类的直接构造
- `GMP_FACTORY_REGISTER(...)`：向对象工厂注册具体产品

## 说明

- `singleton` 适合低摩擦的基础设施代码
- `object_factory` 适合集中式构造与运行时按名称选择对象
- `spin_lock` 是 busy-wait 原语，应避免长时间临界区

## 相关页面

- [快速开始](getting-started.html)
- [命名操作符](named-operators.html)
- [API Reference (English)](../api/)
