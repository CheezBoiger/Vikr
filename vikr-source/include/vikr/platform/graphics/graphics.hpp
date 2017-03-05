//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_GRAPHICS_HPP
#define __VIKR_GRAPHICS_HPP


#include <vikr/platform/platform.hpp>

#include <vikr/platform/graphics/vk.hpp>
#include <vikr/platform/graphics/opengl.hpp>

#if defined(VIKR_VULKAN)
 #define GLFW_INCLUDE_VULKAN
#endif // _VIKR_VULKAN

#include <glfw3.h>


namespace vikr {


/**
  Graphics Pipeline to implement.
*/
enum GraphicsPipeline {
  vikr_PIPELINE_UNKNOWN,
  vikr_PIPELINE_OPENGL,
  vikr_PIPELINE_VULKAN,
  vikr_PIPELINE_D3D,
  vikr_PIPELINE_METAL
};


struct GraphicsHardwareInfo {
  const char *vendor;
  const char *renderer;
  const char *extensions;
  const char *version;
  const char *shader_language;
};


struct GraphicsPerformanceInfo {
  int total_mem_kb;
  int curr_available_mem_kb;
};

VIKR_FORCEINLINE int VikrInit() { return glfwInit(); }
VIKR_FORCEINLINE void VikrWindowHint(int hint, int value) { glfwWindowHint(hint, value); }
VIKR_FORCEINLINE void VikrMakeContextCurrent(GLFWwindow *window) { glfwMakeContextCurrent(window); }
VIKR_FORCEINLINE void VikrDestroyWindow(GLFWwindow *window) { glfwDestroyWindow(window); }
VIKR_FORCEINLINE void VikrTerminateGLFW() { glfwTerminate(); }
VIKR_FORCEINLINE GLFWwindow *VikrCreateGLFWwindow(int width, int height, 
                                  const char *title, GLFWmonitor *monitor, GLFWwindow *share) { 
  return glfwCreateWindow(width, height, title, monitor, share);
}

} // vikr
#endif // __VIKR_GRAPHICS_HPP