//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <graphics/command_buffer.hpp>
#include <graphics/render_context.hpp>
#include <graphics/graphics_command.hpp>
#include <graphics/buffer.hpp>
#include <shader/shader_uniform_params.hpp>


namespace vikr {


CommandBuffer::CommandBuffer()
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
class QueryVertexBufferSetter : public GraphicsCommand {
public:
  QueryVertexBufferSetter(VertexBuffer *buf = nullptr)
    : buffer(buf)
  { }

  vvoid Execute(RenderContext *context) override {
    context->QueryVertexBuffer(buffer);
  }

private:
  VertexBuffer *buffer;
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


//------------------------------------------------------------------------------------
//
//                              Command Buffer Functions.
//
//------------------------------------------------------------------------------------


vvoid CommandBuffer::Pushback(std::unique_ptr<GraphicsCommand> &command) {
  m_commandBuffer.push_back(std::move(command));
}


vvoid CommandBuffer::Pushback(std::vector<std::unique_ptr<GraphicsCommand> > &commands) {
  
}


vvoid CommandBuffer::SetShaderUniforms(ShaderUniformParams *params) {
   m_commandBuffer.push_back(
      std::make_unique<ShaderUniformSetter>(params));
}


vvoid CommandBuffer::SetDraw(vuint32 start, vuint32 vertices) {
  m_commandBuffer.push_back(
    std::make_unique<DrawSetter>(start, vertices));
}


vvoid CommandBuffer::SetDrawIndexed(const vvoid *indices, vuint32 size) {
  m_commandBuffer.push_back(
    std::make_unique<DrawIndexedSetter>(indices, size));
}


vvoid CommandBuffer::SetTopology(Topology topology) {
}


vvoid CommandBuffer::SetRenderTarget(RenderTarget *target) {
}


vvoid CommandBuffer::SetRenderPass(RenderPass *pass) {
}


vvoid CommandBuffer::SetClear() {
}


vvoid CommandBuffer::SetClearWithColor(glm::vec4 color) {
}


vvoid CommandBuffer::SetChangeViewport(Viewport *viewport) {
}


vvoid CommandBuffer::SetShaderProgram(vuint32 program_id) {
  m_commandBuffer.push_back(
    std::make_unique<ShaderProgramSetter>(program_id));
}


vvoid CommandBuffer::SetConfigurePipelineState(PipelineState *pipelinestate) {
}


vvoid CommandBuffer::SetQueryVertexBuffer(VertexBuffer *buffer) {
  m_commandBuffer.push_back(
    std::make_unique<QueryVertexBufferSetter>(buffer));
}


vvoid CommandBuffer::Execute(RenderContext *context) {
  context->ExecuteCommands(this);
  m_commandBuffer.clear();
}
} // vikr