---
title: GMP 文档
slug: /
sidebar_position: 1
---

# GMP 文档

**GMP** 是一个面向编译时代码生成的 C++ 头文件式元编程库。

它包含四个互补模块：

- **宏元编程**：面向预处理器的代码生成与 token 操作
- **反射元编程**：编译期类型、枚举和聚合类型反射
- **命名操作符**：用于构建更易读的中缀 DSL
- **通用设计模式**：提供单例、同步原语和对象工厂等基础设施工具

## 快速入口

- [快速开始](./getting-started.md)
- [宏元编程](./macro-metaprogramming.md)
- [反射元编程](./reflection.md)
- [命名操作符](./named-operators.md)
- [通用设计模式](./design-patterns.md)
- [API Reference (English)](https://lkimuk.github.io/gmp/api/)

## 功能概览

| 模块 | 最低语言标准 | 说明 |
|------|--------------|------|
| 宏元编程 | C++11 | 预处理器工具、tuple 操作、循环与重载分发 |
| 反射元编程 | C++20 | 固定字符串、枚举反射、聚合类型内省 |
| 命名操作符 | C++20 | 自定义中缀语法与 callable 绑定 |
| 通用设计模式 | C++11 | 单例、spin lock、对象工厂 |

## 多语言说明

- 英文文档是当前的主版本
- 简体中文优先覆盖使用指南与概念说明
- [API Reference](https://lkimuk.github.io/gmp/api/) 目前仅提供英文版本
