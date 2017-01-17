//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_CUBE_HPP
#define __VIKR_CUBE_HPP

#include <vikr/platform/vikr_types.hpp>
#include <glm/glm.hpp>
#include <vector>

namespace vikr {


/**
  Cube testing! Credit goes to Joey De Vries and his collaborators for 
  helping me learn the amazing topics of modern OpenGL!
*/
class Cube {
public:
  Cube();

  std::vector<glm::vec3> GetVertices() { return m_vertices; }
  std::vector<glm::vec3> GetNormals() { return m_normals; }
  std::vector<glm::vec2> GetUVs() { return m_uvs; }

  std::vector<vuint32> GetIndices() { return m_indices; }

private:
  std::vector<glm::vec3> m_vertices;
  std::vector<glm::vec3> m_normals;
  std::vector<glm::vec2> m_uvs;
  std::vector<vuint32> m_indices;
};
} // vikr
#endif // __VIKR_CUBE_HPP