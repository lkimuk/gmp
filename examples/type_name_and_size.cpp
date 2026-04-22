#include <gmp/gmp.hpp>

struct Packet {
    char tag;
    int value;
};

int main() {
    constexpr auto int_name = gmp::type_name<int>();

    static_assert(int_name == gmp::fixed_string("int"));
    static_assert(gmp::type_size<Packet>() == sizeof(char) + sizeof(int));
    static_assert(gmp::type_size<Packet>() <= sizeof(Packet));

    return 0;
}
