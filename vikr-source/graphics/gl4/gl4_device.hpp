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
  
  std::unique_ptr<Framebuffer> CreateFramebuffer() override;

  Shader *GetShader(std::string name) override;

  vvoid StoreShader(std::string name,
    std::string vs, std::string fs, std::string include = ".") override;

  Material *CreateMaterial(std::string name) override;

  std::unique_ptr<VertexBuffer> CreateVertexBuffer(std::vector<Vertex> &vertices, 
    std::vector<vuint32> &indices, VertexUsageType type) override;

  ResourceManager *GetResourceManager() override { return &manager; }

  /**
    Get the context of this device.
  */
  RenderContext *GetContext() override { return &context; }

  /**
    Create a Renderbuffer object for the OpenGL device.
  */
  std::unique_ptr<Renderbuffer> CreateRenderbuffer(vuint32 width, vuint32 height) override;

  /**
    Create a RenderTexture object for the OpenGL device.
  */
  std::unique_ptr<RenderTexture> CreateRenderTexture(vuint32 width, vuint32 height) override;


  std::unique_ptr<Cubemap> CreateCubemap() override;

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