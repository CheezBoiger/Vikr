//
// Copyright(c) Mario Garcia. Under the MIT License.
// 
#ifndef __VIKR_IMESH_HPP
#define __VIKR_IMESH_HPP


#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <vikr/graphics/graphics_config.hpp>
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
class IMesh : public GUID {
public:
  IMesh() { }
  virtual ~IMesh() { }

  virtual vvoid Build(RenderDevice *device,
    VertexUsageType type, std::vector<Vertex> &vertices,
    std::vector<vuint32> &indices = std::vector<vuint32>()) = 0;

  virtual Vertexbuffer *GetVertexBuffer() = 0;
  virtual GraphicsPipeline GetRenderType() = 0;
  virtual vbool IsDirty() = 0;

  virtual vuint32 GetNumOfVertices() = 0;
  virtual vuint32 GetNumOfIndices() = 0;
};
} // vikr
#endif // __VIKR_IMESH_HPP