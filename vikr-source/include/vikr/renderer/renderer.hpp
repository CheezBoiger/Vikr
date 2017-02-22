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
  Renderer resources to use Globally. It also serves as an Abstract Renderer.
  Plugins are initialized via Factory method, but overall, this renderer is to be used 
  for global functioning.
*/
class Renderer {
public:
  /**
    Get the Renderer globally.
  */
  static IRenderer *GetRenderer() { return renderer; }

  /**
    NOTE(): If you dynamically allocate a renderer, you need
    to clean it up yourself by calling "delete" or "free".
  */
  static vvoid SetRenderer(IRenderer *r) { renderer = r; }

private:
  /**
    The current renderer plugin.
  */
  static IRenderer *renderer;
};
}
#endif // __VIKR_RENDERER_HPP