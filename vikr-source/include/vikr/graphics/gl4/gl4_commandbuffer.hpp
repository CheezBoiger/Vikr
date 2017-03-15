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
  GL4Commandbuffer() 
    : commands(0)
    , recording(false)
    , Commandbuffer(vikr_API_OPENGL) { }
  
  ~GL4Commandbuffer() { }

  vvoid BeginRecord() override;
  vvoid EndRecord() override;
  vvoid Draw(vuint32 start, vuint32 vertices, vuint32 instances) override;
  vvoid DrawIndexed(const vvoid *indices, vuint32 vertices, vuint32 instances) override;
  vvoid BindVertexbuffers(Vertexbuffer *buffer) override;
  vvoid BindRenderPass(RenderPass *pass) override;
  vvoid Clear() override;
  vvoid BindMaterial(Material *material) override;
  vvoid ClearWithColor(glm::vec4 color) override;
  vvoid SetViewport(Viewport *viewport) override;
  vvoid BindGraphicsPipelineState(GraphicsPipelineState *pipelinestate) override;
  vvoid BindComputePipelineState(ComputePipelineState *pipelinestate) override;
  vvoid SetScissor(Scissor2D *scissor) override;
  vvoid SetBufferData(VertexUsageType type, 
    std::unique_ptr<std::vector<Vertex> > data) override;
  vbool IsRecording() override;
  vvoid AddCommand(GL4GraphicsCommand command) { commands.push_back(command); }

private:
  vbool recording = false;
  std::vector<GL4GraphicsCommand> commands;
};
} // vikr
#endif // __VIKR_GL4_COMMANDBUFFER_HPP