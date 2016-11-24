//
//
//
#include <resources/opengl/gl_resources.hpp>
#include <shader/glsl/glsl_shader.hpp>

namespace vikr {


std::unordered_map<std::string, 
          std::pair<std::string, std::unique_ptr<GLSLShader> > > GLResources::shaders;


vint32 GLResources::StoreShader(std::string name, GLSLShader *shader) {
  vint32 success = 0;
  if (shader && shader->IsLinked()) {
    shaders[name] = std::make_pair(name, std::make_unique<GLSLShader>(std::move(*shader)));
  }
  return success;
}


GLSLShader *GLResources::GetShader(std::string name) {
  if (shaders.find(name) != shaders.end()) {
    return shaders[name].second.get();
  }
  return nullptr;
}
} // vikr