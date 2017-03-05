//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/math/geometry/sphere.hpp>
#include <initializer_list>
#include <vikr/util/vikr_assert.hpp>

#include <vikr/mesh/vertex.hpp>


// Jes try it manggg
#define OCTAHEDRON 0


namespace vikr {


vreal32 AngleFromXY(vreal32 x, vreal32 y) {
  vreal32 theta = 0.0f;
  if (x >= 0.0f) {
    theta = std::atanf(y / x);
    if (theta < 0.0f) {
      theta += static_cast<vreal32>(2.0f * VIKR_PI);
    } else {
      theta = std::atanf(y / x) + static_cast<vreal32>(VIKR_PI);
    }
  } 
  return theta; 
}


/**
  Implementation very much referenced by Frank Luna's GeometryGenerator.h
  code.
*/
Sphere::Sphere(vreal32 radius, vuint32 num_subdivisions) {
  num_subdivisions = std::min(num_subdivisions, 5u);
  
  const vreal32 X = 0.525731f;
  const vreal32 Z = 0.850651f;

  glm::vec3 pos[] = { 
#if OCTAHEDRON
    glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, -1.0f),
    glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f),
    glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 1.0f),

    glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 1.0f),
    glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f),
    glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f) 
#else
    glm::vec3(-X, 0.0f, Z), glm::vec3(X, 0.0f, Z),
    glm::vec3(-X, 0.0f, -Z), glm::vec3(X, 0.0f, -Z),
    glm::vec3(0.0f, Z, X), glm::vec3(0.0f, Z, -X),
    glm::vec3(0.0f, -Z, X), glm::vec3(0.0f, -Z, -X),
    glm::vec3(Z, X, 0.0f), glm::vec3(-Z, X, 0.0f),
    glm::vec3(Z, -X, 0.0f), glm::vec3(-Z, -X, 0.0f)
#endif
  };

  vuint32 k[] = {
#if OCTAHEDRON 
    1,2,3,  3,4,5,  6,7,8,  9,10,11,
    1,3,13, 3,5,13, 6,8,13, 9,11,13 
#else
		1,4,0,  4,9,0,  4,5,9,  8,5,4,  1,8,4,    
		1,10,8, 10,3,8, 8,3,5,  3,2,5,  3,7,2,    
		3,10,7, 10,6,7, 6,11,7, 6,0,11, 6,1,0, 
		10,1,6, 11,0,9, 2,11,9, 5,2,9,  11,2,7 
#endif
  };

  // Depending on the machine, this can be problematic...
  positions.resize(sizeof(pos) / 12);
  indices.resize(sizeof(k) / 4);

  for (vuint32 i = 0; i < (sizeof(pos) / 12); ++i) {
    positions[i] = pos[i];
  }

  for (vuint32 i = 0; i < (sizeof(k) / 4); ++i) {
    indices[i] = k[i];
  }

  for (vuint32 i = 0; i < num_subdivisions; ++i) {
    Subdivide();  
  }

  for (vuint32 i = 0; i < positions.size(); ++i) {
    glm::vec3 normal = glm::normalize(positions[i]);
    // project onto sphere.
    glm::vec3 p = radius * normal;
    
    positions[i] = p;
    normals.push_back(normal);

    vreal32 theta = AngleFromXY(positions[i].x, positions[i].y);
    vreal32 phi = std::acosf(positions[i].y / radius);

    glm::vec2 uv(
      static_cast<vreal32>(theta / VIKR_PI_2), 
      static_cast<vreal32>(phi / VIKR_PI)
    );
    glm::vec3 tangent(
      -radius * std::sinf(phi) * std::sinf(theta),
      0.0f,
      radius * std::sinf(phi) * std::cosf(theta)
    );
    tangent = glm::normalize(tangent);
    
    tangents.push_back(tangent);
    uvs.push_back(uv);
  }
}


vvoid Sphere::Subdivide() {
  // save a copy of the positions and indices.
  std::vector<glm::vec3> copy_pos = positions;
  std::vector<vuint32> copy_ind = indices;

  // rebuild with subdivisions.
  positions.resize(0);
  indices.resize(0);

  vuint32 num_tris = copy_ind.size() / 3;
  for (vuint32 i = 0; i < num_tris; ++i) {
    glm::vec3 t_pos0 = copy_pos[copy_ind[i * 3 + 0] ];
    glm::vec3 t_pos1 = copy_pos[copy_ind[i * 3 + 1] ];
    glm::vec3 t_pos2 = copy_pos[copy_ind[i * 3 + 2] ];

    // midpoints.
    glm::vec3 m0, m1, m2;
    m0.x = 0.5f * (t_pos0.x + t_pos1.x);
    m0.y = 0.5f * (t_pos0.y + t_pos1.y);
    m0.z = 0.5f * (t_pos0.z + t_pos1.z);

    m1.x = 0.5f * (t_pos1.x + t_pos2.x);
    m1.y = 0.5f * (t_pos1.y + t_pos2.y);
    m1.z = 0.5f * (t_pos1.z + t_pos2.z);

    m2.x = 0.5f * (t_pos0.x + t_pos2.x);
    m2.y = 0.5f * (t_pos0.y + t_pos2.y);
    m2.z = 0.5f * (t_pos0.z + t_pos2.z);

    positions.push_back(t_pos0);
    positions.push_back(t_pos1);
    positions.push_back(t_pos2);
    positions.push_back(m0);
    positions.push_back(m1);
    positions.push_back(m2);

    indices.push_back(i * 6 + 0);
    indices.push_back(i * 6 + 3);
    indices.push_back(i * 6 + 5);

    indices.push_back(i * 6 + 3);
    indices.push_back(i * 6 + 4);
    indices.push_back(i * 6 + 5);

    indices.push_back(i * 6 + 5);
    indices.push_back(i * 6 + 4);
    indices.push_back(i * 6 + 2);

    indices.push_back(i * 6 + 3);
    indices.push_back(i * 6 + 1);
    indices.push_back(i * 6 + 4);
  }
}
} // vikr