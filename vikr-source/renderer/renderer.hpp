//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_RENDERER_HPP
#define __VIKR_RENDERER_HPP

#include <renderer/irenderer.hpp>
#include <renderer/render_queue.hpp>
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


/**
  Renderer resources to use with the Renderer. It also serves as an Abstract Renderer.
*/
class Renderer : public IRenderer {
public:
  Renderer(GraphicsPipeline type) 
    : renderer_type(type)
    , camera(nullptr) { }

  virtual ~Renderer() { }

  static vvoid LoadShader(Renderer *renderer, std::string shader_name, std::string fs, std::string vs);
  static Shader *GetShader(std::string shader_name);
  static Renderer *GetRenderer() { return renderer; }
  static vvoid SetRenderer(Renderer *r) { renderer = r; }

  Camera *GetCamera() { return camera; }
  vvoid SwapCamera(Camera *camera) { std::swap(this->camera, camera); }
  vvoid SetCamera(Camera *camera) { this->camera = camera; }

  virtual vint32 Init() override = 0;
  virtual vvoid Render() override = 0;

  virtual vvoid PushBack(RenderCommand *command) override;
  virtual vvoid PushBack(Light *light) override;// need to do this too.
  virtual vvoid Sort() override { m_command_list.Sort();}

  GraphicsPipeline GetRenderType()  { return renderer_type; }
  vvoid SetClearColor(glm::vec3 cc) { clear_color = cc; }
  glm::vec3 GetClearColor() { return clear_color; }
  vbool IsRendering() { return rendering; }

  vvoid SetCurrentRenderTarget(RenderTarget *target) override { m_current_render_target = target; }
  RenderTarget *GetCurrentRenderTarget() override { return m_current_render_target; }

  vint32 CleanupResources();

protected:
  vbool rendering = false;
  RenderQueue m_command_list;
  std::vector<PointLight*> m_pointlights;
  std::vector<RenderTarget *> m_render_targets;
  
  RenderTarget *m_current_render_target;

  GraphicsPipeline renderer_type;
  glm::vec3 clear_color;
  Camera *camera;  
private:
  static Renderer *renderer;
  static std::unordered_map<std::string, 
                            std::pair<std::string, std::unique_ptr<Shader>> > shader_storage;
};
}
#endif // __VIKR_RENDERER_HPP