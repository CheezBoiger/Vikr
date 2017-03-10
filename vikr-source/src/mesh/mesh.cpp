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
{
}


vvoid Mesh::Build(RenderDevice *device, VertexUsageType type,
  std::vector<Vertex> &vertices, std::vector<vuint32> &indices) 
{ 
  if (device) {
    m_vertices = vertices;
    m_indices = indices;
    m_usageType = type;
    m_vertexBuffer = device->CreateVertexbuffer(type, m_vertices, m_indices);
  }
}
} // vikr