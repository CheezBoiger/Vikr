//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_GLSL_PREPROCESSOR_HPP
#define __VIKR_GLSL_PREPROCESSOR_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <string>

namespace vikr {


class GLSLPreprocessor {
public:

  GLSLPreprocessor();

  
  std::string Preprocess(std::string filepath);


  vvoid SetSourceDirectory(std::string path);

private:
  std::string source_directory;
};
} // vikr
#endif // __VIKR_GLSL_PREPROCESSOR_HPP