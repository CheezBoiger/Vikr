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
    : Vertexbuffer()
  { }

  vuint32 GetVertexBufferId() override { return m_vbo; }
  vvoid StoreVertexBufferId(vuint32 vbo) override { m_vbo = vbo; }
  
  vvoid StoreVertexArrayId(vuint32 vao) { m_vao = vao; }
  vuint32 GetVertexArrayId() { return m_vao; }

  vuint32 GetElementBufferId() override { return m_ibo; }
  vvoid StoreElementBufferId(vuint32 ibo) override { m_ibo = ibo; }

  vvoid BufferSubData(vint32 offset, vuint32 size, vvoid *data) override {
    // subdata for dynamic stuff.
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    VIKR_ASSERT(glGetError() == 0);
  }

private:

  vuint32 m_vbo   = 0;
  vuint32 m_vao   = 0;
  vuint32 m_ibo   = 0;

  VIKR_DISALLOW_COPY_AND_ASSIGN(GL4Vertexbuffer);
};
} // vikr
#endif // __VIKR_GL4_VERTEX_BUFFER_HPP