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
__forceinline void CreateVertexBufferObject(GLuint* vbo) { glGenBuffers(1, vbo); }
__forceinline void CreateVertexArrayObject(GLuint* vao) { glGenVertexArrays(1, vao); }
__forceinline void BufferArrays(GLenum target, GLsizei size, GLint *obj, GLenum usage) { glBufferData(target, size, obj, usage); }
__forceinline void BindBuffer(GLenum target, GLuint vbo) { glBindBuffer(target, vbo); }
__forceinline void BindVertexArray(GLuint vao) { glBindVertexArray(vao); }
__forceinline void EnableVertexAttribArray(GLuint i) { glEnableVertexAttribArray(i); }


__forceinline void BufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage) { 
  glBufferData(target, size, data, usage);
}

__forceinline void VertexAttribPointer(GLuint i, 
                                           GLint size, 
                                           GLenum type, 
                                           GLboolean normalized, 
                                           GLsizei stride, 
                                           const void *pointer) 
{  
  glVertexAttribPointer(i, size, type, normalized, stride, pointer);
}

__forceinline GLint GetUniformLocation(GLuint program, const char *uniform_name) { return glGetUniformLocation(program, uniform_name); }
__forceinline void Uniform1i(GLuint uniform, GLint var) { glUniform1i(uniform, var); }

__forceinline GLuint CreateShader(GLenum shader_type) { return glCreateShader(shader_type); }
__forceinline void ShaderSource(GLuint source, GLsizei count, const GLchar *const *string, GLint *length) {
  glShaderSource(source, count, string, length);
}

__forceinline void CompileShader(GLuint shader) { glCompileShader(shader); }
__forceinline void GetShaderiv(GLuint shader, GLenum status, GLint *success) { glGetShaderiv(shader, status, success); }

__forceinline void GetShaderInfoLog(GLuint shader, GLsizei log_size, GLsizei *length, GLchar *infolog) { 
  glGetShaderInfoLog(shader, log_size, length, infolog); 
}

__forceinline void UseProgram(GLuint program) { glUseProgram(program); }
__forceinline GLuint CreateProgram() { return glCreateProgram(); }
#endif // __VIKR_OPENGL_HPP