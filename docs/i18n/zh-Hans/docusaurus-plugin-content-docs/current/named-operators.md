---
title: 命名操作符
sidebar_position: 5
---

# 命名操作符

命名操作符模块允许你把 callable 包装成轻量级操作符 token，从而写出自定义中缀风格语法。

本模块需要 **C++20**。

## 主头文件

```cpp
#include <gmp/meta/named_operator.hpp>
```

## 亮点

- 支持 `^_^`、`<_>`、`+_+`、`*_*`、`-_-`、`/_/`、`%_%`、`&_&`、`|_|`、`^o^` 等操作符风格语法
- `make_named_operator(...)` 可将 callable 转换为命名操作符 token
- `GMP_DISABLE_DEFAULT_NAMED_OPERATORS` 可关闭默认操作符集合

## 相关页面

- [反射元编程](./reflection.md)
- [通用设计模式](./design-patterns.md)
- [API Reference (English)](https://lkimuk.github.io/gmp/api/)
