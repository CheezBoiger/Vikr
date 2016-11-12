#include <vikr.hpp>
#include <renderer/glrenderer.hpp>
#include <renderer/vkrenderer.hpp>
#include <util/vikr_log.hpp>

namespace vikr {


/**
Returns the same renderer back, initialized!
*/
GLRenderer *InitGLRenderer(GLRenderer *renderer) {
  return renderer;
}


IRenderer *InitVikrEngine(GraphicsPipeline pipeline) {
  LoadGlad();
  IRenderer *renderer = nullptr;
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
} // vikr