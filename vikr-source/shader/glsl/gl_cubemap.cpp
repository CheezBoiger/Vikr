//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <shader/glsl/gl_cubemap.hpp>
#include <shader/glsl/gl_texture2d.hpp>


namespace vikr { 


const vuint32 SHADOW_WIDTH = 1024;
const vuint32 SHADOW_HEIGHT = 1024;


GLCubemap::GLCubemap()
{
}


/**
  We will need to figure out something to work this crap. Empty vector will produce
  a depth cubemap instead.
*/
vvoid GLCubemap::Generate(std::vector<const vchar *> faces) {
  glGenTextures(1, &m_id);
  glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
  const vbyte *img;
  vint32 width, height;
  for (vuint32 i = 0; i < 6; ++i) {
    if (faces.empty()) {
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
        0, 
        GL_DEPTH_COMPONENT, 
        SHADOW_WIDTH, 
        SHADOW_HEIGHT, 
        0, 
        GL_DEPTH_COMPONENT, 
        GL_FLOAT, 
        0);
    } else {
      img = Texture::CreateImageByteCode(faces[i], &width, &height, 0, false);
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
        0, 
        GL_RGB,
        width,
        height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        img);
      stbi_image_free((vvoid *)img);
    }
  }
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
} // vikr