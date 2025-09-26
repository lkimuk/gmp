#include <iostream>

#include <gmp/gmp.hpp>

int main() {
    std::cout << GMP_MAX_MACRO_ARGS << "\n";
    std::cout << GMP_PREPROCESSOR_TYPE << "\n";
}