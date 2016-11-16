//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_VULKAN_RENDERER_HPP
#define __VIKR_VULKAN_RENDERER_HPP


#include <renderer/renderer.hpp>

namespace vikr {



class VKRenderer : public Renderer {
public:
  VKRenderer() : Renderer(vikr_VULKAN) { }
  ~VKRenderer() { }

  vint32 Init() override;

  vvoid Render() override;
private: 

  VIKR_DISALLOW_COPY_AND_ASSIGN(VKRenderer);
};
} // vikr
#endif // __VIKR_VULKAN_RENDERER_HPP