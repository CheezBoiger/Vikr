//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GLSL_LINKER_HPP
#define __VIKR_GLSL_LINKER_HPP

#include <shader/shader_linker.hpp>

namespace vikr {


class GLSLCompiler;


class GLSLLinker : public ShaderLinker {
public:
  GLSLLinker(Shader *shader);

  vint32 Link(IShaderCompiler *vs, IShaderCompiler *fs, IShaderCompiler *gs = nullptr) override;

  GLSLCompiler *ToCompiler(IShaderCompiler *c);  

private:
};
} // vikr
#endif // __VIKR_GLSL_LINKER_HPP
