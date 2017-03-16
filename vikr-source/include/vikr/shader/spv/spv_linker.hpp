//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_SPV_LINKER_HPP
#define __VIKR_SPV_LINKER_HPP


#include <vikr/platform/vikr_api.hpp>
#include <vikr/platform/vikr_types.hpp>

#include <glslang/Public/ShaderLang.h>
#include <SPIRV/GlslangToSpv.h>


namespace vikr {


/// SPIR-V linker object, used to link several 
/// SPIR-V shader objects into one program.
class SpvLinker {
public:

private:

  glslang::TProgram *program;
};
} // vikr
#endif // __VIKR_SPV_LINKER_HPP