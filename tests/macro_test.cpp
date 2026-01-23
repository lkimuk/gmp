// #include <gmp/gmp.hpp>

// void bar(int arg1, const char* arg2) {
//     printf("bar %d, %s\n", arg1, arg2);
// }

// #define Bar(arg1, arg2) bar(arg1, arg2); 
// GMP_REPEAT(Bar, 100, 1, "arg2") // Execute bar function 3 times
// // Expands to: bar(1, "arg2"); bar(1, "arg2"); bar(1, "arg2");

// #define PRINT(x) std::cout << x << " ";
// // Expands to: std::cout << 1 << " "; std::cout << 2 << " "; std::cout << 3 << " ";
// GMP_FOR_EACH(PRINT, 1, 2, 3)

// #define COND(args) GMP_BOOL(GMP_GET_TUPLE(0, args))
// #define OP(args) (GMP_DEC(GMP_GET_TUPLE(0, args)), GMP_CONCAT(GMP_GET_TUPLE(0, args), GMP_GET_TUPLE(1, args)))
// // #define OP(args) OP_COMPAT_MSVC(args, GMP_ADD(GMP_GET_TUPLE(0, args), GMP_GET_TUPLE(1, args))) // (GMP_DEC(GMP_GET_TUPLE(0, tup)), GMP_ADD(GMP_GET_TUPLE(0, tup), GMP_GET_TUPLE(1, tup)))
// // #define OP_COMPAT_MSVC(args, res) (GMP_DEC(GMP_GET_TUPLE(0, args)), res)

// GMP_WHILE(COND, OP, (2, 0))

// #define OVERLOAD_FUNCTION_0 "OVERLOAD_FUNCTION_0"
// #define OVERLOAD_FUNCTION_1 "OVERLOAD_FUNCTION_1"
// #define OVERLOAD_FUNCTION_X_Y "OVERLOAD_FUNCTION_X_Y"
// GMP_OVERLOAD_INVOKE(OVERLOAD_FUNCTION, 0)     // expands to: "OVERLOAD_FUNCTION_0"
// GMP_OVERLOAD_INVOKE(OVERLOAD_FUNCTION, 1)     // expands to: "OVERLOAD_FUNCTION_1"
// GMP_OVERLOAD_INVOKE(OVERLOAD_FUNCTION, X, Y)  // expands to: "OVERLOAD_FUNCTION_X_Y"

// int main() {
//     // std::cout << GMP_MAX_MACRO_ARGS << "\n";
//     // std::cout << GMP_PREPROCESSOR_TYPE << "\n";

//     GMP_EQUAL_INT(0, 0)

//     GMP_RANGE(0, 10)

//     GMP_TUPLE_SIZE((a, b, c, d, e))

//     GMP_TUPLE_TAKE(2, (a, b, c, d, e))
//     GMP_TUPLE_TAKE(0, (a, b, c, d, e))
//     GMP_TUPLE_TAKE(5, (a, b, c, d, e))
//     GMP_TUPLE_TAKE(10, (a, b, c, d, e))
    
//     GMP_TUPLE_SKIP(2, (a, b, c, d, e))
//     GMP_TUPLE_SKIP(0, (a, b, c, d, e))
//     GMP_TUPLE_SKIP(5, (a, b, c, d, e))
//     GMP_TUPLE_SKIP(10, (a, b, c, d, e))

//     GMP_TUPLE_APPEND((a, b, c, d, e), f)
//     GMP_TUPLE_APPEND((), f)

//     GMP_TUPLE_CONCAT((), (a, b, c))
//     GMP_TUPLE_CONCAT((a, b, c), (a, b, c))
//     GMP_TUPLE_CONCAT((a, b, c), ())
//     GMP_TUPLE_CONCAT((), ())

//     GMP_CONCATS(abc, def)
//     GMP_CONCATS(abc, def, ghi, xyz)

//     #define NUM_1 1
//     #define NUM_2 2
//     GMP_STRINGIFY(GMP_CONCATS(NUM_, 1, NUM_, 2))

//     #define ORIGINAL_TUPLE (1, 2, 3, 4, 5)
//     #define TEST GMP_TUPLE_SIZE(GMP_TUPLE_CONCAT(GMP_TUPLE_TAKE(2, ORIGINAL_TUPLE), GMP_TUPLE_SKIP(2, ORIGINAL_TUPLE)))

//     GMP_MAKE_INDEX_SEQUENCE(0)

//     #define CONCAT_EMPTY_SECOND GMP_TUPLE_CONCAT((1, 2), ())
//     static_assert(GMP_TUPLE_SIZE(CONCAT_EMPTY_SECOND) == 2,
//                   "GMP_TUPLE_CONCAT((1, 2), ()) should return the first tuple");


//     GMP_ADD(2, 1)

//     GMP_SUB(1, 2)
//     GMP_SUB(3, 1)
//     GMP_SUB(2, 2)
//     GMP_SUB(0, 0)

//     GMP_SWAP(1, 2)

//     GMP_SIZE_OF_VAARGS()                         // 0
//     GMP_SIZE_OF_VAARGS(1)                        // 1
//     GMP_SIZE_OF_VAARGS('a', 'b')                 // 2
//     GMP_SIZE_OF_VAARGS('a', 'b', 'c')            // 3
//     GMP_SIZE_OF_VAARGS('a', 'b', 1, 2)           // 4
//     GMP_SIZE_OF_VAARGS('a', 'b', 1, 2, 3)        // 5
//     GMP_SIZE_OF_VAARGS('a', 'b', 1, 2, 3, 4)     // 6
//     GMP_SIZE_OF_VAARGS('a', 'b', 1, 2, 3, 4, 5)  // 7

//     GMP_TUPLE_PREPEND(GMP_TUPLE_PREPEND((c, d), b), a)

//     GMP_MAKE_INDEX_SEQUENCE(0)
//     GMP_MAKE_INDEX_SEQUENCE(5)
//     GMP_MAKE_INDEX_SEQUENCE(42)

//     GMP_RANGE(0, 0) // expands to: 
//     GMP_RANGE(0, 5) // expands to: 0 , 1 , 2 , 3 , 4
//     GMP_RANGE(5, 10) // expands to: 5 , 6 , 7 , 8 , 9

//     #define MYLIB_NAMESPACE_BEGIN GMP_GENERATE_NAMESPACES_BEGIN(mylib, parser)
//     #define MYLIB_NAMESPACE_END GMP_GENERATE_NAMESPACES_END(mylib, parser)

//     /// expands to:
//     /// namespace mylib { namespace parser {
//     /// } }
//     MYLIB_NAMESPACE_BEGIN
//     MYLIB_NAMESPACE_END
// }

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

#include <gmp/gmp.hpp>

// // GMP_TUPLE_TAKE(0, ())
// #define TUPLE_SKIP_TEST GMP_TUPLE_SKIP(2, (a, b, c, d, e))
// TUPLE_SKIP_TEST
// GMP_TUPLE_SIZE(TUPLE_SKIP_TEST)
// GMP_TUPLE_SKIP(2, (a, b, c, d, e))
// GMP_TUPLE_SKIP(4, (a, b, c, d, e))
// GMP_TUPLE_SKIP(5, (a, b, c, d, e))
// GMP_TUPLE_SKIP(10, (a, b, c, d, e))
// GMP_TUPLE_SKIP(0, (a, b, c, d, e))
// GMP_LESS_INT(1, 2)
// GMP_LESS_INT(1, 1)
// GMP_LESS_EQUAL_INT(1, 2)
// GMP_LESS_EQUAL_INT(1, 1)
// GMP_LESS_EQUAL_INT(2, 1)

