//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/graphics/gl4/gl4_commandbuffer.hpp>
#include <vikr/graphics/gl4/gl4_context.hpp>
#include <vikr/graphics/gl4/gl4_device.hpp>
#include <vikr/shader/shader_uniform_params.hpp>
#include <vikr/graphics/gl4/gl4_vertexbuffer.hpp>
#include <vikr/shader/glsl/glsl_program.hpp>
#include <vikr/shader/material.hpp>
#include <vikr/resources/threading/vikr_thread.hpp>
#include <vikr/util/vikr_log.hpp>

#include <list>


#define CHECK_RECORDING() \
  if (!IsRecording()) { \
    VikrLog::DisplayMessage(VIKR_ERROR, \
      "You must call Record() in order to record commands! Cancelling..."); \
    return; \
  } 


namespace vikr {


vvoid GL4Commandbuffer::BeginRecord() {
  recording = true; 
}


vvoid GL4Commandbuffer::EndRecord() {
  recording = false;
}


vbool GL4Commandbuffer::IsRecording() 
{
  return recording;
}


vvoid GL4Commandbuffer::Draw(vuint32 start, vuint32 vertices, vuint32 instances) {
  CHECK_RECORDING();
  static_cast<GL4RenderDevice *>(GetRenderDevice())->GetContext().Draw(
    this, start, vertices, instances);
}


vvoid GL4Commandbuffer::DrawIndexed(const vvoid *indices, vuint32 vertices, vuint32 instances) {
  CHECK_RECORDING();
  static_cast<GL4RenderDevice *>(GetRenderDevice())->GetContext().DrawIndexed(
    this, indices, vertices, instances);
}


vvoid GL4Commandbuffer::BindRenderPass(RenderPass *pass) {
  CHECK_RECORDING();
  static_cast<GL4RenderDevice *>(GetRenderDevice())->GetContext().SetRenderPass(
    this, pass);
}


vvoid GL4Commandbuffer::BindGraphicsPipelineState(GraphicsPipelineState *state) {
  CHECK_RECORDING();
  static_cast<GL4RenderDevice *>(GetRenderDevice())->GetContext().BindGraphicsPipelineState(
    this, state);
}


vvoid GL4Commandbuffer::BindVertexbuffers(Vertexbuffer *buffer) {
  CHECK_RECORDING();
  static_cast<GL4RenderDevice *>(GetRenderDevice())->GetContext().QueryVertexbuffer(
    this, buffer);
    
}


vvoid GL4Commandbuffer::BindMaterial(Material *material) {
  CHECK_RECORDING();
  static_cast<GL4RenderDevice *>(GetRenderDevice())->GetContext().SetMaterial(
    this, material);
}


vvoid GL4Commandbuffer::SetViewport(Viewport *viewport) 
{
  CHECK_RECORDING();
  static_cast<GL4RenderDevice *>(GetRenderDevice())->GetContext().SetViewport(
    this, viewport);
}


vvoid GL4Commandbuffer::Clear() {
  CHECK_RECORDING();
  static_cast<GL4RenderDevice *>(GetRenderDevice())->GetContext().Clear(
    this);
}


vvoid GL4Commandbuffer::ClearWithColor(glm::vec4 color) {
  CHECK_RECORDING();
  static_cast<GL4RenderDevice *>(GetRenderDevice())->GetContext().ClearWithColor(
    this, color);
}


vvoid GL4Commandbuffer::BindComputePipelineState(ComputePipelineState *pipeline) {
  CHECK_RECORDING();
  static_cast<GL4RenderDevice *>(GetRenderDevice())->GetContext().BindComputePipelineState(
    this, pipeline);
}
} // vikr