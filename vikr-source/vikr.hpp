//
// Copyright (c) Mario Garcia. Under the MIT License.
//
// This is a temp header file for testing, it will be replaced with headers
// only after the final product is finished.
//
#ifndef __VIKR_HPP
#define __VIKR_HPP

#include <platform/vikr_api.hpp>
#include <platform/vikr_types.hpp>
#include <platform/vikr_time.hpp>
#include <renderer/renderer.hpp>

namespace vikr {

/**
*/
VIKR_FORCEINLINE vint32 LoadGlad() {
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    return -1;
  }
  return 1;
}
/**
  Initialize the Vikr engine based on what type of Graphics API to load.

  NOTE(Garcia): This WON'T be here for the release. The Renderer is supposed to be
                created by the programmer, and not this function.
  @param GraphicsPipeline 
*/
Renderer* InitVikrEngine(GraphicsPipeline pipeline);

/**
  
*/
VIKR_FORCEINLINE vvoid PollEvents() { glfwPollEvents(); }

/**
  Swap buffers with the window to prevent gittering and tears on the rendering.
*/
VIKR_FORCEINLINE vvoid DoubleBufferSwap(GLFWwindow *window) { glfwSwapBuffers(window); }
VIKR_FORCEINLINE vint32 WindowShouldClose(GLFWwindow  *window) { return glfwWindowShouldClose(window); }
/**
  Cleanup renderer and it's resources after use.
*/
vint32 Cleanup();
} // vikr
#endif // __VIKR_HPP