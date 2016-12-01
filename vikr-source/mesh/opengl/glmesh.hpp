//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_OPENGL_MESH_HPP
#define __VIKR_OPENGL_MESH_HPP

#include <mesh/mesh.hpp>

namespace vikr {


class GLMesh : public Mesh {
public:
  GLMesh();
  GLMesh(std::vector<glm::vec3> positions,
         std::vector<glm::vec3> normals,
         std::vector<glm::vec2> uvs,
         std::vector<vuint32> indices = std::vector<vuint32>(),
         MeshDrawMode draw_mode = vikr_TRIANGLES);

  vvoid Create() override;

};
} // vikr
#endif // __VIKR_OPENGL_MESH_HPP