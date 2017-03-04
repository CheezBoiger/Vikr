//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VK_CONTEXT_HPP
#define __VIKR_VK_CONTEXT_HPP


#include <vikr/graphics/render_context.hpp>


namespace vikr {


class VKPipelineState;


class VKRenderContext : public RenderContext {
public:
  VKRenderContext();

  vvoid Draw(vuint32 start, vuint32 vertices) override;

  vvoid DrawIndexed(const vvoid *indices, vuint32 elements) override;

  vvoid SetTexture(Texture *texture, vuint32 index) override;

  vvoid SetRenderTarget(RenderTarget *target, vuint32 index) override;

  vvoid SetFramebuffer(Framebuffer *framebuffer) override;

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

  vvoid ExecuteCommands(CommandbufferList *buffer) override;

  vvoid SetShaderUniforms(ShaderUniformParams *params) override;

  vvoid QueryVertexbuffer(Vertexbuffer *buffer) override;

  vvoid BeginRecord(Commandbuffer *buf) override;
  vvoid EndRecord() override;
  Framebuffer *GetFramebuffer() override;
  GraphicsPipelineState *GetGraphicsPipelineState() override;
  vvoid ApplyGraphicsPipelineState(GraphicsPipelineState *pipeline) override;

  vvoid Present() override;

  vvoid Dispatch(vuint32 x, vuint32 y, vuint32 z) override;

  vvoid SetRenderPass(RenderPass *pass) override;
  vvoid SetMaterial(Material *material) override;

  Vertexbuffer *GetCurrentVertexbuffer() { return nullptr; }

  VkQueue &GetGraphicsQueue() { return m_queueGraphicsBuffer; }
  VkQueue &GetPresentationQueue() { return m_queuePresentBuffer; }

private:
  
  /**
    Current Pipeline State to use.
  */
  VKPipelineState *m_currPipelineState = nullptr;

  VkQueue m_queueGraphicsBuffer;
  VkQueue m_queuePresentBuffer;
};
} // vikr
#endif // __VIKR_VK_CONTEXT_HPP