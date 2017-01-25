//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VERTEX_BUFFER_HPP
#define __VIKR_VERTEX_BUFFER_HPP


#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>


namespace vikr {


/**
  VertexBuffers are buffers that contain information to sent to the 
  render for use in drawing and whatnot.
*/
class Vertexbuffer {
  VIKR_DISALLOW_COPY_AND_ASSIGN(Vertexbuffer);
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(Vertexbuffer);
  Vertexbuffer() { }
  virtual ~Vertexbuffer() { }

  /**
    Get the Vertex Buffer id.
  */
  virtual vuint32 GetVertexBufferId() = 0;

  /**
    Store a vertex buffer id into this VertexBuffer
  */
  virtual vvoid StoreVertexBufferId(vuint32 vbo) = 0;

  virtual vuint32 GetElementBufferId() = 0;

  virtual vvoid StoreElementBufferId(vuint32 ibo) = 0;

  virtual vvoid BufferSubData(vint32 offset, vuint32 size, vvoid *data) = 0;

};
} // vikr
#endif // __VIKR_VERTEX_BUFFER_HPP