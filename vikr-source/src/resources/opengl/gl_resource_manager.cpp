//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/resources/opengl/gl_resource_manager.hpp>
#include <vikr/shader/glsl/glsl_shader.hpp>
#include <vikr/shader/material.hpp>
#include <vikr/mesh/mesh.hpp>
#include <vikr/shader/glsl/gl4_texture1d.hpp>
#include <vikr/shader/glsl/gl4_texture2d.hpp>
#include <vikr/shader/glsl/gl4_texture3d.hpp>
#include <vikr/shader/glsl/glsl_program.hpp>
#include <vikr/shader/stb/stb_image.h>

#include <vikr/graphics/gl4/gl4_pipeline_state.hpp>
#include <vikr/shader/glsl/glsl_program.hpp>
#include <vikr/util/vikr_log.hpp>


namespace vikr {


std::unordered_map<guid_t, std::unique_ptr<GLSLShader> > GLResources::shaders;
std::map<guid_t, std::unique_ptr<GL4Texture> > GLResources::textures;
std::map<guid_t, std::unique_ptr<GLSLShaderProgram> > GLResources::shader_programs;
std::map<guid_t, std::unique_ptr<GL4PipelineState> > GLResources::pipelinestates;


GLResourceManager::GLResourceManager()
  : ResourceManager(vikr_PIPELINE_OPENGL)
{
}


Shader *GLResourceManager::CreateShader(std::string name, ShaderStage stage) {
  std::unique_ptr<GLSLShader> shader = std::make_unique<GLSLShader>(stage);
  shader->SetName(name);

  guid_t id = shader->GetUID();
  GLResources::shaders[shader->GetUID()] = std::move(shader);
  return static_cast<Shader *>(GLResources::shaders[id].get());
}


Shader *GLResourceManager::GetShader(guid_t id) {
  if (GLResources::shaders.find(id) != GLResources::shaders.end()) {
    return static_cast<Shader *>(GLResources::shaders[id].get());
  }
  return nullptr;
}


vbool GLResourceManager::DestroyShader(guid_t id) {
  vbool success = false;
  auto it = GLResources::shaders.find(id);
  if (it != GLResources::shaders.end()) {
    // cleanup first. Make sure the shader is not leaked.
    it->second->Cleanup();
    GLResources::shaders.erase(it);
    VikrLog::DisplayMessage(VIKR_RUNTIME_DEBUG, "Shader id => " 
      + std::to_string(id) + " removed.");
    success = true;
  } 
  return success;
}


Texture *GLResourceManager::CreateTexture(
  std::string name, 
  TextureTarget target, 
  std::string filepath, 
  vbool alpha) 
{
  std::unique_ptr<GL4Texture> texture = nullptr;
  vint32 width = 0;
  vint32 height = 0;
  vint32 depth = 0;
  vbyte *bytecode = stbi_load(filepath.c_str(), &width, &height, &depth,
                              alpha ? STBI_rgb_alpha : STBI_rgb);
  switch(target) {
  case vikr_TARGET_1D: texture = std::make_unique<GL4Texture1D>(width); break;
  case vikr_TARGET_2D: texture = std::make_unique<GL4Texture2D>(width, height); break;
  case vikr_TARGET_3D: texture = std::make_unique<GL4Texture3D>(width, height, depth); break;
  case vikr_TARGET_CUBEMAP: // not implemented yet.
  default: break;
  }
  guid_t id = texture->GetUID();
  if (texture) {
    texture->SetByteCode(bytecode);
    //texture->Finalize(); // No need to tell the resource manager to finalize for us.
    texture->SetPath(filepath);
    texture->SetName(name);
    GLResources::textures[texture->GetUID()] = std::move(texture);
  }
  return GLResources::textures[id].get();
}


Texture *GLResourceManager::GetTexture(guid_t id) {
  return GLResources::textures[id].get();
}


vbool GLResourceManager::DestroyTexture(guid_t id) {
  auto it = GLResources::textures.find(id);
  vbool success = false;
  if (it != GLResources::textures.end()) {
    // Cleanup first.
    it->second->Cleanup();
    GLResources::textures.erase(it);
    success = true;
  }
  return success;
}


PipelineState *GLResourceManager::CreatePipelineState(std::string name) {
  std::unique_ptr<GL4PipelineState> gl_pipeline =
    std::make_unique<GL4PipelineState>();
  gl_pipeline->SetName(name);
  guid_t id = gl_pipeline->GetUID();
  GLResources::pipelinestates[gl_pipeline->GetUID()] = std::move(gl_pipeline);
  return static_cast<PipelineState *>(GLResources::pipelinestates[id].get());
}


PipelineState *GLResourceManager::GetPipelineState(guid_t id) {
  auto it = GLResources::pipelinestates.find(id);
  if (it != GLResources::pipelinestates.end()) {
    return GLResources::pipelinestates[id].get();
  }
  return nullptr;
}


vbool GLResourceManager::DestroyPipelineState(guid_t id) {
  vbool success = false;
  auto it = GLResources::pipelinestates.find(id);
  if (it != GLResources::pipelinestates.end()) {
    GLResources::pipelinestates.erase(it);
    success = true;
  }
  return success;
}


ShaderProgram *GLResourceManager::CreateShaderProgram() {
  std::unique_ptr<GLSLShaderProgram> prgm =
    std::make_unique<GLSLShaderProgram>();
  guid_t id = prgm->GetUID();
  GLResources::shader_programs[prgm->GetUID()] = std::move(prgm);
  return GLResources::shader_programs[id].get();
}


ShaderProgram *GLResourceManager::GetShaderProgram(guid_t uid) {
  auto it = GLResources::shader_programs.find(uid);
  if (it != GLResources::shader_programs.end()) {
    return GLResources::shader_programs[uid].get();
  }
  return nullptr;
}


vbool GLResourceManager::DestroyShaderProgram(guid_t id) {
  vbool success = false;
  auto it = GLResources::shader_programs.find(id);
  if (it != GLResources::shader_programs.end()) {
    it->second->Cleanup();
    GLResources::shader_programs.erase(it);
    success = true;
  }
  return success;
}
} // vikr