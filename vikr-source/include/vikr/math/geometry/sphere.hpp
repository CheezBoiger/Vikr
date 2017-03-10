//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_SPHERE_HPP
#define __VIKR_SPHERE_HPP


#include <vikr/platform/vikr_types.hpp>
#include <vikr/mesh/vertex.hpp>
#include <vector>
#include <glm/glm.hpp>

// Constants from math.h
#define VIKR_PI       3.14159265358979323846   // pi
#define VIKR_PI_2     1.57079632679489661923   // pi/2
#define VIKR_PI_4     0.785398163397448309616  // pi/4


namespace vikr {


/**
  Not implemented yet, do not use!
*/
class Sphere {
public:
  // Uses the power of gray skull, well, actually references Frank Luna's Geometry Generator. Kudos!
  Sphere(vreal32 radius, vuint32 num_subdivisions);


  std::vector<Vertex> &GetVertices() { return m_vertices; }

  std::vector<vuint32> &GetIndices() { return indices; }

private:

  vvoid Subdivide();

  std::vector<Vertex> m_vertices;
  std::vector<vuint32> indices;
};
} // vikr
#endif // __VIKR_SPHERE_HPP