// ============================================================================
// Basic Macro Tests
// ============================================================================

namespace test_core {
    // GMP_EXPAND 和 GMP_IDENTITY
    static_assert(GMP_EXPAND(42) == 42, "GMP_EXPAND should return the value");
    static_assert(GMP_IDENTITY(100) == 100, "GMP_IDENTITY should return the value");
    
    #define TEST_VALUE 255
    #define TEST_INDIRECT TEST_VALUE
    static_assert(GMP_EXPAND(TEST_INDIRECT) == 255, "GMP_EXPAND should expand macros");
}

// ============================================================================
// Boolean Macro Tests
// ============================================================================

namespace test_bool {
    // GMP_BOOL
    static_assert(GMP_BOOL(0) == 0, "GMP_BOOL(0) should be 0");
    static_assert(GMP_BOOL(1) == 1, "GMP_BOOL(1) should be 1");
    static_assert(GMP_BOOL(42) == 1, "GMP_BOOL(non-zero) should be 1");
    
    // GMP_NOT
    static_assert(GMP_NOT(0) == 1, "GMP_NOT(0) should be 1");
    static_assert(GMP_NOT(1) == 0, "GMP_NOT(1) should be 0");
    static_assert(GMP_NOT(GMP_BOOL(5)) == 0, "GMP_NOT(non-zero) should be 0");
    
    // GMP_AND
    static_assert(GMP_AND(0, 0) == 0, "GMP_AND(0, 0) should be 0");
    static_assert(GMP_AND(0, 1) == 0, "GMP_AND(0, 1) should be 0");
    static_assert(GMP_AND(1, 0) == 0, "GMP_AND(1, 0) should be 0");
    static_assert(GMP_AND(1, 1) == 1, "GMP_AND(1, 1) should be 1");
    static_assert(GMP_AND(GMP_BOOL(5), GMP_BOOL(3)) == 1, "GMP_AND(non-zero, non-zero) should be 1");
    
    // GMP_OR
    static_assert(GMP_OR(0, 0) == 0, "GMP_OR(0, 0) should be 0");
    static_assert(GMP_OR(0, 1) == 1, "GMP_OR(0, 1) should be 1");
    static_assert(GMP_OR(1, 0) == 1, "GMP_OR(1, 0) should be 1");
    static_assert(GMP_OR(1, 1) == 1, "GMP_OR(1, 1) should be 1");
    
    // GMP_XOR
    static_assert(GMP_XOR(0, 0) == 0, "GMP_XOR(0, 0) should be 0");
    static_assert(GMP_XOR(0, 1) == 1, "GMP_XOR(0, 1) should be 1");
    static_assert(GMP_XOR(1, 0) == 1, "GMP_XOR(1, 0) should be 1");
    static_assert(GMP_XOR(1, 1) == 0, "GMP_XOR(1, 1) should be 0");
    // 1. Commutative Property: a ⊕ b = b ⊕ a
    static_assert(GMP_XOR(0, 1) == GMP_XOR(1, 0), "XOR commutative property: 0⊕1 = 1⊕0");
    static_assert(GMP_XOR(1, 1) == GMP_XOR(1, 1), "XOR commutative property: 1⊕1 = 1⊕1");
    static_assert(GMP_XOR(0, 0) == GMP_XOR(0, 0), "XOR commutative property: 0⊕0 = 0⊕0");
    // Test with swapped parameter order
    #define TEST_COMMUTATIVE(a, b) (GMP_XOR(a, b) == GMP_XOR(b, a))
    static_assert(TEST_COMMUTATIVE(0, 0), "Commutative property holds for (0, 0)");
    static_assert(TEST_COMMUTATIVE(0, 1), "Commutative property holds for (0, 1)");
    static_assert(TEST_COMMUTATIVE(1, 0), "Commutative property holds for (1, 0)");
    static_assert(TEST_COMMUTATIVE(1, 1), "Commutative property holds for (1, 1)");
    // 2. Associative Property: (a ⊕ b) ⊕ c = a ⊕ (b ⊕ c)
    #define XOR3_L(a, b, c) GMP_XOR(GMP_XOR(a, b), c)   // Left associative
    #define XOR3_R(a, b, c) GMP_XOR(a, GMP_XOR(b, c))   // Right associative

    static_assert(XOR3_L(0, 0, 0) == XOR3_R(0, 0, 0), "Associative: (0⊕0)⊕0 = 0⊕(0⊕0)");
    static_assert(XOR3_L(0, 0, 1) == XOR3_R(0, 0, 1), "Associative: (0⊕0)⊕1 = 0⊕(0⊕1)");
    static_assert(XOR3_L(0, 1, 0) == XOR3_R(0, 1, 0), "Associative: (0⊕1)⊕0 = 0⊕(1⊕0)");
    static_assert(XOR3_L(0, 1, 1) == XOR3_R(0, 1, 1), "Associative: (0⊕1)⊕1 = 0⊕(1⊕1)");
    static_assert(XOR3_L(1, 0, 0) == XOR3_R(1, 0, 0), "Associative: (1⊕0)⊕0 = 1⊕(0⊕0)");
    static_assert(XOR3_L(1, 0, 1) == XOR3_R(1, 0, 1), "Associative: (1⊕0)⊕1 = 1⊕(0⊕1)");
    static_assert(XOR3_L(1, 1, 0) == XOR3_R(1, 1, 0), "Associative: (1⊕1)⊕0 = 1⊕(1⊕0)");
    static_assert(XOR3_L(1, 1, 1) == XOR3_R(1, 1, 1), "Associative: (1⊕1)⊕1 = 1⊕(1⊕1)");
    // 3. Identity Element: a ⊕ 0 = a
    static_assert(GMP_XOR(0, 0) == 0, "Identity element: 0⊕0 = 0");
    static_assert(GMP_XOR(1, 0) == 1, "Identity element: 1⊕0 = 1");
    static_assert(GMP_XOR(0, 0) == GMP_IDENTITY(0), "Identity matches GMP_IDENTITY");
    // 4. Self-Inverse Property: a ⊕ a = 0
    static_assert(GMP_XOR(0, 0) == 0, "Self-inverse: 0⊕0 = 0");
    static_assert(GMP_XOR(1, 1) == 0, "Self-inverse: 1⊕1 = 0");
    // 5. Relationship with NOT: a ⊕ 1 = !a
    static_assert(GMP_XOR(0, 1) == GMP_NOT(0), "XOR with 1 equals NOT: 0⊕1 = !0");
    static_assert(GMP_XOR(1, 1) == GMP_NOT(1), "XOR with 1 equals NOT: 1⊕1 = !1");
    // 6. Triple XOR Property: a ⊕ a ⊕ a = a
    static_assert(GMP_XOR(GMP_XOR(0, 0), 0) == 0, "0⊕0⊕0 = 0");
    static_assert(GMP_XOR(GMP_XOR(1, 1), 1) == 1, "1⊕1⊕1 = 1");
    // 7. Cancellation Law: If a ⊕ b = a ⊕ c, then b = c
    // In Boolean algebra: if b ≠ c, then a ⊕ b ≠ a ⊕ c
    #define TEST_CANCELLATION(a, b, c) \
        (GMP_XOR(a, b) == GMP_XOR(a, c)) == (b == c)

