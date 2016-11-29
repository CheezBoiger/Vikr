//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_GLSL_PREPROCESSOR_HPP
#define __VIKR_GLSL_PREPROCESSOR_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <string>

namespace vikr {


/**
  Preprocessor for GLSL. It can set the include path for the preprocessor to
  paste a file into a currently read file, and eventually be recursed through.
*/
class GLSLPreprocessor {
public:

  GLSLPreprocessor();

  /**
    Preprocesses the given file. Returns the 
    GLSL file in the form of a big ass string.
  */
  std::string Preprocess(std::string filepath);

  /**
    Set the include path for this preprocessor. 
  */
  vvoid SetSourceDirectory(std::string path);

private:
  /**
    Include directory, or source directory.
  */
  std::string source_directory;
};
} // vikr
#endif // __VIKR_GLSL_PREPROCESSOR_HPP