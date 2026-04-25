---
title: 反射元编程
sidebar_position: 3
---

# 反射元编程

GMP 的反射层为 C++20 提供编译期内省能力，覆盖库代码经常需要的几类信息：类型名、枚举值、枚举名、聚合成员名、聚合成员类型和成员引用。

入口头文件：

```cpp
#include <gmp/meta/meta.hpp>
// 或
#include <gmp/gmp.hpp>
```

## 编译期元数据

反射模块包括：

- `gmp::fixed_string`、`operator""_fs`、`gmp::to_fixed_string_v<N>`：编译期字符串
- `gmp::type_name<T>()`、`gmp::pretty_type_name<T>()()`：类型名
- `gmp::enum_values<E>()`、`gmp::enum_names<E>()`、`gmp::enum_entries<E>()`、`gmp::enum_cast<E>(name)`：枚举反射
- `GMP_ENUM_RANGE`、`GMP_ENUM_VALUES`：枚举扫描定制
- `gmp::member_count<T>()`、`gmp::member_name<I, T>()`、`gmp::member_names<T>()`、`gmp::member_type_t<I, T>`、`gmp::member_ref<I>(object)`、`gmp::for_each_member(object, fn)`：聚合类型内省

## 减少手写表格

没有反射时，项目里经常要重复维护结构信息：枚举到字符串表、字符串到枚举查找、调试打印、序列化元数据和成员列表。

GMP 让这些信息尽量靠近 C++ 声明本身。编译器负责提供名字和结构，用户代码消费小型编译期数组或成员引用。

## 枚举反射

普通枚举值可以在编译期发现值和名字：

```cpp
#include <gmp/gmp.hpp>

enum class color { red, green, blue };

static_assert(gmp::enum_count<color>() == 3);
static_assert(gmp::enum_names<color>()[1] == "green");
static_assert(gmp::enum_cast<color>("blue").value() == color::blue);
```

稀疏枚举或超出默认扫描范围的枚举可以显式指定：

```cpp
enum class status { ok = 200, not_found = 404, error = 500 };

GMP_ENUM_VALUES(status, status::ok, status::not_found, status::error);
```

## 聚合类型内省

按成员索引检查聚合类型：

```cpp
#include <gmp/gmp.hpp>
#include <string>
#include <type_traits>

struct person {
  std::string name;
  int age;
};

static_assert(gmp::member_count<person>() == 2);
static_assert(gmp::member_name<0, person>() == "name");
static_assert(std::is_same_v<gmp::member_type_t<1, person>, int>);
```

遍历运行时对象：

```cpp
person p{"Miles", 28};

gmp::member_ref<1>(p) = 29;

gmp::for_each_member(p, [](std::string_view name, auto&& value) {
  std::cout << name << ": " << value << "\n";
});
```