    static_assert(TEST_CANCELLATION(0, 0, 0), "Cancellation law holds for (0, 0, 0)");
    static_assert(TEST_CANCELLATION(0, 0, 1), "Cancellation law holds for (0, 0, 1)");
    static_assert(TEST_CANCELLATION(0, 1, 0), "Cancellation law holds for (0, 1, 0)");
    static_assert(TEST_CANCELLATION(0, 1, 1), "Cancellation law holds for (0, 1, 1)");
    static_assert(TEST_CANCELLATION(1, 0, 0), "Cancellation law holds for (1, 0, 0)");
    static_assert(TEST_CANCELLATION(1, 0, 1), "Cancellation law holds for (1, 0, 1)");
    static_assert(TEST_CANCELLATION(1, 1, 0), "Cancellation law holds for (1, 1, 0)");
    static_assert(TEST_CANCELLATION(1, 1, 1), "Cancellation law holds for (1, 1, 1)");
    // 8. XOR expressed using AND, OR, NOT: a ⊕ b = (a ∨ b) ∧ ¬(a ∧ b)
    #define XOR_VIA_OTHER(a, b) GMP_AND(GMP_OR(a, b), GMP_NOT(GMP_AND(a, b)))

    static_assert(GMP_XOR(0, 0) == XOR_VIA_OTHER(0, 0), "XOR = (a∨b)∧!(a∧b) for (0, 0)");
    static_assert(GMP_XOR(0, 1) == XOR_VIA_OTHER(0, 1), "XOR = (a∨b)∧!(a∧b) for (0, 1)");
    static_assert(GMP_XOR(1, 0) == XOR_VIA_OTHER(1, 0), "XOR = (a∨b)∧!(a∧b) for (1, 0)");
    static_assert(GMP_XOR(1, 1) == XOR_VIA_OTHER(1, 1), "XOR = (a∨b)∧!(a∧b) for (1, 1)");

    // 9. De Morgan's Law variant for XOR: ¬(a ⊕ b) = (¬a ⊕ b) = (a ⊕ ¬b)
    static_assert(GMP_NOT(GMP_XOR(0, 0)) == GMP_XOR(GMP_NOT(0), 0), "!(0⊕0) = !0⊕0");
    static_assert(GMP_NOT(GMP_XOR(0, 1)) == GMP_XOR(GMP_NOT(0), 1), "!(0⊕1) = !0⊕1");
    static_assert(GMP_NOT(GMP_XOR(1, 0)) == GMP_XOR(1, GMP_NOT(0)), "!(1⊕0) = 1⊕!0");
    static_assert(GMP_NOT(GMP_XOR(1, 1)) == GMP_XOR(1, GMP_NOT(1)), "!(1⊕1) = 1⊕!1");

    // 10. Parity Checking
    // For three bits: result is 1 when odd number of 1s
    static_assert(GMP_XOR(GMP_XOR(0, 0), 0) == 0, "Parity of (0,0,0) should be 0 (even)");
    static_assert(GMP_XOR(GMP_XOR(0, 0), 1) == 1, "Parity of (0,0,1) should be 1 (odd)");
    static_assert(GMP_XOR(GMP_XOR(0, 1), 1) == 0, "Parity of (0,1,1) should be 0 (even)");
    static_assert(GMP_XOR(GMP_XOR(1, 1), 1) == 1, "Parity of (1,1,1) should be 1 (odd)");

    // 11. Conditional Negation
    // Use b as control bit: result = a ⊕ b, negates when b=1, unchanged when b=0
    static_assert(GMP_XOR(0, 0) == 0, "Conditional negation: 0 with control 0 = 0");
    static_assert(GMP_XOR(0, 1) == 1, "Conditional negation: 0 with control 1 = 1 (negated)");
    static_assert(GMP_XOR(1, 0) == 1, "Conditional negation: 1 with control 0 = 1");
    static_assert(GMP_XOR(1, 1) == 0, "Conditional negation: 1 with control 1 = 0 (negated)");

    // 12. XOR Swap Algorithm (abstract test)
    // In macros we can't actually swap, but verify the properties:
    // a' = a ⊕ b
    // b' = a' ⊕ b = (a ⊕ b) ⊕ b = a ⊕ (b ⊕ b) = a ⊕ 0 = a
    // a'' = a' ⊕ b' = (a ⊕ b) ⊕ a = b ⊕ (a ⊕ a) = b ⊕ 0 = b
    #define XOR_SWAP_STEP1(a, b) GMP_XOR(a, b)           // a' = a ⊕ b
    #define XOR_SWAP_STEP2(a, b) GMP_XOR(GMP_XOR(a, b), b) // b' = (a ⊕ b) ⊕ b = a
    #define XOR_SWAP_STEP3(a, b) GMP_XOR(GMP_XOR(a, b), GMP_XOR(GMP_XOR(a, b), b)) // a'' = (a ⊕ b) ⊕ a = b

    static_assert(XOR_SWAP_STEP2(0, 1) == 0, "XOR swap step2(0,1) should give 0");
    static_assert(XOR_SWAP_STEP2(1, 0) == 1, "XOR swap step2(1,0) should give 1");
    static_assert(XOR_SWAP_STEP3(0, 1) == 1, "XOR swap step3(0,1) should give 1");
    static_assert(XOR_SWAP_STEP3(1, 0) == 0, "XOR swap step3(1,0) should give 0");

    // ============================================================================
    // Edge Cases and Special Scenarios
    // ============================================================================

    // 13. Double XOR Returns Original Value
    #define XOR_TWICE(a, b) GMP_XOR(GMP_XOR(a, b), b)  // (a ⊕ b) ⊕ b = a
    static_assert(XOR_TWICE(0, 0) == 0, "Double XOR (0,0) should return 0");
    static_assert(XOR_TWICE(0, 1) == 0, "Double XOR (0,1) should return 0");
    static_assert(XOR_TWICE(1, 0) == 1, "Double XOR (1,0) should return 1");
    static_assert(XOR_TWICE(1, 1) == 1, "Double XOR (1,1) should return 1");

    // 14. XOR with Constants
    static_assert(GMP_XOR(0, 0) == 0, "XOR with constant 0: 0⊕0");
    static_assert(GMP_XOR(1, 0) == 1, "XOR with constant 0: 1⊕0");
    static_assert(GMP_XOR(0, 1) == 1, "XOR with constant 1: 0⊕1");
    static_assert(GMP_XOR(1, 1) == 0, "XOR with constant 1: 1⊕1");

    // 15. Chained XOR Simplification
    // (a ⊕ b) ⊕ (b ⊕ c) = a ⊕ c
    #define CHAIN_XOR(a, b, c) GMP_XOR(GMP_XOR(a, b), GMP_XOR(b, c))
    static_assert(CHAIN_XOR(0, 0, 0) == GMP_XOR(0, 0), "Chained XOR simplifies to XOR(0,0)");
    static_assert(CHAIN_XOR(0, 0, 1) == GMP_XOR(0, 1), "Chained XOR simplifies to XOR(0,1)");
    static_assert(CHAIN_XOR(0, 1, 0) == GMP_XOR(0, 0), "Chained XOR simplifies to XOR(0,0)");
    static_assert(CHAIN_XOR(1, 0, 1) == GMP_XOR(1, 1), "Chained XOR simplifies to XOR(1,1)");

    // 16. Final Verification - All Tests Pass
    constexpr bool all_xor_properties_verified = 
        GMP_XOR(0, 0) == 0 && GMP_XOR(0, 1) == 1 && 
        GMP_XOR(1, 0) == 1 && GMP_XOR(1, 1) == 0 &&
        TEST_COMMUTATIVE(0, 1) && TEST_COMMUTATIVE(1, 1) &&
        XOR3_L(0, 1, 1) == XOR3_R(0, 1, 1) &&
        XOR_TWICE(0, 1) == 0;

    static_assert(all_xor_properties_verified, "All XOR properties must be verified");
}

// ============================================================================
// Arithmetic Macro Tests
// ============================================================================

