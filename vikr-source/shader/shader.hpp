//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#ifndef __VIKR_SHADER_HPP
#define __VIKR_SHADER_HPP

#include <shader/ishader.hpp>


namespace vikr {


class GLShader;


/**
  For now it only works with OpenGL, Spir-V not yet implemented!
*/
class Shader {
public:
  Shader();

  vvoid Link(IShader* vs, IShader* fs, IShader* gs = nullptr);
  vvoid Use() { UseProgram(program); }
  vuint32 GetProgram() { return program; }
private:
  vuint32 program;
};
} // vikr
#endif // __VIKR_SHADER_HPP