//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_RENDERER_HPP
#define __VIKR_RENDERER_HPP

#include <vikr/graphics/command_buffer.hpp>
#include <vikr/graphics/framebuffer.hpp>
#include <vikr/graphics/render_pass.hpp>
#include <vikr/renderer/irenderer.hpp>
#include <vikr/renderer/render_queue.hpp>
#include <vikr/shader/texture_config.hpp>
#include <vikr/shader/shader.hpp>
#include <vikr/shader/cubemap.hpp>
#include <vikr/shader/font_printer.hpp>
#include <vikr/mesh/mesh.hpp>
#include <vikr/renderer/gbuffer.hpp>
#include <vikr/renderer/screen_quad.hpp>
#include <vikr/renderer/skybox.hpp>
#include <glm/glm.hpp>
#include <string>
#include <memory>
#include <unordered_map>

namespace vikr {


// Forward declarations.
class Camera;
class Light;
class RenderTarget;
class PointLight;
class DirectionalLight;
class SpotLight;
class Material;
class Texture;
class ShaderProgram;
class Framebuffer;


/**
  Renderer resources to use with the Renderer. It also serves as an Abstract Renderer.
  Plugins are initialized via Factory method, but overall, this renderer is cross compatible.
*/
class Renderer : public IRenderer {
public:
  Renderer();

  virtual ~Renderer() { }

  /**
    Get the Renderer globally.
  */
  static Renderer *GetRenderer() { return renderer; }

  /**
    NOTE(): If you dynamically allocate a renderer, you need
    to clean it up yourself by calling "delete" or "free".
  */
  static vvoid SetRenderer(Renderer *r) { renderer = r; }

  /**
    Get the Camera that is currently being renderer by the Renderer.
  */
  ICamera *GetCamera() override { return camera; }

  /**
    Set a camera.
  */
  vvoid SetCamera(ICamera *camera) override { this->camera = camera; }

  /**
    Initialize the current Renderer plugin.
  */  
  virtual vint32 Init(RenderDevice *device) override;

  /**
    Define the current Renderer plugin, rendering scheme.
  */
  virtual vvoid Render() override;

  /**
    Pushback a RenderCommand.
  */
  virtual vvoid PushBack(RenderCommand *command) override;

  /**
    Pushback a SceneNode.
  */
  virtual vvoid PushBack(SceneNode *obj) override;

  virtual vvoid PushBackDeferred(RenderCommand *command) override;

  virtual vvoid Sort() override { m_renderQueue.Sort(); }

  vvoid SetClearColor(glm::vec4 cc) { clear_color = cc; }
  glm::vec3 GetClearColor() { return clear_color; }
  vbool IsRendering() { return rendering; }

  vvoid Present() override;


  //RenderPass *GetCurrentRenderPass() { return m_renderpass.get(); }
  // testing one renderpass.
  //vvoid SetRenderPass(RenderPass *pass) { m_renderpass.reset(pass); }

  RenderDevice *GetDevice() { return m_renderDevice; }

  virtual vint32 CleanupResources();

protected:
  /**
    Checks if the renderer is in the middle of rendering.
  */
  vbool rendering = false;

  /**
  */
  RenderQueue m_renderQueue;

  /**
    Screen filled mesh quad.
  */
  Mesh *m_quad                                            = nullptr;
  
  /**
    Gbuffer pass.
  */
  GBuffer m_gbuffer;

  /**
    Le Screen quad.
  */
  ScreenQuad m_screenquad;

  /**
    shadow pass.
  */
  std::unique_ptr<RenderPass> m_shadowPass                = nullptr;

  /**
    light shader.
  */
  ShaderProgram *lightShader                                     = nullptr;

  CommandbufferList m_commandBufferList;
  CommandbufferList m_deferredBufferList;

  FontPrinter printer;

  Skybox skybox;

  /**
    Render device used by this Renderer.
  */
  RenderDevice *m_renderDevice                            = nullptr;

  glm::vec4 clear_color;
  ICamera *camera;  

private:
  /**
    The current renderer plugin.
  */
  static Renderer *renderer;
};
}
#endif // __VIKR_RENDERER_HPP