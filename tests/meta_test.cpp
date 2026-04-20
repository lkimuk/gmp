//   ___ __  __ ___ 
//  / __|  \/  | _ \ GMP(Generative Metaprogramming)
// | (_ | |\/| |  _/ version 0.2.0
//  \___|_|  |_|_|   https://github.com/lkimuk/gmp
//
// SPDX-FileCopyrightText: 2023-2026 Gaoxing Li <https://www.cppmore.com/>
// SPDX-License-Identifier: MIT
//
// Compile-time tests for GMP library using static_assert
// If this file compiles, all tests pass!

#include <utility>
#include <iostream>
#include <string>
#include <vector>

#include <gmp/gmp.hpp>

#ifdef _MSC_VER
#   pragma warning(push)
#   pragma warning(disable: 5045 4820)
#endif

struct S {
    double b;
    std::string str;
};

namespace enum_test {

enum class Color { Red, Green, Blue, Yellow };
enum class Empty {};

// Count enumerators
constexpr auto count = gmp::enum_count<Color>();
static_assert(count == 4);
static_assert(gmp::enum_count<Empty>() == 0);

// Can be used in template metaprogramming
template<typename E, size_t N = gmp::enum_count<E>()>
struct EnumTraits {
    static constexpr size_t size = N;
};

static_assert(EnumTraits<Color>::size == 4);

enum class Status { Ok = 200, NotFound = 404, Error = 500 };
enum { A, B, C };  // Unscoped enumeration

// Get individual enumerator names
constexpr auto ok_name = gmp::enum_name<Status::Ok>();
static_assert(ok_name == "Ok");

constexpr auto not_found_name = gmp::enum_name<Status::NotFound>();
static_assert(not_found_name == "NotFound");

// Works with unscoped enums
constexpr auto a_name = gmp::enum_name<A>();
static_assert(a_name == "A");

// Compile-time string comparison
static_assert(gmp::enum_name<Status::Error>() == "Error");

enum class Permission { Read, Write, Execute };

// Get all enumerator names
constexpr auto names = gmp::enum_names<Permission>();
static_assert(names.size() == 3);
static_assert(names[0] == "Read");
static_assert(names[1] == "Write");
static_assert(names[2] == "Execute");

// Iterate over enumerator names at compile-time
template<typename E>
constexpr bool has_enumerator(std::string_view name) {
    constexpr auto e_names = gmp::enum_names<E>();
    for (size_t i = 0; i < e_names.size(); ++i) {
        if (e_names[i] == name) return true;
    }
    return false;
}

static_assert(has_enumerator<Permission>("Write"));
static_assert(!has_enumerator<Permission>("Delete"));

// Empty enum
constexpr auto empty_names = gmp::enum_names<Empty>();
static_assert(empty_names.empty());

} // namespace 

namespace member_test {

struct Point { int x; int y; };
struct Empty {};

// Count members of aggregate types
static_assert(gmp::member_count<Point>() == 2);
static_assert(gmp::member_count<Empty>() == 0);

// Can be used in template constraints
template<typename T>
concept HasTwoMembers = std::is_aggregate_v<T> && gmp::member_count<T>() == 2;

static_assert(HasTwoMembers<Point>);

struct Person {
    std::string name;
    int age;
    double height;
};

// Get individual member names
constexpr auto first_member = gmp::member_name<0, Person>();
static_assert(first_member == "name");

constexpr auto second_member = gmp::member_name<1, Person>();
static_assert(second_member == "age");

constexpr auto third_member = gmp::member_name<2, Person>();
static_assert(third_member == "height");

// Use in static assertions
static_assert(gmp::member_name<0, Person>().size() == 4);

// Template metaprogramming
template<typename T, size_t I>
struct MemberTraits {
    static constexpr auto name = gmp::member_name<I, T>();
    static constexpr size_t index = I;
};

static_assert(MemberTraits<Person, 1>::name == "age");

// These would cause compile-time errors:
// member_name<0, Empty>();     // Error: I < member_count<T>() fails
// member_name<3, Person>();    // Error: Index out of bounds
// member_name<0, int>();       // Error: Not an aggregate

struct Vector3 { float x; float y; float z; };
struct Config { int timeout; bool enabled; std::string host; };

// Get all member names
constexpr auto vec_members = gmp::member_names<Vector3>();
static_assert(vec_members.size() == 3);
static_assert(vec_members[0] == "x");
static_assert(vec_members[1] == "y");
static_assert(vec_members[2] == "z");

// Empty aggregate
constexpr auto empty_members = gmp::member_names<Empty>();
static_assert(empty_members.empty());

// Compile-time iteration
template<typename T>
constexpr bool has_member(std::string_view name) {
    constexpr auto names = gmp::member_names<T>();
    for (size_t i = 0; i < names.size(); ++i) {
        if (names[i] == name) return true;
    }
    return false;
}

static_assert(has_member<Config>("timeout"));
static_assert(has_member<Config>("host"));
static_assert(!has_member<Config>("port"));

// Generate compile-time member name list
template<typename T>
struct MemberList {
    static constexpr auto names = gmp::member_names<T>();
    static constexpr size_t size = names.size();
    
