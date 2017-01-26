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
#include <string>
#include <memory>


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

  virtual std::string GetShaderLanguage() = 0;

  virtual Texture *GenerateTexture(std::string path, 
    TextureTarget target, vbool alpha) = 0;

  /**
    Generate a framebuffer.
  */
  virtual std::unique_ptr<Framebuffer> CreateFramebuffer() = 0;

  virtual Shader *GetShader(std::string name) = 0;

  /**
    Store a shader into resources.
  */
  virtual vvoid StoreShader(
    std::string name, 
    std::string vs, 
    std::string fs,
    std::string include = ".",
    std::string gs = "") = 0;
  
  /**
    Create material, which is handled by resources.
  */
  virtual Material *CreateMaterial(std::string name) = 0;

  /**
    Create vertex buffer id.
  */
  virtual std::unique_ptr<Vertexbuffer> CreateVertexbuffer(VertexContainer &vertices) = 0;

  virtual ResourceManager *GetResourceManager() = 0;
  virtual RenderContext *GetContext() = 0;

  virtual std::unique_ptr<RenderTexture> CreateRenderTexture(std::string t_name, vuint32 width, vuint32 height, 
    vbool alpha = false, vbool multisample = false, DataTypeFormat precision = data_UNSIGNED_BYTE) = 0;

  virtual std::unique_ptr<Renderbuffer> CreateRenderbuffer(vuint32 width, vuint32 height, vbool multisample = false) = 0;

  /**
    Create a cubemap object.
  */
  virtual std::unique_ptr<Cubemap> CreateCubemap() = 0;

  /**
    Generate RenderPass.
  */
  virtual std::unique_ptr<RenderPass> CreateRenderPass() = 0;

  /**
    Create a command buffer to handle recording commands into an organized batch.
  */
  virtual std::unique_ptr<Commandbuffer> CreateCommandbuffer() = 0;
};
} // vikr
#endif // __VIKR_RENDER_DEVICE_HPP