//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_RENDER_DEVICE_HPP
#define __VIKR_RENDER_DEVICE_HPP


#include <vikr/platform/vikr_api.hpp>
#include <vikr/platform/vikr_types.hpp>
#include <vikr/graphics/graphics_config.hpp>
#include <vikr/shader/texture_config.hpp>
#include <vikr/mesh/imesh.hpp>
#include <vikr/scene/guid_generator.hpp>

#include <string>


namespace vikr {


////////////////////////////////////////////////////////
// Forward abstractions that inherit RenderDeviceObject
class Texture;
class Framebuffer;
class Renderbuffer;
class RenderTexture;
class RenderTarget;
class RenderPass;
class Shader;
class Material;
class ResourceManager;
class GraphicsPipelineState;
class ComputePipelineState;
class RenderContext;
class Vertexbuffer;
class Cubemap;
class Commandbuffer;
class Uniformbuffer;
/////////////////////////////////////////////////////////


/// Render Device is an interface, with a driver type format.
/// Creates our buffers to use, as well as our textures, shaders, and 
/// framebuffers. It also serves as the Rendering Hardware Interface for
/// practically anything involving rendering. Commandbuffers are executed by
/// the RenderDevice.
class RenderDevice {
  VIKR_DISALLOW_COPY_AND_ASSIGN(RenderDevice);
public:
  RenderDevice(GraphicsAPIType type = vikr_API_UNKNOWN) 
    : m_api(type) { }

  virtual ~RenderDevice() { }

  ///  Get the Shader language used by this Render Device.
  virtual std::string GetShaderLanguage() = 0;

  ///  Generate a framebuffer.
  virtual Framebuffer *CreateFramebuffer() = 0;

  ///  Create vertex buffer id.
  virtual Vertexbuffer *CreateVertexbuffer(VertexUsageType type, 
    std::vector<Vertex> &vertices, std::vector<vuint32> &indices = std::vector<vuint32>()) = 0;

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
  /// Determine whether or not the pipeline will be inherited by multiple
  /// new pipelines, otherwise if the parent pipeline is not a derivative,
  /// calling CreateChild() will return a nullptr.
  virtual GraphicsPipelineState *CreateGraphicsPipelineState(vbool derivative) = 0;

  /// Get the GraphicsPipelineState with the specified guid_t. Returns
  /// nullptr if no graphics pipelinestate was found with that id. 
  virtual GraphicsPipelineState *GetGraphicsPipelineState(guid_t id) = 0;

  /// Destroy a GraphicsPipelineState provided the guid. Returns
  /// true if a graphics pipeline was successfully destroyed, otherwise
  /// false if unsuccessful. 
  virtual vbool DestroyGraphicsPipelineState(guid_t id) = 0;

  virtual ComputePipelineState *CreateComputePipelineState(std::string name) = 0;
  virtual ComputePipelineState *GetComputePipelineState(guid_t id) = 0;
  virtual vbool DestroyComputePipelineState(guid_t id) = 0;

  /// Create a shader, and store it into RenderDevice Resources, the id of the shader will
  /// be returned. Resources takes care of this.
  virtual Shader *CreateShader(std::string name, ShaderStage stage) = 0;

  /// Get the shader with the provided id. If no shader was found with the provided
  /// id, then a nullptr is returned.
  virtual Shader *GetShader(guid_t id) = 0;

  /// Destroys the Shader provided with the id. If no shader was found, or 
  /// the shader unsuccessfully destroyed, false will be returned.
  virtual vbool DestroyShader(guid_t id) = 0;

  /// Create a texture object from this RenderDevice.
  virtual Texture *CreateTexture(std::string name, TextureTarget target, 
    std::string filepath, vbool alpha) = 0;

  /// Get the texture stored in resources, provided the guid_t of the
  /// texture.
  virtual Texture *GetTexture(guid_t id) = 0;

  /// Destroy the Texture object that is stored. Returns true if the 
  /// Texture was found and successfully destroyed, false otherwise.
  virtual vbool DestroyTexture(guid_t id) = 0;

  /// Get the Hardware information of this device.
  virtual GraphicsHardwareInfo GetHardwareInformation() = 0;

  /// Get the Performance of this device.
  virtual GraphicsPerformanceInfo GetPerformanceInformation() = 0;

  /// Create a material object to use for the RenderDevice.
  /// This is ultimately a descriptor set for Vulkan, and simply
  /// just a clump of mapped values for OpenGL. 
  virtual Material *CreateMaterial() = 0;

  /// Get the material provided with the necessary id.
  virtual Material *GetMaterial(guid_t id) = 0;

  /// Destroy the material.
  virtual vbool DestroyMaterial(guid_t id) = 0;

  /// Submit a commandbuffer through the RenderDevice.
  /// This ultimately deprecates RenderContext, As it is no longer needed
  /// for rendering. In terms of vulkan, everything gets submitted to the 
  /// a queue buffer in the GPU, so we will attempt to mimick that feature
  /// with OpenGL. 
  virtual vbool SubmitCommandbuffer(Commandbuffer *commandbuffer) = 0;

  /// Present the Rendered Frame.
  virtual vvoid Present() = 0;

  GraphicsAPIType GetAPIType() { return m_api; }

private:
  GraphicsAPIType m_api;
};


/// RenderDeviceObject, an object that is created by the RenderDevice.
/// This is useful for referencing the Rendering Device that this 
/// device came from. It is also useful for Vulkan in this case.
class RenderDeviceObject {
public:
  /// Render Device Object describes the API from which is was created with, as well as the 
  /// Render Device used to create it.
  RenderDeviceObject(GraphicsAPIType type = vikr_API_UNKNOWN, RenderDevice *device = nullptr)
    : m_Device(device)
    , m_api(type) { }
  
  /// Virtual stuff...
  virtual ~RenderDeviceObject() { }

  /// Get the RenderDevice for this RenderDeviceObject.
  RenderDevice *GetRenderDevice() { return m_Device; }

  /// Set the RenderDevice for this RenderDevice object.
  /// Note that setting a new device will require it be the 
  /// same render api as it's creation, otherwise the call will
  /// be ignored.
  vvoid SetRenderDevice(RenderDevice *device) {
    if (device) {
      if (device->GetAPIType() == m_api) { 
        m_Device = device; 
      }
    } 
  }

  /// Get the render API Type of this object.
  GraphicsAPIType GetAPIType() { return m_api; }

private:
  /// The RenderDevice used to create this Object.
  RenderDevice *m_Device;
  
  /// The RenderAPI used to create this object, as well as 
  /// the API used to even do anything with this object.
  GraphicsAPIType m_api;
};
} // vikr
#endif // __VIKR_RENDER_DEVICE_HPP