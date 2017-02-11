//
// Copyright(c) Mario Garcia. Under the MIT License.
// 
#ifndef __VIKR_IMESH_HPP
#define __VIKR_IMESH_HPP


#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <vikr/scene/guid_generator.hpp>
#include <vikr/mesh/vertex.hpp>
#include <glm/glm.hpp>
#include <vector>

namespace vikr {


class Material;
class RenderDevice;
class Vertexbuffer;



/**
  Mesh Interface. Used for abstracting meshes if new meshes need to be created.
*/
class IMesh {
public:
  IMesh() { }
  virtual ~IMesh() { }

  virtual vvoid Build(RenderDevice *device) = 0;

  virtual vvoid Buffer(
    std::vector<glm::vec3> positions,
    std::vector<glm::vec3> normals,
    std::vector<glm::vec2> uvs,
    std::vector<vuint32> indices,
    std::vector<glm::vec3> tangents,
    std::vector<glm::vec3> bitangents,
    std::vector<glm::vec3> colors) = 0;
  
  virtual vvoid Buffer(
            std::vector<Vertex> vertices,
            std::vector<vuint32> indices = std::vector<vuint32>()) = 0;

  virtual Vertexbuffer *GetVertexBuffer() = 0;
  virtual GraphicsPipeline GetRenderType() = 0;
  virtual VertexContainer &GetVertices() = 0;
  virtual vbool IsDirty() = 0;

  virtual guid_t GetGUID() = 0;
};
} // vikr
#endif // __VIKR_IMESH_HPP