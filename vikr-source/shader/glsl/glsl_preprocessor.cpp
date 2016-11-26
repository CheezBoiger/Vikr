//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <shader/glsl/glsl_preprocessor.hpp>
#include <util/vikr_filesystem.hpp>
#include <fstream>
#include <regex>

namespace vikr {


const std::string include_dir = "#include";


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
  // We need to use Filesystem to check if path exists.
  source_directory = path;
}
} // vikr