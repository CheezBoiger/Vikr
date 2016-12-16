//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <shader/glsl/glsl_preprocessor.hpp>
#include <util/vikr_filesystem.hpp>
#include <fstream>
#include <regex>

namespace vikr {


const std::string include_dir             = "#include";
/**
Static values to be implemented into the vertex shader.
*/
const std::string vikr_model              = "uniform mat4 vikr_model;";
const std::string vikr_view               = "uniform mat4 vikr_view;";
const std::string vikr_projection         = "uniform mat4 vikr_projection;";
/**
Static values to be implemented into the fragement shader.
*/
const std::string vikr_camPosition        = "uniform vec3 vikr_camPosition";
const std::string vikr_pointLights        = "uniform PointLight vikr_pointLights[]";
const std::string vikr_directionalLights  = "uniform DirectionLight vikr_directionalLights[]";
const std::string vikr_spotLights         = "uniform SpotLight vikr_spotLights[]";


GLSLPreprocessor::GLSLPreprocessor()
  : source_directory(".")
{
}


std::string GLSLPreprocessor::Preprocess(std::string filepath) {
  std::regex reg("\\\"");
  std::string code_src;
  std::string code_line;
  std::ifstream file;
  file.open(filepath);
  if (file.is_open()) {
    while (std::getline(file, code_line)) {
      if (code_line.substr(0, 8) == include_dir) {
        std::string include_path = source_directory + "/" + std::regex_replace(code_line.substr(9), reg, "");
        code_src += Preprocess(include_path) + "\n";
        // continue here.
      } else {
        code_src += code_line + "\n";
      }
    }
    file.close();
  }
  return code_src;
}


vvoid GLSLPreprocessor::SetSourceDirectory(std::string path) {
  if (path.empty()) {
    path = ".";
  }
  // We need to use Filesystem to check if path exists.
  source_directory = path;
}
} // vikr