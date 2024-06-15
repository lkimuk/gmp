#ifndef GMP_MACRO_HPP_
#define GMP_MACRO_HPP_


/**
 * \def GMP_EXPAND(x)
 * \brief Force the expansion of a macro.
 * 
 * This macro forces the expansion of its argument \a x.
 * It is often used as an intermediary step to ensure that
 * macro arguments are fully expanded before being passed
 * to other macros.
 *
 * \param x The macro to be expanded.
 * \return The expanded result of \a x.
 *
 * \par Example
 * \code
 * #define FOO 42
 * #define BAR FOO
 * #define BAZ(x) GMP_EXPAND(x)
 *
 * int value = BAZ(BAR); // value will be 42
 * \endcode
 */
#define GMP_EXPAND(x) x

/**
 * \def GMP_CONCAT_HELPER(lhs, rhs)
 * \brief Helper macro to concatenate two tokens.
 *
 * This macro performs the actual concatenation of two tokens.
 * It is used internally by the \ref GMP_CONCAT macro to ensure
 * proper expansion of the tokens before concatenation.
 *
 * \param lhs First token.
 * \param rhs Second token.
 * \return The concatenation of \a lhs and \a rhs.
 */
#define GMP_CONCAT_HELPER(lhs, rhs) lhs ## rhs

/**
 * \def GMP_CONCAT(lhs, rhs)
 * \brief  Concatenates two tokens after expanding them.
 * 
 * This macro concatenates two tokens \a lhs and \a rhs after
 * expanding them. It uses \ref GMP_CONCAT_HELPER to perform the
 * actual concatenation. 
 * 
 * \param lhs First token.
 * \param rhs Second token.
 * \return The concatenation of the expanded \a lhs and \a rhs.
 * 
 * \par Example
 * \code
 * #define FOO 1
 * #define BAR 2
 * GMP_CONCAT(FOO, BAR) // Results in 12
 * \endcode
 */
#define GMP_CONCAT(lhs, rhs) GMP_CONCAT_HELPER(lhs, rhs)


/**
 * \brief Get the number of variable arguments.
 *
 * This macro calculates the number of variable arguments passed to it by expanding
 * all arguments recursively until the last one is found, determining the count of arguments.
 *
 * \param ... Variable argument list
 * \return Number of arguments
 */
#define GMP_GET_VARARGS(...) GMP_EXPAND( _GMP_GET_VARARGS_IMPL(__VA_ARGS__) )
// #define _GMP_GET_VARARGS_IMPL(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, \
//                         _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, \
//                         _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, \
//                         _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, \
//                         _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, \
//                         _92, _93, _94, _95, _96, _97, _98, _99, _100, _101, _102, _103, _104, _105, _106, _107, _108, \
//                         _109, _110, _111, _112, _113, _114, _115, _116, _117, _118, _119, _120, _121, _122, _123, _124, \
//                         N, ...) N
#define _GMP_GET_VARARGS_IMPL( \
    _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, \
    _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, \
    _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, \
    _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, \
    _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, \
    _92, _93, _94, _95, _96, _97, _98, _99, _100, _101, _102, _103, _104, _105, _106, _107, _108, \
    _109, _110, _111, _112, _113, _114, _115, _116, _117, _118, _119, _120, _121, _122, _123, _124, \
    _125, _126, _127, _128, _129, _130, _131, _132, _133, _134, _135, _136, _137, _138, _139, _140, \
    _141, _142, _143, _144, _145, _146, _147, _148, _149, _150, _151, _152, _153, _154, _155, _156, \
    _157, _158, _159, _160, _161, _162, _163, _164, _165, _166, _167, _168, _169, _170, _171, _172, \
    _173, _174, _175, _176, _177, _178, _179, _180, _181, _182, _183, _184, _185, _186, _187, _188, \
    _189, _190, _191, _192, _193, _194, _195, _196, _197, _198, _199, _200, _201, _202, _203, _204, \
    _205, _206, _207, _208, _209, _210, _211, _212, _213, _214, _215, _216, _217, _218, _219, _220, \
    _221, _222, _223, _224, _225, _226, _227, _228, _229, _230, _231, _232, _233, _234, _235, _236, \
    _237, _238, _239, _240, _241, _242, _243, _244, _245, _246, _247, _248, _249, _250, _251, _252, \
    _253, _254, N, ...) N

/**
 * \def GMP_SIZE_OF_VAARGS(...)
 * \brief Get the size of variable arguments.
 * 
 * \param ... Variable argument list
 * \return Size of arguments
 * 
 * \par Example
 * \code
 * GMP_SIZE_OF_VAARGS()                      // 0
 * GMP_SIZE_OF_VAARGS(1)                     // 1
 * GMP_SIZE_OF_VAARGS('a', 'b')              // 2
 * GMP_SIZE_OF_VAARGS('a', 'b', 'c')         // 3
 * GMP_SIZE_OF_VAARGS('a', 'b', 1, 2)        // 4
 * GMP_SIZE_OF_VAARGS('a', 'b', 1, 2, 3, 4)  // 6
 * \endcode
 */
// #define GMP_SIZE_OF_VAARGS(...) GMP_EXPAND( GMP_GET_VARARGS(GMP_OPT_COMMA(__VA_ARGS__) __VA_ARGS__, 124, 123, 122, 121, 120, 119, 118, 117, \
//                                           116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103, \
//                                           102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, \
//                                           85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, \
//                                           67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, \
//                                           49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, \
//                                           31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, \
//                                           13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0) )
#define GMP_SIZE_OF_VAARGS(...) GMP_EXPAND( GMP_GET_VARARGS(GMP_OPT_COMMA(__VA_ARGS__) __VA_ARGS__, \
    254, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 243, 242, 241, 240, 239, 238, 237, \
    236, 235, 234, 233, 232, 231, 230, 229, 228, 227, 226, 225, 224, 223, 222, 221, 220, 219, \
    218, 217, 216, 215, 214, 213, 212, 211, 210, 209, 208, 207, 206, 205, 204, 203, 202, 201, \
    200, 199, 198, 197, 196, 195, 194, 193, 192, 191, 190, 189, 188, 187, 186, 185, 184, 183, \
    182, 181, 180, 179, 178, 177, 176, 175, 174, 173, 172, 171, 170, 169, 168, 167, 166, 165, \
    164, 163, 162, 161, 160, 159, 158, 157, 156, 155, 154, 153, 152, 151, 150, 149, 148, 147, \
    146, 145, 144, 143, 142, 141, 140, 139, 138, 137, 136, 135, 134, 133, 132, 131, 130, 129, \
    128, 127, 126, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 112, 111, \
    110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, \
    90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, \
    67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, \
    44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, \
    21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0) )


/**
 * \brief Check if variable arguments are empty.
 * 
 * This macro checks if the variable arguments are empty by expanding
 * and evaluating the arguments in various forms. It uses helper macros
 * to perform the actual checks.
 * 
 * \param ... Variable argument list
 * \return 1 if variable arguments are empty, otherwise 0.
 * 
 * \par Example
 * \code
 * GMP_IS_EMPTY()       // 1
 * GMP_IS_EMPTY(1)      // 0
 * GMP_IS_EMPTY(1, 2)   // 0
 * \endcode
 */
#define GMP_IS_EMPTY(...) \
    _GMP_IS_EMPTY_IMPL( \
        GMP_EXPAND( GMP_HAS_COMMA(__VA_ARGS__) ), \
        GMP_EXPAND( GMP_HAS_COMMA(_TRIGGER_PARENTHESIS __VA_ARGS__) ), \
        GMP_EXPAND( GMP_HAS_COMMA(__VA_ARGS__ ()) ), \
        GMP_EXPAND( GMP_HAS_COMMA(_TRIGGER_PARENTHESIS __VA_ARGS__ ()) ) \
    )
#define _GMP_IS_EMPTY_IMPL(_0, _1, _2, _3) GMP_HAS_COMMA(_GMP_IS_EMPTY_CASE(_0, _1, _2, _3))
#define _GMP_IS_EMPTY_CASE(_0, _1, _2, _3) _GMP_IS_EMPTY_CASE_ ## _0 ## _1 ## _2 ## _3
#define _GMP_IS_EMPTY_CASE_0001 ,


/**
 * \def GMP_HAS_COMMA(...)
 * \brief Check if the variable argument list contains a comma.
 *
 * This macro checks if the variable argument list contains a comma.
 * It expands the arguments and uses the \ref _GMP_COMMA_CHECK macro
 * to perform the actual check.
 *
 * \param ... Variable argument list.
 * \return 1 if a comma is found, otherwise 0.
 */
#define GMP_HAS_COMMA(...) GMP_EXPAND( _GMP_COMMA_CHECK(__VA_ARGS__, \
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0) )
// #define _GMP_COMMA_CHECK(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
//                         _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
//                         _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, \
//                         _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, \
//                         _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, _92, _93, _94, _95, _96, _97, _98, _99, _100, \
//                         _101, _102, _103, _104, _105, _106, _107, _108, _109, _110, _111, _112, _113, _114, _115, _116, _117, _118, _119, _120, \
//                         _121, _122, _123, _124, R, ...) R
#define _GMP_COMMA_CHECK( \
    _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, \
    _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, \
    _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, \
    _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, \
    _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, \
    _92, _93, _94, _95, _96, _97, _98, _99, _100, _101, _102, _103, _104, _105, _106, _107, _108, \
    _109, _110, _111, _112, _113, _114, _115, _116, _117, _118, _119, _120, _121, _122, _123, _124, \
    _125, _126, _127, _128, _129, _130, _131, _132, _133, _134, _135, _136, _137, _138, _139, _140, \
    _141, _142, _143, _144, _145, _146, _147, _148, _149, _150, _151, _152, _153, _154, _155, _156, \
    _157, _158, _159, _160, _161, _162, _163, _164, _165, _166, _167, _168, _169, _170, _171, _172, \
    _173, _174, _175, _176, _177, _178, _179, _180, _181, _182, _183, _184, _185, _186, _187, _188, \
    _189, _190, _191, _192, _193, _194, _195, _196, _197, _198, _199, _200, _201, _202, _203, _204, \
    _205, _206, _207, _208, _209, _210, _211, _212, _213, _214, _215, _216, _217, _218, _219, _220, \
    _221, _222, _223, _224, _225, _226, _227, _228, _229, _230, _231, _232, _233, _234, _235, _236, \
    _237, _238, _239, _240, _241, _242, _243, _244, _245, _246, _247, _248, _249, _250, _251, _252, \
    _253, _254, R, ...) R
#define _TRIGGER_PARENTHESIS(...) ,


/**
 * \def GMP_OPT_COMMA(...)
 * \brief Optional comma based on argument emptiness.
 *
 * This macro adds a comma if the arguments are empty, otherwise
 * it does not add a comma.
 *
 * \param ... Variable argument list.
 * \return Comma if arguments are empty, otherwise nothing.
 */
#define GMP_OPT_COMMA(...) GMP_CONCAT(_GMP_OPT_COMMA_, GMP_IS_EMPTY(__VA_ARGS__))
#define _GMP_OPT_COMMA_1
#define _GMP_OPT_COMMA_0 ,


/**
 * \def GMP_OVERLOAD_INVOKE(call, ...)
 * \brief Call an overloaded macro based on the special version.
 *
 * This macro allows for the invocation of different versions of a macro
 * depending on the version provided. It works by concatenating
 * the base call name with the version argument, and then invoking the
 * appropriate overloaded macro.
 *
 * Example usage:
 * \code
 * #define TEST_1(x) printf("One argument: %c\n", (x))
 * #define TEST_1_1(x, y) printf("Two arguments: %c, %c\n", (x), (y))
 * 
 * GMP_OVERLOAD_INVOKE(TEST, 1)('a');         // Expands to: TEST_1('a')
 * GMP_OVERLOAD_INVOKE(TEST, 1, 1)('a', 'b'); // Expands to: TEST_1_1('a', 'b')
 * \endcode
 *
 * \param call The base macro to be called.
 * \param ... The arguments to be passed to the macro. The arguments
 *            determine which overloaded version of the macro is invoked.
 */
#define GMP_OVERLOAD_INVOKE(call, ...) GMP_CONCAT( _GMP_OVERLOAD_INVOKE_, GMP_SIZE_OF_VAARGS(__VA_ARGS__) )(call, __VA_ARGS__)
#define _GMP_OVERLOAD_INVOKE_1(call, v1) GMP_CONCAT(GMP_CONCAT(call, _), v1)
#define _GMP_OVERLOAD_INVOKE_2(call, v1, v2) GMP_CONCAT( GMP_CONCAT(_GMP_OVERLOAD_INVOKE_1(call, v1), _), v2 )
#define _GMP_OVERLOAD_INVOKE_3(call, v1, v2, v3) GMP_CONCAT( GMP_CONCAT(_GMP_OVERLOAD_INVOKE_2(call, v1, v2), _), v3)
#define _GMP_OVERLOAD_INVOKE_4(call, v1, v2, v3, v4) GMP_CONCAT( GMP_CONCAT(_GMP_OVERLOAD_INVOKE_3(call, v1, v2, v3), _), v4)
#define _GMP_OVERLOAD_INVOKE_5(call, v1, v2, v3, v4, v5) GMP_CONCAT( GMP_CONCAT(_GMP_OVERLOAD_INVOKE_4(call, v1, v2, v3, v4), _), v5)


/**
 * \def GMP_FOR_EACH(call, ...)
 * \brief Call a macro for each argument provided.
 *
 * This macro allows for the invocation of a given macro on each argument
 * in a list of arguments. It expands to a series of calls to the provided
 * macro, one for each argument.
 *
 * Example usage:
 * \code
 * #define DECLARE_VARIABLES(num) int variable_ ## num;
 * GMP_FOR_EACH(DECLARE_VARIABLES, 1, 2) // Expands to: int variable_1; int variable_2;
 * \endcode
 *
 * \param call The macro to be called for each argument.
 * \param ... The list of arguments to be passed to the macro.
 */
