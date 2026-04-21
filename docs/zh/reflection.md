# 反射元编程

语言：简体中文 | [English](../reflection.html)

反射元编程模块提供编译期固定字符串、类型名、枚举反射以及聚合类型成员内省能力。

本模块需要 **C++20**。

## 主头文件

```cpp
#include <gmp/meta/meta.hpp>
```

也可以通过：

```cpp
#include <gmp/gmp.hpp>
```

## 适用场景

- 在编译期生成可读的类型名
- 无需手写查表即可遍历枚举值与名称
- 为序列化、调试或元数据提取提供聚合类型成员访问
- 基于 NTTP 与 constexpr 字符串构建更强的编译期工具

## 功能分组

### 固定字符串与类型工具

- `fixed_string`
- `operator+(fixed_string, fixed_string)`
- `operator""_fs`
- `to_fixed_string_v<N>`
- `type_name<T>()`
- `pretty_type_name<T>()()`
- `remove_all<Values...>(constant_arg_t<fixed_string>)`

### 基础工具

- `constant_arg_t<V>`
- `constant_arg<V>`
- `any`
- `as_value<T>()`

### 枚举反射

- `enum_count<E>()`
- `enum_name<V>()`
- `enum_names<E>()`
- `enum_values<E>()`
- `enum_entries<E>()`
- `enum_index(value)`
- `enum_cast<E>(name)`
- `GMP_ENUM_RANGE(Enum, Min, Max)`
- `GMP_ENUM_VALUES(Enum, ...)`

### 聚合类型内省

- `member_count<T>()`
- `member_name<I, T>()`
- `member_names<T>()`
- `member_type_t<I, T>`
- `member_type_names<T>()`
- `member_ref<I>(obj)`
- `for_each_member(obj, fn)`
- `type_size<T>()`

## 实用说明

- `type_name<T>()` 更接近编译器原始输出，而 `pretty_type_name<T>()()` 会在支持的场景下给出更易读的结果
- 当默认枚举扫描范围不合适时，可以通过 `GMP_ENUM_RANGE` 或 `GMP_ENUM_VALUES` 自定义
- 聚合类型内省最适合减少结构化样板代码

## 相关页面

- [快速开始](getting-started.html)
- [命名操作符](named-operators.html)
- [API Reference (English)](../api/)
