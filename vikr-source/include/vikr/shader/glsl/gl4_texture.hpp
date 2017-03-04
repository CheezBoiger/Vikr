// 
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_GLTEXTURE_HPP
#define __VIKR_GLTEXTURE_HPP

#include <vikr/shader/texture.hpp>


namespace vikr {


class GL4Texture : public Texture {
public:
  static GLenum GetNativeWrapMode(TextureWrapMode mode);
  static GLenum GetNativeFilterMode(TextureFilterMode mode);
  static GLenum GetNativeTextureTarget(TextureTarget target);
  static GLenum GetBaseFormat(ImageFormat format);
  static GLenum GetInternalFormat(ImageFormat format);
  static GLenum GetNativeDataTypeFormat(ImageFormat format);

  GL4Texture();


  virtual vint32 Finalize() override = 0;
  virtual vvoid Bind(vint32 texture = -1) override;
  virtual vvoid Unbind() override;

  vvoid SetFormat(ImageFormat format) override;
  vvoid SetFilterMin(TextureFilterMode filter) override;
  vvoid SetFilterMax(TextureFilterMode filter) override;
  vvoid SetWrapS(TextureWrapMode mode) override;
  vvoid SetWrapT(TextureWrapMode mode) override;
  vvoid SetWrapR(TextureWrapMode mode) override;
  vvoid SetTarget(TextureTarget target) override;
  vuint32 GetNativeId() { return id; }

  vuint32 GetNativeFormat() { return native_format; }
  vuint32 GetNativeTarget() { return native_target; }
  vuint32 GetNativeInternalFormat() { return native_internal_format; }
  vuint32 GetNativeFilterMin() { return native_filter_min; }
  vuint32 GetNativeFilterMax() { return native_filter_max; }
  vuint32 GetNativeWrapS() { return native_wrap_s; }
  vuint32 GetNativeWrapT() { return native_wrap_t; }
  vuint32 GetNativeWrapR() { return native_wrap_r; }
  vuint32 GetNativeDataType() { return native_datatype; }

  vvoid SetMultisampled(vbool enable) override { m_multisampled = enable; }
  vbool IsMultisampled() override { return m_multisampled; }

  virtual vvoid SetHeight(vint32 height) override = 0;
  virtual vvoid SetDepth(vint32 depth) override = 0;
  virtual vint32 GetHeight() override = 0;
  virtual vint32 GetDepth() override = 0;

  /**
    Cleanup the Texture value if needed.
  */
  vvoid Cleanup() override { glDeleteTextures(1, &id); id = Texture::kNoTextureId; }

protected:
  vvoid SetPixelStore();
  vuint32 id                          = 0;

  vuint32 native_target               = GL_TEXTURE_2D;
  vuint32 native_format               = GL_RGBA;
  vuint32 native_internal_format      = GL_RGBA32UI;
  vuint32 native_filter_min           = GL_LINEAR_MIPMAP_LINEAR;
  vuint32 native_datatype             = GL_UNSIGNED_INT;
  vuint32 native_filter_max           = GL_LINEAR;
  vuint32 native_wrap_s               = GL_REPEAT;
  vuint32 native_wrap_t               = GL_REPEAT;
  vuint32 native_wrap_r               = GL_REPEAT;

  /**
    Clean the Shader params.
  */
  vvoid CleanParams();
};
} // vikr
#endif // __VIKR_GLTEXTURE_HPP