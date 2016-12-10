//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_ASSERT_HPP
#define __VIKR_ASSERT_HPP

#include <platform/platform.hpp>
#include <cassert>
#include <cstdio>

#if defined(VIKR_LINUX)
 #include <csignal>
#endif // VIKR_LINUX


#if defined(VIKR_DEBUG_ENABLED)
 #define VIKR_DEBUG(stmnt, ...) std::printf(stmnt, ##__VA_ARGS__)
 #if defined(VIKR_WINDOWS)
  #define VIKR_DEBUG_BREAK() __asm { int 3 }
 #elif defined(VIKR_LINUX)
  #define VIKR_DEBUG_BREAK() raise(SIGTRAP)
 #else
  #define VIKR_DEBUG_BREAK()
 #endif // VIKR_WINDOWS
 #define VIKR_ASSERT(expr) assert(expr)
 #define VIKR_ASSERT_MSG(expr, msg) assert(expr && msg)
 #define VIKR_ASSERTION(expr) do { \
           if ((expr)) { } \
           else { \
            VIKR_DEBUG("ASSERTION ERROR: %s\nFILE: %s\nLine: %d\n", #expr, __FILE__, __LINE__); \
            VIKR_DEBUG_BREAK(); \
           } \
         } while (0)
#else
 #define VIKR_DEBUG(stmnt, ...)
 #define VIKR_DEBUG_BREAK()
 #define VIKR_ASSERT(expr)
 #define VIKR_ASSERT_MSG(expr, msg)
 #define VIKR_ASSERTION(expr)
#endif // VIKR_ASSERT_ENABLED
#endif // __VIKR_ASSERT_HPP