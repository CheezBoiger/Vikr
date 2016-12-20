//
// Copyright(c) Mario Garcia. Under the MIT License.
// 
#ifndef __VIKR_IMESH_HPP
#define __VIKR_IMESH_HPP


#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <scene/guid_generator.hpp>
#include <mesh/vertex.hpp>
#include <glm/glm.hpp>
#include <vector>

namespace vikr {


class Material;
class RenderDevice;
class Vertexbuffer;




class IMesh {
public:
  IMesh() { }
  virtual ~IMesh() { }

  virtual vvoid Create(RenderDevice *device) = 0;

  virtual vvoid Buffer(
    std::vector<glm::vec3> positions,
    std::vector<glm::vec3> normals,
    std::vector<glm::vec2> uvs,
    std::vector<vuint32> indices,
    std::vector<glm::vec3> tangents,
    std::vector<glm::vec3> bitangents) = 0;
  
  virtual vvoid Buffer(
            std::vector<Vertex> vertices,
            std::vector<vuint32> indices = std::vector<vuint32>()) = 0;

  virtual Vertexbuffer *GetVertexBuffer() = 0;
  virtual VertexUsageType GetVertexUsageType() = 0;
  virtual GraphicsPipeline GetRenderType() = 0;

  virtual guid_t GetGUID() = 0;
};
} // vikr
#endif // __VIKR_IMESH_HPP