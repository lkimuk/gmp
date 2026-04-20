#include <cassert>
#include <memory>
#include <string>
#include <type_traits>

#include <gmp/gmp.hpp>

int main() {
    int a = 10;
    int b = 3;

    auto _ = gmp::make_named_operator([](int x, int y) {
        return x + y;
    });

    auto o = gmp::make_named_operator([](int x, int y) {
        return x * y;
    });

    assert((a ^_^ b) == 13);
    assert((a <_> b) == 13);
    assert((a +_+ b) == 13);
    assert((a *_* b) == 13);
    assert((a -_- b) == 13);
    assert((a /_/ b) == 13);
    assert((a %_% b) == 13);
    assert((a &_& b) == 13);
    assert((a |_| b) == 13);
    assert((a *_^ b) == 13);
    assert((a ^o^ b) == 30);

    auto add_assign = gmp::make_named_operator([](int& x, int y) -> int& {
        x += y;
        return x;
    });
    int x = 1;
    int& add_assign_result = x ^add_assign^ 2;
    assert(&add_assign_result == &x);
    assert(x == 3);

    auto check_lvalue = gmp::make_named_operator([](auto&& lhs, int) {
        static_assert(std::is_lvalue_reference_v<decltype(lhs)>);
        return lhs;
    });
    assert((a ^check_lvalue^ 0) == 10);

    auto size_plus = gmp::make_named_operator([](std::string s, int n) {
        return static_cast<int>(s.size()) + n;
    });
    assert((std::string("abc") ^size_plus^ 2) == 5);

    auto consume = gmp::make_named_operator([](std::unique_ptr<int> p, int n) {
        return *p + n;
    });
    auto r13 = (std::make_unique<int>(40) ^consume^ 2);
    assert(r13 == 42);

    auto rhs_category = gmp::make_named_operator([](int, auto&& rhs) {
        return std::is_rvalue_reference_v<decltype(rhs)>;
    });
    int rhs = 7;
    assert(!(a ^rhs_category^ rhs));
    assert((a ^rhs_category^ 7));
}
