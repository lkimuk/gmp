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

#ifndef GMP_PLATFORM_HPP_
#define GMP_PLATFORM_HPP_

/** @addtogroup macro_metaprogramming
 * @{
 */

/**
 * @name Platform Detection
 * @brief Compile-time operating system detection macros.
 *
 * These macros expose the detected target platform as boolean constants
 * and provide a human-readable platform name.
 * @{
 */
/** @def GMP_PLATFORM_WINDOWS
 * @brief Evaluate to `1` when compiling for Windows, otherwise `0`.
 * @hideinitializer
 */
/** @def GMP_PLATFORM_LINUX
 * @brief Evaluate to `1` when compiling for Linux, otherwise `0`.
 * @hideinitializer
 */
/** @def GMP_PLATFORM_MAC
 * @brief Evaluate to `1` when compiling for macOS, otherwise `0`.
 * @hideinitializer
 */
/** @def GMP_PLATFORM_IOS
 * @brief Evaluate to `1` when compiling for iOS, otherwise `0`.
 * @hideinitializer
 */
/** @def GMP_PLATFORM_ANDROID
 * @brief Evaluate to `1` when compiling for Android, otherwise `0`.
 * @hideinitializer
 */
/** @def GMP_PLATFORM_NAME
 * @brief Expand to a string literal describing the detected target platform.
 * @hideinitializer
 */
#if defined(_WIN32) || defined(_WIN64)
    #define GMP_PLATFORM_WINDOWS 1
    #define GMP_PLATFORM_LINUX 0
    #define GMP_PLATFORM_MAC 0
    #define GMP_PLATFORM_IOS 0
    #define GMP_PLATFORM_ANDROID 0
    #define GMP_PLATFORM_NAME "Windows"
#elif defined(__APPLE__) && defined(__MACH__)
    #include <TargetConditionals.h>
    #if TARGET_OS_IPHONE || TARGET_OS_SIMULATOR
        #define GMP_PLATFORM_IOS 1
        #define GMP_PLATFORM_MAC 0
        #define GMP_PLATFORM_NAME "iOS"
    #else
        #define GMP_PLATFORM_MAC 1
        #define GMP_PLATFORM_IOS 0
        #define GMP_PLATFORM_NAME "macOS"
    #endif
    #define GMP_PLATFORM_WINDOWS 0
    #define GMP_PLATFORM_LINUX 0
    #define GMP_PLATFORM_ANDROID 0
#elif defined(__linux__)
    #define GMP_PLATFORM_LINUX 1
    #define GMP_PLATFORM_WINDOWS 0
    #define GMP_PLATFORM_MAC 0
    #define GMP_PLATFORM_IOS 0
    #if defined(__ANDROID__)
        #define GMP_PLATFORM_ANDROID 1
        #define GMP_PLATFORM_NAME "Android"
    #else
        #define GMP_PLATFORM_ANDROID 0
        #define GMP_PLATFORM_NAME "Linux"
    #endif
#else
    #define GMP_PLATFORM_WINDOWS 0
    #define GMP_PLATFORM_LINUX 0
    #define GMP_PLATFORM_MAC 0
    #define GMP_PLATFORM_IOS 0
    #define GMP_PLATFORM_ANDROID 0
    #define GMP_PLATFORM_NAME "Unknown"
#endif
/** @} */

/**
 * @name Platform-Specific Code Blocks
 * @brief Conditionally include a code block for a specific platform.
 *
 * These macros expand to their argument only when the named platform is
 * active. Otherwise they expand to nothing.
 * @{
 */
/** @def GMP_WINDOWS_ONLY(code)
 * @brief Expand `code` only when compiling for Windows.
 * @param code The code block to include conditionally.
 * @hideinitializer
 */
/** @def GMP_LINUX_ONLY(code)
 * @brief Expand `code` only when compiling for Linux.
 * @param code The code block to include conditionally.
 * @hideinitializer
 */
/** @def GMP_MAC_ONLY(code)
 * @brief Expand `code` only when compiling for macOS.
 * @param code The code block to include conditionally.
 * @hideinitializer
 */
/** @def GMP_IOS_ONLY(code)
 * @brief Expand `code` only when compiling for iOS.
 * @param code The code block to include conditionally.
 * @hideinitializer
 */
/** @def GMP_ANDROID_ONLY(code)
 * @brief Expand `code` only when compiling for Android.
 * @param code The code block to include conditionally.
 * @hideinitializer
 */
