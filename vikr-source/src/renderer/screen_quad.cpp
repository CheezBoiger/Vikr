//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#include <vikr/renderer/screen_quad.hpp>
#include <vikr/graphics/render_context.hpp>
#include <vikr/resources/resource_manager.hpp>
#include <vikr/util/vikr_log.hpp>
#include <vikr/shader/cubemap.hpp>
#include <vikr/scene/icamera.hpp>
#include <vikr/graphics/pipeline_state.hpp>
#include <vikr/math/shape/cube.hpp>


namespace vikr {


ScreenQuad::ScreenQuad()
{
}


vvoid ScreenQuad::Init(RenderDevice *device) {
  if (!device) {
    VikrLog::DisplayMessage(VIKR_ERROR, "Device was null! Cannot init ScreenQuad!");
    return;
  }
  Quad quad;
  m_device = device;
  m_quad = device->GetResourceManager()->CreateMesh(
    quad.GetPositions(), quad.GetNormals(), quad.GetUVs());
  m_quad->Build(device);

  std::unique_ptr<Commandbuffer> buffer = device->CreateCommandbuffer();
  command.m_mesh = m_quad;
  command.Record(buffer.get());
  list.PushBack(buffer);
}


vvoid ScreenQuad::Execute()
{
  m_device->GetContext()->ExecuteCommands(&list);
    
}
} // vikr