//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/shader/shader.hpp>


namespace vikr {


Shader::Shader(ShaderStage stage, ShaderLanguage lang)
  : shader_lang(lang)
  , shader_stage(stage)
{
}
} // vikr