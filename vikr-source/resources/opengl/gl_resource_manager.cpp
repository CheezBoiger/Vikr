//
//
//
#include <resources/opengl/gl_resource_manager.hpp>
#include <shader/glsl/glsl_shader.hpp>
#include <shader/material.hpp>
#include <mesh/mesh.hpp>
#include <shader/glsl/gl_texture1d.hpp>
#include <shader/glsl/gl_texture2d.hpp>
#include <shader/glsl/gl_texture3d.hpp>

namespace vikr {


std::unordered_map<std::string,
  std::pair<std::string, std::unique_ptr<GLSLShader> > > GLResources::shaders;

std::map<guid_t, std::shared_ptr<Mesh> > GLResources::meshes;
std::map<std::string, std::shared_ptr<Material> > GLResources::materials;
std::map<std::string, std::shared_ptr<GLTexture> > GLResources::textures;


GLResourceManager::GLResourceManager()
  : ResourceManager(vikr_PIPELINE_OPENGL)
{
}


vint32 GLResourceManager::StoreShader(std::string name, Shader *shader) {
  vint32 success = 0;
  if (shader && shader->IsLinked()) {
    shader->SetName(name);
    GLResources::shaders[name] = std::make_pair(name, std::make_unique<GLSLShader>(
                    std::move(*static_cast<GLSLShader *>(shader))));
    success = true;
  }
  return success;
}


Shader *GLResourceManager::GetShader(std::string name) {
  if (GLResources::shaders.find(name) != GLResources::shaders.end()) {
    return static_cast<Shader *>(GLResources::shaders[name].second.get());
  }
  return nullptr;
}


Mesh *GLResourceManager::CreateMesh(
  std::vector<glm::vec3> positions,
  std::vector<glm::vec3> normals,
  std::vector<glm::vec2> uvs,
  std::vector<vuint32> indices) 
{
  std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
  mesh->Buffer(positions, normals, uvs, indices);
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


/**
  For now.
*/
Material *GLResourceManager::CreateMaterial(std::string name) {
  std::shared_ptr<Material> material = std::make_shared<Material>();
  material->SetName(name);
  GLResources::materials[material->GetName()] = material;
  return material.get();
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
  if(texture) {
    texture->Create(bytecode);
    texture->SetString(img_path);
    GLResources::textures[img_path] = texture;
  }
  stbi_image_free(bytecode);
  return texture.get();
}


Texture *GLResourceManager::GetTexture(std::string img_path) {
  return GLResources::textures[img_path].get();
}


vint32 GLResourceManager::StoreShader(
  std::string shader_name,
  std::string vs,
  std::string fs,
  std::string include_path)
{
  GLSLShader shader;
  shader.SetIncludeSearchPath(include_path);
  shader.Compile(vs, fs);
  if(shader.IsLinked()) {
    return StoreShader(shader_name, &shader);
  }
  return -1;
}
} // vikr