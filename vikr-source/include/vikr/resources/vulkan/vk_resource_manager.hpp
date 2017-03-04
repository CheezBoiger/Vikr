//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_VULKAN_RESOURCE_MANAGER_HPP
#define __VIKR_VULKAN_RESOURCE_MANAGER_HPP

#include <vikr/resources/resource_manager.hpp>



namespace vikr {


/**
  Vulkan Resource Manager object. Handles resources within the VkResources.
*/
class VKResourceManager : public ResourceManager {
public:
  VKResourceManager();

  Shader *CreateShader(std::string name, ShaderStage stage) override;
  Shader *GetShader(guid_t id) override;
  vbool DestroyShader(guid_t id) override;

  GraphicsPipelineState *CreateGraphicsPipelineState(std::string name) override;
  GraphicsPipelineState *GetGraphicsPipelineState(guid_t id) override;
  vbool DestroyGraphicsPipelineState(guid_t id) override;

  ComputePipelineState *CreateComputePipelineState(std::string name) override;
  ComputePipelineState *GetComputePipelineState(guid_t id) override;
  vbool DestroyComputePipelineState(guid_t id) override;  

  ShaderProgram *CreateShaderProgram() override;
  ShaderProgram *GetShaderProgram(guid_t id) override;
  vbool DestroyShaderProgram(guid_t id) override;
  
  Texture *CreateTexture(std::string name, TextureTarget target, 
    std::string filepath, vbool alpha) override;
  Texture *GetTexture(guid_t id) override;
  vbool DestroyTexture(guid_t id) override;

};


/**
  Vulkan Resources held within this singleton object.
*/
class VKResources : public Resources {


};
} // vikr
#endif // __VIKR_VULKAN_RESOURCE_MANAGER_HPP