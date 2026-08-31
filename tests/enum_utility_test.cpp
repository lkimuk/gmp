#include <limits>
#include <type_traits>

#include <gmp/gmp.hpp>

enum class color : unsigned char {
    red = 1,
    green = 2,
    blue = 4
};

GMP_ENUM_RANGE(color, 1, 4);

enum class signed_edge : int {
    minus_one = -1
};

GMP_ENUM_VALUES(signed_edge, signed_edge::minus_one);

enum class unsigned_edge : unsigned {
    maximum = std::numeric_limits<unsigned>::max()
};

GMP_ENUM_VALUES(unsigned_edge, unsigned_edge::maximum);

enum class character_edge : char {
    zero = 0
};

GMP_ENUM_VALUES(character_edge, character_edge::zero);

static_assert(gmp::enum_underlying(color::red) == 1);
static_assert(std::is_same_v<
    decltype(gmp::enum_underlying(color::red)),
    unsigned char
>);
static_assert(gmp::enum_contains(color::green));
static_assert(gmp::enum_contains<color>(4));
static_assert(!gmp::enum_contains<color>(3));
static_assert(gmp::enum_contains<signed_edge>(-1));
static_assert(!gmp::enum_contains<signed_edge>(std::numeric_limits<unsigned>::max()));
static_assert(gmp::enum_contains<unsigned_edge>(std::numeric_limits<unsigned>::max()));
static_assert(!gmp::enum_contains<unsigned_edge>(-1));
static_assert(gmp::enum_contains<color>(char{1}));
static_assert(gmp::enum_contains<color>(wchar_t{1}));
static_assert(gmp::enum_contains<color>(char16_t{1}));
static_assert(gmp::enum_contains<color>(char32_t{1}));
static_assert(gmp::enum_contains<color>(true));
static_assert(gmp::enum_contains<character_edge>(0));

int main() {
    if (!gmp::enum_contains(color::red)) {
        return 1;
    }
    if (gmp::enum_contains(static_cast<color>(3))) {
        return 1;
    }
}