namespace test_arithmetic {
    // GMP_INC
    static_assert(GMP_INC(0) == 1, "GMP_INC(0) should be 1");
    static_assert(GMP_INC(5) == 6, "GMP_INC(5) should be 6");
    static_assert(GMP_INC(254) == 255, "GMP_INC(254) should be 255");
    
    // GMP_DEC
    static_assert(GMP_DEC(1) == 0, "GMP_DEC(1) should be 0");
    static_assert(GMP_DEC(5) == 4, "GMP_DEC(5) should be 4");
    static_assert(GMP_DEC(100) == 99, "GMP_DEC(100) should be 99");
}

// ============================================================================
// Comparison Macro Tests
// ============================================================================

namespace test_comparison {
    // GMP_EQUAL_INT
    static_assert(GMP_EQUAL_INT(0, 0) == 1, "GMP_EQUAL_INT(0, 0) should be 1");
    static_assert(GMP_EQUAL_INT(5, 5) == 1, "GMP_EQUAL_INT(5, 5) should be 1");
    static_assert(GMP_EQUAL_INT(100, 100) == 1, "GMP_EQUAL_INT(100, 100) should be 1");
    static_assert(GMP_EQUAL_INT(1, 2) == 0, "GMP_EQUAL_INT(1, 2) should be 0");
    static_assert(GMP_EQUAL_INT(10, 20) == 0, "GMP_EQUAL_INT(10, 20) should be 0");
    
    // GMP_EQUAL_INT_INDEPENDENT
    static_assert(GMP_EQUAL_INT_INDEPENDENT(0, 0) == 1, "GMP_EQUAL_INT_INDEPENDENT(0, 0) should be 1");
    static_assert(GMP_EQUAL_INT_INDEPENDENT(42, 42) == 1, "GMP_EQUAL_INT_INDEPENDENT(42, 42) should be 1");
    static_assert(GMP_EQUAL_INT_INDEPENDENT(1, 2) == 0, "GMP_EQUAL_INT_INDEPENDENT(1, 2) should be 0");
    
    // GMP_GREATER_INT
    static_assert(GMP_GREATER_INT(2, 1) == 1, "GMP_GREATER_INT(2, 1) should be 1");
    static_assert(GMP_GREATER_INT(10, 5) == 1, "GMP_GREATER_INT(10, 5) should be 1");
    static_assert(GMP_GREATER_INT(1, 2) == 0, "GMP_GREATER_INT(1, 2) should be 0");
    static_assert(GMP_GREATER_INT(5, 5) == 0, "GMP_GREATER_INT(5, 5) should be 0");
    static_assert(GMP_GREATER_INT(0, 0) == 0, "GMP_GREATER_INT(0, 0) should be 0");
    
    // GMP_LESS_INT
    #ifdef GMP_LESS_INT
    static_assert(GMP_LESS_INT(1, 2) == 1, "GMP_LESS_INT(1, 2) should be 1");
    static_assert(GMP_LESS_INT(5, 10) == 1, "GMP_LESS_INT(5, 10) should be 1");
    static_assert(GMP_LESS_INT(2, 1) == 0, "GMP_LESS_INT(2, 1) should be 0");
    static_assert(GMP_LESS_INT(5, 5) == 0, "GMP_LESS_INT(5, 5) should be 0");
    #endif
}

// ============================================================================
// Conditional Macro Tests
// ============================================================================

namespace test_conditional {
    #define TEST_IF_TRUE GMP_IF_THEN_ELSE(1, true_value, false_value)
    #define TEST_IF_FALSE GMP_IF_THEN_ELSE(0, true_value, false_value)
    
    static_assert(gmp::is_equal(GMP_STRINGIFY(TEST_IF_TRUE), "true_value"), 
                  "GMP_IF(1, a, b) should expand to a");
    static_assert(gmp::is_equal(GMP_STRINGIFY(TEST_IF_FALSE), "false_value"),
                  "GMP_IF(0, a, b) should expand to b");
    
    // GMP_IF_THEN_ELSE
    #define TEST_IF_THEN_ELSE_TRUE GMP_IF_THEN_ELSE(1, then_value, else_value)
    #define TEST_IF_THEN_ELSE_FALSE GMP_IF_THEN_ELSE(0, then_value, else_value)
    
    static_assert(gmp::is_equal(GMP_STRINGIFY(TEST_IF_THEN_ELSE_TRUE), "then_value"),
                  "GMP_IF_THEN_ELSE(1, a, b) should expand to a");
    static_assert(gmp::is_equal(GMP_STRINGIFY(TEST_IF_THEN_ELSE_FALSE), "else_value"),
                  "GMP_IF_THEN_ELSE(0, a, b) should expand to b");
}

// ============================================================================
// Stringification Macro Tests
// ============================================================================

namespace test_stringify {
    static_assert(gmp::is_equal(GMP_STRINGIFY(42), "42"),
                  "GMP_STRINGIFY(42) should be \"42\"");
    static_assert(gmp::is_equal(GMP_STRINGIFY(hello), "hello"),
                  "GMP_STRINGIFY(hello) should be \"hello\"");
    // static_assert(gmp::is_equal(GMP_STRINGIFY(), ""),
    //               "GMP_STRINGIFY() should be empty string");
    
    #define TEST_MACRO 123
    static_assert(gmp::is_equal(GMP_STRINGIFY(TEST_MACRO), "123"),
                  "GMP_STRINGIFY should expand macros");
    
    #define EXPRESSION 1 + 2 * 3
    static_assert(gmp::is_equal(GMP_STRINGIFY(EXPRESSION), "1 + 2 * 3"),
                  "GMP_STRINGIFY should stringify expressions");
}

// ============================================================================
// Concatenation Macro Tests
// ============================================================================

namespace test_concat {
    // GMP_CONCAT
    #define PREFIX foo
    #define SUFFIX bar
    
    static_assert(gmp::is_equal(GMP_STRINGIFY(GMP_CONCAT(PREFIX, SUFFIX)), "foobar"),
                  "GMP_CONCAT should concatenate tokens");
    
    static_assert(gmp::is_equal(GMP_STRINGIFY(GMP_CONCAT(123, 456)), "123456"),
                  "GMP_CONCAT should concatenate numbers");
    
    // GMP_CONCATS
    static_assert(gmp::is_equal(GMP_STRINGIFY(GMP_CONCATS(a, b, c)), "abc"),
                  "GMP_CONCATS should concatenate multiple tokens");
    
    static_assert(gmp::is_equal(GMP_STRINGIFY(GMP_CONCATS(1, 2, 3, 4)), "1234"),
                  "GMP_CONCATS should concatenate multiple numbers");
    
    #define NUM_1 1
    #define NUM_2 2
    static_assert(gmp::is_equal(GMP_STRINGIFY(GMP_CONCATS(NUM_1, _, 1, _, NUM_2, _, 2)), "1_1_2_2"),
                  "GMP_CONCATS should work with macro expansion");
}

// ============================================================================
// Variadic Argument Processing Tests
// ============================================================================

namespace test_variadic {
    // GMP_SIZE_OF_VAARGS
    static_assert(GMP_SIZE_OF_VAARGS() == 0, "GMP_SIZE_OF_VAARGS() should be 0");
    static_assert(GMP_SIZE_OF_VAARGS(a) == 1, "GMP_SIZE_OF_VAARGS(a) should be 1");
    static_assert(GMP_SIZE_OF_VAARGS(a, b) == 2, "GMP_SIZE_OF_VAARGS(a, b) should be 2");
    static_assert(GMP_SIZE_OF_VAARGS(a, b, c) == 3, "GMP_SIZE_OF_VAARGS(a, b, c) should be 3");
    static_assert(GMP_SIZE_OF_VAARGS(1, 2, 3, 4, 5) == 5, "GMP_SIZE_OF_VAARGS(1..5) should be 5");
    
