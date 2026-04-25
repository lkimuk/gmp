---
title: 安装
sidebar_position: 2
---

# 安装

GMP 是 header-only 库，所以安装可以简单到只把发布包里的 `include/` 目录加入编译器 include path。若你的项目已经使用 CMake，也可以先安装 GMP，再通过 `find_package` 引入。

## 使用发布头文件

从最新 release 下载 `include` 压缩包：

[Download include.zip](https://github.com/lkimuk/gmp/releases/download/v0.3.0/include.zip)

解压到你的项目或第三方依赖目录，然后包含聚合头文件：

```cpp
#include <gmp/gmp.hpp>
```

这是试用 GMP 或把 GMP vendoring 到现有代码库中最直接的方式。

## 通过 CMake 安装

克隆、构建并安装项目：

```bash
git clone https://github.com/lkimuk/gmp.git
cd gmp
cmake -B ./build
cmake --build ./build
cmake --install ./build
```

Linux 和 macOS 上是否需要 `sudo` 取决于你选择的安装前缀。

在另一个 CMake 项目中使用 GMP：

```cmake
find_package(gmp 0.3.0 REQUIRED)
target_link_libraries(your_target PRIVATE gmp::gmp)
```

## 编译器要求

库有两层兼容性：

| 功能区域 | 标准 |
|----------|------|
| 宏元编程 | C++11 及之后版本 |
| 泛型设计模式 | C++11 及之后版本 |
| 反射元编程 | C++20 及之后版本 |
| 命名操作符 | C++20 及之后版本 |

C++20 功能推荐最低编译器版本：

| 编译器 | 最低版本 |
|--------|----------|
| MSVC   | 19.37+   |
| GCC    | 11.1+    |
| Clang  | 18.1.0+  |
