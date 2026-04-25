---
title: 概览
slug: /
sidebar_position: 1
---

# 概览

GMP 是一个面向 C++20 的产生式元编程库，借其可在编译期自动产生成千上万行 C++ 代码。

一个编程语言的代码生成能力，决定了库和框的灵活性与简洁性。然而，C++ 的代码生成能力一直不像其他语言那般强大，Python、Java、C#、Go、TypeScript 等语言具有动态反射，Rust 也有编译期生成代码的机制 Procedural Macros（过程宏），C++ 只有从 C 继承而来的原始替换宏、模板元编程、常量表达式和 C++26 才引进的静态反射。

先不论静态反射提供的 Spec API 代码注入模型有多弱小，哪一年 C++26 才能在实际项目中普及开来？

事实上，C++20 已经具备的代码生成能力，并非那般弱小。它已经能够通过一些技巧实现静态反射，满足序列化/反序列化、ORM 框架、日志、调试等常见场景。并且，代码生成方式也不只反射一种机制，C++ 中还存在宏元编程、模板元编程和常量表达式元编程，它们都适应不同的代码生成场景，组合起来使用，效果不弱。

但是，这些元编程，有的处于石器时间，如宏元编程；有的太晦涩，如模板元编程；有的又太精微，如常量表达式元编程。只有专家水平，才能挥动这些利器。即便是如今的 AI 编程，在这方面也差许多，因为这种级别的开源作品寥寥，训练语料不足。于是，它们成了少数人的工具。

也因如此，目前比较流行的一些框架，都不是用 C++ 写的，这是语言能力欠缺和表达力弱的原因。如当前的 Agent Framework，都是使用 Python、C# 或 TypeScript 开发的。

GMP 库就是为了解决这个问题而诞生的，其最早出现在 2023 年，当时我还在摸索宏元编程（这是最难的部分），最终产生了宏元编程工具集。2024 年，我开始深入模板元编程和反射元编程，年底开始编写并完成了 C++ Generative Metaprogramming 一书，此时 GMP 库已具雏形。其后，搁置半载，2025 年底开始完善宏元编程模块，读过 CGM 一书的，定然知晓这块的复杂性。最终，2026 年一月发布第一版，只含宏元编程模块，三月发布第二版，增加反射元编程模块，四月发布第三版，完善宏元编程和反射元编程模块，并新增泛型设计模式和命名操作符模块。

从 0 到 1 最难的部分早已完成，如今有了 AI 的加持，想必要不了多久，GMP 就可以迭代出许多版本。

总而言之，GMP 为 C++ 提供了全面的产生式元编程能力，包含宏元编程、反射元编程和其他常量元编程能力。

针对每个模块，下面各展示一个在真实项目中的使用代码。

第一，宏元编程。

```cpp
#define GMP_FIELD_GETTER_DEFINE(i) \
    template<std::size_t I, typename T> \
    consteval auto field_getter(constant_arg_t<i>) { \
        const auto& [GMP_GET_FIRST_N(i, GMP_IDENTIFIERS)] = as_value<std::remove_cv_t<T>>(); \
        const auto get_ptr = [](const auto&... fields) { \
            return std::get<I>(std::tuple{&fields...}); \
        }; \
        return get_ptr(GMP_GET_FIRST_N(i, GMP_IDENTIFIERS)); \
    }

GMP_FOR_EACH(GMP_FIELD_GETTER_DEFINE, GMP_RANGE(1, 256))
```

这是 GMP 反射元编程模块实现代码。它用来自动生成 255 个 field_getter() 重载，将原本的 3000 行左右的代码，缩减至 10 行左右。这里此类开源项目中，最简的实现。

这就是宏元编程的威力。

第二，反射元编程。

```cpp
template<typename T>
json build_json_value(T&& value) {
  using value_type = std::remove_cvref_t<T>;

  if constexpr (is_field_v<value_type>) {
    return build_json_value(value.value);
  }
  else if constexpr (std::is_aggregate_v<value_type>) {
    auto result = json::object();
    gmp::for_each_member(std::forward<T>(value), [&](auto&& mem_name, auto&& mem_value) {
      result[std::string(mem_name)] =
        build_json_value(std::forward<decltype(mem_value)>(mem_value));
    });
    return result;
  }
  // ...
}
```

这是 Wuwe Agent Framework 中实现 Tool Use 功能的部分代码，做了简化。

Tool Use 为 Agent 提供外部工具调用的能力，需要序列化和反序列化工具类。如果没有反射，这部分功能不可能优雅地实现，工具的定制方式也会很糟糕。

第三，命名操作符。

```cpp
auto classify(const std::string& request) {
  using wuwe::says;
  return wuwe::make_message()
    << ("system" <says> "You are an incident triage router.\n"
                        "Classify each request into exactly one label:\n"
                        "- security: account takeover, suspicious login, data leak, phishing\n"
                        "- infra: outage, timeout, high latency, service unavailable\n"
                        "- data: wrong report, missing records, dashboard mismatch\n"
                        "- unclear: none of the above or not enough context\n\n"
                        "Return ONLY one word: security, infra, data, or unclear.")
    << ("user" <says> request);
}
```

这是 Wuwe Agent Framework 中实现请求消息列表的方式。`<says>` 这种原本 C++ 无法直接表达的效果，便可由命名操作符轻松实现。

第四，泛型设计模式。

```cpp
GMP_FACTORY_REGISTER(llm_client, llm_config,
  (OpenAI, openai_llm_client),
  (Anthropic, anthropic_llm_client),
  (Google, google_llm_client),
  (OpenRouter, openrouter_llm_client),
  (DeepSeek, deepseek_llm_client)
)

using llm_client_factory = gmp::object_factory<llm_client, llm_config>;

int main() {
  wuwe::llm_config config {
    .base_url = "https://xxx.ai/api",
    .model = "xxx",
    .timeout = 30000,
  };

  wuwe::llm_client_factory factory;
  auto openai_client = factory.create_shared("OpenAI", config);
  auto anthropic_client = factory.create_shared("Anthropic", config);
  auto google_client = factory.create_shared("Google", config);
  auto openrouter_client = factory.create_shared("OpenRouter", config);
  auto deepseek_client = factory.create_shared("DeepSeek", config);
}
```

这是 Wuwe Agent Framework 中实现大模型客户端创建的实现。借助 GMP 中提供的对象工厂，后续便能够从字符串动态创建不同的大模型支持客户端。

这是最主要的四个模块，其中实际包含不计其数的组件可用，可在文档中查看 API References。
