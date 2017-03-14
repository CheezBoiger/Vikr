//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GL4_CONTEXT_HPP
#define __VIKR_GL4_CONTEXT_HPP


#include <vikr/graphics/render_context.hpp>
#include <vikr/graphics/command_buffer.hpp>
#include <vikr/graphics/gl4/gl4_graphics_pipeline_state.hpp>
#include <vikr/shader/shader_config.hpp>


namespace vikr {


class Framebuffer;
class GL4RenderPass;
class GL4Framebuffer;
class GL4Commandbuffer;
class GL4GraphicsPipelineState;
class GL4Vertexbuffer;
struct TextureSampler;


/**
  OpenGL 4.3 Render Context.
*/
class GL4RenderContext {
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(GL4RenderContext);
  GL4RenderContext();

  /**
    You are using the OpenGL context, which makes it easier to 
    understand.
  */
  vvoid Draw(GL4Commandbuffer *buffer, vuint32 start, vuint32 vertices);
  vvoid DrawIndexed(GL4Commandbuffer *buffer, const vvoid *indices, vuint32 elements);
  vvoid SetTexture(Texture *texture, vuint32 index);
  
  vvoid SetRenderTarget(RenderTarget *target, vuint32 index);

  /**
    These functions might need to hit the PipelineState instead. They involve
    mostly rasterization.
  */
  vvoid SetBlendEq(BlendEq eq);
  vvoid SetBlendMode(BlendFunc src, BlendFunc dst);
  vvoid SetDepthFunc(DepthCompare depth);
  vvoid EnableCullMode(vbool enable);
  vvoid EnableBlendMode(vbool enable);
  vvoid EnableDepthMode(vbool enable);
  vvoid SetCullFace(CullFace face);
  vvoid SetFrontFace(FrontFace face);

  
  vvoid Clear(GL4Commandbuffer *buffer);
  vvoid ClearWithColor(GL4Commandbuffer *buffer, glm::vec4 color);
  vvoid ChangeViewport(GL4Commandbuffer *buffer, Viewport *port);
  vvoid ChangeTopology(Topology topology);

  vvoid SetShaderUniforms(ShaderUniformParams *params);
  vvoid QueryVertexbuffer(GL4Commandbuffer *buffer, Vertexbuffer *vertexbuffer);

  vvoid SetFramebuffer(Framebuffer *framebuffer);
  vvoid SetRenderPass(GL4Commandbuffer *buffer, RenderPass *renderpass);
  vvoid BeginRecord(GL4Commandbuffer *buf); 
  vvoid EndRecord();

  Framebuffer *GetFramebuffer();
  GraphicsPipelineState *GetGraphicsPipelineState();
  vvoid ApplyGraphicsPipelineState(GL4Commandbuffer *buffer, GraphicsPipelineState *pipelinestate);
  vvoid SetMaterial(GL4Commandbuffer *buffer, Material *material);
  vvoid QueryVertexbuffer(GL4Commandbuffer *buffer, vuint32 instances, Vertexbuffer *vertexbuffer);

  GL4Vertexbuffer *GetCurrentVertexbuffer() { return m_queriedVertexbuffer; }

  vvoid Dispatch(GL4Commandbuffer *buffer, vuint32 x, vuint32 y, vuint32 z) override;
  vvoid ClearTextures() override;

private:

  GL4GraphicsPipelineState *m_currPipeline                = nullptr;

  std::vector<TextureSampler> m_currTextures;
  GL4Commandbuffer *m_recordCommandbuffer         = nullptr;
  GL4Framebuffer *m_currFramebuffer               = nullptr;
  GL4Vertexbuffer *m_queriedVertexbuffer          = nullptr;
};
} // vikr
#endif // __VIKR_GL4_CONTEXT_HPP