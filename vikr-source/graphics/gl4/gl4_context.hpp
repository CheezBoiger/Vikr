//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GL4_CONTEXT_HPP
#define __VIKR_GL4_CONTEXT_HPP


#include <graphics/render_context.hpp>
#include <graphics/command_buffer.hpp>


namespace vikr {


class Framebuffer;


/**
  OpenGL 4.3 Render Context.
*/
class GL4RenderContext : public RenderContext {
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(GL4RenderContext);
  GL4RenderContext();

  /**
    You are using the OpenGL context, which makes it easier to 
    understand.
  */
  vvoid Draw(vuint32 start, vuint32 vertices) override;
  vvoid DrawIndexed(const vvoid *indices, vuint32 vertices) override;
  vvoid SetTexture(Texture *texture, vuint32 index) override;
  
  vvoid SetRenderTarget(RenderTarget *target, vuint32 index) override;
  vvoid SetRenderPass(RenderPass *pass) override;

  /**
    These functions might need to hit the PipelineState instead. They involve
    mostly rasterization.
  */
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

  vvoid ExecuteCommands(CommandBuffer *command_buffer) override;
  vvoid ConfigurePipelineState(PipelineState *state) override;

private:
  /**
    Current topology.
  */
  Topology m_currTopology         = VIKR_TRIANGLES;
  /**
    Current Framebuffer being used. This might be settled to blit other 
    Framebuffers.
  */
  Framebuffer *m_currFramebuffer  = nullptr;

  /**
    Current RenderPass being used.
  */
  RenderPass *m_currRenderPass    = nullptr;

  PipelineState *pipeline;
};
} // vikr
#endif // __VIKR_GL4_CONTEXT_HPP