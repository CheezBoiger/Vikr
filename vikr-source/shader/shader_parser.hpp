//
// Copyright (c) Mario Garcia, under the MIT License.
//
#ifndef __VIKR_SHADER_PARSER_HPP
#define __VIKR_SHADER_PARSER_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>

namespace vikr {


class GLShader;
class Shader;


class ShaderParser {
public:
  static vvoid FillUniforms(Shader *shader, GLShader *gl);
};
} // vikr
#endif // __VIKR_SHADER_PARSER_HPP