//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/graphics/vk/vk_surface.hpp>
#include <vikr/graphics/vk/vk_instance.hpp>

#include <vikr/input/window.hpp>
#include <vikr/util/vikr_log.hpp>

namespace vikr {


VkMemoryManager<VkSurfaceKHR> VKSurface::surface = { VKInstance::instance, vkDestroySurfaceKHR };


vvoid VKSurface::CreateSurface() {
  if(glfwCreateWindowSurface(VKInstance::instance, 
    Window::GetMainWindow()->GetWindow(), nullptr, surface.Replace()) != VK_SUCCESS) 
  {
    VikrLog::DisplayMessage(VIKR_ERROR, "Surface creation error!");
  }
}
} // vikr