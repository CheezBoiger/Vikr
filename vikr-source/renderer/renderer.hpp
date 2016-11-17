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
#include <unordered_map>

namespace vikr {


class Camera;
class Light;


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
  virtual vvoid PushBack(RenderCommand *command) override;
  virtual vvoid PushBack(Light *light) override { } // need to do this too.
  virtual vvoid Sort() override { m_command_list.Sort();}
  virtual vvoid Render() override = 0;

  GraphicsPipeline GetRenderType()  { return renderer_type; }
  vvoid SetClearColor(glm::vec3 cc) { clear_color = cc; }
  glm::vec3 GetClearColor() { return clear_color; }
  vbool IsRendering() { return rendering; }

protected:
  vbool rendering = false;
  RenderQueue m_command_list;
  std::vector<Light*> m_deferred_lights;
  GraphicsPipeline renderer_type;
  glm::vec3 clear_color;
  Camera *camera;  
private:
  static Renderer *renderer;
  static std::unordered_map<std::string, std::pair<std::string, Shader*> > shader_storage;
};
}
#endif // __VIKR_RENDERER_HPP