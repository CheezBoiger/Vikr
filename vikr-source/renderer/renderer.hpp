//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_RENDERER_HPP
#define __VIKR_RENDERER_HPP

#include <renderer/irenderer.hpp>
#include <shader/shader.hpp>
#include <string>
#include <unordered_map>

namespace vikr {


class Camera;

/**
  Renderer resources to use with the Renderer. It also serves as an Interface Renderer.
*/
class Renderer : public IRenderer {
public:
  virtual ~Renderer() { }

  static vvoid LoadShader(Renderer *renderer, std::string shader_name, std::string fs, std::string vs);
  static Shader *GetShader(std::string shader_name);
  static Renderer *GetRenderer() { return renderer; }
  static vvoid SetRenderer(Renderer *r) { renderer = r; }

  virtual Camera *GetCamera() = 0;
  virtual vvoid SwapCamera(Camera *camera) = 0;
  virtual vvoid SetCamera(Camera *camera) = 0;

  virtual vint32 Init() override = 0;
  virtual vvoid PushBack(RenderCommand *command) override = 0;
  virtual vvoid Sort() override = 0;
  virtual vvoid Render() override = 0;

private:
  static Renderer *renderer;
  static std::unordered_map<std::string, IShader*> shader_storage;
};
}
#endif // __VIKR_RENDERER_HPP