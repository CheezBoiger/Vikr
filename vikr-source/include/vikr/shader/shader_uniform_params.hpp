//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_SHADER_UNIFORM_PARAMS_HPP
#define __VIKR_SHADER_UNIFORM_PARAMS_HPP


#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <vikr/shader/shader_config.hpp>

#include <map>


namespace vikr {


/**
  Container holding the values of Material.
*/
struct ShaderUniformParams {
  std::map<std::string, MaterialValue>  *uniforms   = nullptr;
  std::map<std::string, TextureSampler> *samplers   = nullptr;
};
} // vikr
#endif // __VIKR_SHADER_UNIFORM_PARAMS_HPP