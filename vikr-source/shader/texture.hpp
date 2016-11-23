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


enum TextureWrapMode {
  vikr_TEXTURE_REPEAT,
  vikr_TEXTURE_MIRRORED_REPEAT,
  vikr_TEXTURE_CLAMP_TO_EDGE,
  vikr_TEXTURE_CLAMP_TO_BORDER
};


enum TextureFilterMode {
  vikr_TEXTURE_NEAREST,
  vikr_TEXTURE_LINEAR,
  vikr_TEXTURE_NEAREST_MIPMAP_NEAREST,
  vikr_TEXTURE_LINEAR_MIPMAP_NEAREST,
  vikr_TEXTURE_LINEAR_MIPMAP_LINEAR,
  vikr_TEXTURE_NEAREST_MIPMAP_LINEAR
};


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
  static vbyte *CreateImageByteCode(std::string tex_path, vint32 *width, vint32 *height, vint32 *channels, vbool alpha);

  TextureTarget GetTargetFormat() { return m_target; }
  TextureFormat GetFormat() { return m_format; }
  TextureFormat GetInternalFormat() { return m_internal_format; }
  TextureFilterMode GetFilterMin() { return m_filter_min; }
  TextureFilterMode GetFilterMax() {  return m_filter_max; }
  vbool IsMipmapping() { return mipmapping; }

protected:
  TextureTarget m_target;
  TextureFormat m_format;
  TextureFormat m_internal_format;
  TextureFilterMode m_filter_min;
  TextureFilterMode m_filter_max;
  vbool mipmapping;
private:
  VIKR_DISALLOW_COPY_AND_ASSIGN(Texture);
};
} // vikr
#endif // __VIKR_TEXTURE_HPP