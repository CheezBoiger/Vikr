//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/graphics/gl4/gl4_commandbuffer.hpp>
#include <vikr/graphics/gl4/gl4_context.hpp>
#include <vikr/shader/shader_uniform_params.hpp>
#include <vikr/graphics/gl4/gl4_vertexbuffer.hpp>
#include <vikr/shader/glsl/glsl_program.hpp>
#include <vikr/shader/material.hpp>
#include <vikr/resources/threading/vikr_thread.hpp>
#include <vikr/util/vikr_log.hpp>

#include <list>


#define CHECK_RECORDING() \
  if (!IsRecording()) { \
    VikrLog::DisplayMessage(VIKR_ERROR, \
      "You must call Record() in order to record commands! Cancelling..."); \
    return; \
  } 


namespace vikr {


class DrawSetter : public GL4GraphicsCommand {
public:
  DrawSetter(vuint32 start, vuint32 vertices)
    : start(start)
    , vertices(vertices) { }

  vvoid Execute(GL4RenderContext *context) override {
    context->Draw(start, vertices);
  }

private:
  vuint32 start;
  vuint32 vertices;
};


class DrawIndexedSetter : public GL4GraphicsCommand {
public:
  DrawIndexedSetter(const vvoid *indices, vuint32 vertices)
    : indices(indices)
    , vertices(vertices) { }

  vvoid Execute(GL4RenderContext *context) override {
    context->DrawIndexed(indices, vertices);
  }

private:
  const vvoid *indices;
  vuint32 vertices;
};


class TopologySetter : public GL4GraphicsCommand {
public:
  TopologySetter(Topology topology)
    : topology(topology) { }

  vvoid Execute(GL4RenderContext *cx) override {
    cx->ChangeTopology(topology);
  }

private:
  Topology topology;
};


class QueryVertexbufferSetter : public GL4GraphicsCommand {
public:
  QueryVertexbufferSetter(Vertexbuffer *buffer)
    : buffer(buffer) { }

  vvoid Execute(GL4RenderContext *cx) override {
    cx->QueryVertexbuffer(buffer);
  }

private:
  Vertexbuffer *buffer;
};


class ShaderUniformSetter : public GL4GraphicsCommand {
public:
  ShaderUniformSetter(ShaderUniformParams params)
    : params(params) { }

  vvoid Execute(GL4RenderContext *cx) override {
    cx->SetShaderUniforms(&params);
  }
  
private:
  ShaderUniformParams params;
};


class MaterialSetter : public GL4GraphicsCommand {
public:
  MaterialSetter(Material *params)
    : params(params) { }

  vvoid Execute(GL4RenderContext *cx) override {
    cx->SetMaterial(params);
  }

private:
  Material *params;
};


class ShaderProgramSetter : public GL4GraphicsCommand {
public:
  ShaderProgramSetter(ShaderProgram *pgrm) 
    : program(pgrm) { }

  vvoid Execute(GL4RenderContext *cx) override {
    cx->GetGraphicsPipelineState()->SetShaderProgram(program);
  }

private:
  ShaderProgram *program;
};


class BlendingSetter : public GL4GraphicsCommand {
public:
  BlendingSetter(vbool enable) 
    : enable(enable) { }

  vvoid Execute(GL4RenderContext *cx) override {
    cx->GetGraphicsPipelineState()->SetBlendMode(enable);
  }
private:
  vbool enable;
};


class DepthModeSetter : public GL4GraphicsCommand {
public:
  DepthModeSetter(vbool enable)
    : enable(enable) { }

  vvoid Execute(GL4RenderContext *cx) override {
    cx->GetGraphicsPipelineState()->SetDepthMode(enable);
  }

private:
  vbool enable;
};


class CullingSetter : public GL4GraphicsCommand {
public:
  CullingSetter(vbool enable)
    : enable(enable) { }

  vvoid Execute(GL4RenderContext *cx) override {
    cx->GetGraphicsPipelineState()->SetCullMode(enable);
  }

private:
  vbool enable;
};


class DepthFuncSetter : public GL4GraphicsCommand {
public:
  DepthFuncSetter(DepthFunc func)
    : func(func) { }

  vvoid Execute(GL4RenderContext *cx) {
    cx->GetGraphicsPipelineState()->SetDepthFunc(func);
  }
  
private:
  DepthFunc func;
};


class BlendFuncSetter : public GL4GraphicsCommand {
public:
  BlendFuncSetter(BlendFunc src, BlendFunc dst)
    : src(src)
    , dst(dst) { }

