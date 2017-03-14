//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GRAPHICS_CONFIG_HPP
#define __VIKR_GRAPHICS_CONFIG_HPP



namespace vikr {


/**
Graphics Pipeline to implement.
*/
enum GraphicsAPIType {
  vikr_API_UNKNOWN,
  vikr_API_OPENGL,
  vikr_API_VULKAN,
  vikr_API_D3D,
  vikr_API_METAL
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
} // vikr
#endif // __VIKR_GRAPHICS_CONFIG_HPP