//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/graphics/gl4/gl4_commandbuffer.hpp>
#include <vikr/graphics/gl4/gl4_context.hpp>
#include <vikr/shader/shader_uniform_params.hpp>
#include <vikr/shader/glsl/glsl_program.hpp>
#include <vikr/shader/material.hpp>
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
    cx->GetPipelineState()->SetShaderProgram(program);
  }

private:
  ShaderProgram *program;
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


vvoid GL4Commandbuffer::SetDraw(vuint32 start, vuint32 vertices) {
  CHECK_RECORDING();
  commands.push_back(std::make_unique<DrawSetter>(start, vertices));
}


vvoid GL4Commandbuffer::SetDrawIndexed(const vvoid *indices, vuint32 vertices) {
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


vvoid GL4Commandbuffer::SetConfigurePipelineState(PipelineState *state) {
}


vvoid GL4Commandbuffer::SetQueryVertexbuffer(Vertexbuffer *buffer) {
  CHECK_RECORDING();
  commands.push_back(std::make_unique<QueryVertexbufferSetter>(buffer));
}


vvoid GL4Commandbuffer::SetMaterial(Material *material) {
  CHECK_RECORDING();
  commands.push_back(std::make_unique<MaterialSetter>(material));
}


vvoid GL4Commandbuffer::SetChangeViewport(Viewport *viewport) {
  CHECK_RECORDING();
}


vvoid GL4Commandbuffer::SetClear() {
  CHECK_RECORDING();
}


vvoid GL4Commandbuffer::SetClearWithColor(glm::vec4 color) {
  CHECK_RECORDING();
}


vvoid GL4Commandbuffer::Execute(GL4RenderContext * context) {
  for (auto &command : commands) {
    command->Execute(context);
  }
}
} // vikr