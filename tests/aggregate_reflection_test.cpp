#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>

#include <gmp/gmp.hpp>

namespace {

struct person {
    std::string name;
    int age;
};

struct empty {};

union reflected_union {
    int integer;
    float floating;
};

struct reference_member {
    int& value;
};

static_assert(gmp::reflectable<person>);
static_assert(gmp::reflectable<empty>);
static_assert(!gmp::reflectable<int>);
static_assert(!gmp::reflectable<int[2]>);
static_assert(!gmp::reflectable<reflected_union>);
static_assert(!gmp::reflectable<reference_member>);
static_assert(gmp::member_count_v<person> == 2);
static_assert(gmp::member_count_v<empty> == 0);

static_assert(gmp::has_member<person>("name"));
static_assert(gmp::has_member<person>("age"));
static_assert(!gmp::has_member<person>("missing"));
static_assert(gmp::member_index<person>("name") == std::optional<std::size_t>{0});
static_assert(gmp::member_index<person>("age") == std::optional<std::size_t>{1});
static_assert(!gmp::member_index<person>("missing").has_value());

static_assert(std::is_same_v<
    decltype(gmp::member_ref<0>(std::declval<person&>())),
    std::string&
>);
static_assert(std::is_same_v<
    decltype(gmp::member_ref<0>(std::declval<const person&>())),
    const std::string&
>);
static_assert(std::is_same_v<
    decltype(gmp::member_ref<0>(std::declval<person&&>())),
    std::string&&
>);

static_assert(noexcept(gmp::for_each_member(
    std::declval<person&>(),
    [](std::string_view, auto&) noexcept {}
)));
static_assert(!noexcept(gmp::for_each_member(
    std::declval<person&>(),
    [](std::string_view, auto&) {}
)));

} // namespace

int main() {
    person value{"Miles", 28};

    auto members = gmp::tie_members(value);
    static_assert(std::is_same_v<
        decltype(members),
        std::tuple<std::string&, int&>
    >);
    std::get<1>(members) = 29;
    if (value.age != 29) {
        return 1;
    }

    const auto sum = gmp::apply_members(value, [](const auto& name, int age) {
        return name.size() + static_cast<std::size_t>(age);
    });
    if (sum != value.name.size() + 29) {
        return 1;
    }

    std::size_t visited_count = 0;
    gmp::for_each_member(value, [&](std::string_view, auto&&) {
        ++visited_count;
    });
    if (visited_count != 2) {
        return 1;
    }

    gmp::for_each_member(empty{}, [](std::string_view, auto&&) {});

    const bool found = gmp::visit_member(value, "age", [](auto&& member) {
        using member_type = std::remove_cvref_t<decltype(member)>;
        if constexpr (std::is_same_v<member_type, int>) {
            member = 30;
        }
    });
    if (!found || value.age != 30) {
        return 1;
    }
    if (gmp::visit_member(value, "missing", [](auto&&) {})) {
        return 1;
    }
}
