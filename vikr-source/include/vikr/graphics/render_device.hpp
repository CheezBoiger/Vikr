//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_RENDER_DEVICE_HPP
#define __VIKR_RENDER_DEVICE_HPP


#include <vikr/platform/vikr_api.hpp>
#include <vikr/platform/vikr_types.hpp>
#include <vikr/graphics/graphics_config.hpp>
#include <vikr/graphics/vertexbuffer.hpp>
#include <vikr/graphics/render_target.hpp>
#include <vikr/graphics/render_pass.hpp>
#include <vikr/graphics/command_buffer.hpp>
#include <vikr/shader/texture.hpp>
#include <vikr/mesh/imesh.hpp>
#include <vikr/scene/guid_generator.hpp>

#include <string>


namespace vikr {


class Texture;
class Framebuffer;
class Renderbuffer;
class RenderTexture;
class RenderTarget;
class RenderPass;
class Shader;
class Material;
class ResourceManager;
class RenderContext;
class Vertexbuffer;
class Cubemap;
class Uniformbuffer;


///  Render Device is an interface, with a driver type format.
///  Creates our buffers to use, as well as our textures, shaders, and 
///  framebuffers.
class RenderDevice {
  VIKR_DISALLOW_COPY_AND_ASSIGN(RenderDevice);
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(RenderDevice);
  RenderDevice() { }
  virtual ~RenderDevice() { }

  ///  Get the Shader language used by this Render Device.
  virtual std::string GetShaderLanguage() = 0;

  ///  Generate a framebuffer.
  virtual Framebuffer *CreateFramebuffer() = 0;

  ///  Create vertex buffer id.
  virtual Vertexbuffer *CreateVertexbuffer(VertexUsageType type, 
    std::vector<Vertex> &vertices, std::vector<vuint32> &indices = std::vector<vuint32>()) = 0;

  ///  Get the contet of this Rendering Device.
  virtual RenderContext *GetContext() = 0;

  ///  Create a cubemap object.
  virtual Cubemap *CreateCubemap() = 0;

  ///  Generate RenderPass.
  virtual RenderPass *CreateRenderPass() = 0;

  ///  Destroys the Renderpass in the device.
  virtual vbool DestroyRenderPass(guid_t id) = 0;

  ///  Destroys the Vertexbuffer stored inside the device.
  virtual vbool DestroyVertexbuffer(guid_t id) = 0;
  
  ///  Destorys the cubemap stored by the device.
  virtual vbool DestroyCubemap(guid_t id) = 0;

  ///  Destroys the Framebuffer inside the device.
  virtual vbool DestroyFramebuffer(guid_t id) = 0;

  /// Create a command buffer to handle recording commands into an organized batch,
  /// which will then be stored inside the specified CommandbufferList. This
  /// Commandbuffer is not dynamically allocated!
  virtual Commandbuffer &CreateCommandbuffer() = 0;

  /// Create a Uniformbuffer object.
  virtual Uniformbuffer *CreateUniformbuffer() = 0;

  /// Get the uniform buffer object created.
  virtual Uniformbuffer *GetUniformbuffer(guid_t id) = 0;

  /// Destroy the uniform buffer object, provided it's guid_t.
  virtual vbool DestroyUniformbuffer(guid_t id) = 0;

  /// Create a Graphics pipeline state for the Rendering device to use.
  virtual GraphicsPipelineState *CreateGraphicsPipelineState(std::string name) = 0;
  virtual GraphicsPipelineState *GetGraphicsPipelineState(guid_t id) = 0;
  virtual vbool DestroyGraphicsPipelineState(guid_t id) = 0;

  virtual ComputePipelineState *CreateComputePipelineState(std::string name) = 0;
  virtual ComputePipelineState *GetComputePipelineState(guid_t id) = 0;
  virtual vbool DestroyComputePipelineState(guid_t id) = 0;

  /// Create a shader, and store it into Resources, the id of the shader will
  /// be returned. Resources takes care of this.
  virtual Shader *CreateShader(std::string name, ShaderStage stage) = 0;
  virtual Shader *GetShader(guid_t id) = 0;
  virtual vbool DestroyShader(guid_t id) = 0;


  virtual ShaderProgram *CreateShaderProgram() = 0;
  virtual ShaderProgram *GetShaderProgram(guid_t id) = 0;
  virtual vbool DestroyShaderProgram(guid_t id) = 0;

  virtual Texture *CreateTexture(std::string name, TextureTarget target, 
    std::string filepath, vbool alpha) = 0;
  virtual Texture *GetTexture(guid_t id) = 0;
  virtual vbool DestroyTexture(guid_t id) = 0;

  virtual GraphicsHardwareInfo GetHardwareInformation() = 0;

  virtual GraphicsPerformanceInfo GetPerformanceInformation() = 0;

  /// Submit a commandbuffer through the RenderDevice.
  /// This ultimately deprecates RenderContext, As it is no longer needed
  /// for rendering. In terms of vulkan, everything gets submitted to the 
  /// a queue buffer in the GPU, so we will attempt to mimick that feature
  /// with OpenGL. 
  virtual vbool SubmitCommandbuffer(Commandbuffer *commandbuffer) = 0;
};
} // vikr
#endif // __VIKR_RENDER_DEVICE_HPP