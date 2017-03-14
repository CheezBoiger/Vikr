//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GL4_VERTEX_BUFFER_HPP
#define __VIKR_GL4_VERTEX_BUFFER_HPP


#include <vikr/graphics/vertexbuffer.hpp>
#include <vikr/util/vikr_assert.hpp>


#include <vikr/graphics/graphics.hpp>


namespace vikr {



///  OpenGL Vertexbuffer, for storing vertex data to send. 
class GL4Vertexbuffer : public Vertexbuffer {
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(GL4Vertexbuffer);
  GL4Vertexbuffer()
    : Vertexbuffer(vikr_API_OPENGL)
  { }

  GLuint GetVertexBufferId() { return m_vbo; }
  vvoid StoreVertexBufferId(GLuint vbo) { m_vbo = vbo; }
  
  vvoid StoreVertexArrayId(GLuint vao) { m_vao = vao; }
  GLuint GetVertexArrayId() { return m_vao; }

  GLuint GetElementBufferId() { return m_ibo; }
  vvoid StoreElementBufferId(GLuint ibo) { m_ibo = ibo; }

  vvoid BufferData(VertexUsageType type, vuint32 size, Vertex *data) override {
    // Change the entire data buffer for dynamic stuff.
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, size, data, (type == vikr_DYNAMIC ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    VIKR_ASSERT(glGetError() == 0);
  }

  vvoid Cleanup() override {
    if (m_vbo) {
      glDeleteBuffers(1, &m_vbo); 
    }
    if (m_ibo) {
      glDeleteBuffers(1, &m_ibo);
    }

    if (m_vao) {
      glDeleteVertexArrays(1, &m_vao);
    }
  }

private:

  GLuint m_vbo   = 0;
  GLuint m_vao   = 0;
  GLuint m_ibo   = 0;

  VIKR_DISALLOW_COPY_AND_ASSIGN(GL4Vertexbuffer);
};
} // vikr
#endif // __VIKR_GL4_VERTEX_BUFFER_HPP