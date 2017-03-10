//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GL4_DEVICE_HPP
#define __VIKR_GL4_DEVICE_HPP


#include <vikr/graphics/render_device.hpp>
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
  
  Framebuffer *CreateFramebuffer() override;

  Vertexbuffer *CreateVertexbuffer(VertexUsageType type, 
    std::vector<Vertex> &vertices, std::vector<vuint32> &indices = std::vector<vuint32>()) override;

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

  vbool DestroyUniformbuffer(guid_t id) override;
  Uniformbuffer *GetUniformbuffer(guid_t id) override;
  Uniformbuffer *CreateUniformbuffer() override;

  GraphicsPipelineState *CreateGraphicsPipelineState(std::string name) override;
  GraphicsPipelineState *GetGraphicsPipelineState(guid_t id) override;
  vbool DestroyGraphicsPipelineState(guid_t id) override;

  ComputePipelineState *CreateComputePipelineState(std::string name) override;
  ComputePipelineState *GetComputePipelineState(guid_t id) override;
  vbool DestroyComputePipelineState(guid_t id) override;

  /**
  Create a shader, and store it into Resources, the id of the shader will
  be returned. Resources takes care of this.
  */
  Shader *CreateShader(std::string name, ShaderStage stage) override;
  Shader *GetShader(guid_t id) override;
  vbool DestroyShader(guid_t id) override;


  ShaderProgram *CreateShaderProgram() override;
  ShaderProgram *GetShaderProgram(guid_t id) override;
  vbool DestroyShaderProgram(guid_t id) override;

  Texture *CreateTexture(std::string name, TextureTarget target,
                                 std::string filepath, vbool alpha) override;
  Texture *GetTexture(guid_t id) override;
  vbool DestroyTexture(guid_t id) override;

  GraphicsHardwareInfo GetHardwareInformation() override;
  GraphicsPerformanceInfo GetPerformanceInformation() override;

private:
  /**
    Rendering context that this device uses.
  */
  GL4RenderContext context;
};
} // vikr
#endif // __VIKR_GL4_DEVICE_HPP