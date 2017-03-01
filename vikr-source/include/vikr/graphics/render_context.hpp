//
// Copyright (c) Mario Garcia, Under the MIT License.
//
/**
  A huge inspiration from Mogemimi's Pomdog Game Engine Architecture for the 
  Graphics API Abstraction.

  RenderContext is practically the Render API core for our graphics library.
  It is intended to act as a context for what ever Rendering API you plan to use,
  be it OpenGL, OpenGL ES, Vulkan, Metal, DirectX10-12, etc...

  We tell our gpu what we want it to do through here, which provides a neat abstraction
  from the specific details. This is rather useful as we do not need to do super specific 
  things, unless the programmer wishes to get into a more detailed context, to which this 
  interface will ultimately allow. 
*/
#ifndef __VIKR_RENDER_CONTEXT_HPP
#define __VIKR_RENDER_CONTEXT_HPP


#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <vikr/graphics/blendmode.hpp>
#include <vikr/graphics/depthmode.hpp>
#include <vikr/graphics/cullmode.hpp>
#include <vikr/graphics/stencildepth.hpp>
#include <vikr/graphics/topology.hpp>
#include <glm/glm.hpp>


namespace vikr {


class Texture;
class RenderTarget;
class RenderPass;
class RenderDevice;
class Shader;
class Commandbuffer;
class CommandbufferList;
class PipelineState;
class Vertexbuffer;
class Framebuffer;

struct ShaderUniformParams;
struct Viewport;


/**
  Render Context for which we use when rendering. 

  An inspiration from Mogemimi's Pomdog Game engine
  implementation,

  You can see her work here! 
  https://github.com/mogemimi/pomdog


*/
class RenderContext {
  VIKR_DISALLOW_COPY_AND_ASSIGN(RenderContext);
public:
  RenderContext() { }
  VIKR_DEFAULT_MOVE_AND_ASSIGN(RenderContext);
  virtual ~RenderContext() { }

  /**
    Draw function.
  */
  virtual vvoid Draw(vuint32 start, vuint32 vertices) = 0;

  /**
    Draw with indices function.
  */
  virtual vvoid DrawIndexed(const vvoid *indices, vuint32 elements) = 0;

  /**
    Set texture function.
  */
  virtual vvoid SetTexture(Texture *texture, vuint32 index) = 0;
    
  /**
    Set Rendertarget.
  */
  virtual vvoid SetRenderTarget(RenderTarget *target, vuint32 index) = 0;

  /**
    Set the Framebuffer to use in this context. Passing nullptr will set to default framebuffer.
  */
  virtual vvoid SetFramebuffer(Framebuffer *framebuffer) = 0;

  /**
    Set the Blend equation to use.
  */
  virtual vvoid SetBlendEq(BlendEq eq) = 0;

  /**
    Set the blend function for both the context source and destination.
  */
  virtual vvoid SetBlendMode(BlendFunc src, BlendFunc dst) = 0;

  /**
    Set the Depth function, this is mainly kept in default.
  */
  virtual vvoid SetDepthFunc(DepthFunc depth) = 0;

  /**
    Enable culling mode if necessary.
  */
  virtual vvoid EnableCullMode(vbool enable) = 0;

  /**
    Set the blend mode for the current context.
  */
  virtual vvoid EnableBlendMode(vbool enable) = 0;  

  /**
    Enable depth mode if needed. This is used for 3D graphics.
  */
  virtual vvoid EnableDepthMode(vbool enable) = 0;

  /**
    Set the face that is to be culled away.
  */
  virtual vvoid SetCullFace(CullFace face) = 0;

  /**
    Set the Face cycle to be clockwise or counter-clockwise. this is to 
    tell the vertex assembly the winding order of how vertices describe a 
    patch and whatnot.
  */
  virtual vvoid SetFrontFace(FrontFace face) = 0;

  /**
    Begin recording a command buffer. This tells the Context that 
    a thread is handling the rendering context.
  */
  virtual vvoid BeginRecord(Commandbuffer *buf) = 0;

  /**
    End the recording, this tells Context that a thread has successfully stopped
    recording.
  */
  virtual vvoid EndRecord() = 0;
  
  /**
    Clear the screen.
  */
  virtual vvoid Clear() = 0;

  /**
    Flush the screen with a specified color.
  */
  virtual vvoid ClearWithColor(glm::vec4 color) = 0;

  /**
    Change the Viewport of the screen.
  */
  virtual vvoid ChangeViewport(Viewport *port) = 0;

  /**
    Topology.
  */
  virtual vvoid ChangeTopology(Topology topology) = 0;

  /**
    Digest, or execute commands immediately.
  */
  virtual vvoid ExecuteCommands(CommandbufferList *command_buffer) = 0;

  /**
    Sets the Shader uniforms when needed.
  */
  virtual vvoid SetShaderUniforms(ShaderUniformParams *params) = 0;

  /**
    Query the Vertex buffer, in this case, it must be called everytime
    you plan to draw.
  */
  virtual vvoid QueryVertexbuffer(Vertexbuffer *buffer) = 0;

  /**
    Grab the current pipeline state
  */
  virtual PipelineState *GetPipelineState() = 0;

  /**
    Set the pipeline state.
  */
  virtual vvoid ApplyPipelineState(PipelineState *pipeline) = 0;

  /**
    Present the Image onto the screen.
  */
  virtual vvoid Present() = 0;


  virtual Framebuffer *GetFramebuffer() = 0;
};
} // vikr
#endif // __VIKR_RENDER_CONTEXT_HPP