#if GMP_PLATFORM_WINDOWS
    #define GMP_WINDOWS_ONLY(code) code
    #define GMP_LINUX_ONLY(code)
    #define GMP_MAC_ONLY(code)
    #define GMP_IOS_ONLY(code)
    #define GMP_ANDROID_ONLY(code)
#elif GMP_PLATFORM_LINUX
    #define GMP_WINDOWS_ONLY(code)
    #define GMP_LINUX_ONLY(code) code
    #define GMP_MAC_ONLY(code)
    #define GMP_IOS_ONLY(code)
    #if GMP_PLATFORM_ANDROID
        #define GMP_ANDROID_ONLY(code) code
    #else
        #define GMP_ANDROID_ONLY(code)
    #endif
#elif GMP_PLATFORM_MAC
    #define GMP_WINDOWS_ONLY(code)
    #define GMP_LINUX_ONLY(code)
    #define GMP_MAC_ONLY(code) code
    #define GMP_IOS_ONLY(code)
    #define GMP_ANDROID_ONLY(code)
#elif GMP_PLATFORM_IOS
    #define GMP_WINDOWS_ONLY(code)
    #define GMP_LINUX_ONLY(code)
    #define GMP_MAC_ONLY(code)
    #define GMP_IOS_ONLY(code) code
    #define GMP_ANDROID_ONLY(code)
#endif
/** @} */

/**
 * @name Compiler Detection
 * @brief Compile-time compiler detection macros.
 *
 * These macros identify the active compiler and expose a numeric version and
 * descriptive compiler name.
 * @{
 */
/** @def GMP_COMPILER_MSVC
 * @brief Evaluate to `1` when compiling with MSVC, otherwise `0`.
 * @hideinitializer
 */
/** @def GMP_COMPILER_GCC
 * @brief Evaluate to `1` when compiling with GCC, otherwise `0`.
 * @hideinitializer
 */
/** @def GMP_COMPILER_CLANG
 * @brief Evaluate to `1` when compiling with Clang, otherwise `0`.
 * @hideinitializer
 */
/** @def GMP_COMPILER_NAME
 * @brief Expand to a string literal describing the detected compiler.
 * @hideinitializer
 */
/** @def GMP_COMPILER_VERSION
 * @brief Expand to a compiler-specific numeric version value.
 * @hideinitializer
 */
#if defined(_MSC_VER)
    #define GMP_COMPILER_MSVC 1
    #define GMP_COMPILER_GCC 0
    #define GMP_COMPILER_CLANG 0
    #define GMP_COMPILER_NAME "MSVC"
    #define GMP_COMPILER_VERSION _MSC_VER
#elif defined(__clang__)
    #define GMP_COMPILER_CLANG 1
    #define GMP_COMPILER_GCC 0
    #define GMP_COMPILER_MSVC 0
    #define GMP_COMPILER_NAME "Clang"
    #define GMP_COMPILER_VERSION (__clang_major__ * 100 + __clang_minor__)
#elif defined(__GNUC__)
    #define GMP_COMPILER_GCC 1
    #define GMP_COMPILER_MSVC 0
    #define GMP_COMPILER_CLANG 0
    #define GMP_COMPILER_NAME "GCC"
    #define GMP_COMPILER_VERSION (__GNUC__ * 100 + __GNUC_MINOR__)
#else
    #define GMP_COMPILER_MSVC 0
    #define GMP_COMPILER_GCC 0
    #define GMP_COMPILER_CLANG 0
    #define GMP_COMPILER_NAME "Unknown"
    #define GMP_COMPILER_VERSION 0
#endif
/** @} */

/**
 * @name Compiler-Specific Code Blocks
 * @brief Conditionally include a code block for a specific compiler.
 * @{
 */
/** @def GMP_MSVC_ONLY(code)
 * @brief Expand `code` only when compiling with MSVC.
 * @param code The code block to include conditionally.
 * @hideinitializer
 */
/** @def GMP_GCC_ONLY(code)
 * @brief Expand `code` only when compiling with GCC.
 * @param code The code block to include conditionally.
 * @hideinitializer
 */
/** @def GMP_CLANG_ONLY(code)
 * @brief Expand `code` only when compiling with Clang.
 * @param code The code block to include conditionally.
 * @hideinitializer
 */
