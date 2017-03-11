//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_UNIFORMBUFFER_HPP
#define __VIKR_UNIFORMBUFFER_HPP

#include <vikr/platform/vikr_api.hpp>
#include <vikr/platform/vikr_types.hpp>

#include <string>


namespace vikr {


class ShaderProgram;



/// Uniform Buffer Objects act as global uniform variables that should remain the 
/// same through all shader stages in a program, there would be no need to constantly
/// declare variables and pass them as varying parameters.
class Uniformbuffer : public GUID {
  VIKR_DISALLOW_COPY_AND_ASSIGN(Uniformbuffer);
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(Uniformbuffer);
  Uniformbuffer() { }

  virtual ~Uniformbuffer() { }

  /// Generate the Uniformbuffer object with allocated x amount of bytes.
  virtual vvoid Generate(vuint32 bytes) = 0;

  /// Get a shader program from this uniformbuffer.
  virtual ShaderProgram *GetShaderProgram(vuint32 i) = 0;

  /// Store a given shader program that contains the layout of the 
  /// uniform block in your shader code.
  /// Very useful for programs using view projections from camera.
  virtual vvoid StoreShaderProgram(ShaderProgram *program) = 0;

  /// Update the the Uniform buffer.
  virtual vvoid Update() = 0;

  /// Set the binding for the uniform block. This is to be kept inside a 
  /// dictionary for the uniformbuffer object.
  virtual vvoid SetBlockBinding(vuint32 point, std::string identifier) = 0;

  ///  Store data into the uniform buffer.
  ///  @param bytes Size of data in bytes.
  ///  @param data Raw data.
  virtual vvoid StoreData(vuint32 bytes, vbyte *data) = 0;
};
} // vikr
#endif // __VIKR_UNIFORMBUFFER_HPP