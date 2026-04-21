---
title: API 指南
sidebar_position: 7
---

# API 指南

本项目发布一份由 Doxygen 生成的英文 API 参考。

## 查看 API

- [Open the generated API reference](https://lkimuk.github.io/gmp/api/)

## 本地生成

如果本机安装了 Doxygen，可以执行：

```bash
cmake -B build-docs -DBUILD_DOCS=ON
cmake --build build-docs --target docs
```

生成结果会写入 `static/api/reference/`。

## 语言策略

- 手写指南维护英文与简体中文
- 生成式 API 参考当前仅提供英文
