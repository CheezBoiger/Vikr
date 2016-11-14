//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_MESH_HPP
#define __VIKR_MESH_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <renderer/mesh_command.hpp>
#include <glm/vec3.hpp>
#include <vector>

namespace vikr {


class ProgramState;
class Material;


enum MeshDrawMode {
  vikr_POINTS,
  vikr_LINE_STRIP,
  vikr_LINE_LOOP,
  vikr_LINES,
  vikr_TRIANGLE_STRIP,
  vikr_TRIANGE_FAN,
  vikr_TRIANGLES,
  vikr_QUAD_STRIP,
  vikr_QUADS,
  vikr_POLYGON,
};


/**
  Mesh object to be used for rendering.
*/
class Mesh {
public:
  Mesh();
  Mesh(std::vector<glm::vec3> positions, 
       std::vector<glm::vec3> normals,
       std::vector<glm::vec2> uvs,
       std::vector<glm::vec3> indices,
       MeshDrawMode draw_mode = vikr_TRIANGLES);

  vvoid Create();
  vvoid Create(std::vector<glm::vec3> positions, 
               std::vector<glm::vec3> normals,
               std::vector<glm::vec2> uvs,
               std::vector<glm::vec3> indices, 
               MeshDrawMode draw_mode = vikr_TRIANGLES);

  vvoid Draw();

  vvoid SetProgramState(ProgramState *state);

  ProgramState *GetProgramState() const { return m_program; }

  vuint32 GetVAO() { return m_vao; }
  vuint32 GetVBO() { return m_vbo; }
  vuint32 GetEBO() { return m_ebo; }

  MeshDrawMode GetMeshMode() { return m_mode; }

protected:
  MeshDrawMode m_mode;
  vuint32 m_vao;
  vuint32 m_vbo;
  vuint32 m_ebo;
  Material *m_material;
  ProgramState *m_program;
  glm::mat4 modelview;

  MeshCommand m_command;

  std::vector<glm::vec3> m_vertices;
  std::vector<glm::vec3> m_normals;
  std::vector<glm::vec3> m_indices;
  std::vector<glm::vec2> m_uvs;
  // For lighting...
  std::vector<glm::vec3> m_tangents;
  std::vector<glm::vec3> m_bitangents;
};
} // vikr
#endif // __VIKR_MESH_HPP