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


/// OpenGL 4.3 Render Context. This keeps track of the dynamic
/// state of OpenGL, since Vulkan is all static based. We tend to
/// use this context by means of implementing dynamic states, which is debatable
/// as to whether it should even be interfaced... which not really. 
/// 
/// Treat this Context as a means to keep the current state of OpenGL.
class GL4RenderContext {
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(GL4RenderContext);
  GL4RenderContext();

  /**
    You are using the OpenGL context, which makes it easier to 
    understand.
  */
  vvoid Draw(GL4Commandbuffer *buffer, vuint32 start, vuint32 vertices, vuint32 instances);
  vvoid DrawIndexed(GL4Commandbuffer *buffer, const vvoid *indices, vuint32 elements, vuint32 instances);
  vvoid SetTexture(Texture *texture, vuint32 index);
  
  //vvoid SetRenderTarget(RenderTarget *target, vuint32 index);
  vvoid Clear(GL4Commandbuffer *buffer);
  vvoid ClearWithColor(GL4Commandbuffer *buffer, glm::vec4 color);
  vvoid SetViewport(GL4Commandbuffer *buffer, Viewport *port);

  /// Currently not in use. But kept if needed.
  vvoid SetShaderUniforms(ShaderUniformParams *params);

  /// queries the vertex buffer to this context.
  vvoid QueryVertexbuffer(GL4Commandbuffer *buffer, Vertexbuffer *vertexbuffer);

  vvoid SetFramebuffer(Framebuffer *framebuffer);
  vvoid SetRenderPass(GL4Commandbuffer *buffer, RenderPass *renderpass);

  Framebuffer *GetFramebuffer();
  GraphicsPipelineState *GetGraphicsPipelineState();
  vvoid BindGraphicsPipelineState(GL4Commandbuffer *buffer, GraphicsPipelineState *pipelinestate);
  vvoid BindComputePipelineState(GL4Commandbuffer *buffer, ComputePipelineState *pipelinestate);
  vvoid SetMaterial(GL4Commandbuffer *buffer, Material *material);
  vvoid QueryVertexbuffer(GL4Commandbuffer *buffer, Vertexbuffer *vertexbuffer);

  GL4Vertexbuffer *GetCurrentVertexbuffer() { return m_queriedVertexbuffer; }

  vvoid Dispatch(GL4Commandbuffer *buffer, vuint32 x, vuint32 y, vuint32 z);
  vvoid ClearTextures();

private:
  GL4GraphicsPipelineState *m_currPipeline        = nullptr;
  GL4Framebuffer *m_currFramebuffer               = nullptr;
  GL4Vertexbuffer *m_queriedVertexbuffer          = nullptr;
  std::vector<TextureSampler> m_currTextures;
};
} // vikr
#endif // __VIKR_GL4_CONTEXT_HPP