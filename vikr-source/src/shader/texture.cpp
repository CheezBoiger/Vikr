//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/shader/texture.hpp>
#include <vikr/util/vikr_log.hpp>
#include <vikr/util/vikr_assert.hpp>

#include <vikr/shader/stb/stb_image.h>


namespace vikr {


const std::string Texture::kDefaultName = "default_texture";
const vuint32 Texture::kNoTextureId = -1;
guid_t Texture::count = 0;


Texture::~Texture()
{
}


vbyte *Texture::CreateImageByteCode(std::string tex_path, vint32 *width, vint32 *height, vint32 *channels, vbool alpha) {
  stbi_uc *image = stbi_load(tex_path.c_str(), width, height, channels, alpha ? STBI_rgb_alpha : STBI_rgb);
  if (!image) {
    VIKR_ASSERTION(!image);
    image = nullptr;
  }
  return image;
}


vvoid Texture::SetByteCode(vbyte *bytecode, vbool is_stbi) {
  if (m_bytecode && is_stbi) {
    stbi_image_free(m_bytecode);
  }
  m_bytecode = bytecode; 
}
} // vikr