    template<size_t I>
    static constexpr auto get() { return names[I]; }
};

using Vector3Members = MemberList<Vector3>;
static_assert(Vector3Members::size == 3);
static_assert(Vector3Members::get<1>() == "y");

} // namespace member_test

namespace type_size_test {

struct Empty {};

struct Padded {
    char tag;
    int value;
    short code;
};

struct Inner {
    char marker;
    int count;
};

struct Outer {
    char tag;
    Inner inner;
    double score;
};

static_assert(gmp::type_size<Empty>() == 0);
static_assert(gmp::type_size<Padded>() == sizeof(char) + sizeof(int) + sizeof(short));
static_assert(gmp::type_size<Padded>() < sizeof(Padded));
static_assert(gmp::type_size<Outer>() == sizeof(char) + sizeof(char) + sizeof(int) + sizeof(double));
static_assert(gmp::type_size<Outer>() < sizeof(Outer));
static_assert(gmp::type_size<int[3]>() == sizeof(int) * 3);
static_assert(gmp::type_size<int>() == sizeof(int));

} // namespace type_size_test

struct get_weather {
  std::string_view description = "Get weather";

  std::string city;
  std::string unit = "celsius";
  std::array<std::string_view, 5> test;
  std::vector<std::string> haha;

  std::string invoke() const { return "current time"; }
};

template<typename T>
void print() {
    std::cout << "name: " << gmp::type_name<T>() << "\n";
    
    constexpr auto member_names = gmp::member_names<T>();
    constexpr auto member_type_names = gmp::member_type_names<T>();
    
    for (unsigned i = 0; i < member_names.size(); ++i) {
        std::cout << "type: " << member_type_names[i] << " name: " << member_names[i] << "\n";
    }
}

int main() {
    std::cout << "All compile-time tests passed successfully!" << std::endl;
    
    [[maybe_unused]] constexpr auto type = gmp::type_name<int>();
    // auto sv = gmp::type_name<int>();
    std::cout << "int: " << gmp::type_name<int>() << "\n";
    std::cout << "int: " << gmp::type_name<int>().to_string_view() << "\n";
    std::cout << "int: " << gmp::type_name<std::vector<std::string>>() << "\n";

    std::cout << gmp::member_count<S>() << "\n";
    std::cout << gmp::member_name<0, S>() << "\n";
    std::cout << gmp::member_name<1, S>() << "\n";

    std::cout << "------------------------\n";

    for (const auto& e : gmp::enum_names<enum_test::Color>()) {
        std::cout << e << ", ";
    }

    std::cout << "\n------------------------\n";

    for (const auto& e : gmp::member_names<S>()) {
        std::cout << e << ", ";
    }

    std::cout << std::endl;

    print<get_weather>();

    std::cout << "-------------------\n";

    member_test::Person person {
        .name = "Miles",
        .age = 28,
        .height = 183.0
    };

    gmp::for_each_member(person, [](auto&& member_name, auto&& member_value) {
        std::cout << member_name << ": " << member_value << "\n";
    });
}

#ifdef _MSC_VER
#   pragma warning(pop)
#endif

