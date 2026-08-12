---
title: Overview
slug: /
sidebar_position: 1
---

# Overview

GMP is a generative metaprogramming library for C++20. With it, C++ can automatically generate thousands of lines of code at compile time.

The code-generation capability of a programming language determines the flexibility and concision of its libraries and frameworks. However, C++ code generation has never been as powerful as it is in many other languages. Python, Java, C#, Go, TypeScript, and others have dynamic reflection. Rust also has a compile-time code-generation mechanism: Procedural Macros. C++ has only the primitive substitution macros inherited from C, template metaprogramming, constant expressions, and static reflection introduced only in C++26.

Leaving aside how weak the code-injection model of the Spec API provided by static reflection may be, in what year will C++26 actually become popular in real projects?

In fact, the code-generation capability already available in C++20 is not that weak. With certain techniques, it can already implement static reflection and satisfy common scenarios such as serialization/deserialization, ORM frameworks, logging, and debugging. Reflection is not the only mechanism for code generation either. C++ also has macro metaprogramming, template metaprogramming, and constant-expression metaprogramming. Each adapts to different code-generation scenarios, and when combined, the result is not weak at all.

But these forms of metaprogramming have their own problems. Some are still in the Stone Age, such as macro metaprogramming; some are too obscure, such as template metaprogramming; and some are too subtle, such as constant-expression metaprogramming. Only expert-level programmers can wield these tools. Even today's AI programming still falls far short here, because open-source works at this level are rare and the training corpus is insufficient. As a result, they have become tools for only a small number of people.

For this reason, many currently popular frameworks are not written in C++. This is caused by deficiencies in language capability and weakness in expressiveness. Current Agent Frameworks, for example, are mostly developed in Python, C#, or TypeScript.

The GMP library was born to solve this problem. It first appeared in 2023, when I was still exploring macro metaprogramming, which is the hardest part, and eventually produced a macro-metaprogramming toolkit. In 2024, I began to go deeper into template metaprogramming and reflection metaprogramming. By the end of that year, I had started and completed the book C++ Generative Metaprogramming, and by then the GMP library had already taken shape. After that, it was set aside for half a year. At the end of 2025, I began improving the macro-metaprogramming module. Anyone who has read CGM will certainly understand the complexity of this part. Finally, the first version was released in January 2026, containing only the macro-metaprogramming module. The second version was released in March, adding the reflection-metaprogramming module. The third version was released in April, improving the macro-metaprogramming and reflection-metaprogramming modules and adding the generic design patterns and named operators modules.

The hardest part, going from 0 to 1, has already been completed. Now, with the help of AI, I believe it will not take long for GMP to iterate through many versions.

In short, GMP provides C++ with comprehensive generative metaprogramming capability, including macro metaprogramming, reflection metaprogramming, and other constant metaprogramming capabilities.

For each module, the following sections show one code example from a real project.

First, macro metaprogramming.

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

This is implementation code from GMP's reflection-metaprogramming module. It automatically generates 255 `field_getter()` overloads, reducing what would otherwise be about 3000 lines of code to around 10 lines. Among open-source projects of this kind, this is the simplest implementation.

This is the power of macro metaprogramming.

Second, reflection metaprogramming.

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

This is simplified code from the Tool Use implementation in Wuwe Agent Framework.

Tool Use gives an Agent the ability to call external tools, which requires serializing and deserializing tool classes. Without reflection, this feature would be impossible to implement elegantly, and the customization model for tools would also be poor.

Third, named operators.

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

This is how Wuwe Agent Framework implements request message lists. The `<says>` effect, which C++ originally cannot express directly, can be implemented easily with named operators.

Fourth, generic design patterns.

```cpp
GMP_FACTORY_REGISTER(llm_client, llm_config,
  ("OpenAI", openai_llm_client),
  ("Anthropic", anthropic_llm_client),
  ("Google", google_llm_client),
  ("OpenRouter", openrouter_llm_client),
  ("DeepSeek", deepseek_llm_client)
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

This is the implementation used in Wuwe Agent Framework to create large language model clients. With the object factory provided by GMP, different LLM provider clients can later be created dynamically from strings.

These are the four main modules. In practice, GMP includes countless usable components, which can be viewed in the API References.
