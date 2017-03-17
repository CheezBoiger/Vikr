//
// Copyright (c) Mario Garcia, Under the MIT license.
//
#ifndef __VIKR_GL4_UNIFORMBUFFER_HPP
#define __VIKR_GL4_UNIFORMBUFFER_HPP


#include <vikr/graphics/uniformbuffer.hpp>
#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <vikr/graphics/gl4/gl4_graphics_pipeline_state.hpp>


#include <vikr/shader/texture_config.hpp>


namespace vikr {


/// The OpenGL 4.3 uniformbuffer object for use with redudant data
/// passed on to your shaders. Data passed in the uniform buffer object
/// vary from matrices to vectors, to integers to floats. If a sampler 
/// needs to be passed, such as Textures or depth maps, use Materials
/// instead...
///
/// Binding and unbinding happens implicitly, so no need to explicitly
/// do so...
class GL4Uniformbuffer : public Uniformbuffer {
public:
  /// Default Uniform buffer.
  GL4Uniformbuffer();

  vvoid Generate(vuint32 bind, vuint32 bytes) override;
  vvoid Reallocate(vuint32 new_bytes) override;

  vvoid Bind();
  vvoid Unbind();

  vvoid Update() override;
  vvoid StoreData(vuint32 offset, vuint32 bytes, vbyte *data) override;
  vvoid Cleanup() override;

  vvoid SetInt(vuint32 offset, vint32 value) override;
  vvoid SetBool(vuint32 offset, vbool value) override;
  vvoid SetVector4fv(vuint32 offset, glm::vec4 value) override;
  vvoid SetVector3fv(vuint32 offset, glm::vec3 value) override;
  vvoid SetVector2fv(vuint32 offset, glm::vec2 value) override;
  vvoid SetFloat(vuint32 offset, vreal32 value) override;
  vvoid SetDouble(vuint32 offset, vreal64 value) override;
  vvoid SetMat4(vuint32 offset, glm::mat4 value) override;
  vvoid SetMat3(vuint32 offset, glm::mat3 value) override;
  vvoid SetMat2(vuint32 offset, glm::mat2 value) override;

  GLuint GetNativeUBO() { return m_ubo; }

private:
  GLuint m_ubo; 
  vuint32 m_bytes;
  vuint32 m_bind;
};
} // vikr
#endif // __VIKR_GL4_UNIFORMBUFFER_HPP