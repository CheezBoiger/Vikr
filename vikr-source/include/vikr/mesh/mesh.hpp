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

  VIKR_DEFAULT_MOVE_AND_ASSIGN(Mesh);
  /**
    This must be abstracted. Builds the Mesh object based on The type of Renderer.
  */
  virtual vvoid Build(RenderDevice *device) override;
  /**
    Inputs the vertex data to the Mesh object. 
  */
  vvoid Buffer(
    std::vector<glm::vec3> &positions, 
    std::vector<glm::vec3> &normals,
    std::vector<glm::vec2> &uvs,
    std::vector<vuint32> &indices = std::vector<vuint32>(),
    std::vector<glm::vec3> &tangents = std::vector<glm::vec3>(),
    std::vector<glm::vec3> &bitangents = std::vector<glm::vec3>(),
    std::vector<glm::vec3> &colors = std::vector<glm::vec3>()) override;

  /**
    Create the object using the Vertex Object to store info into.
  */
  vvoid Buffer(
    std::vector<Vertex> &vertices,
    std::vector<vuint32> &indices = std::vector<vuint32>()) override;

  /**
    Set the name of this Mesh.
  */
  vvoid SetName(std::string name) { m_name = name; }

  /**
    Grab the Vertex Buffer Object id of this mesh.
  */
  Vertexbuffer *GetVertexBuffer() override { return m_vertexBuffer.get(); }

  /**
    Grab the type of Graphics Pipeline that this mesh is associated with.
  */
  GraphicsPipeline GetRenderType() override { return m_render_type; }
 
  /**
    Grabe the Vertices inside this Mesh. This is a container holding vertices
    in a data oriented manner.
  */
  VertexContainer &GetVertices() override { return m_vertices; }

  /**
    Get the name of the Mesh object.
  */
  std::string GetName() { return m_name; }

  /**
    Unique Identification number for the mesh.
  */
  guid_t GetGUID() override { return guid; }

  /**
    For animation purposes. Dirty values are checked in case the mesh needs to
    update other components.
  */
  vbool IsDirty() override { return is_dirty; }

private:

  std::string m_name;
  GraphicsPipeline m_render_type;
  std::unique_ptr<Vertexbuffer> m_vertexBuffer;
  vbool is_transparent                  = false;
  vbool is_dirty                        = false;
  VertexContainer m_vertices;

  guid_t guid;
};
} // vikr
#endif // __VIKR_MESH_HPP