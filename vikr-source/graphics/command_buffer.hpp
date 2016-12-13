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


namespace vikr {


class Shader;
class GraphicsCommand;
class RenderContext;
class RenderTarget;
class RenderPass;
class PipelineState;
class VertexBuffer;

struct ShaderUniformParams;
struct Viewport;


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
  vvoid SetShaderProgram(vuint32 program_id);
  vvoid SetConfigurePipelineState(PipelineState *pipelinestate);
  vvoid SetShaderUniforms(ShaderUniformParams *params);
  vvoid SetQueryVertexBuffer(VertexBuffer *buffer);

  vvoid Execute(RenderContext *context);

private:

  std::vector<std::unique_ptr<GraphicsCommand> > m_commandBuffer;
};
} // vikr
#endif // __VIKR_COMMAND_BUFFER_HPP