#if GMP_COMPILER_MSVC
    #define GMP_MSVC_ONLY(code) code
    #define GMP_GCC_ONLY(code)
    #define GMP_CLANG_ONLY(code)
#elif GMP_COMPILER_CLANG
    #define GMP_MSVC_ONLY(code)
    #define GMP_GCC_ONLY(code)
    #define GMP_CLANG_ONLY(code) code
#elif GMP_COMPILER_GCC
    #define GMP_MSVC_ONLY(code)
    #define GMP_GCC_ONLY(code) code
    #define GMP_CLANG_ONLY(code)
#endif
/** @} */

/**
 * @name Build Configuration Detection
 * @brief Detect whether the current build is a debug or release build.
 * @{
 */
/** @def GMP_BUILD_RELEASE
 * @brief Evaluate to `1` for release builds, otherwise `0`.
 * @hideinitializer
 */
/** @def GMP_BUILD_DEBUG
 * @brief Evaluate to `1` for debug builds, otherwise `0`.
 * @hideinitializer
 */
/** @def GMP_BUILD_TYPE
 * @brief Expand to a string literal describing the active build configuration.
 * @hideinitializer
 */
#if defined(NDEBUG) || defined(_NDEBUG)
    #define GMP_BUILD_RELEASE 1
    #define GMP_BUILD_DEBUG 0
    #define GMP_BUILD_TYPE "Release"
#else
    #define GMP_BUILD_DEBUG 1
    #define GMP_BUILD_RELEASE 0
    #define GMP_BUILD_TYPE "Debug"
#endif
/** @} */

/**
 * @name Architecture Detection
 * @brief Detect the target processor architecture at compile time.
 * @{
 */
/** @def GMP_ARCH_X64
 * @brief Evaluate to `1` when targeting x64, otherwise `0`.
 * @hideinitializer
 */
/** @def GMP_ARCH_ARM64
 * @brief Evaluate to `1` when targeting ARM64, otherwise `0`.
 * @hideinitializer
 */
/** @def GMP_ARCH_X86
 * @brief Evaluate to `1` when targeting x86, otherwise `0`.
 * @hideinitializer
 */
/** @def GMP_ARCH_NAME
 * @brief Expand to a string literal describing the detected architecture.
 * @hideinitializer
 */
#if defined(__x86_64__) || defined(_M_X64)
    #define GMP_ARCH_X64 1
    #define GMP_ARCH_ARM64 0
    #define GMP_ARCH_X86 0
    #define GMP_ARCH_NAME "x64"
#elif defined(__aarch64__) || defined(_M_ARM64)
    #define GMP_ARCH_ARM64 1
    #define GMP_ARCH_X64 0
    #define GMP_ARCH_X86 0
    #define GMP_ARCH_NAME "ARM64"
#elif defined(__i386__) || defined(_M_IX86)
    #define GMP_ARCH_X86 1
    #define GMP_ARCH_X64 0
    #define GMP_ARCH_ARM64 0
    #define GMP_ARCH_NAME "x86"
#else
    #define GMP_ARCH_X64 0
    #define GMP_ARCH_ARM64 0
    #define GMP_ARCH_X86 0
    #define GMP_ARCH_NAME "Unknown"
#endif
/** @} */

/**
 * @name Preprocessor Capabilities
 * @brief Describe the supported preprocessor mode and argument limits.
 * @{
 */
/** @def GMP_MAX_MACRO_ARGS
 * @brief Maximum supported variadic macro arity for the active preprocessor mode.
 * @hideinitializer
 */
/** @def GMP_PREPROCESSOR_TYPE
 * @brief Expand to a string literal describing the detected preprocessor mode.
 * @hideinitializer
 */
/** @def GMP_STANDARD_PREPROCESSOR
 * @brief Evaluate to `1` when the compiler provides a standard-conforming preprocessor.
 * @hideinitializer
 */
#if defined(_MSC_VER) && (!defined(_MSVC_TRADITIONAL) || _MSVC_TRADITIONAL)
    #define GMP_MAX_MACRO_ARGS 127
    #define GMP_PREPROCESSOR_TYPE "MSVC Traditional"
    #define GMP_STANDARD_PREPROCESSOR 0
#else
    #define GMP_MAX_MACRO_ARGS 256  
    #define GMP_PREPROCESSOR_TYPE "C++ Standard Compliant"
    #define GMP_STANDARD_PREPROCESSOR 1
#endif
/** @} */

/** @} */

#endif // GMP_PLATFORM_HPP_
