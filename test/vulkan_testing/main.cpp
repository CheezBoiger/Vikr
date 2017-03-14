/*
  Vulkan Sample Test.
*/
#include <vikr/vikr.hpp>
#include <vikr/graphics/vk/vk_device.hpp>
#include <vikr/renderer/deferred_renderer.hpp>
#include <vikr/input/window.hpp>
#include <vikr/scene/first_person_camera.hpp>
#include <vikr/resources/resource_manager.hpp>


using namespace vikr;

vuint32 screen_width = 1200;
vuint32 screen_height = 800;
FPSCamera camera(89.0f, glm::vec3(0.0f, 0.0f, 1.0f));


int main(int argc, char *argv[]) {
  InitVikr(vikr_API_VULKAN);
  Window main_window = Window::CreateVikrWindow(screen_width, screen_height, "Vikr Vulkan");
  Window::SetMainWindow(&main_window);

  // Initialize the Rendering device.
  VKRenderDevice device;
  // Initialize the Renderer.
  DeferredRenderer renderer;
  // Set this to be the global renderer.
  Renderer::SetRenderer(&renderer);
  ResourceManager mgr;

  renderer.Init(&device, &mgr);

  while (!Window::GetMainWindow()->IsClosed()) {
    CalculateDeltaTime();  
    PollEvents();
  }

  vikr::Cleanup();
  return 0;
}