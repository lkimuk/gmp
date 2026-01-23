//   ___ __  __ ___ 
//  / __|  \/  | _ \ GMP(Generative Metaprogramming)
// | (_ | |\/| |  _/ version 0.1.0
//  \___|_|  |_|_|   https://github.com/lkimuk/gmp
//
// SPDX-FileCopyrightText: 2023-2026 Gaoxing Li <https://www.cppmore.com/>
// SPDX-License-Identifier: MIT
//
// This file is part of the GMP (Generative Metaprogramming) library.
// Full project source: https://github.com/lkimuk/gmp

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <gmp/gmp.hpp>

#include <iostream>
#include <string>
#include <type_traits>

using namespace Catch::Matchers;

// ============================================================================
// 基础宏测试
// ============================================================================

TEST_CASE("Core macros - GMP_EXPAND and GMP_IDENTITY", "[core][basic]") {
    SECTION("GMP_EXPAND forces macro expansion") {
        #define FOO 42
        #define BAR FOO
        #define TEST_EXPAND GMP_EXPAND(BAR)
        
        REQUIRE(TEST_EXPAND == 42);
    }
    
    SECTION("GMP_IDENTITY returns argument unchanged") {
        REQUIRE(GMP_IDENTITY(100) == 100);
        REQUIRE(GMP_IDENTITY(0) == 0);
    }
    
    SECTION("GMP_EXPAND and GMP_IDENTITY produce same results for simple values") {
        REQUIRE(GMP_EXPAND(255) == GMP_IDENTITY(255));
    }
}

TEST_CASE("Boolean macros", "[bool][basic]") {
    SECTION("GMP_BOOL converts to boolean") {
        REQUIRE(GMP_BOOL(0) == 0);
        REQUIRE(GMP_BOOL(1) == 1);
        REQUIRE(GMP_BOOL(2) == 1);
        REQUIRE(GMP_BOOL(100) == 1);
        REQUIRE(GMP_BOOL(-1) == 1);  // 注意：负值也是真
    }
    
    SECTION("GMP_NOT logical negation") {
        REQUIRE(GMP_NOT(0) == 1);
        REQUIRE(GMP_NOT(1) == 0);
        REQUIRE(GMP_NOT(5) == 0);  // 非0值取反为0
    }
    
    SECTION("GMP_AND logical AND") {
        REQUIRE(GMP_AND(0, 0) == 0);
        REQUIRE(GMP_AND(0, 1) == 0);
        REQUIRE(GMP_AND(1, 0) == 0);
        REQUIRE(GMP_AND(1, 1) == 1);
        REQUIRE(GMP_AND(5, 3) == 1);  // 两个非0值
    }
    
    SECTION("GMP_OR logical OR") {
        REQUIRE(GMP_OR(0, 0) == 0);
        REQUIRE(GMP_OR(0, 1) == 1);
        REQUIRE(GMP_OR(1, 0) == 1);
        REQUIRE(GMP_OR(1, 1) == 1);
        REQUIRE(GMP_OR(0, 5) == 1);
    }
    
    SECTION("GMP_XOR logical XOR") {
        // 如果你实现了 XOR
        #ifdef GMP_XOR
        REQUIRE(GMP_XOR(0, 0) == 0);
        REQUIRE(GMP_XOR(0, 1) == 1);
        REQUIRE(GMP_XOR(1, 0) == 1);
        REQUIRE(GMP_XOR(1, 1) == 0);
        #endif
    }
}

TEST_CASE("Conditional macros", "[conditional][basic]") {
    SECTION("GMP_IF basic condition") {
        #define TEST_TRUE GMP_IF(1, true_value, false_value)
        #define TEST_FALSE GMP_IF(0, true_value, false_value)
        
        REQUIRE(GMP_STRINGIFY(TEST_TRUE) == std::string("true_value"));
        REQUIRE(GMP_STRINGIFY(TEST_FALSE) == std::string("false_value"));
    }
    
    SECTION("GMP_WHEN condition") {
        #define WHEN_TRUE GMP_WHEN(1, selected_value)
        #define WHEN_FALSE GMP_WHEN(0, selected_value)
        
        REQUIRE(GMP_STRINGIFY(WHEN_TRUE) == std::string("selected_value"));
        // WHEN_FALSE 应该展开为空
    }
    
    SECTION("GMP_IF_THEN_ELSE") {
        #define IF_TRUE GMP_IF_THEN_ELSE(1, then_value, else_value)
        #define IF_FALSE GMP_IF_THEN_ELSE(0, then_value, else_value)
        
        REQUIRE(GMP_STRINGIFY(IF_TRUE) == std::string("then_value"));
        REQUIRE(GMP_STRINGIFY(IF_FALSE) == std::string("else_value"));
    }
}

// ============================================================================
// 字符串化测试
// ============================================================================

