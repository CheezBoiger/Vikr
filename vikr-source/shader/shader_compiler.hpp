//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_ISHADER_COMPILER_HPP
#define __VIKR_ISHADER_COMPILER_HPP


#include <platform/vikr_types.hpp>


namespace vikr {


enum ShaderCompilerType {
  vikr_GLSL,
  vikr_SPIRV
};


/**
  Shader interface to define shader type for a specific graphics API.
*/
class IShaderCompiler {
public:
  IShaderCompiler() { }
  virtual ~IShaderCompiler() { }

  virtual vvoid Compile() = 0;
  virtual vvoid Cleanup() = 0;

  virtual ShaderCompilerType GetShaderType() = 0;

  virtual vbool IsCompiled() = 0;

  virtual vuint32 GetShaderId() = 0;
};
} // vikr
#endif // __VIKR_ISHADER_COMPILER_HPP