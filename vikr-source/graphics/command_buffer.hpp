//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_COMMAND_BUFFER_HPP
#define __VIKR_COMMAND_BUFFER_HPP


#include <platform/vikr_api.hpp>
#include <platform/vikr_types.hpp>
#include <graphics/topology.hpp>
#include <graphics/graphics_command.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <functional>


namespace vikr {


class Shader;
class GraphicsCommand;
class RenderContext;
class RenderTarget;
class RenderPass;
class Viewport;
class PipelineState;

/*
  Speed is key, and we need to say as much as we can.
*/
using ShaderUniformFunction = std::function<vvoid()>;


/**
  CommandBuffer to send to RenderContext. This is a raw commandbuffer,
  so sorting is not needed here.

  Manual commands must be set here.
*/
class CommandBuffer {
public:
  CommandBuffer();

  vvoid Clear() { m_commandBuffer.clear(); }

  vvoid Pushback(std::unique_ptr<GraphicsCommand> &command);
  vvoid Pushback(std::vector<std::unique_ptr<GraphicsCommand> > &commands);
  
  std::vector<std::unique_ptr<GraphicsCommand> > &GetCommands() { return m_commandBuffer; }


  vvoid SetDraw(vuint32 start, vuint32 vertices);
  vvoid SetDrawIndexed(const vvoid *indices, vuint32 vertices);
  vvoid SetTopology(Topology topology);
  vvoid SetRenderTarget(RenderTarget *target);
  vvoid SetRenderPass(RenderPass *pass);
  vvoid SetClear();
  vvoid SetClearWithColor(glm::vec4 color);
  vvoid SetChangeViewport(Viewport *viewport);
  vvoid SetUseShader(Shader *shader);
  vvoid SetConfigurePipelineState(PipelineState *pipelinestate);
  vvoid SetShaderUniforms(ShaderUniformFunction func);

private:

  std::vector<std::unique_ptr<GraphicsCommand> > m_commandBuffer;
};
} // vikr
#endif // __VIKR_COMMAND_BUFFER_HPP