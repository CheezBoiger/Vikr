//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#include <mesh/mesh.hpp>
#include <graphics/render_device.hpp>
#include <shader/material.hpp>
#include <util/vikr_log.hpp>
#include <memory>

namespace vikr {


const std::string Mesh::kDefaultName = "Default_Mesh";


Mesh::Mesh(GraphicsPipeline pipeline)
  : m_vertexBuffer(nullptr)
  , m_render_type(pipeline)
  , m_name(kDefaultName)
  , guid(GUIDGenerator::Generate())
{
}


Mesh::Mesh(GraphicsPipeline pipeline,
  std::vector<glm::vec3> positions,
  std::vector<glm::vec3> normals,
  std::vector<glm::vec2> uvs,
  std::vector<vuint32> indices)
  : m_vertexBuffer(nullptr)
  , m_indices(indices)
  , m_render_type(pipeline)
  , guid(GUIDGenerator::Generate())
{
  for (vuint32 i = 0; i < positions.size(); ++i) {
    Vertex vert;
    vert.position = std::move(positions[i]);
    vert.normal = std::move(normals[i]);
    vert.uv = std::move(uvs[i]);  
    m_vertices.push_back(std::move(vert));
  }
}


vvoid Mesh::Buffer(std::vector<glm::vec3> positions,
  std::vector<glm::vec3> normals,
  std::vector<glm::vec2> uvs,
  std::vector<vuint32> indices,
  std::vector<glm::vec3> tangents,
  std::vector<glm::vec3> bitangents)
{
  for (vuint32 i = 0; i < positions.size(); ++i) {
    Vertex vert;
    vert.position = std::move(positions[i]);
    if (i < normals.size()) {
      vert.normal = std::move(normals[i]);
    } else {
      vert.normal = glm::vec3();
    }
    if (i < uvs.size()) {
      vert.uv = std::move(uvs[i]);
    } else {
      vert.uv = glm::vec2();
    }
    if (i < tangents.size()) {
      vert.tangent = std::move(tangents[i]);
    } else {
      vert.tangent = glm::vec3(0);
    }
    if (i < bitangents.size()) {
      vert.bitangent = std::move(bitangents[i]);
    } else {
      vert.bitangent = glm::vec3(0);
    }
    m_vertices.push_back(std::move(vert));
  }
  if (!indices.empty()) {
    m_indices = std::move(indices);
  }
}


vvoid Mesh::Buffer(std::vector<Vertex> vertices, 
  std::vector<vuint32> indices) 
{
  if (!vertices.empty()) {
    m_vertices = std::move(vertices);
  }
  if (!indices.empty()) {
    m_indices = std::move(indices);
  }
}


vvoid Mesh::Create(RenderDevice *device) { 
  if (device) {
    m_vertexBuffer = device->CreateVertexbuffer(m_vertices, m_indices, m_usage_type);
  }
}
} // vikr