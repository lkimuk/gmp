#include <iostream>

#include <gmp/dp/singleton.hpp>

struct S : gmp::singleton<S> {
    int value = 42;

    GMP_DISABLE_CONSTRUCTION(S)
};

int main() {
    // S* s = new S; // error
    // std::cout << s->val << "\n"; // error

    // okay
    std::cout << S::instance().value << "\n";
}
