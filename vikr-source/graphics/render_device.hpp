//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_RENDER_DEVICE_HPP
#define __VIKR_RENDER_DEVICE_HPP


#include <platform/vikr_api.hpp>
#include <platform/vikr_types.hpp>
#include <shader/texture.hpp>
#include <mesh/imesh.hpp>

#include <string>
#include <memory>


namespace vikr {


class Texture;
class Framebuffer;
class Renderbuffer;
class RenderTarget;
class RenderPass;
class Shader;
class Material;
class ResourceManager;
class RenderContext;

/**
  Render Device is an interface, with a driver type format.
  Creates our buffers to use, as well as our textures, shaders, and 
  framebuffers.
*/
class RenderDevice {
  VIKR_DISALLOW_COPY_AND_ASSIGN(RenderDevice);
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(RenderDevice);
  virtual ~RenderDevice() { }

  virtual std::string GetShaderLanguage() = 0;

  virtual Texture *GenerateTexture(std::string path, 
    TextureTarget target, vbool alpha) = 0;

  /**
    Generate a framebuffer.
  */
  virtual Framebuffer *GenerateFramebuffer() = 0;

  virtual Shader *GetShader(std::string name) = 0;

  /**
    Store a shader into resources.
  */
  virtual vvoid StoreShader(
    std::string name, 
    std::string vs, 
    std::string fs, 
    std::string include) = 0;
  
  /**
    Create material, which is handled by resources.
  */
  virtual Material *CreateMaterial() = 0;

  /**
    Create vertex buffer id.
  */
  virtual vuint32 CreateVertexBufferId(std::vector<Vertex> &vertices) = 0;

  virtual vuint32 CreateElementBufferId(std::vector<vuint32> &indices) = 0;

  virtual ResourceManager *GetResourceManager() = 0;
  virtual RenderContext *GetContext() = 0;
};
} // vikr
#endif // __VIKR_RENDER_DEVICE_HPP