//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#include <vikr/renderer/screen_quad.hpp>
#include <vikr/graphics/render_context.hpp>
#include <vikr/resources/resource_manager.hpp>
#include <vikr/util/vikr_log.hpp>
#include <vikr/shader/cubemap.hpp>
#include <vikr/scene/icamera.hpp>
#include <vikr/graphics/graphics_pipeline_state.hpp>
#include <vikr/math/geometry/cube.hpp>


namespace vikr {


ScreenQuad::ScreenQuad()
{
}


vvoid ScreenQuad::Init(RenderDevice *device, ResourceManager *mgr) {
  if (!device) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Device was null! Cannot init ScreenQuad!");
    return;
  }
  Quad quad;
  m_device = device;
  m_mgr = mgr;
  m_quad = mgr->CreateMesh();
  m_quad->Build(device, vikr_STATIC, quad.GetVertices());

  list = device->CreateCommandbufferList();
  Commandbuffer &buffer = device->CreateCommandbuffer(list);
  command.m_mesh = m_quad;
  command.Record(buffer);
}


vvoid ScreenQuad::Execute()
{
  m_device->GetContext()->ExecuteCommands(list);
    
}
} // vikr