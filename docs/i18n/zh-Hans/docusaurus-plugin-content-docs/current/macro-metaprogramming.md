---
title: 宏元编程
sidebar_position: 2
---

# 宏元编程

GMP 的宏层是一个 C++11 预处理器工具箱，用于在编译器解析程序之前生成 token。它处理宏编程中常见但繁琐的部分：参数计数、tuple 风格宏数据、条件展开、重复生成、重载分发、token 拼接和命名空间生成。

入口头文件：

```cpp
#include <gmp/macro/macro.hpp>
// 或
#include <gmp/gmp.hpp>
```

## 预处理器工具层

这个模块围绕几类可复用能力组织：

- 条件展开：`GMP_BOOL`、`GMP_NOT`、`GMP_AND`、`GMP_OR`、`GMP_IF`、`GMP_IF_THEN_ELSE`
- token 工具：`GMP_STRINGIFY`、`GMP_CONCAT`、`GMP_CONCATS`、`GMP_EXPAND`
- 可变参数工具：`GMP_SIZE_OF_VAARGS`、`GMP_GET_N`、`GMP_GET_FIRST_N`、`GMP_IS_EMPTY`
- tuple 工具：`GMP_TUPLE_SIZE`、`GMP_GET_TUPLE`、`GMP_TUPLE_APPEND`、`GMP_TUPLE_TAKE`、`GMP_TUPLE_SKIP`
- 生成工具：`GMP_REPEAT`、`GMP_FOR_EACH`、`GMP_OVERLOAD_INVOKE`、`GMP_RANGE`、`GMP_GENERATE_NAMESPACES_BEGIN`

## 适合使用的场景

模板在 C++ 语法已经存在之后很强，但它不能在解析前创造新的 token。宏元编程仍然适合生成声明、重复相似代码、构造标识符、选择生成的宏重载，或者在较旧标准下完成模板不方便表达的任务。

GMP 为这些模式提供稳定的命名工具。你不需要在每个项目里重新写一套递归宏系统，而是可以用同一组基础设施生成字段、重载入口、分发代码或命名空间包装。

## 常见用法

条件展开：

```cpp
#include <gmp/gmp.hpp>

GMP_IF(1, int enabled;)
GMP_IF_THEN_ELSE(0, int yes;, int no;)
```

把可变参数和 tuple 风格宏值当作数据处理：

```cpp
GMP_SIZE_OF_VAARGS(a, b, c)      // 3
GMP_GET_N(1, a, b, c)            // b

GMP_TUPLE_SIZE((x, y, z))        // 3
GMP_TUPLE_GET(1, (x, y, z))      // y
GMP_TUPLE_APPEND((x, y), z)      // (x, y, z)
GMP_TUPLE_TAKE(2, (x, y, z, w))  // (x, y)
```

从紧凑列表生成重复声明：

```cpp
#define DECLARE_FIELD(name) int name;

struct record {
  GMP_FOR_EACH(DECLARE_FIELD, id, count, flags)
};

#undef DECLARE_FIELD
```

根据参数构造宏名：

```cpp
#define HANDLER_read read_handler
#define HANDLER_read_write read_write_handler

GMP_OVERLOAD_INVOKE(HANDLER, read)        // HANDLER_read
GMP_OVERLOAD_INVOKE(HANDLER, read, write) // HANDLER_read_write
```
