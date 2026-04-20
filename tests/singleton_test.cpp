#include <iostream>

#include <gmp/dp/singleton.hpp>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4625 4626 4627 5026 5027 4820)
#endif

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

#ifdef _MSC_VER
#pragma warning(pop)
#endif
