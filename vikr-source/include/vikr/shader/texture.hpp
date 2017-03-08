//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_TEXTURE_HPP
#define __VIKR_TEXTURE_HPP

#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>
#include <vikr/shader/texture_config.hpp>
#include <vikr/scene/guid_generator.hpp>
#include <string>

namespace vikr {


/**
  Texture object, abstraction. This is the texture that is associated with 
  Materials, Meshes, RenderTargets, Cubemaps, and SceneObjects.
*/
class Texture : public GUID {
protected:
  static const std::string kDefaultName;
public:
  static const vuint32 kNoTextureId;
  Texture() { }
  VIKR_DEFAULT_MOVE_AND_ASSIGN(Texture);

  virtual ~Texture();

  /**
    Generates bytecode for the provided image.
  */
  static vbyte *CreateImageByteCode(std::string filepath, 
            vint32 *width, vint32 *height, vint32 *channels, vbool alpha);

  /**
    Target format, intends to be the type of format that the texture is going to be.
    This can be a 1D, 2D, 3D, or cubemap.
  */
  TextureTarget GetTargetFormat() { return m_target; }
  ImageFormat GetFormat() { return m_format; }
  TextureFilterMode GetFilterMin() { return m_filter_min; }
  TextureFilterMode GetFilterMax() {  return m_filter_max; }

  /**
    Texture coordinate wrapping for coord S. 
  */
  TextureWrapMode GetWrapS() { return m_wrap_s; }

  /**
    Texture coordinate wrapping for coord t.
  */
  TextureWrapMode GetWrapT() { return m_wrap_t; }

  /**
    Texture coordinate wrapping for coord r.
  */
  TextureWrapMode GetWrapR() { return m_wrap_r; }

  /**
    Determines if the Texture is mipmapped.
  */
  vbool IsMipmapping() { return m_mipmapping; }

  /**
    Get the width of the texture image.
  */
  vint32 GetWidth() { return m_width; }

  virtual vint32 GetHeight() = 0;
  virtual vint32 GetDepth() = 0;

  /**
    Get the path to the source image file of this texture.
  */
  std::string GetPath() { return m_path; }

  /**
    Get the name of this texture.
  */
  std::string GetName() { return m_name; }

  /**
    Create the Texture object.
  */
  virtual vint32 Finalize() = 0;

  /**
    Bind our texture object with the associated attachment point
    ( or, our id).
  */
  virtual vvoid Bind(vint32 id = -1) = 0;

  /**
    Unbind the texture from our Renderer.
  */
  virtual vvoid Unbind() = 0;

  /**
    Format represents the storage type of the texture. This can be RGB, RGBA, Depth, or
    ALPHA, etc.
  */
  virtual vvoid SetFormat(ImageFormat format) = 0;

  /**
  */
  virtual vvoid SetFilterMin(TextureFilterMode filter) = 0;

  /**
  */
  virtual vvoid SetFilterMax(TextureFilterMode filter) = 0;

  virtual vvoid SetTarget(TextureTarget target) = 0;

  /**
    Texture clamp modes. Tells our Rendering API how to clamp the texture onto 
    a Mesh or Quad. This is specified for coord S.
  */
  virtual vvoid SetWrapS(TextureWrapMode mode) = 0;

  /**
    Texture clamp modes. Tells our Rendering API how to clamp the texture onto
    a Mesh or Quad. This is specified for coord T.
  */
  virtual vvoid SetWrapT(TextureWrapMode mode) = 0;

  /**
    Texture clamp modes. Tells our Rendering API how to clamp the texture onto
    a Mesh or Quad. This is specified for coord R.
  */
  virtual vvoid SetWrapR(TextureWrapMode mode) = 0;

  virtual vbool IsMultisampled() = 0;

  virtual vvoid SetMultisampled(vbool enable) = 0;

  /**
    Set whether this texture needs to generate a mipmap for itself.
  */
  vvoid SetMipmapping(vbool mipmap) { m_mipmapping = mipmap; }
  /**
    Grab the path of the image file that this texture is going to load.
  */
  vvoid SetPath(std::string path) { m_path = path; }
  /**
    Width size of the texture object.
  */
  vvoid SetWidth(vint32 width) { m_width = width; }

  virtual vvoid SetHeight(vint32 height) = 0;
  virtual vvoid SetDepth(vint32 depth) = 0;

  vvoid SetName(std::string name) { m_name = name; }

  vvoid SetByteCode(vbyte *bytecode, vbool is_stbi = true);
  
  vbyte *GetBytecode() { return m_bytecode; }

  virtual vvoid Cleanup() = 0;

  vvoid SetSamples(vint32 samples) { m_samples = samples; }
  vint32 GetSamples() { return m_samples; }

protected:

  TextureTarget     m_target                    = vikr_TARGET_2D;
  ImageFormat     m_format                      = vikr_FORMAT_R8G8B8A8_UINT;
  TextureFilterMode m_filter_min                = vikr_FILTER_LINEAR_MIPMAP_LINEAR;
  TextureFilterMode m_filter_max                = vikr_FILTER_LINEAR;
  TextureWrapMode   m_wrap_s                    = vikr_WRAP_REPEAT;
  TextureWrapMode   m_wrap_t                    = vikr_WRAP_REPEAT;
  TextureWrapMode   m_wrap_r                    = vikr_WRAP_REPEAT;
  vbool             m_mipmapping                = true;
  vbool             m_alpha                     = true;
  vbool             m_multisampled              = false;
  vint32            m_width                     = 0;
  vint32            m_samples                   = 4;
  std::string       m_path                      = "";
  std::string       m_name                      = "noname";
  vbyte             *m_bytecode                 = nullptr;

private:
  VIKR_DISALLOW_COPY_AND_ASSIGN(Texture);
};
} // vikr
#endif // __VIKR_TEXTURE_HPP