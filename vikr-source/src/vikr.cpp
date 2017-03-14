#include <vikr/vikr.hpp>
#include <vikr/input/window.hpp>
#include <vikr/util/vikr_log.hpp>

namespace vikr {


vint32 InitVikr(GraphicsPipeline graphicsAPI) {
  vint32 success = 1;
  if (!GladLoaded()) {
    glfwInit();
  }
  switch (graphicsAPI) {
    case vikr_API_OPENGL:
    {
      VikrWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
      VikrWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      VikrWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      VikrWindowHint(GLFW_RESIZABLE, GL_FALSE);
    }
    break;
    case vikr_API_VULKAN:
    {
      glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
      glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    }
    break;
    case vikr_API_D3D:
    {
      VikrLog::DisplayMessage(VIKR_ERROR, "Direct X is not implemented yet!");
    }
    break;
    case vikr_API_METAL:
    {
      VikrLog::DisplayMessage(VIKR_ERROR, "Metal is not implemented yet!");
    }
    break;
    case vikr_API_UNKNOWN:
    default: success = 0; break;
  }
  return success;
}


vint32 Cleanup() {
  VikrLog::DisplayMessage(VIKR_NOTIFY, "cleaning up resources and renderer...");
  vint32 result = 0; 
  if (Renderer::GetRenderer() != nullptr) {
    Renderer::GetRenderer()->CleanupResources(); 
    VikrDestroyWindow(Window::GetMainWindow()->GetWindow());
    VikrTerminateGLFW();
  }
  return result;
}
} // vikr