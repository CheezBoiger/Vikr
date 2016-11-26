//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_RENDERER_HPP
#define __VIKR_RENDERER_HPP

#include <renderer/irenderer.hpp>
#include <renderer/render_queue.hpp>
#include <shader/texture_config.hpp>
#include <shader/shader.hpp>
#include <glm/glm.hpp>
#include <string>
#include <memory>
#include <unordered_map>

namespace vikr {


class Camera;
class Light;
class RenderTarget;
class PointLight;
class Material;
class Texture;


/**
  Renderer resources to use with the Renderer. It also serves as an Abstract Renderer.
  Plugins are initialized via Factory method.
*/
class Renderer : public IRenderer {
public:
  Renderer(GraphicsPipeline pipeline);

  virtual ~Renderer() { }
  /**
    TODO(Garcia): This will need to move to resources.
  */
  static Renderer *GetRenderer() { return renderer; }
  static vvoid SetRenderer(Renderer *r) { renderer = r; }

  Camera *GetCamera() { return camera; }
  vvoid SwapCamera(Camera *camera) { std::swap(this->camera, camera); }
  vvoid SetCamera(Camera *camera) { this->camera = camera; }
  /**
    Initialize the current Renderer plugin.
  */  
  virtual vint32 Init() override = 0;
  /**
    Define the current Renderer plugin, rendering scheme.
  */
  virtual vvoid Render() override = 0;

  virtual vvoid PushBack(RenderCommand *command) override;
  virtual vvoid PushBack(Light *light) override;
  virtual vvoid Sort() override { m_command_list.Sort(); }

  virtual vint32 StoreShader(std::string shader_name, 
                             std::string vs, 
                             std::string fs, 
                             std::string include_searchpath = ".") = 0;

  virtual Shader *GetShader(std::string shader_name) = 0;
  virtual Texture *CreateTexture(TextureTarget target, std::string image_path, vbool alpha) = 0;

  //virtual Material *CreateMaterial(std::string name) = 0;

  GraphicsPipeline GetRenderType()  { return renderer_type; }
  vvoid SetClearColor(glm::vec3 cc) { clear_color = cc; }
  glm::vec3 GetClearColor() { return clear_color; }
  vbool IsRendering() { return rendering; }

  vvoid SetCurrentRenderTarget(RenderTarget *target) override { m_current_render_target = target; }
  RenderTarget *GetCurrentRenderTarget() override { return m_current_render_target; }

  virtual vint32 CleanupResources();

protected:
  /**
    Checks if the renderer is in the middle of rendering.
  */
  vbool rendering = false;
  /**
    List of commands in the to be rendered.
  */
  RenderQueue<RenderCommand> m_command_list;
  RenderQueue<PointLight> m_pointlights;
  RenderQueue<RenderTarget> m_render_targets;
  
  RenderTarget *m_current_render_target;
  /**
    Currently bound renderer type.
  */
  GraphicsPipeline renderer_type;
  glm::vec3 clear_color;
  Camera *camera;  
private:
  /**
    The current renderer plugin.
  */
  static Renderer *renderer;
};
}
#endif // __VIKR_RENDERER_HPP