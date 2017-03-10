//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VERTEX_BUFFER_HPP
#define __VIKR_VERTEX_BUFFER_HPP


#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <vikr/scene/guid_generator.hpp>
#include <vikr/mesh/vertex.hpp>


namespace vikr {


/**
  VertexBuffers are buffers that contain information to sent to the 
  render for use in drawing and whatnot.

  Vertex buffers are organized into batches of the same variables
  ( in a [VVVNNNUUU] format ), within one buffer. This allows for quick
  rendering and fast lookup for the gpu, instead of using multiple vertex
  buffers to handle information:

  One VBO:
  ___________________________________________________
  |    P    |    N    |    U    |    T    |    B    |
  |_________|_________|_________|_________|_________|

  Where:
    P = position
    N = normal
    U = uvs
    T = tangent
    B = bitangent

  Organization:

  |-----P-----||-----N-----||---U---||-----T-----||-----B-----|
  [x|y|z|x|y|z][x|y|z|x|y|z][x|y|x|y][x|y|z|x|y|z][x|y|z|x|y|z]


  This does depend on the manufacturer though. AMD gpus are differently
  implemented than Nvidia gpus.  
*/
class Vertexbuffer : public GUID {
  VIKR_DISALLOW_COPY_AND_ASSIGN(Vertexbuffer);
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(Vertexbuffer);
  Vertexbuffer() { }
  virtual ~Vertexbuffer() { }

  /**
    For meshes that require text.
  */
  virtual vvoid BufferData(VertexUsageType type, vuint32 size, vvoid *data) = 0;

  virtual vvoid Cleanup() = 0;
};
} // vikr
#endif // __VIKR_VERTEX_BUFFER_HPP