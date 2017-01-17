//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_QUAD_HPP
#define __VIKR_QUAD_HPP


#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <glm/glm.hpp>

#include <vector>

namespace vikr {


class Quad {
public:
  Quad();

  std::vector<glm::vec3>& GetPositions() { return positions; }
  std::vector<glm::vec3>& GetNormals() { return normals; }
  std::vector<glm::vec2>& GetUVs() { return uvs; }
private:
  std::vector<glm::vec3> positions;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec2> uvs;
};
} // vikr
#endif // __VIKR_QUAD_HPP