//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_GLSL_PARSER_HPP
#define __VIKR_GLSL_PARSER_HPP

#include <shader/shader_parser.hpp>


namespace vikr {


class GLSLParser : public ShaderParser {
public:
  GLSLParser(Shader *shader);
  GLSLParser(GLSLParser&& p) = default;
  GLSLParser& operator=(GLSLParser&&) = default;

  vvoid ParseActiveUniforms() override;
  vvoid ParseActiveAttributes() override;

private:

};
} // vikr
#endif // __VIKR_GLSL_PARSER_HPP