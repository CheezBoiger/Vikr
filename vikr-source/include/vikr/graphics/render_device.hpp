//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_RENDER_DEVICE_HPP
#define __VIKR_RENDER_DEVICE_HPP


#include <vikr/platform/vikr_api.hpp>
#include <vikr/platform/vikr_types.hpp>
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


/**
  Render Device is an interface, with a driver type format.
  Creates our buffers to use, as well as our textures, shaders, and 
  framebuffers.
*/
class RenderDevice {
  VIKR_DISALLOW_COPY_AND_ASSIGN(RenderDevice);
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(RenderDevice);
  RenderDevice() { }
  virtual ~RenderDevice() { }

  /**
    Get the Shader language used by this Render Device.
  */
  virtual std::string GetShaderLanguage() = 0;

  /**
    Generate a Texture from this RenderDevice.

    @param path The file path to the texture file.
    @param target The texture target, such as if it's 1D, 2D, 3D, etc.
    @param alpha If the texture contains an alpha component, this is transparency.
  */
  virtual Texture *GenerateTexture(std::string path, 
    TextureTarget target, vbool alpha) = 0;

  /**
    Generate a framebuffer.
  */
  virtual Framebuffer *CreateFramebuffer() = 0;
  
  /**
    Create material, which is handled by resources.
  */
  virtual Material *CreateMaterial(std::string name) = 0;

  /**
    Create vertex buffer id.
  */
  virtual Vertexbuffer *CreateVertexbuffer(VertexContainer &vertices) = 0;

  /**
    Get the Resource manager from this Rendering Device.
  */
  virtual ResourceManager *GetResourceManager() = 0;

  /**
    Get the contet of this Rendering Device.
  */
  virtual RenderContext *GetContext() = 0;

  /**
    Create a cubemap object.
  */
  virtual Cubemap *CreateCubemap() = 0;

  /**
    Generate RenderPass.
  */
  virtual RenderPass *CreateRenderPass() = 0;

  /**
    Destroys the Renderpass in the device.
  */
  virtual vbool DestroyRenderPass(guid_t id) = 0;

  /**
    Destroys the Vertexbuffer stored inside the device.
  */
  virtual vbool DestroyVertexbuffer(guid_t id) = 0;
  
  /**
    Destorys the cubemap stored by the device.
  */
  virtual vbool DestroyCubemap(guid_t id) = 0;

  /**
    Destroys the Framebuffer inside the device.
  */
  virtual vbool DestroyFramebuffer(guid_t id) = 0;

  /**
    Destroy the commandbuffer list.
  */
  virtual vbool DestroyCommandbufferList(guid_t id) = 0;

  /**
    Create a command buffer to handle recording commands into an organized batch,
      which will then be stored inside the specified CommandbufferList.
  */
  virtual Commandbuffer &CreateCommandbuffer(CommandbufferList *list) = 0;

  /**
    Create Commandbuffer list to use for your Commandbuffers.
  */
  virtual CommandbufferList *CreateCommandbufferList() = 0;
};
} // vikr
#endif // __VIKR_RENDER_DEVICE_HPP