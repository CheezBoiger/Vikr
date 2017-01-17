//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_COMMAND_BUFFER_HPP
#define __VIKR_COMMAND_BUFFER_HPP


#include <vikr/platform/vikr_api.hpp>
#include <vikr/platform/vikr_types.hpp>

#include <vikr/shader/shader_uniform_params.hpp>

#include <vikr/graphics/topology.hpp>
#include <vikr/graphics/graphics_command.hpp>
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
class Vertexbuffer;

struct ShaderUniformParams;
struct Viewport;


/**
  CommandBuffer to send to RenderContext. This is a raw commandbuffer,
  so sorting is not needed here.

  Manual commands must be set here.
*/
class Commandbuffer {
  VIKR_DISALLOW_COPY_AND_ASSIGN(Commandbuffer);
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(Commandbuffer);
  Commandbuffer() { }
  virtual ~Commandbuffer() { }

  virtual vvoid BeginRecord() = 0;
  virtual vvoid EndRecord() = 0;
  virtual vvoid SetDraw(vuint32 start, vuint32 vertices) = 0;
  virtual vvoid SetDrawIndexed(const vvoid *indices, vuint32 vertices) = 0;
  virtual vvoid SetTopology(Topology topology) = 0;
  virtual vvoid SetRenderTarget(RenderTarget *target) = 0;
  virtual vvoid SetRenderPass(RenderPass *pass) = 0;
  virtual vvoid SetClear() = 0;
  virtual vvoid SetClearWithColor(glm::vec4 color) = 0;
  virtual vvoid SetChangeViewport(Viewport *viewport) = 0;
  virtual vvoid SetShaderProgram(vuint32 program_id) = 0;
  virtual vvoid SetConfigurePipelineState(PipelineState *pipelinestate) = 0;
  virtual vvoid SetShaderUniforms(ShaderUniformParams params) = 0;
  virtual vvoid SetQueryVertexbuffer(Vertexbuffer *buffer) = 0;

  virtual vbool IsRecording() = 0;
};


/**
  commandbuffer list to allocate to.
*/
class CommandbufferList {
  VIKR_DISALLOW_COPY_AND_ASSIGN(CommandbufferList);
public:
  CommandbufferList() { }
  VIKR_DEFAULT_MOVE_AND_ASSIGN(CommandbufferList);
  vvoid PushBack(std::unique_ptr<Commandbuffer> &buffer) {
    if (buffer) {
      // This is an issue!!
      m_buffer.emplace_back(std::move(buffer));
      m_raw.emplace_back(m_buffer.back().get());
    }
  }

  vvoid Clear() {
    m_raw.clear();
    m_buffer.clear();
  }

  std::vector<Commandbuffer *> &Raw() {
    return m_raw;
  }

private:
  std::vector<std::unique_ptr<Commandbuffer> > m_buffer;
  std::vector<Commandbuffer *> m_raw;
};
} // vikr
#endif // __VIKR_COMMAND_BUFFER_HPP