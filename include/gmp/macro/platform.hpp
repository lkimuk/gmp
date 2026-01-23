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

/** 
 * @brief Platform detection macros.
 * 
 * Defines compile-time macros to detect the operating system.
 * Provides boolean macros for Windows, Linux, macOS, iOS and Android,
 * as well as a string macro for the platform name.
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

/**
 * @brief Platform-specific code block macros.
 * 
 * These macros allow writing platform-specific code blocks that are
 * conditionally compiled based on the target platform.
 * 
 * Usage example:
 * @code
 *   GMP_WINDOWS_ONLY({
 *       // Windows code here
 *   });
 * @endcode
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

/**
 * @brief Compiler detection macros.
 * 
 * These macros detect the compiler being used and provide version information.
 * Supports MSVC, Clang, and GCC compilers with version numbering.
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

/**
 * @brief Compiler-specific code block macros.
 * 
 * These macros allow writing compiler-specific code blocks that are
 * conditionally compiled based on the detected compiler.
 *
 * Usage example:
 * @code
 *   GMP_MSVC_ONLY({
 *       // MSVC specific code
 *   });
 * @endcode
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

/**
 * @brief Build configuration detection macros.
 * 
 * These macros detect whether the code is being compiled in debug or release mode.
 * Determined by the presence of NDEBUG or _NDEBUG preprocessor definitions.
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

/**
 * @brief Processor architecture detection macros.
 * 
 * These macros detect the CPU architecture at compile-time.
 * Supports x86, x64, and ARM64 architectures.
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

#if defined(_MSC_VER) && (!defined(_MSVC_TRADITIONAL) || _MSVC_TRADITIONAL)
    #define GMP_MAX_MACRO_ARGS 127
    #define GMP_PREPROCESSOR_TYPE "MSVC Traditional"
    #define GMP_STANDARD_PREPROCESSOR 0
#else
    #define GMP_MAX_MACRO_ARGS 256  
    #define GMP_PREPROCESSOR_TYPE "C++ Standard Compliant"
    #define GMP_STANDARD_PREPROCESSOR 1
#endif

#endif // GMP_PLATFORM_HPP_