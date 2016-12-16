//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <graphics/command_buffer.hpp>
#include <graphics/render_context.hpp>
#include <graphics/graphics_command.hpp>
#include <graphics/vertexbuffer.hpp>
#include <shader/shader_uniform_params.hpp>


namespace vikr {


Commandbuffer::Commandbuffer()
{
}


/**
  ShaderUniformSetter.
*/
class ShaderUniformSetter : public GraphicsCommand {
public:
  ShaderUniformSetter(ShaderUniformParams *f)
    : params(*f) { }

  vvoid Execute(RenderContext *context) override {
    context->SetShaderUniforms(&params);
  }
  
private:
  ShaderUniformParams params;
};


/**
  DrawSetter.
*/
class DrawSetter : public GraphicsCommand {
public:
  DrawSetter(vuint32 start, vuint32 vertices)
    : start(start)
    , vertices(vertices)
  { }

  vvoid Execute(RenderContext *context) override {
    context->Draw(start, vertices);
  }

private:
  vuint32 start       = 0;
  vuint32 vertices    = 0;
};


/**
  ShaderProgramSetter.
*/
class ShaderProgramSetter : public GraphicsCommand {
public:
  ShaderProgramSetter(vuint32 program_id)
    : program_id(program_id)
  { }

  vvoid Execute(RenderContext *context) override {
    context->ApplyShaderProgram(program_id);    
  }

private:
  vuint32 program_id;
};


/**
  QueryVertexBufferSetter.
*/
class QueryVertexbufferSetter : public GraphicsCommand {
public:
  QueryVertexbufferSetter(Vertexbuffer *buf = nullptr)
    : buffer(buf)
  { }

  vvoid Execute(RenderContext *context) override {
    context->QueryVertexbuffer(buffer);
  }

private:
  Vertexbuffer *buffer;
};


/**
  DrawIndexedSetter.
*/
class DrawIndexedSetter : public GraphicsCommand {
public:
  DrawIndexedSetter(const vvoid *indices, vuint32 size) 
    : indices(indices)
    , size(size) 
  { }
  
  vvoid Execute(RenderContext *context) override {
    context->DrawIndexed(indices, size);
  }

private:
  const vvoid *indices;
  vuint32 size;
};


/**
  TopologySetter.
*/
class TopologySetter : public GraphicsCommand {
public:
  TopologySetter(Topology topo)
    : t(topo) 
  { }

  vvoid Execute(RenderContext *context) override {
    context->ChangeTopology(t);
  }

private:
  Topology t;
};


//------------------------------------------------------------------------------------
//
//                              Command Buffer Functions.
//
//------------------------------------------------------------------------------------


vvoid Commandbuffer::Pushback(std::unique_ptr<GraphicsCommand> &command) {
  m_commandBuffer.push_back(std::move(command));
}


vvoid Commandbuffer::Pushback(std::vector<std::unique_ptr<GraphicsCommand> > &commands) {
  
}


vvoid Commandbuffer::SetShaderUniforms(ShaderUniformParams *params) {
   m_commandBuffer.push_back(
      std::make_unique<ShaderUniformSetter>(params));
}


vvoid Commandbuffer::SetDraw(vuint32 start, vuint32 vertices) {
  m_commandBuffer.push_back(
    std::make_unique<DrawSetter>(start, vertices));
}


vvoid Commandbuffer::SetDrawIndexed(const vvoid *indices, vuint32 size) {
  m_commandBuffer.push_back(
    std::make_unique<DrawIndexedSetter>(indices, size));
}


vvoid Commandbuffer::SetTopology(Topology topology) {
  m_commandBuffer.push_back(
    std::make_unique<TopologySetter>(topology));
}


vvoid Commandbuffer::SetRenderTarget(RenderTarget *target) {
}


vvoid Commandbuffer::SetRenderPass(RenderPass *pass) {
}


vvoid Commandbuffer::SetClear() {
}


vvoid Commandbuffer::SetClearWithColor(glm::vec4 color) {
}


vvoid Commandbuffer::SetChangeViewport(Viewport *viewport) {
}


vvoid Commandbuffer::SetShaderProgram(vuint32 program_id) {
  m_commandBuffer.push_back(
    std::make_unique<ShaderProgramSetter>(program_id));
}


vvoid Commandbuffer::SetConfigurePipelineState(PipelineState *pipelinestate) {
}


vvoid Commandbuffer::SetQueryVertexbuffer(Vertexbuffer *buffer) {
  m_commandBuffer.push_back(
    std::make_unique<QueryVertexbufferSetter>(buffer));
}


vvoid Commandbuffer::Execute(RenderContext *context) {
  context->ExecuteCommands(this);
  m_commandBuffer.clear();
}
} // vikr