//
//
//
#include <resources/opengl/gl_resource_manager.hpp>
#include <shader/glsl/glsl_shader.hpp>
#include <shader/material.hpp>

namespace vikr {


std::unordered_map<std::string,
  std::pair<std::string, std::unique_ptr<GLSLShader> > > GLResourceManager::shaders;


std::vector<std::shared_ptr<GLMesh> > GLResourceManager::meshes;
std::vector<std::shared_ptr<Material> > GLResourceManager::materials;


GLResourceManager::GLResourceManager()
  : ResourceManager(vikr_OPENGL)
{
}


vint32 GLResourceManager::StoreShader(std::string name, Shader *shader) {
  vint32 success = 0;
  if (shader && shader->IsLinked()) {
    shaders[name] = std::make_pair(name, std::make_unique<GLSLShader>(
                    std::move(*static_cast<GLSLShader *>(shader))));
  }
  return success;
}


Shader *GLResourceManager::GetShader(std::string name) {
  if (shaders.find(name) != shaders.end()) {
    return static_cast<Shader *>(shaders[name].second.get());
  }
  return nullptr;
}


Mesh *GLResourceManager::CreateMesh(std::vector<glm::vec3> positions,
                                    std::vector<glm::vec3> normals,
                                    std::vector<glm::vec2> uvs,
                                    std::vector<vuint32> indices) 
{
  std::shared_ptr<GLMesh> mesh = std::make_shared<GLMesh>();
  mesh->Buffer(positions, normals, uvs, indices);
  mesh->Create();
  meshes.push_back(mesh);
  return mesh.get();
}


/**
  For now.
*/
Material *GLResourceManager::CreateMaterial() {
  std::shared_ptr<Material> material = std::make_shared<Material>();
  materials.push_back(material);
  return material.get();
}
} // vikr