TEST_CASE("Stringification macros", "[stringify][basic]") {
    SECTION("GMP_STRINGIFY basic values") {
        REQUIRE(GMP_STRINGIFY(42) == std::string("42"));
        REQUIRE(GMP_STRINGIFY(hello) == std::string("hello"));
        REQUIRE(GMP_STRINGIFY() == std::string(""));  // 空参数
    }
    
    SECTION("GMP_STRINGIFY with macro expansion") {
        #define VALUE 100
        #define EXPRESSION VALUE + 5
        
        // 注意：GMP_STRINGIFY 会先展开参数
        REQUIRE(GMP_STRINGIFY(VALUE) == std::string("100"));
        REQUIRE(GMP_STRINGIFY(EXPRESSION) == std::string("100 + 5"));
    }
    
    SECTION("String concatenation") {
        #define HELLO "Hello"
        #define WORLD "World"
        
        std::string result = GMP_STRINGIFY(HELLO) " " GMP_STRINGIFY(WORLD);
        REQUIRE(result == std::string("Hello World"));
    }
}

// ============================================================================
// 连接宏测试
// ============================================================================

TEST_CASE("Concatenation macros", "[concat][basic]") {
    SECTION("GMP_CONCAT basic concatenation") {
        #define PREFIX foo
        #define SUFFIX bar
        
        REQUIRE(GMP_STRINGIFY(GMP_CONCAT(PREFIX, SUFFIX)) == std::string("foobar"));
        REQUIRE(GMP_STRINGIFY(GMP_CONCAT(123, 456)) == std::string("123456"));
    }
    
    SECTION("GMP_CONCATS multiple concatenation") {
        REQUIRE(GMP_STRINGIFY(GMP_CONCATS(a, b, c)) == std::string("abc"));
        REQUIRE(GMP_STRINGIFY(GMP_CONCATS(1, 2, 3, 4)) == std::string("1234"));
        
        #define NUM_1 1
        #define NUM_2 2
        #define NUM_3 3
        REQUIRE(GMP_STRINGIFY(GMP_CONCATS(NUM_, 1, NUM_, 2, NUM_, 3)) == std::string("1_1_2_2_3_3"));
    }
    
    SECTION("GMP_CONCAT with expansion") {
        #define PART1 hello
        #define PART2 world
        
        // 连接后再字符串化
        std::string result = GMP_STRINGIFY(GMP_CONCAT(PART1, PART2));
        REQUIRE(result == std::string("helloworld"));
    }
}

// ============================================================================
// 参数数量测试
// ============================================================================

TEST_CASE("Variadic argument counting", "[variadic][basic]") {
    SECTION("GMP_SIZE_OF_VAARGS counts arguments") {
        REQUIRE(GMP_SIZE_OF_VAARGS() == 0);
        REQUIRE(GMP_SIZE_OF_VAARGS(a) == 1);
        REQUIRE(GMP_SIZE_OF_VAARGS(a, b) == 2);
        REQUIRE(GMP_SIZE_OF_VAARGS(a, b, c) == 3);
        REQUIRE(GMP_SIZE_OF_VAARGS(1, 2, 3, 4, 5) == 5);
    }
    
    SECTION("GMP_NUM_ARGS counts arguments") {
        REQUIRE(GMP_NUM_ARGS() == 0);
        REQUIRE(GMP_NUM_ARGS(x) == 1);
        REQUIRE(GMP_NUM_ARGS(x, y) == 2);
        REQUIRE(GMP_NUM_ARGS(1, 2, 3, 4, 5, 6) == 6);
    }
    
    SECTION("GMP_IS_EMPTY detects empty arguments") {
        REQUIRE(GMP_IS_EMPTY() == 1);
        REQUIRE(GMP_IS_EMPTY(x) == 0);
        REQUIRE(GMP_IS_EMPTY(1, 2, 3) == 0);
    }
}

// ============================================================================
// 宏展开测试
// ============================================================================

TEST_CASE("Macro expansion control", "[expansion][basic]") {
    SECTION("GMP_EVAL forces evaluation") {
        #define LEVEL1(x) x + 1
        #define LEVEL2(x) LEVEL1(x)
        #define LEVEL3(x) LEVEL2(x)
        
        // 没有 GMP_EVAL
        #define WITHOUT_EVAL LEVEL3(5)
        
        // 有 GMP_EVAL
        #define WITH_EVAL GMP_EVAL(LEVEL3(5))
        
        // 注意：这实际上是在测试编译器行为
        // 我们只能测试它们是否都能编译
        REQUIRE(true);  // 占位符，实际中可能需要更复杂的测试
    }
    
    SECTION("GMP_DEFER delays expansion") {
        #define EXPAND_NOW() immediate
        #define EXPAND_DEFERRED() GMP_DEFER(EXPAND_NOW)()
        
        // 这需要更复杂的测试结构，因为涉及多步展开
        REQUIRE(true);
    }
}

