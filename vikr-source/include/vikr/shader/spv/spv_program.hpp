//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_SPV_SHADER_PROGRAM_HPP
#define __VIKR_SPV_SHADER_PROGRAM_HPP


#include <vikr/shader/shader_program.hpp>
#include <map>


namespace vikr {


class SpvShader;


class SpvShaderProgram : public ShaderProgram {
public:
  SpvShaderProgram();

  Shader *GetShader(ShaderStage stage) override;

  vbool LoadShader(Shader *shader, vbool force = false) override;

  vbool RemoveShader(ShaderStage stage) override;

  vuint32 GetNativeId() override;

  vbool Build() override;

  vbool IsLinked() override;

  vvoid Cleanup() override;

private:

  std::map<ShaderStage, SpvShader *> m_shaders;
};
} // vikr
#endif // __VIKR_SPV_SHADER_PROGRAM_HPP