# 快速开始

语言：简体中文 | [English](../getting-started.html)

本页介绍 GMP 的编译器要求、安装方式以及最短上手路径。

## GMP 包含什么

GMP 主要分为四部分：

- 宏元编程：用于预处理阶段的组合与代码生成
- 反射元编程：用于编译期类型与聚合类型检查
- 命名操作符：用于自定义中缀表达式风格语法
- 通用设计模式：提供轻量级运行时基础设施工具

## 编译器支持

GMP 的不同模块对语言标准的要求不同。

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

如果只需要部分模块，也可以按功能包含更细粒度的头文件：

```cpp
#include <gmp/macro/macro.hpp>
#include <gmp/meta/meta.hpp>
#include <gmp/meta/named_operator.hpp>
#include <gmp/dp/singleton.hpp>
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

一个典型的 consumer 配置如下：

```cmake
cmake_minimum_required(VERSION 3.16)
project(example LANGUAGES CXX)

find_package(gmp 0.3.0 REQUIRED)

add_executable(example main.cpp)
target_link_libraries(example PRIVATE gmp::gmp)
target_compile_features(example PRIVATE cxx_std_20)
```

如果只依赖宏模块或设计模式模块，可以将标准降到 `cxx_std_11`。

## 第一个例子

```cpp
#include <gmp/gmp.hpp>

struct logger : gmp::singleton<logger> {
    void write(const char* text) const {}
    GMP_DISABLE_CONSTRUCTION(logger)
};

int main() {
    static_assert(GMP_ADD(2, 3) == 5);
    logger::instance().write("hello");
}
```

这个例子同时使用了一个 C++11 宏能力和一个通用设计模式工具。反射和命名操作符相关功能需要在 C++20 下使用。

## 运行测试

GMP 当前测试以 `static_assert` 与构建期验证为主：

```bash
cmake -B ./build -DBUILD_TESTS=ON
cmake --build ./build
```

## 推荐阅读顺序

- [宏元编程](macro-metaprogramming.html)
- [反射元编程](reflection.html)
- [命名操作符](named-operators.html)
- [通用设计模式](design-patterns.html)
- [API Reference (English)](../api/)

## 语言说明

- 手写指南同时维护英文与简体中文
- [API Reference](../api/) 目前仅提供英文版本
