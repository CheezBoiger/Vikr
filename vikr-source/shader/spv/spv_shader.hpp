//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_SPV_SHADER_HPP
#define __VIKR_SPV_SHADER_HPP


#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <shader/shader.hpp>

#include <resources/vulkan/vk_memorymanager.hpp>


namespace vikr {


class SpvShader : public Shader {
public:
 SpvShader();
  

private:

  VkMemoryManager<VkShaderModule> vert_module;
  VkMemoryManager<VkShaderModule> frag_module;
  VkMemoryManager<VkShaderModule> comp_module;
  VkMemoryManager<VkShaderModule> geom_module;
};
} // vikr
#endif // __VIKR_SPV_SHADER_HPP