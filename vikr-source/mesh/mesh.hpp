//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_MESH_HPP
#define __VIKR_MESH_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <renderer/mesh_command.hpp>
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
  Mesh();
  Mesh(std::vector<glm::vec3> positions, 
       std::vector<glm::vec3> normals,
       std::vector<glm::vec2> uvs,
       std::vector<vuint32> indices = std::vector<vuint32>(),
       MeshDrawMode draw_mode = vikr_TRIANGLES);

  VIKR_DEFAULT_MOVE_AND_ASSIGN(Mesh);
  /**
    This must be abstracted. Creates the Mesh object based on The type of Renderer.
  */
  vvoid Create() override;
  /**
    Inputs the vertex data to the Mesh object. 
  */
  vvoid Create(std::vector<glm::vec3> positions, 
               std::vector<glm::vec3> normals,
               std::vector<glm::vec2> uvs,
               std::vector<vuint32> indices = std::vector<vuint32>(), 
               MeshDrawMode draw_mode = vikr_TRIANGLES) override;

  /**
    Create the object using the Vertex Object to store info into.
  */
  vvoid Create(std::vector<Vertex> vertices, MeshDrawMode draw_mode = vikr_TRIANGLES) override;
  /**
    Set the name of this Mesh.
  */
  vvoid SetName(std::string name) { m_name = name; }
  /**
    Grab the Vertex Array Object id of this mesh.
  */
  vuint32 GetVAO() override { return m_vao; }
  /**
    Grab the Vertex Buffer Object id of this mesh.
  */
  vuint32 GetVBO() override { return m_vbo; }
  /**
    Grab the Element Buffer Object id of this mesh. Currently only supporting
    drawing of VBOs instead of EBOs.
  */
  vuint32 GetEBO() override { return m_ebo; }
  /**
    Grab the mesh mode of this Mesh object. In other words, grabs the topology
    of how this mesh is supposed to be drawn with... (eg. Triangles, TriangleStrip?).
  */
  MeshDrawMode GetMeshMode() override { return m_mode; }
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

protected:
  std::string m_name;
  MeshDrawMode m_mode;
  GraphicsPipeline m_render_type;
  vuint32 m_vao;
  vuint32 m_vbo;
  vuint32 m_ebo;
  vbool is_transparent;

  std::vector<Vertex> m_vertices;
  std::vector<vuint32> m_indices;
};
} // vikr
#endif // __VIKR_MESH_HPP