#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include <gmp/gmp.hpp>

namespace {

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

} // namespace

int main() {
    auto& factory = gmp::object_factory<shape>::instance();

    if (!factory.contains("circle") || !factory.contains("square")) {
        return 1;
    }
    if (factory.contains("missing")) {
        return 1;
    }

    const auto keys = factory.registered_keys();
    if (std::find(keys.begin(), keys.end(), "circle") == keys.end()) {
        return 1;
    }
    if (std::find(keys.begin(), keys.end(), "square") == keys.end()) {
        return 1;
    }

    const auto circle_product = factory.try_create_unique("circle");
    if (!circle_product || std::string(circle_product->name()) != "circle") {
        return 1;
    }
    if (factory.try_create_unique("missing")) {
        return 1;
    }

    const auto square_product = factory.try_create_shared("square");
    if (!square_product || std::string(square_product->name()) != "square") {
        return 1;
    }
    if (factory.try_create_shared("missing")) {
        return 1;
    }
}
