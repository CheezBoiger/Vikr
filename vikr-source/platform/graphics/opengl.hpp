//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_OPENGL_HPP
#define __VIKR_OPENGL_HPP

// This should be implemented first!
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <platform/platform.hpp>

#define VIKR_OPENGL

#define VIKR_OPENGL_VERSION_STRUCT gladGLversionStruct
#define VIKR_OPENGL_VERSION        GLVersion
#define VIKR_OPENGL_VERSION_MINOR  VIKR_OPENGL_VERSION.minor
#define VIKR_OPENGL_VERSION_MAJOR  VIKR_OPENGL_VERSION.major

/*
  Still working on this, time consuming I know, but wraps the library for when we 
  need to update OpenGL.
*/
void VikrCreateVertexBufferObject(GLuint* vbo);
void VikrCreateVertexArrayObject(GLuint* vao);

void VikrGetUniformLocation(GLuint program, const char *uniform_name);

#endif // __VIKR_OPENGL_HPP