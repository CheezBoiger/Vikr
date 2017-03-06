//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_OPENGL_HPP
#define __VIKR_OPENGL_HPP

// This should be implemented first!
#include <vikr/glad/glad.h>


#include <vikr/platform/vikr_api.hpp>
#include <vikr/platform/platform.hpp>

#define VIKR_OPENGL

#define VIKR_OPENGL_VERSION_STRUCT      gladGLversionStruct
#define VIKR_OPENGL_VERSION             GLVersion
#define VIKR_OPENGL_VERSION_MINOR       VIKR_OPENGL_VERSION.minor
#define VIKR_OPENGL_VERSION_MAJOR       VIKR_OPENGL_VERSION.major
#define VIKR_DEPTH24_STENCIL8           GL_DEPTH24_STENCIL8
// NVidia's way of handling mem.
#define GL_TOTAL_MEM_AVAILABLE_NVX      0x9048
#define GL_CURRENT_MEM_AVAILABLE_NVX    0x9049


namespace vikr {


/*
  Still working on this, time consuming I know, but wraps the library for when we 
  need to update OpenGL.
*/
VIKR_FORCEINLINE void CreateVertexBufferObject(GLuint* vbo) { glGenBuffers(1, vbo); }
VIKR_FORCEINLINE void GenBuffers(GLsizei n, GLuint *buffer) { glGenBuffers(n, buffer); }
VIKR_FORCEINLINE void CreateVertexArrayObject(GLuint* vao) { glGenVertexArrays(1, vao); }
VIKR_FORCEINLINE void GenVertexArrays(GLsizei n, GLuint *vao) { glGenVertexArrays(n, vao); }
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

VIKR_FORCEINLINE void GetActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei *length, GLint *size, GLenum *type, GLchar *name) { 
  glGetActiveUniform(program, index, bufsize, length, size, type, name); 
}

VIKR_FORCEINLINE GLuint GetUniformLocation(GLuint program, const char *uniform_name) { return glGetUniformLocation(program, uniform_name); }
VIKR_FORCEINLINE void Uniform1i(GLuint uniform, GLint var) { glUniform1i(uniform, var); }

VIKR_FORCEINLINE GLuint CreateShader(GLenum shader_type) { return glCreateShader(shader_type); }
VIKR_FORCEINLINE void ShaderSource(GLuint source, GLsizei count, const GLchar *const *string, GLint *length) {
  glShaderSource(source, count, string, length);
}

VIKR_FORCEINLINE void CompileShader(GLuint shader) { glCompileShader(shader); }
VIKR_FORCEINLINE void DeleteShader(GLuint shader) { glDeleteShader(shader); }
VIKR_FORCEINLINE void GetShaderiv(GLuint shader, GLenum status, GLint *success) { glGetShaderiv(shader, status, success); }
VIKR_FORCEINLINE void AttachShader(GLuint program, GLuint shader) { glAttachShader(program, shader); }
VIKR_FORCEINLINE void GetShaderInfoLog(GLuint shader, GLsizei log_size, GLsizei *length, GLchar *infolog) {
  glGetShaderInfoLog(shader, log_size, length, infolog); 
}

VIKR_FORCEINLINE void UseProgram(GLuint program) { glUseProgram(program); }
VIKR_FORCEINLINE GLuint CreateProgram() { return glCreateProgram(); }
VIKR_FORCEINLINE void LinkProgram(GLuint program) { glLinkProgram(program); }
VIKR_FORCEINLINE void GetProgramiv(GLuint program, GLenum pname, GLint *params) { glGetProgramiv(program, pname, params); }
VIKR_FORCEINLINE void GetProgramInfoLog(GLuint program, GLsizei size, GLsizei *length, GLchar *info_log) { 
  glGetProgramInfoLog(program, size, length, info_log); 
}

VIKR_FORCEINLINE void ClearDisplay(GLbitfield mask) { glClear(mask); }
VIKR_FORCEINLINE void ClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) { glClearColor(red, green, blue, alpha); }

