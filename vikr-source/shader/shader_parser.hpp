//
// Copyright (c) Mario Garcia, under the MIT License.
//
#ifndef __VIKR_SHADER_PARSER_HPP
#define __VIKR_SHADER_PARSER_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>

namespace vikr {


class Shader;


class ShaderParser {
public:
  ShaderParser(ShaderParser&&) = default;
  ShaderParser& operator=(ShaderParser&&) = default;
  virtual ~ShaderParser() { }

  virtual vvoid ParseActiveUniforms() = 0;
  virtual vvoid ParseActiveAttributes() = 0;


protected:
  ShaderParser(Shader *shader_ref)
    : shader_ref(shader_ref) { }

  Shader *shader_ref;

  friend class Shader;
};
} // vikr
#endif // __VIKR_SHADER_PARSER_HPP