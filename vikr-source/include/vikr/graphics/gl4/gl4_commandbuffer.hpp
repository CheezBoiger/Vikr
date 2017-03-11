//
// Copyright (c) Mario Garcia, under the MIT License.
//
#ifndef __VIKR_GL4_COMMANDBUFFER_HPP
#define __VIKR_GL4_COMMANDBUFFER_HPP


#include <vikr/graphics/command_buffer.hpp>
#include <vikr/graphics/gl4/gl4_graphics_command.hpp>

#include <list>
#include <vector>
#include <memory>


namespace vikr {


/// GL4Commandbuffer. It requires a little optimization, as it is
/// allocating objects that are used for handling data and the 
/// OpenGL pipeline. This is problematic, especially for comparing
/// Vulkan and OpenGL. 
///
/// Will fix this problem soon enough!
class GL4Commandbuffer : public Commandbuffer {
  VIKR_DISALLOW_COPY_AND_ASSIGN(GL4Commandbuffer);
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(GL4Commandbuffer);
  GL4Commandbuffer() : commands(0), recording(false) { }
  ~GL4Commandbuffer() { }

  vvoid BeginRecord() override;
  vvoid EndRecord() override;
  vvoid Draw(vuint32 start, vuint32 vertices) override;
  vvoid DrawIndexed(const vvoid *indices, vuint32 vertices) override;
  vvoid SetTopology(Topology topology) override;
  vvoid SetRenderTarget(RenderTarget *target) override;
  vvoid SetRenderPass(RenderPass *pass) override;
  vvoid Clear() override;
  vvoid ClearWithColor(glm::vec4 color) override;
  vvoid ChangeViewport(Viewport *viewport) override;
  vvoid SetShaderProgram(ShaderProgram *program) override;
  vvoid SetFramebuffer(Framebuffer *framebuffer) override;
  vvoid SetTexture(Texture *texture, vuint32 index) override;
  vvoid ApplyGraphicsPipelineState(GraphicsPipelineState *pipelinestate) override;
  vvoid ApplyComputePipelineState(ComputePipelineState *pipelinestate) override;
  vvoid SetBufferData(VertexUsageType type, 
    std::unique_ptr<std::vector<Vertex> > data) override;
  vvoid SetShaderUniforms(ShaderUniformParams params) override;
  vvoid SetQueryVertexbuffer(Vertexbuffer *buffer) override;
  vvoid SetMaterial(Material *material) override;
  vvoid SetBlending(vbool enable) override;
  vvoid SetDepthMode(vbool enable) override;
  vvoid SetCulling(vbool enable) override;
  vvoid SetDepthFunc(DepthFunc func) override;
  vvoid SetBlendFunc(BlendFunc src, BlendFunc dst) override;
  vvoid SetBlendEq(BlendEq eq) override;
  vvoid SetFrontFace(FrontFace face) override;
  vvoid SetCullFace(CullFace face) override;
  vvoid ForcePipelineUpdate() override;
  vvoid ClearTextures() override;  
  vbool IsRecording() override;
  vvoid Execute(GL4RenderContext *context);

private:
  vbool recording = false;
  std::vector<std::unique_ptr<GL4GraphicsCommand> > commands;
};


class GL4CommandbufferList : public CommandbufferList {
public:
  GL4CommandbufferList();
  vvoid Enqueue(Commandbuffer &buffer) override;
  vvoid Reserve(vuint32 size) override;
  vvoid Clear() override;
  std::vector<GL4Commandbuffer> &GetList() { return m_commandbuffers; }

private:
  /// commandbuffer list, holds all commandbuffers intended for
  /// rendering computation.
  std::vector<GL4Commandbuffer> m_commandbuffers;
};
} // vikr
#endif // __VIKR_GL4_COMMANDBUFFER_HPP