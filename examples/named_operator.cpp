#include <gmp/gmp.hpp>

int main() {
    auto plus = gmp::make_named_operator([](int lhs, int rhs) {
        return lhs + rhs;
    });

    auto add_assign = gmp::make_named_operator([](int& lhs, int rhs) -> int& {
        lhs += rhs;
        return lhs;
    });

    int value = 10;
    const int result = value ^plus^ 5;
    value ^add_assign^ 7;

    return (result == 15 && value == 17) ? 0 : 1;
}
