---
title: 命名操作符
sidebar_position: 4
---

# 命名操作符

命名操作符让一个 callable 出现在两个操作数之间。通过 `gmp::make_named_operator` 创建的 token 可以参与生成的操作符对，例如 `lhs ^op^ rhs` 会调用 `op` 内部保存的 callable。

入口头文件：

```cpp
#include <gmp/meta/named_operator.hpp>
// 或
#include <gmp/gmp.hpp>
```

## 基于 callable 的中缀语法

默认支持这些形式：

- `lhs ^op^ rhs`
- `lhs <op> rhs`
- `lhs +op+ rhs`
- `lhs *op* rhs`
- `lhs -op- rhs`
- `lhs /op/ rhs`
- `lhs %op% rhs`
- `lhs &op& rhs`
- `lhs |op| rhs`

callable 按值保存。左侧操作数如果是 lvalue 就按引用保存，如果是 rvalue 就按值保存；右侧操作数在表达式完成时转发。

## 适合使用的场景

命名操作符适合小型 DSL 和表达式密集的代码：当某个领域操作位于两个值之间比包在函数调用里更自然时，它能改善可读性。

它不适合替代所有普通函数调用。更适合表达组合、连接、匹配、绑定或符号化实验。

## 基本用法

创建 token：

```cpp
#include <cassert>
#include <gmp/gmp.hpp>

int main() {
  auto add = gmp::make_named_operator([](int lhs, int rhs) {
    return lhs + rhs;
  });

  assert((10 ^add^ 3) == 13);
  assert((10 <add> 3) == 13);
  assert((10 +add+ 3) == 13);
}
```

callable 可以使用任意匹配左右操作数的签名：

```cpp
auto join = gmp::make_named_operator([](std::string lhs, std::string rhs) {
  return lhs + "/" + rhs;
});

assert(("usr" ^join^ "local") == "usr/local");
```

需要修改左侧 lvalue 时也可以保留引用语义：

```cpp
auto add_assign = gmp::make_named_operator([](int& lhs, int rhs) -> int& {
  lhs += rhs;
  return lhs;
});

int value = 40;
value ^add_assign^ 2;
```
