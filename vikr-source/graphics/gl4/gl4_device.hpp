//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GL4_DEVICE_HPP
#define __VIKR_GL4_DEVICE_HPP


#include <graphics/render_device.hpp>
#include <resources/opengl/gl_resource_manager.hpp>
#include <graphics/gl4/gl4_context.hpp>

namespace vikr {


class GL4RenderDevice : public RenderDevice {
  static const std::string kGLSLShaderLanguage;
public:
  GL4RenderDevice();
  /**
  
  */
  std::string GetShaderLanguage() override;
  
  Texture *GenerateTexture(std::string path,
    TextureTarget target, vbool alpha) override;
  
  Framebuffer *GenerateFramebuffer() override;

  Shader *GetShader(std::string name) override;

  vvoid StoreShader(std::string name,
    std::string vs, std::string fs, std::string include) override;

  Material *CreateMaterial() override;

  vuint32 CreateVertexBufferId(std::vector<Vertex> &vertices) override;
  vuint32 CreateElementBufferId(std::vector<vuint32> &indices) override;

  ResourceManager *GetResourceManager() override;

  RenderContext *GetContext() override;

private:
  
  /**
    Resource manager.
  */
  GLResourceManager manager;

  /**
    Rendering context that this device uses.
  */
  GL4RenderContext context;
};
} // vikr
#endif // __VIKR_GL4_DEVICE_HPP