---
title: 序列化与反序列化
sidebar_position: 5
---

# 序列化与反序列化

GMP 可以直接序列化可反射 aggregate，不需要注册、宏或手写成员表。基础类型、字符串、枚举、`optional`、常用序列与集合、字符串键 map、tuple、variant 和嵌套 aggregate 均由同一套递归引擎自动处理。

```cpp
struct address {
    std::string city;
    int postcode;
};

struct person {
    std::string name;
    int age;
    std::optional<std::string> nickname;
    address home;
};

person value{"Miles", 28, std::nullopt, {"Shanghai", 200000}};

auto json = gmp::to_json(value);
auto decoded = gmp::from_json<person>(*json);

auto xml = gmp::to_xml(value);
auto xml_decoded = gmp::from_xml<person>(*xml);
```

默认 API 返回 `gmp::serialization_result<T>`。错误包含稳定错误码、说明、反射字段路径，以及适用时的解析位置。需要异常接口时，可以使用 JSON 和 XML 各自的 `*_or_throw` 便捷接口。

## 默认规则

- aggregate 编码为以反射成员名作为 key 的对象。
- enum 默认按反射名称编码；数值形式反序列化需要显式开启。
- 缺失的 `optional` 成员得到 `nullopt`；其他成员默认视为 required。
- 未知字段和重复字段默认拒绝，也可以通过策略调整。
- 非有限浮点数、整数溢出、非法 Unicode、过深嵌套和超限输入均会失败。
- 裸指针、循环对象图、多态构造和 C 数组不会被库擅自猜测。非字符串 key 的 map 使用可移植的 `[[key,value], ...]` 表示。

## 字段级 schema 定制

`serialization_schema<T>` 只描述例外字段，其余结构仍由反射自动生成。通过 `static constexpr auto fields = gmp::define_schema(...)` 声明 `gmp::field<"member">`，并使用 `.name<"wire">()`、`.alias<"legacy">()`、`.transient()`、`.defaulted<Value>()`、`.default_with<Provider>()`。成员引用、wire 名冲突和重复 descriptor 都会在编译期检查。

## 完整类型定制

只有类型无法使用自动表示，或者协议明确要求另一种表示时，才特化 `serialization_traits<T>`。显式 traits 的优先级高于所有自动规则，编码和解码分别检测。

## 架构

`basic_serializer<Writer>` 和 `basic_deserializer<Reader>` 采用与格式无关的 archive 驱动。JSON 与 XML 输出都使用直接事件 writer，不构造 DOM。解析过程先生成受深度和容量限制的 `serialization_value` 树，再由共享 reader 应用 schema、递归和定制策略。`serialization_value` 加上 `value_writer/value_reader` 也可作为公开的格式无关后端。

## XML 表示

XML 使用带版本、保留类型信息的 GMP 词汇，而不是从任意业务 XML 中猜测 C++ 类型：

```xml
<gmp version="1">
  <value kind="object">
    <member name="city"><value kind="string">Shanghai</value></member>
  </value>
</gmp>
```

解析器支持 XML 1.0 UTF-8 声明、预定义实体、数字字符引用和标准属性引号，并拒绝 DTD 与外部实体。输入只接受这套 GMP 元素词汇；该 API 并非任意 XML 到对象的通用映射器。
