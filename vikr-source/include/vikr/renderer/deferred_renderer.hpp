//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_DEFERRED_RENDERER_HPP
#define __VIKR_DEFERRED_RENDERER_HPP


#include <vikr/renderer/renderer.hpp>
#include <vikr/graphics/command_buffer.hpp>
#include <vikr/graphics/framebuffer.hpp>
#include <vikr/graphics/render_pass.hpp>
#include <vikr/renderer/render_queue.hpp>
#include <vikr/shader/texture_config.hpp>
#include <vikr/shader/shader.hpp>
#include <vikr/shader/cubemap.hpp>
#include <vikr/shader/font_printer.hpp>
#include <vikr/renderer/shadowmap.hpp>
#include <vikr/mesh/mesh.hpp>
#include <vikr/renderer/gbuffer.hpp>
#include <vikr/renderer/screen_quad.hpp>
#include <vikr/renderer/skybox.hpp>
#include <glm/glm.hpp>
#include <string>
#include <memory>
#include <unordered_map>


namespace vikr {


class DeferredRenderer : public IRenderer {
public:
  DeferredRenderer();
  
  vvoid SetCamera(ICamera *cam) override { camera = cam; }
  ICamera *GetCamera() override { return camera; }
  /**
    Initialize the current Renderer plugin.
  */  
  vint32 Init(RenderDevice *device, ResourceManager *mgr) override;

  /**
    Define the current Renderer plugin, rendering scheme.
  */
  vvoid Render() override;

  /**
    Pushback a RenderCommand.
  */
  vvoid PushBack(RenderCommand *command) override;

  /**
    Pushback a SceneNode.
  */
  vvoid PushBack(SceneNode *obj) override;

  vvoid PushBackDeferred(RenderCommand *command) override;

  vvoid Sort() override { m_renderQueue.Sort(); }

  vvoid SetClearColor(glm::vec4 cc) { clear_color = cc; }
  glm::vec4 GetClearColor() { return clear_color; }
  vbool IsRendering() { return rendering; }

  vvoid Present() override;


  //RenderPass *GetCurrentRenderPass() { return m_renderpass.get(); }
  // testing one renderpass.
  //vvoid SetRenderPass(RenderPass *pass) { m_renderpass.reset(pass); }

  RenderDevice *GetDevice() { return m_renderDevice; }

  vint32 CleanupResources();


private:
  /**
    Camera currently used for rendering.
  */
  ICamera *camera;

  /**
    Checks if the renderer is in the middle of rendering.
  */
  vbool rendering = false;

  /**
  */
  RenderQueue m_renderQueue;
  
  /**
    Gbuffer pass.
  */
  GBuffer m_gbuffer;

  /**
    Le Screen quad.
  */
  ScreenQuad m_screenquad;

  DirectionalShadowMap directional_shadowmap;

  /**
    shadow pass.
  */
  std::unique_ptr<RenderPass> m_shadowPass                = nullptr;

  /**
    light shader.
  */
  ShaderProgram *lightShader                              = nullptr;

  CommandbufferList *m_commandBufferList;
  CommandbufferList *m_deferredBufferList;

  std::vector<DirectionalLight *> m_directionalLights;

  FontPrinter printer;

  Skybox skybox;

  /**
    Render device used by this Renderer.
  */
  RenderDevice *m_renderDevice                            = nullptr;

  glm::vec4 clear_color;
};
} // vikr
#endif // __VIKR_DEFERRED_RENDERER_HPP