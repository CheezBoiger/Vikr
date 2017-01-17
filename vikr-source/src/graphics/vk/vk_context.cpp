//
// Copyright (c) Mario Garcia, Under the MIT License. 
//
#include <vikr/graphics/vk/vk_context.hpp>

namespace vikr {


VKContext::VKContext()
{
}


vvoid VKContext::Draw(vuint32 start, vuint32 vertices) {
}


vvoid VKContext::DrawIndexed(const vvoid *indices, vuint32 elements) {
}


vvoid VKContext::SetTexture(vuint32 texture, vuint32 target, vuint32 index) {
}


vvoid VKContext::SetRenderTarget(RenderTarget *target, vuint32 index) {
}


vvoid VKContext::SetRenderPass(RenderPass *pass) {
}


vvoid VKContext::SetBlendEq(BlendEq eq) {
}


vvoid VKContext::SetBlendMode(BlendFunc src, BlendFunc dst) {
}


vvoid VKContext::SetDepthFunc(DepthFunc depth) {
}


vvoid VKContext::EnableCullMode(vbool enable) {
}


vvoid VKContext::EnableBlendMode(vbool enable) {
}


vvoid VKContext::EnableDepthMode(vbool enable) {
}


vvoid VKContext::SetCullFace(CullFace face) {
}


vvoid VKContext::SetFrontFace(FrontFace face) {
}


vvoid VKContext::Clear() {
}


vvoid VKContext::ClearWithColor(glm::vec4 color) {
}


vvoid VKContext::ChangeViewport(Viewport *port) {
}


vvoid VKContext::ChangeTopology(Topology topology) {
}


vvoid VKContext::ExecuteCommands(CommandbufferList *buffer) {
}


vvoid VKContext::ConfigurePipelineState(PipelineState *state) {
}


vvoid VKContext::SetShaderUniforms(ShaderUniformParams *params) {
}


vvoid VKContext::ApplyShaderProgram(vuint32 program_id) {
}


vvoid VKContext::QueryVertexbuffer(Vertexbuffer *buffer) {
}


vvoid VKContext::Present() {
}
} // vikr