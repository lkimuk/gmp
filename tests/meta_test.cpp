//   ___ __  __ ___ 
//  / __|  \/  | _ \ GMP(Generative Metaprogramming)
// | (_ | |\/| |  _/ version 0.1.0
//  \___|_|  |_|_|   https://github.com/lkimuk/gmp
//
// SPDX-FileCopyrightText: 2023-2026 Gaoxing Li <https://www.cppmore.com/>
// SPDX-License-Identifier: MIT
//
// Compile-time tests for GMP library using static_assert
// If this file compiles, all tests pass!

#include <utility>
#include <iostream>
#include <string>
#include <vector>

#include <gmp/gmp.hpp>

struct S {
    double b;
    // std::string c;
};

enum class Color : int { red, green, blue };

int main() {
    std::cout << "All compile-time tests passed successfully!" << std::endl;
    
    constexpr auto type = gmp::type_name<int>();
    // auto sv = gmp::type_name<int>();
    std::cout << "int: " << gmp::type_name<int>() << "\n";
    std::cout << "int: " << gmp::type_name<int>().to_string_view() << "\n";
    std::cout << "int: " << gmp::type_name<std::vector<std::string>>() << "\n";

    std::cout << gmp::member_count<S>() << "\n";
    std::cout << gmp::member_name<0, S>() << "\n";
    // std::cout << gmp::member_name<1, S>() << "\n";

    std::cout << "------------------------\n";

    std::cout << gmp::type_name<Color>() << "\n";
    // std::cout << gmp::type_name<decltype(gmp::detail::field_getter<0, S>(gmp::constant_arg<2>))>() << "\n";
    std::cout << gmp::detail::value_name_of<Color(3)>() << "\n";
    std::cout << gmp::enum_count<Color>() << "\n";
    std::cout << gmp::enum_name<Color(3)>() << "\n";

    for (const auto& e : gmp::enum_names<Color>()) {
        std::cout << e << ", ";
    }
}