//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_ISHADER_LINKER_HPP
#define __VIKR_ISHADER_LINKER_HPP


#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>


namespace vikr {


class IShaderCompiler;
class Shader;


class ShaderLinker {
public:
  ShaderLinker(Shader *shader)
    : shader_ref(shader) { }

  virtual ~ShaderLinker() { }

  virtual vint32 Link(IShaderCompiler *vs, IShaderCompiler *fs, IShaderCompiler *gs = nullptr) = 0;

protected:
  Shader *shader_ref;  
};
} // vikr
#endif // __VIKR_ISHADER_LINKER_HPP