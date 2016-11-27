//
// Copyright(c) Mario Garcia. Under the MIT License.
// 
#ifndef __VIKR_IMESH_HPP
#define __VIKR_IMESH_HPP


#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <vector>

namespace vikr {


class Material;
class MeshCommand;


/*
Vertex of the mesh.
*/
struct Vertex {
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 uv;
  // for now we don't do this.
  //glm::vec3 tangent;
  //glm::vec3 bitangent;
};


enum MeshDrawMode {
  vikr_POINTS,
  vikr_LINE_STRIP,
  vikr_LINE_LOOP,
  vikr_LINES,
  vikr_TRIANGLE_STRIP,
  vikr_TRIANGLE_FAN,
  vikr_TRIANGLES,
  vikr_TRIANGLE_STRIP_ADJACENCY,
  vikr_POLYGON,
};


class IMesh {
public:
  IMesh() { }
  virtual ~IMesh() { }

  virtual vvoid Create() = 0;
  virtual vvoid Create(std::vector<glm::vec3> positions,
               std::vector<glm::vec3> normals,
               std::vector<glm::vec2> uvs,
               std::vector<vuint32> indices,
               MeshDrawMode draw_mode = vikr_TRIANGLES) = 0;
  virtual vvoid Create(std::vector<Vertex> vertices, MeshDrawMode draw_mode = vikr_TRIANGLES) = 0;
  virtual MeshDrawMode GetMeshMode() = 0;
  virtual MeshCommand *GetMeshCommand() = 0;
  virtual vuint32 GetVAO() = 0;
  virtual vuint32 GetVBO() = 0;
  virtual vuint32 GetEBO() = 0;
  virtual GraphicsPipeline GetRenderType() = 0;
};
} // vikr
#endif // __VIKR_IMESH_HPP