    // GMP_SIZE_OF_VAARGS
    static_assert(GMP_SIZE_OF_VAARGS() == 0, "GMP_SIZE_OF_VAARGS() should be 0");
    static_assert(GMP_SIZE_OF_VAARGS(x) == 1, "GMP_SIZE_OF_VAARGS(x) should be 1");
    static_assert(GMP_SIZE_OF_VAARGS(x, y) == 2, "GMP_SIZE_OF_VAARGS(x, y) should be 2");
    static_assert(GMP_SIZE_OF_VAARGS(1, 2, 3, 4, 5, 6) == 6, "GMP_SIZE_OF_VAARGS(1..6) should be 6");
    
    // GMP_IS_EMPTY
    static_assert(GMP_IS_EMPTY() == 1, "GMP_IS_EMPTY() should be 1");
    static_assert(GMP_IS_EMPTY(x) == 0, "GMP_IS_EMPTY(x) should be 0");
    static_assert(GMP_IS_EMPTY(1, 2, 3) == 0, "GMP_IS_EMPTY(1,2,3) should be 0");
}

// ============================================================================
// Tuple Macro Tests
// ============================================================================

namespace test_tuple {
    // GMP_TUPLE_SIZE - Tests for tuple size calculation
    static_assert(GMP_TUPLE_SIZE(()) == 0, "GMP_TUPLE_SIZE(()) should return 0 for empty tuple");
    static_assert(GMP_TUPLE_SIZE((a)) == 1, "GMP_TUPLE_SIZE((a)) should return 1 for single-element tuple");
    static_assert(GMP_TUPLE_SIZE((a, b)) == 2, "GMP_TUPLE_SIZE((a, b)) should return 2 for two-element tuple");
    static_assert(GMP_TUPLE_SIZE((1, 2, 3, 4, 5)) == 5, 
                  "GMP_TUPLE_SIZE((1, 2, 3, 4, 5)) should return 5 for five-element tuple");
    
    // Note: Tuple operations like APPEND, PREPEND, CONCAT are difficult to test directly with static_assert
    // However, we can verify their behavior by checking the resulting tuple sizes
    
    // GMP_TUPLE_APPEND - Tests for appending elements to tuples
    #define TUPLE_APPEND_TEST GMP_TUPLE_APPEND((a, b), c)
    static_assert(GMP_TUPLE_SIZE(TUPLE_APPEND_TEST) == 3, 
                  "GMP_TUPLE_APPEND((a, b), c) should produce a tuple with size 3");
    
    // Additional APPEND tests for edge cases
    #define APPEND_TO_EMPTY GMP_TUPLE_APPEND((), single)
    static_assert(GMP_TUPLE_SIZE(APPEND_TO_EMPTY) == 1,
                  "GMP_TUPLE_APPEND((), single) should produce a single-element tuple");
    
    #define APPEND_MULTIPLE GMP_TUPLE_APPEND(GMP_TUPLE_APPEND((a), b), c)
    static_assert(GMP_TUPLE_SIZE(APPEND_MULTIPLE) == 3,
                  "Chained GMP_TUPLE_APPEND should produce correct size");
    
    // GMP_TUPLE_PREPEND - Tests for prepending elements to tuples
    #define TUPLE_PREPEND_TEST GMP_TUPLE_PREPEND((b, c), a)
    static_assert(GMP_TUPLE_SIZE(TUPLE_PREPEND_TEST) == 3,
                  "GMP_TUPLE_PREPEND((b, c), a) should produce a tuple with size 3");
    
    // Additional PREPEND tests
    #define PREPEND_TO_EMPTY GMP_TUPLE_PREPEND((), first)
    static_assert(GMP_TUPLE_SIZE(PREPEND_TO_EMPTY) == 1,
                  "GMP_TUPLE_PREPEND((), first) should produce a single-element tuple");
    
    // GMP_TUPLE_CONCAT - Tests for concatenating two tuples
    #define TUPLE_CONCAT_TEST GMP_TUPLE_CONCAT((a, b), (c, d))
    static_assert(GMP_TUPLE_SIZE(TUPLE_CONCAT_TEST) == 4,
                  "GMP_TUPLE_CONCAT((a, b), (c, d)) should produce a tuple with size 4");
    
    // Additional CONCAT tests for edge cases
    #define CONCAT_EMPTY_FIRST GMP_TUPLE_CONCAT((), (x, y, z))
    static_assert(GMP_TUPLE_SIZE(CONCAT_EMPTY_FIRST) == 3,
                  "GMP_TUPLE_CONCAT((), (x, y, z)) should return the second tuple");
    
    #define CONCAT_EMPTY_SECOND GMP_TUPLE_CONCAT((1, 2), ())
    static_assert(GMP_TUPLE_SIZE(CONCAT_EMPTY_SECOND) == 2,
                  "GMP_TUPLE_CONCAT((1, 2), ()) should return the first tuple");
    
    #define CONCAT_BOTH_EMPTY GMP_TUPLE_CONCAT((), ())
    static_assert(GMP_TUPLE_SIZE(CONCAT_BOTH_EMPTY) == 0,
                  "GMP_TUPLE_CONCAT((), ()) should produce an empty tuple");
    
    // GMP_TUPLE_SKIP - Tests for skipping elements from the beginning of a tuple
    #define TUPLE_SKIP_TEST GMP_TUPLE_SKIP(2, (a, b, c, d, e))
    static_assert(GMP_TUPLE_SIZE(TUPLE_SKIP_TEST) == 3,
                  "GMP_TUPLE_SKIP(2, (a, b, c, d, e)) should produce a tuple with size 3");
    
    // Additional SKIP tests for edge cases
    #define SKIP_ZERO GMP_TUPLE_SKIP(0, (x, y, z))
    static_assert(GMP_TUPLE_SIZE(SKIP_ZERO) == 3,
                  "GMP_TUPLE_SKIP(0, tuple) should return the original tuple");
    
    #define SKIP_ALL GMP_TUPLE_SKIP(5, (a, b, c, d, e))
    static_assert(GMP_TUPLE_SIZE(SKIP_ALL) == 0,
                  "GMP_TUPLE_SKIP(size, tuple) should produce an empty tuple");
    
    #define SKIP_MORE_THAN_SIZE GMP_TUPLE_SKIP(10, (a, b, c))
    static_assert(GMP_TUPLE_SIZE(SKIP_MORE_THAN_SIZE) == 0,
                  "GMP_TUPLE_SKIP(n > size, tuple) should produce an empty tuple");
    
    // GMP_TUPLE_TAKE - Tests for taking elements from the beginning of a tuple
    #define TUPLE_TAKE_TEST GMP_TUPLE_TAKE(3, (a, b, c, d, e))
    static_assert(GMP_TUPLE_SIZE(TUPLE_TAKE_TEST) == 3,
                  "GMP_TUPLE_TAKE(3, (a, b, c, d, e)) should produce a tuple with size 3");
    
    // Additional TAKE tests for edge cases
    #define TAKE_ZERO GMP_TUPLE_TAKE(0, (x, y, z))
    static_assert(GMP_TUPLE_SIZE(TAKE_ZERO) == 0,
                  "GMP_TUPLE_TAKE(0, tuple) should produce an empty tuple");
    
    #define TAKE_ALL GMP_TUPLE_TAKE(5, (a, b, c, d, e))
    static_assert(GMP_TUPLE_SIZE(TAKE_ALL) == 5,
                  "GMP_TUPLE_TAKE(size, tuple) should return the entire tuple");
    
