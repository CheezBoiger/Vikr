//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VERTEX_HPP
#define __VIKR_VERTEX_HPP


#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <glm/glm.hpp>


namespace vikr {


/*
  Vertex of the mesh. This is an object oriented approach.
*/
struct Vertex {
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 uv;
  glm::vec3 tangent;
  glm::vec3 bitangent;
};


/**
Change the Useage type of the Mesh.
*/
enum VertexUsageType {
  vikr_STATIC,
  vikr_DYNAMIC
};


/**
  Vertex Container. Used to separate values.
*/
struct VertexContainer {
  std::vector<vreal32>  positions;
  std::vector<vreal32>  normals;
  std::vector<vreal32>  uvs;
  std::vector<vreal32>  tangents;
  std::vector<vreal32>  bitangents;
  std::vector<vuint32>  indices;
  VertexUsageType       usage_type;
  vuint32 size = 0;
};
} // vikr
#endif // __VIKR_VERTEX_HPP