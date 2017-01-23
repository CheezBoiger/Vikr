//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GL4_CONTEXT_HPP
#define __VIKR_GL4_CONTEXT_HPP


#include <vikr/graphics/render_context.hpp>
#include <vikr/graphics/command_buffer.hpp>
#include <vikr/graphics/gl4/gl4_pipeline_state.hpp>
#include <vikr/shader/shader_config.hpp>


namespace vikr {


class Framebuffer;
class GL4RenderPass;
class GL4Commandbuffer;
class GL4PipelineState;
struct TextureSampler;


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
  vvoid DrawIndexed(const vvoid *indices, vuint32 elements) override;
  vvoid SetTexture(vuint32 texture, vuint32 target, vuint32 index) override;
  
  vvoid SetRenderTarget(RenderTarget *target, vuint32 index) override;

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

  vvoid ExecuteCommands(CommandbufferList *command_buffer) override;

  vvoid SetShaderUniforms(ShaderUniformParams *params) override;
  vvoid ApplyShaderProgram(Shader *shader) override;
  vvoid QueryVertexbuffer(Vertexbuffer *buffer) override;

  vvoid SetRenderPass(RenderPass *pass) override;
  vvoid BeginRecord(Commandbuffer *buf) override; 
  vvoid EndRecord() override;

  RenderPass *GetRenderPass() override;
  PipelineState *GetPipelineState() override;

  vvoid Present() override;

private:

  vvoid ClearTextures();

  GL4PipelineState m_currPipeline;

  //vuint32 m_currShaderProgram                     = 0;
  GL4RenderPass *m_currRenderPass                 = nullptr;
  std::vector<TextureSampler> m_currTextures;
  GL4Commandbuffer *m_recordCommandbuffer         = nullptr;
};
} // vikr
#endif // __VIKR_GL4_CONTEXT_HPP