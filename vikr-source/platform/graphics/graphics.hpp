//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_GRAPHICS_HPP
#define __VIKR_GRAPHICS_HPP


#include <platform/platform.hpp>

#include <platform/graphics/vk.hpp>
#include <platform/graphics/opengl.hpp>

#if defined(VIKR_VULKAN)
 #define GLFW_INCLUDE_VULKAN
#endif // _VIKR_VULKAN

#include <GLFW/glfw3.h>


namespace vikr {


/**
  Graphics Pipeline to implement.
*/
enum GraphicsPipeline {
  vikr_PIPELINE_UNKNOWN,
  vikr_PIPELINE_OPENGL,
  vikr_PIPELINE_VULKAN
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