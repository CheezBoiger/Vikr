//
// Copyright (c) Mario Garcia under the MIT License.
// 
#ifndef __VIKR_TYPES_HPP
#define __VIKR_TYPES_HPP

#include <platform/graphics/graphics.hpp>
#include <platform/platform.hpp>

namespace vikr {
 

#if defined (VIKR_OPENGL)

typedef GLfloat     vreal32;
typedef GLdouble    vreal64;
typedef GLint       vint32;
typedef GLuint      vuint32;
typedef GLshort     vint16;
typedef GLvoid      vvoid;
typedef GLboolean vbool;
typedef GLchar vchar;

// vulkan defines. Maybe
#else

typedef float vreal32;
typedef double vreal64;
typedef int vint32;
typedef unsigned int vuint32;
typedef short vint16;
typedef void vvoid;
typedef bool vbool;
typedef char vchar;

#endif // VIKR_OPENGL

typedef unsigned long long     vuint64;
typedef long long   vint64;
typedef unsigned char vbyte;
} // vikr
#endif // __VIKR_TYPES_HPP