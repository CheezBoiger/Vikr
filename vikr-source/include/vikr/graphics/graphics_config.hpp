//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GRAPHICS_CONFIG_HPP
#define __VIKR_GRAPHICS_CONFIG_HPP



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
} // vikr
#endif // __VIKR_GRAPHICS_CONFIG_HPP