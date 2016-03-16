/*------------------------------------------------------------------------
  Turf: Configurable C++ platform adapter
  Copyright (c) 2016 Jeff Preshing

  Distributed under the Simplified BSD License.
  Original location: https://github.com/preshing/turf

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the LICENSE file for more information.
------------------------------------------------------------------------*/

#ifndef TURF_C_PLATFORM_DETECT_H
#define TURF_C_PLATFORM_DETECT_H

// clang-format off

#if defined(_WIN32)
    // Win32 API
    #define TURF_COMPILER_MSVC 1
    #define TURF_TARGET_WIN32 1
    #define TURF_LONG_SIZE 4
    #ifndef TURF_HAS_STDINT
        #if _MSC_VER >= 1600
            #define TURF_HAS_STDINT 1
        #endif
    #endif
    #if defined(_M_X64)
        // x64
        #define TURF_CPU_X64 1
        #define TURF_PTR_SIZE 8
    #elif defined(_M_IX86)
        // x86
        #define TURF_CPU_X86 1
        #define TURF_PTR_SIZE 4
    #else
        #error "Unrecognized platform!"
    #endif

#elif defined(__GNUC__)
    // GCC compiler family
    #define TURF_COMPILER_GCC 1
    #ifndef TURF_HAS_STDINT
        #define TURF_HAS_STDINT 1
    #endif
    #if defined(__APPLE__)
        #define TURF_TARGET_POSIX 1
    #endif
    #if defined(__linux__)
        #define TURF_TARGET_POSIX 1
        #define TURF_KERNEL_LINUX 1
    #endif
    #if defined(__MACH__)
        // Mach kernel, eg. Apple MacOS/iOS
        #define TURF_KERNEL_MACH 1
    #endif
    #if defined(__x86_64__)
        // x64
        #define TURF_CPU_X64 1
        #if defined(__ILP32__)
            #define TURF_PTR_SIZE 4
        #else
            #define TURF_PTR_SIZE 8
        #endif
    #elif defined(__i386__)
        // x86
        #define TURF_CPU_X86 1
        #define TURF_PTR_SIZE 4
    #elif defined(__arm__)
        // ARM
        #define TURF_CPU_ARM 1
        #if defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7EM__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
            // ARMv7
            #define TURF_CPU_ARM_VERSION 7
            #define TURF_PTR_SIZE 4
        #elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6T2__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__)
            // ARMv6
            #define TURF_CPU_ARM_VERSION 6
            #define TURF_PTR_SIZE 4
        #else
            // Could support earlier ARM versions at some point using compiler barriers and swp instruction
            #error "Unrecognized ARM CPU architecture version!"
        #endif
        #if defined(__thumb__)
            // Thumb instruction set mode
            #define TURF_CPU_ARM_THUMB 1
        #endif
    #elif defined(__powerpc__) || defined(__POWERPC__) || defined(__PPC__)
        #define TURF_CPU_POWERPC 1
        #define TURF_PTR_SIZE 4  // Only 32-bit detected for now
    #else
        #error "Unrecognized target CPU!"
    #endif
    #define TURF_LONG_SIZE TURF_PTR_SIZE

#else
    #error "Unrecognized compiler!"
#endif

#endif // TURF_C_PLATFORM_DETECT_H