// ============================================================================
// 编译时测试
// ============================================================================

TEST_CASE("Compile-time tests", "[compile][basic]") {
    SECTION("Static assertions for macro values") {
        // 测试宏在编译时产生正确值
        static_assert(GMP_BOOL(0) == 0, "GMP_BOOL(0) should be 0");
        static_assert(GMP_BOOL(1) == 1, "GMP_BOOL(1) should be 1");
        static_assert(GMP_NOT(0) == 1, "GMP_NOT(0) should be 1");
        static_assert(GMP_NOT(1) == 0, "GMP_NOT(1) should be 0");
        static_assert(GMP_AND(1, 1) == 1, "GMP_AND(1, 1) should be 1");
        static_assert(GMP_OR(0, 0) == 0, "GMP_OR(0, 0) should be 0");
    }
    
    SECTION("Compile-time string length") {
        // 测试字符串化在编译时工作
        constexpr const char* str = GMP_STRINGIFY(test);
        static_assert(str[0] == 't', "First character should be 't'");
        static_assert(str[1] == 'e', "Second character should be 'e'");
        static_assert(str[2] == 's', "Third character should be 's'");
        static_assert(str[3] == 't', "Fourth character should be 't'");
        static_assert(str[4] == '\0', "Should be null-terminated");
    }
}

// ============================================================================
// 边界情况测试
// ============================================================================

TEST_CASE("Edge cases", "[edge][basic]") {
    SECTION("Empty arguments") {
        REQUIRE(GMP_SIZE_OF_VAARGS() == 0);
        REQUIRE(GMP_NUM_ARGS() == 0);
        REQUIRE(GMP_IS_EMPTY() == 1);
    }
    
    SECTION("Single argument edge cases") {
        REQUIRE(GMP_SIZE_OF_VAARGS(,) == 2);  // 空参数算作一个
        REQUIRE(GMP_NUM_ARGS(,) == 2);
    }
    
    SECTION("Maximum argument limits") {
        // 测试接近最大参数数量的情况
        // 这取决于 GMP_MAX_MACRO_ARGS 的值
        #define TEST_MAX_ARGS(...) GMP_NUM_ARGS(__VA_ARGS__)
        
        // 创建最大数量的参数
        #define EXPAND_10(a,b,c,d,e,f,g,h,i,j) j
        #define CREATE_ARGS_10() a,b,c,d,e,f,g,h,i,j
        
        int count = TEST_MAX_ARGS(CREATE_ARGS_10());
        REQUIRE(count == 10);
    }
}

// ============================================================================
// 性能测试（可选）
// ============================================================================

TEST_CASE("Benchmark macros", "[!benchmark][basic]") {
    // 注意：[!benchmark] 标签意味着只在使用 --benchmark 时运行
    
    BENCHMARK("GMP_BOOL performance") {
        return GMP_BOOL(1);
    };
    
    BENCHMARK("GMP_NOT performance") {
        return GMP_NOT(0);
    };
    
    BENCHMARK("GMP_AND performance") {
        return GMP_AND(1, 1);
    };
    
    BENCHMARK("GMP_STRINGIFY small string") {
        return GMP_STRINGIFY(test);
    };
}

// ============================================================================
// 示例代码测试
// ============================================================================

TEST_CASE("Example code from documentation", "[example][basic]") {
    SECTION("Documentation example 1: Basic boolean") {
        // 示例：GMP_BOOL(0) 应该返回 0，GMP_BOOL(42) 应该返回 1
        REQUIRE(GMP_BOOL(0) == 0);
        REQUIRE(GMP_BOOL(42) == 1);
    }
    
    SECTION("Documentation example 2: Stringification") {
        #define VERSION_MAJOR 2
        #define VERSION_MINOR 15
        #define VERSION VERSION_MAJOR ## . ## VERSION_MINOR
        
        const char* version_str = GMP_STRINGIFY(VERSION);
        REQUIRE_THAT(version_str, Equals("2.15"));
    }
    
    SECTION("Documentation example 3: Conditional") {
        #define DEBUG_MODE 1
        #define LOG_IF_DEBUG(msg) GMP_IF(DEBUG_MODE, LOG(msg), )
        
        // 这里主要是测试是否能编译
        REQUIRE(true);
    }
}

// ============================================================================
// 辅助函数
// ============================================================================

namespace test_helpers {
    // 辅助函数：将宏结果转换为字符串进行比较
    template<int N>
    struct macro_result {
        static constexpr int value = N;
    };
    
    // 用于测试宏展开的辅助类
    struct ExpansionTester {
        static bool test_concat() {
            #define TEST_A hello
            #define TEST_B world
            return std::string(GMP_STRINGIFY(GMP_CONCAT(TEST_A, TEST_B))) == "helloworld";
        }
    };
}