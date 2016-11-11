//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_OPENGL_HPP
#define __VIKR_OPENGL_HPP

// This should be implemented first!
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <platform/vikr_api.hpp>
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
VIKR_FORCEINLINE void CreateVertexBufferObject(GLuint* vbo) { glGenBuffers(1, vbo); }
VIKR_FORCEINLINE void CreateVertexArrayObject(GLuint* vao) { glGenVertexArrays(1, vao); }
VIKR_FORCEINLINE void BufferArrays(GLenum target, GLsizei size, GLint *obj, GLenum usage) { glBufferData(target, size, obj, usage); }
VIKR_FORCEINLINE void BindBuffer(GLenum target, GLuint vbo) { glBindBuffer(target, vbo); }
VIKR_FORCEINLINE void BindVertexArray(GLuint vao) { glBindVertexArray(vao); }
VIKR_FORCEINLINE void EnableVertexAttribArray(GLuint i) { glEnableVertexAttribArray(i); }


VIKR_FORCEINLINE void BufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage) {
  glBufferData(target, size, data, usage);
}

VIKR_FORCEINLINE void VertexAttribPointer(GLuint i,
                                           GLint size, 
                                           GLenum type, 
                                           GLboolean normalized, 
                                           GLsizei stride, 
                                           const void *pointer) 
{  
  glVertexAttribPointer(i, size, type, normalized, stride, pointer);
}

VIKR_FORCEINLINE GLint GetUniformLocation(GLuint program, const char *uniform_name) { return glGetUniformLocation(program, uniform_name); }
VIKR_FORCEINLINE void Uniform1i(GLuint uniform, GLint var) { glUniform1i(uniform, var); }

VIKR_FORCEINLINE GLuint CreateShader(GLenum shader_type) { return glCreateShader(shader_type); }
VIKR_FORCEINLINE void ShaderSource(GLuint source, GLsizei count, const GLchar *const *string, GLint *length) {
  glShaderSource(source, count, string, length);
}

VIKR_FORCEINLINE void CompileShader(GLuint shader) { glCompileShader(shader); }
VIKR_FORCEINLINE void GetShaderiv(GLuint shader, GLenum status, GLint *success) { glGetShaderiv(shader, status, success); }

VIKR_FORCEINLINE void GetShaderInfoLog(GLuint shader, GLsizei log_size, GLsizei *length, GLchar *infolog) {
  glGetShaderInfoLog(shader, log_size, length, infolog); 
}

VIKR_FORCEINLINE void UseProgram(GLuint program) { glUseProgram(program); }
VIKR_FORCEINLINE GLuint CreateProgram() { return glCreateProgram(); }
#endif // __VIKR_OPENGL_HPP