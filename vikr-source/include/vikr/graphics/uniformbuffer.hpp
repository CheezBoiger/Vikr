//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_UNIFORMBUFFER_HPP
#define __VIKR_UNIFORMBUFFER_HPP

#include <vikr/platform/vikr_api.hpp>
#include <vikr/platform/vikr_types.hpp>
#include <vikr/graphics/render_device.hpp>

#include <string>


namespace vikr {


class ShaderProgram;



/// Uniform Buffer Objects act as global uniform variables that should remain the 
/// same through all shader stages in a program, there would be no need to constantly
/// declare variables and pass them as varying parameters.
/// Vulkan has an interesting implementation, in that uniform variables
/// are to be provided in a struct-like buffer object in GLSL code. 
/// Since vulkan commands are not dynamic, nor do they execute immidiately,
/// It's in our best interest to allocate a sized array of bytes within this
/// uniform buffer object, to which we then pass on offsets to Vulkan upon
/// execution of the MVP matrix, to which each Renderable will have their 
/// own unique model matrix.
class Uniformbuffer : public RenderDeviceObject, public GUID {
  VIKR_DISALLOW_COPY_AND_ASSIGN(Uniformbuffer);
public:
  VIKR_DEFAULT_MOVE_AND_ASSIGN(Uniformbuffer);
  Uniformbuffer(GraphicsAPIType type) 
    : RenderDeviceObject(type) { }

  virtual ~Uniformbuffer() { }

  /// Generate the Uniformbuffer object with allocated x amount of bytes.
  /// The x amount of bytes is determined by the number of data values 
  /// the programmer intends to allocate for the shader. If the uniform
  /// buffer object is dynamic (in the case for vulkan) model matrices may
  /// need to be allocated depending on the number of model matrices per object. 
  virtual vvoid Generate(vuint32 bind, vuint32 bytes) = 0;

  /// Update the the Uniform buffer. This is useful when the uniformbuffer
  /// needs to update contents in the shader. Shader will see this as 
  /// visible.
  virtual vvoid Update() = 0;

  /// Reallocate the number of bytes for this uniform buffer. This would be
  /// usefull for vulkan implementations.
  virtual vvoid Reallocate(vuint32 new_bytes) = 0;

  ///  Store data into the uniform buffer.
  ///  @param bytes Size of data in bytes.
  ///  @param data Raw data.
  virtual vvoid StoreData(vuint32 offset, vuint32 bytes, vbyte *data) = 0;

  /// Primitive uniform defines.
  virtual vvoid SetTexture(vuint32 offset, Texture *texture) = 0;
  virtual vvoid SetCubemap(vuint32 offset, Cubemap *cubemap) = 0;
  virtual vvoid SetInt(vuint32 offset, vint32 value) = 0;
  virtual vvoid SetBool(vuint32 offset, vbool value) = 0;
  virtual vvoid SetVector4fv(vuint32 offset, glm::vec4 value) = 0;
  virtual vvoid SetVector3fv(vuint32 offset, glm::vec3 value) = 0;
  virtual vvoid SetVector2fv(vuint32 offset, glm::vec2 value) = 0;
  virtual vvoid SetFloat(vuint32 offset, vreal32 value) = 0;
  virtual vvoid SetDouble(vuint32 offset, vreal64 value) = 0;
  virtual vvoid SetMat4(vuint32 offset, glm::mat4 value) = 0;
  virtual vvoid SetMat3(vuint32 offset, glm::mat3 value) = 0;
  virtual vvoid SetMat2(vuint32 offset, glm::mat2 value) = 0;
};
} // vikr
#endif // __VIKR_UNIFORMBUFFER_HPP