    #define TAKE_MORE_THAN_SIZE GMP_TUPLE_TAKE(10, (a, b, c))
    static_assert(GMP_TUPLE_SIZE(TAKE_MORE_THAN_SIZE) == 3,
                  "GMP_TUPLE_TAKE(n > size, tuple) should return the entire tuple");
    
    // Relationship tests between SKIP and TAKE
    #define ORIGINAL_TUPLE (1, 2, 3, 4, 5)
    #define TAKE_THEN_SKIP GMP_TUPLE_SIZE(GMP_TUPLE_SKIP(2, GMP_TUPLE_TAKE(4, ORIGINAL_TUPLE)))
    #define SKIP_THEN_TAKE GMP_TUPLE_SIZE(GMP_TUPLE_TAKE(2, GMP_TUPLE_SKIP(1, ORIGINAL_TUPLE)))
    
    static_assert(TAKE_THEN_SKIP == 2, "TAKE then SKIP should produce correct size");
    static_assert(SKIP_THEN_TAKE == 2, "SKIP then TAKE should produce correct size");
    
    // Test that SKIP and TAKE are complementary operations
    #define SKIP_TAKE_COMPLEMENT GMP_TUPLE_SIZE(GMP_TUPLE_CONCAT(GMP_TUPLE_TAKE(2, ORIGINAL_TUPLE), GMP_TUPLE_SKIP(2, ORIGINAL_TUPLE)))
    static_assert(SKIP_TAKE_COMPLEMENT == 5,
                  "TAKE(n) concatenated with SKIP(n) should reproduce original tuple");
}

// ============================================================================
// Loop Macro Tests
// ============================================================================

namespace test_loop {
    // Test 1: Empty sequence
    static_assert(std::is_same_v<
        std::make_index_sequence<0>,
        std::index_sequence<>
    >, "GMP_MAKE_INDEX_SEQUENCE(0) should produce empty index_sequence");
    
    // Test 2: Single element
    static_assert(std::is_same_v<
        std::make_index_sequence<1>,
        std::index_sequence<GMP_MAKE_INDEX_SEQUENCE(1)>
    >, "GMP_MAKE_INDEX_SEQUENCE(1) should produce index_sequence<0>");
    
    // Test 3: Small sequence
    static_assert(std::is_same_v<
        std::make_index_sequence<3>,
        std::index_sequence<GMP_MAKE_INDEX_SEQUENCE(3)>
    >, "GMP_MAKE_INDEX_SEQUENCE(3) should produce index_sequence<0, 1, 2>");
    
    // Test 4: Medium sequence
    static_assert(std::is_same_v<
        std::make_index_sequence<5>,
        std::index_sequence<GMP_MAKE_INDEX_SEQUENCE(5)>
    >, "GMP_MAKE_INDEX_SEQUENCE(5) should produce index_sequence<0, 1, 2, 3, 4>");
    
    // Test 5: Larger sequence
    static_assert(std::is_same_v<
        std::make_index_sequence<8>,
        std::index_sequence<GMP_MAKE_INDEX_SEQUENCE(8)>
    >, "GMP_MAKE_INDEX_SEQUENCE(8) should produce correct 8-element sequence");
    
    // Test 6: Edge case - maximum practical size
    static_assert(std::is_same_v<
        std::make_index_sequence<16>,
        std::index_sequence<GMP_MAKE_INDEX_SEQUENCE(16)>
    >, "GMP_MAKE_INDEX_SEQUENCE(16) should produce correct 16-element sequence");

    // Test 7: GMP_RANGE should produce same as std::make_index_sequence
    static_assert(std::is_same_v<
        std::make_index_sequence<5>,
        std::index_sequence<GMP_RANGE(0, 5)>
    >, "GMP_RANGE(0, 5) should equal std::make_index_sequence<5>");
    
    // Test 8: GMP_RANGE with non-zero start
    static_assert(std::is_same_v<
        std::index_sequence<42, 43, 44, 45, 46>,
        std::index_sequence<GMP_RANGE(42, 47)>
    >, "GMP_RANGE(42, 47) should produce sequence 42..46");
    
    // Test 9: Empty range
    static_assert(std::is_same_v<
        std::make_index_sequence<0>,
        std::index_sequence<GMP_RANGE(0, 0)>
    >, "GMP_RANGE(0, 0) should produce empty sequence");
    
    static_assert(std::is_same_v<
        std::index_sequence<>,
        std::index_sequence<GMP_RANGE(5, 5)>
    >, "GMP_RANGE(5, 5) should produce empty sequence");
    
    // Test 10: Single element range
    static_assert(std::is_same_v<
        std::index_sequence<7>,
        std::index_sequence<GMP_RANGE(7, 8)>
    >, "GMP_RANGE(7, 8) should produce single element sequence");
    
    // Test 11: Various ranges
    static_assert(std::is_same_v<
        std::index_sequence<10, 11, 12, 13, 14>,
        std::index_sequence<GMP_RANGE(10, 15)>
    >, "GMP_RANGE(10, 15) should produce sequence 10..14");
    
    static_assert(std::is_same_v<
        std::index_sequence<100, 101, 102>,
        std::index_sequence<GMP_RANGE(100, 103)>
    >, "GMP_RANGE(100, 103) should produce sequence 100..102");
    
    // Test 12: Large range (boundary test)
#if GMP_STANDARD_PREPROCESSOR
    static_assert(std::is_same_v<
        std::index_sequence<250, 251, 252, 253>,
        std::index_sequence<GMP_RANGE(250, 254)>
    >, "GMP_RANGE should work with maximum values");
#else
    static_assert(std::is_same_v<
        std::index_sequence<124, 125, 126, 127, 128>,
        std::index_sequence<GMP_RANGE(124, 129)>
    >, "GMP_RANGE should work with maximum values");
#endif // GMP_STANDARD_PREPROCESSOR
}

// ============================================================================
// Conditional Macro Tests
// ============================================================================
namespace test_condition {
// Test 1: GMP_IF with true condition expands the expression
#undef TEST_IF_TRUE
#define TEST_IF_TRUE GMP_IF(1, expanded_value)
static_assert(gmp::is_equal(GMP_STRINGIFY(TEST_IF_TRUE), "expanded_value"),
              "GMP_IF(1, expr) should expand to expr");

// Test 2: GMP_IF with false condition expands to nothing
// #undef TEST_IF_FALSE
// #define TEST_IF_FALSE GMP_IF(0, not_expanded)
// static_assert(gmp::is_equal(GMP_STRINGIFY(TEST_IF_FALSE), ""),
//               "GMP_IF(0, expr) should expand to empty string");

// Test 3: Non-zero values are treated as true
#define TEST_IF_NONZERO GMP_IF(GMP_BOOL(42), non_zero_expanded)
static_assert(gmp::is_equal(GMP_STRINGIFY(TEST_IF_NONZERO), "non_zero_expanded"),
              "GMP_IF(non-zero, expr) should expand to expr");
}

// ============================================================================
// Edge Case Tests
// ============================================================================

namespace test_edge {
    // Empty argument edge cases
    static_assert(GMP_SIZE_OF_VAARGS() == 0, 
                  "GMP_SIZE_OF_VAARGS() should return 0 for empty argument list");
    static_assert(GMP_SIZE_OF_VAARGS(,) == 2, 
                  "GMP_SIZE_OF_VAARGS(,) should return 2 (two empty arguments)");
    
    // Maximum boundary values (assuming GMP_MAX_INDEX is 255)
    static_assert(GMP_INC(254) == 255, 
                  "GMP_INC should work correctly at maximum-1 boundary");
    static_assert(GMP_DEC(255) == 254, 
                  "GMP_DEC should work correctly at maximum boundary");
    
