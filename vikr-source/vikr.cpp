#include <vikr.hpp>
#include <renderer/opengl/glrenderer.hpp>
#include <renderer/vulkan/vkrenderer.hpp>
#include <util/vikr_log.hpp>

namespace vikr {


/**
Returns the same renderer back, initialized!
*/
GLRenderer *InitGLRenderer(GLRenderer *renderer) {
  renderer->Init();
  return renderer;
}


Renderer *InitVikrEngine(GraphicsPipeline pipeline) {
  LoadGlad();
  Renderer *renderer = nullptr;
  switch (pipeline) {
    case vikr_OPENGL: {
      GLRenderer *gl = new GLRenderer();
      renderer = InitGLRenderer(gl);
    }
    break;
    case vikr_VULKAN: {
      VikrLog::DisplayMessage(VIKR_ERROR, "Vulkan renderer not yet written!");
    }
    break;
    default:
      VikrLog::DisplayMessage(VIKR_ERROR, "Enum does not match any compatible renderers!");
      break;
  }
  if (!Renderer::GetRenderer()) {
    Renderer::SetRenderer(renderer);
  } else {
    VikrLog::DisplayMessage(VIKR_WARNING, "A Renderer is already set! Still building a new renderer...");
  }
  return renderer;
}


vint32 Cleanup() {
  VikrLog::DisplayMessage(VIKR_NOTIFY, "cleaning up resources and renderer...");
  vint32 result = 0;
  if (Renderer::GetRenderer() != nullptr) {
    Renderer *renderer = Renderer::GetRenderer();
    delete renderer;
    renderer = nullptr;
    result = 1;
  }
  return result;
}
} // vikr