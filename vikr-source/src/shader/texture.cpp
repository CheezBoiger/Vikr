//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/shader/texture.hpp>
#include <vikr/util/vikr_log.hpp>
#include <vikr/util/vikr_assert.hpp>


namespace vikr {


const std::string Texture::kDefaultName = "default_texture";


vbyte *Texture::CreateImageByteCode(std::string tex_path, vint32 *width, vint32 *height, vint32 *channels, vbool alpha) {
  stbi_uc *image = stbi_load(tex_path.c_str(), width, height, channels, alpha ? STBI_rgb_alpha : STBI_rgb);
  if (!image) {
    VIKR_ASSERTION(!image);
    image = nullptr;
  }
  return image;
}
} // vikr