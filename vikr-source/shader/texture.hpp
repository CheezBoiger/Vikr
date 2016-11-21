//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_TEXTURE_HPP
#define __VIKR_TEXTURE_HPP

#include <platform/vikr_types.hpp>
#include <platform/vikr_api.hpp>
#include <shader/stb/stb_image.h>
#include <shader/itexture.hpp>
#include <string>

namespace vikr {


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
  Texture object, currently only supporting OpenGL.
*/
class Texture : public ITexture {
  static const std::string kDefaultName;
public:

  static Texture Generate(std::string texture_path, vbool has_alpha = true, vbool is_mipmapped = true);
  
  Texture(Texture&& texture) = default;
  vint32 GetWidth() override { return width; }
  vint32 GetHeight() override { return height; }
  vbool ContainsAlpha() override { return contains_alpha; }
  vuint32 GetId() override { return m_id; }

protected:

  Texture(std::string name = kDefaultName
          , TextureTarget target = vikr_TEXTURE_2D
          , vbool has_alpha = false)
    : m_id(0)
    , name(name)
    , width(0)
    , height(0)
    , depth(0)
    , channels(0)
    , target(target)
    , contains_alpha(has_alpha) { }

  std::string name;
  vvoid Bind(stbi_uc *image);
  vvoid GenerateTextureId();
  vuint32 m_id;
  
  vint32 width;
  vint32 height;
  vint32 channels;
  vint32 depth;
  TextureTarget target;
  vbool contains_alpha;
  vbool uses_mipmap;

  static stbi_uc *CreateTextureImage(std::string tex_path
                                    , vint32 *width
                                    , vint32 *height
                                    , vint32 *channels
                                    , vbool alpha);

private:
  VIKR_DISALLOW_COPY_AND_ASSIGN(Texture);
};
} // vikr
#endif // __VIKR_TEXTURE_HPP