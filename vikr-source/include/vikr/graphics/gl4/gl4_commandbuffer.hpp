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


/**
  GL4Commandbuffer.
*/
class GL4Commandbuffer : public Commandbuffer {
  VIKR_DISALLOW_COPY_AND_ASSIGN(GL4Commandbuffer);
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(GL4Commandbuffer);
  GL4Commandbuffer() : commands(0), recording(false) { }
  ~GL4Commandbuffer() { }

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

  
  vvoid SetFramebuffer(Framebuffer *framebuffer) override;


  vvoid SetTexture(Texture *texture, vuint32 index) override;


  vvoid SetConfigurePipelineState(PipelineState *pipelinestate) override;


  vvoid SetBufferSubData(vint32 offset, vuint32 size, 
    vreal32 *data, vbool heap_allocated = false) override;


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


  vbool IsRecording() override;
  

  vvoid Execute(GL4RenderContext *context);

private:
  vbool recording = false;
  std::vector<std::unique_ptr<GL4GraphicsCommand> > commands;
};


class GL4CommandbufferList : public CommandbufferList {
public:
  GL4CommandbufferList();
  vvoid PushBack(Commandbuffer &buffer) override;
  vvoid Clear() override;
  
  std::list<Commandbuffer *> &Raw() override;

private:

  // TODO(): Needs better optimization!
  // Vector will ruin m_raw ptr data, need a better solution...
  std::list<GL4Commandbuffer> m_commandbuffers;
  std::list<Commandbuffer *> m_raw;
};
} // vikr
#endif // __VIKR_GL4_COMMANDBUFFER_HPP