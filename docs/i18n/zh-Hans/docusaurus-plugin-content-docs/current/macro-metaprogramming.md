---
title: 宏元编程
sidebar_position: 3
---

# 宏元编程

宏元编程模块提供一组 C++ 预处理器工具，用于布尔逻辑、算术、tuple 操作、迭代、重载分发以及命名空间生成。

本模块支持 **C++11**。

## 主头文件

```cpp
#include <gmp/macro/macro.hpp>
```

## 功能分组

### 宏工具

- 布尔操作：`GMP_BOOL`、`GMP_NOT`、`GMP_AND`、`GMP_OR`、`GMP_XOR`、`GMP_IMPLIES`
- 算术宏：`GMP_INC`、`GMP_DEC`、`GMP_ADD`、`GMP_SUB`
- 比较宏：`GMP_EQUAL_INT`、`GMP_GREATER_INT`、`GMP_GREATER_EQUAL_INT`、`GMP_LESS_INT`、`GMP_LESS_EQUAL_INT`、`GMP_EQUAL_INT_INDEPENDENT`
- 条件宏：`GMP_IF`、`GMP_IF_THEN_ELSE`
- 字符串化与拼接：`GMP_STRINGIFY`、`GMP_CONCAT`、`GMP_CONCATS`

## 相关页面

- [快速开始](./getting-started.md)
- [反射元编程](./reflection.md)
- [API Reference (English)](https://lkimuk.github.io/gmp/api/)
