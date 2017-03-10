//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_QUAD_HPP
#define __VIKR_QUAD_HPP


#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <vikr/mesh/vertex.hpp>
#include <glm/glm.hpp>

#include <vector>

namespace vikr {


class Quad {
public:
  Quad();

  std::vector<Vertex>& GetVertices() { return m_vertices; }
private:
  std::vector<Vertex> m_vertices;
};
} // vikr
#endif // __VIKR_QUAD_HPP