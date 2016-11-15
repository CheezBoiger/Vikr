#include <shader/texture.hpp>
#include <util/vikr_log.hpp>


namespace vikr {


Texture Texture::Generate(std::string texture_path) {
  Texture texture;
  stbi_uc *image = Texture::CreateTextureImage(texture_path, &texture.width, &texture.height, &texture.channels);
  
  // TODO(Garcia): Perform texture binding.

  stbi_image_free(image);
  return std::move(texture);
}


stbi_uc *Texture::CreateTextureImage(std::string tex_path, vint32 *width, vint32 *height, vint32 *channels) {
  stbi_uc *image = stbi_load(tex_path.c_str(), width, height, channels, STBI_rgb_alpha);
  if (!image) {
    image = nullptr;
  }
  return image;
}
} // vikr