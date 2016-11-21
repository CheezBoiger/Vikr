//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <shader/texture.hpp>
#include <util/vikr_log.hpp>
#include <util/vikr_assert.hpp>


namespace vikr {


const std::string Texture::kDefaultName = "default_texture";


Texture Texture::Generate(std::string texture_path, vbool has_alpha, vbool is_mipmapped) {
  Texture texture;
  texture.contains_alpha = has_alpha;
  texture.uses_mipmap = is_mipmapped;
  stbi_uc *image = Texture::CreateTextureImage(texture_path, &texture.width, &texture.height, &texture.channels, has_alpha);
  
  // TODO(Garcia): Perform texture binding.
  texture.Bind(image);
  stbi_image_free(image);
  return std::move(texture);
}


stbi_uc *Texture::CreateTextureImage(std::string tex_path, vint32 *width, vint32 *height, vint32 *channels, vbool alpha) {
  stbi_uc *image = stbi_load(tex_path.c_str(), width, height, channels, alpha ? STBI_rgb_alpha : STBI_rgb);
  if (!image) {
    VIKR_ASSERTION(!image);
    image = nullptr;
  }
  return image;
}

/*
  TODO(Garcia): Need to figure out how to not tightly pack OpenGL into Textures.
*/
vvoid Texture::GenerateTextureId() {
  if (!m_id) {
    GenTextures(1, &m_id);
  }
}


vvoid Texture::Bind(stbi_uc *image) {
  GenerateTextureId();
  BindTexture(GL_TEXTURE_2D, m_id);
  TexImage2D(GL_TEXTURE_2D, 
                0, 
                contains_alpha ? GL_RGBA : GL_RGB, 
                width, 
                height, 
                0, 
                contains_alpha ? GL_RGBA : GL_RGB,
                GL_UNSIGNED_BYTE, 
                image);
  if (uses_mipmap) {
    GenerateMipmap(GL_TEXTURE_2D);
  }
  TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, contains_alpha ? GL_CLAMP_TO_EDGE : GL_REPEAT);
  TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, contains_alpha ? GL_CLAMP_TO_EDGE : GL_REPEAT);
  TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  BindTexture(GL_TEXTURE_2D, 0);
}
} // vikr