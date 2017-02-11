//
// Copyright (c) Mario Garcia, under the MIT License.
//
#ifndef __VIKR_GL4_COMMANDBUFFER_HPP
#define __VIKR_GL4_COMMANDBUFFER_HPP


#include <vikr/graphics/command_buffer.hpp>
#include <vikr/graphics/gl4/gl4_graphics_command.hpp>

#include <vector>
#include <memory>


namespace vikr {


/**
  GL4Commandbuffer.
*/
class GL4Commandbuffer : public Commandbuffer {
  VIKR_DISALLOW_COPY_AND_ASSIGN(GL4Commandbuffer);
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(GL4Commandbuffer);
  GL4Commandbuffer() { }


  vvoid BeginRecord() override;


  vvoid EndRecord() override;


  vvoid SetDraw(vuint32 start, vuint32 vertices) override;


  vvoid SetDrawIndexed(const vvoid *indices, vuint32 vertices) override;


  vvoid SetTopology(Topology topology) override;


  vvoid SetRenderTarget(RenderTarget *target) override;


  vvoid SetRenderPass(RenderPass *pass) override;


  vvoid SetClear() override;


  vvoid SetClearWithColor(glm::vec4 color) override;


  vvoid SetChangeViewport(Viewport *viewport) override;


  vvoid SetShaderProgram(ShaderProgram *program) override;


  vvoid SetConfigurePipelineState(PipelineState *pipelinestate) override;


  vvoid SetShaderUniforms(ShaderUniformParams params) override;


  vvoid SetQueryVertexbuffer(Vertexbuffer *buffer) override;


  vbool IsRecording() override;
  

  vvoid Execute(GL4RenderContext *context);

private:
  vbool recording = false;
  std::vector<std::unique_ptr<GL4GraphicsCommand> > commands;
};
} // vikr
#endif // __VIKR_GL4_COMMANDBUFFER_HPP