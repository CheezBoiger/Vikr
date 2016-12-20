//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VERTEX_HPP
#define __VIKR_VERTEX_HPP


#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <glm/glm.hpp>


namespace vikr {


/*
Vertex of the mesh.
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
} // vikr
#endif // __VIKR_VERTEX_HPP