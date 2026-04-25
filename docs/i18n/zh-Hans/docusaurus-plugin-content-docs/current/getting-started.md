---
title: 快速开始
sidebar_position: 3
---

# 快速开始

把 GMP 放到 include path 后，可以先从聚合头文件开始：

```cpp
#include <gmp/gmp.hpp>
```

探索库功能时，聚合头文件最方便。在更大的项目里，也可以只包含实际使用的模块头文件。

## 试一个小例子

如果想先不配置本地项目，可以直接打开在线示例：

[Compiler Explorer Demo](https://godbolt.org/z/W156818n5)

本地 CMake 项目在安装后链接导入 target：

```cmake
find_package(gmp 0.3.0 REQUIRED)
target_link_libraries(your_target PRIVATE gmp::gmp)
```

然后按所使用模块需要的 C++ 标准编译你的 target。宏元编程和设计模式工具支持 C++11；反射和命名操作符需要 C++20。

## 选择合适的模块

根据问题形态选择入口：

- 需要预处理期重复、token 操作或生成声明时，使用 **宏元编程**。
- 需要在编译期获得枚举名、类型名、聚合成员名、成员类型或成员引用时，使用 **反射元编程**。
- 希望 callable 像操作符一样放在两个操作数之间时，使用 **命名操作符**。
- 需要可复用 singleton 服务或字符串 key 对象工厂时，使用 **泛型设计模式**。

## 构建测试

如果你在修改 GMP 本身，可以启用并构建测试：

```bash
cmake -B ./build -DBUILD_TESTS=ON
cmake --build ./build
```

多数测试以编译期验证为主，因此成功构建本身就是有意义的验证。
