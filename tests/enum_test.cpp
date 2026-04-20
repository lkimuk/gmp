#include <cassert>
#include <cstddef>
#include <iostream>
#include <optional>
#include <string_view>
#include <type_traits>

#include <gmp/gmp.hpp>

// =========================
// test enums
// =========================

enum class color {
    red,
    green,
    blue
};

enum class number {
    one = 1,
    two = 2,
    four = 4
};

GMP_ENUM_RANGE(number, 1, 4);

enum class token {
    ident  = 1,
    number = 100,
    string = 2000
};

GMP_ENUM_VALUES(token, token::ident, token::number, token::string);

enum class empty_enum {};

// GMP_ENUM_RANGE(empty_enum, 0, -1);
// GMP_ENUM_VALUES(empty_enum);

// =========================
// helpers
// =========================

template<typename T, std::size_t N>
void print_array(const std::array<T, N>& arr, std::string_view title) {
    std::cout << title << " [size=" << arr.size() << "]: ";
    for (std::size_t i = 0; i < arr.size(); ++i) {
        if constexpr (std::is_same_v<T, std::string_view>) {
            std::cout << arr[i];
        } else {
            std::cout << static_cast<int>(arr[i]);
        }
        if (i + 1 != arr.size()) {
            std::cout << ", ";
        }
    }
    std::cout << '\n';
}

// =========================
// tests
// =========================

void test_enum_count() {
    static_assert(gmp::enum_count<color>() == 3);
    static_assert(gmp::enum_count<number>() == 3);
    static_assert(gmp::enum_count<token>() == 3);
    static_assert(gmp::enum_count<empty_enum>() == 0);

    std::cout << "[ok] enum_count\n";
}

void test_enum_name() {
    static_assert(gmp::enum_name<color::red>() == "red");
    static_assert(gmp::enum_name<color::green>() == "green");
    static_assert(gmp::enum_name<color::blue>() == "blue");

    static_assert(gmp::enum_name<number::one>() == "one");
    static_assert(gmp::enum_name<number::four>() == "four");

    static_assert(gmp::enum_name<token::ident>() == "ident");
    static_assert(gmp::enum_name<token::number>() == "number");
    static_assert(gmp::enum_name<token::string>() == "string");

    std::cout << "[ok] enum_name\n";
}

void test_enum_values() {
    constexpr auto color_values = gmp::enum_values<color>();
    static_assert(color_values.size() == 3);
    static_assert(color_values[0] == color::red);
    static_assert(color_values[1] == color::green);
    static_assert(color_values[2] == color::blue);

    constexpr auto number_values = gmp::enum_values<number>();
    static_assert(number_values.size() == 3);
    static_assert(number_values[0] == number::one);
    static_assert(number_values[1] == number::two);
    static_assert(number_values[2] == number::four);

    constexpr auto token_values = gmp::enum_values<token>();
    static_assert(token_values.size() == 3);
    static_assert(token_values[0] == token::ident);
    static_assert(token_values[1] == token::number);
    static_assert(token_values[2] == token::string);

    constexpr auto empty_values = gmp::enum_values<empty_enum>();
    static_assert(empty_values.empty());

    std::cout << "[ok] enum_values\n";
}

void test_enum_names() {
    constexpr auto color_names = gmp::enum_names<color>();
    static_assert(color_names.size() == 3);
    static_assert(color_names[0] == "red");
    static_assert(color_names[1] == "green");
    static_assert(color_names[2] == "blue");

    constexpr auto number_names = gmp::enum_names<number>();
    static_assert(number_names.size() == 3);
    static_assert(number_names[0] == "one");
    static_assert(number_names[1] == "two");
    static_assert(number_names[2] == "four");

    constexpr auto token_names = gmp::enum_names<token>();
    static_assert(token_names.size() == 3);
    static_assert(token_names[0] == "ident");
    static_assert(token_names[1] == "number");
    static_assert(token_names[2] == "string");

    constexpr auto empty_names = gmp::enum_names<empty_enum>();
    static_assert(empty_names.empty());

    std::cout << "[ok] enum_names\n";
}

void test_enum_entries() {
    constexpr auto color_entries = gmp::enum_entries<color>();
    static_assert(color_entries.size() == 3);
    static_assert(color_entries[0].first == color::red);
    static_assert(color_entries[0].second == "red");
    static_assert(color_entries[1].first == color::green);
    static_assert(color_entries[1].second == "green");
    static_assert(color_entries[2].first == color::blue);
    static_assert(color_entries[2].second == "blue");

    constexpr auto token_entries = gmp::enum_entries<token>();
    static_assert(token_entries.size() == 3);
    static_assert(token_entries[0].first == token::ident);
    static_assert(token_entries[0].second == "ident");
    static_assert(token_entries[1].first == token::number);
    static_assert(token_entries[1].second == "number");
    static_assert(token_entries[2].first == token::string);
    static_assert(token_entries[2].second == "string");

    std::cout << "[ok] enum_entries\n";
}

void test_enum_index() {
    {
        auto idx = gmp::enum_index(color::red);
        assert(idx.has_value());
        assert(*idx == 0);
    }

    {
        auto idx = gmp::enum_index(color::green);
        assert(idx.has_value());
        assert(*idx == 1);
    }

    {
        auto idx = gmp::enum_index(color::blue);
        assert(idx.has_value());
        assert(*idx == 2);
    }

    {
        auto idx = gmp::enum_index(number::one);
        assert(idx.has_value());
        assert(*idx == 0);
    }

    {
        auto idx = gmp::enum_index(number::four);
        assert(idx.has_value());
        assert(*idx == 2);
    }

    {
        auto idx = gmp::enum_index(token::string);
        assert(idx.has_value());
        assert(*idx == 2);
    }

    std::cout << "[ok] enum_index\n";
}

void test_enum_cast() {
    {
        auto v = gmp::enum_cast<color>("red");
        assert(v.has_value());
        assert(*v == color::red);
    }

    {
        auto v = gmp::enum_cast<color>("green");
        assert(v.has_value());
        assert(*v == color::green);
    }

    {
        auto v = gmp::enum_cast<number>("four");
        assert(v.has_value());
        assert(*v == number::four);
    }

    {
        auto v = gmp::enum_cast<token>("ident");
        assert(v.has_value());
        assert(*v == token::ident);
    }

    {
        auto v = gmp::enum_cast<token>("not_exist");
        assert(!v.has_value());
    }

    std::cout << "[ok] enum_cast\n";
}

void test_runtime_print() {
    constexpr auto color_values = gmp::enum_values<color>();
    constexpr auto color_names  = gmp::enum_names<color>();
    constexpr auto color_entries = gmp::enum_entries<color>();

    print_array(color_values, "color values");
    print_array(color_names,  "color names");

    std::cout << "color entries [size=" << color_entries.size() << "]: ";
    for (std::size_t i = 0; i < color_entries.size(); ++i) {
        std::cout << '{'
                  << static_cast<int>(color_entries[i].first)
                  << ", "
                  << color_entries[i].second
                  << '}';
        if (i + 1 != color_entries.size()) {
            std::cout << ", ";
        }
    }
    std::cout << '\n';
}

int main() {
    test_enum_count();
    test_enum_name();
    test_enum_values();
    test_enum_names();
    test_enum_entries();
    test_enum_index();
    test_enum_cast();
    test_runtime_print();

    std::cout << "\nall enum tests passed\n";
    return 0;
}
