//
//
//
#include <resources/opengl/gl_resource_manager.hpp>
#include <shader/glsl/glsl_shader.hpp>

namespace vikr {


std::unordered_map<std::string,
  std::pair<std::string, std::unique_ptr<GLSLShader> > > GLResourceManager::shaders;


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
} // vikr