//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_VULKAN_RENDERER_HPP
#define __VIKR_VULKAN_RENDERER_HPP


#include <renderer/irenderer.hpp>

namespace vikr {



class VKRenderer : public IRenderer {
public:
  VKRenderer();
  ~VKRenderer();

  vint32 Init();
  vvoid PushBack(RenderCommand command);
  vvoid Sort();
  vvoid Render();
private: 
};
} // vikr
#endif // __VIKR_VULKAN_RENDERER_HPP