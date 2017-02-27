//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GL4_VERTEX_BUFFER_HPP
#define __VIKR_GL4_VERTEX_BUFFER_HPP


#include <vikr/graphics/vertexbuffer.hpp>
#include <vikr/util/vikr_assert.hpp>


namespace vikr {


/**
  OpenGL Vertexbuffer, for storing vertex data to send. 
*/
class GL4Vertexbuffer : public Vertexbuffer {
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(GL4Vertexbuffer);
  GL4Vertexbuffer()
  { }

  vuint64 GetVertexBufferId() override { return static_cast<vuint64>(m_vbo); }
  vvoid StoreVertexBufferId(vuint64 vbo) override { m_vbo = static_cast<vuint32>(vbo); }
  
  vvoid StoreVertexArrayId(vuint64 vao) { m_vao = static_cast<vuint32>(vao); }
  vuint64 GetVertexArrayId() { return m_vao; }

  vuint64 GetElementBufferId() override { return static_cast<vuint64>(m_ibo); }
  vvoid StoreElementBufferId(vuint64 ibo) override { m_ibo = static_cast<vuint32>(ibo); }

  vvoid BufferSubData(vint32 offset, vuint32 size, vvoid *data) override {
    // subdata for dynamic stuff.
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
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

  vuint32 m_vbo   = 0;
  vuint32 m_vao   = 0;
  vuint32 m_ibo   = 0;

  VIKR_DISALLOW_COPY_AND_ASSIGN(GL4Vertexbuffer);
};
} // vikr
#endif // __VIKR_GL4_VERTEX_BUFFER_HPP