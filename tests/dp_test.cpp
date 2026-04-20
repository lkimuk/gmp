#include <iostream>
#include <memory>
#include <string>
#include <gmp/gmp.hpp>

struct logger : gmp::singleton<logger> {
    void write(const std::string& message) const {
        std::cout << message << "\n";
    }

    GMP_DISABLE_CONSTRUCTION(logger)
};

struct shape {
    virtual ~shape() = default;
    virtual const char* name() const = 0;
};

struct circle : shape {
    const char* name() const override { return "circle"; }
};

struct square : shape {
    const char* name() const override { return "square"; }
};

GMP_FACTORY_REGISTER(shape, (), circle, square)
using shape_factory = gmp::object_factory<shape>;

int main() {
    logger::instance().write("hello from singleton");

    auto product = shape_factory::instance().create_unique("circle");
    std::cout << product->name() << "\n";
}