#define GMP_FOR_EACH(call, ...) \
    GMP_EXPAND( GMP_OVERLOAD_INVOKE(_GMP_FOR_EACH, GMP_SIZE_OF_VAARGS(__VA_ARGS__))(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_0(call, ...)
#define _GMP_FOR_EACH_1(call, x) call(x)
#define _GMP_FOR_EACH_2(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_1(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_3(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_2(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_4(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_3(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_5(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_4(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_6(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_5(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_7(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_6(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_8(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_7(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_9(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_8(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_10(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_9(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_11(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_10(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_12(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_11(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_13(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_12(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_14(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_13(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_15(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_14(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_16(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_15(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_17(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_16(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_18(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_17(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_19(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_18(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_20(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_19(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_21(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_20(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_22(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_21(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_23(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_22(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_24(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_23(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_25(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_24(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_26(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_25(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_27(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_26(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_28(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_27(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_29(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_28(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_30(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_29(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_31(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_30(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_32(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_31(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_33(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_32(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_34(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_33(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_35(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_34(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_36(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_35(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_37(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_36(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_38(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_37(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_39(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_38(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_40(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_39(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_41(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_40(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_42(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_41(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_43(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_42(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_44(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_43(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_45(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_44(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_46(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_45(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_47(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_46(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_48(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_47(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_49(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_48(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_50(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_49(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_51(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_50(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_52(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_51(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_53(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_52(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_54(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_53(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_55(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_54(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_56(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_55(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_57(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_56(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_58(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_57(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_59(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_58(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_60(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_59(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_61(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_60(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_62(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_61(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_63(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_62(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_64(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_63(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_65(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_64(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_66(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_65(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_67(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_66(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_68(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_67(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_69(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_68(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_70(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_69(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_71(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_70(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_72(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_71(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_73(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_72(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_74(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_73(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_75(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_74(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_76(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_75(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_77(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_76(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_78(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_77(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_79(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_78(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_80(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_79(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_81(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_80(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_82(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_81(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_83(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_82(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_84(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_83(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_85(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_84(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_86(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_85(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_87(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_86(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_88(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_87(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_89(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_88(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_90(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_89(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_91(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_90(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_92(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_91(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_93(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_92(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_94(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_93(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_95(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_94(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_96(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_95(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_97(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_96(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_98(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_97(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_99(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_98(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_100(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_99(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_101(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_100(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_102(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_101(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_103(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_102(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_104(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_103(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_105(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_104(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_106(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_105(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_107(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_106(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_108(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_107(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_109(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_108(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_110(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_109(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_111(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_110(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_112(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_111(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_113(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_112(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_114(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_113(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_115(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_114(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_116(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_115(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_117(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_116(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_118(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_117(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_119(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_118(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_120(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_119(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_121(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_120(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_122(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_121(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_123(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_122(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_124(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_123(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_125(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_124(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_126(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_125(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_127(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_126(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_128(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_127(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_129(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_128(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_130(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_129(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_131(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_130(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_132(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_131(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_133(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_132(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_134(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_133(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_135(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_134(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_136(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_135(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_137(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_136(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_138(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_137(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_139(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_138(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_140(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_139(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_141(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_140(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_142(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_141(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_143(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_142(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_144(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_143(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_145(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_144(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_146(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_145(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_147(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_146(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_148(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_147(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_149(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_148(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_150(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_149(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_151(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_150(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_152(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_151(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_153(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_152(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_154(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_153(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_155(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_154(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_156(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_155(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_157(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_156(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_158(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_157(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_159(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_158(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_160(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_159(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_161(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_160(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_162(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_161(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_163(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_162(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_164(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_163(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_165(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_164(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_166(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_165(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_167(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_166(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_168(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_167(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_169(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_168(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_170(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_169(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_171(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_170(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_172(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_171(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_173(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_172(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_174(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_173(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_175(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_174(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_176(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_175(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_177(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_176(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_178(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_177(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_179(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_178(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_180(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_179(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_181(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_180(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_182(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_181(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_183(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_182(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_184(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_183(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_185(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_184(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_186(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_185(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_187(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_186(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_188(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_187(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_189(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_188(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_190(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_189(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_191(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_190(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_192(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_191(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_193(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_192(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_194(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_193(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_195(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_194(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_196(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_195(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_197(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_196(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_198(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_197(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_199(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_198(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_200(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_199(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_201(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_200(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_202(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_201(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_203(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_202(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_204(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_203(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_205(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_204(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_206(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_205(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_207(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_206(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_208(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_207(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_209(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_208(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_210(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_209(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_211(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_210(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_212(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_211(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_213(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_212(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_214(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_213(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_215(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_214(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_216(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_215(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_217(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_216(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_218(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_217(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_219(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_218(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_220(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_219(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_221(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_220(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_222(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_221(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_223(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_222(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_224(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_223(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_225(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_224(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_226(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_225(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_227(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_226(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_228(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_227(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_229(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_228(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_230(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_229(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_231(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_230(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_232(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_231(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_233(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_232(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_234(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_233(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_235(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_234(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_236(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_235(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_237(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_236(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_238(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_237(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_239(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_238(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_240(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_239(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_241(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_240(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_242(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_241(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_243(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_242(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_244(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_243(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_245(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_244(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_246(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_245(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_247(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_246(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_248(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_247(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_249(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_248(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_250(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_249(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_251(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_250(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_252(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_251(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_253(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_252(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_254(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_253(call, __VA_ARGS__) )
#define _GMP_FOR_EACH_255(call, x, ...) call(x) GMP_EXPAND( _GMP_FOR_EACH_254(call, __VA_ARGS__) )

/**
 * \def GMP_INC(value)
 * \brief Increment a value by 1.
 * 
 * This macro uses overload invocation to increment a value by 1.
 * It relies on specific macro definitions for each value.
 * 
 * \param value The value to increment.
 * \return The incremented value.
 */
#define GMP_INC(value) GMP_OVERLOAD_INVOKE(_GMP_INC, value)()
#define _GMP_INC_0() 1
#define _GMP_INC_1() 2
#define _GMP_INC_2() 3
#define _GMP_INC_3() 4
#define _GMP_INC_4() 5
#define _GMP_INC_5() 6
#define _GMP_INC_6() 7
#define _GMP_INC_7() 8
#define _GMP_INC_8() 9
#define _GMP_INC_9() 10
#define _GMP_INC_10() 11
#define _GMP_INC_11() 12
#define _GMP_INC_12() 13
#define _GMP_INC_13() 14
#define _GMP_INC_14() 15
#define _GMP_INC_15() 16
#define _GMP_INC_16() 17
#define _GMP_INC_17() 18
#define _GMP_INC_18() 19
#define _GMP_INC_19() 20
#define _GMP_INC_20() 21
#define _GMP_INC_21() 22
#define _GMP_INC_22() 23
#define _GMP_INC_23() 24
#define _GMP_INC_24() 25
#define _GMP_INC_25() 26
#define _GMP_INC_26() 27
#define _GMP_INC_27() 28
#define _GMP_INC_28() 29
#define _GMP_INC_29() 30
#define _GMP_INC_30() 31
#define _GMP_INC_31() 32
#define _GMP_INC_32() 33
#define _GMP_INC_33() 34
#define _GMP_INC_34() 35
#define _GMP_INC_35() 36
#define _GMP_INC_36() 37
#define _GMP_INC_37() 38
#define _GMP_INC_38() 39
#define _GMP_INC_39() 40
#define _GMP_INC_40() 41
#define _GMP_INC_41() 42
#define _GMP_INC_42() 43
#define _GMP_INC_43() 44
#define _GMP_INC_44() 45
#define _GMP_INC_45() 46
#define _GMP_INC_46() 47
#define _GMP_INC_47() 48
#define _GMP_INC_48() 49
#define _GMP_INC_49() 50
#define _GMP_INC_50() 51
#define _GMP_INC_51() 52
#define _GMP_INC_52() 53
#define _GMP_INC_53() 54
#define _GMP_INC_54() 55
#define _GMP_INC_55() 56
#define _GMP_INC_56() 57
#define _GMP_INC_57() 58
#define _GMP_INC_58() 59
#define _GMP_INC_59() 60
#define _GMP_INC_60() 61
#define _GMP_INC_61() 62
#define _GMP_INC_62() 63
#define _GMP_INC_63() 64
#define _GMP_INC_64() 65
#define _GMP_INC_65() 66
#define _GMP_INC_66() 67
#define _GMP_INC_67() 68
#define _GMP_INC_68() 69
#define _GMP_INC_69() 70
#define _GMP_INC_70() 71
#define _GMP_INC_71() 72
#define _GMP_INC_72() 73
#define _GMP_INC_73() 74
#define _GMP_INC_74() 75
#define _GMP_INC_75() 76
#define _GMP_INC_76() 77
#define _GMP_INC_77() 78
#define _GMP_INC_78() 79
#define _GMP_INC_79() 80
#define _GMP_INC_80() 81
#define _GMP_INC_81() 82
#define _GMP_INC_82() 83
#define _GMP_INC_83() 84
#define _GMP_INC_84() 85
#define _GMP_INC_85() 86
#define _GMP_INC_86() 87
#define _GMP_INC_87() 88
#define _GMP_INC_88() 89
#define _GMP_INC_89() 90
#define _GMP_INC_90() 91
#define _GMP_INC_91() 92
#define _GMP_INC_92() 93
#define _GMP_INC_93() 94
#define _GMP_INC_94() 95
#define _GMP_INC_95() 96
#define _GMP_INC_96() 97
#define _GMP_INC_97() 98
#define _GMP_INC_98() 99
#define _GMP_INC_99() 100
#define _GMP_INC_100() 101
#define _GMP_INC_101() 102
#define _GMP_INC_102() 103
#define _GMP_INC_103() 104
#define _GMP_INC_104() 105
#define _GMP_INC_105() 106
#define _GMP_INC_106() 107
#define _GMP_INC_107() 108
#define _GMP_INC_108() 109
#define _GMP_INC_109() 110
#define _GMP_INC_110() 111
#define _GMP_INC_111() 112
#define _GMP_INC_112() 113
#define _GMP_INC_113() 114
#define _GMP_INC_114() 115
#define _GMP_INC_115() 116
#define _GMP_INC_116() 117
#define _GMP_INC_117() 118
#define _GMP_INC_118() 119
#define _GMP_INC_119() 120
#define _GMP_INC_120() 121
#define _GMP_INC_121() 122
#define _GMP_INC_122() 123
#define _GMP_INC_123() 124
#define _GMP_INC_124() 125
#define _GMP_INC_125() 126
#define _GMP_INC_126() 127
#define _GMP_INC_127() 128
#define _GMP_INC_128() 129
#define _GMP_INC_129() 130
#define _GMP_INC_130() 131
#define _GMP_INC_131() 132
#define _GMP_INC_132() 133
#define _GMP_INC_133() 134
#define _GMP_INC_134() 135
#define _GMP_INC_135() 136
#define _GMP_INC_136() 137
#define _GMP_INC_137() 138
#define _GMP_INC_138() 139
#define _GMP_INC_139() 140
#define _GMP_INC_140() 141
#define _GMP_INC_141() 142
#define _GMP_INC_142() 143
#define _GMP_INC_143() 144
#define _GMP_INC_144() 145
#define _GMP_INC_145() 146
#define _GMP_INC_146() 147
#define _GMP_INC_147() 148
#define _GMP_INC_148() 149
#define _GMP_INC_149() 150
#define _GMP_INC_150() 151
#define _GMP_INC_151() 152
#define _GMP_INC_152() 153
#define _GMP_INC_153() 154
#define _GMP_INC_154() 155
#define _GMP_INC_155() 156
#define _GMP_INC_156() 157
#define _GMP_INC_157() 158
#define _GMP_INC_158() 159
#define _GMP_INC_159() 160
#define _GMP_INC_160() 161
#define _GMP_INC_161() 162
#define _GMP_INC_162() 163
#define _GMP_INC_163() 164
#define _GMP_INC_164() 165
#define _GMP_INC_165() 166
#define _GMP_INC_166() 167
#define _GMP_INC_167() 168
#define _GMP_INC_168() 169
#define _GMP_INC_169() 170
#define _GMP_INC_170() 171
#define _GMP_INC_171() 172
#define _GMP_INC_172() 173
#define _GMP_INC_173() 174
#define _GMP_INC_174() 175
#define _GMP_INC_175() 176
#define _GMP_INC_176() 177
#define _GMP_INC_177() 178
#define _GMP_INC_178() 179
#define _GMP_INC_179() 180
#define _GMP_INC_180() 181
#define _GMP_INC_181() 182
#define _GMP_INC_182() 183
#define _GMP_INC_183() 184
#define _GMP_INC_184() 185
#define _GMP_INC_185() 186
#define _GMP_INC_186() 187
#define _GMP_INC_187() 188
#define _GMP_INC_188() 189
#define _GMP_INC_189() 190
#define _GMP_INC_190() 191
#define _GMP_INC_191() 192
#define _GMP_INC_192() 193
#define _GMP_INC_193() 194
#define _GMP_INC_194() 195
#define _GMP_INC_195() 196
#define _GMP_INC_196() 197
#define _GMP_INC_197() 198
#define _GMP_INC_198() 199
#define _GMP_INC_199() 200
#define _GMP_INC_200() 201
#define _GMP_INC_201() 202
#define _GMP_INC_202() 203
#define _GMP_INC_203() 204
#define _GMP_INC_204() 205
#define _GMP_INC_205() 206
#define _GMP_INC_206() 207
#define _GMP_INC_207() 208
#define _GMP_INC_208() 209
#define _GMP_INC_209() 210
#define _GMP_INC_210() 211
#define _GMP_INC_211() 212
#define _GMP_INC_212() 213
#define _GMP_INC_213() 214
#define _GMP_INC_214() 215
#define _GMP_INC_215() 216
#define _GMP_INC_216() 217
#define _GMP_INC_217() 218
#define _GMP_INC_218() 219
#define _GMP_INC_219() 220
#define _GMP_INC_220() 221
#define _GMP_INC_221() 222
#define _GMP_INC_222() 223
#define _GMP_INC_223() 224
#define _GMP_INC_224() 225
#define _GMP_INC_225() 226
#define _GMP_INC_226() 227
#define _GMP_INC_227() 228
#define _GMP_INC_228() 229
#define _GMP_INC_229() 230
#define _GMP_INC_230() 231
#define _GMP_INC_231() 232
#define _GMP_INC_232() 233
#define _GMP_INC_233() 234
#define _GMP_INC_234() 235
#define _GMP_INC_235() 236
#define _GMP_INC_236() 237
#define _GMP_INC_237() 238
#define _GMP_INC_238() 239
#define _GMP_INC_239() 240
#define _GMP_INC_240() 241
#define _GMP_INC_241() 242
#define _GMP_INC_242() 243
#define _GMP_INC_243() 244
#define _GMP_INC_244() 245
#define _GMP_INC_245() 246
#define _GMP_INC_246() 247
#define _GMP_INC_247() 248
#define _GMP_INC_248() 249
#define _GMP_INC_249() 250
#define _GMP_INC_250() 251
#define _GMP_INC_251() 252
#define _GMP_INC_252() 253
#define _GMP_INC_253() 254
#define _GMP_INC_254() 255
#define _GMP_INC_255() 256


/**
 * \def GMP_DEC(value)
 * \brief Decrement a value by 1.
 * 
 * This macro uses overload invocation to decrement a value by 1.
 * It relies on specific macro definitions for each value.
 * 
 * \param value The value to decrement.
 * \return The decremented value.
 */
#define GMP_DEC(value) GMP_OVERLOAD_INVOKE(_GMP_DEC, value)()
#define _GMP_DEC_1() 0
#define _GMP_DEC_2() 1
#define _GMP_DEC_3() 2
#define _GMP_DEC_4() 3
#define _GMP_DEC_5() 4
#define _GMP_DEC_6() 5
#define _GMP_DEC_7() 6
#define _GMP_DEC_8() 7
#define _GMP_DEC_9() 8
#define _GMP_DEC_10() 9
#define _GMP_DEC_11() 10
#define _GMP_DEC_12() 11
#define _GMP_DEC_13() 12
#define _GMP_DEC_14() 13
#define _GMP_DEC_15() 14
#define _GMP_DEC_16() 15
#define _GMP_DEC_17() 16
#define _GMP_DEC_18() 17
#define _GMP_DEC_19() 18
#define _GMP_DEC_20() 19
#define _GMP_DEC_21() 20
#define _GMP_DEC_22() 21
#define _GMP_DEC_23() 22
#define _GMP_DEC_24() 23
#define _GMP_DEC_25() 24
#define _GMP_DEC_26() 25
#define _GMP_DEC_27() 26
#define _GMP_DEC_28() 27
#define _GMP_DEC_29() 28
#define _GMP_DEC_30() 29
#define _GMP_DEC_31() 30
#define _GMP_DEC_32() 31
#define _GMP_DEC_33() 32
#define _GMP_DEC_34() 33
#define _GMP_DEC_35() 34
#define _GMP_DEC_36() 35
#define _GMP_DEC_37() 36
#define _GMP_DEC_38() 37
#define _GMP_DEC_39() 38
#define _GMP_DEC_40() 39
#define _GMP_DEC_41() 40
#define _GMP_DEC_42() 41
#define _GMP_DEC_43() 42
#define _GMP_DEC_44() 43
#define _GMP_DEC_45() 44
#define _GMP_DEC_46() 45
#define _GMP_DEC_47() 46
#define _GMP_DEC_48() 47
#define _GMP_DEC_49() 48
#define _GMP_DEC_50() 49
#define _GMP_DEC_51() 50
#define _GMP_DEC_52() 51
#define _GMP_DEC_53() 52
#define _GMP_DEC_54() 53
#define _GMP_DEC_55() 54
#define _GMP_DEC_56() 55
#define _GMP_DEC_57() 56
#define _GMP_DEC_58() 57
#define _GMP_DEC_59() 58
#define _GMP_DEC_60() 59
#define _GMP_DEC_61() 60
#define _GMP_DEC_62() 61
#define _GMP_DEC_63() 62
#define _GMP_DEC_64() 63
#define _GMP_DEC_65() 64
#define _GMP_DEC_66() 65
#define _GMP_DEC_67() 66
#define _GMP_DEC_68() 67
#define _GMP_DEC_69() 68
#define _GMP_DEC_70() 69
#define _GMP_DEC_71() 70
#define _GMP_DEC_72() 71
#define _GMP_DEC_73() 72
#define _GMP_DEC_74() 73
#define _GMP_DEC_75() 74
#define _GMP_DEC_76() 75
#define _GMP_DEC_77() 76
#define _GMP_DEC_78() 77
#define _GMP_DEC_79() 78
#define _GMP_DEC_80() 79
#define _GMP_DEC_81() 80
#define _GMP_DEC_82() 81
#define _GMP_DEC_83() 82
#define _GMP_DEC_84() 83
#define _GMP_DEC_85() 84
#define _GMP_DEC_86() 85
#define _GMP_DEC_87() 86
#define _GMP_DEC_88() 87
#define _GMP_DEC_89() 88
#define _GMP_DEC_90() 89
#define _GMP_DEC_91() 90
#define _GMP_DEC_92() 91
#define _GMP_DEC_93() 92
#define _GMP_DEC_94() 93
#define _GMP_DEC_95() 94
#define _GMP_DEC_96() 95
#define _GMP_DEC_97() 96
#define _GMP_DEC_98() 97
#define _GMP_DEC_99() 98
#define _GMP_DEC_100() 99
#define _GMP_DEC_101() 100
#define _GMP_DEC_102() 101
#define _GMP_DEC_103() 102
#define _GMP_DEC_104() 103
#define _GMP_DEC_105() 104
#define _GMP_DEC_106() 105
#define _GMP_DEC_107() 106
#define _GMP_DEC_108() 107
#define _GMP_DEC_109() 108
#define _GMP_DEC_110() 109
#define _GMP_DEC_111() 110
#define _GMP_DEC_112() 111
#define _GMP_DEC_113() 112
#define _GMP_DEC_114() 113
#define _GMP_DEC_115() 114
#define _GMP_DEC_116() 115
#define _GMP_DEC_117() 116
#define _GMP_DEC_118() 117
#define _GMP_DEC_119() 118
#define _GMP_DEC_120() 119
#define _GMP_DEC_121() 120
#define _GMP_DEC_122() 121
#define _GMP_DEC_123() 122
#define _GMP_DEC_124() 123
#define _GMP_DEC_125() 124
#define _GMP_DEC_126() 125
#define _GMP_DEC_127() 126
#define _GMP_DEC_128() 127
#define _GMP_DEC_129() 128
#define _GMP_DEC_130() 129
#define _GMP_DEC_131() 130
#define _GMP_DEC_132() 131
#define _GMP_DEC_133() 132
#define _GMP_DEC_134() 133
#define _GMP_DEC_135() 134
#define _GMP_DEC_136() 135
#define _GMP_DEC_137() 136
#define _GMP_DEC_138() 137
#define _GMP_DEC_139() 138
#define _GMP_DEC_140() 139
#define _GMP_DEC_141() 140
#define _GMP_DEC_142() 141
#define _GMP_DEC_143() 142
#define _GMP_DEC_144() 143
#define _GMP_DEC_145() 144
#define _GMP_DEC_146() 145
#define _GMP_DEC_147() 146
#define _GMP_DEC_148() 147
#define _GMP_DEC_149() 148
#define _GMP_DEC_150() 149
#define _GMP_DEC_151() 150
#define _GMP_DEC_152() 151
#define _GMP_DEC_153() 152
#define _GMP_DEC_154() 153
#define _GMP_DEC_155() 154
#define _GMP_DEC_156() 155
#define _GMP_DEC_157() 156
#define _GMP_DEC_158() 157
#define _GMP_DEC_159() 158
#define _GMP_DEC_160() 159
#define _GMP_DEC_161() 160
#define _GMP_DEC_162() 161
#define _GMP_DEC_163() 162
#define _GMP_DEC_164() 163
#define _GMP_DEC_165() 164
#define _GMP_DEC_166() 165
#define _GMP_DEC_167() 166
#define _GMP_DEC_168() 167
#define _GMP_DEC_169() 168
#define _GMP_DEC_170() 169
#define _GMP_DEC_171() 170
#define _GMP_DEC_172() 171
#define _GMP_DEC_173() 172
#define _GMP_DEC_174() 173
#define _GMP_DEC_175() 174
#define _GMP_DEC_176() 175
#define _GMP_DEC_177() 176
#define _GMP_DEC_178() 177
#define _GMP_DEC_179() 178
#define _GMP_DEC_180() 179
#define _GMP_DEC_181() 180
#define _GMP_DEC_182() 181
#define _GMP_DEC_183() 182
#define _GMP_DEC_184() 183
#define _GMP_DEC_185() 184
#define _GMP_DEC_186() 185
#define _GMP_DEC_187() 186
#define _GMP_DEC_188() 187
#define _GMP_DEC_189() 188
#define _GMP_DEC_190() 189
#define _GMP_DEC_191() 190
#define _GMP_DEC_192() 191
#define _GMP_DEC_193() 192
#define _GMP_DEC_194() 193
#define _GMP_DEC_195() 194
#define _GMP_DEC_196() 195
#define _GMP_DEC_197() 196
#define _GMP_DEC_198() 197
#define _GMP_DEC_199() 198
#define _GMP_DEC_200() 199
#define _GMP_DEC_201() 200
#define _GMP_DEC_202() 201
#define _GMP_DEC_203() 202
#define _GMP_DEC_204() 203
#define _GMP_DEC_205() 204
#define _GMP_DEC_206() 205
#define _GMP_DEC_207() 206
#define _GMP_DEC_208() 207
#define _GMP_DEC_209() 208
#define _GMP_DEC_210() 209
#define _GMP_DEC_211() 210
#define _GMP_DEC_212() 211
#define _GMP_DEC_213() 212
#define _GMP_DEC_214() 213
#define _GMP_DEC_215() 214
#define _GMP_DEC_216() 215
#define _GMP_DEC_217() 216
#define _GMP_DEC_218() 217
#define _GMP_DEC_219() 218
#define _GMP_DEC_220() 219
#define _GMP_DEC_221() 220
#define _GMP_DEC_222() 221
#define _GMP_DEC_223() 222
#define _GMP_DEC_224() 223
#define _GMP_DEC_225() 224
#define _GMP_DEC_226() 225
#define _GMP_DEC_227() 226
#define _GMP_DEC_228() 227
#define _GMP_DEC_229() 228
#define _GMP_DEC_230() 229
#define _GMP_DEC_231() 230
#define _GMP_DEC_232() 231
#define _GMP_DEC_233() 232
#define _GMP_DEC_234() 233
#define _GMP_DEC_235() 234
#define _GMP_DEC_236() 235
#define _GMP_DEC_237() 236
#define _GMP_DEC_238() 237
#define _GMP_DEC_239() 238
#define _GMP_DEC_240() 239
#define _GMP_DEC_241() 240
#define _GMP_DEC_242() 241
#define _GMP_DEC_243() 242
#define _GMP_DEC_244() 243
#define _GMP_DEC_245() 244
#define _GMP_DEC_246() 245
#define _GMP_DEC_247() 246
#define _GMP_DEC_248() 247
#define _GMP_DEC_249() 248
#define _GMP_DEC_250() 249
#define _GMP_DEC_251() 250
#define _GMP_DEC_252() 251
#define _GMP_DEC_253() 252
#define _GMP_DEC_254() 253
#define _GMP_DEC_255() 254

/**
 * \def GMP_NOT(value)
 * \brief Macro to perform logical NOT operation on a value.
 * 
 * This macro uses overload invocation to perform a logical NOT operation.
 * It relies on specific macro definitions for each value.
 * 
 * \param value The value to perform logical NOT on.
 * \return 1 if the value is 0, 0 otherwise.
 */
#define GMP_NOT(value) GMP_OVERLOAD_INVOKE(_GMP_NOT, value)
#define _GMP_NOT_0 1
#define _GMP_NOT_1 0

/**
 * \brief Macro to perform logical AND operation between two values.
 * 
 * This macro uses overload invocation to perform a logical AND operation.
 * It relies on specific macro definitions for each combination of values.
 * 
 * \param a The first operand (0 or 1).
 * \param b The second operand (0 or 1).
 * \return 1 if both operands are 1, 0 otherwise.
 */
#define GMP_AND(a, b) GMP_OVERLOAD_INVOKE(_GMP_AND, a, b)
#define _GMP_AND_0_0 0
#define _GMP_AND_0_1 0
#define _GMP_AND_1_0 0
#define _GMP_AND_1_1 1

/**
 * \brief Macro to convert a value to a boolean representation.
 * 
 * This macro uses overload invocation to convert a value to its boolean representation.
 * It relies on specific macro definitions for each value.
 * 
 * \param value The value to convert (0 or non-zero).
 * \return 0 if the value is 0, 1 otherwise.
 */
#define GMP_BOOL(value) GMP_OVERLOAD_INVOKE(_GMP_BOOL, value)
#define _GMP_BOOL_0 0
#define _GMP_BOOL_1() 1
#define _GMP_BOOL_2() 1
#define _GMP_BOOL_3() 1
#define _GMP_BOOL_4() 1
#define _GMP_BOOL_5() 1
#define _GMP_BOOL_6() 1
#define _GMP_BOOL_7() 1
#define _GMP_BOOL_8() 1
#define _GMP_BOOL_9() 1
#define _GMP_BOOL_10() 1
#define _GMP_BOOL_11() 1
#define _GMP_BOOL_12() 1
#define _GMP_BOOL_13() 1
#define _GMP_BOOL_14() 1
#define _GMP_BOOL_15() 1
#define _GMP_BOOL_16() 1
#define _GMP_BOOL_17() 1
#define _GMP_BOOL_18() 1
#define _GMP_BOOL_19() 1
#define _GMP_BOOL_20() 1
#define _GMP_BOOL_21() 1
#define _GMP_BOOL_22() 1
#define _GMP_BOOL_23() 1
#define _GMP_BOOL_24() 1
#define _GMP_BOOL_25() 1
#define _GMP_BOOL_26() 1
#define _GMP_BOOL_27() 1
#define _GMP_BOOL_28() 1
#define _GMP_BOOL_29() 1
#define _GMP_BOOL_30() 1
#define _GMP_BOOL_31() 1
#define _GMP_BOOL_32() 1
#define _GMP_BOOL_33() 1
#define _GMP_BOOL_34() 1
#define _GMP_BOOL_35() 1
#define _GMP_BOOL_36() 1
#define _GMP_BOOL_37() 1
#define _GMP_BOOL_38() 1
#define _GMP_BOOL_39() 1
#define _GMP_BOOL_40() 1
#define _GMP_BOOL_41() 1
#define _GMP_BOOL_42() 1
#define _GMP_BOOL_43() 1
#define _GMP_BOOL_44() 1
#define _GMP_BOOL_45() 1
#define _GMP_BOOL_46() 1
#define _GMP_BOOL_47() 1
#define _GMP_BOOL_48() 1
#define _GMP_BOOL_49() 1
#define _GMP_BOOL_50() 1
#define _GMP_BOOL_51() 1
#define _GMP_BOOL_52() 1
#define _GMP_BOOL_53() 1
#define _GMP_BOOL_54() 1
#define _GMP_BOOL_55() 1
#define _GMP_BOOL_56() 1
#define _GMP_BOOL_57() 1
#define _GMP_BOOL_58() 1
#define _GMP_BOOL_59() 1
#define _GMP_BOOL_60() 1
#define _GMP_BOOL_61() 1
#define _GMP_BOOL_62() 1
#define _GMP_BOOL_63() 1
#define _GMP_BOOL_64() 1
#define _GMP_BOOL_65() 1
#define _GMP_BOOL_66() 1
#define _GMP_BOOL_67() 1
#define _GMP_BOOL_68() 1
#define _GMP_BOOL_69() 1
#define _GMP_BOOL_70() 1
#define _GMP_BOOL_71() 1
#define _GMP_BOOL_72() 1
#define _GMP_BOOL_73() 1
#define _GMP_BOOL_74() 1
#define _GMP_BOOL_75() 1
#define _GMP_BOOL_76() 1
#define _GMP_BOOL_77() 1
#define _GMP_BOOL_78() 1
#define _GMP_BOOL_79() 1
#define _GMP_BOOL_80() 1
#define _GMP_BOOL_81() 1
#define _GMP_BOOL_82() 1
#define _GMP_BOOL_83() 1
#define _GMP_BOOL_84() 1
#define _GMP_BOOL_85() 1
#define _GMP_BOOL_86() 1
#define _GMP_BOOL_87() 1
#define _GMP_BOOL_88() 1
#define _GMP_BOOL_89() 1
#define _GMP_BOOL_90() 1
#define _GMP_BOOL_91() 1
#define _GMP_BOOL_92() 1
#define _GMP_BOOL_93() 1
#define _GMP_BOOL_94() 1
#define _GMP_BOOL_95() 1
#define _GMP_BOOL_96() 1
#define _GMP_BOOL_97() 1
#define _GMP_BOOL_98() 1
#define _GMP_BOOL_99() 1
#define _GMP_BOOL_100() 1
#define _GMP_BOOL_101() 1
#define _GMP_BOOL_102() 1
#define _GMP_BOOL_103() 1
#define _GMP_BOOL_104() 1
#define _GMP_BOOL_105() 1
#define _GMP_BOOL_106() 1
#define _GMP_BOOL_107() 1
#define _GMP_BOOL_108() 1
#define _GMP_BOOL_109() 1
#define _GMP_BOOL_110() 1
#define _GMP_BOOL_111() 1
#define _GMP_BOOL_112() 1
#define _GMP_BOOL_113() 1
#define _GMP_BOOL_114() 1
#define _GMP_BOOL_115() 1
#define _GMP_BOOL_116() 1
#define _GMP_BOOL_117() 1
#define _GMP_BOOL_118() 1
#define _GMP_BOOL_119() 1
#define _GMP_BOOL_120() 1
#define _GMP_BOOL_121() 1
#define _GMP_BOOL_122() 1
#define _GMP_BOOL_123() 1
#define _GMP_BOOL_124() 1
#define _GMP_BOOL_125() 1
#define _GMP_BOOL_126() 1
#define _GMP_BOOL_127() 1
#define _GMP_BOOL_128() 1
#define _GMP_BOOL_129() 1
#define _GMP_BOOL_130() 1
#define _GMP_BOOL_131() 1
#define _GMP_BOOL_132() 1
#define _GMP_BOOL_133() 1
#define _GMP_BOOL_134() 1
#define _GMP_BOOL_135() 1
#define _GMP_BOOL_136() 1
#define _GMP_BOOL_137() 1
#define _GMP_BOOL_138() 1
#define _GMP_BOOL_139() 1
#define _GMP_BOOL_140() 1
#define _GMP_BOOL_141() 1
#define _GMP_BOOL_142() 1
#define _GMP_BOOL_143() 1
#define _GMP_BOOL_144() 1
#define _GMP_BOOL_145() 1
#define _GMP_BOOL_146() 1
#define _GMP_BOOL_147() 1
#define _GMP_BOOL_148() 1
#define _GMP_BOOL_149() 1
#define _GMP_BOOL_150() 1
#define _GMP_BOOL_151() 1
#define _GMP_BOOL_152() 1
#define _GMP_BOOL_153() 1
#define _GMP_BOOL_154() 1
#define _GMP_BOOL_155() 1
#define _GMP_BOOL_156() 1
#define _GMP_BOOL_157() 1
#define _GMP_BOOL_158() 1
#define _GMP_BOOL_159() 1
#define _GMP_BOOL_160() 1
#define _GMP_BOOL_161() 1
#define _GMP_BOOL_162() 1
#define _GMP_BOOL_163() 1
#define _GMP_BOOL_164() 1
#define _GMP_BOOL_165() 1
#define _GMP_BOOL_166() 1
#define _GMP_BOOL_167() 1
#define _GMP_BOOL_168() 1
#define _GMP_BOOL_169() 1
#define _GMP_BOOL_170() 1
#define _GMP_BOOL_171() 1
#define _GMP_BOOL_172() 1
#define _GMP_BOOL_173() 1
#define _GMP_BOOL_174() 1
#define _GMP_BOOL_175() 1
#define _GMP_BOOL_176() 1
#define _GMP_BOOL_177() 1
#define _GMP_BOOL_178() 1
#define _GMP_BOOL_179() 1
#define _GMP_BOOL_180() 1
#define _GMP_BOOL_181() 1
#define _GMP_BOOL_182() 1
#define _GMP_BOOL_183() 1
#define _GMP_BOOL_184() 1
#define _GMP_BOOL_185() 1
#define _GMP_BOOL_186() 1
#define _GMP_BOOL_187() 1
#define _GMP_BOOL_188() 1
#define _GMP_BOOL_189() 1
#define _GMP_BOOL_190() 1
#define _GMP_BOOL_191() 1
#define _GMP_BOOL_192() 1
#define _GMP_BOOL_193() 1
#define _GMP_BOOL_194() 1
#define _GMP_BOOL_195() 1
#define _GMP_BOOL_196() 1
#define _GMP_BOOL_197() 1
#define _GMP_BOOL_198() 1
#define _GMP_BOOL_199() 1
#define _GMP_BOOL_200() 1
#define _GMP_BOOL_201() 1
#define _GMP_BOOL_202() 1
#define _GMP_BOOL_203() 1
#define _GMP_BOOL_204() 1
#define _GMP_BOOL_205() 1
#define _GMP_BOOL_206() 1
#define _GMP_BOOL_207() 1
#define _GMP_BOOL_208() 1
#define _GMP_BOOL_209() 1
#define _GMP_BOOL_210() 1
#define _GMP_BOOL_211() 1
#define _GMP_BOOL_212() 1
#define _GMP_BOOL_213() 1
#define _GMP_BOOL_214() 1
#define _GMP_BOOL_215() 1
#define _GMP_BOOL_216() 1
#define _GMP_BOOL_217() 1
#define _GMP_BOOL_218() 1
#define _GMP_BOOL_219() 1
#define _GMP_BOOL_220() 1
#define _GMP_BOOL_221() 1
#define _GMP_BOOL_222() 1
#define _GMP_BOOL_223() 1
#define _GMP_BOOL_224() 1
#define _GMP_BOOL_225() 1
#define _GMP_BOOL_226() 1
#define _GMP_BOOL_227() 1
#define _GMP_BOOL_228() 1
#define _GMP_BOOL_229() 1
#define _GMP_BOOL_230() 1
#define _GMP_BOOL_231() 1
#define _GMP_BOOL_232() 1
#define _GMP_BOOL_233() 1
#define _GMP_BOOL_234() 1
#define _GMP_BOOL_235() 1
#define _GMP_BOOL_236() 1
#define _GMP_BOOL_237() 1
#define _GMP_BOOL_238() 1
#define _GMP_BOOL_239() 1
#define _GMP_BOOL_240() 1
#define _GMP_BOOL_241() 1
#define _GMP_BOOL_242() 1
#define _GMP_BOOL_243() 1
#define _GMP_BOOL_244() 1
#define _GMP_BOOL_245() 1
#define _GMP_BOOL_246() 1
#define _GMP_BOOL_247() 1
#define _GMP_BOOL_248() 1
#define _GMP_BOOL_249() 1
#define _GMP_BOOL_250() 1
#define _GMP_BOOL_251() 1
#define _GMP_BOOL_252() 1
#define _GMP_BOOL_253() 1
#define _GMP_BOOL_254() 1
#define _GMP_BOOL_255() 1

/**
 * @brief Maximum depth allowed for macro nesting.
 * 
 * This macro defines the maximum depth allowed for macro nesting.
 * Exceeding this depth may lead to compiler errors or warnings related to
 * macro recursion depth.
 */
#define GMP_MAX_INDEX 254

/**
 * \brief Macro to check if an index is within a specified range.
 * 
 * This macro checks if the given index is within a specified range defined by \ref GMP_MAX_INDEX.
 * If the index exceeds \ref GMP_MAX_INDEX, an error is generated; otherwise, it performs no action.
 * 
 * \param index The index to check.
 */
#define GMP_CHECK_INDEX(index) GMP_OVERLOAD_INVOKE(_GMP_CHECK_INDEX_R, GMP_HAS_COMMA(GMP_OVERLOAD_INVOKE(_GMP_CHECK_INDEX, index)))(index)
#define _GMP_CHECK_INDEX_R_1(index)
#define _GMP_CHECK_INDEX_ERROR_MSG_IMPL(index, maximum) Error_Index_##index##_Exceeds_Maximum_Macro_Index_##maximum;
#define _GMP_CHECK_INDEX_ERROR_MSG(index, maximum) _GMP_CHECK_INDEX_ERROR_MSG_IMPL(index, maximum)
#define _GMP_CHECK_INDEX_R_0(index) _GMP_CHECK_INDEX_ERROR_MSG(index, GMP_MAX_INDEX)
#define _GMP_CHECK_INDEX_0 ,
#define _GMP_CHECK_INDEX_1 ,
#define _GMP_CHECK_INDEX_2 ,
#define _GMP_CHECK_INDEX_3 ,
#define _GMP_CHECK_INDEX_4 ,
#define _GMP_CHECK_INDEX_5 ,
#define _GMP_CHECK_INDEX_6 ,
#define _GMP_CHECK_INDEX_7 ,
#define _GMP_CHECK_INDEX_8 ,
#define _GMP_CHECK_INDEX_9 ,
#define _GMP_CHECK_INDEX_10 ,
#define _GMP_CHECK_INDEX_11 ,
#define _GMP_CHECK_INDEX_12 ,
#define _GMP_CHECK_INDEX_13 ,
#define _GMP_CHECK_INDEX_14 ,
#define _GMP_CHECK_INDEX_15 ,
#define _GMP_CHECK_INDEX_16 ,
#define _GMP_CHECK_INDEX_17 ,
#define _GMP_CHECK_INDEX_18 ,
#define _GMP_CHECK_INDEX_19 ,
#define _GMP_CHECK_INDEX_20 ,
#define _GMP_CHECK_INDEX_21 ,
#define _GMP_CHECK_INDEX_22 ,
#define _GMP_CHECK_INDEX_23 ,
#define _GMP_CHECK_INDEX_24 ,
#define _GMP_CHECK_INDEX_25 ,
#define _GMP_CHECK_INDEX_26 ,
#define _GMP_CHECK_INDEX_27 ,
#define _GMP_CHECK_INDEX_28 ,
#define _GMP_CHECK_INDEX_29 ,
#define _GMP_CHECK_INDEX_30 ,
#define _GMP_CHECK_INDEX_31 ,
#define _GMP_CHECK_INDEX_32 ,
#define _GMP_CHECK_INDEX_33 ,
#define _GMP_CHECK_INDEX_34 ,
#define _GMP_CHECK_INDEX_35 ,
#define _GMP_CHECK_INDEX_36 ,
#define _GMP_CHECK_INDEX_37 ,
#define _GMP_CHECK_INDEX_38 ,
#define _GMP_CHECK_INDEX_39 ,
#define _GMP_CHECK_INDEX_40 ,
#define _GMP_CHECK_INDEX_41 ,
#define _GMP_CHECK_INDEX_42 ,
#define _GMP_CHECK_INDEX_43 ,
#define _GMP_CHECK_INDEX_44 ,
#define _GMP_CHECK_INDEX_45 ,
#define _GMP_CHECK_INDEX_46 ,
#define _GMP_CHECK_INDEX_47 ,
#define _GMP_CHECK_INDEX_48 ,
#define _GMP_CHECK_INDEX_49 ,
#define _GMP_CHECK_INDEX_50 ,
#define _GMP_CHECK_INDEX_51 ,
#define _GMP_CHECK_INDEX_52 ,
#define _GMP_CHECK_INDEX_53 ,
#define _GMP_CHECK_INDEX_54 ,
#define _GMP_CHECK_INDEX_55 ,
#define _GMP_CHECK_INDEX_56 ,
#define _GMP_CHECK_INDEX_57 ,
#define _GMP_CHECK_INDEX_58 ,
#define _GMP_CHECK_INDEX_59 ,
#define _GMP_CHECK_INDEX_60 ,
#define _GMP_CHECK_INDEX_61 ,
#define _GMP_CHECK_INDEX_62 ,
#define _GMP_CHECK_INDEX_63 ,
#define _GMP_CHECK_INDEX_64 ,
#define _GMP_CHECK_INDEX_65 ,
#define _GMP_CHECK_INDEX_66 ,
#define _GMP_CHECK_INDEX_67 ,
#define _GMP_CHECK_INDEX_68 ,
#define _GMP_CHECK_INDEX_69 ,
#define _GMP_CHECK_INDEX_70 ,
#define _GMP_CHECK_INDEX_71 ,
#define _GMP_CHECK_INDEX_72 ,
#define _GMP_CHECK_INDEX_73 ,
#define _GMP_CHECK_INDEX_74 ,
#define _GMP_CHECK_INDEX_75 ,
#define _GMP_CHECK_INDEX_76 ,
#define _GMP_CHECK_INDEX_77 ,
#define _GMP_CHECK_INDEX_78 ,
#define _GMP_CHECK_INDEX_79 ,
#define _GMP_CHECK_INDEX_80 ,
#define _GMP_CHECK_INDEX_81 ,
#define _GMP_CHECK_INDEX_82 ,
#define _GMP_CHECK_INDEX_83 ,
#define _GMP_CHECK_INDEX_84 ,
#define _GMP_CHECK_INDEX_85 ,
#define _GMP_CHECK_INDEX_86 ,
#define _GMP_CHECK_INDEX_87 ,
#define _GMP_CHECK_INDEX_88 ,
#define _GMP_CHECK_INDEX_89 ,
#define _GMP_CHECK_INDEX_90 ,
#define _GMP_CHECK_INDEX_91 ,
#define _GMP_CHECK_INDEX_92 ,
#define _GMP_CHECK_INDEX_93 ,
#define _GMP_CHECK_INDEX_94 ,
#define _GMP_CHECK_INDEX_95 ,
#define _GMP_CHECK_INDEX_96 ,
#define _GMP_CHECK_INDEX_97 ,
#define _GMP_CHECK_INDEX_98 ,
#define _GMP_CHECK_INDEX_99 ,
#define _GMP_CHECK_INDEX_100 ,
#define _GMP_CHECK_INDEX_101 ,
#define _GMP_CHECK_INDEX_102 ,
#define _GMP_CHECK_INDEX_103 ,
#define _GMP_CHECK_INDEX_104 ,
#define _GMP_CHECK_INDEX_105 ,
#define _GMP_CHECK_INDEX_106 ,
#define _GMP_CHECK_INDEX_107 ,
#define _GMP_CHECK_INDEX_108 ,
#define _GMP_CHECK_INDEX_109 ,
#define _GMP_CHECK_INDEX_110 ,
#define _GMP_CHECK_INDEX_111 ,
#define _GMP_CHECK_INDEX_112 ,
#define _GMP_CHECK_INDEX_113 ,
#define _GMP_CHECK_INDEX_114 ,
#define _GMP_CHECK_INDEX_115 ,
#define _GMP_CHECK_INDEX_116 ,
#define _GMP_CHECK_INDEX_117 ,
#define _GMP_CHECK_INDEX_118 ,
#define _GMP_CHECK_INDEX_119 ,
#define _GMP_CHECK_INDEX_120 ,
#define _GMP_CHECK_INDEX_121 ,
#define _GMP_CHECK_INDEX_122 ,
#define _GMP_CHECK_INDEX_123 ,
#define _GMP_CHECK_INDEX_124 ,
#define _GMP_CHECK_INDEX_125 ,
#define _GMP_CHECK_INDEX_126 ,
#define _GMP_CHECK_INDEX_127 ,
#define _GMP_CHECK_INDEX_128 ,
#define _GMP_CHECK_INDEX_129 ,
#define _GMP_CHECK_INDEX_130 ,
#define _GMP_CHECK_INDEX_131 ,
#define _GMP_CHECK_INDEX_132 ,
#define _GMP_CHECK_INDEX_133 ,
#define _GMP_CHECK_INDEX_134 ,
#define _GMP_CHECK_INDEX_135 ,
#define _GMP_CHECK_INDEX_136 ,
#define _GMP_CHECK_INDEX_137 ,
#define _GMP_CHECK_INDEX_138 ,
#define _GMP_CHECK_INDEX_139 ,
#define _GMP_CHECK_INDEX_140 ,
#define _GMP_CHECK_INDEX_141 ,
#define _GMP_CHECK_INDEX_142 ,
#define _GMP_CHECK_INDEX_143 ,
#define _GMP_CHECK_INDEX_144 ,
#define _GMP_CHECK_INDEX_145 ,
#define _GMP_CHECK_INDEX_146 ,
#define _GMP_CHECK_INDEX_147 ,
#define _GMP_CHECK_INDEX_148 ,
#define _GMP_CHECK_INDEX_149 ,
#define _GMP_CHECK_INDEX_150 ,
#define _GMP_CHECK_INDEX_151 ,
#define _GMP_CHECK_INDEX_152 ,
#define _GMP_CHECK_INDEX_153 ,
#define _GMP_CHECK_INDEX_154 ,
#define _GMP_CHECK_INDEX_155 ,
#define _GMP_CHECK_INDEX_156 ,
#define _GMP_CHECK_INDEX_157 ,
#define _GMP_CHECK_INDEX_158 ,
#define _GMP_CHECK_INDEX_159 ,
#define _GMP_CHECK_INDEX_160 ,
#define _GMP_CHECK_INDEX_161 ,
#define _GMP_CHECK_INDEX_162 ,
#define _GMP_CHECK_INDEX_163 ,
#define _GMP_CHECK_INDEX_164 ,
#define _GMP_CHECK_INDEX_165 ,
#define _GMP_CHECK_INDEX_166 ,
#define _GMP_CHECK_INDEX_167 ,
#define _GMP_CHECK_INDEX_168 ,
#define _GMP_CHECK_INDEX_169 ,
#define _GMP_CHECK_INDEX_170 ,
#define _GMP_CHECK_INDEX_171 ,
#define _GMP_CHECK_INDEX_172 ,
#define _GMP_CHECK_INDEX_173 ,
#define _GMP_CHECK_INDEX_174 ,
#define _GMP_CHECK_INDEX_175 ,
#define _GMP_CHECK_INDEX_176 ,
#define _GMP_CHECK_INDEX_177 ,
#define _GMP_CHECK_INDEX_178 ,
#define _GMP_CHECK_INDEX_179 ,
#define _GMP_CHECK_INDEX_180 ,
#define _GMP_CHECK_INDEX_181 ,
#define _GMP_CHECK_INDEX_182 ,
#define _GMP_CHECK_INDEX_183 ,
#define _GMP_CHECK_INDEX_184 ,
#define _GMP_CHECK_INDEX_185 ,
#define _GMP_CHECK_INDEX_186 ,
#define _GMP_CHECK_INDEX_187 ,
#define _GMP_CHECK_INDEX_188 ,
#define _GMP_CHECK_INDEX_189 ,
#define _GMP_CHECK_INDEX_190 ,
#define _GMP_CHECK_INDEX_191 ,
#define _GMP_CHECK_INDEX_192 ,
#define _GMP_CHECK_INDEX_193 ,
#define _GMP_CHECK_INDEX_194 ,
#define _GMP_CHECK_INDEX_195 ,
#define _GMP_CHECK_INDEX_196 ,
#define _GMP_CHECK_INDEX_197 ,
#define _GMP_CHECK_INDEX_198 ,
#define _GMP_CHECK_INDEX_199 ,
#define _GMP_CHECK_INDEX_200 ,
#define _GMP_CHECK_INDEX_201 ,
#define _GMP_CHECK_INDEX_202 ,
#define _GMP_CHECK_INDEX_203 ,
#define _GMP_CHECK_INDEX_204 ,
#define _GMP_CHECK_INDEX_205 ,
#define _GMP_CHECK_INDEX_206 ,
#define _GMP_CHECK_INDEX_207 ,
#define _GMP_CHECK_INDEX_208 ,
#define _GMP_CHECK_INDEX_209 ,
#define _GMP_CHECK_INDEX_210 ,
#define _GMP_CHECK_INDEX_211 ,
#define _GMP_CHECK_INDEX_212 ,
#define _GMP_CHECK_INDEX_213 ,
#define _GMP_CHECK_INDEX_214 ,
#define _GMP_CHECK_INDEX_215 ,
#define _GMP_CHECK_INDEX_216 ,
#define _GMP_CHECK_INDEX_217 ,
#define _GMP_CHECK_INDEX_218 ,
#define _GMP_CHECK_INDEX_219 ,
#define _GMP_CHECK_INDEX_220 ,
#define _GMP_CHECK_INDEX_221 ,
#define _GMP_CHECK_INDEX_222 ,
#define _GMP_CHECK_INDEX_223 ,
#define _GMP_CHECK_INDEX_224 ,
#define _GMP_CHECK_INDEX_225 ,
#define _GMP_CHECK_INDEX_226 ,
#define _GMP_CHECK_INDEX_227 ,
#define _GMP_CHECK_INDEX_228 ,
#define _GMP_CHECK_INDEX_229 ,
#define _GMP_CHECK_INDEX_230 ,
#define _GMP_CHECK_INDEX_231 ,
#define _GMP_CHECK_INDEX_232 ,
#define _GMP_CHECK_INDEX_233 ,
#define _GMP_CHECK_INDEX_234 ,
#define _GMP_CHECK_INDEX_235 ,
#define _GMP_CHECK_INDEX_236 ,
#define _GMP_CHECK_INDEX_237 ,
#define _GMP_CHECK_INDEX_238 ,
#define _GMP_CHECK_INDEX_239 ,
#define _GMP_CHECK_INDEX_240 ,
#define _GMP_CHECK_INDEX_241 ,
#define _GMP_CHECK_INDEX_242 ,
#define _GMP_CHECK_INDEX_243 ,
#define _GMP_CHECK_INDEX_244 ,
#define _GMP_CHECK_INDEX_245 ,
#define _GMP_CHECK_INDEX_246 ,
#define _GMP_CHECK_INDEX_247 ,
#define _GMP_CHECK_INDEX_248 ,
#define _GMP_CHECK_INDEX_249 ,
#define _GMP_CHECK_INDEX_250 ,
#define _GMP_CHECK_INDEX_251 ,
#define _GMP_CHECK_INDEX_252 ,
#define _GMP_CHECK_INDEX_253 ,
#define _GMP_CHECK_INDEX_254 ,

/**
  * \brief Macro to check if an index is within a specified range.
  *
  * This macro checks if the given index is within a specified range defined by \ref GMP_MAX_INDEX.
  * If the index exceeds \ref GMP_MAX_INDEX, an error is generated; otherwise, it performs no action.
  *
  * \param index The index to check.
  * \return 1 if the given index is valid, 0 otherwise.
  */
#define GMP_CHECK_INDEX_BOOL(index) GMP_OVERLOAD_INVOKE(_GMP_CHECK_INDEX_BOOL_R, GMP_HAS_COMMA(GMP_OVERLOAD_INVOKE(_GMP_CHECK_INDEX, index)))
#define _GMP_CHECK_INDEX_BOOL_R_1 1
#define _GMP_CHECK_INDEX_BOOL_R_0 0

/**
 * \def GMP_MAKE_INDEX_SEQUENCE(index)
 * \brief Generates a comma-separated index sequence up to a given index.
 * 
 * This macro uses overload invocation and recursive macro expansion
 * to generate a comma-separated sequence of indices from 0 up to the specified index.
 * 
 * \param index The maximum index value to include in the sequence.
 * \return A comma-separated sequence of indices.
 */
#define GMP_MAKE_INDEX_SEQUENCE(index) GMP_OVERLOAD_INVOKE(_GMP_MAKE_INDEX_SEQUENCE_PRECHECK, GMP_CHECK_INDEX_BOOL(index))(index)
#define _GMP_MAKE_INDEX_SEQUENCE_PRECHECK_1(index) GMP_OVERLOAD_INVOKE(_GMP_MAKE_INDEX_SEQUENCE, GMP_DEC(index))()
#define _GMP_MAKE_INDEX_SEQUENCE_PRECHECK_0(index) GMP_CHECK_INDEX(index)
#define _GMP_MAKE_INDEX_SEQUENCE_0() 0
#define _GMP_MAKE_INDEX_SEQUENCE_1() _GMP_MAKE_INDEX_SEQUENCE_0(), 1
#define _GMP_MAKE_INDEX_SEQUENCE_2() _GMP_MAKE_INDEX_SEQUENCE_1(), 2
#define _GMP_MAKE_INDEX_SEQUENCE_3() _GMP_MAKE_INDEX_SEQUENCE_2(), 3
#define _GMP_MAKE_INDEX_SEQUENCE_4() _GMP_MAKE_INDEX_SEQUENCE_3(), 4
#define _GMP_MAKE_INDEX_SEQUENCE_5() _GMP_MAKE_INDEX_SEQUENCE_4(), 5
#define _GMP_MAKE_INDEX_SEQUENCE_6() _GMP_MAKE_INDEX_SEQUENCE_5(), 6
#define _GMP_MAKE_INDEX_SEQUENCE_7() _GMP_MAKE_INDEX_SEQUENCE_6(), 7
#define _GMP_MAKE_INDEX_SEQUENCE_8() _GMP_MAKE_INDEX_SEQUENCE_7(), 8
#define _GMP_MAKE_INDEX_SEQUENCE_9() _GMP_MAKE_INDEX_SEQUENCE_8(), 9
#define _GMP_MAKE_INDEX_SEQUENCE_10() _GMP_MAKE_INDEX_SEQUENCE_9(), 10
#define _GMP_MAKE_INDEX_SEQUENCE_11() _GMP_MAKE_INDEX_SEQUENCE_10(), 11
#define _GMP_MAKE_INDEX_SEQUENCE_12() _GMP_MAKE_INDEX_SEQUENCE_11(), 12
#define _GMP_MAKE_INDEX_SEQUENCE_13() _GMP_MAKE_INDEX_SEQUENCE_12(), 13
#define _GMP_MAKE_INDEX_SEQUENCE_14() _GMP_MAKE_INDEX_SEQUENCE_13(), 14
#define _GMP_MAKE_INDEX_SEQUENCE_15() _GMP_MAKE_INDEX_SEQUENCE_14(), 15
#define _GMP_MAKE_INDEX_SEQUENCE_16() _GMP_MAKE_INDEX_SEQUENCE_15(), 16
#define _GMP_MAKE_INDEX_SEQUENCE_17() _GMP_MAKE_INDEX_SEQUENCE_16(), 17
#define _GMP_MAKE_INDEX_SEQUENCE_18() _GMP_MAKE_INDEX_SEQUENCE_17(), 18
#define _GMP_MAKE_INDEX_SEQUENCE_19() _GMP_MAKE_INDEX_SEQUENCE_18(), 19
#define _GMP_MAKE_INDEX_SEQUENCE_20() _GMP_MAKE_INDEX_SEQUENCE_19(), 20
#define _GMP_MAKE_INDEX_SEQUENCE_21() _GMP_MAKE_INDEX_SEQUENCE_20(), 21
#define _GMP_MAKE_INDEX_SEQUENCE_22() _GMP_MAKE_INDEX_SEQUENCE_21(), 22
#define _GMP_MAKE_INDEX_SEQUENCE_23() _GMP_MAKE_INDEX_SEQUENCE_22(), 23
#define _GMP_MAKE_INDEX_SEQUENCE_24() _GMP_MAKE_INDEX_SEQUENCE_23(), 24
#define _GMP_MAKE_INDEX_SEQUENCE_25() _GMP_MAKE_INDEX_SEQUENCE_24(), 25
#define _GMP_MAKE_INDEX_SEQUENCE_26() _GMP_MAKE_INDEX_SEQUENCE_25(), 26
#define _GMP_MAKE_INDEX_SEQUENCE_27() _GMP_MAKE_INDEX_SEQUENCE_26(), 27
#define _GMP_MAKE_INDEX_SEQUENCE_28() _GMP_MAKE_INDEX_SEQUENCE_27(), 28
#define _GMP_MAKE_INDEX_SEQUENCE_29() _GMP_MAKE_INDEX_SEQUENCE_28(), 29
#define _GMP_MAKE_INDEX_SEQUENCE_30() _GMP_MAKE_INDEX_SEQUENCE_29(), 30
#define _GMP_MAKE_INDEX_SEQUENCE_31() _GMP_MAKE_INDEX_SEQUENCE_30(), 31
#define _GMP_MAKE_INDEX_SEQUENCE_32() _GMP_MAKE_INDEX_SEQUENCE_31(), 32
#define _GMP_MAKE_INDEX_SEQUENCE_33() _GMP_MAKE_INDEX_SEQUENCE_32(), 33
#define _GMP_MAKE_INDEX_SEQUENCE_34() _GMP_MAKE_INDEX_SEQUENCE_33(), 34
#define _GMP_MAKE_INDEX_SEQUENCE_35() _GMP_MAKE_INDEX_SEQUENCE_34(), 35
#define _GMP_MAKE_INDEX_SEQUENCE_36() _GMP_MAKE_INDEX_SEQUENCE_35(), 36
#define _GMP_MAKE_INDEX_SEQUENCE_37() _GMP_MAKE_INDEX_SEQUENCE_36(), 37
#define _GMP_MAKE_INDEX_SEQUENCE_38() _GMP_MAKE_INDEX_SEQUENCE_37(), 38
#define _GMP_MAKE_INDEX_SEQUENCE_39() _GMP_MAKE_INDEX_SEQUENCE_38(), 39
#define _GMP_MAKE_INDEX_SEQUENCE_40() _GMP_MAKE_INDEX_SEQUENCE_39(), 40
#define _GMP_MAKE_INDEX_SEQUENCE_41() _GMP_MAKE_INDEX_SEQUENCE_40(), 41
#define _GMP_MAKE_INDEX_SEQUENCE_42() _GMP_MAKE_INDEX_SEQUENCE_41(), 42
#define _GMP_MAKE_INDEX_SEQUENCE_43() _GMP_MAKE_INDEX_SEQUENCE_42(), 43
#define _GMP_MAKE_INDEX_SEQUENCE_44() _GMP_MAKE_INDEX_SEQUENCE_43(), 44
#define _GMP_MAKE_INDEX_SEQUENCE_45() _GMP_MAKE_INDEX_SEQUENCE_44(), 45
#define _GMP_MAKE_INDEX_SEQUENCE_46() _GMP_MAKE_INDEX_SEQUENCE_45(), 46
#define _GMP_MAKE_INDEX_SEQUENCE_47() _GMP_MAKE_INDEX_SEQUENCE_46(), 47
#define _GMP_MAKE_INDEX_SEQUENCE_48() _GMP_MAKE_INDEX_SEQUENCE_47(), 48
#define _GMP_MAKE_INDEX_SEQUENCE_49() _GMP_MAKE_INDEX_SEQUENCE_48(), 49
#define _GMP_MAKE_INDEX_SEQUENCE_50() _GMP_MAKE_INDEX_SEQUENCE_49(), 50
#define _GMP_MAKE_INDEX_SEQUENCE_51() _GMP_MAKE_INDEX_SEQUENCE_50(), 51
#define _GMP_MAKE_INDEX_SEQUENCE_52() _GMP_MAKE_INDEX_SEQUENCE_51(), 52
#define _GMP_MAKE_INDEX_SEQUENCE_53() _GMP_MAKE_INDEX_SEQUENCE_52(), 53
#define _GMP_MAKE_INDEX_SEQUENCE_54() _GMP_MAKE_INDEX_SEQUENCE_53(), 54
#define _GMP_MAKE_INDEX_SEQUENCE_55() _GMP_MAKE_INDEX_SEQUENCE_54(), 55
#define _GMP_MAKE_INDEX_SEQUENCE_56() _GMP_MAKE_INDEX_SEQUENCE_55(), 56
#define _GMP_MAKE_INDEX_SEQUENCE_57() _GMP_MAKE_INDEX_SEQUENCE_56(), 57
#define _GMP_MAKE_INDEX_SEQUENCE_58() _GMP_MAKE_INDEX_SEQUENCE_57(), 58
#define _GMP_MAKE_INDEX_SEQUENCE_59() _GMP_MAKE_INDEX_SEQUENCE_58(), 59
#define _GMP_MAKE_INDEX_SEQUENCE_60() _GMP_MAKE_INDEX_SEQUENCE_59(), 60
#define _GMP_MAKE_INDEX_SEQUENCE_61() _GMP_MAKE_INDEX_SEQUENCE_60(), 61
#define _GMP_MAKE_INDEX_SEQUENCE_62() _GMP_MAKE_INDEX_SEQUENCE_61(), 62
#define _GMP_MAKE_INDEX_SEQUENCE_63() _GMP_MAKE_INDEX_SEQUENCE_62(), 63
#define _GMP_MAKE_INDEX_SEQUENCE_64() _GMP_MAKE_INDEX_SEQUENCE_63(), 64
#define _GMP_MAKE_INDEX_SEQUENCE_65() _GMP_MAKE_INDEX_SEQUENCE_64(), 65
#define _GMP_MAKE_INDEX_SEQUENCE_66() _GMP_MAKE_INDEX_SEQUENCE_65(), 66
#define _GMP_MAKE_INDEX_SEQUENCE_67() _GMP_MAKE_INDEX_SEQUENCE_66(), 67
#define _GMP_MAKE_INDEX_SEQUENCE_68() _GMP_MAKE_INDEX_SEQUENCE_67(), 68
#define _GMP_MAKE_INDEX_SEQUENCE_69() _GMP_MAKE_INDEX_SEQUENCE_68(), 69
#define _GMP_MAKE_INDEX_SEQUENCE_70() _GMP_MAKE_INDEX_SEQUENCE_69(), 70
#define _GMP_MAKE_INDEX_SEQUENCE_71() _GMP_MAKE_INDEX_SEQUENCE_70(), 71
#define _GMP_MAKE_INDEX_SEQUENCE_72() _GMP_MAKE_INDEX_SEQUENCE_71(), 72
#define _GMP_MAKE_INDEX_SEQUENCE_73() _GMP_MAKE_INDEX_SEQUENCE_72(), 73
#define _GMP_MAKE_INDEX_SEQUENCE_74() _GMP_MAKE_INDEX_SEQUENCE_73(), 74
#define _GMP_MAKE_INDEX_SEQUENCE_75() _GMP_MAKE_INDEX_SEQUENCE_74(), 75
#define _GMP_MAKE_INDEX_SEQUENCE_76() _GMP_MAKE_INDEX_SEQUENCE_75(), 76
#define _GMP_MAKE_INDEX_SEQUENCE_77() _GMP_MAKE_INDEX_SEQUENCE_76(), 77
#define _GMP_MAKE_INDEX_SEQUENCE_78() _GMP_MAKE_INDEX_SEQUENCE_77(), 78
#define _GMP_MAKE_INDEX_SEQUENCE_79() _GMP_MAKE_INDEX_SEQUENCE_78(), 79
#define _GMP_MAKE_INDEX_SEQUENCE_80() _GMP_MAKE_INDEX_SEQUENCE_79(), 80
#define _GMP_MAKE_INDEX_SEQUENCE_81() _GMP_MAKE_INDEX_SEQUENCE_80(), 81
#define _GMP_MAKE_INDEX_SEQUENCE_82() _GMP_MAKE_INDEX_SEQUENCE_81(), 82
#define _GMP_MAKE_INDEX_SEQUENCE_83() _GMP_MAKE_INDEX_SEQUENCE_82(), 83
#define _GMP_MAKE_INDEX_SEQUENCE_84() _GMP_MAKE_INDEX_SEQUENCE_83(), 84
#define _GMP_MAKE_INDEX_SEQUENCE_85() _GMP_MAKE_INDEX_SEQUENCE_84(), 85
#define _GMP_MAKE_INDEX_SEQUENCE_86() _GMP_MAKE_INDEX_SEQUENCE_85(), 86
#define _GMP_MAKE_INDEX_SEQUENCE_87() _GMP_MAKE_INDEX_SEQUENCE_86(), 87
#define _GMP_MAKE_INDEX_SEQUENCE_88() _GMP_MAKE_INDEX_SEQUENCE_87(), 88
#define _GMP_MAKE_INDEX_SEQUENCE_89() _GMP_MAKE_INDEX_SEQUENCE_88(), 89
#define _GMP_MAKE_INDEX_SEQUENCE_90() _GMP_MAKE_INDEX_SEQUENCE_89(), 90
#define _GMP_MAKE_INDEX_SEQUENCE_91() _GMP_MAKE_INDEX_SEQUENCE_90(), 91
#define _GMP_MAKE_INDEX_SEQUENCE_92() _GMP_MAKE_INDEX_SEQUENCE_91(), 92
#define _GMP_MAKE_INDEX_SEQUENCE_93() _GMP_MAKE_INDEX_SEQUENCE_92(), 93
#define _GMP_MAKE_INDEX_SEQUENCE_94() _GMP_MAKE_INDEX_SEQUENCE_93(), 94
#define _GMP_MAKE_INDEX_SEQUENCE_95() _GMP_MAKE_INDEX_SEQUENCE_94(), 95
#define _GMP_MAKE_INDEX_SEQUENCE_96() _GMP_MAKE_INDEX_SEQUENCE_95(), 96
#define _GMP_MAKE_INDEX_SEQUENCE_97() _GMP_MAKE_INDEX_SEQUENCE_96(), 97
#define _GMP_MAKE_INDEX_SEQUENCE_98() _GMP_MAKE_INDEX_SEQUENCE_97(), 98
#define _GMP_MAKE_INDEX_SEQUENCE_99() _GMP_MAKE_INDEX_SEQUENCE_98(), 99
#define _GMP_MAKE_INDEX_SEQUENCE_100() _GMP_MAKE_INDEX_SEQUENCE_99(), 100
#define _GMP_MAKE_INDEX_SEQUENCE_101() _GMP_MAKE_INDEX_SEQUENCE_100(), 101
#define _GMP_MAKE_INDEX_SEQUENCE_102() _GMP_MAKE_INDEX_SEQUENCE_101(), 102
#define _GMP_MAKE_INDEX_SEQUENCE_103() _GMP_MAKE_INDEX_SEQUENCE_102(), 103
#define _GMP_MAKE_INDEX_SEQUENCE_104() _GMP_MAKE_INDEX_SEQUENCE_103(), 104
#define _GMP_MAKE_INDEX_SEQUENCE_105() _GMP_MAKE_INDEX_SEQUENCE_104(), 105
#define _GMP_MAKE_INDEX_SEQUENCE_106() _GMP_MAKE_INDEX_SEQUENCE_105(), 106
#define _GMP_MAKE_INDEX_SEQUENCE_107() _GMP_MAKE_INDEX_SEQUENCE_106(), 107
#define _GMP_MAKE_INDEX_SEQUENCE_108() _GMP_MAKE_INDEX_SEQUENCE_107(), 108
#define _GMP_MAKE_INDEX_SEQUENCE_109() _GMP_MAKE_INDEX_SEQUENCE_108(), 109
#define _GMP_MAKE_INDEX_SEQUENCE_110() _GMP_MAKE_INDEX_SEQUENCE_109(), 110
#define _GMP_MAKE_INDEX_SEQUENCE_111() _GMP_MAKE_INDEX_SEQUENCE_110(), 111
#define _GMP_MAKE_INDEX_SEQUENCE_112() _GMP_MAKE_INDEX_SEQUENCE_111(), 112
#define _GMP_MAKE_INDEX_SEQUENCE_113() _GMP_MAKE_INDEX_SEQUENCE_112(), 113
#define _GMP_MAKE_INDEX_SEQUENCE_114() _GMP_MAKE_INDEX_SEQUENCE_113(), 114
#define _GMP_MAKE_INDEX_SEQUENCE_115() _GMP_MAKE_INDEX_SEQUENCE_114(), 115
#define _GMP_MAKE_INDEX_SEQUENCE_116() _GMP_MAKE_INDEX_SEQUENCE_115(), 116
#define _GMP_MAKE_INDEX_SEQUENCE_117() _GMP_MAKE_INDEX_SEQUENCE_116(), 117
#define _GMP_MAKE_INDEX_SEQUENCE_118() _GMP_MAKE_INDEX_SEQUENCE_117(), 118
#define _GMP_MAKE_INDEX_SEQUENCE_119() _GMP_MAKE_INDEX_SEQUENCE_118(), 119
#define _GMP_MAKE_INDEX_SEQUENCE_120() _GMP_MAKE_INDEX_SEQUENCE_119(), 120
#define _GMP_MAKE_INDEX_SEQUENCE_121() _GMP_MAKE_INDEX_SEQUENCE_120(), 121
#define _GMP_MAKE_INDEX_SEQUENCE_122() _GMP_MAKE_INDEX_SEQUENCE_121(), 122
#define _GMP_MAKE_INDEX_SEQUENCE_123() _GMP_MAKE_INDEX_SEQUENCE_122(), 123
#define _GMP_MAKE_INDEX_SEQUENCE_124() _GMP_MAKE_INDEX_SEQUENCE_123(), 124
#define _GMP_MAKE_INDEX_SEQUENCE_125() _GMP_MAKE_INDEX_SEQUENCE_124(), 125
#define _GMP_MAKE_INDEX_SEQUENCE_126() _GMP_MAKE_INDEX_SEQUENCE_125(), 126
#define _GMP_MAKE_INDEX_SEQUENCE_127() _GMP_MAKE_INDEX_SEQUENCE_126(), 127
#define _GMP_MAKE_INDEX_SEQUENCE_128() _GMP_MAKE_INDEX_SEQUENCE_127(), 128
#define _GMP_MAKE_INDEX_SEQUENCE_129() _GMP_MAKE_INDEX_SEQUENCE_128(), 129
#define _GMP_MAKE_INDEX_SEQUENCE_130() _GMP_MAKE_INDEX_SEQUENCE_129(), 130
#define _GMP_MAKE_INDEX_SEQUENCE_131() _GMP_MAKE_INDEX_SEQUENCE_130(), 131
#define _GMP_MAKE_INDEX_SEQUENCE_132() _GMP_MAKE_INDEX_SEQUENCE_131(), 132
#define _GMP_MAKE_INDEX_SEQUENCE_133() _GMP_MAKE_INDEX_SEQUENCE_132(), 133
#define _GMP_MAKE_INDEX_SEQUENCE_134() _GMP_MAKE_INDEX_SEQUENCE_133(), 134
#define _GMP_MAKE_INDEX_SEQUENCE_135() _GMP_MAKE_INDEX_SEQUENCE_134(), 135
#define _GMP_MAKE_INDEX_SEQUENCE_136() _GMP_MAKE_INDEX_SEQUENCE_135(), 136
#define _GMP_MAKE_INDEX_SEQUENCE_137() _GMP_MAKE_INDEX_SEQUENCE_136(), 137
#define _GMP_MAKE_INDEX_SEQUENCE_138() _GMP_MAKE_INDEX_SEQUENCE_137(), 138
#define _GMP_MAKE_INDEX_SEQUENCE_139() _GMP_MAKE_INDEX_SEQUENCE_138(), 139
#define _GMP_MAKE_INDEX_SEQUENCE_140() _GMP_MAKE_INDEX_SEQUENCE_139(), 140
#define _GMP_MAKE_INDEX_SEQUENCE_141() _GMP_MAKE_INDEX_SEQUENCE_140(), 141
#define _GMP_MAKE_INDEX_SEQUENCE_142() _GMP_MAKE_INDEX_SEQUENCE_141(), 142
#define _GMP_MAKE_INDEX_SEQUENCE_143() _GMP_MAKE_INDEX_SEQUENCE_142(), 143
#define _GMP_MAKE_INDEX_SEQUENCE_144() _GMP_MAKE_INDEX_SEQUENCE_143(), 144
#define _GMP_MAKE_INDEX_SEQUENCE_145() _GMP_MAKE_INDEX_SEQUENCE_144(), 145
#define _GMP_MAKE_INDEX_SEQUENCE_146() _GMP_MAKE_INDEX_SEQUENCE_145(), 146
#define _GMP_MAKE_INDEX_SEQUENCE_147() _GMP_MAKE_INDEX_SEQUENCE_146(), 147
#define _GMP_MAKE_INDEX_SEQUENCE_148() _GMP_MAKE_INDEX_SEQUENCE_147(), 148
#define _GMP_MAKE_INDEX_SEQUENCE_149() _GMP_MAKE_INDEX_SEQUENCE_148(), 149
#define _GMP_MAKE_INDEX_SEQUENCE_150() _GMP_MAKE_INDEX_SEQUENCE_149(), 150
#define _GMP_MAKE_INDEX_SEQUENCE_151() _GMP_MAKE_INDEX_SEQUENCE_150(), 151
#define _GMP_MAKE_INDEX_SEQUENCE_152() _GMP_MAKE_INDEX_SEQUENCE_151(), 152
#define _GMP_MAKE_INDEX_SEQUENCE_153() _GMP_MAKE_INDEX_SEQUENCE_152(), 153
#define _GMP_MAKE_INDEX_SEQUENCE_154() _GMP_MAKE_INDEX_SEQUENCE_153(), 154
#define _GMP_MAKE_INDEX_SEQUENCE_155() _GMP_MAKE_INDEX_SEQUENCE_154(), 155
#define _GMP_MAKE_INDEX_SEQUENCE_156() _GMP_MAKE_INDEX_SEQUENCE_155(), 156
#define _GMP_MAKE_INDEX_SEQUENCE_157() _GMP_MAKE_INDEX_SEQUENCE_156(), 157
#define _GMP_MAKE_INDEX_SEQUENCE_158() _GMP_MAKE_INDEX_SEQUENCE_157(), 158
#define _GMP_MAKE_INDEX_SEQUENCE_159() _GMP_MAKE_INDEX_SEQUENCE_158(), 159
#define _GMP_MAKE_INDEX_SEQUENCE_160() _GMP_MAKE_INDEX_SEQUENCE_159(), 160
#define _GMP_MAKE_INDEX_SEQUENCE_161() _GMP_MAKE_INDEX_SEQUENCE_160(), 161
#define _GMP_MAKE_INDEX_SEQUENCE_162() _GMP_MAKE_INDEX_SEQUENCE_161(), 162
#define _GMP_MAKE_INDEX_SEQUENCE_163() _GMP_MAKE_INDEX_SEQUENCE_162(), 163
#define _GMP_MAKE_INDEX_SEQUENCE_164() _GMP_MAKE_INDEX_SEQUENCE_163(), 164
#define _GMP_MAKE_INDEX_SEQUENCE_165() _GMP_MAKE_INDEX_SEQUENCE_164(), 165
#define _GMP_MAKE_INDEX_SEQUENCE_166() _GMP_MAKE_INDEX_SEQUENCE_165(), 166
#define _GMP_MAKE_INDEX_SEQUENCE_167() _GMP_MAKE_INDEX_SEQUENCE_166(), 167
#define _GMP_MAKE_INDEX_SEQUENCE_168() _GMP_MAKE_INDEX_SEQUENCE_167(), 168
#define _GMP_MAKE_INDEX_SEQUENCE_169() _GMP_MAKE_INDEX_SEQUENCE_168(), 169
#define _GMP_MAKE_INDEX_SEQUENCE_170() _GMP_MAKE_INDEX_SEQUENCE_169(), 170
#define _GMP_MAKE_INDEX_SEQUENCE_171() _GMP_MAKE_INDEX_SEQUENCE_170(), 171
#define _GMP_MAKE_INDEX_SEQUENCE_172() _GMP_MAKE_INDEX_SEQUENCE_171(), 172
#define _GMP_MAKE_INDEX_SEQUENCE_173() _GMP_MAKE_INDEX_SEQUENCE_172(), 173
#define _GMP_MAKE_INDEX_SEQUENCE_174() _GMP_MAKE_INDEX_SEQUENCE_173(), 174
#define _GMP_MAKE_INDEX_SEQUENCE_175() _GMP_MAKE_INDEX_SEQUENCE_174(), 175
#define _GMP_MAKE_INDEX_SEQUENCE_176() _GMP_MAKE_INDEX_SEQUENCE_175(), 176
#define _GMP_MAKE_INDEX_SEQUENCE_177() _GMP_MAKE_INDEX_SEQUENCE_176(), 177
#define _GMP_MAKE_INDEX_SEQUENCE_178() _GMP_MAKE_INDEX_SEQUENCE_177(), 178
#define _GMP_MAKE_INDEX_SEQUENCE_179() _GMP_MAKE_INDEX_SEQUENCE_178(), 179
#define _GMP_MAKE_INDEX_SEQUENCE_180() _GMP_MAKE_INDEX_SEQUENCE_179(), 180
#define _GMP_MAKE_INDEX_SEQUENCE_181() _GMP_MAKE_INDEX_SEQUENCE_180(), 181
#define _GMP_MAKE_INDEX_SEQUENCE_182() _GMP_MAKE_INDEX_SEQUENCE_181(), 182
#define _GMP_MAKE_INDEX_SEQUENCE_183() _GMP_MAKE_INDEX_SEQUENCE_182(), 183
#define _GMP_MAKE_INDEX_SEQUENCE_184() _GMP_MAKE_INDEX_SEQUENCE_183(), 184
#define _GMP_MAKE_INDEX_SEQUENCE_185() _GMP_MAKE_INDEX_SEQUENCE_184(), 185
#define _GMP_MAKE_INDEX_SEQUENCE_186() _GMP_MAKE_INDEX_SEQUENCE_185(), 186
#define _GMP_MAKE_INDEX_SEQUENCE_187() _GMP_MAKE_INDEX_SEQUENCE_186(), 187
#define _GMP_MAKE_INDEX_SEQUENCE_188() _GMP_MAKE_INDEX_SEQUENCE_187(), 188
#define _GMP_MAKE_INDEX_SEQUENCE_189() _GMP_MAKE_INDEX_SEQUENCE_188(), 189
#define _GMP_MAKE_INDEX_SEQUENCE_190() _GMP_MAKE_INDEX_SEQUENCE_189(), 190
#define _GMP_MAKE_INDEX_SEQUENCE_191() _GMP_MAKE_INDEX_SEQUENCE_190(), 191
#define _GMP_MAKE_INDEX_SEQUENCE_192() _GMP_MAKE_INDEX_SEQUENCE_191(), 192
#define _GMP_MAKE_INDEX_SEQUENCE_193() _GMP_MAKE_INDEX_SEQUENCE_192(), 193
#define _GMP_MAKE_INDEX_SEQUENCE_194() _GMP_MAKE_INDEX_SEQUENCE_193(), 194
#define _GMP_MAKE_INDEX_SEQUENCE_195() _GMP_MAKE_INDEX_SEQUENCE_194(), 195
#define _GMP_MAKE_INDEX_SEQUENCE_196() _GMP_MAKE_INDEX_SEQUENCE_195(), 196
#define _GMP_MAKE_INDEX_SEQUENCE_197() _GMP_MAKE_INDEX_SEQUENCE_196(), 197
#define _GMP_MAKE_INDEX_SEQUENCE_198() _GMP_MAKE_INDEX_SEQUENCE_197(), 198
#define _GMP_MAKE_INDEX_SEQUENCE_199() _GMP_MAKE_INDEX_SEQUENCE_198(), 199
#define _GMP_MAKE_INDEX_SEQUENCE_200() _GMP_MAKE_INDEX_SEQUENCE_199(), 200
#define _GMP_MAKE_INDEX_SEQUENCE_201() _GMP_MAKE_INDEX_SEQUENCE_200(), 201
#define _GMP_MAKE_INDEX_SEQUENCE_202() _GMP_MAKE_INDEX_SEQUENCE_201(), 202
#define _GMP_MAKE_INDEX_SEQUENCE_203() _GMP_MAKE_INDEX_SEQUENCE_202(), 203
#define _GMP_MAKE_INDEX_SEQUENCE_204() _GMP_MAKE_INDEX_SEQUENCE_203(), 204
#define _GMP_MAKE_INDEX_SEQUENCE_205() _GMP_MAKE_INDEX_SEQUENCE_204(), 205
#define _GMP_MAKE_INDEX_SEQUENCE_206() _GMP_MAKE_INDEX_SEQUENCE_205(), 206
#define _GMP_MAKE_INDEX_SEQUENCE_207() _GMP_MAKE_INDEX_SEQUENCE_206(), 207
#define _GMP_MAKE_INDEX_SEQUENCE_208() _GMP_MAKE_INDEX_SEQUENCE_207(), 208
#define _GMP_MAKE_INDEX_SEQUENCE_209() _GMP_MAKE_INDEX_SEQUENCE_208(), 209
#define _GMP_MAKE_INDEX_SEQUENCE_210() _GMP_MAKE_INDEX_SEQUENCE_209(), 210
#define _GMP_MAKE_INDEX_SEQUENCE_211() _GMP_MAKE_INDEX_SEQUENCE_210(), 211
#define _GMP_MAKE_INDEX_SEQUENCE_212() _GMP_MAKE_INDEX_SEQUENCE_211(), 212
#define _GMP_MAKE_INDEX_SEQUENCE_213() _GMP_MAKE_INDEX_SEQUENCE_212(), 213
#define _GMP_MAKE_INDEX_SEQUENCE_214() _GMP_MAKE_INDEX_SEQUENCE_213(), 214
#define _GMP_MAKE_INDEX_SEQUENCE_215() _GMP_MAKE_INDEX_SEQUENCE_214(), 215
#define _GMP_MAKE_INDEX_SEQUENCE_216() _GMP_MAKE_INDEX_SEQUENCE_215(), 216
#define _GMP_MAKE_INDEX_SEQUENCE_217() _GMP_MAKE_INDEX_SEQUENCE_216(), 217
#define _GMP_MAKE_INDEX_SEQUENCE_218() _GMP_MAKE_INDEX_SEQUENCE_217(), 218
#define _GMP_MAKE_INDEX_SEQUENCE_219() _GMP_MAKE_INDEX_SEQUENCE_218(), 219
#define _GMP_MAKE_INDEX_SEQUENCE_220() _GMP_MAKE_INDEX_SEQUENCE_219(), 220
#define _GMP_MAKE_INDEX_SEQUENCE_221() _GMP_MAKE_INDEX_SEQUENCE_220(), 221
#define _GMP_MAKE_INDEX_SEQUENCE_222() _GMP_MAKE_INDEX_SEQUENCE_221(), 222
#define _GMP_MAKE_INDEX_SEQUENCE_223() _GMP_MAKE_INDEX_SEQUENCE_222(), 223
#define _GMP_MAKE_INDEX_SEQUENCE_224() _GMP_MAKE_INDEX_SEQUENCE_223(), 224
#define _GMP_MAKE_INDEX_SEQUENCE_225() _GMP_MAKE_INDEX_SEQUENCE_224(), 225
#define _GMP_MAKE_INDEX_SEQUENCE_226() _GMP_MAKE_INDEX_SEQUENCE_225(), 226
#define _GMP_MAKE_INDEX_SEQUENCE_227() _GMP_MAKE_INDEX_SEQUENCE_226(), 227
#define _GMP_MAKE_INDEX_SEQUENCE_228() _GMP_MAKE_INDEX_SEQUENCE_227(), 228
#define _GMP_MAKE_INDEX_SEQUENCE_229() _GMP_MAKE_INDEX_SEQUENCE_228(), 229
#define _GMP_MAKE_INDEX_SEQUENCE_230() _GMP_MAKE_INDEX_SEQUENCE_229(), 230
#define _GMP_MAKE_INDEX_SEQUENCE_231() _GMP_MAKE_INDEX_SEQUENCE_230(), 231
#define _GMP_MAKE_INDEX_SEQUENCE_232() _GMP_MAKE_INDEX_SEQUENCE_231(), 232
#define _GMP_MAKE_INDEX_SEQUENCE_233() _GMP_MAKE_INDEX_SEQUENCE_232(), 233
#define _GMP_MAKE_INDEX_SEQUENCE_234() _GMP_MAKE_INDEX_SEQUENCE_233(), 234
#define _GMP_MAKE_INDEX_SEQUENCE_235() _GMP_MAKE_INDEX_SEQUENCE_234(), 235
#define _GMP_MAKE_INDEX_SEQUENCE_236() _GMP_MAKE_INDEX_SEQUENCE_235(), 236
#define _GMP_MAKE_INDEX_SEQUENCE_237() _GMP_MAKE_INDEX_SEQUENCE_236(), 237
#define _GMP_MAKE_INDEX_SEQUENCE_238() _GMP_MAKE_INDEX_SEQUENCE_237(), 238
#define _GMP_MAKE_INDEX_SEQUENCE_239() _GMP_MAKE_INDEX_SEQUENCE_238(), 239
#define _GMP_MAKE_INDEX_SEQUENCE_240() _GMP_MAKE_INDEX_SEQUENCE_239(), 240
#define _GMP_MAKE_INDEX_SEQUENCE_241() _GMP_MAKE_INDEX_SEQUENCE_240(), 241
#define _GMP_MAKE_INDEX_SEQUENCE_242() _GMP_MAKE_INDEX_SEQUENCE_241(), 242
#define _GMP_MAKE_INDEX_SEQUENCE_243() _GMP_MAKE_INDEX_SEQUENCE_242(), 243
#define _GMP_MAKE_INDEX_SEQUENCE_244() _GMP_MAKE_INDEX_SEQUENCE_243(), 244
#define _GMP_MAKE_INDEX_SEQUENCE_245() _GMP_MAKE_INDEX_SEQUENCE_244(), 245
#define _GMP_MAKE_INDEX_SEQUENCE_246() _GMP_MAKE_INDEX_SEQUENCE_245(), 246
#define _GMP_MAKE_INDEX_SEQUENCE_247() _GMP_MAKE_INDEX_SEQUENCE_246(), 247
#define _GMP_MAKE_INDEX_SEQUENCE_248() _GMP_MAKE_INDEX_SEQUENCE_247(), 248
#define _GMP_MAKE_INDEX_SEQUENCE_249() _GMP_MAKE_INDEX_SEQUENCE_248(), 249
#define _GMP_MAKE_INDEX_SEQUENCE_250() _GMP_MAKE_INDEX_SEQUENCE_249(), 250
#define _GMP_MAKE_INDEX_SEQUENCE_251() _GMP_MAKE_INDEX_SEQUENCE_250(), 251
#define _GMP_MAKE_INDEX_SEQUENCE_252() _GMP_MAKE_INDEX_SEQUENCE_251(), 252
#define _GMP_MAKE_INDEX_SEQUENCE_253() _GMP_MAKE_INDEX_SEQUENCE_252(), 253

/**
 * \brief Macro to compare two integer values for equality.
 *
 * This macro compares two integer values, \a i and \a j, and returns 1 if they are equal,
 * and 0 if they are not. The maximum values for \a i and \a j should not exceed \ref GMP_MAX_INDEX.
 *
 * \param i The first integer value to compare.
 * \param j The second integer value to compare.
 * \return 1 if \a i and \a j are equal, 0 otherwise.
 *
 * \note Both \a i and \a j should be less than or equal to \ref GMP_MAX_INDEX.
 */
#define GMP_EQUAL_INT(i, j) GMP_CHECK_INDEX(i) GMP_CHECK_INDEX(j) GMP_OVERLOAD_INVOKE(_GMP_EQUAL_INT_RESULT, \
    GMP_HAS_COMMA(GMP_OVERLOAD_INVOKE(_GMP_EQUAL_INT, i, j)))
#define _GMP_EQUAL_INT_RESULT_0 0
#define _GMP_EQUAL_INT_RESULT_1 1
#define _GMP_EQUAL_INT_0_0 ,
#define _GMP_EQUAL_INT_1_1 ,
#define _GMP_EQUAL_INT_2_2 ,
#define _GMP_EQUAL_INT_3_3 ,
#define _GMP_EQUAL_INT_4_4 ,
#define _GMP_EQUAL_INT_5_5 ,
#define _GMP_EQUAL_INT_6_6 ,
#define _GMP_EQUAL_INT_7_7 ,
#define _GMP_EQUAL_INT_8_8 ,
#define _GMP_EQUAL_INT_9_9 ,
#define _GMP_EQUAL_INT_10_10 ,
#define _GMP_EQUAL_INT_11_11 ,
#define _GMP_EQUAL_INT_12_12 ,
#define _GMP_EQUAL_INT_13_13 ,
#define _GMP_EQUAL_INT_14_14 ,
#define _GMP_EQUAL_INT_15_15 ,
#define _GMP_EQUAL_INT_16_16 ,
#define _GMP_EQUAL_INT_17_17 ,
#define _GMP_EQUAL_INT_18_18 ,
#define _GMP_EQUAL_INT_19_19 ,
#define _GMP_EQUAL_INT_20_20 ,
#define _GMP_EQUAL_INT_21_21 ,
#define _GMP_EQUAL_INT_22_22 ,
#define _GMP_EQUAL_INT_23_23 ,
#define _GMP_EQUAL_INT_24_24 ,
#define _GMP_EQUAL_INT_25_25 ,
#define _GMP_EQUAL_INT_26_26 ,
#define _GMP_EQUAL_INT_27_27 ,
#define _GMP_EQUAL_INT_28_28 ,
#define _GMP_EQUAL_INT_29_29 ,
#define _GMP_EQUAL_INT_30_30 ,
#define _GMP_EQUAL_INT_31_31 ,
#define _GMP_EQUAL_INT_32_32 ,
#define _GMP_EQUAL_INT_33_33 ,
#define _GMP_EQUAL_INT_34_34 ,
#define _GMP_EQUAL_INT_35_35 ,
#define _GMP_EQUAL_INT_36_36 ,
#define _GMP_EQUAL_INT_37_37 ,
#define _GMP_EQUAL_INT_38_38 ,
#define _GMP_EQUAL_INT_39_39 ,
#define _GMP_EQUAL_INT_40_40 ,
#define _GMP_EQUAL_INT_41_41 ,
#define _GMP_EQUAL_INT_42_42 ,
#define _GMP_EQUAL_INT_43_43 ,
#define _GMP_EQUAL_INT_44_44 ,
#define _GMP_EQUAL_INT_45_45 ,
#define _GMP_EQUAL_INT_46_46 ,
#define _GMP_EQUAL_INT_47_47 ,
#define _GMP_EQUAL_INT_48_48 ,
#define _GMP_EQUAL_INT_49_49 ,
#define _GMP_EQUAL_INT_50_50 ,
#define _GMP_EQUAL_INT_51_51 ,
#define _GMP_EQUAL_INT_52_52 ,
#define _GMP_EQUAL_INT_53_53 ,
#define _GMP_EQUAL_INT_54_54 ,
#define _GMP_EQUAL_INT_55_55 ,
#define _GMP_EQUAL_INT_56_56 ,
#define _GMP_EQUAL_INT_57_57 ,
#define _GMP_EQUAL_INT_58_58 ,
#define _GMP_EQUAL_INT_59_59 ,
#define _GMP_EQUAL_INT_60_60 ,
#define _GMP_EQUAL_INT_61_61 ,
#define _GMP_EQUAL_INT_62_62 ,
#define _GMP_EQUAL_INT_63_63 ,
#define _GMP_EQUAL_INT_64_64 ,
#define _GMP_EQUAL_INT_65_65 ,
#define _GMP_EQUAL_INT_66_66 ,
#define _GMP_EQUAL_INT_67_67 ,
#define _GMP_EQUAL_INT_68_68 ,
#define _GMP_EQUAL_INT_69_69 ,
#define _GMP_EQUAL_INT_70_70 ,
#define _GMP_EQUAL_INT_71_71 ,
#define _GMP_EQUAL_INT_72_72 ,
#define _GMP_EQUAL_INT_73_73 ,
#define _GMP_EQUAL_INT_74_74 ,
#define _GMP_EQUAL_INT_75_75 ,
#define _GMP_EQUAL_INT_76_76 ,
#define _GMP_EQUAL_INT_77_77 ,
#define _GMP_EQUAL_INT_78_78 ,
#define _GMP_EQUAL_INT_79_79 ,
#define _GMP_EQUAL_INT_80_80 ,
#define _GMP_EQUAL_INT_81_81 ,
#define _GMP_EQUAL_INT_82_82 ,
#define _GMP_EQUAL_INT_83_83 ,
#define _GMP_EQUAL_INT_84_84 ,
#define _GMP_EQUAL_INT_85_85 ,
#define _GMP_EQUAL_INT_86_86 ,
#define _GMP_EQUAL_INT_87_87 ,
#define _GMP_EQUAL_INT_88_88 ,
#define _GMP_EQUAL_INT_89_89 ,
#define _GMP_EQUAL_INT_90_90 ,
#define _GMP_EQUAL_INT_91_91 ,
#define _GMP_EQUAL_INT_92_92 ,
#define _GMP_EQUAL_INT_93_93 ,
#define _GMP_EQUAL_INT_94_94 ,
#define _GMP_EQUAL_INT_95_95 ,
#define _GMP_EQUAL_INT_96_96 ,
#define _GMP_EQUAL_INT_97_97 ,
#define _GMP_EQUAL_INT_98_98 ,
#define _GMP_EQUAL_INT_99_99 ,
#define _GMP_EQUAL_INT_100_100 ,
#define _GMP_EQUAL_INT_101_101 ,
#define _GMP_EQUAL_INT_102_102 ,
#define _GMP_EQUAL_INT_103_103 ,
#define _GMP_EQUAL_INT_104_104 ,
#define _GMP_EQUAL_INT_105_105 ,
#define _GMP_EQUAL_INT_106_106 ,
#define _GMP_EQUAL_INT_107_107 ,
#define _GMP_EQUAL_INT_108_108 ,
#define _GMP_EQUAL_INT_109_109 ,
#define _GMP_EQUAL_INT_110_110 ,
#define _GMP_EQUAL_INT_111_111 ,
#define _GMP_EQUAL_INT_112_112 ,
#define _GMP_EQUAL_INT_113_113 ,
#define _GMP_EQUAL_INT_114_114 ,
#define _GMP_EQUAL_INT_115_115 ,
#define _GMP_EQUAL_INT_116_116 ,
#define _GMP_EQUAL_INT_117_117 ,
#define _GMP_EQUAL_INT_118_118 ,
#define _GMP_EQUAL_INT_119_119 ,
#define _GMP_EQUAL_INT_120_120 ,
#define _GMP_EQUAL_INT_121_121 ,
#define _GMP_EQUAL_INT_122_122 ,
#define _GMP_EQUAL_INT_123_123 ,
#define _GMP_EQUAL_INT_124_124 ,
#define _GMP_EQUAL_INT_125_125 ,
#define _GMP_EQUAL_INT_126_126 ,
#define _GMP_EQUAL_INT_127_127 ,
#define _GMP_EQUAL_INT_128_128 ,
#define _GMP_EQUAL_INT_129_129 ,
#define _GMP_EQUAL_INT_130_130 ,
#define _GMP_EQUAL_INT_131_131 ,
#define _GMP_EQUAL_INT_132_132 ,
#define _GMP_EQUAL_INT_133_133 ,
#define _GMP_EQUAL_INT_134_134 ,
#define _GMP_EQUAL_INT_135_135 ,
#define _GMP_EQUAL_INT_136_136 ,
#define _GMP_EQUAL_INT_137_137 ,
#define _GMP_EQUAL_INT_138_138 ,
#define _GMP_EQUAL_INT_139_139 ,
#define _GMP_EQUAL_INT_140_140 ,
#define _GMP_EQUAL_INT_141_141 ,
#define _GMP_EQUAL_INT_142_142 ,
#define _GMP_EQUAL_INT_143_143 ,
#define _GMP_EQUAL_INT_144_144 ,
#define _GMP_EQUAL_INT_145_145 ,
#define _GMP_EQUAL_INT_146_146 ,
#define _GMP_EQUAL_INT_147_147 ,
#define _GMP_EQUAL_INT_148_148 ,
#define _GMP_EQUAL_INT_149_149 ,
#define _GMP_EQUAL_INT_150_150 ,
#define _GMP_EQUAL_INT_151_151 ,
#define _GMP_EQUAL_INT_152_152 ,
#define _GMP_EQUAL_INT_153_153 ,
#define _GMP_EQUAL_INT_154_154 ,
#define _GMP_EQUAL_INT_155_155 ,
#define _GMP_EQUAL_INT_156_156 ,
#define _GMP_EQUAL_INT_157_157 ,
#define _GMP_EQUAL_INT_158_158 ,
#define _GMP_EQUAL_INT_159_159 ,
#define _GMP_EQUAL_INT_160_160 ,
#define _GMP_EQUAL_INT_161_161 ,
#define _GMP_EQUAL_INT_162_162 ,
#define _GMP_EQUAL_INT_163_163 ,
#define _GMP_EQUAL_INT_164_164 ,
#define _GMP_EQUAL_INT_165_165 ,
#define _GMP_EQUAL_INT_166_166 ,
#define _GMP_EQUAL_INT_167_167 ,
#define _GMP_EQUAL_INT_168_168 ,
#define _GMP_EQUAL_INT_169_169 ,
#define _GMP_EQUAL_INT_170_170 ,
#define _GMP_EQUAL_INT_171_171 ,
#define _GMP_EQUAL_INT_172_172 ,
#define _GMP_EQUAL_INT_173_173 ,
#define _GMP_EQUAL_INT_174_174 ,
#define _GMP_EQUAL_INT_175_175 ,
#define _GMP_EQUAL_INT_176_176 ,
#define _GMP_EQUAL_INT_177_177 ,
#define _GMP_EQUAL_INT_178_178 ,
#define _GMP_EQUAL_INT_179_179 ,
#define _GMP_EQUAL_INT_180_180 ,
#define _GMP_EQUAL_INT_181_181 ,
#define _GMP_EQUAL_INT_182_182 ,
#define _GMP_EQUAL_INT_183_183 ,
#define _GMP_EQUAL_INT_184_184 ,
#define _GMP_EQUAL_INT_185_185 ,
#define _GMP_EQUAL_INT_186_186 ,
#define _GMP_EQUAL_INT_187_187 ,
#define _GMP_EQUAL_INT_188_188 ,
#define _GMP_EQUAL_INT_189_189 ,
#define _GMP_EQUAL_INT_190_190 ,
#define _GMP_EQUAL_INT_191_191 ,
#define _GMP_EQUAL_INT_192_192 ,
#define _GMP_EQUAL_INT_193_193 ,
#define _GMP_EQUAL_INT_194_194 ,
#define _GMP_EQUAL_INT_195_195 ,
#define _GMP_EQUAL_INT_196_196 ,
#define _GMP_EQUAL_INT_197_197 ,
#define _GMP_EQUAL_INT_198_198 ,
#define _GMP_EQUAL_INT_199_199 ,
#define _GMP_EQUAL_INT_200_200 ,
#define _GMP_EQUAL_INT_201_201 ,
#define _GMP_EQUAL_INT_202_202 ,
#define _GMP_EQUAL_INT_203_203 ,
#define _GMP_EQUAL_INT_204_204 ,
#define _GMP_EQUAL_INT_205_205 ,
#define _GMP_EQUAL_INT_206_206 ,
#define _GMP_EQUAL_INT_207_207 ,
#define _GMP_EQUAL_INT_208_208 ,
#define _GMP_EQUAL_INT_209_209 ,
#define _GMP_EQUAL_INT_210_210 ,
#define _GMP_EQUAL_INT_211_211 ,
#define _GMP_EQUAL_INT_212_212 ,
#define _GMP_EQUAL_INT_213_213 ,
#define _GMP_EQUAL_INT_214_214 ,
#define _GMP_EQUAL_INT_215_215 ,
#define _GMP_EQUAL_INT_216_216 ,
#define _GMP_EQUAL_INT_217_217 ,
#define _GMP_EQUAL_INT_218_218 ,
#define _GMP_EQUAL_INT_219_219 ,
#define _GMP_EQUAL_INT_220_220 ,
#define _GMP_EQUAL_INT_221_221 ,
#define _GMP_EQUAL_INT_222_222 ,
#define _GMP_EQUAL_INT_223_223 ,
#define _GMP_EQUAL_INT_224_224 ,
#define _GMP_EQUAL_INT_225_225 ,
#define _GMP_EQUAL_INT_226_226 ,
#define _GMP_EQUAL_INT_227_227 ,
#define _GMP_EQUAL_INT_228_228 ,
#define _GMP_EQUAL_INT_229_229 ,
#define _GMP_EQUAL_INT_230_230 ,
#define _GMP_EQUAL_INT_231_231 ,
#define _GMP_EQUAL_INT_232_232 ,
#define _GMP_EQUAL_INT_233_233 ,
#define _GMP_EQUAL_INT_234_234 ,
#define _GMP_EQUAL_INT_235_235 ,
#define _GMP_EQUAL_INT_236_236 ,
#define _GMP_EQUAL_INT_237_237 ,
#define _GMP_EQUAL_INT_238_238 ,
#define _GMP_EQUAL_INT_239_239 ,
#define _GMP_EQUAL_INT_240_240 ,
#define _GMP_EQUAL_INT_241_241 ,
#define _GMP_EQUAL_INT_242_242 ,
#define _GMP_EQUAL_INT_243_243 ,
#define _GMP_EQUAL_INT_244_244 ,
#define _GMP_EQUAL_INT_245_245 ,
#define _GMP_EQUAL_INT_246_246 ,
#define _GMP_EQUAL_INT_247_247 ,
#define _GMP_EQUAL_INT_248_248 ,
#define _GMP_EQUAL_INT_249_249 ,
#define _GMP_EQUAL_INT_250_250 ,
#define _GMP_EQUAL_INT_251_251 ,
#define _GMP_EQUAL_INT_252_252 ,
#define _GMP_EQUAL_INT_253_253 ,
#define _GMP_EQUAL_INT_254_254 ,

/**
 * \brief Macro that expands to nothing.
 *
 * This macro expands to nothing and is used to assist other macros in achieving specific
 * functionalities, such as delayed expansion or conditional compilation.
 *
 * \return This macro does not return any value or generate any output.
 */
#define GMP_EMPTY()

/**
 * \brief Macro to defer the expansion of another macro.
 *
 * This macro is used to defer the expansion of the given macro \a id by inserting 
 * an additional layer of indirection. This can be useful in certain macro programming 
 * scenarios where immediate expansion of a macro needs to be prevented.
 *
 * \param id The macro to be deferred.
 * \return This macro does not return any value. It simply defers the expansion of \a id.
 * 
 * \par Example
 * \code
 * #define Bar() 1
 * Bar() // Expands to: 1
 * GMP_DEFER(Bar)() // Expands to: Bar()
 * \endcode
 */
#define GMP_DEFER(id) id GMP_EMPTY()


#define GMP_EVAL(...) GMP_EVAL_1(GMP_EVAL_1(GMP_EVAL_1(__VA_ARGS__)))
#define GMP_EVAL_1(...) GMP_EVAL_2(GMP_EVAL_2(GMP_EVAL_2(__VA_ARGS__)))
#define GMP_EVAL_2(...) GMP_EVAL_3(GMP_EVAL_3(GMP_EVAL_3(__VA_ARGS__)))
#define GMP_EVAL_3(...) GMP_EVAL_4(GMP_EVAL_4(GMP_EVAL_4(__VA_ARGS__)))
#define GMP_EVAL_4(...) GMP_EVAL_5(GMP_EVAL_5(GMP_EVAL_5(__VA_ARGS__)))
#define GMP_EVAL_5(...) __VA_ARGS__

/**
 * \brief Macro to generate a sequence of numbers from \a begin to \a end.
 *
 * This macro generates a sequence of numbers starting from \a begin and ending at \a end.
 * The value of \a end should not exceed \ref GMP_MAX_INT.
 *
 * \param begin The starting number of the sequence.
 * \param end The ending number of the sequence. Must be less than or equal to \ref GMP_MAX_INT.
 * \return A sequence of numbers from \a begin to \a end.
 *
 * \note The \a end value should not be greater than \ref GMP_MAX_INT.
 */
#define GMP_RANGE(begin, end) GMP_OVERLOAD_INVOKE(_GMP_RANGE_PRECHECK, GMP_CHECK_INDEX_BOOL(end))(begin, end)
#define _GMP_RANGE_PRECHECK_1(begin, end) GMP_EVAL( _GMP_RANGE_IMPL(begin, end) )
#define _GMP_RANGE_PRECHECK_0(begin, end) GMP_CHECK_INDEX(end)
#define _GMP_RANGE_IMPL(begin, end) begin GMP_OVERLOAD_INVOKE(_GMP_RANGE_GEN_WHEN, GMP_EQUAL_INT(begin, GMP_DEC(end))) (GMP_INC(begin), end)
#define _GMP_RANGE_GEN_WHEN_1(cur, end)
#define _GMP_RANGE_GEN_WHEN_0(cur, end) , GMP_DEFER(_GMP_RANGE_INDIRECT)()(cur, end)
#define _GMP_RANGE_INDIRECT() _GMP_RANGE_IMPL


/**
 * \brief Macro to loop a function call a specified number of times.
 *
 * This macro executes the function call \a call for \a count iterations.
 * The arguments for the function call are provided by __VA_ARGS__.
 *
 * \param call The function or macro to be called in each iteration.
 * \param count The number of times the function call should be executed.
 * \param ... Additional arguments passed to each invocation of \a call.
 * 
 * \note The \a count value should not be greater than \ref GMP_MAX_INT.
 * 
 * \par Example
 * \code {.c}
 * void bar(int arg1, const char* arg2) {
 *     printf("bar %d, %s\n", arg1, arg2);
 * }
 * 
 * #define Bar(arg1, arg2) bar(arg1, arg2); 
 * GMP_LOOP(Bar, 254, 1, "arg2") // Execute bar function 254 times
 * \endcode
 * 
 */
#define GMP_LOOP(call, count, ...) GMP_OVERLOAD_INVOKE(_GMP_LOOP_PRECHECK, GMP_CHECK_INDEX_BOOL(count))(call, count, __VA_ARGS__)
#define _GMP_LOOP_PRECHECK_1(call, count, ...) GMP_EVAL( _GMP_LOOP_IMPL(call, count, __VA_ARGS__) )
#define _GMP_LOOP_PRECHECK_0(call, count, ...) GMP_CHECK_INDEX(count)
#define _GMP_LOOP_IMPL(call, count, ...) GMP_OVERLOAD_INVOKE(_GMP_LOOP_IMPL_END, GMP_EQUAL_INT(0, count))(call, count, __VA_ARGS__)
#define _GMP_LOOP_IMPL_END_1(call, count, ...)
#define _GMP_LOOP_IMPL_END_0(call, count, ...) call(__VA_ARGS__) GMP_DEFER(_GMP_LOOP_INDIRECT)()(call, GMP_DEC(count), __VA_ARGS__)
#define _GMP_LOOP_INDIRECT() _GMP_LOOP_IMPL


#endif // GMP_MACRO_HPP_