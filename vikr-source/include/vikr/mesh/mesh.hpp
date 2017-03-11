//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_MESH_HPP
#define __VIKR_MESH_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <vikr/graphics/vertexbuffer.hpp>
#include <glm/vec3.hpp>
#include <vikr/mesh/imesh.hpp>

#include <string>
#include <memory>

namespace vikr {


///  OpenGL Mesh object to be used for rendering. This requires that we 
///  abstract the Mesh to be used by Specific Renderer APIs.
class Mesh : public IMesh {
  ///  Default name given to our mesh.
  static const std::string kDefaultName;
  VIKR_DISALLOW_COPY_AND_ASSIGN(Mesh);

public:
  /// Mesh Constructor.
  Mesh(GraphicsPipeline pipeline = vikr_PIPELINE_OPENGL);

  VIKR_DEFAULT_MOVE_AND_ASSIGN(Mesh);

  ///  This must be abstracted. Builds the Mesh object based on The type of Renderer.
  virtual vvoid Build(RenderDevice *device, VertexUsageType type,
    std::vector<Vertex> &vertices,
    std::vector<vuint32> &indices = std::vector<vuint32>()) override;

  ///  Set the name of this Mesh.
  vvoid SetName(std::string name) { m_name = name; }

  ///  Grab the Vertex Buffer Object id of this mesh.
  Vertexbuffer *GetVertexBuffer() override { return m_vertexBuffer; }

  ///  Grab the type of Graphics Pipeline that this mesh is associated with.
  GraphicsPipeline GetRenderType() override { return m_render_type; }

  /// Get the name of the Mesh object. This can be the same
  /// name as any other Mesh object. Their GUID is their unique
  /// id.
  std::string GetName() { return m_name; }

  ///  For animation purposes. Dirty values are checked in case the mesh needs to
  ///  update other components.
  vbool IsDirty() override { return is_dirty; }

  /// Get the number of fat vertices stored inside this mesh object.
  /// This information is contained along with the vertexbuffer object
  /// provided by the RenderDevice.
  vuint32 GetNumOfVertices() override { return m_vertices.size(); }
  vuint32 GetNumOfIndices() override { return m_indices.size(); }

private:
  std::string m_name;
  GraphicsPipeline m_render_type;
  Vertexbuffer *m_vertexBuffer;
  vbool is_transparent                  = false;
  vbool is_dirty                        = false;
  VertexUsageType m_usageType;

  std::vector<Vertex> m_vertices;
  std::vector<vuint32> m_indices;
};
} // vikr
#endif // __VIKR_MESH_HPP