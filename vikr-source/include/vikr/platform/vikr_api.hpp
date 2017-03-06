//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_API_HPP
#define __VIKR_API_HPP


#include "platform.hpp"


#if defined(VIKR_WINDOWS)
 #include <Windows.h>
 #if defined(_MSC_VER)
  #define VIKR_FORCEINLINE __forceinline
  #define VIKR_ALIGN(x) __declspec(align(x))
 #endif
#elif defined(VIKR_LINUX)
 #if defined(__GNUC__) || defined(__GNUG__)
  #define VIKR_FORCEINLINE __inline __attribute__((always_inline))
  #define VIKR_ALIGN(x) __attribute__((aligned(x)))
 #endif 
#else
 #define VIKR_FORCEINLINE
 #define VIKR_ALIGN(x)
#endif // VIKR_WINDOWS


#define VIKR_DISALLOW_COPY_AND_ASSIGN(class_name) \
                  class_name(class_name& obj) = delete; \
                  class_name& operator=(class_name& obj) = delete

#define VIKR_DEFAULT_MOVE_AND_ASSIGN(class_name) \
                  class_name(class_name &&obj) = default; \
                  class_name &operator=(class_name &&obj) = default


#define VIKR_ABSTRACT
#define VIKR_INTERFACE
#define VIKR_ABSTRACT_CLASS class
#define VIKR_INTERFACE_CLASS class


namespace vikr {


} // vikr
#endif // __VIKR_API_HPP