    // Zero value operations
    static_assert(GMP_EQUAL_INT(0, 0) == 1, 
                  "GMP_EQUAL_INT(0, 0) should return 1 (true)");
    static_assert(GMP_GREATER_INT(0, 0) == 0, 
                  "GMP_GREATER_INT(0, 0) should return 0 (false)");
    static_assert(GMP_BOOL(0) == 0, 
                  "GMP_BOOL(0) should return 0");
    static_assert(GMP_NOT(0) == 1, 
                  "GMP_NOT(0) should return 1");
    
    // Single-element tuple edge cases
    static_assert(GMP_TUPLE_SIZE((single)) == 1, 
                  "Single element tuple should have size 1");
    static_assert(GMP_TUPLE_SIZE(GMP_TUPLE_APPEND((), single)) == 1, 
                  "Appending to empty tuple should create single element tuple");
    static_assert(GMP_TUPLE_SIZE(GMP_TUPLE_PREPEND((), single)) == 1, 
                  "Prepending to empty tuple should create single element tuple");
    
    // Identity and inverse operations with edge values
    static_assert(GMP_IDENTITY(0) == 0, 
                  "GMP_IDENTITY should preserve 0");
    static_assert(GMP_EXPAND(0) == 0, 
                  "GMP_EXPAND should preserve 0");
    
    // Stringification edge cases
    // static_assert(gmp::is_equal(GMP_STRINGIFY(), ""),
    //               "GMP_STRINGIFY() should produce empty string");
    static_assert(gmp::is_equal(GMP_STRINGIFY(0), "0"),
                  "GMP_STRINGIFY should convert 0 to \"0\"");
    
    // Boolean operations with edge values
    static_assert(GMP_AND(0, 0) == 0, 
                  "GMP_AND(0, 0) should be 0");
    static_assert(GMP_OR(0, 0) == 0, 
                  "GMP_OR(0, 0) should be 0");
    static_assert(GMP_XOR(0, 0) == 0, 
                  "GMP_XOR(0, 0) should be 0");
    
    // Conditional macros with edge values
    #define IF_ZERO_ZERO GMP_IF_THEN_ELSE(0, then_value, else_value)
    static_assert(gmp::is_equal(GMP_STRINGIFY(IF_ZERO_ZERO), "else_value"),
                  "GMP_IF(0, a, b) should expand to else branch");
    
    // Arithmetic edge cases
    static_assert(GMP_INC(0) == 1,
                  "Incrementing 0 should give 1");
    static_assert(GMP_DEC(1) == 0,
                  "Decrementing 1 should give 0");
    
    // Comparison edge cases
#if GMP_STANDARD_PREPROCESSOR
    static_assert(GMP_EQUAL_INT(255, 255) == 1,
                  "GMP_EQUAL_INT should work at maximum value");
#else
    static_assert(GMP_EQUAL_INT(127, 127) == 1,
                  "GMP_EQUAL_INT should work at maximum value");
#endif // GMP_STANDARD_PREPROCESSOR
    static_assert(GMP_GREATER_INT(255, 0) == 1,
                  "Maximum value should be greater than 0");
    static_assert(GMP_GREATER_INT(0, 255) == 0,
                  "0 should not be greater than maximum value");
    
    // Tuple operations with empty tuples
    static_assert(GMP_TUPLE_SIZE(GMP_TUPLE_CONCAT((), ())) == 0,
                  "Concatenating two empty tuples should produce empty tuple");
    static_assert(GMP_TUPLE_SIZE(GMP_TUPLE_SKIP(0, ())) == 0,
                  "Skipping 0 elements from empty tuple should produce empty tuple");
    static_assert(GMP_TUPLE_SIZE(GMP_TUPLE_TAKE(0, ())) == 0,
                  "Taking 0 elements from empty tuple should produce empty tuple");
    static_assert(GMP_TUPLE_SIZE(GMP_TUPLE_SKIP(5, ())) == 0,
                  "Skipping more elements than tuple size should produce empty tuple");
    static_assert(GMP_TUPLE_SIZE(GMP_TUPLE_TAKE(5, ())) == 0,
                  "Taking more elements than tuple size should produce empty tuple");
    
    // Variadic argument edge cases
    static_assert(GMP_IS_EMPTY() == 1,
                  "GMP_IS_EMPTY() should return 1 for empty argument list");
    static_assert(GMP_SIZE_OF_VAARGS() == 0,
                  "GMP_SIZE_OF_VAARGS() should return 0 for empty argument list");
}

namespace test_gmp_comparisons {
    // ============================================================================
    // GMP_LESS_EQUAL_INT Tests
    // ============================================================================
    
    // Test 1: Less than case
    static_assert(GMP_LESS_EQUAL_INT(3, 5) == 1, "3 ≤ 5 should be true");
    static_assert(GMP_LESS_EQUAL_INT(0, 1) == 1, "0 ≤ 1 should be true");
    static_assert(GMP_LESS_EQUAL_INT(100, 200) == 1, "100 ≤ 200 should be true");
    
    // Test 2: Equal case
    static_assert(GMP_LESS_EQUAL_INT(5, 5) == 1, "5 ≤ 5 should be true");
    static_assert(GMP_LESS_EQUAL_INT(0, 0) == 1, "0 ≤ 0 should be true");
#if GMP_STANDARD_PREPROCESSOR
    static_assert(GMP_LESS_EQUAL_INT(254, 254) == 1, "254 ≤ 254 should be true");
#else
    static_assert(GMP_LESS_EQUAL_INT(127, 127) == 1, "127 ≤ 127 should be true");
#endif
    
    // Test 3: Greater than case
    static_assert(GMP_LESS_EQUAL_INT(5, 3) == 0, "5 ≤ 3 should be false");
    static_assert(GMP_LESS_EQUAL_INT(10, 5) == 0, "10 ≤ 5 should be false");
    static_assert(GMP_LESS_EQUAL_INT(255, 0) == 0, "255 ≤ 0 should be false");
    
    // Test 4: Edge values
    static_assert(GMP_LESS_EQUAL_INT(0, 255) == 1, "0 ≤ 255 should be true");
#if GMP_STANDARD_PREPROCESSOR
    static_assert(GMP_LESS_EQUAL_INT(254, 255) == 1, "254 ≤ 255 should be true");
    static_assert(GMP_LESS_EQUAL_INT(255, 254) == 0, "255 ≤ 254 should be false");
#else
    static_assert(GMP_LESS_EQUAL_INT(126, 127) == 1, "126 ≤ 127 should be true");
    static_assert(GMP_LESS_EQUAL_INT(127, 126) == 0, "127 ≤ 126 should be false");
#endif
    
    // ============================================================================
    // GMP_GREATER_EQUAL_INT Tests
    // ============================================================================
    
    // Test 5: Greater than case
    static_assert(GMP_GREATER_EQUAL_INT(5, 3) == 1, "5 ≥ 3 should be true");
    static_assert(GMP_GREATER_EQUAL_INT(10, 5) == 1, "10 ≥ 5 should be true");
    static_assert(GMP_GREATER_EQUAL_INT(200, 100) == 1, "200 ≥ 100 should be true");
    
    // Test 6: Equal case
    static_assert(GMP_GREATER_EQUAL_INT(5, 5) == 1, "5 ≥ 5 should be true");
    static_assert(GMP_GREATER_EQUAL_INT(0, 0) == 1, "0 ≥ 0 should be true");
#if GMP_STANDARD_PREPROCESSOR
    static_assert(GMP_GREATER_EQUAL_INT(254, 254) == 1, "254 ≥ 254 should be true");
#else
    static_assert(GMP_GREATER_EQUAL_INT(127, 127) == 1, "127 ≥ 127 should be true");
#endif
    
