//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/resources/vulkan/vk_resource_manager.hpp>
#include <vikr/shader/spv/spv_shader.hpp>
#include <vikr/graphics/vk/vk_pipeline_state.hpp>
#include <vikr/shader/spv/spv_program.hpp>
#include <vikr/shader/spv/spv_texture.hpp>


namespace vikr {


VKResourceManager::VKResourceManager()
{
}


Shader *VKResourceManager::CreateShader(std::string name, ShaderStage stage) {
  return nullptr;
}


Shader *VKResourceManager::GetShader(guid_t id) {
  return nullptr;
}


vbool VKResourceManager::DestroyShader(guid_t id) {
  return false;
}


PipelineState *VKResourceManager::CreatePipelineState(std::string name) {
  return nullptr;
}


PipelineState *VKResourceManager::GetPipelineState(guid_t id) {
  return nullptr;
}


vbool VKResourceManager::DestroyPipelineState(guid_t id) {
  return false;
}


ShaderProgram *VKResourceManager::CreateShaderProgram() {
  return nullptr;
}


ShaderProgram *VKResourceManager::GetShaderProgram(guid_t id) {
  return nullptr;
}


vbool VKResourceManager::DestroyShaderProgram(guid_t id) {
  return false;
}


Texture *VKResourceManager::CreateTexture(
  std::string name, 
  TextureTarget target,
  std::string img_path,
  vbool alpha)
{
  return nullptr;
}


Texture *VKResourceManager::GetTexture(std::string filepath) {
  return nullptr;
}


vbool VKResourceManager::DestroyTexture(std::string filepath) {
  return false;
}
} // vikr