//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#include <vikr/mesh/mesh.hpp>
#include <vikr/graphics/render_device.hpp>
#include <vikr/shader/material.hpp>
#include <vikr/util/vikr_log.hpp>

#include <vikr/resources/threading/vikr_thread.hpp>
#include <memory>
#include <thread>

namespace vikr {


const std::string Mesh::kDefaultName = "Default_Mesh";


Mesh::Mesh(GraphicsPipeline pipeline)
  : m_vertexBuffer(nullptr)
  , m_render_type(pipeline)
  , m_name(kDefaultName)
  , guid(GUIDGenerator::Generate())
{
}


vvoid Mesh::Buffer(std::vector<glm::vec3> &positions,
  std::vector<glm::vec3> &normals,
  std::vector<glm::vec2> &uvs,
  std::vector<vuint32> &indices,
  std::vector<glm::vec3> &tangents,
  std::vector<glm::vec3> &bitangents,
  std::vector<glm::vec3> &colors)
{
  VikrThread pos([&] () -> vvoid {
    for(vuint32 i = 0; i < positions.size(); ++i) {
      m_vertices.positions.push_back(positions[i].x);
      m_vertices.positions.push_back(positions[i].y);
      m_vertices.positions.push_back(positions[i].z);
    }
  });

  VikrThread norms([&] () -> vvoid { 
    for(vuint32 i = 0; i < normals.size(); ++i) {
      m_vertices.normals.push_back(normals[i].x);
      m_vertices.normals.push_back(normals[i].y);
      m_vertices.normals.push_back(normals[i].z);
    }
  });
  VikrThread uv([&] () -> vvoid {
    for(vuint32 i = 0; i < uvs.size(); ++i) {
      m_vertices.uvs.push_back(uvs[i].x);
      m_vertices.uvs.push_back(uvs[i].y);
    }
  });
  VikrThread tang([&] () -> vvoid {
    for(vuint32 i = 0; i < tangents.size(); ++i) {
      m_vertices.tangents.push_back(tangents[i].x);
      m_vertices.tangents.push_back(tangents[i].y);
      m_vertices.tangents.push_back(tangents[i].z);
    }
  });
  VikrThread bitang([&] () -> vvoid {
    for(vuint32 i = 0; i < bitangents.size(); ++i) {
      m_vertices.bitangents.push_back(bitangents[i].x);
      m_vertices.bitangents.push_back(bitangents[i].y);
      m_vertices.bitangents.push_back(bitangents[i].z);
    }
  });
  VikrThread color([&] () -> vvoid {
    for(vuint32 i = 0; i < colors.size(); ++i) {
      m_vertices.colors.push_back(colors[i].x);
      m_vertices.colors.push_back(colors[i].y);
      m_vertices.colors.push_back(colors[i].z);
    }
  });
  VikrThread ind([&] () -> vvoid {
    for(vuint32 i = 0; i < indices.size(); ++i) {
      m_vertices.indices.push_back(indices[i]);
    }
  });
  
  pos.Join();
  norms.Join();
  uv.Join();
  tang.Join();
  bitang.Join();
  color.Join();
  ind.Join();
}


vvoid Mesh::Buffer(std::vector<Vertex> &vertices, 
  std::vector<vuint32> &indices) 
{
  std::thread handle([&] () -> vvoid {
    for(vuint32 i = 0; i < vertices.size(); ++i) {
      Vertex &vertex = vertices[i];
      m_vertices.positions.push_back(vertex.position.x);
      m_vertices.positions.push_back(vertex.position.y);
      m_vertices.positions.push_back(vertex.position.z);
      m_vertices.normals.push_back(vertex.normal.x);
      m_vertices.normals.push_back(vertex.normal.y);
      m_vertices.normals.push_back(vertex.normal.z);
      m_vertices.uvs.push_back(vertex.uv.x);
      m_vertices.uvs.push_back(vertex.uv.y);
      m_vertices.tangents.push_back(vertex.tangent.x);
      m_vertices.tangents.push_back(vertex.tangent.y);
      m_vertices.tangents.push_back(vertex.tangent.z);
      m_vertices.bitangents.push_back(vertex.bitangent.x);
      m_vertices.bitangents.push_back(vertex.bitangent.y);
      m_vertices.bitangents.push_back(vertex.bitangent.z);
      m_vertices.colors.push_back(vertex.color.x);
      m_vertices.colors.push_back(vertex.color.y);
      m_vertices.colors.push_back(vertex.color.z);
    }
  });

  std::thread ind([&] () -> vvoid {
    for(vuint32 i = 0; i < indices.size(); ++i) {
      m_vertices.indices.push_back(indices[i]);
    }
  });

  ind.join();
  handle.join();
}


vvoid Mesh::Build(RenderDevice *device) { 
  if (device) {
    m_vertexBuffer = device->CreateVertexbuffer(m_vertices);
  }
}
} // vikr