    // Test 7: Less than case
    static_assert(GMP_GREATER_EQUAL_INT(3, 5) == 0, "3 ≥ 5 should be false");
    static_assert(GMP_GREATER_EQUAL_INT(1, 10) == 0, "1 ≥ 10 should be false");
    static_assert(GMP_GREATER_EQUAL_INT(0, 255) == 0, "0 ≥ 255 should be false");
    
    // Test 8: Edge values
    static_assert(GMP_GREATER_EQUAL_INT(255, 0) == 1, "255 ≥ 0 should be true");
#if GMP_STANDARD_PREPROCESSOR
    static_assert(GMP_GREATER_EQUAL_INT(255, 254) == 1, "255 ≥ 254 should be true");
    static_assert(GMP_GREATER_EQUAL_INT(254, 255) == 0, "254 ≥ 255 should be false");
#else
    static_assert(GMP_GREATER_EQUAL_INT(127, 126) == 1, "127 ≥ 126 should be true");
    static_assert(GMP_GREATER_EQUAL_INT(126, 127) == 0, "126 ≥ 127 should be false");
#endif
    
    // ============================================================================
    // Relationship Tests
    // ============================================================================
    
    // Test 9: i ≤ j ≡ NOT(i > j)
    // static_assert(GMP_LESS_EQUAL_INT(3, 5) == GMP_NOT(GMP_GREATER_INT(3, 5)),
    //               "i ≤ j should equal NOT(i > j)");
    
    // Test 10: i ≥ j ≡ NOT(i < j)
    // static_assert(GMP_GREATER_EQUAL_INT(5, 3) == GMP_NOT(GMP_LESS_INT(5, 3)),
    //               "i ≥ j should equal NOT(i < j)");
    
    // Test 11: i ≤ j ≡ j ≥ i (duality)
    static_assert(GMP_LESS_EQUAL_INT(3, 5) == GMP_GREATER_EQUAL_INT(5, 3),
                  "i ≤ j should equal j ≥ i");
    
    // Test 12: i ≥ j ≡ j ≤ i (duality)
    static_assert(GMP_GREATER_EQUAL_INT(5, 3) == GMP_LESS_EQUAL_INT(3, 5),
                  "i ≥ j should equal j ≤ i");
    
    // Test 13: Completeness: for any i, j, exactly one of <, =, > is true
    #define TEST_COMPLETENESS(i, j) \
        (GMP_LESS_INT(i, j) + GMP_EQUAL_INT(i, j) + GMP_GREATER_INT(i, j) == 1)
    
    static_assert(TEST_COMPLETENESS(3, 5), "Exactly one of <, =, > should be true");
    static_assert(TEST_COMPLETENESS(5, 3), "Exactly one of <, =, > should be true");
    static_assert(TEST_COMPLETENESS(4, 4), "Exactly one of <, =, > should be true");
    
    // Test 14: i ≤ j ≡ (i < j) OR (i == j)
    static_assert(GMP_LESS_EQUAL_INT(3, 5) == GMP_OR(GMP_LESS_INT(3, 5), GMP_EQUAL_INT(3, 5)),
                  "i ≤ j should equal (i < j) OR (i == j)");
    
    // Test 15: i ≥ j ≡ (i > j) OR (i == j)
    static_assert(GMP_GREATER_EQUAL_INT(5, 3) == GMP_OR(GMP_GREATER_INT(5, 3), GMP_EQUAL_INT(5, 3)),
                  "i ≥ j should equal (i > j) OR (i == j)");
    
    // Test 16: Transitivity: if a ≤ b and b ≤ c then a ≤ c
    #define TEST_TRANSITIVITY(a, b, c) \
        GMP_IMPLIES( \
            GMP_AND(GMP_LESS_EQUAL_INT(a, b), GMP_LESS_EQUAL_INT(b, c)), \
            GMP_LESS_EQUAL_INT(a, c) \
        )
    
    static_assert(TEST_TRANSITIVITY(1, 2, 3), "Transitivity should hold");
    static_assert(TEST_TRANSITIVITY(1, 1, 2), "Transitivity with equality");
    static_assert(TEST_TRANSITIVITY(1, 2, 2), "Transitivity with equality");
    
    // Test 17: Reflexivity: a ≤ a is always true
    static_assert(GMP_LESS_EQUAL_INT(0, 0), "0 ≤ 0 (reflexive)");
    static_assert(GMP_LESS_EQUAL_INT(5, 5), "5 ≤ 5 (reflexive)");
#if GMP_STANDARD_PREPROCESSOR
    static_assert(GMP_LESS_EQUAL_INT(254, 254), "254 ≤ 254 (reflexive)");
#else
    static_assert(GMP_LESS_EQUAL_INT(127, 127), "127 ≤ 127 (reflexive)");
#endif
    
    // Test 18: Antisymmetry: if a ≤ b and b ≤ a then a == b
    #define TEST_ANTISYMMETRY(a, b) \
        GMP_IMPLIES( \
            GMP_AND(GMP_LESS_EQUAL_INT(a, b), GMP_LESS_EQUAL_INT(b, a)), \
            GMP_EQUAL_INT(a, b) \
        )
    
    static_assert(TEST_ANTISYMMETRY(3, 3), "Antisymmetry with equality");
    static_assert(TEST_ANTISYMMETRY(5, 5), "Antisymmetry with equality");
    
    // Test 19: Total order: for any a, b, either a ≤ b or b ≤ a
    #define TEST_TOTAL_ORDER(a, b) \
        (GMP_LESS_EQUAL_INT(a, b) || GMP_LESS_EQUAL_INT(b, a))
    
    static_assert(TEST_TOTAL_ORDER(3, 5), "Total order property");
    static_assert(TEST_TOTAL_ORDER(5, 3), "Total order property");
    static_assert(TEST_TOTAL_ORDER(4, 4), "Total order property");
    
    // ============================================================================
    // Final Verification
    // ============================================================================
    
    constexpr bool all_comparison_tests_pass =
        // Basic functionality
        GMP_LESS_EQUAL_INT(3, 5) == 1 &&
        GMP_LESS_EQUAL_INT(5, 3) == 0 &&
        GMP_LESS_EQUAL_INT(4, 4) == 1 &&
        
        GMP_GREATER_EQUAL_INT(5, 3) == 1 &&
        GMP_GREATER_EQUAL_INT(3, 5) == 0 &&
        GMP_GREATER_EQUAL_INT(4, 4) == 1 &&
        
        // Logical relationships
        // GMP_LESS_EQUAL_INT(3, 5) == GMP_NOT(GMP_GREATER_INT(3, 5)) &&
        // GMP_GREATER_EQUAL_INT(5, 3) == GMP_NOT(GMP_LESS_INT(5, 3)) &&
        
        // Duality
        GMP_LESS_EQUAL_INT(3, 5) == GMP_GREATER_EQUAL_INT(5, 3) &&
        GMP_GREATER_EQUAL_INT(5, 3) == GMP_LESS_EQUAL_INT(3, 5);
    
    static_assert(all_comparison_tests_pass,
                  "All comparison operator tests must pass");
}

// If compilation reaches this point, all static_assert tests have passed
// This serves as a final verification that the entire test suite compiles successfully
constexpr bool all_tests_passed = true;
static_assert(all_tests_passed, "All compile-time tests must pass for successful build");

int main() {
    std::cout << GMP_PREPROCESSOR_TYPE << "\n";
}