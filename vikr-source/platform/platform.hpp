//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_PLATFORM_HPP
#define __VIKR_PLATFORM_HPP

/*
  OS declarations in case they need to be used.
*/
#if defined(_WIN32) || defined(__WIN32__) || defined(_MSC_VER)
 #define VIKR_WINDOWS
 #define VIKR_WIN32
#elif defined(__linux__) || defined(__POSIX__)
 #define VIKR_LINUX
 #define VIKR_POSIX
#elif defined(__APPLE__) && defined(__MACH__)
 #define VIKR_APPLE
 #define VIKR_MACH
#else
 #error "Your operating system is not supported, please try one of the compatible operating systems (Windows/Apple/Linux)"
#endif // defined(_WIN32)
#endif // __VIKR_PLATFORM_HPP