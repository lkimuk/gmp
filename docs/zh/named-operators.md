# 命名操作符

语言：简体中文 | [English](../named-operators.html)

命名操作符模块允许你把 callable 包装成轻量级操作符 token，从而写出自定义中缀风格语法。

本模块需要 **C++20**。

## 主头文件

```cpp
#include <gmp/meta/named_operator.hpp>
```

或者通过：

```cpp
#include <gmp/gmp.hpp>
```

## 适用场景

- 构建更接近领域语言的表达式形式
- 用更紧凑的中缀语法组合二元 callable
- 在保留 move 语义的同时提升表达式可读性

## 亮点

- 支持 `^_^`、`<_>`、`+_+`、`*_*`、`-_-`、`/_/`、`%_%`、`&_&`、`|_|`、`^o^` 等操作符风格语法
- `make_named_operator(...)` 可将 callable 转换为命名操作符 token
- `GMP_GENERATE_NAMED_OPERATOR_PAIRS(...)` 可生成显式操作符配对
- `GMP_GENERATE_NAMED_OPERATOR_IDENTICAL_PAIRS(...)` 可生成左右相同的操作符对
- `GMP_DISABLE_DEFAULT_NAMED_OPERATORS` 可关闭默认操作符集合
- 保留左值/右值类别，适合 move-only 类型和转发敏感场景

## 说明

- 默认操作符形式比较“有个性”，适合局部 DSL
- 当命名操作符确实比普通函数调用更易读时，它最有价值
- 当前 [API Reference](../api/) 仍为英文

## 相关页面

- [反射元编程](reflection.html)
- [通用设计模式](design-patterns.html)
- [API Reference (English)](../api/)
