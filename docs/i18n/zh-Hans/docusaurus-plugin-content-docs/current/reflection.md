---
title: 反射元编程
sidebar_position: 4
---

# 反射元编程

反射元编程模块提供编译期固定字符串、类型名、枚举反射以及聚合类型成员内省能力。

本模块需要 **C++20**。

## 主头文件

```cpp
#include <gmp/meta/meta.hpp>
```

## 功能分组

### 固定字符串与类型工具

- `fixed_string`
- `operator+(fixed_string, fixed_string)`
- `operator""_fs`
- `to_fixed_string_v<N>`
- `type_name<T>()`
- `pretty_type_name<T>()()`

### 枚举反射

- `enum_count<E>()`
- `enum_name<V>()`
- `enum_names<E>()`
- `enum_values<E>()`
- `enum_entries<E>()`
- `enum_cast<E>(name)`

## 相关页面

- [快速开始](./getting-started.md)
- [命名操作符](./named-operators.md)
- [API Reference (English)](https://lkimuk.github.io/gmp/api/)
