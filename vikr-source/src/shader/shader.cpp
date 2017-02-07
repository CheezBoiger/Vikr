//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/shader/shader.hpp>


namespace vikr {


Shader::Shader(ShaderStage stage, ShaderLanguage lang)
  : shader_id(0)
  , shader_lang(lang)
{
}
} // vikr