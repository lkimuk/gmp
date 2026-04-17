#include <iostream>

#include <gmp/gmp.hpp>

struct impl : gmp::singleton<impl> {
    int v = 3;
};

int main() {
    impl var;

    std::cout << var.v << '\n';
}