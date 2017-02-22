//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GL4_DEVICE_HPP
#define __VIKR_GL4_DEVICE_HPP


#include <vikr/graphics/render_device.hpp>
#include <vikr/resources/opengl/gl_resource_manager.hpp>
#include <vikr/graphics/gl4/gl4_context.hpp>

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
  
  std::unique_ptr<Framebuffer> CreateFramebuffer() override;

  Material *CreateMaterial(std::string name) override;

  std::unique_ptr<Vertexbuffer> CreateVertexbuffer(VertexContainer &vertices) override;

  ResourceManager *GetResourceManager() override { return &manager; }

  /**
    Get the context of this device.
  */
  RenderContext *GetContext() override { return &context; }

  std::unique_ptr<Cubemap> CreateCubemap() override;

  std::unique_ptr<RenderPass> CreateRenderPass() override;

  std::unique_ptr<Commandbuffer> CreateCommandbuffer() override;


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