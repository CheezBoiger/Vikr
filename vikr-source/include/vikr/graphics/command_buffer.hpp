//
// Copyright (c) Mario Garcia, Under the MIT License.
//
//
//  Commandbuffers handle commands that must be sent to the gpu for execution. Think of them
//  as an audio recorder, you say what you want the listener to do, with the exact instructions,
//  and the listener can replay the instuctions over and over if need be, to do what you want them
//  to do.
//
//  To clarify how this works we do this:
//  
//      1. Create Commandbuffer. (Different RenderContext's have different Commandbuffers).
//      2. Begin recording.
//      3. Record your commands.
//      4. End recording.
//      5. Store into a list along with other Commandbuffers.
//      6. Execute the list of Commandbuffers.
//
//
//  Where these command buffers are stored, is called a CommandbufferList. This object
//  holds all commandbuffers that are to be sent to the gpu RenderAPI:
//
//  |--------------------CommandbufferList---------------------|
//  |                                                          |
//  [Commandbuffer][Commandbuffer][Commandbuffer][Commandbuffer]
//
//  What goes on is that the Render Context reads (or replays the commandbuffers). Once 
//  the RenderContext is done, the programmer would be able to reuse the same CommandbufferList 
//  to execute again and again. This can be beneficial if a renderer needs to render a scene 
//  more than once for different renderpasses, skyboxes, reflections, and whatnot.
#ifndef __VIKR_COMMAND_BUFFER_HPP
#define __VIKR_COMMAND_BUFFER_HPP


#include <vikr/platform/vikr_api.hpp>
#include <vikr/platform/vikr_types.hpp>

#include <vikr/shader/shader_uniform_params.hpp>

#include <vikr/graphics/topology.hpp>
#include <vikr/graphics/graphics_command.hpp>
#include <vikr/graphics/render_device.hpp>
#include <vikr/scene/guid_generator.hpp>

#include <vikr/graphics/blendmode.hpp>
#include <vikr/graphics/depthmode.hpp>
#include <vikr/graphics/cullmode.hpp>
#include <vikr/graphics/stencildepth.hpp>

#include <vikr/mesh/vertex.hpp>
#include <glm/glm.hpp>

#include <vector>
#include <list>
#include <memory>


namespace vikr {


class Shader;
class GraphicsCommand;
class RenderContext;
class RenderTarget;
class RenderPass;
class GraphicsPipelineState;
class ComputePipelineState;
class Vertexbuffer;
class ShaderProgram;
class Material;
class Framebuffer;
class Texture;

struct ShaderUniformParams;
struct Viewport;
struct Scissor2D;


///  A Commandbuffer is an object that holds the recordings of commands for the RenderContext.
///  It is not sorted, so be sure that whatever you list in the commands, the RenderContext will
///  read and execute it the exact same way (think of it as filling a queue).
///
///  NOTE: Be sure to use BeginRecord to begin recording your command, otherwise it won't record!
class Commandbuffer : public RenderDeviceObject {
public:
  Commandbuffer(GraphicsAPIType type)
    : RenderDeviceObject(type) { }

  virtual ~Commandbuffer() { }

  virtual vvoid BeginRecord() = 0;
  virtual vvoid EndRecord() = 0;
  virtual vvoid Draw(vuint32 start, vuint32 vertices, vuint32 instances) = 0;
  virtual vvoid DrawIndexed(const vvoid *indices, vuint32 vertices, vuint32 instances) = 0;
  virtual vvoid BindRenderPass(RenderPass *pass) = 0;
  virtual vvoid UnbindRenderPass() = 0;
  virtual vvoid Clear() = 0;
  virtual vvoid ClearWithColor(glm::vec4 color) = 0;
  virtual vvoid SetViewport(Viewport *viewport) = 0;
  virtual vvoid SetScissor(Scissor2D *scissor) = 0;
  virtual vvoid BindGraphicsPipelineState(GraphicsPipelineState *pipelinestate) = 0;
  virtual vvoid BindComputePipelineState(ComputePipelineState *pipelinestate) = 0;
  virtual vvoid BindVertexbuffers(Vertexbuffer *buffer) = 0;
  virtual vvoid BindMaterial(Material *material) = 0;

  ///  TODO(): This requires new in order to subdata with text! Need better optimization.
  virtual vvoid SetBufferData(VertexUsageType type, 
    std::unique_ptr<std::vector<Vertex> > data) = 0;

  // New Commands!

  virtual vbool IsRecording() = 0;
};
} // vikr
#endif // __VIKR_COMMAND_BUFFER_HPP