VIKR_FORCEINLINE void GetActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei *length, GLint *size, GLenum *type, GLchar *name) { 
  glGetActiveAttrib(program, index, bufsize, length, size, type, name);
}

VIKR_FORCEINLINE GLuint GetAttribLocation(GLuint program, GLchar *name) { return glGetAttribLocation(program, name); }
VIKR_FORCEINLINE void UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat *value) { glUniformMatrix4fv(location, count, transpose, value); }
VIKR_FORCEINLINE void UniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, GLfloat *value) { glUniformMatrix3fv(location, count, transpose, value); }
VIKR_FORCEINLINE void UniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, GLfloat *value) { glUniformMatrix2fv(location, count, transpose, value); }
VIKR_FORCEINLINE void UniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, GLdouble *value) { glUniformMatrix2dv(location, count, transpose, value); }
VIKR_FORCEINLINE void Uniform1f(GLint location, GLfloat value) { glUniform1f(location, value); }
VIKR_FORCEINLINE void Uniform2f(GLint location, GLfloat v0, GLfloat v1) { glUniform2f(location, v0, v1); }
VIKR_FORCEINLINE void Uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) { glUniform3f(location, v0, v1, v2); }
VIKR_FORCEINLINE void Uniform1fv(GLint location, GLsizei count, const GLfloat *value) { glUniform1fv(location, count, value); }
VIKR_FORCEINLINE void Uniform2fv(GLint location, GLsizei count, const GLfloat *value) { glUniform2fv(location, count, value); }
VIKR_FORCEINLINE void Uniform3fv(GLint location, GLsizei count, const GLfloat *value) { glUniform3fv(location, count, value); }
VIKR_FORCEINLINE void Uniform4fv(GLint location, GLsizei count, const GLfloat *value) { glUniform4fv(location, count, value); } 
VIKR_FORCEINLINE void Uniform1i(GLint location, GLint value) { glUniform1i(location, value); }
VIKR_FORCEINLINE void Uniform1ui(GLint location, GLuint value) { glUniform1ui(location, value); }
VIKR_FORCEINLINE void Uniform1iv(GLint location, GLsizei count, const GLint *value) { glUniform1iv(location, count, value); }
VIKR_FORCEINLINE void Uniform1d(GLint location, GLdouble v0) { glUniform1d(location, v0); }

VIKR_FORCEINLINE void GenTextures(GLsizei n, GLuint *textures) { glGenTextures(n, textures); }
VIKR_FORCEINLINE void BindTexture(GLenum target, GLuint texture) { glBindTexture(target, texture); }
VIKR_FORCEINLINE void TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels) { 
  glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels); 
}
VIKR_FORCEINLINE void ActiveTexture(GLenum texture) { glActiveTexture(texture); }
VIKR_FORCEINLINE void GenerateMipmap(GLenum target) { glGenerateMipmap(target); }
VIKR_FORCEINLINE void TexParameteri(GLenum target, GLenum pname, GLint param) { glTexParameteri(target, pname, param); }
VIKR_FORCEINLINE void DrawArrays(GLenum mode, GLint first, GLsizei count) { glDrawArrays(mode, first, count); }

VIKR_FORCEINLINE void GLEnable(GLenum cap) { glEnable(cap); }
VIKR_FORCEINLINE void GLDisable(GLenum cap) { glDisable(cap); }
VIKR_FORCEINLINE void GLDepthFunc(GLenum func) { glDepthFunc(func); }
VIKR_FORCEINLINE void GLFrontFace(GLenum face) { glFrontFace(face); }
VIKR_FORCEINLINE void GLCullFace(GLenum face) { glCullFace(face); }
VIKR_FORCEINLINE void GLBlendFunc(GLenum sfactor, GLenum dfactor) { glBlendFunc(sfactor, dfactor); }
} // vikr
#endif // __VIKR_OPENGL_HPP