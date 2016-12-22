//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <shader/glsl/glsl_shader.hpp>
#include <shader/glsl/glsl_compiler.hpp>
#include <shader/glsl/glsl_linker.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <util/vikr_log.hpp>

namespace vikr {


GLSLShader::GLSLShader()
{
  shader_type = vikr_GLSL;
}


vvoid GLSLShader::Compile(std::string vs, std::string fs, std::string gs) {
  GLSLCompiler vert(vikr_VERTEX_SHADER, vs);
  GLSLCompiler frag(vikr_FRAGMENT_SHADER, fs);
  GLSLCompiler geo(vikr_GEOMETRY_SHADER, gs);
  GLSLLinker linker(this);
  vert.GetPreprocessor()->SetSourceDirectory(include_searchpath);
  frag.GetPreprocessor()->SetSourceDirectory(include_searchpath);
  geo.GetPreprocessor()->SetSourceDirectory(include_searchpath);
  vert.Compile();
  frag.Compile();
  if (!gs.empty()) {
    geo.Compile();
  }
  if (vert.IsCompiled() && frag.IsCompiled()) {
    shader_id = CreateProgram();
    linker.Link(&vert, &frag, &geo);
    if (!linker.IsLinked()) {
      VikrLog::DisplayMessage(VIKR_ERROR, "Shader was not linked!");
    }
  } else {
    VikrLog::DisplayMessage(VIKR_ERROR, "Shaders unsuccessfully compiled!");
    if (!vert.IsCompiled()) {
      VikrLog::DisplayMessage(VIKR_ERROR, "In Vertex Shader!");
    } else if (!frag.IsCompiled()) {
      VikrLog::DisplayMessage(VIKR_ERROR, "In Fragment Shader!");
    } else {
      VikrLog::DisplayMessage(VIKR_ERROR, "In Geometry Shader!!");
    }
  }
  is_linked = linker.IsLinked();
}
} // vikr