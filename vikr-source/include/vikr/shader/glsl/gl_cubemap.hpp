//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_GL_CUBE_MAP_HPP
#define __VIKR_GL_CUBE_MAP_HPP


#include <vikr/shader/cubemap.hpp>
#include <vikr/shader/glsl/gl_texture.hpp>

namespace vikr {


class GL4Cubemap : public Cubemap, public GLTexture {
public:

  GL4Cubemap();

  vvoid Load(std::vector<const vchar *> *faces_path = nullptr) override;

  vuint32 GetNativeId() override { return id; }

  vint32 Finalize() override;

  vvoid SetMagFilter(TextureFilterMode mode) override 
    { GLTexture::SetFilterMax(mode); }

  vvoid SetMinFilter(TextureFilterMode mode) override
    { GLTexture::SetFilterMin(mode); }

  vvoid SetWrapS(TextureWrapMode mode) override
    { GLTexture::SetWrapS(mode); }

  vvoid SetWrapT(TextureWrapMode mode) override 
    { GLTexture::SetWrapT(mode); }

  vvoid SetWrapR(TextureWrapMode mode) override
    { GLTexture::SetWrapR(mode); }

  vvoid OverrideFaceWidth(vuint32 val) override
    { overriding = true; image_width = val; }

  vvoid OverrideFaceHeight(vuint32 val) override
    { overriding = true; image_height = val; }

  vvoid Cleanup() override
    { GLTexture::Cleanup(); } 

  vvoid ClearSizeOverride() override
    { overriding = false; }

  vvoid SetHeight(vint32 height) override
    { OverrideFaceHeight(static_cast<vint32>(height)); }

  vvoid SetDepth(vint32 depth) override 
    { image_channels = depth; }

  vint32 GetHeight() override 
    { return image_height; }

  vint32 GetDepth() override
    { return image_channels; }

  guid_t GetUID() override 
    { return GLTexture::GetUID(); }

private:
  std::vector<const vchar *> *m_faces = nullptr;
  
  vbool overriding = false;

  vint32 image_width;
  vint32 image_height;
  vint32 image_channels;
};
} // vikr
#endif // __VIKR_GL_CUBE_MAP_HPP