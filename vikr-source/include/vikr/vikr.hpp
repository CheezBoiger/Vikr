//
// Copyright (c) Mario Garcia. Under the MIT License.
//
// This is a temp header file for testing, it will be replaced with headers
// only after the final product is finished.
//
#ifndef __VIKR_HPP
#define __VIKR_HPP

#include <vikr/platform/vikr_api.hpp>
#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_time.hpp>
#include <vikr/renderer/renderer.hpp>

#include <vikr/graphics/graphics.hpp>


namespace vikr {
namespace detail {


static vbool glad_loaded = false;
static vbool glfw_loaded = false;
} // detail;


/**
  Initializes the Vikr library. This should be relatively quick.
*/
vint32 InitVikr(GraphicsPipeline graphicsAPI);


/**
  Has GLAD loaded the OpenGL library?
*/
VIKR_FORCEINLINE vbool GladLoaded() { return detail::glad_loaded; }
VIKR_FORCEINLINE vbool GLFWLoaded() { return detail::glad_loaded; }

/**
*/
VIKR_FORCEINLINE vint32 LoadGlad() {
  if (GladLoaded()) {
    return 1;
  }

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    return -1;
  }
  detail::glad_loaded = true;
  return 1;
}

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


//GraphicsInfo GetGraphicsInfo() { return GraphicsInfo(); }
} // vikr
#endif // __VIKR_HPP