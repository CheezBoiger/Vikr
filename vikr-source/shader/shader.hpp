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
  inline vuint32 GetProgram() { return program; }
  inline vbool IsLinked() { return is_linked; }
private:
  vuint32 program;
  vbool is_linked;
};
} // vikr
#endif // __VIKR_SHADER_HPP