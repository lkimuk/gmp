# 宏元编程

语言：简体中文 | [English](../macro-metaprogramming.html)

宏元编程模块提供一组 C++ 预处理器工具，用于布尔逻辑、算术、tuple 操作、迭代、重载分发以及命名空间生成。

本模块支持 **C++11**。

## 主头文件

```cpp
#include <gmp/macro/macro.hpp>
```

也可以通过总入口头文件使用：

```cpp
#include <gmp/gmp.hpp>
```

## 适用场景

- 从一次宏调用生成重复声明
- 根据参数数量或 token 形式分发到不同宏实现
- 在不引入模板的情况下操作预处理器 tuple
- 构建轻量级注册、展开或命名空间生成 DSL

## 功能分组

### 宏工具

- 布尔操作：`GMP_BOOL`、`GMP_NOT`、`GMP_AND`、`GMP_OR`、`GMP_XOR`、`GMP_IMPLIES`
- 算术宏：`GMP_INC`、`GMP_DEC`、`GMP_ADD`、`GMP_SUB`
- 比较宏：`GMP_EQUAL_INT`、`GMP_GREATER_INT`、`GMP_GREATER_EQUAL_INT`、`GMP_LESS_INT`、`GMP_LESS_EQUAL_INT`、`GMP_EQUAL_INT_INDEPENDENT`
- 条件宏：`GMP_IF`、`GMP_IF_THEN_ELSE`
- 字符串化与拼接：`GMP_STRINGIFY`、`GMP_CONCAT`、`GMP_CONCATS`
- 可变参数处理：`GMP_SIZE_OF_VAARGS`、`GMP_GET_N`、`GMP_GET_FIRST_N`、`GMP_IS_EMPTY`
- 工具算法：`GMP_MAX`、`GMP_MIN`、`GMP_MINMAX`、`GMP_MAXMIN`、`GMP_SWAP`
- 其他工具：`GMP_REMOVE_TRAILING_COMMA`、`GMP_IDENTIFIERS`

### Tuple 操作

- 大小与访问：`GMP_TUPLE_SIZE`、`GMP_GET_TUPLE`
- 修改：`GMP_TUPLE_APPEND`、`GMP_TUPLE_PREPEND`、`GMP_TUPLE_CONCAT`
- 切片：`GMP_TUPLE_SKIP`、`GMP_TUPLE_TAKE`
- 检测：`GMP_IS_TUPLE`

### 高级能力

- 循环宏：`GMP_REPEAT`、`GMP_WHILE`、`GMP_FOR_EACH`、`GMP_FOR_EACH_INDEPENDENT`
- 重载分发：`GMP_OVERLOAD_INVOKE`
- 展开控制：`GMP_EXPAND`、`GMP_EVAL`、`GMP_DEFER`
- 下标序列生成：`GMP_MAKE_INDEX_SEQUENCE`、`GMP_RANGE`
- 命名空间生成：`GMP_GENERATE_NAMESPACES_BEGIN`、`GMP_GENERATE_NAMESPACES_END`

## 示例

```cpp
#include <gmp/gmp.hpp>

static_assert(GMP_BOOL(42) == 1, "Non-zero values are true");
static_assert(GMP_NOT(0) == 1, "NOT false is true");
static_assert(GMP_AND(1, 1) == 1, "Logical AND");
static_assert(GMP_ADD(2, 3) == 5, "Addition");
static_assert(GMP_TUPLE_SIZE((a, b, c)) == 3, "Tuple size");

#define PRINT(x) std::cout << x << " ";
GMP_FOR_EACH(PRINT, 1, 2, 3)
```

## 说明

- 这一层适合 token 级操作，而不是类型级计算
- 这里的 tuple 指 `(a, b, c)` 这种预处理器 tuple，不是 `std::tuple`
- `GMP_OVERLOAD_INVOKE` 很适合构建多入口的宏前端

## 相关页面

- [快速开始](getting-started.html)
- [反射元编程](reflection.html)
- [API Reference (English)](../api/)
