//
//
//
#include <resources/opengl/gl_resource_manager.hpp>
#include <shader/glsl/glsl_shader.hpp>
#include <shader/material.hpp>
#include <shader/glsl/gl_texture1d.hpp>
#include <shader/glsl/gl_texture2d.hpp>
#include <shader/glsl/gl_texture3d.hpp>

namespace vikr {


std::unordered_map<std::string,
  std::pair<std::string, std::unique_ptr<GLSLShader> > > GLResources::shaders;

std::vector<std::shared_ptr<GLMesh> > GLResources::meshes;
std::vector<std::shared_ptr<Material> > GLResources::materials;


GLResourceManager::GLResourceManager()
  : ResourceManager(vikr_OPENGL)
{
}


vint32 GLResourceManager::StoreShader(std::string name, Shader *shader) {
  vint32 success = 0;
  if (shader && shader->IsLinked()) {
    GLResources::shaders[name] = std::make_pair(name, std::make_unique<GLSLShader>(
                    std::move(*static_cast<GLSLShader *>(shader))));
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
  std::shared_ptr<GLMesh> mesh = std::make_shared<GLMesh>();
  mesh->Buffer(positions, normals, uvs, indices);
 // mesh->Create();
  GLResources::meshes.push_back(mesh);
  return mesh.get();
}


Mesh *GLResourceManager::CreateMesh(
  std::vector<Vertex> vertices,
  std::vector<vuint32> indices) 
{
  std::shared_ptr<GLMesh> mesh = std::make_shared<GLMesh>();
  mesh->Buffer(vertices, indices);
  //mesh->Create();
  GLResources::meshes.push_back(mesh);
  return mesh.get();
}


/**
  For now.
*/
Material *GLResourceManager::CreateMaterial() {
  std::shared_ptr<Material> material = std::make_shared<Material>();
  GLResources::materials.push_back(material);
  return material.get();
}


Texture *GLResourceManager::CreateTexture(TextureTarget target, std::string img_path, vbool alpha) {
  Texture *texture = nullptr;
  vint32 width = 0;
  vint32 height = 0;
  vint32 depth = 0;
  vbyte *bytecode = stbi_load(img_path.c_str(), &width, &height, &depth,
                              alpha ? STBI_rgb_alpha : STBI_rgb);
  switch(target) {
  case vikr_TEXTURE_1D: texture = new GLTexture1D(width); break;
  case vikr_TEXTURE_2D: texture = new GLTexture2D(width, height); break;
  case vikr_TEXTURE_3D: texture = new GLTexture3D(width, height, depth); break;
  case vikr_TEXTURE_CUBEMAP: // not implemented yet.
  default: break;
  }
  if(texture) {
    texture->Create(bytecode);
    texture->SetString(img_path);
  }
  return texture;
}


vint32 GLResourceManager::StoreShader(std::string shader_name,
                               std::string vs,
                               std::string fs,
                               std::string include_path)
{
  GLSLShader shader;
  shader.SetIncludeSearchPath(include_path);
  shader.Compile(vs, fs);
  if(shader.IsLinked()) {
    return ResourceManager::GetResourceManager()->StoreShader(shader_name, &shader);
  }
  return -1;
}
} // vikr