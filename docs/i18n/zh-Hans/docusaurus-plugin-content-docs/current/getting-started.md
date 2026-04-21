---
title: 快速开始
sidebar_position: 2
---

# 快速开始

本页介绍 GMP 的编译器要求、安装方式以及最短上手路径。

## GMP 包含什么

GMP 主要分为四部分：

- 宏元编程：用于预处理阶段的组合与代码生成
- 反射元编程：用于编译期类型与聚合类型检查
- 命名操作符：用于自定义中缀表达式风格语法
- 通用设计模式：提供轻量级运行时基础设施工具

## 编译器支持

GMP 的不同模块对语言标准要求不同。

### C++11 及以上

以下模块可在 **C++11** 及更高版本中使用：

- 宏元编程
- 通用设计模式

### C++20 及以上

以下模块需要 **C++20**：

- 反射元编程
- 命名操作符

建议的最低编译器版本：

| 编译器 | 最低版本 |
|--------|----------|
| MSVC | 19.37+ |
| GCC | 11.1+ |
| Clang | 18.1.0+ |

## 在线快速试用

- [Compiler Explorer Demo](https://godbolt.org/z/W156818n5)

## 头文件方式使用

下载发布的头文件后，直接包含 `gmp/gmp.hpp`：

- [Download include.zip](https://github.com/lkimuk/gmp/releases/download/v0.3.0/include.zip)

```cpp
#include <gmp/gmp.hpp>
```

## CMake 集成

先克隆、构建并安装 GMP：

```bash
git clone https://github.com/lkimuk/gmp.git
cd gmp
cmake -B ./build
cmake --build ./build
cmake --install ./build
```

然后在你的工程中这样使用：

```cmake
find_package(gmp 0.3.0 REQUIRED)
target_link_libraries(your_target PRIVATE gmp::gmp)
```

## 推荐阅读顺序

- [宏元编程](./macro-metaprogramming.md)
- [反射元编程](./reflection.md)
- [命名操作符](./named-operators.md)
- [通用设计模式](./design-patterns.md)
- [API Reference (English)](https://lkimuk.github.io/gmp/api/)
