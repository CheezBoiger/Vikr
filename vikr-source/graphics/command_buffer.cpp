//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <graphics/command_buffer.hpp>
#include <graphics/render_context.hpp>
#include <graphics/graphics_command.hpp>


namespace vikr {


CommandBuffer::CommandBuffer()
{
}


class ShaderUniformSetter : public GraphicsCommand {
public:
  ShaderUniformSetter(ShaderUniformFunction f)
    : func(f) { }

  vvoid Execute(RenderContext *context) override {
    func();
  }
  
private:
  ShaderUniformFunction func;
};


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


vvoid CommandBuffer::Pushback(std::unique_ptr<GraphicsCommand> &command) {
  m_commandBuffer.push_back(std::move(command));
}


vvoid CommandBuffer::Pushback(std::vector<std::unique_ptr<GraphicsCommand> > &commands) {
  
}


vvoid CommandBuffer::SetShaderUniforms(ShaderUniformFunction func) {
   m_commandBuffer.push_back(
      std::make_unique<ShaderUniformSetter>(func));
}


vvoid CommandBuffer::SetDraw(vuint32 start, vuint32 vertices) {
  m_commandBuffer.push_back(
    std::make_unique<DrawSetter>(start, vertices));
}


vvoid CommandBuffer::SetDrawIndexed(const vvoid *indices, vuint32 vertices) {
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


vvoid CommandBuffer::SetUseShader(Shader *shader) {
}


vvoid CommandBuffer::SetConfigurePipelineState(PipelineState *pipelinestate) {
}
} // vikr