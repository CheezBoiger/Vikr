//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_VULKAN_RENDERER_HPP
#define __VIKR_VULKAN_RENDERER_HPP


#include <renderer/renderer.hpp>

namespace vikr {



class VKRenderer : public Renderer {
public:
  VKRenderer() { }
  ~VKRenderer() { }

  Camera *GetCamera() override { return current_camera; }
  vvoid SetCamera(Camera *camera) override { current_camera = camera; }
  vvoid SwapCamera(Camera *camera) override { std::swap(current_camera, camera); }  

  vint32 Init() override;
  vvoid PushBack(RenderCommand *command) override;
  vvoid Sort() override;
  vvoid Render() override;
private: 

  Camera *current_camera;

  RenderQueue m_command_list;

  VIKR_DISALLOW_COPY_AND_ASSIGN(VKRenderer);
};
} // vikr
#endif // __VIKR_VULKAN_RENDERER_HPP