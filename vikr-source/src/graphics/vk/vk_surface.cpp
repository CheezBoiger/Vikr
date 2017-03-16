//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/graphics/vk/vk_surface.hpp>
#include <vikr/graphics/vk/vk_instance.hpp>

#include <vikr/input/window.hpp>
#include <vikr/util/vikr_log.hpp>

namespace vikr {


vvoid VKSurface::CreateSurface() {
  // Surface is handled by glfw for simplicity.
  // PS: We are soon going to remove Library support in order to reduce dependency!
  if (glfwCreateWindowSurface(VKInstance::instance, 
    Window::GetMainWindow()->GetWindow(), nullptr, &surface) != VK_SUCCESS) 
  {
    VikrLog::DisplayMessage(VIKR_ERROR, "Surface creation error!");
  }
}


vvoid VKSurface::Cleanup()
{
}
} // vikr