//
// Copyright (c) Mario Garcia, Under the MIT license.
//
#ifndef __VIKR_GL4_UNIFORMBUFFER_HPP
#define __VIKR_GL4_UNIFORMBUFFER_HPP


#include <vikr/graphics/uniformbuffer.hpp>
#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>


#include <vikr/shader/glsl/glsl_program.hpp>


namespace vikr {


/// The OpenGL 4.3 uniformbuffer object for use with redudant data
/// passed on to your shaders. 
///
/// Binding and unbinding happens implicitly, so no need to explicitly
/// do so...
class GL4Uniformbuffer : public Uniformbuffer {
public:
  /// Default Uniform buffer.
  GL4Uniformbuffer();

  vvoid Generate(vuint32 bytes) override;
  vvoid StoreShaderProgram(ShaderProgram *program) override;
  ShaderProgram *GetShaderProgram(vuint32 i) override;
  vbool RemoveShaderProgram(vuint32 i) override;

  vvoid Bind();
  vvoid Unbind();

  vvoid Update() override;
  vvoid StoreData(vuint32 bytes, vbyte *data) override;
    

private:

  std::vector<GLSLShaderProgram *> m_shaderPrograms;
};
} // vikr
#endif // __VIKR_GL4_UNIFORMBUFFER_HPP