  vvoid Execute(GL4RenderContext *cx) override {
    cx->GetGraphicsPipelineState()->SetBlendFunc(src, dst);
  }

private:
  BlendFunc src;
  BlendFunc dst;
};


class BlendEqSetter : public GL4GraphicsCommand {
public:
  BlendEqSetter(BlendEq eq)
    : eq(eq) { }

  vvoid Execute(GL4RenderContext *cx) override {
    cx->GetGraphicsPipelineState()->SetBlendEq(eq);
  }
private:
  BlendEq eq;
};


class FrontFaceSetter : public GL4GraphicsCommand {
public:
  FrontFaceSetter(FrontFace face) 
    : face(face) { }

  vvoid Execute(GL4RenderContext *cx) override {
    cx->GetGraphicsPipelineState()->SetFrontFace(face);
  }
  
private:
  FrontFace face;
};


class CullFaceSetter : public GL4GraphicsCommand {
public:
  CullFaceSetter(CullFace face) 
    : face(face) { }
  
  vvoid Execute(GL4RenderContext *cx) override {
    cx->GetGraphicsPipelineState()->SetCullFace(face);
  }
  
private:
  CullFace face;
};


class PipelineUpdateForcer : public GL4GraphicsCommand {
public:
  PipelineUpdateForcer() { }

  vvoid Execute(GL4RenderContext *cx) override {
    cx->GetGraphicsPipelineState()->Update();
  } 
};


class FramebufferSetter : public GL4GraphicsCommand {
public:
  FramebufferSetter(Framebuffer *framebuffer)
    : framebuffer(framebuffer) { }

  vvoid Execute(GL4RenderContext *cx) override {
    cx->SetFramebuffer(framebuffer);
  }
private:
  Framebuffer *framebuffer;
};


class ClearSetter : public GL4GraphicsCommand {
public:
  ClearSetter() { }

  vvoid Execute(GL4RenderContext *cx) override {
    cx->Clear();
  }
};


class ClearWithColorSetter : public GL4GraphicsCommand {
public:
  ClearWithColorSetter(glm::vec4 color)
    : color(color) { }

  vvoid Execute(GL4RenderContext *cx) override {
    cx->ClearWithColor(color);
  }

private:
  glm::vec4 color;
};


class TextureSetter : public GL4GraphicsCommand {
public:
  TextureSetter(Texture *texture, vuint32 index) 
    : texture(texture)
    , index(index) { }

  vvoid Execute(GL4RenderContext *cx) override {
    cx->SetTexture(texture, index);
  }

private:
  Texture *texture;
  vuint32 index;
};


class VertexBufferSubDataSetter : public GL4GraphicsCommand {
public:
  VertexBufferSubDataSetter(vint32 offset, vuint32 size, vreal32 *data, vbool heap_allocated)
    : offset(offset)
    , size(size)
    , data(data)
    , heap_allocated(heap_allocated)
    { 
    }

  ~VertexBufferSubDataSetter()
  {
    if (data && heap_allocated) {
      delete[] data;
    }
  }

