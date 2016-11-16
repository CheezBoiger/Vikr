//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_ISHADER_HPP
#define __VIKR_ISHADER_HPP


#include <platform/vikr_types.hpp>


namespace vikr {


enum ShaderType {
  vikr_GLSL,
  vikr_SPIRV
};


/**
  Shader interface to define shader type for a specific graphics API.
*/
class IShader {
public:
  IShader() { }
  virtual ~IShader() { }

  virtual vvoid Compile() = 0;
  virtual vvoid Cleanup() = 0;

  virtual ShaderType GetShaderType() = 0;

  virtual vbool IsCompiled() = 0;

  virtual vuint32 GetShaderId() = 0;
};
} // vikr
#endif // __VIKR_ISHADER_HPP