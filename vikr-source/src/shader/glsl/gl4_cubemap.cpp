//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <vikr/shader/glsl/gl4_cubemap.hpp>
#include <vikr/shader/glsl/gl4_texture2d.hpp>

#include <vikr/shader/stb/stb_image.h>
#include <vikr/util/vikr_assert.hpp>

namespace vikr { 


#define GL_MAX_CUBE_MAP_FACES 6


const vuint32 SHADOW_WIDTH = 1024;
const vuint32 SHADOW_HEIGHT = 1024;


GL4Cubemap::GL4Cubemap()
{
  GL4Texture::SetTarget(vikr_TARGET_CUBEMAP);
  GL4Texture::SetFilterMin(vikr_FILTER_LINEAR);
  GL4Texture::SetWrapS(vikr_WRAP_CLAMP_TO_EDGE);
  GL4Texture::SetWrapT(vikr_WRAP_CLAMP_TO_EDGE);
  GL4Texture::SetWrapR(vikr_WRAP_CLAMP_TO_EDGE);
  GL4Texture::SetFormat(vikr_FORMAT_R8G8B8_UINT);
}


vvoid GL4Cubemap::Load(std::vector<const vchar *> *face_path) {
  m_faces = face_path;
  Finalize();
}


vint32 GL4Cubemap::Finalize() {
  m_target = vikr_TARGET_CUBEMAP;
  native_target = GL4Texture::GetNativeTextureTarget(m_target);
  SetPixelStore();
  if (id == Texture::kNoTextureId) {
    glGenTextures(1, &id);
  }
  glActiveTexture(GL_TEXTURE0);
  vint32 width, height, channels;
  vbyte *image;
  glBindTexture(GL_TEXTURE_CUBE_MAP, id);
  for (vuint32 i = 0; i < GL_MAX_CUBE_MAP_FACES; ++i) {
    if (m_faces && (i < m_faces->size())) {
      image = GL4Texture::CreateImageByteCode(
        (*m_faces)[i], &width, &height, &channels, false);
    } else {
      image = nullptr;
    }
    VIKR_ASSERT(glGetError() == 0);
    if (overriding) {
      width = image_width;
      height = image_height;
      channels = image_channels;
    } else {
      image_width = width;
      image_height = height;
      image_channels = channels;
    }
    glTexImage2D(
      GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
      0,
      native_internal_format,
      width,
      height,
      0,
      native_format,
      native_datatype, 
      image
    ); 
    GLenum err = glGetError();
    VikrLog::DisplayMessage(VIKR_RUNTIME_DEBUG, "Cubemap Error Status: " + std::to_string(err));
    VIKR_ASSERT(err == 0);
  }
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, native_filter_min);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, native_filter_max);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, native_wrap_s);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, native_wrap_t);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, native_wrap_r);
  VIKR_ASSERT(glGetError() == 0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
  return 1;
}
} // vikr