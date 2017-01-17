//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_SPIRV_COMPILER_HPP
#define __VIKR_SPIRV_COMPILER_HPP


#include <shader/shader.hpp>
#include <shader/shader_config.hpp>
#include <glslang/Public/ShaderLang.h>

//
// We write SPIR-V shader here!
//

namespace vikr {


/**
  SpirV Compiler
*/
class SpvCompiler {
public:
  
private:
  /**
    GLslang compiler handle
  */
  ShHandle compiler_handle = nullptr;
};
} // vikr
#endif // __VIKR_SPIRV_COMPILER_HP