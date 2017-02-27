//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GL4_DEVICE_HPP
#define __VIKR_GL4_DEVICE_HPP


#include <vikr/graphics/render_device.hpp>
#include <vikr/resources/opengl/gl_resource_manager.hpp>
#include <vikr/graphics/gl4/gl4_context.hpp>

#include <map>
#include <memory>


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
  
  Framebuffer *CreateFramebuffer() override;

  Material *CreateMaterial(std::string name) override;

  Vertexbuffer *CreateVertexbuffer(VertexContainer &vertices) override;

  ResourceManager *GetResourceManager() override { return &manager; }

  /**
    Get the context of this device.
  */
  RenderContext *GetContext() override { return &context; }

  Cubemap *CreateCubemap() override;

  RenderPass *CreateRenderPass() override;

  Commandbuffer &CreateCommandbuffer(CommandbufferList *list) override;

  vbool DestroyRenderPass(guid_t id) override;
  vbool DestroyVertexbuffer(guid_t id) override;
  vbool DestroyCubemap(guid_t id) override;
  vbool DestroyFramebuffer(guid_t id) override;
  vbool DestroyCommandbufferList(guid_t id) override;

  CommandbufferList *CreateCommandbufferList() override;


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