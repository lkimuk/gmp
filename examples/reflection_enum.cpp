#include <gmp/gmp.hpp>

enum class Color {
    Red,
    Green,
    Blue,
};

int main() {
    constexpr auto values = gmp::enum_values<Color>();

    static_assert(gmp::enum_count<Color>() == 3);
    static_assert(gmp::enum_name<Color::Red>() == "Red");
    static_assert(values[0] == Color::Red);
    static_assert(values[1] == Color::Green);
    static_assert(values[2] == Color::Blue);

    return 0;
}
