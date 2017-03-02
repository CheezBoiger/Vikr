//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_SHADER_PROGRAM_HPP
#define __VIKR_SHADER_PROGRAM_HPP

#include <vikr/platform/vikr_api.hpp>
#include <vikr/platform/vikr_types.hpp>

#include <vikr/shader/shader_config.hpp>
#include <vikr/shader/shader.hpp>
#include <vikr/scene/guid_generator.hpp>


namespace vikr {


/**
  ShaderProgram is the program used for the pipeline state of our rendering device.
*/
class ShaderProgram : public GUID {
  VIKR_DISALLOW_COPY_AND_ASSIGN(ShaderProgram);
public:
  static const vuint32 kNoShaderProgramId;

  VIKR_DEFAULT_MOVE_AND_ASSIGN(ShaderProgram);
  ShaderProgram() { }

  virtual ~ShaderProgram() { }

  /**
    Get the shader stage of this pipeline.
  */
  virtual Shader *GetShader(ShaderStage stage) = 0;

  /**
    Load the shader reference into this program. Does not build yet until the 
    programmer explicitly says so!
  */
  virtual vbool LoadShader(Shader *shader, vbool force = false) = 0;

  virtual vbool RemoveShader(ShaderStage stage) = 0;

  virtual vbool Build() = 0;

  virtual vbool IsLinked() = 0;

  virtual vvoid Cleanup() = 0;
};
} // vikr
#endif // __VIKR_SHADER_PROGRAM_HPP