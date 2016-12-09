// 
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_GLTEXTURE_HPP
#define __VIKR_GLTEXTURE_HPP

#include <shader/texture.hpp>


namespace vikr {


class GLTexture : public Texture {
protected:
  GLenum GetNativeWrapMode(TextureWrapMode mode);
  GLenum GetNativeFilterMode(TextureFilterMode mode);
  GLenum GetNativeTextureTarget(TextureTarget target);
  GLenum GetNativeTextureFormat(TextureFormat format);
public:
  GLTexture();


  virtual vint32 Create(vbyte *bytecode) override = 0;
  virtual vvoid Bind(vint32 texture = -1) override;
  virtual vvoid Unbind() override;

  vvoid SetFormat(TextureFormat format) override;
  vvoid SetInternalFormat(TextureFormat format) override;
  vvoid SetFilterMin(TextureFilterMode filter) override;
  vvoid SetFilterMax(TextureFilterMode filter) override;
  vvoid SetWrapS(TextureWrapMode mode) override;
  vvoid SetWrapT(TextureWrapMode mode) override;
  vvoid SetWrapR(TextureWrapMode mode) override;
  vuint32 GetNativeId() override { return id; }

  vuint32 GetNativeFormat() { return native_format; }
  vuint32 GetNativeTarget() { return native_target; }
  vuint32 GetNativeInternalFormat() { return native_internal_format; }
  vuint32 GetFilterMin() { return native_filter_min; }
  vuint32 GetFilterMax() { return native_filter_max; }
  vuint32 GetNativeWrapS() { return native_wrap_s; }
  vuint32 GetNativeWrapT() { return native_wrap_t; }
  vuint32 GetNativeWrapR() { return native_wrap_r; }


protected:
  vuint32 id                          = 0;

  vuint32 native_target               = GL_TEXTURE_2D;
  vuint32 native_format               = GL_RGBA;
  vuint32 native_internal_format      = GL_RGBA;
  vuint32 native_filter_min           = GL_LINEAR_MIPMAP_LINEAR;
  vuint32 native_filter_max           = GL_LINEAR;
  vuint32 native_wrap_s               = GL_REPEAT;
  vuint32 native_wrap_t               = GL_REPEAT;
  vuint32 native_wrap_r               = GL_REPEAT;
};
} // vikr
#endif // __VIKR_GLTEXTURE_HPP