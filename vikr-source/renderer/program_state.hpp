//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_PROGRAM_STATE_HPP
#define __VIKR_PROGRAM_STATE_HPP

#include <platform/vikr_types.hpp>
#include <string>

namespace vikr {

class IShader;

/**
  Will have to be abstract.
*/
class ProgramState {
public:
  static ProgramState *Create();
  static ProgramState *CreateWithShaders(std::string vs, std::string fs);
  
  IShader *GetShader() { return shader; }
  vvoid SetShader(IShader *shader) { this->shader = shader; }
protected:
  IShader *shader;
  bool compiled;
};
} // vikr
#endif // __VIKR_PROGRAM_STATE_HPP