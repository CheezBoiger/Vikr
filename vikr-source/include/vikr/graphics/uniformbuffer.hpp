//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_UNIFORMBUFFER_HPP
#define __VIKR_UNIFORMBUFFER_HPP

#include <vikr/platform/vikr_api.hpp>
#include <vikr/platform/vikr_types.hpp>


namespace vikr {


class ShaderProgram;


/**
  Uniform Buffer Objects act as global uniform variables that should remain the 
  same through all shader stages in a program, there would be no need to constantly
  declare variables and pass them as varying parameters.
*/
class Uniformbuffer : public GUID {
  VIKR_DISALLOW_COPY_AND_ASSIGN(Uniformbuffer);
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(Uniformbuffer);
  Uniformbuffer() { }

  virtual ~Uniformbuffer() { }

  /**
    Generate the Uniformbuffer object with allocated x amount of bytes.
  */
  virtual vvoid Generate(vuint32 bytes) = 0;

  /**
    Get the Uniform Id.
  */
  virtual vuint64 GetUniformId() = 0;
  
  virtual vvoid Bind() = 0;
  virtual vvoid Unbind() = 0;

  virtual ShaderProgram *GetShaderProgram() = 0;
  virtual vvoid SetShaderProgram(ShaderProgram *program) = 0;

  /**
    Update the the Uniform buffer.
  */
  virtual vvoid Update() = 0;

  virtual vvoid SetBlockBinding(vuint32 point, std::string identifier) = 0;

  /**
    Store data into the uniform buffer.
    @param bytes Size of data in bytes.
    @param data Raw data.
  */
  virtual vvoid StoreData(vuint32 bytes, vbyte *data) = 0;
};
} // vikr
#endif // __VIKR_UNIFORMBUFFER_HPP