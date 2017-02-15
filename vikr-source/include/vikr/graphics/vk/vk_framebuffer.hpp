//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VK_FRAMEBUFFER_HPP
#define __VIKR_VK_FRAMEBUFFER_HPP


#include <vikr/platform/vikr_api.hpp>
#include <vikr/platform/vikr_types.hpp>
#include <vikr/graphics/framebuffer.hpp>
#include <vikr/resources/vulkan/vk_memorymanager.hpp>


namespace vikr {


/**
  Vulkan Framebuffer implemenation.
*/
class VKFramebuffer : public Framebuffer {
public:
  VKFramebuffer();

  vvoid Generate() override;

  vvoid SetClearColor(glm::vec3 color) override;
  glm::vec3 GetClearColor() override;


private:

  VkMemoryManager<VkFramebuffer> m_fbo;
};
} // vikr
#endif // __VIKR_VK_FRAMEBUFFER_HPP