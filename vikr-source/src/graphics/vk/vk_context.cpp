//
// Copyright (c) Mario Garcia, Under the MIT License. 
//
#include <vikr/graphics/vk/vk_context.hpp>
#include <vikr/shader/material.hpp>


namespace vikr {


VKRenderContext::VKRenderContext()
{
}


vvoid VKRenderContext::Draw(vuint32 start, vuint32 vertices) {
}


vvoid VKRenderContext::DrawIndexed(const vvoid *indices, vuint32 elements) {
}


vvoid VKRenderContext::SetTexture(Texture *texture, vuint32 index) {
}


vvoid VKRenderContext::SetRenderTarget(RenderTarget *target, vuint32 index) {
}


vvoid VKRenderContext::SetBlendEq(BlendEq eq) {
}


vvoid VKRenderContext::SetBlendMode(BlendFunc src, BlendFunc dst) {
}


vvoid VKRenderContext::SetDepthFunc(DepthFunc depth) {
}


vvoid VKRenderContext::EnableCullMode(vbool enable) {
}


vvoid VKRenderContext::EnableBlendMode(vbool enable) {
}


vvoid VKRenderContext::EnableDepthMode(vbool enable) {
}


vvoid VKRenderContext::SetCullFace(CullFace face) {
}


vvoid VKRenderContext::SetFrontFace(FrontFace face) {
}


vvoid VKRenderContext::Clear() {
}


vvoid VKRenderContext::ClearWithColor(glm::vec4 color) {
}


vvoid VKRenderContext::ChangeViewport(Viewport *port) {
}


vvoid VKRenderContext::ChangeTopology(Topology topology) {
}


vvoid VKRenderContext::ExecuteCommands(CommandbufferList *buffer) {
}


vvoid VKRenderContext::SetShaderUniforms(ShaderUniformParams *params) {
}


vvoid VKRenderContext::QueryVertexbuffer(Vertexbuffer *buffer) {
}


vvoid VKRenderContext::Present() {
}


vvoid VKRenderContext::SetFramebuffer(Framebuffer *framebuffer) {

}


vvoid VKRenderContext::BeginRecord(Commandbuffer *buf) {
}


vvoid VKRenderContext::EndRecord() {
}


Framebuffer *VKRenderContext::GetFramebuffer() {
  return nullptr;
}


GraphicsPipelineState *VKRenderContext::GetGraphicsPipelineState() {
  return nullptr;
}


vvoid VKRenderContext::ApplyGraphicsPipelineState(GraphicsPipelineState *pipeline) {
}


vvoid VKRenderContext::SetMaterial(Material *material) {
}


vvoid VKRenderContext::Dispatch(vuint32 x, vuint32 y, vuint32 z) {
}


vvoid VKRenderContext::SetRenderPass(RenderPass *pass) {
}
} // vikr