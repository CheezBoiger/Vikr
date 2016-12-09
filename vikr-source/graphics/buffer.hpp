//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VERTEX_BUFFER_HPP
#define __VIKR_VERTEX_BUFFER_HPP


#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>


namespace vikr {


/**
  VertexBuffers are buffers that contain information to sent to the 
  render for use in drawing and whatnot.
*/
class VertexBuffer {
  VIKR_DISALLOW_COPY_AND_ASSIGN(VertexBuffer);
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(VertexBuffer);
  VertexBuffer() { }
  virtual ~VertexBuffer() { }

  /**
    Get the Vertex Buffer id.
  */
  virtual vuint32 GetVertexBufferId() = 0;

  /**
    Store a vertex buffer id into this VertexBuffer
  */
  virtual vvoid StoreVertexBufferId(vuint32 vbo) = 0;
};
} // vikr
#endif // __VIKR_VERTEX_BUFFER_HPP