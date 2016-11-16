//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_PROGRAM_STATE_HPP
#define __VIKR_PROGRAM_STATE_HPP

#include <platform/vikr_types.hpp>
#include <string>

namespace vikr {


class Shader;


/**
  Will have to be abstract.
*/
class ProgramState {
public:
  static ProgramState *Create();
  static ProgramState *CreateWithShaders(std::string vs, std::string fs);
  
  Shader *GetShader() { return shader; }
  vvoid SetShader(Shader *shader) { this->shader = shader; }

protected:
  Shader *shader;
};
} // vikr
#endif // __VIKR_PROGRAM_STATE_HPP