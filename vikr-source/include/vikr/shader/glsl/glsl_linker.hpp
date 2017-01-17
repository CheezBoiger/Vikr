//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GLSL_LINKER_HPP
#define __VIKR_GLSL_LINKER_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>

namespace vikr {


class GLSLCompiler;
class Shader;


class GLSLLinker {
public:
  GLSLLinker(Shader *shader);

  vint32 Link(GLSLCompiler *vs, GLSLCompiler *fs, GLSLCompiler *gs = nullptr);

  vbool IsLinked() { return is_linked; }
private:
  Shader *shader;

  vbool is_linked = false;
};
} // vikr
#endif // __VIKR_GLSL_LINKER_HPP
