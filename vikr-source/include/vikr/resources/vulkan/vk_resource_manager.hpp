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
class VkResourceManager : public ResourceManager {
public:
  VkResourceManager();

  Shader *CreateShader(std::string name, ShaderStage stage) override;
  Shader *GetShader(std::string name) override;
  vbool DestroyShader(std::string name) override;

  PipelineState *CreatePipelineState(std::string name) override;
  PipelineState *GetPipelineState(std::string name) override;
  vbool DestroyPipelineState(std::string name) override;
  
  ShaderProgram *CreateShaderProgram() override;
  ShaderProgram *GetShaderProgram(guid_t id) override;
  vbool DestroyShaderProgram(guid_t id) override;

  Mesh *CreateMesh(std::vector<glm::vec3> positions,
    std::vector<glm::vec3> normals,
    std::vector<glm::vec2> uvs,
    std::vector<vuint32> indices = std::vector<vuint32>(),
    std::vector<glm::vec3> tangents = std::vector<glm::vec3>(),
    std::vector<glm::vec3> bitangents = std::vector<glm::vec3>(),
    std::vector<glm::vec3> colors = std::vector<glm::vec3>()) override;


};


/**
  Vulkan Resources held within this singleton object.
*/
class VkResources : public Resources {


};
} // vikr
#endif // __VIKR_VULKAN_RESOURCE_MANAGER_HPP