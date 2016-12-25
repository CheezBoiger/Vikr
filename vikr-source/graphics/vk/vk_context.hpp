//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VK_CONTEXT_HPP
#define __VIKR_VK_CONTEXT_HPP


#include <graphics/render_context.hpp>


namespace vikr {


class VKContext : public RenderContext {
public:
  VKContext();

  vvoid Draw(vuint32 start, vuint32 vertices) override;

  vvoid DrawIndexed(const vvoid *indices, vuint32 elements) override;

  vvoid SetTexture(vuint32 texture, vuint32 target, vuint32 index) override;

  vvoid SetRenderTarget(RenderTarget *target, vuint32 index) override;

  vvoid SetRenderPass(RenderPass *pass) override;

  vvoid SetBlendEq(BlendEq eq) override;

  vvoid SetBlendMode(BlendFunc src, BlendFunc dst) override;

  vvoid SetDepthFunc(DepthFunc depth) override;

  vvoid EnableCullMode(vbool enable) override;

  vvoid EnableBlendMode(vbool enable) override;

  vvoid EnableDepthMode(vbool enable) override;

  vvoid SetCullFace(CullFace face) override;

  vvoid SetFrontFace(FrontFace face) override;

  vvoid Clear() override;
  
  vvoid ClearWithColor(glm::vec4 color) override;

  vvoid ChangeViewport(Viewport *port) override;

  vvoid ChangeTopology(Topology topology) override;

  vvoid ExecuteCommands(Commandbuffer *buffer) override;

  vvoid ConfigurePipelineState(PipelineState *state) override;

  vvoid SetShaderUniforms(ShaderUniformParams *params) override;

  vvoid ApplyShaderProgram(vuint32 program_id) override;

  vvoid QueryVertexbuffer(Vertexbuffer *buffer) override;

  vvoid Present() override;


  VkQueue &GetGraphicsQueue() { return m_queueGraphicsBuffer; }
  VkQueue &GetPresentationQueue() { return m_queuePresentBuffer; }

private:

  VkQueue m_queueGraphicsBuffer;
  VkQueue m_queuePresentBuffer;
};
} // vikr
#endif // __VIKR_VK_CONTEXT_HPP