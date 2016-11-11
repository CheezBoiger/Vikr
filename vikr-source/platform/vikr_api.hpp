//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_API_HPP
#define __VIKR_API_HPP


#include "platform.hpp"



#if defined(VIKR_WINDOWS)
 #if defined(_MSC_VER)
  #define VIKR_FORCEINLINE __forceinline
 #endif
#elif defined(VIKR_LINUX)
 #if defined(__GCC__)
  #define VIKR_FORCEINLINE __inline __attribute__((always_inline))
 #endif 
#else
 #define VIKR_FORCEINLINE
#endif // VIKR_WINDOWS
namespace vikr {



} // vikr
#endif // __VIKR_API_HPP