//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <graphics/vk/vk_surface.hpp>
#include <graphics/vk/vk_instance.hpp>

#include <input/window.hpp>
#include <util/vikr_log.hpp>

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