  vvoid Execute(GL4RenderContext *cx) override {
    GL4Vertexbuffer *buffer = cx->GetCurrentVertexbuffer();
    if (buffer && data) {
      buffer->BufferSubData(offset, (size * sizeof(vreal32)), (vvoid *)data);
    }
  }

private:
  vint32 offset; 
  vuint32 size; 
  vreal32 *data;
  const vbool heap_allocated;
};


GL4CommandbufferList::GL4CommandbufferList()
  : m_commandbuffers(0)
  , m_raw(0)
{
}


vvoid GL4CommandbufferList::PushBack(Commandbuffer &buffer) {
  GL4Commandbuffer &b = static_cast<GL4Commandbuffer &>(buffer);
  m_commandbuffers.push_back(std::move(b));
  m_raw.push_back(&m_commandbuffers.back());
}


std::list<Commandbuffer *> &GL4CommandbufferList::Raw() {
  return m_raw;
}


vvoid GL4CommandbufferList::Clear() {
  m_commandbuffers.clear();
  m_raw.clear();
}


vvoid GL4Commandbuffer::BeginRecord() {
  recording = true; 
}


vvoid GL4Commandbuffer::EndRecord() {
  recording = false;
}


vbool GL4Commandbuffer::IsRecording() {
  return recording;
}


vvoid GL4Commandbuffer::Draw(vuint32 start, vuint32 vertices) {
  CHECK_RECORDING();
  commands.push_back(std::make_unique<DrawSetter>(start, vertices));
}


vvoid GL4Commandbuffer::DrawIndexed(const vvoid *indices, vuint32 vertices) {
  CHECK_RECORDING();
  commands.push_back(std::make_unique<DrawIndexedSetter>(indices, vertices));
}


vvoid GL4Commandbuffer::SetTopology(Topology topology) {
  CHECK_RECORDING();
  commands.push_back(std::make_unique<TopologySetter>(topology));
}


vvoid GL4Commandbuffer::SetShaderProgram(ShaderProgram *prgm) {
  CHECK_RECORDING();
  commands.push_back(std::make_unique<ShaderProgramSetter>(prgm));
}


vvoid GL4Commandbuffer::SetShaderUniforms(ShaderUniformParams params) {
  CHECK_RECORDING();
  commands.push_back(std::make_unique<ShaderUniformSetter>(params));
}


vvoid GL4Commandbuffer::SetRenderTarget(RenderTarget *target) {
  CHECK_RECORDING();
}


vvoid GL4Commandbuffer::SetRenderPass(RenderPass *pass) {
  CHECK_RECORDING();
}


vvoid GL4Commandbuffer::ApplyGraphicsPipelineState(GraphicsPipelineState *state) {
  CHECK_RECORDING();
}


vvoid GL4Commandbuffer::SetQueryVertexbuffer(Vertexbuffer *buffer) {
  CHECK_RECORDING();
  commands.push_back(std::make_unique<QueryVertexbufferSetter>(buffer));
}


vvoid GL4Commandbuffer::SetMaterial(Material *material) {
  CHECK_RECORDING();
  commands.push_back(std::make_unique<MaterialSetter>(material));
}


vvoid GL4Commandbuffer::ChangeViewport(Viewport *viewport) {
  CHECK_RECORDING();
}


vvoid GL4Commandbuffer::Clear() {
  CHECK_RECORDING();
  commands.push_back(std::make_unique<ClearSetter>());
}


vvoid GL4Commandbuffer::ClearWithColor(glm::vec4 color) {
  CHECK_RECORDING();
  commands.push_back(std::make_unique<ClearWithColorSetter>(color));
}


vvoid GL4Commandbuffer::SetBlending(vbool enable) {
  CHECK_RECORDING();
  commands.push_back(std::make_unique<BlendingSetter>(enable));
}


vvoid GL4Commandbuffer::SetDepthMode(vbool enable) {
  CHECK_RECORDING();
  commands.push_back(std::make_unique<DepthModeSetter>(enable));
}


vvoid GL4Commandbuffer::SetCulling(vbool enable) {
  CHECK_RECORDING();
  commands.push_back(std::make_unique<CullingSetter>(enable));
}


vvoid GL4Commandbuffer::SetDepthFunc(DepthFunc func) {
  CHECK_RECORDING();
  commands.push_back(std::make_unique<DepthFuncSetter>(func));
}


vvoid GL4Commandbuffer::SetBlendFunc(BlendFunc src, BlendFunc dst) {
  CHECK_RECORDING();
  commands.push_back(std::make_unique<BlendFuncSetter>(src, dst));
}


vvoid GL4Commandbuffer::SetBlendEq(BlendEq eq) {
  CHECK_RECORDING();
  commands.push_back(std::make_unique<BlendEqSetter>(eq));
}


vvoid GL4Commandbuffer::SetFrontFace(FrontFace face) {
  CHECK_RECORDING();
  commands.push_back(std::make_unique<FrontFaceSetter>(face));
}


vvoid GL4Commandbuffer::SetCullFace(CullFace face) {
  CHECK_RECORDING();
  commands.push_back(std::make_unique<CullFaceSetter>(face));
}


vvoid GL4Commandbuffer::ForcePipelineUpdate() {
  CHECK_RECORDING();
  commands.push_back(std::make_unique<PipelineUpdateForcer>());
}


vvoid GL4Commandbuffer::SetFramebuffer(Framebuffer *buffer) {
  CHECK_RECORDING();
  commands.push_back(std::make_unique<FramebufferSetter>(buffer));
};


vvoid GL4Commandbuffer::SetTexture(Texture *texture, vuint32 index) {
  CHECK_RECORDING();
  commands.push_back(std::make_unique<TextureSetter>(texture, index));
}


vvoid GL4Commandbuffer::SetBufferSubData(vint32 offset, vuint32 size, 
  vreal32 *data, vbool heap_allocated) 
{
  CHECK_RECORDING();
  commands.push_back(
    std::make_unique<VertexBufferSubDataSetter>(offset, size, data, heap_allocated));
}


vvoid GL4Commandbuffer::ApplyComputePipelineState(ComputePipelineState *pipeline) {
}


vvoid GL4Commandbuffer::Execute(GL4RenderContext * context) {
  for (auto &command : commands) {
    command->Execute(context);
  }
}
} // vikr