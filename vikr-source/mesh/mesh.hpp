//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_MESH_HPP
#define __VIKR_MESH_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <graphics/buffer.hpp>
#include <glm/vec3.hpp>
#include <mesh/imesh.hpp>
#include <string>

namespace vikr {


/**
  OpenGL Mesh object to be used for rendering. This requires that we 
  abstract the Mesh to be used by Specific Renderer APIs.
*/
class Mesh : public IMesh {
  /**
    Default name given to our mesh.
  */
  static const std::string kDefaultName;
  VIKR_DISALLOW_COPY_AND_ASSIGN(Mesh);
public:
  Mesh(GraphicsPipeline pipeline = vikr_PIPELINE_OPENGL);
  Mesh(GraphicsPipeline pipeline,
       std::vector<glm::vec3> positions, 
       std::vector<glm::vec3> normals,
       std::vector<glm::vec2> uvs,
       std::vector<vuint32> indices = std::vector<vuint32>());

  VIKR_DEFAULT_MOVE_AND_ASSIGN(Mesh);
  /**
    This must be abstracted. Creates the Mesh object based on The type of Renderer.
  */
  virtual vvoid Create(RenderDevice *device) override;
  /**
    Inputs the vertex data to the Mesh object. 
  */
  vvoid Buffer(
    std::vector<glm::vec3> positions, 
    std::vector<glm::vec3> normals,
    std::vector<glm::vec2> uvs,
    std::vector<vuint32> indices = std::vector<vuint32>()) override;

  /**
    Create the object using the Vertex Object to store info into.
  */
  vvoid Buffer(
    std::vector<Vertex> vertices,
    std::vector<vuint32> indices = std::vector<vuint32>()) override;

  /**
    Set the name of this Mesh.
  */
  vvoid SetName(std::string name) { m_name = name; }

  /**
    Grab the Vertex Buffer Object id of this mesh.
  */
  VertexBuffer *GetVertexBuffer() override { return m_vertexBuffer.get(); }
  /**
    Grab the Element Buffer Object id of this mesh. Currently only supporting
    drawing of VBOs instead of EBOs.
  */
  vuint32 GetIndexBufferId() override { return m_ibo; }

  /**
    Grab the type of Graphics Pipeline that this mesh is associated with.
  */
  GraphicsPipeline GetRenderType() override { return m_render_type; } 
  /**
    Grab our vertices? TODO(Garcia): This is kind of stupid... lulz.
  */
  std::vector<Vertex>& GetVertices() { return m_vertices; }
  /**
    Get the name of the Mesh object.
  */
  std::string GetName() { return m_name; }
  /**
    Get the usage type.
  */
  VertexUsageType GetVertexUsageType() override { return m_usage_type; };

protected:

  std::string m_name;
  GraphicsPipeline m_render_type;
  std::unique_ptr<VertexBuffer> m_vertexBuffer;
  vuint32 m_ibo;
  vbool is_transparent                  = false;
  VertexUsageType m_usage_type          = vikr_STATIC;

  std::vector<Vertex> m_vertices;
  std::vector<vuint32> m_indices;
};
} // vikr
#endif // __VIKR_MESH_HPP