//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_CUBE_HPP
#define __VIKR_CUBE_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/mesh/vertex.hpp>
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

  std::vector<Vertex> &GetVertices() { return m_vertices; }

  std::vector<vuint32> &GetIndices() { return m_indices; }

private:
  std::vector<Vertex> m_vertices;
  std::vector<vuint32> m_indices;
};
} // vikr
#endif // __VIKR_CUBE_HPP