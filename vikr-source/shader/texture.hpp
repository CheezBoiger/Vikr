//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_TEXTURE_HPP
#define __VIKR_TEXTURE_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <shader/stb/stb_image.h>
#include <string>

namespace vikr {


/**
  Texture wrap mode depending on the 
  s, t, r texture coordinates.
*/
enum TextureWrapMode {
  vikr_TEXTURE_REPEAT,
  vikr_TEXTURE_MIRRORED_REPEAT,
  vikr_TEXTURE_CLAMP_TO_EDGE,
  vikr_TEXTURE_CLAMP_TO_BORDER
};


/**
  Filter mode, depending on distance from the view.
*/
enum TextureFilterMode {
  vikr_TEXTURE_NEAREST,
  vikr_TEXTURE_LINEAR,
  vikr_TEXTURE_NEAREST_MIPMAP_NEAREST,
  vikr_TEXTURE_LINEAR_MIPMAP_NEAREST,
  vikr_TEXTURE_LINEAR_MIPMAP_LINEAR,
  vikr_TEXTURE_NEAREST_MIPMAP_LINEAR
};


/**
  Texture type, or target, for the 
  Texture object.
*/
enum TextureTarget {
  vikr_TEXTURE_2D,
  vikr_TEXTURE_3D,
  vikr_TEXTURE_CUBEMAP
};


enum TextureFormat {
  vikr_RGB,
  vikr_RGBA
};


/**
  Texture object, abstraction.
*/
class Texture {
protected:
  static const std::string kDefaultName;
public:
  /**
    Generates bytecode for the provided image;
  */
  static vbyte *CreateImageByteCode(std::string tex_path, 
            vint32 *width, vint32 *height, vint32 *channels, vbool alpha);

  TextureTarget GetTargetFormat() { return m_target; }
  TextureFormat GetFormat() { return m_format; }
  TextureFormat GetInternalFormat() { return m_internal_format; }
  TextureFilterMode GetFilterMin() { return m_filter_min; }
  TextureFilterMode GetFilterMax() {  return m_filter_max; }
  TextureWrapMode GetWrapS() { return m_wrap_s; }
  TextureWrapMode GetWrapT() { return m_wrap_t; }
  TextureWrapMode GetWrapR() { return m_wrap_r; }
  vbool IsMipmapping() { return m_mipmapping; }
  vint32 GetWidth() { return m_width; }

  virtual vint32 Create(vbyte *bytecode) = 0;

  virtual vvoid Bind(vint32 id = -1) = 0;
  virtual vvoid Unbind() = 0;

  virtual vvoid SetFormat(TextureFormat format) = 0;
  virtual vvoid SetInternalFormat(TextureFormat format) = 0;
  virtual vvoid SetFilterMin(TextureFilterMode filter) = 0;
  virtual vvoid SetFilterMax(TextureFilterMode filter) = 0;
  virtual vvoid SetWrapS(TextureWrapMode mode) = 0;
  virtual vvoid SetWrapT(TextureWrapMode mode) = 0;
  virtual vvoid SetWrapR(TextureWrapMode mode) = 0;

  vvoid SetMipmapping(vbool mipmap) { m_mipmapping = mipmap; }

  vvoid SetWidth(vint32 width) { m_width = width; }

protected:

  TextureTarget     m_target                    = vikr_TEXTURE_2D;
  TextureFormat     m_format                    = vikr_RGBA;
  TextureFormat     m_internal_format           = vikr_RGBA;
  TextureFilterMode m_filter_min                = vikr_TEXTURE_LINEAR_MIPMAP_LINEAR;
  TextureFilterMode m_filter_max                = vikr_TEXTURE_LINEAR;
  TextureWrapMode   m_wrap_s                    = vikr_TEXTURE_REPEAT;
  TextureWrapMode   m_wrap_t                    = vikr_TEXTURE_REPEAT;
  TextureWrapMode   m_wrap_r                    = vikr_TEXTURE_REPEAT;
  vbool             m_mipmapping                = true;
  vbool             m_alpha                     = true;
  vuint32           m_width                     = 0;

private:
  VIKR_DISALLOW_COPY_AND_ASSIGN(Texture);
};
} // vikr
#endif // __VIKR_TEXTURE_HPP