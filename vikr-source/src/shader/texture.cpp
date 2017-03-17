//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/shader/texture.hpp>
#include <vikr/util/vikr_log.hpp>
#include <vikr/util/vikr_assert.hpp>

#include <vikr/shader/stb/stb_image.h>


namespace vikr {


const std::string Texture::kDefaultName = "default_texture";
const vuint32 Texture::kNoTextureId = 0;


Texture::~Texture()
{
}


vbyte *Texture::CreateImageByteCode(
  std::string filepath, 
  vint32 *width, 
  vint32 *height, 
  vint32 *channels, 
  vbool alpha) 
{
  stbi_uc *image = stbi_load(filepath.c_str(), width, height, channels, alpha ? STBI_rgb_alpha : STBI_rgb);
  if (!image) {
    VIKR_ASSERTION(!image);
    image = nullptr;
  }
  return image;
}


vvoid Texture::FreeImageByteCode(vbyte *bytecode)
{
  if (bytecode) {
    stbi_image_free(bytecode);
    bytecode = nullptr;
  }
}
} // vikr