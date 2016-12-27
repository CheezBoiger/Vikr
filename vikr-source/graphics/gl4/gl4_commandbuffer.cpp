//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <graphics/gl4/gl4_commandbuffer.hpp>
#include <graphics/gl4/gl4_context.hpp>
#include <shader/shader_uniform_params.hpp>


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


class ShaderProgramSetter : public GL4GraphicsCommand {
public:
  ShaderProgramSetter(vuint32 id) 
    : id(id) { }

  vvoid Execute(GL4RenderContext *cx) override {
    cx->ApplyShaderProgram(id);
  }

private:
  vuint32 id;
};





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
  commands.push_back(std::make_unique<DrawSetter>(start, vertices));
}


vvoid GL4Commandbuffer::SetDrawIndexed(const vvoid *indices, vuint32 vertices) {
  commands.push_back(std::make_unique<DrawIndexedSetter>(indices, vertices));
}


vvoid GL4Commandbuffer::SetTopology(Topology topology) {
  commands.push_back(std::make_unique<TopologySetter>(topology));
}


vvoid GL4Commandbuffer::SetShaderProgram(vuint32 id) {
  commands.push_back(std::make_unique<ShaderProgramSetter>(id));
}


vvoid GL4Commandbuffer::SetShaderUniforms(ShaderUniformParams params) {
  commands.push_back(std::make_unique<ShaderUniformSetter>(params));
}


vvoid GL4Commandbuffer::SetRenderTarget(RenderTarget *target) {
}


vvoid GL4Commandbuffer::SetRenderPass(RenderPass *pass) {
}


vvoid GL4Commandbuffer::SetConfigurePipelineState(PipelineState *state) {
}


vvoid GL4Commandbuffer::SetQueryVertexbuffer(Vertexbuffer *buffer) {
  commands.push_back(std::make_unique<QueryVertexbufferSetter>(buffer));
}


vvoid GL4Commandbuffer::SetChangeViewport(Viewport *viewport) {
}


vvoid GL4Commandbuffer::SetClear() {
}


vvoid GL4Commandbuffer::SetClearWithColor(glm::vec4 color) {
}


vvoid GL4Commandbuffer::Execute(GL4RenderContext * context) {
  for (auto &command : commands) {
    command->Execute(context);
  }
}
} // vikr