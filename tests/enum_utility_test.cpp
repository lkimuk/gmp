#include <type_traits>

#include <gmp/gmp.hpp>

enum class color : unsigned char {
    red = 1,
    green = 2,
    blue = 4
};

GMP_ENUM_RANGE(color, 1, 4);

static_assert(gmp::enum_underlying(color::red) == 1);
static_assert(std::is_same_v<
    decltype(gmp::enum_underlying(color::red)),
    unsigned char
>);
static_assert(gmp::enum_contains(color::green));
static_assert(gmp::enum_contains<color>(4));
static_assert(!gmp::enum_contains<color>(3));

int main() {
    if (!gmp::enum_contains(color::red)) {
        return 1;
    }
    if (gmp::enum_contains(static_cast<color>(3))) {
        return 1;
    }
}
