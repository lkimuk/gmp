---
title: Serialization
sidebar_position: 5
---

# Serialization

GMP serializes reflected aggregates without registration, macros, or member tables. The same recursive engine handles scalar values, strings, enums, optionals, standard sequences and sets, string-keyed maps, tuples, variants, and nested aggregates.

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

The non-throwing APIs return `gmp::serialization_result<T>`. Errors contain a stable error code, a message, the reflected field path, and a parser offset when applicable. `to_json_or_throw`/`from_json_or_throw` and `to_xml_or_throw`/`from_xml_or_throw` are convenience wrappers for exception-based code.

## Default rules

- Reflected aggregates are objects whose keys are reflected member names.
- Enums are encoded by reflected name. Numeric decoding is opt-in.
- Missing `std::optional` members become `std::nullopt`; other missing members are errors unless the schema supplies a default.
- Unknown and duplicate fields are rejected by default and can be changed through `deserialization_options`.
- Non-finite floating-point values, overflows, invalid Unicode, excessive nesting, and oversized inputs are rejected.
- Raw pointers, object identity, cyclic graphs, polymorphic construction, and C arrays are not guessed automatically. Maps with non-string keys use a portable array-of-`[key,value]` entries representation.

## Field-level schema customization

`serialization_schema<T>` changes only exceptional fields while retaining automatic reflection for the rest of the aggregate. Declare `static constexpr auto fields = gmp::define_schema(...)` with `gmp::field<"member">`; descriptors support `.name<"wire">()`, `.alias<"legacy">()`, `.transient()`, `.defaulted<Value>()`, and `.default_with<Provider>()`. Member references, wire-name collisions, and duplicate descriptors are checked at compile time.

## Full type customization

Use `serialization_traits<T>` only when a type cannot or should not use its reflected representation. The serializer and deserializer arguments preserve recursion policy and let custom implementations reuse the normal engine. An explicit trait takes precedence over automatic handling.

## Architecture

`basic_serializer<Writer>` and `basic_deserializer<Reader>` are archive-driven and format-neutral. JSON and XML writing use direct event writers and do not build a DOM. Parsing produces a bounded `serialization_value` tree, then the shared reader machinery applies schema, recursion, and customization policies. `serialization_value` plus `value_writer`/`value_reader` is also available as a public format-neutral backend.

## XML representation

XML uses a versioned, type-preserving GMP vocabulary rather than guessing C++ types from arbitrary business XML:

```xml
<gmp version="1">
  <value kind="object">
    <member name="city"><value kind="string">Shanghai</value></member>
  </value>
</gmp>
```

The parser accepts XML 1.0 UTF-8 declarations, predefined entities, numeric character references, and normal XML attribute quoting. It rejects DTDs and external entities. Only the GMP elements shown by this vocabulary are accepted; this API is not a general XML-to-object mapper.
