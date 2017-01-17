//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/shader/shader.hpp>


namespace vikr {


Shader::Shader()
  : shader_id(0)
  , is_linked(false)
  , shader_type(vikr_GLSL)
{
}
} // vikr