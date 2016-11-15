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
  Texture object, currently only supporting OpenGL.
*/
class Texture {
public:
  Texture() { }
  static Texture Generate(std::string texture_path);
  
  Texture(Texture&& texture) = default;
  vvoid Bind();

protected:
  vuint32 m_id;
  
  vint32 width;
  vint32 height;
  vint32 channels;
  vint32 depth; // not really needed, maybe?

  static stbi_uc *CreateTextureImage(std::string tex_path, vint32 *width, vint32 *height, vint32 *channels);

private:
  VIKR_DISALLOW_COPY_AND_ASSIGN(Texture);
};
} // vikr
#endif // __VIKR_TEXTURE_HPP