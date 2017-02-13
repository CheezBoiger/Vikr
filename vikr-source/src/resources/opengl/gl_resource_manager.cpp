//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/resources/opengl/gl_resource_manager.hpp>
#include <vikr/shader/glsl/glsl_shader.hpp>
#include <vikr/shader/material.hpp>
#include <vikr/mesh/mesh.hpp>
#include <vikr/shader/glsl/gl_texture1d.hpp>
#include <vikr/shader/glsl/gl_texture2d.hpp>
#include <vikr/shader/glsl/gl_texture3d.hpp>
#include <vikr/shader/glsl/glsl_program.hpp>
#include <vikr/shader/stb/stb_image.h>

#include <vikr/graphics/gl4/gl4_pipeline_state.hpp>
#include <vikr/shader/glsl/glsl_program.hpp>
#include <vikr/util/vikr_log.hpp>


namespace vikr {


std::unordered_map<std::string, std::shared_ptr<GLSLShader> > GLResources::shaders;

std::map<guid_t, std::shared_ptr<Mesh> > GLResources::meshes;
std::map<std::string, std::shared_ptr<GLTexture> > GLResources::textures;
std::map<guid_t, std::shared_ptr<GLSLShaderProgram> > GLResources::shader_programs;
std::map<std::string, std::shared_ptr<GL4PipelineState> > GLResources::pipelinestates;


GLResourceManager::GLResourceManager()
  : ResourceManager(vikr_PIPELINE_OPENGL)
{
}


Shader *GLResourceManager::CreateShader(std::string name, ShaderStage stage) {
  if (GLResources::shaders.find(name) != GLResources::shaders.end()) {
    return nullptr;
  }
  std::shared_ptr<GLSLShader> shader = std::make_shared<GLSLShader>(stage);
  shader->SetName(name);

  GLResources::shaders[name] = shader;
  return static_cast<Shader *>(shader.get());
}


Shader *GLResourceManager::GetShader(std::string name) {
  if (GLResources::shaders.find(name) != GLResources::shaders.end()) {
    return static_cast<Shader *>(GLResources::shaders[name].get());
  }
  return nullptr;
}


vbool GLResourceManager::DestroyShader(std::string name) {
  vbool success = false;
  auto it = GLResources::shaders.find(name);
  if (it != GLResources::shaders.end()) {
    // cleanup first. Make sure the shader is not leaked.
    it->second->Cleanup();
    GLResources::shaders.erase(it);
    VikrLog::DisplayMessage(VIKR_RUNTIME_DEBUG, "Shader => " + name + " removed.");
    success = true;
  } 
  return success;
}


Mesh *GLResourceManager::CreateMesh(
  std::vector<glm::vec3> positions,
  std::vector<glm::vec3> normals,
  std::vector<glm::vec2> uvs,
  std::vector<vuint32> indices,
  std::vector<glm::vec3> tangents,
  std::vector<glm::vec3> bitangents,
  std::vector<glm::vec3> colors) 
{
  std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
  mesh->Buffer(positions, normals, uvs, indices, tangents, bitangents, colors);
 // mesh->Create();
  GLResources::meshes[mesh->GetGUID()] = mesh;
  return mesh.get();
}


Mesh *GLResourceManager::CreateMesh(
  std::vector<Vertex> vertices,
  std::vector<vuint32> indices) 
{
  std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
  mesh->Buffer(vertices, indices);
  //mesh->Create();
  GLResources::meshes[mesh->GetGUID()] = mesh;
  return mesh.get();
}


Mesh *GLResourceManager::GetMesh(guid_t guid) {
  return GLResources::meshes[guid].get();
}


vbool GLResourceManager::DestroyMesh(guid_t guid) {
  vbool success = false;
  auto it = GLResources::meshes.find(guid);
  if (it != GLResources::meshes.end()) {
    // Cleanup the mesh vertex buffer.  
    it->second->GetVertexBuffer()->Cleanup();
    GLResources::meshes.erase(it);
    success = true;
  }
  return success;
}


Texture *GLResourceManager::CreateTexture(TextureTarget target, std::string img_path, vbool alpha) {
  std::shared_ptr<GLTexture> texture = nullptr;
  vint32 width = 0;
  vint32 height = 0;
  vint32 depth = 0;
  vbyte *bytecode = stbi_load(img_path.c_str(), &width, &height, &depth,
                              alpha ? STBI_rgb_alpha : STBI_rgb);
  switch(target) {
  case vikr_TEXTURE_1D: texture = std::make_shared<GLTexture1D>(width); break;
  case vikr_TEXTURE_2D: texture = std::make_shared<GLTexture2D>(width, height); break;
  case vikr_TEXTURE_3D: texture = std::make_shared<GLTexture3D>(width, height, depth); break;
  case vikr_TEXTURE_CUBEMAP: // not implemented yet.
  default: break;
  }
  if (texture) {
    texture->SetByteCode(bytecode);
    //texture->Finalize(); // No need to tell the resource manager to finalize for us.
    texture->SetPath(img_path);
    GLResources::textures[img_path] = texture;
  }
  return texture.get();
}


Texture *GLResourceManager::GetTexture(std::string img_path) {
  return GLResources::textures[img_path].get();
}


vbool GLResourceManager::DestroyTexture(std::string img_path) {
  auto it = GLResources::textures.find(img_path);
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
  auto it = GLResources::pipelinestates.find(name);
  PipelineState *pipeline = nullptr;
  if (it == GLResources::pipelinestates.end()) {
    std::shared_ptr<GL4PipelineState> gl_pipeline = 
      std::make_unique<GL4PipelineState>();
    gl_pipeline->SetName(name);
    GLResources::pipelinestates[name] = gl_pipeline;
    return static_cast<PipelineState *>(gl_pipeline.get());
  }
  return pipeline;
}


PipelineState *GLResourceManager::GetPipelineState(std::string name) {
  auto it = GLResources::pipelinestates.find(name);
  if (it != GLResources::pipelinestates.end()) {
    return GLResources::pipelinestates[name].get();
  }
  return nullptr;
}


vbool GLResourceManager::DestroyPipelineState(std::string name) {
  vbool success = false;
  auto it = GLResources::pipelinestates.find(name);
  if (it != GLResources::pipelinestates.end()) {
    GLResources::pipelinestates.erase(it);
    success = true;
  }
  return success;
}


ShaderProgram *GLResourceManager::CreateShaderProgram() {
  std::shared_ptr<GLSLShaderProgram> prgm =
    std::make_shared<GLSLShaderProgram>();
  GLResources::shader_programs[prgm->GetGUID()] = prgm;
  return prgm.get();
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