#include <vikr.hpp>
#include <renderer/glrenderer.hpp>
#include <renderer/vkrenderer.hpp>
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
      VKRenderer *vk = new VKRenderer();
      delete vk; vk = nullptr; // delete for now.
      VikrLog::DisplayMessage(VIKR_ERROR, "Vulkan renderer not yet written!");
    }
    break;
    default:
      VikrLog::DisplayMessage(VIKR_ERROR, "Enum does not match any compatible renderers!");
      break;
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