//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/shader/glsl/gl_cubemap.hpp>
#include <vikr/shader/glsl/gl_texture2d.hpp>

#include <vikr/shader/stb/stb_image.h>
#include <vikr/util/vikr_assert.hpp>

namespace vikr { 


const vuint32 SHADOW_WIDTH = 1024;
const vuint32 SHADOW_HEIGHT = 1024;


GL4Cubemap::GL4Cubemap()
{
  GLTexture::SetTarget(vikr_TEXTURE_CUBEMAP);
}


vvoid GL4Cubemap::Load(std::vector<const vchar *> &face_path) {
  m_faces = std::move(face_path);
  Finalize();
}


vint32 GL4Cubemap::Finalize() {
  m_target = vikr_TEXTURE_CUBEMAP;
  native_target = GLTexture::GetNativeTextureTarget(m_target);
  glGenTextures(1, &id);
  glActiveTexture(GL_TEXTURE0);
  vint32 width, height, channels;
  vbyte *image;
  glBindTexture(GL_TEXTURE_CUBE_MAP, id);
  for (vuint32 i = 0; i < m_faces.size(); ++i) {
    image = GLTexture::CreateImageByteCode(
      m_faces[i], &width, &height, &channels, false);
    glTexImage2D(
      GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
      0,
      GL_RGB,
      width,
      height,
      0,
      GL_RGB,
      GL_UNSIGNED_BYTE, 
      image
    ); 
    VIKR_ASSERT(glGetError() == 0);
  }
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  VIKR_ASSERT(glGetError() == 0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
  return 1;
}
} // vikr