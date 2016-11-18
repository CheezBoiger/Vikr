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
 #if defined(__GNUC__) || defined(__GNUG__)
  #define VIKR_FORCEINLINE __inline __attribute__((always_inline))
 #endif 
#else
 #define VIKR_FORCEINLINE
#endif // VIKR_WINDOWS


#define VIKR_DISALLOW_COPY_AND_ASSIGN(class_name) \
                  class_name(class_name& obj) = delete; \
                  class_name& operator=(class_name& obj) = delete; 

namespace vikr {



} // vikr
#endif // __VIKR_API_HPP